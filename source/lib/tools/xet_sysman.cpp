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
    xet_device_group_handle_t hDeviceGroup,         ///< [in] handle of the device group
    uint32_t flags,                                 ///< [in] bitfield of ::xet_sysman_init_flags_t
    xet_sysman_handle_t* phSysman                   ///< [out] handle for accessing SMI features
    )
{
    auto pfnCreate = xet_lib::context.ddiTable.Sysman.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hDeviceGroup, flags, phSysman );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a Sysman handle
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
/// @brief Convert Sysman UUID to a string
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
                                                    ///< If size is non-zero and larger than the string length, the number of
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
/// @brief Retrieves resource containers of a given type
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetResourceContainers(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_res_container_type_t type,                  ///< [in] The type of resource containers to enumerate
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of resource containers.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of resource containers of the given type that are available.
                                                    ///< If count is non-zero, then driver will only retrieve that number of
                                                    ///< resource containers of the given type starting from index 0.
                                                    ///< If count is larger than the number of resource containers available,
                                                    ///< then the driver will update the value with the correct number of
                                                    ///< resource containers of a given type that are available.
    xet_res_container_handle_t* phResContainers     ///< [out][optional][range(0, *pCount)] array of handle of resource
                                                    ///< containers
    )
{
    auto pfnGetResourceContainers = xet_lib::context.ddiTable.Sysman.pfnGetResourceContainers;
    if( nullptr == pfnGetResourceContainers )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetResourceContainers( hSysman, type, pCount, phResContainers );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the resource container for a device
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
///         + nullptr == hDevice
///         + nullptr == phResContainer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetDeviceResourceContainer(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xe_device_handle_t hDevice,                     ///< [in] Handle to the device. It must be a member of the same Device
                                                    ///< Group as hSysman was created from.
    xet_res_container_handle_t* phResContainer      ///< [out] Resource container for the specified device.
    )
{
    auto pfnGetDeviceResourceContainer = xet_lib::context.ddiTable.Sysman.pfnGetDeviceResourceContainer;
    if( nullptr == pfnGetDeviceResourceContainer )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDeviceResourceContainer( hSysman, hDevice, phResContainer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the resource container based on its UUID
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
///         + nullptr == uuid
///         + nullptr == phResContainer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetResourceContainerByUuid(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    const xet_resource_uuid_t* uuid,                ///< [in] UUID for the resource container.
    xet_res_container_handle_t* phResContainer      ///< [out] Resource container with UUID.
    )
{
    auto pfnGetResourceContainerByUuid = xet_lib::context.ddiTable.Sysman.pfnGetResourceContainerByUuid;
    if( nullptr == pfnGetResourceContainerByUuid )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetResourceContainerByUuid( hSysman, uuid, phResContainer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Compare if two resource container handles reference the same
///        underlying resource container
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
///         + nullptr == hLhs
///         + nullptr == hRhs
///         + nullptr == pIsSame
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResContainerIsSame(
    xet_res_container_handle_t hLhs,                ///< [in] Handle of the resource container
    xet_res_container_handle_t hRhs,                ///< [in] Handle of the resource container
    xe_bool_t* pIsSame                              ///< [in] Sets to True if the two resource containers reference the same
                                                    ///< underlying resource container
    )
{
    auto pfnIsSame = xet_lib::context.ddiTable.SysmanResContainer.pfnIsSame;
    if( nullptr == pfnIsSame )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnIsSame( hLhs, hRhs, pIsSame );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get generic information about a resource container
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
///         + nullptr == hResContainer
///         + nullptr == pInfo
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResContainerGetInfo(
    xet_res_container_handle_t hResContainer,       ///< [in] Handle of the resource container
    xet_res_container_info_t* pInfo                 ///< [out] Generic information about the resource container.
    )
{
    auto pfnGetInfo = xet_lib::context.ddiTable.SysmanResContainer.pfnGetInfo;
    if( nullptr == pfnGetInfo )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetInfo( hResContainer, pInfo );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get parent resource container
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
///         + nullptr == hResContainer
///         + nullptr == phResContainer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResContainerGetParent(
    xet_res_container_handle_t hResContainer,       ///< [in] Handle of the resource container.
    xet_res_container_handle_t* phResContainer      ///< [out] Handle of the parent resource container.
    )
{
    auto pfnGetParent = xet_lib::context.ddiTable.SysmanResContainer.pfnGetParent;
    if( nullptr == pfnGetParent )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetParent( hResContainer, phResContainer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get children resource containers
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
///         + nullptr == hResContainter
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResContainerGetChildren(
    xet_res_container_handle_t hResContainter,      ///< [in] Handle of the resource container
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of child resource containers.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of child resource containers.
                                                    ///< If count is non-zero, then driver will only retrieve that number of
                                                    ///< child resource containers starting from index 0.
                                                    ///< If count is larger than the number of child resource containers
                                                    ///< available, then the driver will update the value with the correct
                                                    ///< number of child resource containers.
    xet_res_container_handle_t* phResContainers     ///< [out][optional][range(0, *pCount)] array of handle of resource
                                                    ///< containers
    )
{
    auto pfnGetChildren = xet_lib::context.ddiTable.SysmanResContainer.pfnGetChildren;
    if( nullptr == pfnGetChildren )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetChildren( hResContainter, pCount, phResContainers );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get peer resource containers
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
///         + nullptr == hResContainter
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResContainerGetPeers(
    xet_res_container_handle_t hResContainter,      ///< [in] Handle of the resource container
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of peer resource containers.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of peer resource containers.
                                                    ///< If count is non-zero, then driver will only retrieve that number of
                                                    ///< peer resource containers starting from index 0.
                                                    ///< If count is larger than the number of peer resource containers
                                                    ///< available, then the driver will update the value with the correct
                                                    ///< number of peer resource containers.
    xet_res_container_handle_t* phResContainers     ///< [out][optional][range(0, *pCount)] array of handle of resource
                                                    ///< containers
    )
{
    auto pfnGetPeers = xet_lib::context.ddiTable.SysmanResContainer.pfnGetPeers;
    if( nullptr == pfnGetPeers )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPeers( hResContainter, pCount, phResContainers );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get human-readable name for an accelerator asset
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hResContainer
///         + nullptr == ppName
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResContainerGetAccelAssetName(
    xet_res_container_handle_t hResContainer,       ///< [in] Handle to a resource container where the asset is located
    xet_accel_asset_t type,                         ///< [in] The type of accelerator asset
    const char** ppName                             ///< [in] Pointer to the string will be stored here
    )
{
    auto pfnGetAccelAssetName = xet_lib::context.ddiTable.SysmanResContainer.pfnGetAccelAssetName;
    if( nullptr == pfnGetAccelAssetName )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetAccelAssetName( hResContainer, type, ppName );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves resources of a given type located in a container
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
///         + nullptr == hResContainter
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResContainerGetResources(
    xet_res_container_handle_t hResContainter,      ///< [in] Handle of the resource container
    xet_resource_type_t type,                       ///< [in] The type of resources to enumerate
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of resource.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of resources of the given type that are available.
                                                    ///< If count is non-zero, then driver will only retrieve that number of
                                                    ///< resources of the given type starting from index 0.
                                                    ///< If count is larger than the number of resources available, then the
                                                    ///< driver will update the value with the correct number of resources of a
                                                    ///< given type that are available.
    xet_resource_handle_t* phResources              ///< [in][optional][range(0, *pCount)] array of handle of resources
    )
{
    auto pfnGetResources = xet_lib::context.ddiTable.SysmanResContainer.pfnGetResources;
    if( nullptr == pfnGetResources )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetResources( hResContainter, type, pCount, phResources );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Compare if two resource handles reference the same underlying resource
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
///         + nullptr == hLhs
///         + nullptr == hRhs
///         + nullptr == pIsSame
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceIsSame(
    xet_resource_handle_t hLhs,                     ///< [in] Handle of the resource
    xet_resource_handle_t hRhs,                     ///< [in] Handle of the resource
    xe_bool_t* pIsSame                              ///< [in] Sets to True if the two resources reference the same underlying
                                                    ///< resource
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
    xet_resource_info_t* pInfo                      ///< [out] Generic information about the resource.
    )
{
    auto pfnGetInfo = xet_lib::context.ddiTable.SysmanResource.pfnGetInfo;
    if( nullptr == pfnGetInfo )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetInfo( hResource, pInfo );
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
///         + nullptr == hResContainer
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResContainerGetBoardProperties(
    xet_res_container_handle_t hResContainer,       ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_board_properties_t* pIndexes,         ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetBoardProperties = xet_lib::context.ddiTable.SysmanResContainer.pfnGetBoardProperties;
    if( nullptr == pfnGetBoardProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetBoardProperties( hResContainer, count, pIndexes, pValues, pSize );
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
///         + nullptr == hResContainer
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResContainerGetDeviceProperties(
    xet_res_container_handle_t hResContainer,       ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_device_properties_t* pIndexes,        ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetDeviceProperties = xet_lib::context.ddiTable.SysmanResContainer.pfnGetDeviceProperties;
    if( nullptr == pfnGetDeviceProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDeviceProperties( hResContainer, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set new values of device properties
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
///         + nullptr == hResContainer
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResContainerSetDeviceProperties(
    xet_res_container_handle_t hResContainer,       ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_device_properties_t* pIndexes,        ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetDeviceProperties = xet_lib::context.ddiTable.SysmanResContainer.pfnSetDeviceProperties;
    if( nullptr == pfnSetDeviceProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetDeviceProperties( hResContainer, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PSU property data
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetPsuProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_psu_properties_t* pIndexes,           ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetPsuProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetPsuProperties;
    if( nullptr == pfnGetPsuProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPsuProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set new PSU properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetPsuProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_psu_properties_t* pIndexes,           ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetPsuProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetPsuProperties;
    if( nullptr == pfnSetPsuProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPsuProperties( hResource, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature sensor property data
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetTempProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_temp_properties_t* pIndexes,          ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetTempProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetTempProperties;
    if( nullptr == pfnGetTempProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetTempProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set temperature sensor properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetTempProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_temp_properties_t* pIndexes,          ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetTempProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetTempProperties;
    if( nullptr == pfnSetTempProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetTempProperties( hResource, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan property data
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetFanProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_fan_properties_t* pIndexes,           ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetFanProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetFanProperties;
    if( nullptr == pfnGetFanProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetFanProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set new fan properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetFanProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_fan_properties_t* pIndexes,           ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetFanProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetFanProperties;
    if( nullptr == pfnSetFanProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetFanProperties( hResource, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get LED property data
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetLedProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_led_properties_t* pIndexes,           ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetLedProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetLedProperties;
    if( nullptr == pfnGetLedProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetLedProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set LED properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetLedProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_led_properties_t* pIndexes,           ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetLedProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetLedProperties;
    if( nullptr == pfnSetLedProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetLedProperties( hResource, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware property data
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetFirmwareProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_firmware_properties_t* pIndexes,      ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetFirmwareProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetFirmwareProperties;
    if( nullptr == pfnGetFirmwareProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetFirmwareProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set firmware properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetFirmwareProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_firmware_properties_t* pIndexes,      ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetFirmwareProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetFirmwareProperties;
    if( nullptr == pfnSetFirmwareProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetFirmwareProperties( hResource, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power domain property data
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetPwrProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_pwr_properties_t* pIndexes,           ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetPwrProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetPwrProperties;
    if( nullptr == pfnGetPwrProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPwrProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power domain properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetPwrProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_pwr_properties_t* pIndexes,           ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetPwrProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetPwrProperties;
    if( nullptr == pfnSetPwrProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPwrProperties( hResource, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency domain property data
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetFreqProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_freq_properties_t* pIndexes,          ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetFreqProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetFreqProperties;
    if( nullptr == pfnGetFreqProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetFreqProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency domain properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetFreqProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_freq_properties_t* pIndexes,          ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetFreqProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetFreqProperties;
    if( nullptr == pfnSetFreqProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetFreqProperties( hResource, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power-well domain property data
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetPwrWellProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_pwrwell_properties_t* pIndexes,       ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetPwrWellProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetPwrWellProperties;
    if( nullptr == pfnGetPwrWellProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPwrWellProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power-well domain properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetPwrWellProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_pwrwell_properties_t* pIndexes,       ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetPwrWellProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetPwrWellProperties;
    if( nullptr == pfnSetPwrWellProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPwrWellProperties( hResource, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get accelerator asset resource properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetAccelProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_accel_properties_t* pIndexes,         ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetAccelProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetAccelProperties;
    if( nullptr == pfnGetAccelProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetAccelProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set accelerator asset resource properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetAccelProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_accel_properties_t* pIndexes,         ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetAccelProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetAccelProperties;
    if( nullptr == pfnSetAccelProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetAccelProperties( hResource, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory resource properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetMemProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_mem_properties_t* pIndexes,           ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetMemProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetMemProperties;
    if( nullptr == pfnGetMemProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set memory resource properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetMemProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_mem_properties_t* pIndexes,           ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetMemProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetMemProperties;
    if( nullptr == pfnSetMemProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetMemProperties( hResource, count, pIndexes, pValues, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get link resource properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceGetLinkProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_link_properties_t* pIndexes,          ///< [in] An array of property indexes to be read
    void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
    uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                    ///< If size is zero, then the driver will update the value with the size
                                                    ///< required to store the requested properties.
                                                    ///< If size is less than that required to store the requested data for the
                                                    ///< properties, the driver will update the value with the required size
                                                    ///< and return an error.
                                                    ///< If size is larger than that required to store the requested data for
                                                    ///< the properties, the driver will update the value with the size of the
                                                    ///< data returned.
    )
{
    auto pfnGetLinkProperties = xet_lib::context.ddiTable.SysmanResource.pfnGetLinkProperties;
    if( nullptr == pfnGetLinkProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetLinkProperties( hResource, count, pIndexes, pValues, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set link resource properties
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
///         + nullptr == pIndexes
///         + nullptr == pValues
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanResourceSetLinkProperties(
    xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
    uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
    const xet_link_properties_t* pIndexes,          ///< [in] An array of property indexes to be set
    void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                    ///< properties.
    uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
    )
{
    auto pfnSetLinkProperties = xet_lib::context.ddiTable.SysmanResource.pfnSetLinkProperties;
    if( nullptr == pfnSetLinkProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetLinkProperties( hResource, count, pIndexes, pValues, size );
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
    xet_res_container_handle_t hResource,           ///< [in] Handle of the resource container. Events from any contained
                                                    ///< devices will be registered.
                                                    ///< If the handle is ::XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE, events
                                                    ///< from all devices will be registered.
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
    xet_res_container_handle_t hResource,           ///< [in] Handle of the resource container. Events from any contained
                                                    ///< devices will be unregistered.
                                                    ///< If the handle is ::XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE, events
                                                    ///< from all devices will be unregistered.
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
    SysmanResContainer::SysmanResContainer( 
        res_container_handle_t handle,                  ///< [in] handle of the resource container
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanResource::SysmanResource( 
        resource_handle_t handle,                       ///< [in] handle of resource
        SysmanResContainer* pResContainer               ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pResContainer( pResContainer )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a handle to access SMI features
    /// 
    /// @details
    ///     - Initializes internal structures to support SMI features.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **nvmlInit**
    ///     - **rsmi_init**
    /// 
    /// @returns
    ///     - Sysman*: handle for accessing SMI features
    /// 
    /// @throws result_t
    Sysman* __xecall
    Sysman::Create(
        DeviceGroup* pDeviceGroup,                      ///< [in] pointer to the device group
        uint32_t flags                                  ///< [in] bitfield of ::xet_sysman_init_flags_t
        )
    {
        xet_sysman_handle_t hSysman;

        auto result = static_cast<result_t>( ::xetSysmanCreate(
            reinterpret_cast<xet_device_group_handle_t>( pDeviceGroup->getHandle() ),
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
    /// @brief Convert Sysman UUID to a string
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
                                                        ///< If size is non-zero and larger than the string length, the number of
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
    /// @brief Retrieves resource containers of a given type
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResContainer*: array of handle of resource containers
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetResourceContainers(
        res_container_type_t type,                      ///< [in] The type of resource containers to enumerate
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of resource containers.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of resource containers of the given type that are available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< resource containers of the given type starting from index 0.
                                                        ///< If count is larger than the number of resource containers available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< resource containers of a given type that are available.
        SysmanResContainer** ppResContainers            ///< [out][optional][range(0, *pCount)] array of pointer to resource
                                                        ///< containers
        )
    {
        thread_local std::vector<xet_res_container_handle_t> hResContainers;
        hResContainers.resize( ( ppResContainers ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanGetResourceContainers(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            static_cast<xet_res_container_type_t>( type ),
            pCount,
            hResContainers.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetResourceContainers" );

        for( uint32_t i = 0; ( ppResContainers ) && ( i < *pCount ); ++i )
            ppResContainers[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppResContainers ) && ( i < *pCount ); ++i )
                ppResContainers[ i ] = new SysmanResContainer( reinterpret_cast<res_container_handle_t>( hResContainers[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppResContainers ) && ( i < *pCount ); ++i )
            {
                delete ppResContainers[ i ];
                ppResContainers[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::GetResourceContainers" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves the resource container for a device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResContainer*: Resource container for the specified device.
    /// 
    /// @throws result_t
    SysmanResContainer* __xecall
    Sysman::GetDeviceResourceContainer(
        xe::Device* pDevice                             ///< [in] Handle to the device. It must be a member of the same Device
                                                        ///< Group as hSysman was created from.
        )
    {
        xet_res_container_handle_t hResContainer;

        auto result = static_cast<result_t>( ::xetSysmanGetDeviceResourceContainer(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            &hResContainer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetDeviceResourceContainer" );

        SysmanResContainer* pResContainer = nullptr;

        try
        {
            pResContainer = new SysmanResContainer( reinterpret_cast<res_container_handle_t>( hResContainer ), this );
        }
        catch( std::bad_alloc& )
        {
            delete pResContainer;
            pResContainer = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::GetDeviceResourceContainer" );
        }

        return pResContainer;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves the resource container based on its UUID
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResContainer*: Resource container with UUID.
    /// 
    /// @throws result_t
    SysmanResContainer* __xecall
    Sysman::GetResourceContainerByUuid(
        const resource_uuid_t* uuid                     ///< [in] UUID for the resource container.
        )
    {
        xet_res_container_handle_t hResContainer;

        auto result = static_cast<result_t>( ::xetSysmanGetResourceContainerByUuid(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<const xet_resource_uuid_t*>( uuid ),
            &hResContainer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetResourceContainerByUuid" );

        SysmanResContainer* pResContainer = nullptr;

        try
        {
            pResContainer = new SysmanResContainer( reinterpret_cast<res_container_handle_t>( hResContainer ), this );
        }
        catch( std::bad_alloc& )
        {
            delete pResContainer;
            pResContainer = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::GetResourceContainerByUuid" );
        }

        return pResContainer;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Compare if two resource container handles reference the same
    ///        underlying resource container
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResContainer::IsSame(
        SysmanResContainer* pRhs,                       ///< [in] Handle of the resource container
        xe::bool_t* pIsSame                             ///< [in] Sets to True if the two resource containers reference the same
                                                        ///< underlying resource container
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResContainerIsSame(
            reinterpret_cast<xet_res_container_handle_t>( getHandle() ),
            reinterpret_cast<xet_res_container_handle_t>( pRhs->getHandle() ),
            reinterpret_cast<xe_bool_t*>( pIsSame ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::IsSame" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get generic information about a resource container
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - Sysman::res_container_info_t: Generic information about the resource container.
    /// 
    /// @throws result_t
    Sysman::Sysman::res_container_info_t __xecall
    SysmanResContainer::GetInfo(
        void
        )
    {
        xet_res_container_info_t info;

        auto result = static_cast<result_t>( ::xetSysmanResContainerGetInfo(
            reinterpret_cast<xet_res_container_handle_t>( getHandle() ),
            &info ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetInfo" );

        return *reinterpret_cast<Sysman::res_container_info_t*>( &info );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get parent resource container
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResContainer*: Handle of the parent resource container.
    /// 
    /// @throws result_t
    SysmanResContainer* __xecall
    SysmanResContainer::GetParent(
        void
        )
    {
        xet_res_container_handle_t hResContainer;

        auto result = static_cast<result_t>( ::xetSysmanResContainerGetParent(
            reinterpret_cast<xet_res_container_handle_t>( getHandle() ),
            &hResContainer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetParent" );

        SysmanResContainer* pResContainer = nullptr;

        try
        {
            pResContainer = new SysmanResContainer( reinterpret_cast<res_container_handle_t>( hResContainer ), m_pSysman );
        }
        catch( std::bad_alloc& )
        {
            delete pResContainer;
            pResContainer = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetParent" );
        }

        return pResContainer;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get children resource containers
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResContainer*: array of handle of resource containers
    /// 
    /// @throws result_t
    void __xecall
    SysmanResContainer::GetChildren(
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of child resource containers.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of child resource containers.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< child resource containers starting from index 0.
                                                        ///< If count is larger than the number of child resource containers
                                                        ///< available, then the driver will update the value with the correct
                                                        ///< number of child resource containers.
        SysmanResContainer** ppResContainers            ///< [out][optional][range(0, *pCount)] array of pointer to resource
                                                        ///< containers
        )
    {
        thread_local std::vector<xet_res_container_handle_t> hResContainers;
        hResContainers.resize( ( ppResContainers ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanResContainerGetChildren(
            reinterpret_cast<xet_res_container_handle_t>( getHandle() ),
            pCount,
            hResContainers.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetChildren" );

        for( uint32_t i = 0; ( ppResContainers ) && ( i < *pCount ); ++i )
            ppResContainers[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppResContainers ) && ( i < *pCount ); ++i )
                ppResContainers[ i ] = new SysmanResContainer( reinterpret_cast<res_container_handle_t>( hResContainers[ i ] ), m_pSysman );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppResContainers ) && ( i < *pCount ); ++i )
            {
                delete ppResContainers[ i ];
                ppResContainers[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetChildren" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get peer resource containers
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanResContainer*: array of handle of resource containers
    /// 
    /// @throws result_t
    void __xecall
    SysmanResContainer::GetPeers(
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of peer resource containers.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of peer resource containers.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< peer resource containers starting from index 0.
                                                        ///< If count is larger than the number of peer resource containers
                                                        ///< available, then the driver will update the value with the correct
                                                        ///< number of peer resource containers.
        SysmanResContainer** ppResContainers            ///< [out][optional][range(0, *pCount)] array of pointer to resource
                                                        ///< containers
        )
    {
        thread_local std::vector<xet_res_container_handle_t> hResContainers;
        hResContainers.resize( ( ppResContainers ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanResContainerGetPeers(
            reinterpret_cast<xet_res_container_handle_t>( getHandle() ),
            pCount,
            hResContainers.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetPeers" );

        for( uint32_t i = 0; ( ppResContainers ) && ( i < *pCount ); ++i )
            ppResContainers[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppResContainers ) && ( i < *pCount ); ++i )
                ppResContainers[ i ] = new SysmanResContainer( reinterpret_cast<res_container_handle_t>( hResContainers[ i ] ), m_pSysman );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppResContainers ) && ( i < *pCount ); ++i )
            {
                delete ppResContainers[ i ];
                ppResContainers[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetPeers" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get human-readable name for an accelerator asset
    /// 
    /// @throws result_t
    void __xecall
    SysmanResContainer::GetAccelAssetName(
        accel_asset_t type,                             ///< [in] The type of accelerator asset
        const char** ppName                             ///< [in] Pointer to the string will be stored here
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResContainerGetAccelAssetName(
            reinterpret_cast<xet_res_container_handle_t>( getHandle() ),
            static_cast<xet_accel_asset_t>( type ),
            ppName ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetAccelAssetName" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves resources of a given type located in a container
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResContainer::GetResources(
        Sysman::resource_type_t type,                   ///< [in] The type of resources to enumerate
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of resource.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of resources of the given type that are available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< resources of the given type starting from index 0.
                                                        ///< If count is larger than the number of resources available, then the
                                                        ///< driver will update the value with the correct number of resources of a
                                                        ///< given type that are available.
        SysmanResource** ppResources                    ///< [in][optional][range(0, *pCount)] array of pointer to resources
        )
    {
        thread_local std::vector<xet_resource_handle_t> hResources;
        hResources.resize( 0 );
        hResources.reserve( *pCount );
        for( uint32_t i = 0; i < *pCount; ++i )
            hResources.emplace_back( ( ppResources ) ? reinterpret_cast<xet_resource_handle_t>( ppResources[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::xetSysmanResContainerGetResources(
            reinterpret_cast<xet_res_container_handle_t>( getHandle() ),
            static_cast<xet_resource_type_t>( type ),
            pCount,
            hResources.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetResources" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Compare if two resource handles reference the same underlying resource
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::IsSame(
        SysmanResource* pRhs,                           ///< [in] Handle of the resource
        xe::bool_t* pIsSame                             ///< [in] Sets to True if the two resources reference the same underlying
                                                        ///< resource
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
    ///     - Sysman::resource_info_t: Generic information about the resource.
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
    /// @brief Get board property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResContainer::GetBoardProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const board_properties_t* pIndexes,             ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResContainerGetBoardProperties(
            reinterpret_cast<xet_res_container_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_board_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetBoardProperties" );
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
    SysmanResContainer::GetDeviceProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const device_properties_t* pIndexes,            ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResContainerGetDeviceProperties(
            reinterpret_cast<xet_res_container_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_device_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::GetDeviceProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set new values of device properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResContainer::SetDeviceProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const device_properties_t* pIndexes,            ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResContainerSetDeviceProperties(
            reinterpret_cast<xet_res_container_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_device_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResContainer::SetDeviceProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PSU property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetPsuProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const psu_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetPsuProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_psu_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetPsuProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set new PSU properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetPsuProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const psu_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetPsuProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_psu_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetPsuProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get temperature sensor property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetTempProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const temp_properties_t* pIndexes,              ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetTempProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_temp_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetTempProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set temperature sensor properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetTempProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const temp_properties_t* pIndexes,              ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetTempProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_temp_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetTempProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get fan property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetFanProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const fan_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetFanProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_fan_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetFanProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set new fan properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetFanProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const fan_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetFanProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_fan_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetFanProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get LED property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetLedProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const led_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetLedProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_led_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetLedProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set LED properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetLedProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const led_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetLedProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_led_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetLedProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get firmware property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetFirmwareProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const firmware_properties_t* pIndexes,          ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetFirmwareProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_firmware_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetFirmwareProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set firmware properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetFirmwareProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const firmware_properties_t* pIndexes,          ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetFirmwareProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_firmware_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetFirmwareProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power domain property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetPwrProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const pwr_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetPwrProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_pwr_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetPwrProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set power domain properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetPwrProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const pwr_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetPwrProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_pwr_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetPwrProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get frequency domain property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetFreqProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const freq_properties_t* pIndexes,              ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetFreqProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_freq_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetFreqProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set frequency domain properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetFreqProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const freq_properties_t* pIndexes,              ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetFreqProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_freq_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetFreqProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power-well domain property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetPwrWellProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const pwrwell_properties_t* pIndexes,           ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetPwrWellProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_pwrwell_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetPwrWellProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set power-well domain properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetPwrWellProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const pwrwell_properties_t* pIndexes,           ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetPwrWellProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_pwrwell_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetPwrWellProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get accelerator asset resource properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetAccelProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const accel_properties_t* pIndexes,             ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetAccelProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_accel_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetAccelProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set accelerator asset resource properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetAccelProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const accel_properties_t* pIndexes,             ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetAccelProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_accel_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetAccelProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory resource properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetMemProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const mem_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetMemProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_mem_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetMemProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set memory resource properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetMemProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const mem_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetMemProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_mem_properties_t*>( pIndexes ),
            pValues,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::SetMemProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get link resource properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::GetLinkProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const link_properties_t* pIndexes,              ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceGetLinkProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_link_properties_t*>( pIndexes ),
            pValues,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanResource::GetLinkProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set link resource properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanResource::SetLinkProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        const link_properties_t* pIndexes,              ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanResourceSetLinkProperties(
            reinterpret_cast<xet_resource_handle_t>( getHandle() ),
            count,
            reinterpret_cast<const xet_link_properties_t*>( pIndexes ),
            pValues,
            size ) );

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
        SysmanResContainer* pResource,                  ///< [in] Handle of the resource container. Events from any contained
                                                        ///< devices will be registered.
                                                        ///< If the handle is ::XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE, events
                                                        ///< from all devices will be registered.
        uint32_t events                                 ///< [in] Bitfield of events to register.
                                                        ///< Construct by ORing (1<<::xet_sysman_event_type_t).
                                                        ///< Set to (~0) to register to receive all events.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanRegisterEvents(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_res_container_handle_t>( pResource->getHandle() ),
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
        SysmanResContainer* pResource,                  ///< [in] Handle of the resource container. Events from any contained
                                                        ///< devices will be unregistered.
                                                        ///< If the handle is ::XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE, events
                                                        ///< from all devices will be unregistered.
        uint32_t events                                 ///< [in] Bitfield of events to unregister.
                                                        ///< Construct by ORing (1<<::xet_sysman_event_type_t).
                                                        ///< Set to (~0) to unregister all events.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanUnregisterEvents(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_res_container_handle_t>( pResource->getHandle() ),
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
    /// @brief Converts Sysman::res_container_type_t to std::string
    std::string to_string( const Sysman::res_container_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::res_container_type_t::UNIT:
            str = "Sysman::res_container_type_t::UNIT";
            break;

        case Sysman::res_container_type_t::BOARD:
            str = "Sysman::res_container_type_t::BOARD";
            break;

        case Sysman::res_container_type_t::DEVICE:
            str = "Sysman::res_container_type_t::DEVICE";
            break;

        case Sysman::res_container_type_t::SUBDEVICE:
            str = "Sysman::res_container_type_t::SUBDEVICE";
            break;

        case Sysman::res_container_type_t::MAX_TYPES:
            str = "Sysman::res_container_type_t::MAX_TYPES";
            break;

        default:
            str = "Sysman::res_container_type_t::?";
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

        case Sysman::resource_type_t::MEMORY:
            str = "Sysman::resource_type_t::MEMORY";
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
    /// @brief Converts Sysman::res_container_info_t to std::string
    std::string to_string( const Sysman::res_container_info_t val )
    {
        std::string str;
        
        str += "Sysman::res_container_info_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";
        
        str += "Sysman::res_container_info_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Sysman::res_container_info_t::haveParent : ";
        str += std::to_string(val.haveParent);
        str += "\n";
        
        str += "Sysman::res_container_info_t::numChildren : ";
        str += std::to_string(val.numChildren);
        str += "\n";
        
        str += "Sysman::res_container_info_t::numPeers : ";
        str += std::to_string(val.numPeers);
        str += "\n";
        
        str += "Sysman::res_container_info_t::numResourcesByType : ";
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
        
        str += "Sysman::resource_info_t::resContainerUuid : ";
        str += to_string(val.resContainerUuid);
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
    /// @brief Converts SysmanResContainer::accel_asset_t to std::string
    std::string to_string( const SysmanResContainer::accel_asset_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResContainer::accel_asset_t::PCIE_CONTROLLER:
            str = "SysmanResContainer::accel_asset_t::PCIE_CONTROLLER";
            break;

        case SysmanResContainer::accel_asset_t::IDI_MEM_CONTROLLER:
            str = "SysmanResContainer::accel_asset_t::IDI_MEM_CONTROLLER";
            break;

        case SysmanResContainer::accel_asset_t::HBM_MEM_CONTROLLER:
            str = "SysmanResContainer::accel_asset_t::HBM_MEM_CONTROLLER";
            break;

        case SysmanResContainer::accel_asset_t::L3_CACHE:
            str = "SysmanResContainer::accel_asset_t::L3_CACHE";
            break;

        case SysmanResContainer::accel_asset_t::BLILTTER:
            str = "SysmanResContainer::accel_asset_t::BLILTTER";
            break;

        case SysmanResContainer::accel_asset_t::VIDEO_DECODER:
            str = "SysmanResContainer::accel_asset_t::VIDEO_DECODER";
            break;

        case SysmanResContainer::accel_asset_t::VIDEO_ENCODER:
            str = "SysmanResContainer::accel_asset_t::VIDEO_ENCODER";
            break;

        case SysmanResContainer::accel_asset_t::VIDEO_PROCESSING:
            str = "SysmanResContainer::accel_asset_t::VIDEO_PROCESSING";
            break;

        case SysmanResContainer::accel_asset_t::_3D_FF:
            str = "SysmanResContainer::accel_asset_t::_3D_FF";
            break;

        case SysmanResContainer::accel_asset_t::_3D_RENDER:
            str = "SysmanResContainer::accel_asset_t::_3D_RENDER";
            break;

        case SysmanResContainer::accel_asset_t::COMPUTE:
            str = "SysmanResContainer::accel_asset_t::COMPUTE";
            break;

        case SysmanResContainer::accel_asset_t::SYSTOLIC:
            str = "SysmanResContainer::accel_asset_t::SYSTOLIC";
            break;

        case SysmanResContainer::accel_asset_t::RAYTRACING:
            str = "SysmanResContainer::accel_asset_t::RAYTRACING";
            break;

        case SysmanResContainer::accel_asset_t::LOCAL_MEM:
            str = "SysmanResContainer::accel_asset_t::LOCAL_MEM";
            break;

        case SysmanResContainer::accel_asset_t::LINK:
            str = "SysmanResContainer::accel_asset_t::LINK";
            break;

        case SysmanResContainer::accel_asset_t::MAX_TYPES:
            str = "SysmanResContainer::accel_asset_t::MAX_TYPES";
            break;

        default:
            str = "SysmanResContainer::accel_asset_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::board_properties_t to std::string
    std::string to_string( const SysmanResContainer::board_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResContainer::board_properties_t::BOARD_PROP_SERIAL_NUMBER:
            str = "SysmanResContainer::board_properties_t::BOARD_PROP_SERIAL_NUMBER";
            break;

        case SysmanResContainer::board_properties_t::BOARD_PROP_BOARD_NUMBER:
            str = "SysmanResContainer::board_properties_t::BOARD_PROP_BOARD_NUMBER";
            break;

        default:
            str = "SysmanResContainer::board_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::pci_bar_type_t to std::string
    std::string to_string( const SysmanResContainer::pci_bar_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResContainer::pci_bar_type_t::CONFIG:
            str = "SysmanResContainer::pci_bar_type_t::CONFIG";
            break;

        case SysmanResContainer::pci_bar_type_t::MMIO:
            str = "SysmanResContainer::pci_bar_type_t::MMIO";
            break;

        case SysmanResContainer::pci_bar_type_t::VRAM:
            str = "SysmanResContainer::pci_bar_type_t::VRAM";
            break;

        case SysmanResContainer::pci_bar_type_t::ROM:
            str = "SysmanResContainer::pci_bar_type_t::ROM";
            break;

        case SysmanResContainer::pci_bar_type_t::VGA_IO:
            str = "SysmanResContainer::pci_bar_type_t::VGA_IO";
            break;

        case SysmanResContainer::pci_bar_type_t::VGA_MEM:
            str = "SysmanResContainer::pci_bar_type_t::VGA_MEM";
            break;

        case SysmanResContainer::pci_bar_type_t::INDIRECT_IO:
            str = "SysmanResContainer::pci_bar_type_t::INDIRECT_IO";
            break;

        case SysmanResContainer::pci_bar_type_t::INDIRECT_MEM:
            str = "SysmanResContainer::pci_bar_type_t::INDIRECT_MEM";
            break;

        case SysmanResContainer::pci_bar_type_t::OTHER:
            str = "SysmanResContainer::pci_bar_type_t::OTHER";
            break;

        default:
            str = "SysmanResContainer::pci_bar_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::hw_error_type_t to std::string
    std::string to_string( const SysmanResContainer::hw_error_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResContainer::hw_error_type_t::HW_ERROR_MESSAGING:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_MESSAGING";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_SGUNIT:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_SGUNIT";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_GSC:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_GSC";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_DISPLAY:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_DISPLAY";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_EU_GRF:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_EU_GRF";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_EU_INSTCACHE:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_EU_INSTCACHE";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_SLM:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_SLM";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_SAMPLER:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_SAMPLER";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_GUC:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_GUC";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_L3:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_L3";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_ALL:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_GPU_ALL";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_PCI:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_PCI";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_PCI_ROUTING:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_PCI_ROUTING";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_SOC:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_SOC";
            break;

        case SysmanResContainer::hw_error_type_t::HW_ERROR_COUNT:
            str = "SysmanResContainer::hw_error_type_t::HW_ERROR_COUNT";
            break;

        default:
            str = "SysmanResContainer::hw_error_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_properties_t to std::string
    std::string to_string( const SysmanResContainer::device_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResContainer::device_properties_t::DEVICE_PROP_BRAND:
            str = "SysmanResContainer::device_properties_t::DEVICE_PROP_BRAND";
            break;

        case SysmanResContainer::device_properties_t::DEVICE_PROP_MODEL:
            str = "SysmanResContainer::device_properties_t::DEVICE_PROP_MODEL";
            break;

        case SysmanResContainer::device_properties_t::DEVICE_PROP_DEVICEID:
            str = "SysmanResContainer::device_properties_t::DEVICE_PROP_DEVICEID";
            break;

        case SysmanResContainer::device_properties_t::DEVICE_PROP_VENDOR_NAME:
            str = "SysmanResContainer::device_properties_t::DEVICE_PROP_VENDOR_NAME";
            break;

        case SysmanResContainer::device_properties_t::DEVICE_PROP_ACCEL_ASSETS:
            str = "SysmanResContainer::device_properties_t::DEVICE_PROP_ACCEL_ASSETS";
            break;

        case SysmanResContainer::device_properties_t::DEVICE_PROP_DRIVER_VERSION:
            str = "SysmanResContainer::device_properties_t::DEVICE_PROP_DRIVER_VERSION";
            break;

        case SysmanResContainer::device_properties_t::DEVICE_PROP_BARS:
            str = "SysmanResContainer::device_properties_t::DEVICE_PROP_BARS";
            break;

        case SysmanResContainer::device_properties_t::DEVICE_PROP_ERROR_STATS:
            str = "SysmanResContainer::device_properties_t::DEVICE_PROP_ERROR_STATS";
            break;

        case SysmanResContainer::device_properties_t::DEVICE_PROP_COLD_SHUTDOWN:
            str = "SysmanResContainer::device_properties_t::DEVICE_PROP_COLD_SHUTDOWN";
            break;

        case SysmanResContainer::device_properties_t::DEVICE_PROP_COLD_RESET:
            str = "SysmanResContainer::device_properties_t::DEVICE_PROP_COLD_RESET";
            break;

        default:
            str = "SysmanResContainer::device_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::board_prop_serial_number_t to std::string
    std::string to_string( const SysmanResContainer::board_prop_serial_number_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::board_prop_serial_number_t::str : ";
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
    /// @brief Converts SysmanResContainer::board_prop_board_number_t to std::string
    std::string to_string( const SysmanResContainer::board_prop_board_number_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::board_prop_board_number_t::str : ";
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
    /// @brief Converts SysmanResContainer::pci_bar_info_t to std::string
    std::string to_string( const SysmanResContainer::pci_bar_info_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::pci_bar_info_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanResContainer::pci_bar_info_t::base : ";
        str += std::to_string(val.base);
        str += "\n";
        
        str += "SysmanResContainer::pci_bar_info_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_brand_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_brand_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::device_prop_brand_t::str : ";
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
    /// @brief Converts SysmanResContainer::device_prop_model_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_model_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::device_prop_model_t::str : ";
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
    /// @brief Converts SysmanResContainer::device_prop_deviceid_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_deviceid_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::device_prop_deviceid_t::str : ";
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
    /// @brief Converts SysmanResContainer::device_prop_vendor_name_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_vendor_name_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::device_prop_vendor_name_t::str : ";
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
    /// @brief Converts SysmanResContainer::device_prop_accel_asset_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_accel_asset_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::device_prop_accel_asset_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanResContainer::device_prop_accel_asset_t::numBlocks : ";
        str += std::to_string(val.numBlocks);
        str += "\n";
        
        str += "SysmanResContainer::device_prop_accel_asset_t::numEngines : ";
        str += std::to_string(val.numEngines);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_accel_assets_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_accel_assets_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::device_prop_accel_assets_t::assetBitfield : ";
        str += std::to_string(val.assetBitfield);
        str += "\n";
        
        str += "SysmanResContainer::device_prop_accel_assets_t::assetInfo : ";
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
    /// @brief Converts SysmanResContainer::device_prop_driver_version_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_driver_version_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::device_prop_driver_version_t::str : ";
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
    /// @brief Converts SysmanResContainer::device_prop_bars_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_bars_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::device_prop_bars_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "SysmanResContainer::device_prop_bars_t::pBars : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pBars);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_error_stats_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_error_stats_t val )
    {
        std::string str;
        
        str += "SysmanResContainer::device_prop_error_stats_t::TotalNonFatalError : ";
        str += std::to_string(val.TotalNonFatalError);
        str += "\n";
        
        str += "SysmanResContainer::device_prop_error_stats_t::errors : ";
        {
            std::string tmp;
            for( auto& entry : val.errors )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "SysmanResContainer::device_prop_error_stats_t::NumResets : ";
        str += std::to_string(val.NumResets);
        str += "\n";
        
        str += "SysmanResContainer::device_prop_error_stats_t::NumHangs : ";
        str += std::to_string(val.NumHangs);
        str += "\n";
        
        str += "SysmanResContainer::device_prop_error_stats_t::NumColdResets : ";
        str += std::to_string(val.NumColdResets);
        str += "\n";

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
    /// @brief Converts SysmanResource::pwr_sustained_limit_version_t to std::string
    std::string to_string( const SysmanResource::pwr_sustained_limit_version_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanResource::pwr_sustained_limit_version_t::CURRENT:
            str = "SysmanResource::pwr_sustained_limit_version_t::CURRENT";
            break;

        default:
            str = "SysmanResource::pwr_sustained_limit_version_t::?";
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

        case SysmanResource::pwrwell_properties_t::PWRWELL_PROP_SLEEP_COUNTER:
            str = "SysmanResource::pwrwell_properties_t::PWRWELL_PROP_SLEEP_COUNTER";
            break;

        case SysmanResource::pwrwell_properties_t::PWRWELL_PROP_IDLE_COUNTER:
            str = "SysmanResource::pwrwell_properties_t::PWRWELL_PROP_IDLE_COUNTER";
            break;

        case SysmanResource::pwrwell_properties_t::PWRWELL_PROP_ACTIVE_COUNTER:
            str = "SysmanResource::pwrwell_properties_t::PWRWELL_PROP_ACTIVE_COUNTER";
            break;

        case SysmanResource::pwrwell_properties_t::PWRWELL_PROP_WAKE_COUNTER:
            str = "SysmanResource::pwrwell_properties_t::PWRWELL_PROP_WAKE_COUNTER";
            break;

        case SysmanResource::pwrwell_properties_t::PWRWELL_PROP_EXEC_COUNTER:
            str = "SysmanResource::pwrwell_properties_t::PWRWELL_PROP_EXEC_COUNTER";
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

        case SysmanResource::accel_properties_t::ACCEL_PROP_ACTIVE_COUNTER:
            str = "SysmanResource::accel_properties_t::ACCEL_PROP_ACTIVE_COUNTER";
            break;

        case SysmanResource::accel_properties_t::ACCEL_PROP_IDLE_COUNTER:
            str = "SysmanResource::accel_properties_t::ACCEL_PROP_IDLE_COUNTER";
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

        case SysmanResource::mem_properties_t::MEM_PROP_ECC_ENABLED:
            str = "SysmanResource::mem_properties_t::MEM_PROP_ECC_ENABLED";
            break;

        case SysmanResource::mem_properties_t::MEM_PROP_ECC_COUNTERS:
            str = "SysmanResource::mem_properties_t::MEM_PROP_ECC_COUNTERS";
            break;

        case SysmanResource::mem_properties_t::MEM_PROP_ECC_CLEAR:
            str = "SysmanResource::mem_properties_t::MEM_PROP_ECC_CLEAR";
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

        case SysmanResource::link_properties_t::LINK_PROP_REPLAY_COUNTER:
            str = "SysmanResource::link_properties_t::LINK_PROP_REPLAY_COUNTER";
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
    /// @brief Converts SysmanResource::pwr_prop_sustained_limit_t to std::string
    std::string to_string( const SysmanResource::pwr_prop_sustained_limit_t val )
    {
        std::string str;
        
        str += "SysmanResource::pwr_prop_sustained_limit_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
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
    /// @brief Converts SysmanResource::mem_prop_ecc_counters_t to std::string
    std::string to_string( const SysmanResource::mem_prop_ecc_counters_t val )
    {
        std::string str;
        
        str += "SysmanResource::mem_prop_ecc_counters_t::parityErrors : ";
        str += std::to_string(val.parityErrors);
        str += "\n";
        
        str += "SysmanResource::mem_prop_ecc_counters_t::correctableErrors : ";
        str += std::to_string(val.correctableErrors);
        str += "\n";
        
        str += "SysmanResource::mem_prop_ecc_counters_t::uncorrectableErrors : ";
        str += std::to_string(val.uncorrectableErrors);
        str += "\n";
        
        str += "SysmanResource::mem_prop_ecc_counters_t::retiredPages : ";
        str += std::to_string(val.retiredPages);
        str += "\n";
        
        str += "SysmanResource::mem_prop_ecc_counters_t::badPages : ";
        str += std::to_string(val.badPages);
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

} // namespace xet
