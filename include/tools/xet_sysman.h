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
/// @brief API version of SMI
typedef enum _xet_sysman_version_t
{
    XET_SYSMAN_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),   ///< version 1.0

} xet_sysman_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief SMI initialization flags (bitfield)
typedef enum _xet_sysman_init_flags_t
{
    XET_SYSMAN_INIT_FLAGS_NONE = 0,                 ///< Default initialization
    XET_SYSMAN_INIT_FLAGS_WRITE = XE_BIT( 0 ),      ///< Request write/control access to resources

} xet_sysman_init_flags_t;

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
    );

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
    );

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
    XET_RESOURCE_TYPE_MEM,                          ///< Memory resource
    XET_RESOURCE_TYPE_LINK,                         ///< Link resource
    XET_RESOURCE_TYPE_MAX_TYPES,                    ///< The number of resource types
    XET_RESOURCE_TYPE_ANY = -1,                     ///< Any resource filter

} xet_resource_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource ID
typedef struct _xet_resource_id_t
{
    xet_resource_type_t type;                       ///< [in,out] Resource type
    uint32_t index;                                 ///< [in,out] Resource index (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::xet_resource_type_t]-1)

} xet_resource_id_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_RESOURCE_ID_ANY
/// @brief Any resource
#define XET_RESOURCE_ID_ANY  { XET_RESOURCE_TYPE_ANY, 0x0 }
#endif // XET_RESOURCE_ID_ANY

