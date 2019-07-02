/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_sysman.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for System Resource Management (SMI)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/sysman.yml
 * @endcond
 *
 */
#ifndef _XET_SYSMAN_H
#define _XET_SYSMAN_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief SMI initialization flags (bitfield)
typedef enum _xet_sysman_init_flags_t
{
    XET_SYSMAN_INIT_FLAGS_NONE = 0,                 ///< default initialization
    XET_SYSMAN_INIT_FLAGS_WRITE = XE_BIT( 0 ),      ///< request write/control access to resources

} xet_sysman_init_flags_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource container types
typedef enum _xet_res_container_type_t
{
    XET_RES_CONTAINER_TYPE_UNIT = 0,                ///< Unit resource container
    XET_RES_CONTAINER_TYPE_BOARD,                   ///< Board resource container
    XET_RES_CONTAINER_TYPE_DEVICE,                  ///< Device resource container
    XET_RES_CONTAINER_TYPE_SUBDEVICE,               ///< Sub-device resource container
    XET_RES_CONTAINER_TYPE_MAX_TYPES,               ///< The number of resource container types

} xet_res_container_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource types
typedef enum _xet_resource_type_t
{
    XET_RESOURCE_TYPE_PSU = 0,                      ///< PSU resource
    XET_RESOURCE_TYPE_TEMP,                         ///< Temperature sensor resource
    XET_RESOURCE_TYPE_FAN,                          ///< Fan resource
    XET_RESOURCE_TYPE_LED,                          ///< LED resource
    XET_RESOURCE_TYPE_FIRMWARE,                     ///< Firmware resource
    XET_RESOURCE_TYPE_PWR,                          ///< Power domain resource
    XET_RESOURCE_TYPE_FREQ,                         ///< Frequency domain resource
    XET_RESOURCE_TYPE_PWRWELL,                      ///< Power-well resource
    XET_RESOURCE_TYPE_ACCEL,                        ///< Accelerator asset resource
    XET_RESOURCE_TYPE_MEMORY,                       ///< Memory resource
    XET_RESOURCE_TYPE_LINK,                         ///< Link resource
    XET_RESOURCE_TYPE_MAX_TYPES,                    ///< The number of resource types

} xet_resource_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Accelerator assets
typedef enum _xet_accel_asset_t
{
    XET_ACCEL_ASSET_PCIE_CONTROLLER = 0,            ///< PCIe controller
    XET_ACCEL_ASSET_IDI_MEM_CONTROLLER,             ///< IDI memory controller
    XET_ACCEL_ASSET_HBM_MEM_CONTROLLER,             ///< HBM memory controller
    XET_ACCEL_ASSET_L3_CACHE,                       ///< L3 cache
    XET_ACCEL_ASSET_BLILTTER,                       ///< Blitter
    XET_ACCEL_ASSET_VIDEO_DECODER,                  ///< Video decoder
    XET_ACCEL_ASSET_VIDEO_ENCODER,                  ///< Video encoder
    XET_ACCEL_ASSET_VIDEO_PROCESSING,               ///< Video processing
    XET_ACCEL_ASSET_3D_FF,                          ///< 3D fixed-function hardware
    XET_ACCEL_ASSET_3D_RENDER,                      ///< 3D programmable shader units
    XET_ACCEL_ASSET_COMPUTE,                        ///< Compute units
    XET_ACCEL_ASSET_SYSTOLIC,                       ///< Systolic array
    XET_ACCEL_ASSET_RAYTRACING,                     ///< Raytracing hardware
    XET_ACCEL_ASSET_LOCAL_MEM,                      ///< Local memory
    XET_ACCEL_ASSET_LINK,                           ///< High speed link
    XET_ACCEL_ASSET_MAX_TYPES,                      ///< The number of accelerator asset types

} xet_accel_asset_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource container universal unique id (UUID)
typedef struct _xet_res_container_uuid_t
{
    uint8_t id[XE_MAX_UUID_SIZE];                   ///< [out] resource container universal unique id

} xet_res_container_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Generic information about a resource container
typedef struct _xet_res_container_info_t
{
    xet_res_container_uuid_t uuid;                  ///< [out] UUID for the resource container
    xet_res_container_type_t type;                  ///< [out] Type of resource container
    xe_bool_t haveParent;                           ///< [out] Indicates if this resource container has a parent container
    uint32_t numChildren;                           ///< [out] The number of child resource containers
    uint32_t numPeers;                              ///< [out] The number of resource containers connected with peer-to-peer
                                                    ///< links
    uint32_t numResourcesByType[XET_RESOURCE_TYPE_MAX_TYPES];   ///< [out] The number of resources of each type attached to this resource
                                                    ///< container (not in the child resource containers)

} xet_res_container_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource universal unique id (UUID)
typedef struct _xet_resource_uuid_t
{
    uint8_t id[XE_MAX_UUID_SIZE];                   ///< [out] resource universal unique id

} xet_resource_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Generic information about a resource
typedef struct _xet_resource_info_t
{
    xet_resource_uuid_t uuid;                       ///< [out] UUID for the resource
    xet_resource_type_t type;                       ///< [out] Type of resource
    xet_res_container_uuid_t resContainerUuid;      ///< [out] UUID for the resource container where this resouce is located

} xet_resource_info_t;

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
    );

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
    );

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
    xet_res_container_uuid_t* uuid,                 ///< [in] UUID for the resource container.
    xet_res_container_handle_t* phResContainer      ///< [out] Resource container with UUID.
    );

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define XET_STRING_PROPERTY_SIZE  32
#endif // XET_STRING_PROPERTY_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Board resource container properties
typedef enum _xet_board_properties_t
{
    XET_BOARD_PROP_SERIAL_NUMBER = 0,               ///< (ro static) The serial number of a board container
    XET_BOARD_PROP_BOARD_NUMBER,                    ///< (ro static) The board number of a board container

} xet_board_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_BOARD_PROP_SERIAL_NUMBER
typedef struct _xet_board_prop_serial_number_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_board_prop_serial_number_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_BOARD_PROP_BOARD_NUMBER
typedef struct _xet_board_prop_board_number_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_board_prop_board_number_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI bar types
typedef enum _xet_pci_bar_type_t
{
    XET_PCI_BAR_TYPE_CONFIG = 0,                    ///< PCI configuration space
    XET_PCI_BAR_TYPE_MMIO,                          ///< MMIO registers
    XET_PCI_BAR_TYPE_VRAM,                          ///< VRAM aperture
    XET_PCI_BAR_TYPE_ROM,                           ///< ROM aperture
    XET_PCI_BAR_TYPE_VGA_IO,                        ///< Legacy VGA IO ports
    XET_PCI_BAR_TYPE_VGA_MEM,                       ///< Legacy VGA memory
    XET_PCI_BAR_TYPE_INDIRECT_IO,                   ///< Indirect IO port access
    XET_PCI_BAR_TYPE_INDIRECT_MEM,                  ///< Indirect memory access
    XET_PCI_BAR_TYPE_OTHER,                         ///< Other type of PCI bar

} xet_pci_bar_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for a PCI bar
typedef struct _xet_pci_bar_info_t
{
    xet_pci_bar_type_t type;                        ///< [out] The type of bar
    uint64_t base;                                  ///< [out] Base address of the bar.
    uint64_t size;                                  ///< [out] Size of the bar.

} xet_pci_bar_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Hardware error types
typedef enum _xet_hw_error_type_t
{
    XET_HW_ERROR_MESSAGING = 0,                     ///< Error while sending messages between sub-devices
    XET_HW_ERROR_SGUNIT,                            ///< Error handling transactions between PCI config space, MMIO registers,
                                                    ///< local memory and sub-devices
    XET_HW_ERROR_GSC,                               ///< Authentication errors
    XET_HW_ERROR_DISPLAY,                           ///< Display sub-system single-bit correctable errors
    XET_HW_ERROR_GPU_EU_GRF,                        ///< Execution unit (EU) register file single-bit correctable errors
    XET_HW_ERROR_GPU_EU_INSTCACHE,                  ///< Execution unit (EU) instruction cache single-bit correctable errors
    XET_HW_ERROR_GPU_SLM,                           ///< Execution unit (EU) shared local memory single-bit correctable errors
    XET_HW_ERROR_GPU_SAMPLER,                       ///< Sampler single-bit correctable errors
    XET_HW_ERROR_GPU_GUC,                           ///< Micro-controller SRAM single-bit correctable errors
    XET_HW_ERROR_GPU_L3,                            ///< L3 single-bit correctable errors
    XET_HW_ERROR_GPU_ALL,                           ///< Total count of GPU errors
    XET_HW_ERROR_PCI,                               ///< PCIe correctable or non-fatal errors
    XET_HW_ERROR_PCI_ROUTING,                       ///< Errors routing PCIe traffic to/from sub-devices
    XET_HW_ERROR_SOC,                               ///< Errors in other parts of the device
    XET_HW_ERROR_COUNT,                             ///< Maximum number of hardware error types

} xet_hw_error_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device resource container properties
typedef enum _xet_device_properties_t
{
    XET_DEVICE_PROP_BRAND = 0,                      ///< (ro static) The brand name of the device
    XET_DEVICE_PROP_MODEL,                          ///< (ro static) The model name of the device
    XET_DEVICE_PROP_DEVICEID,                       ///< (ro static) The device ID of the device
    XET_DEVICE_PROP_VENDOR_NAME,                    ///< (ro static) The vendor name of the device
    XET_DEVICE_PROP_ACCEL_ASSETS,                   ///< (ro static) The accelerator assets available in the device
    XET_DEVICE_PROP_DRIVER_VERSION,                 ///< (ro static) The driver version associated with the device
    XET_DEVICE_PROP_BARS,                           ///< (ro static) The bars configured for the device
    XET_DEVICE_PROP_ERROR_STATS,                    ///< (ro dynamic) Error stats for the device
    XET_DEVICE_PROP_COLD_SHUTDOWN,                  ///< (wo dynamic) Cold shudown the device
    XET_DEVICE_PROP_COLD_RESET,                     ///< (wo dynamic) Cold reset the device

} xet_device_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_DEVICE_PROP_BRAND
typedef struct _xet_device_prop_brand_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_device_prop_brand_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_DEVICE_PROP_MODEL
typedef struct _xet_device_prop_model_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_device_prop_model_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_DEVICE_PROP_DEVICEID
typedef struct _xet_device_prop_deviceid_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_device_prop_deviceid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_DEVICE_PROP_VENDOR_NAME
typedef struct _xet_device_prop_vendor_name_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_device_prop_vendor_name_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data about one type of accelerator asset
typedef struct _xet_device_prop_accel_asset_t
{
    xet_accel_asset_t type;                         ///< [out] The type of asset
    uint32_t numBlocks;                             ///< [out] The number of blocks of this asset type
    uint32_t numEngines;                            ///< [out] The number of submission engines for this type of asset

} xet_device_prop_accel_asset_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_DEVICE_PROP_ACCEL_ASSETS
typedef struct _xet_device_prop_accel_assets_t
{
    uint64_t assetBitfield;                         ///< [out] A bitfield of assets available in the resource container
    xet_device_prop_accel_asset_t assetInfo[XET_ACCEL_ASSET_MAX_TYPES]; ///< [out] Information about each asset.

} xet_device_prop_accel_assets_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_DEVICE_PROP_DRIVER_VERSION
typedef struct _xet_device_prop_driver_version_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_device_prop_driver_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_DEVICE_PROP_BARS
typedef struct _xet_device_prop_bars_t
{
    uint32_t num;                                   ///< [out] The number of bars
    const xet_pci_bar_info_t* pBars;                ///< [out][range(0, num-1)] Information about each bar.

} xet_device_prop_bars_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_DEVICE_PROP_ERROR_STATS
typedef struct _xet_device_prop_error_stats_t
{
    uint32_t TotalNonFatalError;                    ///< [out] The total number of non-fatal hardware errors that have occurred
                                                    ///< since the driver booted
    uint32_t errors[XET_HW_ERROR_COUNT];            ///< [out] Error counters for each type (::xet_hw_error_type_t) of hardware
                                                    ///< error.
    uint32_t NumResets;                             ///< [out] The total number of hardware resets that have been performed
                                                    ///< since the driver booted
    uint32_t NumHangs;                              ///< [out] The total number of hardware hangs that have occurred since the
                                                    ///< driver booted
    uint32_t NumColdResets;                         ///< [out] The total number of cold resets that have been performanced
                                                    ///< since the driver booted

} xet_device_prop_error_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_DEVICE_PROP_COLD_SHUTDOWN
typedef xe_bool_t xet_device_prop_driver_cold_shutdown_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_DEVICE_PROP_COLD_RESET
typedef xe_bool_t xet_device_prop_driver_cold_reset_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief PSU voltage status
typedef enum _xet_psu_voltage_status_t
{
    XET_PSU_VOLTAGE_STATUS_NORMAL = 0,              ///< No unusual voltages have been detected
    XET_PSU_VOLTAGE_STATUS_OVER,                    ///< Over-voltage has occurred
    XET_PSU_VOLTAGE_STATUS_UNDER,                   ///< Under-voltage has occurred

} xet_psu_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PSU resource properties
typedef enum _xet_psu_properties_t
{
    XET_PSU_PROP_AMP_LIMIT = 0,                     ///< (ro static) The maximum electrical current in Amperes that can be
                                                    ///< drawn
    XET_PSU_PROP_VOLTAGE_STATUS,                    ///< (ro dynamic) Indicates if under or over voltage has occurred (one of
                                                    ///< ::xet_psu_voltage_status_t)
    XET_PSU_PROP_FAN_FAILURE,                       ///< (ro dynamic) Indicates if the fan has failed
    XET_PSU_PROP_TEMPERATURE,                       ///< (ro dynamic) Read the current heatsink temperature in degrees celcius
    XET_PSU_PROP_AMPS,                              ///< (ro dynamic) Read the amps being drawn in Amperes

} xet_psu_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PSU_PROP_AMP_LIMIT
typedef uint32_t xet_psu_prop_amp_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PSU_PROP_VOLTAGE_STATUS
typedef struct _xet_psu_prop_voltage_status_t
{
    xet_psu_voltage_status_t status;                ///< [out] The current PSU voltage status)

} xet_psu_prop_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PSU_PROP_FAN_FAILURE
typedef xe_bool_t xet_psu_prop_fan_failure_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PSU_PROP_TEMPERATURE
typedef uint32_t xet_psu_prop_temperature_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PSU_PROP_AMPS
typedef uint32_t xet_psu_prop_amps_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensor resource properties
typedef enum _xet_temp_properties_t
{
    XET_TEMP_PROP_TEMPERATURE = 0,                  ///< (ro dynamic) The current temperature of the sensor in degrees celcius

} xet_temp_properties_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan resource speed mode
typedef enum _xet_fan_speed_mode_t
{
    XET_FAN_SPEED_MODE_FIXED = 0,                   ///< The fan speed is currently set to a fixed value
    XET_FAN_SPEED_MODE_TABLE,                       ///< The fan speed is currently controlled dynamically by hardware based on
                                                    ///< a temp/speed table

} xet_fan_speed_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan speed units
typedef enum _xet_fan_speed_units_t
{
    XET_FAN_SPEED_UNITS_RPM = 0,                    ///< The fan speed is in units of revolutions per minute (rpm)
    XET_FAN_SPEED_UNITS_PERCENT,                    ///< The fan speed is a percentage of the maximum speed of the fan

} xet_fan_speed_units_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan temperature/speed pair
typedef struct _xet_fan_temp_speed_t
{
    uint32_t temperature;                           ///< [in,out] Temperature in degrees celcius
    uint32_t speed;                                 ///< [in,out] The speed of the fan
    xet_fan_speed_units_t units;                    ///< [in,out] The units of the member speed

} xet_fan_temp_speed_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_FAN_TEMP_SPEED_PAIR_COUNT
/// @brief Maximum number of fan temperature/speed pairs in the fan speed table.
#define XET_FAN_TEMP_SPEED_PAIR_COUNT  32
#endif // XET_FAN_TEMP_SPEED_PAIR_COUNT

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan resource properties
typedef enum _xet_fan_properties_t
{
    XET_FAN_PROP_MAX_RPM = 0,                       ///< (ro static) The maximum RPM of the fan
    XET_FAN_PROP_MAX_TABLE_SIZE,                    ///< (ro static) The maximum number of points in the fan temp/speed table
    XET_FAN_PROP_SPEED_RPM,                         ///< (ro dynamic) The current fan speed in units of revolutions per minute
                                                    ///< (rpm)
    XET_FAN_PROP_SPEED_PERCENT,                     ///< (ro dynamic) The current fan speed as a percentage of the maximum
                                                    ///< speed of that fan
    XET_FAN_PROP_MODE,                              ///< (ro dynamic) The current fan speed mode (one of
                                                    ///< ::xet_fan_speed_mode_t)
    XET_FAN_PROP_FIXED_SPEED,                       ///< (rw dynamic) Read/write the fixed speed setting for the fan
    XET_FAN_PROP_SPEED_TABLE,                       ///< (rw dynamic) Read/write the fan speed table

} xet_fan_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_MAX_RPM
typedef uint32_t xet_fan_prop_max_rpm_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_MAX_TABLE_SIZE
typedef uint32_t xet_fan_prop_max_table_size_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_SPEED_RPM
typedef uint32_t xet_fan_prop_speed_rpm_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_SPEED_PERCENT
typedef uint32_t xet_fan_prop_speed_percent_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_MODE
typedef struct _xet_fan_prop_mode_t
{
    xet_fan_speed_mode_t mode;                      ///< [in,out] The current fan speed mode (one of ::xet_fan_speed_mode_t)

} xet_fan_prop_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_FIXED_SPEED
typedef struct _xet_fan_prop_fixed_speed_t
{
    uint32_t speed;                                 ///< [in,out] The speed of the fan
    xet_fan_speed_units_t units;                    ///< [in,out] The units of the member speed

} xet_fan_prop_fixed_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_SPEED_TABLE
typedef struct _xet_fan_prop_speed_table_t
{
    uint32_t* pCount;                               ///< [in,out] The number of temp/speed pairs.
                                                    ///< When reading the current fan speed table, this will be set to the
                                                    ///< number of points returned.
                                                    ///< When setting the fan speed table, this specifies the number of valid
                                                    ///< points in the table.
    xet_fan_temp_speed_t points[XET_FAN_TEMP_SPEED_PAIR_COUNT]; ///< [in,out][range(0, *pCount)] Array of temperature/fan speed pairs

} xet_fan_prop_speed_table_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief LED resource properties
typedef enum _xet_led_properties_t
{
    XET_LED_PROP_RGB_CAP = 0,                       ///< (ro static) Indicates if the LED is RGB capable
    XET_LED_PROP_STATE,                             ///< (rw dynaic) The LED state (on/off and color)

} xet_led_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LED_PROP_RGB_CAP
typedef xe_bool_t xet_led_prop_rgb_cap_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LED_PROP_STATE
typedef struct _xet_led_prop_state_t
{
    xe_bool_t isOn;                                 ///< [in,out] Indicates if the LED is on or off
    uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
    uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
    uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

} xet_led_prop_state_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Firmware resource properties
typedef enum _xet_firmware_properties_t
{
    XET_FIRMWARE_PROP_NAME = 0,                     ///< (ro static) Name encoded in the loaded firmware image
    XET_FIRMWARE_PROP_VERSION,                      ///< (ro static) The version of the loaded firmware image
    XET_FIRMWARE_PROP_CHECK,                        ///< (ro dynamic) Verify the checksum of the loaded firmware image
    XET_FIRMWARE_PROP_FLASH,                        ///< (wo dynamically) Flash a new firmware image

} xet_firmware_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_FIRMWARE_PROP_NAME
typedef struct _xet_firmware_prop_name_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_firmware_prop_name_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_FIRMWARE_PROP_VERSION
typedef struct _xet_firmware_prop_version_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_firmware_prop_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FIRMWARE_PROP_CHECK
typedef struct _xet_firmware_prop_check_t
{
    uint32_t checksum;                              ///< [out] The calculated checksum of the loaded firmware image

} xet_firmware_prop_check_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FIRMWARE_PROP_FLASH
typedef struct _xet_firmware_prop_flash_t
{
    void* pImage;                                   ///< [in] Pointer to the image to be flashed
    uint32_t size;                                  ///< [in] Size in bytes of the image pointed to by pImage

} xet_firmware_prop_flash_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Power domain resource properties
typedef enum _xet_pwr_properties_t
{
    XET_PWR_PROP_ACCEL_ASSETS = 0,                  ///< (ro static) List of accelerator assets that contribute to this power
                                                    ///< domain
    XET_PWR_PROP_MAX_LIMIT,                         ///< (ro static) The maximum power limit that can be requested
    XET_PWR_PROP_ENERGY_COUNTER,                    ///< (ro dynamic) The value of the monotonic energy counter
    XET_PWR_PROP_SUSTAINED_LIMIT,                   ///< (rw dynamic) The sustained power limit
    XET_PWR_PROP_BURST_LIMIT,                       ///< (rw dynamic) The burst power limit
    XET_PWR_PROP_PEAK_LIMIT,                        ///< (rw dynamic) The peak power limit

} xet_pwr_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWR_PROP_ACCEL_ASSETS.
/// 
/// @details
///     - Bitfield of (1<<::xet_accel_asset_t)
typedef uint64_t xet_pwr_prop_accel_assets_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWR_PROP_MAX_LIMIT
/// 
/// @details
///     - Units are in millwatts
typedef uint32_t xet_pwr_prop_max_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWR_PROP_ENERGY_COUNTER
/// 
/// @details
///     - Units are in millijoules
typedef uint64_t xet_pwr_prop_energy_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xet_pwr_prop_sustained_limit_t
typedef enum _xet_pwr_sustained_limit_version_t
{
    XET_PWR_SUSTAINED_LIMIT_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

} xet_pwr_sustained_limit_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWR_PROP_SUSTAINED_LIMIT
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency if
///       the power averaged over a window (typically seconds) exceeds this
///       limit.
typedef struct _xet_pwr_prop_sustained_limit_t
{
    xet_pwr_sustained_limit_version_t version;      ///< [in] ::XET_PWR_SUSTAINED_LIMIT_VERSION_CURRENT
    xe_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts
    uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

} xet_pwr_prop_sustained_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWR_PROP_BURST_LIMIT
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency of
///       the device if the power averaged over a few milliseconds exceeds a
///       limit known as PL2. Typically PL2 > PL1 so that it permits the
///       frequency to burst higher for short periods than would be otherwise
///       permitted by PL1.
typedef struct _xet_pwr_prop_burst_limit_t
{
    xe_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts

} xet_pwr_prop_burst_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWR_PROP_PEAK_LIMIT
/// 
/// @details
///     - The power controller (Punit) will preemptively throttle the operating
///       frequency of the device when the instantaneous power exceeds this
///       limit. The limit is known as PL4. It expresses the maximum power that
///       can be drawn from the power supply.
///     - If this power limit is removed or set too high, the power supply will
///       generate an interrupt when it detects an overcurrent condition and the
///       power controller will throttle the device frequencies down to min. It
///       is thus better to tune the PL4 value in order to avoid such
///       excursions.
typedef struct _xet_pwr_prop_peak_limit_t
{
    uint32_t power;                                 ///< [in,out] power limit in milliwatts

} xet_pwr_prop_peak_limit_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency domain types
typedef enum _xet_freq_domain_type_t
{
    XET_FREQ_DOMAIN_TYPE_INDEPENDENT = 0,           ///< The frequency of this domain can be managed independently of other
                                                    ///< domains
    XET_FREQ_DOMAIN_TYPE_DEPENDENT,                 ///< The frequency of this domain is dependent on another domain through a
                                                    ///< clock divider

} xet_freq_domain_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief DVFS mode
typedef enum _xet_dvfs_mode_t
{
    XET_DVFS_MODE_MIN = 0,                          ///< Fixed minimum frequency will be requested unless specific applications
                                                    ///< request otherwise.
    XET_DVFS_MODE_EFFICIENT,                        ///< Dynamic frequency management that prefers power saving over
                                                    ///< performance.
    XET_DVFS_MODE_STABLE,                           ///< Fixed frequency that should not be throttled under normal operating
                                                    ///< conditions.
    XET_DVFS_MODE_DEFAULT,                          ///< Dynamic frequency management that balances power and performance.
    XET_DVFS_MODE_AGGRESSIVE,                       ///< Dynamic frequency management that trades more power for better
                                                    ///< performance.
    XET_DVFS_MODE_MAX,                              ///< Fixed maximum frequency.

} xet_dvfs_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency throttle reasons
typedef enum _xet_freq_throttle_reasons_t
{
    XET_FREQ_THROTTLE_REASONS_NONE = 0,             ///< frequency not throttled
    XET_FREQ_THROTTLE_REASONS_AVE_PWR_CAP = XE_BIT( 0 ),///< frequency throttled due to average power excursion (PL1)
    XET_FREQ_THROTTLE_REASONS_BURST_PWR_CAP = XE_BIT( 1 ),  ///< frequency throttled due to burst power excursion (PL2)
    XET_FREQ_THROTTLE_REASONS_CURRENT_LIMIT = XE_BIT( 2 ),  ///< frequency throttled due to current excursion (PL4)
    XET_FREQ_THROTTLE_REASONS_THERMAL_LIMIT = XE_BIT( 3 ),  ///< frequency throttled due to thermal excursion (T > TjMax)
    XET_FREQ_THROTTLE_REASONS_PSU_ALERT = XE_BIT( 4 ),  ///< frequency throttled due to power supply assertion
    XET_FREQ_THROTTLE_REASONS_SW_RANGE = XE_BIT( 5 ),   ///< frequency throttled due to software supplied frequency range
    XET_FREQ_THROTTLE_REASONS_HW_RANGE = XE_BIT( 6 ),   ///< frequency throttled due to a sub block that has a lower frequency
                                                    ///< range when it receives clocks

} xet_freq_throttle_reasons_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency divider element
/// 
/// @details
///     - The frequency of a domain of type ::XET_FREQ_DOMAIN_TYPE_DEPENDENT is
///       obtained by the formula:
///     - freq = source domain freq * numerator / denominator
typedef struct _xet_freq_divider_t
{
    uint16_t numerator;                             ///< [in,out] numerator of the ratio
    uint16_t denominator;                           ///< [in,out] denominator of the ratio

} xet_freq_divider_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency domain resource properties
typedef enum _xet_freq_properties_t
{
    XET_FREQ_PROP_ACCEL_ASSETS = 0,                 ///< (ro static) List of accelerator assets that are connected to this
                                                    ///< power domain
    XET_FREQ_PROP_DOMAIN_TYPE,                      ///< (ro static) The type of frequency domain (one of
                                                    ///< ::xet_freq_domain_type_t)
    XET_FREQ_PROP_AVAIL_CLOCKS,                     ///< (ro static) Available frequency clocks that this domain can run at.
    XET_FREQ_PROP_AVAIL_DIVIDERS,                   ///< (ro static) Available dividers that this domain can run with.
    XET_FREQ_PROP_SRC_FREQ,                         ///< (ro static) Get the UUID of the source frequency domain resource if
                                                    ///< the type is dependent.
    XET_FREQ_PROP_DVFS_MODE,                        ///< (rw dynamic) The operating mode of dynamic frequency management for
                                                    ///< this domain (one of ::xet_dvfs_mode_t).
    XET_FREQ_PROP_FREQ_RANGE,                       ///< (rw dynamic) The frequencies between which dynamic frequency
                                                    ///< management operates.
    XET_FREQ_PROP_FREQ_TDP,                         ///< (ro dynamic) The maximum frequency supported under the current TDP
                                                    ///< conditions
    XET_FREQ_PROP_FREQ_EFFICIENT,                   ///< (ro dynamic) The efficient minimum frequency
    XET_FREQ_PROP_FREQ_REQUEST,                     ///< (ro dynamic) The current frequency request.
    XET_FREQ_PROP_FREQ_RESOLVED,                    ///< (ro dynamic) The resolved frequency.
    XET_FREQ_PROP_FREQ_DIVIDER,                     ///< (rw dynamic) The current frequency divider for dependent frequency
                                                    ///< domains.
    XET_FREQ_PROP_THROTTLE_REASONS,                 ///< (ro dynamic) The reasons that the frequency is being limited by the
                                                    ///< PCU.
    XET_FREQ_PROP_THROTTLE_TIME,                    ///< (ro dynamic) The total time that the frequency has been limited by the
                                                    ///< PCU.

} xet_freq_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_ACCEL_ASSETS
/// 
/// @details
///     - Bitfield of (1<<::xet_accel_asset_t)
typedef uint64_t xet_freq_prop_accel_assets_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_DOMAIN_TYPE
typedef struct _xet_freq_prop_domain_type_t
{
    xet_freq_domain_type_t type;                    ///< [out] The type of frequency domain

} xet_freq_prop_domain_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_AVAIL_CLOCKS
/// 
/// @details
///     - The list is ordered from the smallest frequency to the largest
///       frequency.
typedef struct _xet_freq_prop_avail_clocks_t
{
    uint32_t num;                                   ///< [out] The number of clocks
    const uint32_t* pClocks;                        ///< [out] Array of clock frequencies in MHz ordered from smallest to
                                                    ///< largest.

} xet_freq_prop_avail_clocks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_AVAIL_DIVIDERS
/// 
/// @details
///     - The list is ordered from the smallest ratio to the largest ratio.
typedef struct _xet_freq_prop_avail_dividers_t
{
    uint32_t num;                                   ///< [out] The number of dividers
    const xet_freq_divider_t* pDividers;            ///< [out] Array of numerator/denominator for each divider

} xet_freq_prop_avail_dividers_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_SRC_FREQ
typedef struct _xet_freq_prop_src_freq_t
{
    xet_resource_uuid_t uuid;                       ///< [out] The resource UUID of the source frequency domain

} xet_freq_prop_src_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_DVFS_MODE
typedef struct _xet_freq_prop_dvfs_mode_t
{
    xet_dvfs_mode_t mode;                           ///< [in,out] The DVFS operating mode

} xet_freq_prop_dvfs_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_RANGE
typedef struct _xet_freq_prop_freq_range_t
{
    uint32_t min;                                   ///< [in,out] Minimum frequency in MHz
    uint16_t max;                                   ///< [in,out] Maximum frequency in MHz

} xet_freq_prop_freq_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_TDP
/// 
/// @details
///     - In units of MHz
typedef uint32_t xet_freq_prop_freq_tdp_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_EFFICIENT
/// 
/// @details
///     - In units of MHz
typedef uint32_t xet_freq_prop_freq_efficient_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_REQUEST
/// 
/// @details
///     - In units of MHz
typedef uint32_t xet_freq_prop_freq_request_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_RESOLVED
/// 
/// @details
///     - In units of MHz
typedef uint32_t xet_freq_prop_freq_resolved_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_DIVIDER
typedef struct _xet_freq_prop_freq_divider_t
{
    xet_freq_divider_t divider;                     ///< [in,out] The frequency divider

} xet_freq_prop_freq_divider_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_THROTTLE_REASONS
/// 
/// @details
///     - Bitfield of ::xet_freq_throttle_reasons_t
typedef uint32_t xet_freq_prop_throttle_reasons_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_THROTTLE_TIME
/// 
/// @details
///     - In units of microseconds
typedef uint32_t xet_freq_prop_throttle_time_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Power-well domain promotion modes
typedef enum _xet_pwrwell_promo_mode_t
{
    XET_PWRWELL_PROMO_MODE_IMMEDIATE = 0,           ///< The power-well will shutdown immediately when all contained units are
                                                    ///< idle.
    XET_PWRWELL_PROMO_MODE_EFFICIENT,               ///< Favor energy savings over performance. The power-well is more likely
                                                    ///< to shutdown when all contained units are idle, even if this will cause
                                                    ///< some performance degredation.
    XET_PWRWELL_PROMO_MODE_DEFAULT,                 ///< Best compromise between performance and energy savings.
    XET_PWRWELL_PROMO_MODE_PERFORMANCE,             ///< Favor performance over energy savings. The power-well is more likely
                                                    ///< to stay on when all contained units are idle since it has dedicated
                                                    ///< that more work will be executing shortly.
    XET_PWRWELL_PROMO_MODE_NEVER,                   ///< The power-well will never shutdown. This can improve performance but
                                                    ///< uses more energy.

} xet_pwrwell_promo_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Power-well domain resource properties
typedef enum _xet_pwrwell_properties_t
{
    XET_PWRWELL_PROP_ACCEL_ASSETS = 0,              ///< (ro static) List of accelerator assets that are connected to this
                                                    ///< power-well domain
    XET_PWRWELL_PROP_PROMO_CAP,                     ///< (ro static) Find out if the power-well domain has a programmable
                                                    ///< promotion setting
    XET_PWRWELL_PROP_PROMO_MODE,                    ///< (rw dynamic) The current promotion mode
    XET_PWRWELL_PROP_SLEEP_COUNTER,                 ///< (ro dynamic) The monotonic counter for the amount of time the
                                                    ///< power-well is off
    XET_PWRWELL_PROP_IDLE_COUNTER,                  ///< (ro dynamic) The monotonic counter for the amount of time the
                                                    ///< power-well is on but not executing any accelerator workloads
    XET_PWRWELL_PROP_ACTIVE_COUNTER,                ///< (ro dynamic) The monotonic counter for the amount of time the
                                                    ///< power-well is on and executing accelerator workloads
    XET_PWRWELL_PROP_WAKE_COUNTER,                  ///< (ro dynamic) The monotonic counter for the number of times that the
                                                    ///< power-well has transitioned from a sleep state to a powered on state
    XET_PWRWELL_PROP_EXEC_COUNTER,                  ///< (ro dynamic) The monotonic counter for the number of times that the
                                                    ///< power-well has transitioned from a sleep or idle state to an active
                                                    ///< state

} xet_pwrwell_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_ACCEL_ASSETS
/// 
/// @details
///     - Bitfield of (1<<::xet_accel_asset_t)
typedef uint64_t xet_pwrwell_prop_accel_assets_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_PROMO_CAP
typedef xe_bool_t xet_pwrwell_prop_promo_cap_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_PROMO_MODE
typedef struct _xet_pwrwell_prop_promo_mode_t
{
    xet_pwrwell_promo_mode_t mode;                  ///< [in,out] Current promotion mode

} xet_pwrwell_prop_promo_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_SLEEP_COUNTER
/// 
/// @details
///     - Monotonic counter in units of seconds.
typedef uint32_t xet_pwrwell_prop_sleep_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_IDLE_COUNTER
/// 
/// @details
///     - Monotonic counter in units of seconds.
typedef uint32_t xet_pwrwell_prop_idle_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_ACTIVE_COUNTER
/// 
/// @details
///     - Monotonic counter in units of seconds.
typedef uint32_t xet_pwrwell_prop_active_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_WAKE_COUNTER
/// 
/// @details
///     - Monotonic counter.
typedef uint32_t xet_pwrwell_prop_wake_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_EXEC_COUNTER
/// 
/// @details
///     - Monotonic counter.
typedef uint32_t xet_pwrwell_prop_exec_counter_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Accelerator asset resource properties
typedef enum _xet_accel_properties_t
{
    XET_ACCEL_PROP_ACCEL_ASSETS = 0,                ///< (ro static) List of accelerator assets that contribute to counters in
                                                    ///< this resource
    XET_ACCEL_PROP_ACTIVE_COUNTER,                  ///< (ro dynamic) The total wall time accelerator assets in this resource
                                                    ///< are active.
    XET_ACCEL_PROP_IDLE_COUNTER,                    ///< (ro dynamic) The total wall time no accelerator assets in this
                                                    ///< resource are active

} xet_accel_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_ACCEL_PROP_ACCEL_ASSETS
/// 
/// @details
///     - Bitfield of (1<<::xet_accel_asset_t)
typedef uint64_t xet_accel_prop_accel_assets_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_ACCEL_PROP_ACTIVE_COUNTER
/// 
/// @details
///     - Monotonic counter in units of seconds.
typedef uint32_t xet_accel_prop_active_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_ACCEL_PROP_IDLE_COUNTER
/// 
/// @details
///     - Monotonic counter in units of seconds.
typedef uint32_t xet_accel_prop_idle_counter_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory resource types
typedef enum _xet_mem_type_t
{
    XET_MEM_TYPE_HBM = 0,                           ///< HBM memory
    XET_MEM_TYPE_DDR,                               ///< DDR memory
    XET_MEM_TYPE_SRAM,                              ///< SRAM memory
    XET_MEM_TYPE_L1,                                ///< L1 cache
    XET_MEM_TYPE_L3,                                ///< L3 cache
    XET_MEM_TYPE_GRF,                               ///< Execution unit register file
    XET_MEM_TYPE_SLM,                               ///< Execution unit shared local memory

} xet_mem_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory retire reasons
typedef enum _xet_mem_retire_reason_t
{
    XET_MEM_RETIRE_REASON_MULTIPLE_SINGLE_BIT_ERRORS = 0,   ///< Memory page has been retired due to multiple single bit ECC errors
    XET_MEM_RETIRE_REASON_DOUBLE_BIT_ERRORS,        ///< Memory page has been retired due to one or more double bit ECC errors

} xet_mem_retire_reason_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retired page info
typedef struct _xet_mem_retire_info_t
{
    uint64_t address;                               ///< [out] The address of the page
    xet_mem_retire_reason_t reason;                 ///< [out] The reason the page was retired

} xet_mem_retire_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory resource properties
typedef enum _xet_mem_properties_t
{
    XET_MEM_PROP_TYPE = 0,                          ///< (ro static) The type of memory covered by this resource (one of
                                                    ///< ::xet_mem_type_t)
    XET_MEM_PROP_ECC_CAP,                           ///< (ro static) Indicates if this memory resource supports ECC/RAS
                                                    ///< features
    XET_MEM_PROP_BAD_LIST,                          ///< (ro static) Get the list of pages that have been permanently marked
                                                    ///< bad
    XET_MEM_PROP_UTILIZATION,                       ///< (ro dynamic) Get current allocated/unallocated size
    XET_MEM_PROP_BANDWIDTH,                         ///< (ro dynamic) Get current read/write bandwidth counters and maximum
                                                    ///< bandwidth
    XET_MEM_PROP_ECC_ENABLED,                       ///< (rw dynamic) Determine if ECC is enabled/disabled or change this
                                                    ///< setting
    XET_MEM_PROP_ECC_COUNTERS,                      ///< (ro dynamic) ECC error counters
    XET_MEM_PROP_ECC_CLEAR,                         ///< (wo dynamic) Clear ECC error counters
    XET_MEM_PROP_ECC_POISON,                        ///< (wo dynamic) Poison the memory resource

} xet_mem_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_MEM_PROP_TYPE
typedef struct _xet_mem_prop_type_t
{
    xet_mem_type_t type;                            ///< [out] The memory type

} xet_mem_prop_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_MEM_PROP_ECC_CAP
typedef xe_bool_t xet_mem_prop_ecc_cap_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_MEM_PROP_BAD_LIST
typedef struct _xet_mem_prop_bad_list_t
{
    uint32_t* pCount;                               ///< [in,out] The number of elements in pList
                                                    ///< If pCount is zero, then the driver will update the value with the
                                                    ///< number of elements needed to store the bad list.
                                                    ///< If pCount is less than that required to store the bad list, the driver
                                                    ///< will update the value with the required number of elements and return
                                                    ///< an error.
                                                    ///< If pCount is larger than that required to store the bad list, the
                                                    ///< driver will update the value with the number of elements actually returned.
    xet_mem_retire_info_t* pList;                   ///< [in] Pointer to storage for information about each bad page.

} xet_mem_prop_bad_list_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_MEM_PROP_UTILIZATION
typedef struct _xet_mem_prop_utilization_t
{
    uint64_t allocated;                             ///< [out] The total allocated bytes
    uint64_t unallocated;                           ///< [out] The total unallocated bytes

} xet_mem_prop_utilization_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_MEM_PROP_BANDWIDTH
typedef struct _xet_mem_prop_bandwidth_t
{
    uint32_t readCounter;                           ///< [out] Total bytes read from memory
    uint32_t writeCounter;                          ///< [out] Total bytes written to memory
    uint32_t maxBandwidth;                          ///< [out] Current maximum bandwidth in units of bytes/sec

} xet_mem_prop_bandwidth_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_MEM_PROP_ECC_COUNTERS
typedef struct _xet_mem_prop_ecc_counters_t
{
    uint32_t parityErrors;                          ///< [out] Total parity errors that have occurred
    uint32_t correctableErrors;                     ///< [out] Total correctable errors that have occurred
    uint32_t uncorrectableErrors;                   ///< [out] Total uncorrectable errors that have occurred
    uint32_t retiredPages;                          ///< [out] Total number of pages that have been retired
    uint32_t badPages;                              ///< [out] Total number of pages that have been permanently marked as bad

} xet_mem_prop_ecc_counters_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_MEM_PROP_ECC_CLEAR
typedef xe_bool_t xet_mem_prop_ecc_clear_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_MEM_PROP_ECC_POISON
typedef xe_bool_t xet_mem_prop_ecc_poison_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Link resource types
typedef enum _xet_link_type_t
{
    XET_LINK_TYPE_PCI = 0,                          ///< PCI connection
    XET_LINK_TYPE_PEER_TO_PEER,                     ///< Peer-to-peer connection

} xet_link_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Link speed element
typedef struct _xet_link_speed_t
{
    uint32_t numLanes;                              ///< [out] The number of lanes used by the link
    uint32_t speed;                                 ///< [out] The frequency of the link in units of MHz
    uint32_t bandwidth;                             ///< [out] The maximum bandwidth in units of bytes/sec

} xet_link_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Link resource properties
typedef enum _xet_link_properties_t
{
    XET_LINK_PROP_TYPE = 0,                         ///< (ro static) The type of link (one of ::xet_link_type_t)
    XET_LINK_PROP_BUS_ADDRESS,                      ///< (ro static) The bus address of the link
    XET_LINK_PROP_PWR_CAP,                          ///< (ro static) Indicates if the link frequency can adjust to control
                                                    ///< power
    XET_LINK_PROP_AVAIL_SPEEDS,                     ///< (ro static) Available link speeds
    XET_LINK_PROP_MAX_PACKET_SIZE,                  ///< (ro static) Available link speeds
    XET_LINK_PROP_BANDWIDTH,                        ///< (ro dynamic) Available link speeds
    XET_LINK_PROP_REPLAY_COUNTER,                   ///< (ro dynamic) Total number of packet replays that have occurred
    XET_LINK_PROP_SPEED,                            ///< (ro dynamic) Current link speed
    XET_LINK_PROP_SPEED_RANGE,                      ///< (wo dynamic) Set the min/max speeds between which the link can operate

} xet_link_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_LINK_PROP_TYPE
typedef struct _xet_link_prop_type_t
{
    xet_link_type_t type;                           ///< [out] The type of link

} xet_link_prop_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_LINK_PROP_BUS_ADDRESS
typedef struct _xet_link_prop_bus_address_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_link_prop_bus_address_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LINK_PROP_PWR_CAP
typedef xe_bool_t xet_link_prop_pwr_cap_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LINK_PROP_AVAIL_SPEEDS
/// 
/// @details
///     - The list is ordered from the smallest ratio to the largest ratio.
typedef struct _xet_link_prop_avail_speeds_t
{
    uint32_t num;                                   ///< [out] The number of elements in pList
    const xet_link_speed_t* pList;                  ///< [out][range(0, num-1)] Pointer to an array of link speeds

} xet_link_prop_avail_speeds_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LINK_PROP_MAX_PACKET_SIZE
typedef uint32_t xet_link_prop_max_packet_size_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LINK_PROP_BANDWIDTH
typedef struct _xet_link_prop_bandwidth_t
{
    uint32_t recvCounter;                           ///< [out] Total bytes received across the link
    uint32_t sendCounter;                           ///< [out] Total bytes sent across the link
    uint32_t maxBandwidth;                          ///< [out] Maximum bytes/sec that can be transfered acros the link

} xet_link_prop_bandwidth_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LINK_PROP_REPLAY_COUNTER
typedef uint32_t xet_link_prop_replay_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LINK_PROP_SPEED
typedef struct _xet_link_prop_speed_t
{
    const xet_link_speed_t* pSpeed;                 ///< [out] Pointer to the current speed configuration

} xet_link_prop_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LINK_PROP_SPEED_RANGE
typedef struct _xet_link_prop_speed_range_t
{
    const xet_link_speed_t* pMinSpeed;              ///< [out] Pointer to the min speed configuration (one of those in the
                                                    ///< array returned by property ::XET_LINK_PROP_AVAIL_SPEEDS)
    const xet_link_speed_t* pMaxSpeed;              ///< [out] Pointer to the max speed configuration (one of those in the
                                                    ///< array returned by property ::XET_LINK_PROP_AVAIL_SPEEDS)

} xet_link_prop_speed_range_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Event types
typedef enum _xet_sysman_event_type_t
{
    XET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED = 0,       ///< The frequency is being throttled
    XET_SYSMAN_EVENT_TYPE_FREQ_POLICY_CHANGED,      ///< Another API client has modified frequency domain properties
    XET_SYSMAN_EVENT_TYPE_GPU_ERRORS,               ///< GPU hardware errors have occurred
    XET_SYSMAN_EVENT_TYPE_RESET,                    ///< Device reset has occurred
    XET_SYSMAN_EVENT_TYPE_HANG,                     ///< Device hang has occurred
    XET_SYSMAN_EVENT_TYPE_MEM_ERRORS,               ///< ECC correctable errors have occurred in a memory resource
    XET_SYSMAN_EVENT_TYPE_LINK_ERRORS,              ///< Link replays have occured in a link resource
    XET_SYSMAN_EVENT_TYPE_COUNT,                    ///< The number of event types

} xet_sysman_event_type_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Event data
typedef struct _xet_sysman_event_data_t
{
    xet_res_container_uuid_t uuid;                  ///< [out] The UUID of the resource container that generated the event
    uint32_t events;                                ///< [out] Bitfield of events (1<<::xet_sysman_event_type_t) that have been
                                                    ///< triggered.

} xet_sysman_event_data_t;

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
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_SYSMAN_H
