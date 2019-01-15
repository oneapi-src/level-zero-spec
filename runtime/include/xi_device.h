/**************************************************************************//**
*
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
* The source code contained or described herein and all documents related to the
* source code ("Material") are owned by Intel Corporation or its suppliers or
* licensors. Title to the Material remains with Intel Corporation or its suppliers
* and licensors. The Material contains trade secrets and proprietary and confidential
* information of Intel or its suppliers and licensors. The Material is protected by
* worldwide copyright and trade secret laws and treaty provisions. No part of the
* Material may be used, copied, reproduced, modified, published, uploaded, posted
* transmitted, distributed, or disclosed in any way without Intel's prior express
* written permission.
*
* No license under any patent, copyright, trade secret or other intellectual
* property right is granted to or conferred upon you by disclosure or delivery
* of the Materials, either expressly, by implication, inducement, estoppel
* or otherwise. Any license under such intellectual property rights must be
* express and approved by Intel in writing.
*
* @file xi_device.h
*
* @brief Intel Xi Runtime APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/device.yml
* @endcond
*
******************************************************************************/
#ifndef _XI_DEVICE_H
#define _XI_DEVICE_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Reports the number of devices
/// @remarks
///   _Analogues_
///     - **cuDeviceGetCount**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER - "nullptr for count"
xi_result_t __xicall
  xiDeviceGetCount(
    uint32_t* count                                 ///< [out] number of devices available
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns a handle to the device object
/// @remarks
///   _Analogues_
///     - **cuDeviceGet**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + ordinal is out of range reported by ::xiDeviceGetCount
///     + nullptr for phDevice
xi_result_t __xicall
  xiDeviceGet(
    uint32_t ordinal,                               ///< [in] ordinal of device to retrieve
    xi_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported API versions
/// @details
///     - API versions contain major and minor attributes, use
///       ::XI_MAJOR_VERSION and ::XI_MINOR_VERSION
typedef enum _xi_api_version_t
{
    XI_API_VERSION_1_0 = XI_MAKE_VERSION( 1, 0 ),   ///< 1.0

} xi_api_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the device
/// @remarks
///   _Analogues_
///     - **cuCtxGetApiVersion**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for version
xi_result_t __xicall
  xiDeviceGetApiVersion(
    xi_device_handle_t hDevice,                     ///< [in] handle of the device object
    xi_api_version_t* version                       ///< [out] api version
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xi_device_properties_t
#define XI_DEVICE_PROPERTIES_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Maximum device name string size
#define XI_MAX_DEVICE_NAME  256

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using ::xiDeviceGetProperties
typedef struct _xi_device_properties_t
{
    uint32_t version;                               ///< [in] ::XI_DEVICE_PROPERTIES_VERSION
    uint32_t vendorId;                              ///< [out] vendor id from PCI configuration
    uint32_t deviceId;                              ///< [out] device id from PCI configuration
    uint32_t coreClockRate;                         ///< [out] Clock rate for device core.
    uint32_t memClockRate;                          ///< [out] Clock rate for device global memory
    uint32_t memGlobalBusWidth;                     ///< [out] Bus width between core and memory.
    uint32_t totalLocalMemSize;                     ///< [out] Total memory size in MB.
    uint32_t l2CacheSize;                           ///< [out] Device L2 size
    uint32_t numAsyncComputeEngines;                ///< [out] Num asynchronous compute engines
    uint32_t numComputeCores;                       ///< [out] Num compute cores
    char device_name[XI_MAX_DEVICE_NAME];           ///< [out] Device name

} xi_device_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of the device
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
///     - cuDeviceGetName
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for provided for properties
xi_result_t __xicall
  xiDeviceGetProperties(
    xi_device_handle_t hDevice,                     ///< [in] handle of the device object
    xi_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xi_device_compute_properties_t
#define XI_DEVICE_COMPUTE_PROPERTIES_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Device compute properties queried using ::xiDeviceGetComputeProperties
typedef struct _xi_device_compute_properties_t
{
    uint32_t version;                               ///< [in] ::XI_DEVICE_COMPUTE_PROPERTIES_VERSION
    uint32_t maxThreadsPerGroup;                    ///< [out] Max threads per compute group
    uint32_t maxGroupDimX;                          ///< [out] Max threads for X dimension in group
    uint32_t maxGroupDimY;                          ///< [out] Max threads for Y dimension in group
    uint32_t maxGroupDimZ;                          ///< [out] Max threads for Z dimension in group
    uint32_t maxDispatchDimX;                       ///< [out] Max thread groups dispatched for x dimension
    uint32_t maxDipsatchDimY;                       ///< [out] Max thread groups dispatched for y dimension
    uint32_t maxDispatchDimZ;                       ///< [out] Max thread groups dispatched for z dimension
    uint32_t maxSharedLocalMemory;                  ///< [out] Max shared local memory per group. @todo Should this be in device props?
    uint32_t maxGroupRegisters;                     ///< [out] Max physical registers available per group
    uint32_t warpSize;                              ///< [out] Max threads that can be executed in lock-step. @todo: Should we call this something else?

} xi_device_compute_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves compute attributes of the device
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for provided for properties
xi_result_t __xicall
  xiDeviceGetComputeProperties(
    xi_device_handle_t hDevice,                     ///< [in] handle of the device object
    xi_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xi_device_memory_properties_t
#define XI_DEVICE_MEMORY_PROPERTIES_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory access capabilities
/// @details
///     - Supported access capabilities for different types of memory
///       allocations
typedef enum _xi_memory_access_capabilities_t
{
    XI_MEMORY_ACCESS = XI_BIT( 0 ),                 ///< Supports load/store access
    XI_MEMORY_ATOMIC_ACCESS = XI_BIT( 1 ),          ///< Supports atomic access
    XI_MEMORY_CONCURRENT_ACCESS = XI_BIT( 2 ),      ///< Supports concurrent access
    XI_MEMORY_CONCURRENT_ATOMIC_ACCESS = XI_BIT( 3 ),   ///< Supports concurrent atomic access

} xi_memory_access_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device memory properties queried using ::xiDeviceGetMemoryProperties
typedef struct _xi_device_memory_properties_t
{
    uint32_t version;                               ///< [in] ::XI_DEVICE_MEMORY_PROPERTIES_VERSION
    bool isIntegrated;                              ///< [out] Host and device share same physical memory.
    uint32_t maxResourceDims1D;                     ///< [out] Maximum resource dimensions for 1D resources.
    uint32_t maxResourceDims2D;                     ///< [out] Maximum resource dimensions for 2D resources.
    uint32_t maxResourceDims3D;                     ///< [out] Maximum resource dimensions for 3D resources.
    uint32_t maxResourceArraySlices;                ///< [out] Maximum resource array slices
    uint32_t hostAllocCapabilities;                 ///< [out] Supported operations on host memory allocations
    uint32_t deviceAllocCapabilities;               ///< [out] Supported operations on device memory allocations
    uint32_t sharedAllocCapabilities;               ///< [out] Supported operations on shared memory allocations
    uint32_t sharedCrossDeviceAllocCapabilities;    ///< [out] Supported operations on cross-device shared memory allocations

} xi_device_memory_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves memory attributes of the device
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
///     - cuDeviceTotalMem
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for provided for properties
xi_result_t __xicall
  xiDeviceGetMemoryProperties(
    xi_device_handle_t hDevice,                     ///< [in] handle of the device object
    xi_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    );

#endif // _XI_DEVICE_H