///////////////////////////////////////////////////////////////////////////////
/// @brief Accelerator assets
typedef enum _xet_accel_asset_t
{
    XET_ACCEL_ASSET_PCIE_CONTROLLER = 0,            ///< PCIe controller
    XET_ACCEL_ASSET_IDI_MEM_CONTROLLER,             ///< IDI memory controller
    XET_ACCEL_ASSET_HBM_MEM_CONTROLLER,             ///< HBM memory controller
    XET_ACCEL_ASSET_L3_CACHE,                       ///< L3 cache
    XET_ACCEL_ASSET_BLITTER,                        ///< Blitter
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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error type
typedef enum _xet_ras_error_type_t
{
    XET_RAS_ERROR_TYPE_NONE = 0,                    ///< No error type
    XET_RAS_ERROR_TYPE_FATAL = XE_BIT( 0 ),         ///< Error was fatal
    XET_RAS_ERROR_TYPE_NON_FATAL = XE_BIT( 1 ),     ///< Error was not fatal
    XET_RAS_ERROR_TYPE_CORRECTABLE = XE_BIT( 2 ),   ///< Error was corrected
    XET_RAS_ERROR_TYPE_UNCORRECTABLE = XE_BIT( 3 ), ///< Error was not corrected
    XET_RAS_ERROR_TYPE_PARITY = XE_BIT( 4 ),        ///< Parity error occurred
    XET_RAS_ERROR_TYPE_SINGLE_BIT = XE_BIT( 5 ),    ///< Single bit error occurred
    XET_RAS_ERROR_TYPE_DOUBLE_BIT = XE_BIT( 6 ),    ///< Single bit error occurred
    XET_RAS_ERROR_TYPE_REPLAY = XE_BIT( 7 ),        ///< Replay occurred
    XET_RAS_ERROR_TYPE_ALL = ~0,                    ///< Select all error types

} xet_ras_error_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error structural location
typedef enum _xet_ras_error_loc_t
{
    XET_RAS_ERROR_LOC_NONE = 0,                     ///< No location
    XET_RAS_ERROR_LOC_MAIN_MEM = XE_BIT( 0 ),       ///< Error occurred in main onboard memory
    XET_RAS_ERROR_LOC_L3_CACHE = XE_BIT( 1 ),       ///< Error occurred in L3 cache
    XET_RAS_ERROR_LOC_SAMPLER_SRAM = XE_BIT( 2 ),   ///< Error occurred in sampler SRAM
    XET_RAS_ERROR_LOC_GUC_SRAM = XE_BIT( 3 ),       ///< Error occurred in microcontroller SRAM
    XET_RAS_ERROR_LOC_INST_CACHE = XE_BIT( 4 ),     ///< Error occurred in the compute unit instruction cache
    XET_RAS_ERROR_LOC_GRF = XE_BIT( 5 ),            ///< Error occurred in the compute unit register file
    XET_RAS_ERROR_LOC_SLM = XE_BIT( 6 ),            ///< Error occurred in the compute unit shared local memory
    XET_RAS_ERROR_LOC_PCI = XE_BIT( 7 ),            ///< Error occurred in the PCIe controller
    XET_RAS_ERROR_LOC_PCI_ROUTING = XE_BIT( 8 ),    ///< Error occurred routing PCIe traffic to/from sub-devices
    XET_RAS_ERROR_LOC_SGUNIT = XE_BIT( 9 ),         ///< Errors occurred handling transactions between PCI config space, MMIO
                                                    ///< registers, local memory and sub-devices
    XET_RAS_ERROR_LOC_GSC = XE_BIT( 10 ),           ///< Security errors occurred
    XET_RAS_ERROR_LOC_DISPLAY = XE_BIT( 11 ),       ///< Errors occurred in the display
    XET_RAS_ERROR_LOC_SOC = XE_BIT( 12 ),           ///< Errors occurred in other parts of the device
    XET_RAS_ERROR_LOC_GPU_HANG = XE_BIT( 13 ),      ///< Driver detected that the GPU hardware was non-responsive
    XET_RAS_ERROR_LOC_GPU_WARM_RESET = XE_BIT( 14 ),///< Driver performed a GPU warm reset
    XET_RAS_ERROR_LOC_ALL = ~0,                     ///< Select all error locations

} xet_ras_error_loc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS data type
typedef enum _xet_ras_data_type_t
{
    XET_RAS_DATA_TYPE_NONE = 0,                     ///< Errors not supported
    XET_RAS_DATA_TYPE_OCCURRED,                     ///< Indicates if an error occurred
    XET_RAS_DATA_TYPE_COUNTER,                      ///< Provides a counter for the number of errors that have occurred

} xet_ras_data_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Filter RAS errors
typedef struct _xet_ras_filter_t
{
    xet_resource_id_t resourceId;                   ///< [in] Filter based on resource ID. Set to ::XET_RESOURCE_ID_ANY to get
                                                    ///< errors from anywhere in the device
    uint32_t type;                                  ///< [in] Bitfield of error types to filter - one or more of
                                                    ///< ::xet_ras_error_type_t. Set to ::XET_RAS_ERROR_TYPE_ALL to have all
                                                    ///< error types returned.
    uint32_t location;                              ///< [in] Bitfield of error locations to filter - one or more of
                                                    ///< ::xet_ras_error_loc_t. Set to ::XET_RAS_ERROR_LOC_ALL to have all
                                                    ///< error locations returned.
    uint32_t threshold;                             ///< [in] Only return error elements that have occurred at least this
                                                    ///< number of times.
                                                    ///< If set to 0, will get a list of all possible RAS elements, even those
                                                    ///< that have not had errors.
                                                    ///< For error elements of type ::XET_RAS_DATA_TYPE_OCCURRED, there is no
                                                    ///< underlying counter, so they will always be returned independent of the
                                                    ///< threshold setting.

} xet_ras_filter_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_RAS_FILTER_ALL_COUNTERS
/// @brief Filter to get all RAS error counters
#define XET_RAS_FILTER_ALL_COUNTERS  { XET_RESOURCE_ID_ANY, (uint32_t)XET_RAS_ERROR_TYPE_ALL, (uint32_t)XET_RAS_ERROR_LOC_ALL, 0 }
#endif // XET_RAS_FILTER_ALL_COUNTERS

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_RAS_FILTER_ALL_ERRORS
/// @brief Filter to get all RAS error counters that have errors
#define XET_RAS_FILTER_ALL_ERRORS  { XET_RESOURCE_ID_ANY, (uint32_t)XET_RAS_ERROR_TYPE_ALL, (uint32_t)XET_RAS_ERROR_LOC_ALL, 1 }
#endif // XET_RAS_FILTER_ALL_ERRORS

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error
typedef struct _xet_ras_error_t
{
    uint32_t type;                                  ///< [out] Bitfield describing type of error, constructed from one or more
                                                    ///< of ::xet_ras_error_type_t
    uint32_t loc;                                   ///< [out] Bitfield describing structural location of the error,
                                                    ///< constructed from one of ::xet_ras_error_loc_t
    xet_ras_data_type_t dataType;                   ///< [out] How to interpret the data
    uint64_t data;                                  ///< [out] The value of the error - interpretation depends on dataType
    xet_resource_id_t resourceId;                   ///< [out] Resource where the error was generated. If the error doesn't
                                                    ///< come from a specific resource, this will be ::XET_RESOURCE_ID_ANY

} xet_ras_error_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Generic SMI information about a device
typedef struct _xet_sysman_info_t
{
    uint32_t numAssets[XET_ACCEL_ASSET_MAX_TYPES];  ///< [out] The number of each accelerator asset in the device.
    uint32_t numRas;                                ///< [out] The total number of RAS elements available for querying in this
                                                    ///< device.
    uint32_t rasTypes;                              ///< [out] Bitfield of the type of RAS elements (::xet_ras_error_type_t)
                                                    ///< available for querying in this device.
    uint32_t rasLocations;                          ///< [out] Bitfield of the structure location of RAS elements
                                                    ///< (::xet_ras_error_loc_t) available for querying in this device.
    uint32_t numResourcesByType[XET_RESOURCE_TYPE_MAX_TYPES];   ///< [out] The number of resources of each type in this device.

} xet_sysman_info_t;

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
    );

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define XET_STRING_PROPERTY_SIZE  32
#endif // XET_STRING_PROPERTY_SIZE

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
/// @brief Device resource properties
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_device_properties_t
{
    XET_DEVICE_PROP_SERIAL_NUMBER = 0,              ///< (ro static) The serial number of the device (data:
                                                    ///< ::xet_device_prop_serial_number_t)
    XET_DEVICE_PROP_BOARD_NUMBER,                   ///< (ro static) The board number of the device (data:
                                                    ///< ::xet_device_prop_board_number_t)
    XET_DEVICE_PROP_BRAND,                          ///< (ro static) The brand name of the device (data:
                                                    ///< ::xet_device_prop_brand_t)
    XET_DEVICE_PROP_MODEL,                          ///< (ro static) The model name of the device (data:
                                                    ///< ::xet_device_prop_model_t)
    XET_DEVICE_PROP_DEVICEID,                       ///< (ro static) The device ID of the device (data:
                                                    ///< ::xet_device_prop_deviceid_t)
    XET_DEVICE_PROP_VENDOR_NAME,                    ///< (ro static) The vendor name of the device (data:
                                                    ///< ::xet_device_prop_vendor_name_t)
    XET_DEVICE_PROP_DRIVER_VERSION,                 ///< (ro static) The driver version associated with the device (data:
                                                    ///< ::xet_device_prop_driver_version_t)
    XET_DEVICE_PROP_BARS,                           ///< (ro static) The bars configured for the device (data:
                                                    ///< ::xet_device_prop_bars_t)
    XET_DEVICE_PROP_RESET,                          ///< (wo dynamic) Reset the device (data: ::xet_device_prop_reset_t)

} xet_device_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_DEVICE_PROP_SERIAL_NUMBER
typedef struct _xet_device_prop_serial_number_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_device_prop_serial_number_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_DEVICE_PROP_BOARD_NUMBER
typedef struct _xet_device_prop_board_number_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_device_prop_board_number_t;

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
/// @brief Data for the property ::XET_DEVICE_PROP_RESET
typedef struct _xet_device_prop_reset_t
{
    xe_bool_t doReset;                              ///< [in] Set to true to perform a reset of the device

} xet_device_prop_reset_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Property support
typedef enum _xet_prop_support_t
{
    XET_PROP_SUPPORT_NONE = 0,                      ///< The property is not supported by this version of the API
    XET_PROP_SUPPORT_API = XE_BIT( 0 ),             ///< The property is supported by the the API
    XET_PROP_SUPPORT_DEVICE_CLASS = XE_BIT( 1 ),    ///< The property is supported for the class of device
    XET_PROP_SUPPORT_DEVICE = XE_BIT( 2 ),          ///< The property is supported for the device

} xet_prop_support_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Property access permissions
typedef enum _xet_prop_access_t
{
    XET_PROP_ACCESS_NO_PERMISSIONS = 0,             ///< The application does not have read-write access to the property
    XET_PROP_ACCESS_READ_PERMISSIONS = XE_BIT( 0 ), ///< The application has only read access to the property
    XET_PROP_ACCESS_WRITE_PERMISSIONS = XE_BIT( 1 ),///< The application has write access to the property

} xet_prop_access_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure to determine device properties that are
///        supported/accessible
typedef struct _xet_device_prop_capability_t
{
    xet_device_properties_t property;               ///< [in] The property
    uint8_t support;                                ///< [out] API support for the property - one of ::xet_prop_support_t
    uint8_t access;                                 ///< [out] The access permissions for the property - one of
                                                    ///< ::xet_prop_access_t
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_device_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a device property
typedef struct _xet_device_property_request_t
{
    xet_device_properties_t property;               ///< [in] The property being requested (one of ::xet_device_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_device_property_request_t;

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
    );

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
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_psu_properties_t
{
    XET_PSU_PROP_AMP_LIMIT = 0,                     ///< (ro static) The maximum electrical current in amperes that can be
                                                    ///< drawn (data: ::xet_psu_prop_amp_limit_t)
    XET_PSU_PROP_VOLTAGE_STATUS,                    ///< (ro dynamic) Indicates if under or over voltage has occurred (data:
                                                    ///< ::xet_psu_prop_voltage_status_t)
    XET_PSU_PROP_FAN_FAILURE,                       ///< (ro dynamic) Indicates if the fan has failed (data:
                                                    ///< ::xet_psu_prop_fan_failure_t)
    XET_PSU_PROP_TEMPERATURE,                       ///< (ro dynamic) The current heatsink temperature in degrees celcius
                                                    ///< (data: ::xet_psu_prop_temperature_t)
    XET_PSU_PROP_AMPS,                              ///< (ro dynamic) The current amps being drawn in amperes (data:
                                                    ///< ::xet_psu_prop_amps_t)

} xet_psu_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PSU_PROP_AMP_LIMIT
typedef struct _xet_psu_prop_amp_limit_t
{
    uint32_t limit;                                 ///< [out] The maximum electrical current in amperes that can be drawn

} xet_psu_prop_amp_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PSU_PROP_VOLTAGE_STATUS
typedef struct _xet_psu_prop_voltage_status_t
{
    xet_psu_voltage_status_t status;                ///< [out] The current PSU voltage status)

} xet_psu_prop_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PSU_PROP_FAN_FAILURE
typedef struct _xet_psu_prop_fan_failure_t
{
    xe_bool_t status;                               ///< [out] Indicates if the fan has failed

} xet_psu_prop_fan_failure_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PSU_PROP_TEMPERATURE
typedef struct _xet_psu_prop_temperature_t
{
    uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees celcius

} xet_psu_prop_temperature_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PSU_PROP_AMPS
typedef struct _xet_psu_prop_amps_t
{
    uint32_t current;                               ///< [out] The amps being drawn in amperes

} xet_psu_prop_amps_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure to determine PSU resource properties that are
///        supported/accessible
typedef struct _xet_psu_prop_capability_t
{
    xet_psu_properties_t property;                  ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_psu_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a PSU resource property
typedef struct _xet_psu_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the PSU resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_PSU]-1)
    xet_psu_properties_t property;                  ///< [in] The property being requested (one of ::xet_psu_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_psu_property_request_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensor resource properties
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_temp_properties_t
{
    XET_TEMP_PROP_TEMPERATURE = 0,                  ///< (ro dynamic) The current temperature of the sensor in degrees celcius
                                                    ///< (data: ::xet_temp_prop_temperature_t)

} xet_temp_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_TEMP_PROP_TEMPERATURE
typedef struct _xet_temp_prop_temperature_t
{
    uint32_t temperature;                           ///< [out] The current temperature of the sensor in degrees celcius

} xet_temp_prop_temperature_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure to determine temperature sensor properties that are
///        supported/accessible
typedef struct _xet_temp_prop_capability_t
{
    xet_temp_properties_t property;                 ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_temp_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a temperature sensor resource property
typedef struct _xet_temp_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the temperature sensor resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_TEMP]-1)
    xet_temp_properties_t property;                 ///< [in] The property being requested (one of ::xet_temp_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_temp_property_request_t;

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
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_fan_properties_t
{
    XET_FAN_PROP_MAX_RPM = 0,                       ///< (ro static) The maximum RPM of the fan (data:
                                                    ///< ::xet_fan_prop_max_rpm_t)
    XET_FAN_PROP_MAX_TABLE_SIZE,                    ///< (ro static) The maximum number of points in the fan temp/speed table
                                                    ///< (data: ::xet_fan_prop_max_table_size_t)
    XET_FAN_PROP_SPEED_RPM,                         ///< (ro dynamic) The current fan speed in units of revolutions per minute
                                                    ///< (rpm) (data: ::xet_fan_prop_speed_rpm_t)
    XET_FAN_PROP_SPEED_PERCENT,                     ///< (ro dynamic) The current fan speed as a percentage of the maximum
                                                    ///< speed of that fan (data: ::xet_fan_prop_speed_percent_t)
    XET_FAN_PROP_MODE,                              ///< (ro dynamic) The current fan speed mode (one of
                                                    ///< ::xet_fan_speed_mode_t) (data: ::xet_fan_prop_mode_t)
    XET_FAN_PROP_FIXED_SPEED,                       ///< (rw dynamic) Read/write the fixed speed setting for the fan (data:
                                                    ///< ::xet_fan_prop_fixed_speed_t)
    XET_FAN_PROP_SPEED_TABLE,                       ///< (rw dynamic) Read/write the fan speed table (data:
                                                    ///< ::xet_fan_prop_speed_table_t)

} xet_fan_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_MAX_RPM
typedef struct _xet_fan_prop_max_rpm_t
{
    uint32_t maxSpeed;                              ///< [out] The maximum RPM of the fan

} xet_fan_prop_max_rpm_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_MAX_TABLE_SIZE
typedef struct _xet_fan_prop_max_table_size_t
{
    uint32_t maxPoints;                             ///< [out] The maximum number of points in the fan temp/speed table

} xet_fan_prop_max_table_size_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_SPEED_RPM
typedef struct _xet_fan_prop_speed_rpm_t
{
    uint32_t speed;                                 ///< [out] The current fan speed in units of revolutions per minute (rpm)

} xet_fan_prop_speed_rpm_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FAN_PROP_SPEED_PERCENT
typedef struct _xet_fan_prop_speed_percent_t
{
    uint32_t speed;                                 ///< [out] The current fan speed as a percentage of the maximum speed of
                                                    ///< that fan

} xet_fan_prop_speed_percent_t;

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
/// @brief Request structure to determine fan resource properties that are
///        supported/accessible
typedef struct _xet_fan_prop_capability_t
{
    xet_fan_properties_t property;                  ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_fan_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a fan resource property
typedef struct _xet_fan_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the fan resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_FAN]-1)
    xet_fan_properties_t property;                  ///< [in] The property being requested (one of ::xet_fan_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_fan_property_request_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief LED resource properties
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_led_properties_t
{
    XET_LED_PROP_RGB_CAP = 0,                       ///< (ro static) Indicates if the LED is RGB capable (data:
                                                    ///< ::xet_led_prop_rgb_cap_t)
    XET_LED_PROP_STATE,                             ///< (rw dynaic) The LED state - on/off and color (data:
                                                    ///< ::xet_led_prop_state_t)

} xet_led_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LED_PROP_RGB_CAP
typedef struct _xet_led_prop_rgb_cap_t
{
    xe_bool_t haveRGB;                              ///< [out] Indicates if the LED is RGB capable

} xet_led_prop_rgb_cap_t;

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
/// @brief Request structure to determine LED resource properties that are
///        supported/accessible
typedef struct _xet_led_prop_capability_t
{
    xet_led_properties_t property;                  ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_led_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a LED resource property
typedef struct _xet_led_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the LED resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_LED]-1)
    xet_led_properties_t property;                  ///< [in] The property being requested (one of ::xet_led_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_led_property_request_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Firmware resource properties
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_firmware_properties_t
{
    XET_FIRMWARE_PROP_NAME = 0,                     ///< (ro static) Name encoded in the loaded firmware image (data:
                                                    ///< ::xet_firmware_prop_name_t)
    XET_FIRMWARE_PROP_VERSION,                      ///< (ro static) The version of the loaded firmware image (data:
                                                    ///< ::xet_firmware_prop_version_t)
    XET_FIRMWARE_PROP_CHECK,                        ///< (ro dynamic) Verify the checksum of the loaded firmware image (data:
                                                    ///< ::xet_firmware_prop_check_t)
    XET_FIRMWARE_PROP_FLASH,                        ///< (wo dynamically) Flash a new firmware image (data:
                                                    ///< ::xet_firmware_prop_flash_t)

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
/// @brief Request structure to determine firmware resource properties that are
///        supported/accessible
typedef struct _xet_firmware_prop_capability_t
{
    xet_firmware_properties_t property;             ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_firmware_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a firmware resource property
typedef struct _xet_firmware_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the firmware resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_FIRMWARE]-1)
    xet_firmware_properties_t property;             ///< [in] The property being requested (one of
                                                    ///< ::xet_firmware_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_firmware_property_request_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Power domain resource properties
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_pwr_properties_t
{
    XET_PWR_PROP_ACCEL_ASSETS = 0,                  ///< (ro static) List of accelerator assets that contribute to this power
                                                    ///< domain (data: ::xet_pwr_prop_accel_assets_t)
    XET_PWR_PROP_MAX_LIMIT,                         ///< (ro static) The maximum power limit that can be requested (data:
                                                    ///< ::xet_pwr_prop_max_limit_t)
    XET_PWR_PROP_ENERGY_COUNTER,                    ///< (ro dynamic) The value of the monotonic energy counter (data:
                                                    ///< ::xet_pwr_prop_energy_counter_t)
    XET_PWR_PROP_SUSTAINED_LIMIT,                   ///< (rw dynamic) The sustained power limit (data:
                                                    ///< ::xet_pwr_prop_sustained_limit_t)
    XET_PWR_PROP_BURST_LIMIT,                       ///< (rw dynamic) The burst power limit (data:
                                                    ///< ::xet_pwr_prop_burst_limit_t)
    XET_PWR_PROP_PEAK_LIMIT,                        ///< (rw dynamic) The peak power limit (data: ::xet_pwr_prop_peak_limit_t)

} xet_pwr_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWR_PROP_ACCEL_ASSETS
typedef struct _xet_pwr_prop_accel_assets_t
{
    uint64_t assets;                                ///< [out] List of accelerator assets that contribute to this power domain
                                                    ///< (Bitfield of (1<<::xet_accel_asset_t)).

} xet_pwr_prop_accel_assets_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWR_PROP_MAX_LIMIT
typedef struct _xet_pwr_prop_max_limit_t
{
    uint32_t assets;                                ///< [out] The maximum power limit in milliwatts that can be requested.

} xet_pwr_prop_max_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWR_PROP_ENERGY_COUNTER
typedef struct _xet_pwr_prop_energy_counter_t
{
    uint64_t energy;                                ///< [out] The value of the monotonic energy counter in millijoules.

} xet_pwr_prop_energy_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWR_PROP_SUSTAINED_LIMIT
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency if
///       the power averaged over a window (typically seconds) exceeds this
///       limit.
typedef struct _xet_pwr_prop_sustained_limit_t
{
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
/// @brief Request structure to determine power domain resource properties that
///        are supported/accessible
typedef struct _xet_pwr_prop_capability_t
{
    xet_pwr_properties_t property;                  ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_pwr_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a power domain resource property
typedef struct _xet_pwr_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the power domain resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_PWR]-1)
    xet_pwr_properties_t property;                  ///< [in] The property being requested (one of ::xet_pwr_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_pwr_property_request_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency domain types
