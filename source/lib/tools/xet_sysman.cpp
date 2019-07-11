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
/// @brief Creates a handle to access SMI features
/// 
/// @details
///     - Initializes internal structures to support SMI features.
///     - If the write flag ::XET_SYSMAN_INIT_FLAGS_WRITE is specified, no
///       access right checks are made during initialization. The check is done
///       in functions that attempt to control a device.
///     - If the write flag ::XET_SYSMAN_INIT_FLAGS_WRITE is not specified, any
///       function attempting to control a device will return
///       ::XE_RESULT_ACCESS_DENIED.
///     - Multiple SMI handles can be created for the same device group and
///       concurrent access through each handle to access underlying hardware
///       resources is supported.
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
///         + nullptr == hDeviceGroup
///         + nullptr == phSysman
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanCreate(
    xet_device_group_handle_t hDeviceGroup,         ///< [in] Handle of the device group
    xet_sysman_version_t version,                   ///< [in] SMI version that application was built with
    uint32_t flags,                                 ///< [in] Bitfield of ::xet_sysman_init_flags_t
    xet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing SMI features
    )
{
    auto pfnCreate = xet_lib::context.ddiTable.Sysman.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hDeviceGroup, version, flags, phSysman );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a Sysman handle
/// 
/// @details
///     - Only once all SMI handles to a device group have been destroyed will
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
/// @brief Convert SMI resource UUID to a string
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
///         + nullptr == pUuid
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanConvertUuidToString(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    const xet_resource_uuid_t* pUuid,               ///< [in] Pointer to a Sysman UUID
    uint32_t* pSize,                                ///< [in,out] Pointer to the size of the string buffer pointed to by pStr.
                                                    ///< If size is zero, the storage size including end-of-string terminator
                                                    ///< will be returned.
                                                    ///< If size is non-zero and less than the required length, the storage
                                                    ///< size including end-of-string terminator will be returned and an error
                                                    ///< status given.
                                                    ///< If size is non-zero and larger than the required length, the number of
                                                    ///< characters stored in the buffer including the end-of-string terminator
                                                    ///< will be returned.
    char* pStr                                      ///< [in][optional] Pointer to storage for the string representation of the
                                                    ///< UUID
    )
{
    auto pfnConvertUuidToString = xet_lib::context.ddiTable.Sysman.pfnConvertUuidToString;
    if( nullptr == pfnConvertUuidToString )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnConvertUuidToString( hSysman, pUuid, pSize, pStr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves resources of a given type having a specified parent resource
/// 
/// @details
///     - If a parent resource is not specified, then all resources of the given
///       type are returned. Otherwise only resources directly contained
///       in/under the specified parent are returned.
///     - There is a one-to-many mapping between the underlying hardware for a
///       resource and the corresponding handles returned to the application.
///       Thus, the numerical value of the handles should not be compared with
///       those returned by previous function calls - instead, use the function
///       ::xetSysmanResourceIsSame() to check if two handles reference the same
///       hardware object.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == hParentResource
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetResources(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_resource_handle_t hParentResource,          ///< [in] Handle of the parent resource object (can be
                                                    ///< ::XET_INVALID_SYSMAN_RESOURCE_HANDLE)
    xet_resource_type_t type,                       ///< [in] The type of resources to enumerate
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array phResources.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of resources that would be returned.
                                                    ///< If count is non-zero, then driver will only retrieve that number of
                                                    ///< resources of the given type starting from index 0.
                                                    ///< If count is larger than the number of resource that will be returned,
                                                    ///< then the driver will update the value with actual number returned.
    xet_resource_handle_t* phResources              ///< [out][optional][range(0, *pCount)] Array of resources resources
    )
{
    auto pfnGetResources = xet_lib::context.ddiTable.Sysman.pfnGetResources;
    if( nullptr == pfnGetResources )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetResources( hSysman, hParentResource, type, pCount, phResources );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a resource handle for a device
/// 
/// @details
///     - The specified device must be in the same device group that was used to
///       create the SMI handle.
///     - If the device handle refers to a device, then a resource handle of
///       type ::XET_RESOURCE_TYPE_DEVICE_CONTAINER will be returned.
///     - If the device handle refers to a sub-device, then a resource handle of
///       type ::XET_RESOURCE_TYPE_SUBDEVICE_CONTAINER will be returned.
///     - There is a one-to-many mapping between the underlying hardware for a
///       resource and the corresponding handles returned to the application.
///       Thus, the numerical value of the handles should not be compared with
///       those returned by previous function calls - instead, use the function
///       ::xetSysmanResourceIsSame() to check if two handles reference the same
///       hardware object.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == hDevice
///         + nullptr == phResource
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_MISMATCH_DEVICE_GROUP
///         + The device does not belong to the device group that was ued to create the SMI handle
xe_result_t __xecall
xetSysmanGetDeviceResource(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xe_device_handle_t hDevice,                     ///< [in] Handle to the device.
    xet_resource_handle_t* phResource               ///< [out] Resource handle for the specified device
    )
{
    auto pfnGetDeviceResource = xet_lib::context.ddiTable.Sysman.pfnGetDeviceResource;
    if( nullptr == pfnGetDeviceResource )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDeviceResource( hSysman, hDevice, phResource );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a resource handle based on resource UUID
/// 
/// @details
///     - There is a one-to-many mapping between the underlying hardware for a
///       resource and the corresponding handles returned to the application.
///       Thus, the numerical value of the handles should not be compared with
///       those returned by previous function calls - instead, use the function
///       ::xetSysmanResourceIsSame() to check if two handles reference the same
///       hardware object.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == uuid
///         + nullptr == phResource
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_FOUND
///         + No resource could be found with the specified UUID
xe_result_t __xecall
xetSysmanGetResourceByUuid(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    const xet_resource_uuid_t* uuid,                ///< [in] UUID for the resource
    xet_resource_handle_t* phResource               ///< [out] Resource handle
    )
{
    auto pfnGetResourceByUuid = xet_lib::context.ddiTable.Sysman.pfnGetResourceByUuid;
    if( nullptr == pfnGetResourceByUuid )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetResourceByUuid( hSysman, uuid, phResource );
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
///         + nullptr == hResource
///         + nullptr == pCount
///         + nullptr == pErrors
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_TOO_SMALL
///         + The array doesn't have enough elements to store all the errors
xe_result_t __xecall
xetSysmanGetRasErrors(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource. If specified, only errors within that
                                                    ///< resource of child resources are returned. Otherwise all errors are
                                                    ///< returned.
    uint32_t type,                                  ///< [in] Bitfield of error types to filter - one or more of
                                                    ///< ::xet_ras_error_type_t. Set to ::XET_RAS_ERROR_TYPE_ALL to have all
                                                    ///< error types returned.
    uint32_t location,                              ///< [in] Bitfield of error locations to filter - one or more of
                                                    ///< ::xet_ras_error_loc_t. Set to ::XET_RAS_ERROR_LOC_ALL to have all
                                                    ///< error locations returned.
    uint32_t threshold,                             ///< [in] Only return error elements that have occurred at least this
                                                    ///< number of times.
                                                    ///< If set to 0, will get a list of all possible RAS elements, even those
                                                    ///< that have not had errors.
                                                    ///< For error elements of type ::XET_RAS_DATA_TYPE_OCCURRED, there is no
                                                    ///< underlying counter, so they will always be returned independent of the
                                                    ///< threshold setting.
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
    xet_res_error_t* pErrors                        ///< [in] Array of error data
    )
{
    auto pfnGetRasErrors = xet_lib::context.ddiTable.Sysman.pfnGetRasErrors;
    if( nullptr == pfnGetRasErrors )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetRasErrors( hSysman, hResource, type, location, threshold, clear, pCount, pErrors );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Compare if two resource handles reference the same underlying hardware
///        object
/// 
/// @details
///     - There is a one-to-many mapping between the underlying hardware for a
///       resource and the corresponding handles returned to the application.
///       Thus, the numerical value of the handles should not be compared with
///       those returned by previous function calls - instead, use this function
///       to check if two handles reference the same hardware object.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hLhs
///         + nullptr == hRhs
///         + nullptr == pIsSame
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceIsSame(
    xet_resource_handle_t hLhs,                     ///< [in] Handle of of the resources
    xet_resource_handle_t hRhs,                     ///< [in] Handle of the other resource
    xe_bool_t* pIsSame                              ///< [in] Sets to True if the two resources reference the same underlying
                                                    ///< hardware object
    )
{
    auto pfnIsSame = xet_lib::context.ddiTable.SysmanResource.pfnIsSame;
    if( nullptr == pfnIsSame )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnIsSame( hLhs, hRhs, pIsSame );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get generic information about a resource
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
///         + nullptr == hResource
///         + nullptr == pInfo
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetInfo(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    xet_resource_info_t* pInfo                      ///< [out] Generic information about the resource
    )
{
    auto pfnGetInfo = xet_lib::context.ddiTable.SysmanResource.pfnGetInfo;
    if( nullptr == pfnGetInfo )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetInfo( hResource, pInfo );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get a handle to the parent resource
/// 
/// @details
///     - For resource containers, this will return the handle to parent
///       container. For non-container resources, this will return the handle to
///       the container resource in which the resource is located.
///     - If there is no parent (e.g. resources of type
///       ::XET_RESOURCE_TYPE_UNIT_CONTAINER), the returned handle will be
///       ::XET_INVALID_SYSMAN_RESOURCE_HANDLE.
///     - There is a one-to-many mapping between the underlying hardware for a
///       resource and the corresponding handles returned to the application.
///       Thus, the numerical value of the handles should not be compared with
///       those returned by previous function calls - instead, use the function
///       ::xetSysmanResourceIsSame() to check if two handles reference the same
///       hardware object.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hResource
///         + nullptr == phResource
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetParent(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    xet_resource_handle_t* phResource               ///< [out] Handle of the parent resource
    )
{
    auto pfnGetParent = xet_lib::context.ddiTable.SysmanResource.pfnGetParent;
    if( nullptr == pfnGetParent )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetParent( hResource, phResource );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get children resources
/// 
/// @details
///     - If the parent resource is not a container, no children resources will
///       be returned.
///     - Only resource containers will be returned by this function. The
///       function ::xetSysmanGetResources should be used to get non-container
///       resources located in a parent resource.
///     - There is a one-to-many mapping between the underlying hardware for a
///       resource and the corresponding handles returned to the application.
///       Thus, the numerical value of the handles should not be compared with
///       those returned by previous function calls - instead, use the function
///       ::xetSysmanResourceIsSame() to check if two handles reference the same
///       hardware object.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hResource
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetChildren(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array phResources.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of child resources.
                                                    ///< If count is non-zero, then driver will only retrieve that number of
                                                    ///< child resources starting from index 0.
                                                    ///< If count is larger than the number of child resources that will be
                                                    ///< returned, then the driver will update the value with the resources
                                                    ///< actually returned.
    xet_resource_handle_t* phResources              ///< [out][optional][range(0, *pCount)] Array of resource handles.
    )
{
    auto pfnGetChildren = xet_lib::context.ddiTable.SysmanResource.pfnGetChildren;
    if( nullptr == pfnGetChildren )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetChildren( hResource, pCount, phResources );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get peer resources
/// 
/// @details
///     - If the parent resource is not a container, no peer resources will be
///       returned.
///     - Only resource containers will be returned by this function. The
///       function ::xetSysmanGetResources should be used to get non-container
///       resources located in a parent resource.
///     - There is a one-to-many mapping between the underlying hardware for a
///       resource and the corresponding handles returned to the application.
///       Thus, the numerical value of the handles should not be compared with
///       those returned by previous function calls - instead, use the function
///       ::xetSysmanResourceIsSame() to check if two handles reference the same
///       hardware object.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hResource
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetPeers(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array phResources.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of peer resources.
                                                    ///< If count is non-zero, then driver will only retrieve that number of
                                                    ///< peer resources starting from index 0.
                                                    ///< If count is larger than the number of peer resources that will be
                                                    ///< returned, then the driver will update the value with the resources
                                                    ///< actually returned.
    xet_resource_handle_t* phResources              ///< [out][optional][range(0, *pCount)] Array of resource handles.
    )
{
    auto pfnGetPeers = xet_lib::context.ddiTable.SysmanResource.pfnGetPeers;
    if( nullptr == pfnGetPeers )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPeers( hResource, pCount, phResources );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get board property data
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_BOARD_CONTAINER
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetBoardProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_board_property_request_t* pRequest          ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetBoardProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetBoardProperties;
    if( nullptr == pfnGetBoardProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetBoardProperties( hResource, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get device container property data
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_DEVICE_CONTAINER
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetDeviceProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_device_property_request_t* pRequest         ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetDeviceProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetDeviceProperties;
    if( nullptr == pfnGetDeviceProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDeviceProperties( hResource, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set device container property data
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_DEVICE_CONTAINER
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetDeviceProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_device_property_request_t* pRequest         ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetDeviceProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetDeviceProperties;
    if( nullptr == pfnSetDeviceProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetDeviceProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_PSU
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetPsuProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_psu_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetPsuProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetPsuProperties;
    if( nullptr == pfnGetPsuProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPsuProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_PSU
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetPsuProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_psu_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetPsuProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetPsuProperties;
    if( nullptr == pfnSetPsuProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPsuProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_TEMP
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetTempProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_temp_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetTempProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetTempProperties;
    if( nullptr == pfnGetTempProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetTempProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_FAN
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetFanProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_fan_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetFanProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetFanProperties;
    if( nullptr == pfnGetFanProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetFanProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_FAN
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetFanProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_fan_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetFanProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetFanProperties;
    if( nullptr == pfnSetFanProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetFanProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_LED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetLedProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_led_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetLedProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetLedProperties;
    if( nullptr == pfnGetLedProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetLedProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_LED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetLedProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_led_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetLedProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetLedProperties;
    if( nullptr == pfnSetLedProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetLedProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_FIRMWARE
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetFirmwareProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_firmware_property_request_t* pRequest       ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetFirmwareProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetFirmwareProperties;
    if( nullptr == pfnGetFirmwareProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetFirmwareProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_FIRMWARE
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetFirmwareProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_firmware_property_request_t* pRequest       ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetFirmwareProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetFirmwareProperties;
    if( nullptr == pfnSetFirmwareProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetFirmwareProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_PWR
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetPwrProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_pwr_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetPwrProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetPwrProperties;
    if( nullptr == pfnGetPwrProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPwrProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_PWR
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetPwrProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_pwr_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetPwrProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetPwrProperties;
    if( nullptr == pfnSetPwrProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPwrProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_FREQ
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetFreqProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_freq_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetFreqProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetFreqProperties;
    if( nullptr == pfnGetFreqProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetFreqProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_FREQ
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetFreqProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_freq_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetFreqProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetFreqProperties;
    if( nullptr == pfnSetFreqProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetFreqProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_PWRWELL
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetPwrwellProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_pwrwell_property_request_t* pRequest        ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetPwrwellProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetPwrwellProperties;
    if( nullptr == pfnGetPwrwellProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPwrwellProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_PWRWELL
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetPwrwellProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_pwrwell_property_request_t* pRequest        ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetPwrwellProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetPwrwellProperties;
    if( nullptr == pfnSetPwrwellProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPwrwellProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_ACCEL
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetAccelProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_accel_property_request_t* pRequest          ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetAccelProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetAccelProperties;
    if( nullptr == pfnGetAccelProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetAccelProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_MEM
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetMemProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_mem_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetMemProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetMemProperties;
    if( nullptr == pfnGetMemProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_MEM
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetMemProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_mem_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetMemProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetMemProperties;
    if( nullptr == pfnSetMemProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetMemProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_LINK
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetLinkProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_link_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetLinkProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetLinkProperties;
    if( nullptr == pfnGetLinkProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetLinkProperties( hResource, count, pRequest );
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
///         + nullptr == hResource
///         + nullptr == pRequest
///         + The resource is not of type ::XET_RESOURCE_TYPE_LINK
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetLinkProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_link_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetLinkProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetLinkProperties;
    if( nullptr == pfnSetLinkProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetLinkProperties( hResource, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Register to receive events
/// 
/// @details
///     - This will only register the specified list of events. If other events
///       have been registered, notifications for them will continue.
///     - Applies only to devices in the specified SMI handle.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == hResource
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanRegisterEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_resource_handle_t hResource,                ///< [in] Handle of the parent resource. Events from any contained devices
                                                    ///< will be registered.
                                                    ///< If the handle is ::XET_INVALID_SYSMAN_RESOURCE_HANDLE, events from all
                                                    ///< devices will be registered.
    uint32_t events                                 ///< [in] Bitfield of events to register.
                                                    ///< Construct by ORing (1<<::xet_sysman_event_type_t).
                                                    ///< Set to (~0) to register to receive all events.
    )
{
    auto pfnRegisterEvents = xet_lib::context.ddiTable.Sysman.pfnRegisterEvents;
    if( nullptr == pfnRegisterEvents )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnRegisterEvents( hSysman, hResource, events );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Unregister events
/// 
/// @details
///     - This will only unregister the specified list of events. If other
///       events have been registered, notifications for them will continue.
///     - Applies only to devices in the specified SMI handle.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == hResource
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanUnregisterEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_resource_handle_t hResource,                ///< [in] Handle of the parent resource. Events from any contained devices
                                                    ///< will be unregistered.
                                                    ///< If the handle is ::XET_INVALID_SYSMAN_RESOURCE_HANDLE, events from all
                                                    ///< devices will be unregistered.
    uint32_t events                                 ///< [in] Bitfield of events to unregister.
                                                    ///< Construct by ORing (1<<::xet_sysman_event_type_t).
                                                    ///< Set to (~0) to unregister all events.
    )
{
    auto pfnUnregisterEvents = xet_lib::context.ddiTable.Sysman.pfnUnregisterEvents;
    if( nullptr == pfnUnregisterEvents )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnUnregisterEvents( hSysman, hResource, events );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Listen for events
/// 
/// @details
///     - This will only unregister the specified list of events. If other
///       events have been registered, notifications for them will continue.
///     - Applies only to devices in the specified SMI handle.
///     - At most, one event data per device will be returned.
///     - If event data is returned, the corresponding event status is cleared.
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
///         + nullptr == pEventData
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanListenEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xe_bool_t block,                                ///< [in] If set to true, the call will block the calling thread
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array pointed to by pEventData.
                                                    ///< If size is zero, then the driver will update the value with the number
                                                    ///< of elements needed to retrieve the list of events.
                                                    ///< If size is less than that required to store the list of events, the
                                                    ///< driver will update the value with the required number of elements and
                                                    ///< return an error.
                                                    ///< If size is larger than that required to store the list of events, the
                                                    ///< driver will update the value with the number of elements actually returned.
    xet_sysman_event_data_t* pEventData             ///< [in] Pointer to an array of event data
    )
{
    auto pfnListenEvents = xet_lib::context.ddiTable.Sysman.pfnListenEvents;
    if( nullptr == pfnListenEvents )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnListenEvents( hSysman, block, pCount, pEventData );
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
    SysmanResource::SysmanResource( 
        resource_handle_t handle,                       ///< [in] handle of resource
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a handle to access SMI features
    /// 
    /// @details
    ///     - Initializes internal structures to support SMI features.
    ///     - If the write flag ::XET_SYSMAN_INIT_FLAGS_WRITE is specified, no
    ///       access right checks are made during initialization. The check is done
    ///       in functions that attempt to control a device.
    ///     - If the write flag ::XET_SYSMAN_INIT_FLAGS_WRITE is not specified, any
    ///       function attempting to control a device will return
    ///       ::XE_RESULT_ACCESS_DENIED.
    ///     - Multiple SMI handles can be created for the same device group and
    ///       concurrent access through each handle to access underlying hardware
    ///       resources is supported.
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
        DeviceGroup* pDeviceGroup,                      ///< [in] Handle of the device group
        version_t version,                              ///< [in] SMI version that application was built with
        uint32_t flags                                  ///< [in] Bitfield of ::xet_sysman_init_flags_t
        )
    {
        xet_sysman_handle_t hSysman;

        auto result = static_cast<result_t>( ::xetSysmanCreate(
            reinterpret_cast<xet_device_group_handle_t>( pDeviceGroup->getHandle() ),
            static_cast<xet_sysman_version_t>( version ),
            flags,
            &hSysman ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::Create" );

        Sysman* pSysman = nullptr;

        try
        {
            pSysman = new Sysman( reinterpret_cast<sysman_handle_t>( hSysman ), pDeviceGroup );
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
    /// @brief Destroys a Sysman handle
    /// 
    /// @details
    ///     - Only once all SMI handles to a device group have been destroyed will
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
    /// @brief Convert SMI resource UUID to a string
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::ConvertUuidToString(
        const resource_uuid_t* pUuid,                   ///< [in] Pointer to a Sysman UUID
        uint32_t* pSize,                                ///< [in,out] Pointer to the size of the string buffer pointed to by pStr.
                                                        ///< If size is zero, the storage size including end-of-string terminator
                                                        ///< will be returned.
                                                        ///< If size is non-zero and less than the required length, the storage
                                                        ///< size including end-of-string terminator will be returned and an error
                                                        ///< status given.
                                                        ///< If size is non-zero and larger than the required length, the number of
                                                        ///< characters stored in the buffer including the end-of-string terminator
                                                        ///< will be returned.
        char* pStr                                      ///< [in][optional] Pointer to storage for the string representation of the
                                                        ///< UUID
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanConvertUuidToString(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<const xet_resource_uuid_t*>( pUuid ),
            pSize,
            pStr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::ConvertUuidToString" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves resources of a given type having a specified parent resource
    /// 
    /// @details
    ///     - If a parent resource is not specified, then all resources of the given
    ///       type are returned. Otherwise only resources directly contained
    ///       in/under the specified parent are returned.
    ///     - There is a one-to-many mapping between the underlying hardware for a
    ///       resource and the corresponding handles returned to the application.
    ///       Thus, the numerical value of the handles should not be compared with
    ///       those returned by previous function calls - instead, use the function
    ///       ::xetSysmanResourceIsSame() to check if two handles reference the same
    ///       hardware object.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResource*: Array of resources resources
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetResources(
        SysmanResource* pParentResource,                ///< [in] Handle of the parent resource object (can be
                                                        ///< ::XET_INVALID_SYSMAN_RESOURCE_HANDLE)
        resource_type_t type,                           ///< [in] The type of resources to enumerate
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array phResources.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of resources that would be returned.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< resources of the given type starting from index 0.
                                                        ///< If count is larger than the number of resource that will be returned,
                                                        ///< then the driver will update the value with actual number returned.
        SysmanResource** ppResources                    ///< [out][optional][range(0, *pCount)] Array of resources resources
        )
    {
        thread_local std::vector<xet_resource_handle_t> hResources;
        hResources.resize( ( ppResources ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanGetResources(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_resource_handle_t>( pParentResource->getHandle() ),
            static_cast<xet_resource_type_t>( type ),
            pCount,
            hResources.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetResources" );

        for( uint32_t i = 0; ( ppResources ) && ( i < *pCount ); ++i )
            ppResources[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppResources ) && ( i < *pCount ); ++i )
                ppResources[ i ] = new SysmanResource( reinterpret_cast<resource_handle_t>( hResources[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppResources ) && ( i < *pCount ); ++i )
            {
                delete ppResources[ i ];
                ppResources[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::GetResources" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves a resource handle for a device
    /// 
    /// @details
    ///     - The specified device must be in the same device group that was used to
    ///       create the SMI handle.
    ///     - If the device handle refers to a device, then a resource handle of
    ///       type ::XET_RESOURCE_TYPE_DEVICE_CONTAINER will be returned.
    ///     - If the device handle refers to a sub-device, then a resource handle of
    ///       type ::XET_RESOURCE_TYPE_SUBDEVICE_CONTAINER will be returned.
    ///     - There is a one-to-many mapping between the underlying hardware for a
    ///       resource and the corresponding handles returned to the application.
    ///       Thus, the numerical value of the handles should not be compared with
    ///       those returned by previous function calls - instead, use the function
    ///       ::xetSysmanResourceIsSame() to check if two handles reference the same
    ///       hardware object.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResource*: Resource handle for the specified device
    /// 
    /// @throws result_t
    SysmanResource* __xecall
    Sysman::GetDeviceResource(
        xe::Device* pDevice                             ///< [in] Handle to the device.
        )
    {
        xet_resource_handle_t hResource;

        auto result = static_cast<result_t>( ::xetSysmanGetDeviceResource(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            &hResource ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetDeviceResource" );

        SysmanResource* pResource = nullptr;

        try
        {
            pResource = new SysmanResource( reinterpret_cast<resource_handle_t>( hResource ), this );
        }
        catch( std::bad_alloc& )
        {
            delete pResource;
            pResource = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::GetDeviceResource" );
        }

        return pResource;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves a resource handle based on resource UUID
    /// 
    /// @details
    ///     - There is a one-to-many mapping between the underlying hardware for a
    ///       resource and the corresponding handles returned to the application.
    ///       Thus, the numerical value of the handles should not be compared with
    ///       those returned by previous function calls - instead, use the function
    ///       ::xetSysmanResourceIsSame() to check if two handles reference the same
    ///       hardware object.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResource*: Resource handle
    /// 
    /// @throws result_t
    SysmanResource* __xecall
    Sysman::GetResourceByUuid(
        const resource_uuid_t* uuid                     ///< [in] UUID for the resource
        )
    {
        xet_resource_handle_t hResource;

        auto result = static_cast<result_t>( ::xetSysmanGetResourceByUuid(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<const xet_resource_uuid_t*>( uuid ),
            &hResource ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetResourceByUuid" );

        SysmanResource* pResource = nullptr;

        try
        {
            pResource = new SysmanResource( reinterpret_cast<resource_handle_t>( hResource ), this );
        }
        catch( std::bad_alloc& )
        {
            delete pResource;
            pResource = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::GetResourceByUuid" );
        }

        return pResource;
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
        SysmanResource* pResource,                      ///< [in] Handle of the resource. If specified, only errors within that
                                                        ///< resource of child resources are returned. Otherwise all errors are
                                                        ///< returned.
        uint32_t type,                                  ///< [in] Bitfield of error types to filter - one or more of
                                                        ///< ::xet_ras_error_type_t. Set to ::XET_RAS_ERROR_TYPE_ALL to have all
                                                        ///< error types returned.
        uint32_t location,                              ///< [in] Bitfield of error locations to filter - one or more of
                                                        ///< ::xet_ras_error_loc_t. Set to ::XET_RAS_ERROR_LOC_ALL to have all
                                                        ///< error locations returned.
        uint32_t threshold,                             ///< [in] Only return error elements that have occurred at least this
                                                        ///< number of times.
                                                        ///< If set to 0, will get a list of all possible RAS elements, even those
                                                        ///< that have not had errors.
                                                        ///< For error elements of type ::XET_RAS_DATA_TYPE_OCCURRED, there is no
                                                        ///< underlying counter, so they will always be returned independent of the
                                                        ///< threshold setting.
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
        res_error_t* pErrors                            ///< [in] Array of error data
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetRasErrors(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_resource_handle_t>( pResource->getHandle() ),
            type,
            location,
            threshold,
            static_cast<xe_bool_t>( clear ),
            pCount,
            reinterpret_cast<xet_res_error_t*>( pErrors ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetRasErrors" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Compare if two resource handles reference the same underlying hardware
    ///        object
    /// 
    /// @details
    ///     - There is a one-to-many mapping between the underlying hardware for a
    ///       resource and the corresponding handles returned to the application.
    ///       Thus, the numerical value of the handles should not be compared with
    ///       those returned by previous function calls - instead, use this function
    ///       to check if two handles reference the same hardware object.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::IsSame(
        SysmanResource* pRhs,                           ///< [in] Handle of the other resource
        xe::bool_t* pIsSame                             ///< [in] Sets to True if the two resources reference the same underlying
                                                        ///< hardware object
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceIsSame(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            reinterpret_cast<xet_resource_handle_t>( pRhs->getHandle() ),
            reinterpret_cast<xe_bool_t*>( pIsSame ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::IsSame" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get generic information about a resource
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - Sysman::resource_info_t: Generic information about the resource
    /// 
    /// @throws result_t
    Sysman::Sysman::resource_info_t __xecall
    SysmanResource::GetInfo(
        void
        )
    {
        xet_resource_info_t info;

        auto result = static_cast<result_t>( ::xetSysmanResourceGetInfo(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            &info ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetInfo" );

        return *reinterpret_cast<Sysman::resource_info_t*>( &info );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get a handle to the parent resource
    /// 
    /// @details
    ///     - For resource containers, this will return the handle to parent
    ///       container. For non-container resources, this will return the handle to
    ///       the container resource in which the resource is located.
    ///     - If there is no parent (e.g. resources of type
    ///       ::XET_RESOURCE_TYPE_UNIT_CONTAINER), the returned handle will be
    ///       ::XET_INVALID_SYSMAN_RESOURCE_HANDLE.
    ///     - There is a one-to-many mapping between the underlying hardware for a
    ///       resource and the corresponding handles returned to the application.
    ///       Thus, the numerical value of the handles should not be compared with
    ///       those returned by previous function calls - instead, use the function
    ///       ::xetSysmanResourceIsSame() to check if two handles reference the same
    ///       hardware object.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResource*: Handle of the parent resource
    /// 
    /// @throws result_t
    SysmanResource* __xecall
    SysmanResource::GetParent(
        void
        )
    {
        xet_resource_handle_t hResource;

        auto result = static_cast<result_t>( ::xetSysmanResourceGetParent(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            &hResource ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetParent" );

        SysmanResource* pResource = nullptr;

        try
        {
            pResource = new SysmanResource( reinterpret_cast<resource_handle_t>( hResource ), m_pSysman );
        }
        catch( std::bad_alloc& )
        {
            delete pResource;
            pResource = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetParent" );
        }

        return pResource;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get children resources
    /// 
    /// @details
    ///     - If the parent resource is not a container, no children resources will
    ///       be returned.
    ///     - Only resource containers will be returned by this function. The
    ///       function ::xetSysmanGetResources should be used to get non-container
    ///       resources located in a parent resource.
    ///     - There is a one-to-many mapping between the underlying hardware for a
    ///       resource and the corresponding handles returned to the application.
    ///       Thus, the numerical value of the handles should not be compared with
    ///       those returned by previous function calls - instead, use the function
    ///       ::xetSysmanResourceIsSame() to check if two handles reference the same
    ///       hardware object.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResource*: Array of resource handles.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetChildren(
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array phResources.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of child resources.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< child resources starting from index 0.
                                                        ///< If count is larger than the number of child resources that will be
                                                        ///< returned, then the driver will update the value with the resources
                                                        ///< actually returned.
        SysmanResource** ppResources                    ///< [out][optional][range(0, *pCount)] Array of resource handles.
        )
    {
        thread_local std::vector<xet_resource_handle_t> hResources;
        hResources.resize( ( ppResources ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanResourceGetChildren(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            pCount,
            hResources.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetChildren" );

        for( uint32_t i = 0; ( ppResources ) && ( i < *pCount ); ++i )
            ppResources[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppResources ) && ( i < *pCount ); ++i )
                ppResources[ i ] = new SysmanResource( reinterpret_cast<resource_handle_t>( hResources[ i ] ), m_pSysman );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppResources ) && ( i < *pCount ); ++i )
            {
                delete ppResources[ i ];
                ppResources[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetChildren" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get peer resources
    /// 
    /// @details
    ///     - If the parent resource is not a container, no peer resources will be
    ///       returned.
    ///     - Only resource containers will be returned by this function. The
    ///       function ::xetSysmanGetResources should be used to get non-container
    ///       resources located in a parent resource.
    ///     - There is a one-to-many mapping between the underlying hardware for a
    ///       resource and the corresponding handles returned to the application.
    ///       Thus, the numerical value of the handles should not be compared with
    ///       those returned by previous function calls - instead, use the function
    ///       ::xetSysmanResourceIsSame() to check if two handles reference the same
    ///       hardware object.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResource*: Array of resource handles.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetPeers(
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array phResources.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of peer resources.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< peer resources starting from index 0.
                                                        ///< If count is larger than the number of peer resources that will be
                                                        ///< returned, then the driver will update the value with the resources
                                                        ///< actually returned.
        SysmanResource** ppResources                    ///< [out][optional][range(0, *pCount)] Array of resource handles.
        )
    {
        thread_local std::vector<xet_resource_handle_t> hResources;
        hResources.resize( ( ppResources ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanResourceGetPeers(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            pCount,
            hResources.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetPeers" );

        for( uint32_t i = 0; ( ppResources ) && ( i < *pCount ); ++i )
            ppResources[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppResources ) && ( i < *pCount ); ++i )
                ppResources[ i ] = new SysmanResource( reinterpret_cast<resource_handle_t>( hResources[ i ] ), m_pSysman );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppResources ) && ( i < *pCount ); ++i )
            {
                delete ppResources[ i ];
                ppResources[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetPeers" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get board property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetBoardProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        board_property_request_t* pRequest              ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetBoardProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_board_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetBoardProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get device container property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetDeviceProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        device_property_request_t* pRequest             ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetDeviceProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_device_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetDeviceProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set device container property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetDeviceProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        device_property_request_t* pRequest             ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetDeviceProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_device_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetDeviceProperties" );
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
    SysmanResource::GetPsuProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        psu_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetPsuProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_psu_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetPsuProperties" );
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
    SysmanResource::SetPsuProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        psu_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetPsuProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_psu_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetPsuProperties" );
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
    SysmanResource::GetTempProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        temp_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetTempProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_temp_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetTempProperties" );
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
    SysmanResource::GetFanProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        fan_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetFanProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_fan_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetFanProperties" );
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
    SysmanResource::SetFanProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        fan_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetFanProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_fan_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetFanProperties" );
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
    SysmanResource::GetLedProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        led_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetLedProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_led_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetLedProperties" );
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
    SysmanResource::SetLedProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        led_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetLedProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_led_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetLedProperties" );
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
    SysmanResource::GetFirmwareProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        firmware_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetFirmwareProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_firmware_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetFirmwareProperties" );
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
    SysmanResource::SetFirmwareProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        firmware_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetFirmwareProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_firmware_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetFirmwareProperties" );
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
    SysmanResource::GetPwrProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        pwr_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetPwrProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_pwr_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetPwrProperties" );
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
    SysmanResource::SetPwrProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        pwr_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetPwrProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_pwr_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetPwrProperties" );
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
    SysmanResource::GetFreqProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        freq_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetFreqProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_freq_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetFreqProperties" );
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
    SysmanResource::SetFreqProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        freq_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetFreqProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_freq_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetFreqProperties" );
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
    SysmanResource::GetPwrwellProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        pwrwell_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetPwrwellProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_pwrwell_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetPwrwellProperties" );
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
    SysmanResource::SetPwrwellProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        pwrwell_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetPwrwellProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_pwrwell_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetPwrwellProperties" );
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
    SysmanResource::GetAccelProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        accel_property_request_t* pRequest              ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetAccelProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_accel_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetAccelProperties" );
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
    SysmanResource::GetMemProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        mem_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetMemProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_mem_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetMemProperties" );
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
    SysmanResource::SetMemProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        mem_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetMemProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_mem_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetMemProperties" );
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
    SysmanResource::GetLinkProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        link_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetLinkProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_link_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetLinkProperties" );
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
    SysmanResource::SetLinkProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        link_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetLinkProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_link_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetLinkProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Register to receive events
    /// 
    /// @details
    ///     - This will only register the specified list of events. If other events
    ///       have been registered, notifications for them will continue.
    ///     - Applies only to devices in the specified SMI handle.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::RegisterEvents(
        SysmanResource* pResource,                      ///< [in] Handle of the parent resource. Events from any contained devices
                                                        ///< will be registered.
                                                        ///< If the handle is ::XET_INVALID_SYSMAN_RESOURCE_HANDLE, events from all
                                                        ///< devices will be registered.
        uint32_t events                                 ///< [in] Bitfield of events to register.
                                                        ///< Construct by ORing (1<<::xet_sysman_event_type_t).
                                                        ///< Set to (~0) to register to receive all events.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanRegisterEvents(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_resource_handle_t>( pResource->getHandle() ),
            events ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::RegisterEvents" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Unregister events
    /// 
    /// @details
    ///     - This will only unregister the specified list of events. If other
    ///       events have been registered, notifications for them will continue.
    ///     - Applies only to devices in the specified SMI handle.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::UnregisterEvents(
        SysmanResource* pResource,                      ///< [in] Handle of the parent resource. Events from any contained devices
                                                        ///< will be unregistered.
                                                        ///< If the handle is ::XET_INVALID_SYSMAN_RESOURCE_HANDLE, events from all
                                                        ///< devices will be unregistered.
        uint32_t events                                 ///< [in] Bitfield of events to unregister.
                                                        ///< Construct by ORing (1<<::xet_sysman_event_type_t).
                                                        ///< Set to (~0) to unregister all events.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanUnregisterEvents(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_resource_handle_t>( pResource->getHandle() ),
            events ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::UnregisterEvents" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Listen for events
    /// 
    /// @details
    ///     - This will only unregister the specified list of events. If other
    ///       events have been registered, notifications for them will continue.
    ///     - Applies only to devices in the specified SMI handle.
    ///     - At most, one event data per device will be returned.
    ///     - If event data is returned, the corresponding event status is cleared.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::ListenEvents(
        xe::bool_t block,                               ///< [in] If set to true, the call will block the calling thread
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array pointed to by pEventData.
                                                        ///< If size is zero, then the driver will update the value with the number
                                                        ///< of elements needed to retrieve the list of events.
                                                        ///< If size is less than that required to store the list of events, the
                                                        ///< driver will update the value with the required number of elements and
                                                        ///< return an error.
                                                        ///< If size is larger than that required to store the list of events, the
                                                        ///< driver will update the value with the number of elements actually returned.
        event_data_t* pEventData                        ///< [in] Pointer to an array of event data
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanListenEvents(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            static_cast<xe_bool_t>( block ),
            pCount,
            reinterpret_cast<xet_sysman_event_data_t*>( pEventData ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::ListenEvents" );
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
        case Sysman::resource_type_t::UNIT_CONTAINER:
            str = "Sysman::resource_type_t::UNIT_CONTAINER";
            break;

        case Sysman::resource_type_t::BOARD_CONTAINER:
            str = "Sysman::resource_type_t::BOARD_CONTAINER";
            break;

        case Sysman::resource_type_t::DEVICE_CONTAINER:
            str = "Sysman::resource_type_t::DEVICE_CONTAINER";
            break;

        case Sysman::resource_type_t::SUBDEVICE_CONTAINER:
            str = "Sysman::resource_type_t::SUBDEVICE_CONTAINER";
            break;

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

        case Sysman::accel_asset_t::BLILTTER:
            str = "Sysman::accel_asset_t::BLILTTER";
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
    /// @brief Converts Sysman::event_type_t to std::string
    std::string to_string( const Sysman::event_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::event_type_t::FREQ_THROTTLED:
            str = "Sysman::event_type_t::FREQ_THROTTLED";
            break;

        case Sysman::event_type_t::FREQ_POLICY_CHANGED:
            str = "Sysman::event_type_t::FREQ_POLICY_CHANGED";
            break;

        case Sysman::event_type_t::GPU_ERRORS:
            str = "Sysman::event_type_t::GPU_ERRORS";
            break;

        case Sysman::event_type_t::RESET:
            str = "Sysman::event_type_t::RESET";
            break;

        case Sysman::event_type_t::HANG:
            str = "Sysman::event_type_t::HANG";
            break;

        case Sysman::event_type_t::MEM_ERRORS:
            str = "Sysman::event_type_t::MEM_ERRORS";
            break;

        case Sysman::event_type_t::LINK_ERRORS:
            str = "Sysman::event_type_t::LINK_ERRORS";
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
    /// @brief Converts Sysman::resource_uuid_t to std::string
    std::string to_string( const Sysman::resource_uuid_t val )
    {
        std::string str;
        
        str += "Sysman::resource_uuid_t::id : ";
        {
            std::string tmp;
            for( auto& entry : val.id )
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
    /// @brief Converts Sysman::res_error_t to std::string
    std::string to_string( const Sysman::res_error_t val )
    {
        std::string str;
        
        str += "Sysman::res_error_t::type : ";
        str += std::to_string(val.type);
        str += "\n";
        
        str += "Sysman::res_error_t::loc : ";
        str += std::to_string(val.loc);
        str += "\n";
        
        str += "Sysman::res_error_t::dataType : ";
        str += to_string(val.dataType);
        str += "\n";
        
        str += "Sysman::res_error_t::data : ";
        str += std::to_string(val.data);
        str += "\n";
        
        str += "Sysman::res_error_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resource_info_t to std::string
    std::string to_string( const Sysman::resource_info_t val )
    {
        std::string str;
        
        str += "Sysman::resource_info_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";
        
        str += "Sysman::resource_info_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Sysman::resource_info_t::haveParent : ";
        str += std::to_string(val.haveParent);
        str += "\n";
        
        str += "Sysman::resource_info_t::numChildren : ";
        str += std::to_string(val.numChildren);
        str += "\n";
        
        str += "Sysman::resource_info_t::numPeers : ";
        str += std::to_string(val.numPeers);
        str += "\n";
        
        str += "Sysman::resource_info_t::numRas : ";
        str += std::to_string(val.numRas);
        str += "\n";
        
        str += "Sysman::resource_info_t::rasTypes : ";
        str += std::to_string(val.rasTypes);
        str += "\n";
        
        str += "Sysman::resource_info_t::rasLocations : ";
        str += std::to_string(val.rasLocations);
        str += "\n";
        
        str += "Sysman::resource_info_t::numResourcesByType : ";
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
    /// @brief Converts Sysman::event_data_t to std::string
    std::string to_string( const Sysman::event_data_t val )
    {
        std::string str;
        
        str += "Sysman::event_data_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";
        
        str += "Sysman::event_data_t::events : ";
        str += std::to_string(val.events);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::board_properties_t to std::string
    std::string to_string( const SysmanResource::board_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::board_properties_t::BOARD_PROP_SERIAL_NUMBER:
            str = "SysmanResource::board_properties_t::BOARD_PROP_SERIAL_NUMBER";
            break;

        case SysmanResource::board_properties_t::BOARD_PROP_BOARD_NUMBER:
            str = "SysmanResource::board_properties_t::BOARD_PROP_BOARD_NUMBER";
            break;

        default:
            str = "SysmanResource::board_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pci_bar_type_t to std::string
    std::string to_string( const SysmanResource::pci_bar_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::pci_bar_type_t::CONFIG:
            str = "SysmanResource::pci_bar_type_t::CONFIG";
            break;

        case SysmanResource::pci_bar_type_t::MMIO:
            str = "SysmanResource::pci_bar_type_t::MMIO";
            break;

        case SysmanResource::pci_bar_type_t::VRAM:
            str = "SysmanResource::pci_bar_type_t::VRAM";
            break;

        case SysmanResource::pci_bar_type_t::ROM:
            str = "SysmanResource::pci_bar_type_t::ROM";
            break;

        case SysmanResource::pci_bar_type_t::VGA_IO:
            str = "SysmanResource::pci_bar_type_t::VGA_IO";
            break;

        case SysmanResource::pci_bar_type_t::VGA_MEM:
            str = "SysmanResource::pci_bar_type_t::VGA_MEM";
            break;

        case SysmanResource::pci_bar_type_t::INDIRECT_IO:
            str = "SysmanResource::pci_bar_type_t::INDIRECT_IO";
            break;

        case SysmanResource::pci_bar_type_t::INDIRECT_MEM:
            str = "SysmanResource::pci_bar_type_t::INDIRECT_MEM";
            break;

        case SysmanResource::pci_bar_type_t::OTHER:
            str = "SysmanResource::pci_bar_type_t::OTHER";
            break;

        default:
            str = "SysmanResource::pci_bar_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::device_properties_t to std::string
    std::string to_string( const SysmanResource::device_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::device_properties_t::DEVICE_PROP_BRAND:
            str = "SysmanResource::device_properties_t::DEVICE_PROP_BRAND";
            break;

        case SysmanResource::device_properties_t::DEVICE_PROP_MODEL:
            str = "SysmanResource::device_properties_t::DEVICE_PROP_MODEL";
            break;

        case SysmanResource::device_properties_t::DEVICE_PROP_DEVICEID:
            str = "SysmanResource::device_properties_t::DEVICE_PROP_DEVICEID";
            break;

        case SysmanResource::device_properties_t::DEVICE_PROP_VENDOR_NAME:
            str = "SysmanResource::device_properties_t::DEVICE_PROP_VENDOR_NAME";
            break;

        case SysmanResource::device_properties_t::DEVICE_PROP_ACCEL_ASSETS:
            str = "SysmanResource::device_properties_t::DEVICE_PROP_ACCEL_ASSETS";
            break;

        case SysmanResource::device_properties_t::DEVICE_PROP_DRIVER_VERSION:
            str = "SysmanResource::device_properties_t::DEVICE_PROP_DRIVER_VERSION";
            break;

        case SysmanResource::device_properties_t::DEVICE_PROP_BARS:
            str = "SysmanResource::device_properties_t::DEVICE_PROP_BARS";
            break;

        case SysmanResource::device_properties_t::DEVICE_PROP_COLD_SHUTDOWN:
            str = "SysmanResource::device_properties_t::DEVICE_PROP_COLD_SHUTDOWN";
            break;

        case SysmanResource::device_properties_t::DEVICE_PROP_COLD_RESET:
            str = "SysmanResource::device_properties_t::DEVICE_PROP_COLD_RESET";
            break;

        default:
            str = "SysmanResource::device_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_voltage_status_t to std::string
    std::string to_string( const SysmanResource::psu_voltage_status_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::psu_voltage_status_t::NORMAL:
            str = "SysmanResource::psu_voltage_status_t::NORMAL";
            break;

        case SysmanResource::psu_voltage_status_t::OVER:
            str = "SysmanResource::psu_voltage_status_t::OVER";
            break;

        case SysmanResource::psu_voltage_status_t::UNDER:
            str = "SysmanResource::psu_voltage_status_t::UNDER";
            break;

        default:
            str = "SysmanResource::psu_voltage_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_properties_t to std::string
    std::string to_string( const SysmanResource::psu_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::psu_properties_t::PSU_PROP_AMP_LIMIT:
            str = "SysmanResource::psu_properties_t::PSU_PROP_AMP_LIMIT";
            break;

        case SysmanResource::psu_properties_t::PSU_PROP_VOLTAGE_STATUS:
            str = "SysmanResource::psu_properties_t::PSU_PROP_VOLTAGE_STATUS";
            break;

        case SysmanResource::psu_properties_t::PSU_PROP_FAN_FAILURE:
            str = "SysmanResource::psu_properties_t::PSU_PROP_FAN_FAILURE";
            break;

        case SysmanResource::psu_properties_t::PSU_PROP_TEMPERATURE:
            str = "SysmanResource::psu_properties_t::PSU_PROP_TEMPERATURE";
            break;

        case SysmanResource::psu_properties_t::PSU_PROP_AMPS:
            str = "SysmanResource::psu_properties_t::PSU_PROP_AMPS";
            break;

        default:
            str = "SysmanResource::psu_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::temp_properties_t to std::string
    std::string to_string( const SysmanResource::temp_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::temp_properties_t::TEMP_PROP_TEMPERATURE:
            str = "SysmanResource::temp_properties_t::TEMP_PROP_TEMPERATURE";
            break;

        default:
            str = "SysmanResource::temp_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_speed_mode_t to std::string
    std::string to_string( const SysmanResource::fan_speed_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::fan_speed_mode_t::FIXED:
            str = "SysmanResource::fan_speed_mode_t::FIXED";
            break;

        case SysmanResource::fan_speed_mode_t::TABLE:
            str = "SysmanResource::fan_speed_mode_t::TABLE";
            break;

        default:
            str = "SysmanResource::fan_speed_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_speed_units_t to std::string
    std::string to_string( const SysmanResource::fan_speed_units_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::fan_speed_units_t::RPM:
            str = "SysmanResource::fan_speed_units_t::RPM";
            break;

        case SysmanResource::fan_speed_units_t::PERCENT:
            str = "SysmanResource::fan_speed_units_t::PERCENT";
            break;

        default:
            str = "SysmanResource::fan_speed_units_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_properties_t to std::string
    std::string to_string( const SysmanResource::fan_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::fan_properties_t::FAN_PROP_MAX_RPM:
            str = "SysmanResource::fan_properties_t::FAN_PROP_MAX_RPM";
            break;

        case SysmanResource::fan_properties_t::FAN_PROP_MAX_TABLE_SIZE:
            str = "SysmanResource::fan_properties_t::FAN_PROP_MAX_TABLE_SIZE";
            break;

        case SysmanResource::fan_properties_t::FAN_PROP_SPEED_RPM:
            str = "SysmanResource::fan_properties_t::FAN_PROP_SPEED_RPM";
            break;

        case SysmanResource::fan_properties_t::FAN_PROP_SPEED_PERCENT:
            str = "SysmanResource::fan_properties_t::FAN_PROP_SPEED_PERCENT";
            break;

        case SysmanResource::fan_properties_t::FAN_PROP_MODE:
            str = "SysmanResource::fan_properties_t::FAN_PROP_MODE";
            break;

        case SysmanResource::fan_properties_t::FAN_PROP_FIXED_SPEED:
            str = "SysmanResource::fan_properties_t::FAN_PROP_FIXED_SPEED";
            break;

        case SysmanResource::fan_properties_t::FAN_PROP_SPEED_TABLE:
            str = "SysmanResource::fan_properties_t::FAN_PROP_SPEED_TABLE";
            break;

        default:
            str = "SysmanResource::fan_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::led_properties_t to std::string
    std::string to_string( const SysmanResource::led_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::led_properties_t::LED_PROP_RGB_CAP:
            str = "SysmanResource::led_properties_t::LED_PROP_RGB_CAP";
            break;

        case SysmanResource::led_properties_t::LED_PROP_STATE:
            str = "SysmanResource::led_properties_t::LED_PROP_STATE";
            break;

        default:
            str = "SysmanResource::led_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::firmware_properties_t to std::string
    std::string to_string( const SysmanResource::firmware_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::firmware_properties_t::FIRMWARE_PROP_NAME:
            str = "SysmanResource::firmware_properties_t::FIRMWARE_PROP_NAME";
            break;

        case SysmanResource::firmware_properties_t::FIRMWARE_PROP_VERSION:
            str = "SysmanResource::firmware_properties_t::FIRMWARE_PROP_VERSION";
            break;

        case SysmanResource::firmware_properties_t::FIRMWARE_PROP_CHECK:
            str = "SysmanResource::firmware_properties_t::FIRMWARE_PROP_CHECK";
            break;

        case SysmanResource::firmware_properties_t::FIRMWARE_PROP_FLASH:
            str = "SysmanResource::firmware_properties_t::FIRMWARE_PROP_FLASH";
            break;

        default:
            str = "SysmanResource::firmware_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_properties_t to std::string
    std::string to_string( const SysmanResource::pwr_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::pwr_properties_t::PWR_PROP_ACCEL_ASSETS:
            str = "SysmanResource::pwr_properties_t::PWR_PROP_ACCEL_ASSETS";
            break;

        case SysmanResource::pwr_properties_t::PWR_PROP_MAX_LIMIT:
            str = "SysmanResource::pwr_properties_t::PWR_PROP_MAX_LIMIT";
            break;

        case SysmanResource::pwr_properties_t::PWR_PROP_ENERGY_COUNTER:
            str = "SysmanResource::pwr_properties_t::PWR_PROP_ENERGY_COUNTER";
            break;

        case SysmanResource::pwr_properties_t::PWR_PROP_SUSTAINED_LIMIT:
            str = "SysmanResource::pwr_properties_t::PWR_PROP_SUSTAINED_LIMIT";
            break;

        case SysmanResource::pwr_properties_t::PWR_PROP_BURST_LIMIT:
            str = "SysmanResource::pwr_properties_t::PWR_PROP_BURST_LIMIT";
            break;

        case SysmanResource::pwr_properties_t::PWR_PROP_PEAK_LIMIT:
            str = "SysmanResource::pwr_properties_t::PWR_PROP_PEAK_LIMIT";
            break;

        default:
            str = "SysmanResource::pwr_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_domain_type_t to std::string
    std::string to_string( const SysmanResource::freq_domain_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::freq_domain_type_t::INDEPENDENT:
            str = "SysmanResource::freq_domain_type_t::INDEPENDENT";
            break;

        case SysmanResource::freq_domain_type_t::DEPENDENT:
            str = "SysmanResource::freq_domain_type_t::DEPENDENT";
            break;

        default:
            str = "SysmanResource::freq_domain_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::dvfs_mode_t to std::string
    std::string to_string( const SysmanResource::dvfs_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::dvfs_mode_t::MIN:
            str = "SysmanResource::dvfs_mode_t::MIN";
            break;

        case SysmanResource::dvfs_mode_t::EFFICIENT:
            str = "SysmanResource::dvfs_mode_t::EFFICIENT";
            break;

        case SysmanResource::dvfs_mode_t::STABLE:
            str = "SysmanResource::dvfs_mode_t::STABLE";
            break;

        case SysmanResource::dvfs_mode_t::DEFAULT:
            str = "SysmanResource::dvfs_mode_t::DEFAULT";
            break;

        case SysmanResource::dvfs_mode_t::AGGRESSIVE:
            str = "SysmanResource::dvfs_mode_t::AGGRESSIVE";
            break;

        case SysmanResource::dvfs_mode_t::MAX:
            str = "SysmanResource::dvfs_mode_t::MAX";
            break;

        default:
            str = "SysmanResource::dvfs_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_throttle_reasons_t to std::string
    std::string to_string( const SysmanResource::freq_throttle_reasons_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(SysmanResource::freq_throttle_reasons_t::AVE_PWR_CAP) & bits )
            str += "AVE_PWR_CAP | ";
        
        if( static_cast<uint32_t>(SysmanResource::freq_throttle_reasons_t::BURST_PWR_CAP) & bits )
            str += "BURST_PWR_CAP | ";
        
        if( static_cast<uint32_t>(SysmanResource::freq_throttle_reasons_t::CURRENT_LIMIT) & bits )
            str += "CURRENT_LIMIT | ";
        
        if( static_cast<uint32_t>(SysmanResource::freq_throttle_reasons_t::THERMAL_LIMIT) & bits )
            str += "THERMAL_LIMIT | ";
        
        if( static_cast<uint32_t>(SysmanResource::freq_throttle_reasons_t::PSU_ALERT) & bits )
            str += "PSU_ALERT | ";
        
        if( static_cast<uint32_t>(SysmanResource::freq_throttle_reasons_t::SW_RANGE) & bits )
            str += "SW_RANGE | ";
        
        if( static_cast<uint32_t>(SysmanResource::freq_throttle_reasons_t::HW_RANGE) & bits )
            str += "HW_RANGE | ";

        return ( str.size() > 3 ) 
            ? "SysmanResource::freq_throttle_reasons_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "SysmanResource::freq_throttle_reasons_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_properties_t to std::string
    std::string to_string( const SysmanResource::freq_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::freq_properties_t::FREQ_PROP_ACCEL_ASSETS:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_ACCEL_ASSETS";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_DOMAIN_TYPE:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_DOMAIN_TYPE";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_AVAIL_CLOCKS:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_AVAIL_CLOCKS";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_AVAIL_DIVIDERS:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_AVAIL_DIVIDERS";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_SRC_FREQ:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_SRC_FREQ";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_DVFS_MODE:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_DVFS_MODE";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_FREQ_RANGE:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_FREQ_RANGE";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_FREQ_TDP:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_FREQ_TDP";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_FREQ_EFFICIENT:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_FREQ_EFFICIENT";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_FREQ_REQUEST:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_FREQ_REQUEST";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_FREQ_RESOLVED:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_FREQ_RESOLVED";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_FREQ_DIVIDER:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_FREQ_DIVIDER";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_THROTTLE_REASONS:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_THROTTLE_REASONS";
            break;

        case SysmanResource::freq_properties_t::FREQ_PROP_THROTTLE_TIME:
            str = "SysmanResource::freq_properties_t::FREQ_PROP_THROTTLE_TIME";
            break;

        default:
            str = "SysmanResource::freq_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_promo_mode_t to std::string
    std::string to_string( const SysmanResource::pwrwell_promo_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::pwrwell_promo_mode_t::IMMEDIATE:
            str = "SysmanResource::pwrwell_promo_mode_t::IMMEDIATE";
            break;

        case SysmanResource::pwrwell_promo_mode_t::EFFICIENT:
            str = "SysmanResource::pwrwell_promo_mode_t::EFFICIENT";
            break;

        case SysmanResource::pwrwell_promo_mode_t::DEFAULT:
            str = "SysmanResource::pwrwell_promo_mode_t::DEFAULT";
            break;

        case SysmanResource::pwrwell_promo_mode_t::PERFORMANCE:
            str = "SysmanResource::pwrwell_promo_mode_t::PERFORMANCE";
            break;

        case SysmanResource::pwrwell_promo_mode_t::NEVER:
            str = "SysmanResource::pwrwell_promo_mode_t::NEVER";
            break;

        default:
            str = "SysmanResource::pwrwell_promo_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_properties_t to std::string
    std::string to_string( const SysmanResource::pwrwell_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::pwrwell_properties_t::PWRWELL_PROP_ACCEL_ASSETS:
            str = "SysmanResource::pwrwell_properties_t::PWRWELL_PROP_ACCEL_ASSETS";
            break;

        case SysmanResource::pwrwell_properties_t::PWRWELL_PROP_PROMO_CAP:
            str = "SysmanResource::pwrwell_properties_t::PWRWELL_PROP_PROMO_CAP";
            break;

        case SysmanResource::pwrwell_properties_t::PWRWELL_PROP_PROMO_MODE:
            str = "SysmanResource::pwrwell_properties_t::PWRWELL_PROP_PROMO_MODE";
            break;

        case SysmanResource::pwrwell_properties_t::PWRWELL_PROP_UTILIZATION:
            str = "SysmanResource::pwrwell_properties_t::PWRWELL_PROP_UTILIZATION";
            break;

        case SysmanResource::pwrwell_properties_t::PWRWELL_PROP_TRANSITIONS:
            str = "SysmanResource::pwrwell_properties_t::PWRWELL_PROP_TRANSITIONS";
            break;

        default:
            str = "SysmanResource::pwrwell_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::accel_properties_t to std::string
    std::string to_string( const SysmanResource::accel_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::accel_properties_t::ACCEL_PROP_ACCEL_ASSETS:
            str = "SysmanResource::accel_properties_t::ACCEL_PROP_ACCEL_ASSETS";
            break;

        case SysmanResource::accel_properties_t::ACCEL_PROP_UTILIZATION:
            str = "SysmanResource::accel_properties_t::ACCEL_PROP_UTILIZATION";
            break;

        default:
            str = "SysmanResource::accel_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_type_t to std::string
    std::string to_string( const SysmanResource::mem_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::mem_type_t::HBM:
            str = "SysmanResource::mem_type_t::HBM";
            break;

        case SysmanResource::mem_type_t::DDR:
            str = "SysmanResource::mem_type_t::DDR";
            break;

        case SysmanResource::mem_type_t::SRAM:
            str = "SysmanResource::mem_type_t::SRAM";
            break;

        case SysmanResource::mem_type_t::L1:
            str = "SysmanResource::mem_type_t::L1";
            break;

        case SysmanResource::mem_type_t::L3:
            str = "SysmanResource::mem_type_t::L3";
            break;

        case SysmanResource::mem_type_t::GRF:
            str = "SysmanResource::mem_type_t::GRF";
            break;

        case SysmanResource::mem_type_t::SLM:
            str = "SysmanResource::mem_type_t::SLM";
            break;

        default:
            str = "SysmanResource::mem_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_retire_reason_t to std::string
    std::string to_string( const SysmanResource::mem_retire_reason_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::mem_retire_reason_t::MULTIPLE_SINGLE_BIT_ERRORS:
            str = "SysmanResource::mem_retire_reason_t::MULTIPLE_SINGLE_BIT_ERRORS";
            break;

        case SysmanResource::mem_retire_reason_t::DOUBLE_BIT_ERRORS:
            str = "SysmanResource::mem_retire_reason_t::DOUBLE_BIT_ERRORS";
            break;

        default:
            str = "SysmanResource::mem_retire_reason_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_properties_t to std::string
    std::string to_string( const SysmanResource::mem_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::mem_properties_t::MEM_PROP_TYPE:
            str = "SysmanResource::mem_properties_t::MEM_PROP_TYPE";
            break;

        case SysmanResource::mem_properties_t::MEM_PROP_ECC_CAP:
            str = "SysmanResource::mem_properties_t::MEM_PROP_ECC_CAP";
            break;

        case SysmanResource::mem_properties_t::MEM_PROP_BAD_LIST:
            str = "SysmanResource::mem_properties_t::MEM_PROP_BAD_LIST";
            break;

        case SysmanResource::mem_properties_t::MEM_PROP_UTILIZATION:
            str = "SysmanResource::mem_properties_t::MEM_PROP_UTILIZATION";
            break;

        case SysmanResource::mem_properties_t::MEM_PROP_BANDWIDTH:
            str = "SysmanResource::mem_properties_t::MEM_PROP_BANDWIDTH";
            break;

        case SysmanResource::mem_properties_t::MEM_PROP_ECC_ENABLE:
            str = "SysmanResource::mem_properties_t::MEM_PROP_ECC_ENABLE";
            break;

        case SysmanResource::mem_properties_t::MEM_PROP_ECC_POISON:
            str = "SysmanResource::mem_properties_t::MEM_PROP_ECC_POISON";
            break;

        default:
            str = "SysmanResource::mem_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_type_t to std::string
    std::string to_string( const SysmanResource::link_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::link_type_t::PCI:
            str = "SysmanResource::link_type_t::PCI";
            break;

        case SysmanResource::link_type_t::PEER_TO_PEER:
            str = "SysmanResource::link_type_t::PEER_TO_PEER";
            break;

        default:
            str = "SysmanResource::link_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_properties_t to std::string
    std::string to_string( const SysmanResource::link_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::link_properties_t::LINK_PROP_TYPE:
            str = "SysmanResource::link_properties_t::LINK_PROP_TYPE";
            break;

        case SysmanResource::link_properties_t::LINK_PROP_BUS_ADDRESS:
            str = "SysmanResource::link_properties_t::LINK_PROP_BUS_ADDRESS";
            break;

        case SysmanResource::link_properties_t::LINK_PROP_PWR_CAP:
            str = "SysmanResource::link_properties_t::LINK_PROP_PWR_CAP";
            break;

        case SysmanResource::link_properties_t::LINK_PROP_AVAIL_SPEEDS:
            str = "SysmanResource::link_properties_t::LINK_PROP_AVAIL_SPEEDS";
            break;

        case SysmanResource::link_properties_t::LINK_PROP_MAX_PACKET_SIZE:
            str = "SysmanResource::link_properties_t::LINK_PROP_MAX_PACKET_SIZE";
            break;

        case SysmanResource::link_properties_t::LINK_PROP_BANDWIDTH:
            str = "SysmanResource::link_properties_t::LINK_PROP_BANDWIDTH";
            break;

        case SysmanResource::link_properties_t::LINK_PROP_SPEED:
            str = "SysmanResource::link_properties_t::LINK_PROP_SPEED";
            break;

        case SysmanResource::link_properties_t::LINK_PROP_SPEED_RANGE:
            str = "SysmanResource::link_properties_t::LINK_PROP_SPEED_RANGE";
            break;

        default:
            str = "SysmanResource::link_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::board_prop_serial_number_t to std::string
    std::string to_string( const SysmanResource::board_prop_serial_number_t val )
    {
        std::string str;
        
        str += "SysmanResource::board_prop_serial_number_t::str : ";
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
    /// @brief Converts SysmanResource::board_prop_board_number_t to std::string
    std::string to_string( const SysmanResource::board_prop_board_number_t val )
    {
        std::string str;
        
        str += "SysmanResource::board_prop_board_number_t::str : ";
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
    /// @brief Converts SysmanResource::board_property_request_t to std::string
    std::string to_string( const SysmanResource::board_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::board_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::board_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::board_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pci_bar_info_t to std::string
    std::string to_string( const SysmanResource::pci_bar_info_t val )
    {
        std::string str;
        
        str += "SysmanResource::pci_bar_info_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanResource::pci_bar_info_t::base : ";
        str += std::to_string(val.base);
        str += "\n";
        
        str += "SysmanResource::pci_bar_info_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::device_prop_brand_t to std::string
    std::string to_string( const SysmanResource::device_prop_brand_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_prop_brand_t::str : ";
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
    /// @brief Converts SysmanResource::device_prop_model_t to std::string
    std::string to_string( const SysmanResource::device_prop_model_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_prop_model_t::str : ";
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
    /// @brief Converts SysmanResource::device_prop_deviceid_t to std::string
    std::string to_string( const SysmanResource::device_prop_deviceid_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_prop_deviceid_t::str : ";
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
    /// @brief Converts SysmanResource::device_prop_vendor_name_t to std::string
    std::string to_string( const SysmanResource::device_prop_vendor_name_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_prop_vendor_name_t::str : ";
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
    /// @brief Converts SysmanResource::device_prop_accel_asset_t to std::string
    std::string to_string( const SysmanResource::device_prop_accel_asset_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_prop_accel_asset_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanResource::device_prop_accel_asset_t::numBlocks : ";
        str += std::to_string(val.numBlocks);
        str += "\n";
        
        str += "SysmanResource::device_prop_accel_asset_t::numEngines : ";
        str += std::to_string(val.numEngines);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::device_prop_accel_assets_t to std::string
    std::string to_string( const SysmanResource::device_prop_accel_assets_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_prop_accel_assets_t::assetBitfield : ";
        str += std::to_string(val.assetBitfield);
        str += "\n";
        
        str += "SysmanResource::device_prop_accel_assets_t::assetInfo : ";
        {
            std::string tmp;
            for( auto& entry : val.assetInfo )
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
    /// @brief Converts SysmanResource::device_prop_driver_version_t to std::string
    std::string to_string( const SysmanResource::device_prop_driver_version_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_prop_driver_version_t::str : ";
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
    /// @brief Converts SysmanResource::device_prop_bars_t to std::string
    std::string to_string( const SysmanResource::device_prop_bars_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_prop_bars_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "SysmanResource::device_prop_bars_t::pBars : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pBars);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::device_prop_cold_shutdown_t to std::string
    std::string to_string( const SysmanResource::device_prop_cold_shutdown_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_prop_cold_shutdown_t::doShutdown : ";
        str += std::to_string(val.doShutdown);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::device_prop_cold_reset_t to std::string
    std::string to_string( const SysmanResource::device_prop_cold_reset_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_prop_cold_reset_t::doReset : ";
        str += std::to_string(val.doReset);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::device_property_request_t to std::string
    std::string to_string( const SysmanResource::device_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::device_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::device_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::device_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_prop_amp_limit_t to std::string
    std::string to_string( const SysmanResource::psu_prop_amp_limit_t val )
    {
        std::string str;
        
        str += "SysmanResource::psu_prop_amp_limit_t::limit : ";
        str += std::to_string(val.limit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_prop_voltage_status_t to std::string
    std::string to_string( const SysmanResource::psu_prop_voltage_status_t val )
    {
        std::string str;
        
        str += "SysmanResource::psu_prop_voltage_status_t::status : ";
        str += to_string(val.status);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_prop_fan_failure_t to std::string
    std::string to_string( const SysmanResource::psu_prop_fan_failure_t val )
    {
        std::string str;
        
        str += "SysmanResource::psu_prop_fan_failure_t::status : ";
        str += std::to_string(val.status);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_prop_temperature_t to std::string
    std::string to_string( const SysmanResource::psu_prop_temperature_t val )
    {
        std::string str;
        
        str += "SysmanResource::psu_prop_temperature_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_prop_amps_t to std::string
    std::string to_string( const SysmanResource::psu_prop_amps_t val )
    {
        std::string str;
        
        str += "SysmanResource::psu_prop_amps_t::current : ";
        str += std::to_string(val.current);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_property_request_t to std::string
    std::string to_string( const SysmanResource::psu_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::psu_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::psu_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::psu_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::temp_prop_temperature_t to std::string
    std::string to_string( const SysmanResource::temp_prop_temperature_t val )
    {
        std::string str;
        
        str += "SysmanResource::temp_prop_temperature_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::temp_property_request_t to std::string
    std::string to_string( const SysmanResource::temp_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::temp_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::temp_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::temp_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_temp_speed_t to std::string
    std::string to_string( const SysmanResource::fan_temp_speed_t val )
    {
        std::string str;
        
        str += "SysmanResource::fan_temp_speed_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";
        
        str += "SysmanResource::fan_temp_speed_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "SysmanResource::fan_temp_speed_t::units : ";
        str += to_string(val.units);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_prop_max_rpm_t to std::string
    std::string to_string( const SysmanResource::fan_prop_max_rpm_t val )
    {
        std::string str;
        
        str += "SysmanResource::fan_prop_max_rpm_t::maxSpeed : ";
        str += std::to_string(val.maxSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_prop_max_table_size_t to std::string
    std::string to_string( const SysmanResource::fan_prop_max_table_size_t val )
    {
        std::string str;
        
        str += "SysmanResource::fan_prop_max_table_size_t::maxPoints : ";
        str += std::to_string(val.maxPoints);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_prop_speed_rpm_t to std::string
    std::string to_string( const SysmanResource::fan_prop_speed_rpm_t val )
    {
        std::string str;
        
        str += "SysmanResource::fan_prop_speed_rpm_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_prop_speed_percent_t to std::string
    std::string to_string( const SysmanResource::fan_prop_speed_percent_t val )
    {
        std::string str;
        
        str += "SysmanResource::fan_prop_speed_percent_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_prop_mode_t to std::string
    std::string to_string( const SysmanResource::fan_prop_mode_t val )
    {
        std::string str;
        
        str += "SysmanResource::fan_prop_mode_t::mode : ";
        str += to_string(val.mode);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_prop_fixed_speed_t to std::string
    std::string to_string( const SysmanResource::fan_prop_fixed_speed_t val )
    {
        std::string str;
        
        str += "SysmanResource::fan_prop_fixed_speed_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "SysmanResource::fan_prop_fixed_speed_t::units : ";
        str += to_string(val.units);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_prop_speed_table_t to std::string
    std::string to_string( const SysmanResource::fan_prop_speed_table_t val )
    {
        std::string str;
        
        str += "SysmanResource::fan_prop_speed_table_t::pCount : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pCount);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::fan_prop_speed_table_t::points : ";
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
    /// @brief Converts SysmanResource::fan_property_request_t to std::string
    std::string to_string( const SysmanResource::fan_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::fan_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::fan_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::fan_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::led_prop_rgb_cap_t to std::string
    std::string to_string( const SysmanResource::led_prop_rgb_cap_t val )
    {
        std::string str;
        
        str += "SysmanResource::led_prop_rgb_cap_t::haveRGB : ";
        str += std::to_string(val.haveRGB);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::led_prop_state_t to std::string
    std::string to_string( const SysmanResource::led_prop_state_t val )
    {
        std::string str;
        
        str += "SysmanResource::led_prop_state_t::isOn : ";
        str += std::to_string(val.isOn);
        str += "\n";
        
        str += "SysmanResource::led_prop_state_t::red : ";
        str += std::to_string(val.red);
        str += "\n";
        
        str += "SysmanResource::led_prop_state_t::green : ";
        str += std::to_string(val.green);
        str += "\n";
        
        str += "SysmanResource::led_prop_state_t::blue : ";
        str += std::to_string(val.blue);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::led_property_request_t to std::string
    std::string to_string( const SysmanResource::led_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::led_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::led_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::led_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::firmware_prop_name_t to std::string
    std::string to_string( const SysmanResource::firmware_prop_name_t val )
    {
        std::string str;
        
        str += "SysmanResource::firmware_prop_name_t::str : ";
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
    /// @brief Converts SysmanResource::firmware_prop_version_t to std::string
    std::string to_string( const SysmanResource::firmware_prop_version_t val )
    {
        std::string str;
        
        str += "SysmanResource::firmware_prop_version_t::str : ";
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
    /// @brief Converts SysmanResource::firmware_prop_check_t to std::string
    std::string to_string( const SysmanResource::firmware_prop_check_t val )
    {
        std::string str;
        
        str += "SysmanResource::firmware_prop_check_t::checksum : ";
        str += std::to_string(val.checksum);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::firmware_prop_flash_t to std::string
    std::string to_string( const SysmanResource::firmware_prop_flash_t val )
    {
        std::string str;
        
        str += "SysmanResource::firmware_prop_flash_t::pImage : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pImage);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::firmware_prop_flash_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::firmware_property_request_t to std::string
    std::string to_string( const SysmanResource::firmware_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::firmware_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::firmware_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::firmware_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_prop_accel_assets_t to std::string
    std::string to_string( const SysmanResource::pwr_prop_accel_assets_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwr_prop_accel_assets_t::assets : ";
        str += std::to_string(val.assets);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_prop_max_limit_t to std::string
    std::string to_string( const SysmanResource::pwr_prop_max_limit_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwr_prop_max_limit_t::assets : ";
        str += std::to_string(val.assets);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_prop_energy_counter_t to std::string
    std::string to_string( const SysmanResource::pwr_prop_energy_counter_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwr_prop_energy_counter_t::energy : ";
        str += std::to_string(val.energy);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_prop_sustained_limit_t to std::string
    std::string to_string( const SysmanResource::pwr_prop_sustained_limit_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwr_prop_sustained_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "SysmanResource::pwr_prop_sustained_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";
        
        str += "SysmanResource::pwr_prop_sustained_limit_t::interval : ";
        str += std::to_string(val.interval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_prop_burst_limit_t to std::string
    std::string to_string( const SysmanResource::pwr_prop_burst_limit_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwr_prop_burst_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "SysmanResource::pwr_prop_burst_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_prop_peak_limit_t to std::string
    std::string to_string( const SysmanResource::pwr_prop_peak_limit_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwr_prop_peak_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_property_request_t to std::string
    std::string to_string( const SysmanResource::pwr_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwr_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::pwr_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::pwr_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_divider_t to std::string
    std::string to_string( const SysmanResource::freq_divider_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_divider_t::numerator : ";
        str += std::to_string(val.numerator);
        str += "\n";
        
        str += "SysmanResource::freq_divider_t::denominator : ";
        str += std::to_string(val.denominator);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_accel_assets_t to std::string
    std::string to_string( const SysmanResource::freq_prop_accel_assets_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_accel_assets_t::assets : ";
        str += std::to_string(val.assets);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_domain_type_t to std::string
    std::string to_string( const SysmanResource::freq_prop_domain_type_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_domain_type_t::type : ";
        str += to_string(val.type);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_avail_clocks_t to std::string
    std::string to_string( const SysmanResource::freq_prop_avail_clocks_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_avail_clocks_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "SysmanResource::freq_prop_avail_clocks_t::pClocks : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pClocks);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_avail_dividers_t to std::string
    std::string to_string( const SysmanResource::freq_prop_avail_dividers_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_avail_dividers_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "SysmanResource::freq_prop_avail_dividers_t::pDividers : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pDividers);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_src_freq_t to std::string
    std::string to_string( const SysmanResource::freq_prop_src_freq_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_src_freq_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_dvfs_mode_t to std::string
    std::string to_string( const SysmanResource::freq_prop_dvfs_mode_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_dvfs_mode_t::mode : ";
        str += to_string(val.mode);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_freq_range_t to std::string
    std::string to_string( const SysmanResource::freq_prop_freq_range_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_freq_range_t::min : ";
        str += std::to_string(val.min);
        str += "\n";
        
        str += "SysmanResource::freq_prop_freq_range_t::max : ";
        str += std::to_string(val.max);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_freq_tdp_t to std::string
    std::string to_string( const SysmanResource::freq_prop_freq_tdp_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_freq_tdp_t::freqTdp : ";
        str += std::to_string(val.freqTdp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_freq_efficient_t to std::string
    std::string to_string( const SysmanResource::freq_prop_freq_efficient_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_freq_efficient_t::freqEfficient : ";
        str += std::to_string(val.freqEfficient);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_freq_request_t to std::string
    std::string to_string( const SysmanResource::freq_prop_freq_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_freq_request_t::freqRequest : ";
        str += std::to_string(val.freqRequest);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_freq_resolved_t to std::string
    std::string to_string( const SysmanResource::freq_prop_freq_resolved_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_freq_resolved_t::freqResolved : ";
        str += std::to_string(val.freqResolved);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_freq_divider_t to std::string
    std::string to_string( const SysmanResource::freq_prop_freq_divider_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_freq_divider_t::divider : ";
        str += to_string(val.divider);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_throttle_reasons_t to std::string
    std::string to_string( const SysmanResource::freq_prop_throttle_reasons_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_throttle_reasons_t::throttleReasons : ";
        str += std::to_string(val.throttleReasons);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_throttle_time_t to std::string
    std::string to_string( const SysmanResource::freq_prop_throttle_time_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_prop_throttle_time_t::throttleTime : ";
        str += std::to_string(val.throttleTime);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_property_request_t to std::string
    std::string to_string( const SysmanResource::freq_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::freq_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::freq_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::freq_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_prop_accel_assets_t to std::string
    std::string to_string( const SysmanResource::pwrwell_prop_accel_assets_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwrwell_prop_accel_assets_t::assets : ";
        str += std::to_string(val.assets);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_prop_promo_cap_t to std::string
    std::string to_string( const SysmanResource::pwrwell_prop_promo_cap_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwrwell_prop_promo_cap_t::canChangePromoMode : ";
        str += std::to_string(val.canChangePromoMode);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_prop_promo_mode_t to std::string
    std::string to_string( const SysmanResource::pwrwell_prop_promo_mode_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwrwell_prop_promo_mode_t::mode : ";
        str += to_string(val.mode);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_prop_utilization_t to std::string
    std::string to_string( const SysmanResource::pwrwell_prop_utilization_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwrwell_prop_utilization_t::sleepCounter : ";
        str += std::to_string(val.sleepCounter);
        str += "\n";
        
        str += "SysmanResource::pwrwell_prop_utilization_t::idleCounter : ";
        str += std::to_string(val.idleCounter);
        str += "\n";
        
        str += "SysmanResource::pwrwell_prop_utilization_t::activeCounter : ";
        str += std::to_string(val.activeCounter);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_prop_transitions_t to std::string
    std::string to_string( const SysmanResource::pwrwell_prop_transitions_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwrwell_prop_transitions_t::wakeCounter : ";
        str += std::to_string(val.wakeCounter);
        str += "\n";
        
        str += "SysmanResource::pwrwell_prop_transitions_t::execCounter : ";
        str += std::to_string(val.execCounter);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_property_request_t to std::string
    std::string to_string( const SysmanResource::pwrwell_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwrwell_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::pwrwell_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::pwrwell_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::accel_prop_accel_assets_t to std::string
    std::string to_string( const SysmanResource::accel_prop_accel_assets_t val )
    {
        std::string str;
        
        str += "SysmanResource::accel_prop_accel_assets_t::assets : ";
        str += std::to_string(val.assets);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::accel_prop_utilization_t to std::string
    std::string to_string( const SysmanResource::accel_prop_utilization_t val )
    {
        std::string str;
        
        str += "SysmanResource::accel_prop_utilization_t::activeCounter : ";
        str += std::to_string(val.activeCounter);
        str += "\n";
        
        str += "SysmanResource::accel_prop_utilization_t::idleCounter : ";
        str += std::to_string(val.idleCounter);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::accel_property_request_t to std::string
    std::string to_string( const SysmanResource::accel_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::accel_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::accel_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::accel_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_retire_info_t to std::string
    std::string to_string( const SysmanResource::mem_retire_info_t val )
    {
        std::string str;
        
        str += "SysmanResource::mem_retire_info_t::address : ";
        str += std::to_string(val.address);
        str += "\n";
        
        str += "SysmanResource::mem_retire_info_t::reason : ";
        str += to_string(val.reason);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_type_t to std::string
    std::string to_string( const SysmanResource::mem_prop_type_t val )
    {
        std::string str;
        
        str += "SysmanResource::mem_prop_type_t::type : ";
        str += to_string(val.type);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_ecc_cap_t to std::string
    std::string to_string( const SysmanResource::mem_prop_ecc_cap_t val )
    {
        std::string str;
        
        str += "SysmanResource::mem_prop_ecc_cap_t::isEccCapable : ";
        str += std::to_string(val.isEccCapable);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_bad_list_t to std::string
    std::string to_string( const SysmanResource::mem_prop_bad_list_t val )
    {
        std::string str;
        
        str += "SysmanResource::mem_prop_bad_list_t::pCount : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pCount);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::mem_prop_bad_list_t::pList : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pList);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_utilization_t to std::string
    std::string to_string( const SysmanResource::mem_prop_utilization_t val )
    {
        std::string str;
        
        str += "SysmanResource::mem_prop_utilization_t::allocated : ";
        str += std::to_string(val.allocated);
        str += "\n";
        
        str += "SysmanResource::mem_prop_utilization_t::unallocated : ";
        str += std::to_string(val.unallocated);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_bandwidth_t to std::string
    std::string to_string( const SysmanResource::mem_prop_bandwidth_t val )
    {
        std::string str;
        
        str += "SysmanResource::mem_prop_bandwidth_t::readCounter : ";
        str += std::to_string(val.readCounter);
        str += "\n";
        
        str += "SysmanResource::mem_prop_bandwidth_t::writeCounter : ";
        str += std::to_string(val.writeCounter);
        str += "\n";
        
        str += "SysmanResource::mem_prop_bandwidth_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_ecc_enable_t to std::string
    std::string to_string( const SysmanResource::mem_prop_ecc_enable_t val )
    {
        std::string str;
        
        str += "SysmanResource::mem_prop_ecc_enable_t::enable : ";
        str += std::to_string(val.enable);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_ecc_poison_t to std::string
    std::string to_string( const SysmanResource::mem_prop_ecc_poison_t val )
    {
        std::string str;
        
        str += "SysmanResource::mem_prop_ecc_poison_t::doPoison : ";
        str += std::to_string(val.doPoison);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_property_request_t to std::string
    std::string to_string( const SysmanResource::mem_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::mem_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::mem_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::mem_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_speed_t to std::string
    std::string to_string( const SysmanResource::link_speed_t val )
    {
        std::string str;
        
        str += "SysmanResource::link_speed_t::numLanes : ";
        str += std::to_string(val.numLanes);
        str += "\n";
        
        str += "SysmanResource::link_speed_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "SysmanResource::link_speed_t::bandwidth : ";
        str += std::to_string(val.bandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_type_t to std::string
    std::string to_string( const SysmanResource::link_prop_type_t val )
    {
        std::string str;
        
        str += "SysmanResource::link_prop_type_t::type : ";
        str += to_string(val.type);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_bus_address_t to std::string
    std::string to_string( const SysmanResource::link_prop_bus_address_t val )
    {
        std::string str;
        
        str += "SysmanResource::link_prop_bus_address_t::str : ";
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
    /// @brief Converts SysmanResource::link_prop_pwr_cap_t to std::string
    std::string to_string( const SysmanResource::link_prop_pwr_cap_t val )
    {
        std::string str;
        
        str += "SysmanResource::link_prop_pwr_cap_t::havePwrMgmt : ";
        str += std::to_string(val.havePwrMgmt);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_avail_speeds_t to std::string
    std::string to_string( const SysmanResource::link_prop_avail_speeds_t val )
    {
        std::string str;
        
        str += "SysmanResource::link_prop_avail_speeds_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "SysmanResource::link_prop_avail_speeds_t::pList : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pList);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_max_packet_size_t to std::string
    std::string to_string( const SysmanResource::link_prop_max_packet_size_t val )
    {
        std::string str;
        
        str += "SysmanResource::link_prop_max_packet_size_t::maxPacketSize : ";
        str += std::to_string(val.maxPacketSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_bandwidth_t to std::string
    std::string to_string( const SysmanResource::link_prop_bandwidth_t val )
    {
        std::string str;
        
        str += "SysmanResource::link_prop_bandwidth_t::recvCounter : ";
        str += std::to_string(val.recvCounter);
        str += "\n";
        
        str += "SysmanResource::link_prop_bandwidth_t::sendCounter : ";
        str += std::to_string(val.sendCounter);
        str += "\n";
        
        str += "SysmanResource::link_prop_bandwidth_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_speed_t to std::string
    std::string to_string( const SysmanResource::link_prop_speed_t val )
    {
        std::string str;
        
        str += "SysmanResource::link_prop_speed_t::pSpeed : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pSpeed);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_speed_range_t to std::string
    std::string to_string( const SysmanResource::link_prop_speed_range_t val )
    {
        std::string str;
        
        str += "SysmanResource::link_prop_speed_range_t::pMinSpeed : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pMinSpeed);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::link_prop_speed_range_t::pMaxSpeed : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pMaxSpeed);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_property_request_t to std::string
    std::string to_string( const SysmanResource::link_property_request_t val )
    {
        std::string str;
        
        str += "SysmanResource::link_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "SysmanResource::link_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "SysmanResource::link_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

} // namespace xet