typedef enum _xet_freq_domain_type_t
{
    XET_FREQ_DOMAIN_TYPE_PLL = 0,                   ///< The frequency of this domain is controlled by a phased-locked loop
                                                    ///< (PLL). It can generally accept a range of frequencies with a fixed
                                                    ///< step.
    XET_FREQ_DOMAIN_TYPE_DIVIDER,                   ///< The frequency of this domain is dependent on another domain through a
                                                    ///< clock divider. There is generally a limit set of divider ratios.
    XET_FREQ_DOMAIN_TYPE_MULTIPLIER,                ///< The frequency of this domain is dependent on another domain through a
                                                    ///< fractional multiplier.

} xet_freq_domain_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency mode
typedef enum _xet_freq_mode_t
{
    XET_FREQ_MODE_DEFAULT = 0,                      ///< The frequency of this domain is managed autonomously by the hardware.
    XET_FREQ_MODE_FIXED,                            ///< The frequency of this domain has been fixed by SMI.

} xet_freq_mode_t;

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
///     - The frequency of a domain of type ::XET_FREQ_DOMAIN_TYPE_DIVIDER is
///       obtained by the formula:
///     - freq = source domain freq * numerator / denominator
typedef struct _xet_freq_divider_t
{
    uint16_t numerator;                             ///< [in,out] numerator of the ratio
    uint16_t denominator;                           ///< [in,out] denominator of the ratio

} xet_freq_divider_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency multiplier
/// 
/// @details
///     - The frequency of a domain of type ::XET_FREQ_DOMAIN_TYPE_MULTIPLIER is
///       obtained by the formula:
///     - freq = source domain freq * multiplierFP8_8 / 2^8
typedef struct _xet_freq_multiplier_t
{
    uint16_t multiplierFP8_8;                       ///< [in,out] Multiplier in fixed-point U8.8 format

} xet_freq_multiplier_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency domain resource properties
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_freq_properties_t
{
    XET_FREQ_PROP_ACCEL_ASSETS = 0,                 ///< (ro static) List of accelerator assets that are connected to this
                                                    ///< power domain (data: ::xet_freq_prop_accel_assets_t)
    XET_FREQ_PROP_POWER_DOMAIN,                     ///< (ro static) Resource ID of the power domain to which this frequency
                                                    ///< domain is connected
    XET_FREQ_PROP_DOMAIN_TYPE,                      ///< (ro static) The type of frequency domain (data:
                                                    ///< ::xet_freq_prop_domain_type_t)
    XET_FREQ_PROP_AVAIL_CLOCKS,                     ///< (ro static) Available frequency clocks that this domain can run at
                                                    ///< (data: ::xet_freq_prop_avail_clocks_t)
    XET_FREQ_PROP_AVAIL_DIVIDERS,                   ///< (ro static) Available dividers that this domain can run with (data:
                                                    ///< ::xet_freq_prop_avail_dividers_t)
    XET_FREQ_PROP_AVAIL_MULTIPLIERS,                ///< (ro static) The range of multiplier values (data:
                                                    ///< ::xet_freq_prop_avail_multipliers_t)
    XET_FREQ_PROP_SRC_FREQ,                         ///< (ro static) Get the resource ID of the source frequency domain
                                                    ///< resource if the type is dependent (data: ::xet_freq_prop_src_freq_t)
    XET_FREQ_PROP_FREQ_REQUEST,                     ///< (rw dynamic) The current frequency request (data:
                                                    ///< ::xet_freq_prop_freq_request_t)
    XET_FREQ_PROP_FREQ_DIVIDER,                     ///< (rw dynamic) The current frequency divider for frequency domains of
                                                    ///< type ::XET_FREQ_DOMAIN_TYPE_DIVIDER (data:
                                                    ///< ::xet_freq_prop_freq_divider_t)
    XET_FREQ_PROP_FREQ_MULTIPLIER,                  ///< (rw dynamic) The current frequency multiplier for frequency domains of
                                                    ///< type ::XET_FREQ_DOMAIN_TYPE_MULTIPLIER  (data:
                                                    ///< ::xet_freq_prop_freq_divider_t)
    XET_FREQ_PROP_FREQ_TDP,                         ///< (ro dynamic) The maximum frequency supported under the current TDP
                                                    ///< conditions (data: ::xet_freq_prop_freq_tdp_t)
    XET_FREQ_PROP_FREQ_EFFICIENT,                   ///< (ro dynamic) The efficient minimum frequency (data:
                                                    ///< ::xet_freq_prop_freq_efficient_t)
    XET_FREQ_PROP_FREQ_RESOLVED,                    ///< (ro dynamic) The resolved frequency (data:
                                                    ///< ::xet_freq_prop_freq_resolved_t)
    XET_FREQ_PROP_THROTTLE_REASONS,                 ///< (ro dynamic) The reasons that the frequency is being limited by the
                                                    ///< PCU (data: ::xet_freq_prop_throttle_reasons_t)
    XET_FREQ_PROP_THROTTLE_TIME,                    ///< (ro dynamic) The total time that the frequency has been limited by the
                                                    ///< PCU (data: ::xet_freq_prop_throttle_time_t)

} xet_freq_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_ACCEL_ASSETS
typedef struct _xet_freq_prop_accel_assets_t
{
    uint64_t assets;                                ///< [out] List of accelerator assets that are connected to this power
                                                    ///< domain (Bitfield of (1<<::xet_accel_asset_t)).

} xet_freq_prop_accel_assets_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_POWER_DOMAIN
typedef struct _xet_freq_prop_power_domain_t
{
    xet_resource_id_t resource;                     ///< [out] The resource ID of the power domain

} xet_freq_prop_power_domain_t;

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
///     - Provides the set of frequencies as a list and as a range/step.
///     - It is generally recommended that applications choose frequencies from
///       the list. However applications can also construct the list themselves
///       using the range/steps provided.
typedef struct _xet_freq_prop_avail_clocks_t
{
    uint32_t minFP16_16;                            ///< [out] The minimum clock frequency in units of MHz (fixed point
                                                    ///< U16.16).
    uint32_t maxFP16_16;                            ///< [out] The maximum clock frequency in units of MHz (fixed point
                                                    ///< U16.16).
    uint32_t stepFP16_16;                           ///< [out] The step clock frequency in units of MHz (fixed point U16.16).
    uint32_t num;                                   ///< [out] The number of clocks
    const uint32_t* pClocksFP16_16;                 ///< [out] Array of clock frequencies in units of MHz (fixed-point U16.16)
                                                    ///< ordered from smallest to largest.

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
/// @brief Data for the property ::XET_FREQ_PROP_AVAIL_MULTIPLIERS
/// 
/// @details
///     - The range of multiplier values.
typedef struct _xet_freq_prop_avail_multipliers_t
{
    uint16_t minFP8_8;                              ///< [out] The minimum multiplier value in fixed-point U8.8 format
    uint16_t maxFP8_8;                              ///< [out] The maximum multiplier value in fixed-point U8.8 format
    uint16_t minStepFP8_8;                          ///< [out] The smallest multiplier step size in fixed-point U8.8

} xet_freq_prop_avail_multipliers_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_SRC_FREQ
typedef struct _xet_freq_prop_src_freq_t
{
    xet_resource_id_t resourceId;                   ///< [out] The resource ID of the source frequency domain

} xet_freq_prop_src_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_REQUEST
typedef struct _xet_freq_prop_freq_request_t
{
    xet_freq_mode_t mode;                           ///< [in,out] The frequency mode
    uint32_t freqRequest;                           ///< [out] The current frequency request in MHz. If setting this property,
                                                    ///< the value will be used if mode is ::XET_FREQ_MODE_FIXED, otherwise the
                                                    ///< hardware will take back control.

} xet_freq_prop_freq_request_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_DIVIDER
typedef struct _xet_freq_prop_freq_divider_t
{
    xet_freq_mode_t mode;                           ///< [in,out] The frequency mode
    xet_freq_divider_t divider;                     ///< [in,out] The frequency divider. If setting this property, the value
                                                    ///< will be used if mode is ::XET_FREQ_MODE_FIXED, otherwise the hardware
                                                    ///< will take back control.

} xet_freq_prop_freq_divider_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_MULTIPLIER
typedef struct _xet_freq_prop_freq_multiplier_t
{
    xet_freq_mode_t mode;                           ///< [in,out] The frequency mode
    xet_freq_multiplier_t multiplier;               ///< [in,out] The frequency multiplier. If setting this property, the value
                                                    ///< will be used if mode is ::XET_FREQ_MODE_FIXED, otherwise the hardware
                                                    ///< will take back control.

} xet_freq_prop_freq_multiplier_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_TDP
typedef struct _xet_freq_prop_freq_tdp_t
{
    uint32_t freqTdp;                               ///< [out] The maximum frequency in MHz supported under the current TDP
                                                    ///< conditions

} xet_freq_prop_freq_tdp_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_EFFICIENT
typedef struct _xet_freq_prop_freq_efficient_t
{
    uint32_t freqEfficient;                         ///< [out] The efficient minimum frequency in MHz

} xet_freq_prop_freq_efficient_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_FREQ_RESOLVED
typedef struct _xet_freq_prop_freq_resolved_t
{
    uint32_t freqResolved;                          ///< [out] The resolved frequency in MHz

} xet_freq_prop_freq_resolved_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_THROTTLE_REASONS
typedef struct _xet_freq_prop_throttle_reasons_t
{
    uint32_t throttleReasons;                       ///< [out] The reasons that the frequency is being limited by the PCU
                                                    ///< (Bitfield of (1<<::xet_freq_throttle_reasons_t)).

} xet_freq_prop_throttle_reasons_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_FREQ_PROP_THROTTLE_TIME
typedef struct _xet_freq_prop_throttle_time_t
{
    uint32_t throttleTime;                          ///< [out] The total time in microseconds that the frequency has been
                                                    ///< limited by the PCU.

} xet_freq_prop_throttle_time_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure to determine frequency domain resource properties
///        that are supported/accessible
typedef struct _xet_freq_prop_capability_t
{
    xet_freq_properties_t property;                 ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_freq_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a frequency domain resource property
typedef struct _xet_freq_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the frequency domain resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_FREQ]-1)
    xet_freq_properties_t property;                 ///< [in] The property being requested (one of ::xet_freq_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_freq_property_request_t;

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
    );

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
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_pwrwell_properties_t
{
    XET_PWRWELL_PROP_ACCEL_ASSETS = 0,              ///< (ro static) List of accelerator assets that are connected to this
                                                    ///< power-well domain (data: ::xet_pwrwell_prop_accel_assets_t)
    XET_PWRWELL_PROP_PROMO_CAP,                     ///< (ro static) Find out if the power-well domain has a programmable
                                                    ///< promotion setting (data: ::xet_pwrwell_prop_promo_cap_t)
    XET_PWRWELL_PROP_PROMO_MODE,                    ///< (rw dynamic) The current promotion mode (data:
                                                    ///< ::xet_pwrwell_prop_promo_mode_t)
    XET_PWRWELL_PROP_UTILIZATION,                   ///< (ro dynamic) Monotonic counters for the amount of time the power-well
                                                    ///< is off/idle/active (data: ::xet_pwrwell_prop_utilization_t)
    XET_PWRWELL_PROP_TRANSITIONS,                   ///< (ro dynamic) The monotonic counter for the number of times that the
                                                    ///< power-well has transitioned between off/idle/active states (data:
                                                    ///< ::xet_pwrwell_prop_transitions_t)

} xet_pwrwell_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_ACCEL_ASSETS
typedef struct _xet_pwrwell_prop_accel_assets_t
{
    uint64_t assets;                                ///< [out] List of accelerator assets that are connected to this power-well
                                                    ///< domain (bitfield of (1<<::xet_accel_asset_t)).

} xet_pwrwell_prop_accel_assets_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_PROMO_CAP
typedef struct _xet_pwrwell_prop_promo_cap_t
{
    xe_bool_t canChangePromoMode;                   ///< [out] Indicates if the power-well domain has a programmable promotion
                                                    ///< setting.

} xet_pwrwell_prop_promo_cap_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_PROMO_MODE
typedef struct _xet_pwrwell_prop_promo_mode_t
{
    xet_pwrwell_promo_mode_t mode;                  ///< [in,out] Current promotion mode

} xet_pwrwell_prop_promo_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_UTILIZATION
typedef struct _xet_pwrwell_prop_utilization_t
{
    uint32_t sleepCounter;                          ///< [out] The monotonic counter for the amount of time in microseconds
                                                    ///< that the power-well is off.
    uint32_t idleCounter;                           ///< [out] The monotonic counter for the amount of time in microseconds
                                                    ///< that the power-well is on but not executing any accelerator workloads.
    uint32_t activeCounter;                         ///< [out] The monotonic counter for the amount of time the power-well is
                                                    ///< on and executing accelerator workloads.

} xet_pwrwell_prop_utilization_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_PWRWELL_PROP_TRANSITIONS
typedef struct _xet_pwrwell_prop_transitions_t
{
    uint32_t wakeCounter;                           ///< [out] The monotonic counter for the number of times that the
                                                    ///< power-well has transitioned from a sleep state to a powered on state.
    uint32_t execCounter;                           ///< [out] The monotonic counter for the number of times that the
                                                    ///< power-well has transitioned from a sleep or idle state to an active
                                                    ///< state.

} xet_pwrwell_prop_transitions_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure to determine power-well domain resource properties
///        that are supported/accessible
typedef struct _xet_pwrwell_prop_capability_t
{
    xet_pwrwell_properties_t property;              ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_pwrwell_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a power-well domain resource property
typedef struct _xet_pwrwell_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the power-well domain resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_PWRWELL]-1)
    xet_pwrwell_properties_t property;              ///< [in] The property being requested (one of ::xet_pwrwell_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_pwrwell_property_request_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Accelerator asset resource properties
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_accel_properties_t
{
    XET_ACCEL_PROP_ACCEL_ASSETS = 0,                ///< (ro static) List of accelerator assets that contribute to counters in
                                                    ///< this resource (data: ::xet_accel_prop_accel_assets_t)
    XET_ACCEL_PROP_UTILIZATION,                     ///< (ro dynamic) The total wall time accelerator assets in this resource
                                                    ///< are active (data: ::xet_accel_prop_utilization_t)

} xet_accel_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_ACCEL_PROP_ACCEL_ASSETS
typedef struct _xet_accel_prop_accel_assets_t
{
    uint64_t assets;                                ///< [out] List of accelerator assets that contribute to counters in this
                                                    ///< resource (bitfield of (1<<::xet_accel_asset_t)).

} xet_accel_prop_accel_assets_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_ACCEL_PROP_UTILIZATION
typedef struct _xet_accel_prop_utilization_t
{
    uint32_t activeCounter;                         ///< [out] Monotonic counter for total wall time in microseconds that
                                                    ///< accelerator assets in this resource are active.
    uint32_t idleCounter;                           ///< [out] Monotonic counter for total wall time in microseconds that no
                                                    ///< accelerator assets in this resource are active.

} xet_accel_prop_utilization_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure to determine accelerator resource properties that
///        are supported/accessible
typedef struct _xet_accel_prop_capability_t
{
    xet_accel_properties_t property;                ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_accel_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query an accelerator resource property
typedef struct _xet_accel_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the accelerator resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_ACCEL]-1)
    xet_accel_properties_t property;                ///< [in] The property being requested (one of ::xet_accel_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_accel_property_request_t;

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
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_mem_properties_t
{
    XET_MEM_PROP_TYPE = 0,                          ///< (ro static) The type of memory covered by this resource (data:
                                                    ///< ::xet_mem_prop_type_t)
    XET_MEM_PROP_UTILIZATION,                       ///< (ro dynamic) Get current allocated/unallocated size (data:
                                                    ///< ::xet_mem_prop_utilization_t)
    XET_MEM_PROP_BANDWIDTH,                         ///< (ro dynamic) Get current read/write bandwidth counters and maximum
                                                    ///< bandwidth (data: ::xet_mem_prop_bandwidth_t)

} xet_mem_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_MEM_PROP_TYPE
typedef struct _xet_mem_prop_type_t
{
    xet_mem_type_t type;                            ///< [out] The memory type

} xet_mem_prop_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_MEM_PROP_UTILIZATION
/// 
/// @details
///     - The total physical memory is the sum of all others (stolen + bad +
///       allocated + unallocated).
///     - Percent software memory utilization given by 100 * allocated /
///       (allocated + unallocated).
///     - Percent bad memory given by 100 * bad / total
typedef struct _xet_mem_prop_utilization_t
{
    uint64_t total;                                 ///< [out] The total physical memory in bytes
    uint64_t stolen;                                ///< [out] The total stolen memory in bytes
    uint64_t bad;                                   ///< [out] The total bad memory in bytes
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
/// @brief Request structure to determine memory resource properties that are
///        supported/accessible
typedef struct _xet_mem_prop_capability_t
{
    xet_mem_properties_t property;                  ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_mem_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a memory resource property
typedef struct _xet_mem_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the memory resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_MEM]-1)
    xet_mem_properties_t property;                  ///< [in] The property being requested (one of ::xet_mem_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_mem_property_request_t;

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
    );

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
/// 
/// @details
///     - For every property, there is a corresponding structure used to hold
///       the property data. The type of the data structure is derived from the
///       property enumerator, converted to lower-case with '_t' appended.
///     - Properties can be either read-only (ro), write-only (wo) or read-write
///       (rw).
///     - Properties can be either static or dynamic. Static properties are set
///       during initialization and will not change during the lifetime of the
///       application. Dynamic properties can change at any time and should be
///       reread.
typedef enum _xet_link_properties_t
{
    XET_LINK_PROP_TYPE = 0,                         ///< (ro static) The type of link (data: ::xet_link_prop_type_t)
    XET_LINK_PROP_BUS_ADDRESS,                      ///< (ro static) The bus address of the link (data:
                                                    ///< ::xet_link_prop_bus_address_t)
    XET_LINK_PROP_PWR_CAP,                          ///< (ro static) Indicates if the link frequency can adjust to control
                                                    ///< power (data: ::xet_link_prop_pwr_cap_t)
    XET_LINK_PROP_AVAIL_SPEEDS,                     ///< (ro static) Available link speeds (data:
                                                    ///< ::xet_link_prop_avail_speeds_t)
    XET_LINK_PROP_MAX_PACKET_SIZE,                  ///< (ro static) Maximum packet size (data:
                                                    ///< ::xet_link_prop_max_packet_size_t)
    XET_LINK_PROP_BANDWIDTH,                        ///< (ro dynamic) Monotonic bandwidth counters (data:
                                                    ///< ::xet_link_prop_bandwidth_t)
    XET_LINK_PROP_SPEED,                            ///< (ro dynamic) Current link speed (data: ::xet_link_prop_speed_t)
    XET_LINK_PROP_SPEED_RANGE,                      ///< (wo dynamic) Set the min/max speeds between which the link can operate
                                                    ///< (data: ::xet_link_prop_speed_range_t)

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
typedef struct _xet_link_prop_pwr_cap_t
{
    xe_bool_t havePwrMgmt;                          ///< [out] Indicates if the link frequency can adjust to control power.

} xet_link_prop_pwr_cap_t;

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
typedef struct _xet_link_prop_max_packet_size_t
{
    uint32_t maxPacketSize;                         ///< [out] Maximum packet size in bytes.

} xet_link_prop_max_packet_size_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_LINK_PROP_BANDWIDTH
typedef struct _xet_link_prop_bandwidth_t
{
    uint32_t recvCounter;                           ///< [out] Total bytes received across the link
    uint32_t sendCounter;                           ///< [out] Total bytes sent across the link
    uint32_t maxBandwidth;                          ///< [out] Maximum bytes/sec that can be transfered acros the link

} xet_link_prop_bandwidth_t;

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
/// @brief Request structure to determine link resource properties that are
///        supported/accessible
typedef struct _xet_link_prop_capability_t
{
    xet_link_properties_t property;                 ///< [in] The property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minSampleRate;                         ///< [out] The minimum rate in microseconds that this property can be
                                                    ///< polled

} xet_link_prop_capability_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a link resource property
typedef struct _xet_link_property_request_t
{
    uint32_t index;                                 ///< [in] The index of the link resource (0 ...
                                                    ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_LINK]-1)
    xet_link_properties_t property;                 ///< [in] The property being requested (one of ::xet_link_properties_t).
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

} xet_link_property_request_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Event types
typedef enum _xet_sysman_event_type_t
{
    XET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED = 0,       ///< The frequency is being throttled
    XET_SYSMAN_EVENT_TYPE_RAS_ERRORS,               ///< ECC/RAS errors
    XET_SYSMAN_EVENT_TYPE_COUNT,                    ///< The number of event types

} xet_sysman_event_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure to determine events that are supported
typedef struct _xet_event_support_t
{
    xet_sysman_event_type_t event;                  ///< [in] The event
    xe_bool_t supported;                            ///< [out] Set to true/false to know if the event is supported

} xet_event_support_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to register/unregister events
typedef struct _xet_event_request_t
{
    xet_sysman_event_type_t event;                  ///< [in] The event type to register.
    xet_resource_id_t resourceId;                   ///< [in] Only events being generated by the specified resource. If
                                                    ///< ::XET_RESOURCE_ID_ANY, then applies to all events from all resources
                                                    ///< in the device.
    uint32_t threshold;                             ///< [in] The application only receives a notification when the total count
                                                    ///< exceeds this value. Set to zero to receive a notification for every
                                                    ///< new event.

} xet_event_request_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic type
typedef enum _xet_diag_type_t
{
    XET_DIAG_TYPE_SCAN = 0,                         ///< Run SCAN diagnostics
    XET_DIAG_TYPE_ARRAY,                            ///< Run Array diagnostics

} xet_diag_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic results
typedef enum _xet_diag_result_t
{
    XET_DIAG_RESULT_NO_ERRORS = 0,                  ///< Diagnostic completed without finding errors to repair
    XET_DIAG_RESULT_FAILED,                         ///< Diagnostic had problems running tests or attempting to setup repairs
    XET_DIAG_RESULT_REBOOT_FOR_REPAIR,              ///< Diagnostics found errors, setup for repair and reboot is required to
                                                    ///< complete the process

} xet_diag_result_t;

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
xetSysmanRunDiagnostics(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    xet_diag_type_t type,                           ///< [in] Type of diagnostic to run
    xet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_EVENT_WAIT_INFINITE
/// @brief Wait infinitely for events to arrive.
#define XET_EVENT_WAIT_INFINITE  0xFFFFFFFF
#endif // XET_EVENT_WAIT_INFINITE

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
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_SYSMAN_H
