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
* @file xe_device.h
*
* @brief Intel Xe Driver APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/device.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_DEVICE_H
#define _XE_DEVICE_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Reports the number of devices
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetCount**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER - "nullptr for count"
xe_result_t __xecall
  xeDriverGetDeviceCount(
    uint32_t* count                                 ///< [out] number of devices available
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns a handle to the device object
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGet**
///     - clGetDeviceIDs
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + ordinal is out of range reported by ::xeDriverGetDeviceCount
///         + nullptr for phDevice
xe_result_t __xecall
  xeDriverGetDevice(
    uint32_t ordinal,                               ///< [in] ordinal of device to retrieve
    xe_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reports the number of sub-devices for this device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetCount**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER - "nullptr for count"
xe_result_t __xecall
  xeDeviceGetSubDeviceCount(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t* count                                 ///< [out] number of sub-devices available
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns a handle to the sub-device object
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGet**
///     - clGetDeviceIDs
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + ordinal is out of range reported by ::xeDeviceGetSubDeviceCount
///         + nullptr for phDevice
xe_result_t __xecall
  xeDeviceGetSubDevice(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
    xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported API versions
/// 
/// @details
///     - API versions contain major and minor attributes, use
///       ::XE_MAJOR_VERSION and ::XE_MINOR_VERSION
typedef enum _xe_api_version_t
{
    XE_API_VERSION_1_0 = XE_MAKE_VERSION( 1, 0 ),   ///< 1.0

} xe_api_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuCtxGetApiVersion**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for version
xe_result_t __xecall
  xeDeviceGetApiVersion(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_api_version_t* version                       ///< [out] api version
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_device_properties_t
#define XE_DEVICE_PROPERTIES_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Maximum device name string size
#define XE_MAX_DEVICE_NAME  256

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using ::xeDeviceGetProperties
typedef struct _xe_device_properties_t
{
    uint32_t version;                               ///< [in] ::XE_DEVICE_PROPERTIES_VERSION
    uint32_t vendorId;                              ///< [out] vendor id from PCI configuration
    uint32_t deviceId;                              ///< [out] device id from PCI configuration
    uint32_t coreClockRate;                         ///< [out] Clock rate for device core.
    uint32_t memClockRate;                          ///< [out] Clock rate for device global memory
    uint32_t memGlobalBusWidth;                     ///< [out] Bus width between core and memory.
    uint64_t totalLocalMemSize;                     ///< [out] Total memory size in bytes.
    uint32_t numAsyncComputeEngines;                ///< [out] Number of asynchronous compute engines
    uint32_t numAsyncCopyEngines;                   ///< [out] Number of asynchronous copy engines
    uint32_t numComputeCores;                       ///< [out] Number of compute cores
    uint32_t maxCommandQueuePriority;               ///< [out] Maximum priority for command queues. Higher value is higher priority.
    char device_name[XE_MAX_DEVICE_NAME];           ///< [out] Device name

} xe_device_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
///     - cuDeviceGetName
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for provided for properties
xe_result_t __xecall
  xeDeviceGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_device_compute_properties_t
#define XE_DEVICE_COMPUTE_PROPERTIES_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Device compute properties queried using ::xeDeviceGetComputeProperties
typedef struct _xe_device_compute_properties_t
{
    uint32_t version;                               ///< [in] ::XE_DEVICE_COMPUTE_PROPERTIES_VERSION
    uint32_t maxThreadsPerGroup;                    ///< [out] Maximum threads per compute group
    uint32_t maxGroupDimX;                          ///< [out] Maximum threads for X dimension in group
    uint32_t maxGroupDimY;                          ///< [out] Maximum threads for Y dimension in group
    uint32_t maxGroupDimZ;                          ///< [out] Maximum threads for Z dimension in group
    uint32_t maxDispatchDimX;                       ///< [out] Maximum thread groups dispatched for x dimension
    uint32_t maxDipsatchDimY;                       ///< [out] Maximum thread groups dispatched for y dimension
    uint32_t maxDispatchDimZ;                       ///< [out] Maximum thread groups dispatched for z dimension
    uint32_t maxSharedLocalMemory;                  ///< [out] Maximum shared local memory per group. @todo [**Zack**] should this be in device props?
    uint32_t maxGroupRegisters;                     ///< [out] Maximum physical registers available per group
    uint32_t warpSize;                              ///< [out] Maximum threads that can be executed in lock-step. @todo [**Zack**] should we call this something else?

} xe_device_compute_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves compute attributes of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for provided for properties
xe_result_t __xecall
  xeDeviceGetComputeProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_device_memory_properties_t
#define XE_DEVICE_MEMORY_PROPERTIES_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory access capabilities
/// 
/// @details
///     - Supported access capabilities for different types of memory
///       allocations
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
typedef enum _xe_memory_access_capabilities_t
{
    XE_MEMORY_ACCESS = XE_BIT( 0 ),                 ///< Supports load/store access
    XE_MEMORY_ATOMIC_ACCESS = XE_BIT( 1 ),          ///< Supports atomic access
    XE_MEMORY_CONCURRENT_ACCESS = XE_BIT( 2 ),      ///< Supports concurrent access
    XE_MEMORY_CONCURRENT_ATOMIC_ACCESS = XE_BIT( 3 ),   ///< Supports concurrent atomic access

} xe_memory_access_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device memory properties queried using ::xeDeviceGetMemoryProperties
typedef struct _xe_device_memory_properties_t
{
    uint32_t version;                               ///< [in] ::XE_DEVICE_MEMORY_PROPERTIES_VERSION
    bool unifiedMemory;                             ///< [out] Host and device share same physical memory.
    bool onDemandPageFaults;                        ///< [out] Device supports on-demand page-faulting.
    uint32_t maxResourceDims1D;                     ///< [out] Maximum resource dimensions for 1D resources.
    uint32_t maxResourceDims2D;                     ///< [out] Maximum resource dimensions for 2D resources.
    uint32_t maxResourceDims3D;                     ///< [out] Maximum resource dimensions for 3D resources.
    uint32_t maxResourceArraySlices;                ///< [out] Maximum resource array slices
    uint32_t hostAllocCapabilities;                 ///< [out] Supported operations on host memory allocations
    uint32_t deviceAllocCapabilities;               ///< [out] Supported operations on device memory allocations
    uint32_t sharedAllocCapabilities;               ///< [out] Supported operations on shared memory allocations
    uint32_t sharedCrossDeviceAllocCapabilities;    ///< [out] Supported operations on cross-device shared memory allocations
    uint32_t IntermediateCacheSize;                 ///< [out] Device Intermediate Cache(L1/L2) size
    bool IntermediateCacheControl;                  ///< [out] Support User control on Intermediate Cache(i.e. Resize SLM section vs Generic Cache).
    uint32_t LastLevelCacheSize;                    ///< [out] Device LastLevelCacheSize(L3) size
    bool LastLevelCacheSizeControl;                 ///< [out] Support User control on LastLevelCacheSize Cache(i.e. Resize SLM section vs Generic Cache).

} xe_device_memory_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves memory attributes of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
///     - cuDeviceTotalMem
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for provided for properties
xe_result_t __xecall
  xeDeviceGetMemoryProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_device_link_properties_t
#define XE_DEVICE_LINK_PROPERTIES_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using ::xeDeviceGetLinkProperties
typedef struct _xe_device_link_properties_t
{
    uint32_t version;                               ///< [in] ::XE_DEVICE_LINK_PROPERTIES_VERSION
    bool isP2PSupported;                            ///< [out] Is P2P access supported across link
    bool isAtomicsSupported;                        ///< [out] Are atomics supported across link
    uint32_t performanceRank;                       ///< [out] Relative performance rank of link. @todo [**Zack**] should this be different metric?

} xe_device_link_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves link properties between source and destination devices.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaDeviceGetP2PAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid ordinal. Use ::xeDriverGetDeviceCount for valid range.
///         + nullptr for provided for properties
xe_result_t __xecall
  xeDeviceGetLinkProperties(
    uint32_t srcOrdinal,                            ///< [in] source device ordinal
    uint32_t dstOrdinal,                            ///< [in] destination device ordinal
    xe_device_link_properties_t* pLinkProperties    ///< [out] link properties between source and destination devices
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries if one device can directly access peer device allocations
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaDeviceCanAccessPeer**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid handle for hPeerDevice
///         + nullptr for value
xe_result_t __xecall
  xeDeviceCanAccessPeer(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device performing the access
    const xe_device_handle_t hPeerDevice,           ///< [in] handle of the peer device with the allocation
    bool* value                                     ///< [out] returned access capability
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Enables direct access to peer device allocations
/// 
/// @details
///     - The access is uni-directional and only enables access from the device
///       to allocations on the peer device.
///     - A separate call is required to enable access from the peer device to
///       this device.
///     - The application may **not** call this function from simultaneous
///       threads.
///     - @todo [**Ben**] document any limits on number of active p2p
///       connections @todo [**Ben**] document behavior if link is already
///       enabled
/// 
/// @remarks
///   _Analogues_
///     - **cudaDeviceEnablePeerAccess**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid handle for hPeerDevice
///         + devices do not support peer access
xe_result_t __xecall
  xeDeviceEnablePeerAccess(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device performing the access
    const xe_device_handle_t hPeerDevice            ///< [in] handle of the peer device
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Disables direct access to peer device allocations
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads.
///     - @todo [**Ben**] document behavior if link is not enabled
/// 
/// @remarks
///   _Analogues_
///     - **cudaDeviceDisablePeerAccess**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid handle for hPeerDevice
///         + devices do not support peer access
xe_result_t __xecall
  xeDeviceDisablePeerAccess(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device performing the access
    const xe_device_handle_t hPeerDevice            ///< [in] handle of the peer device
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported Cache Config
/// 
/// @details
///     - Supported Cache Config (Default, Large SLM, Large Data Cache)
typedef enum _xe_cache_config_t
{
    XE_CACHE_CONFIG_DEFAULT = XE_BIT( 0 ),          ///< Default Config
    XE_CACHE_CONFIG_LARGE_SLM = XE_BIT( 1 ),        ///< Large SLM size
    XE_CACHE_CONFIG_LARGE_DATA = XE_BIT( 2 ),       ///< Large General Data size

} xe_cache_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred Intermediate cache configuration for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads.
/// 
/// @remarks
///   _Analogues_
///     - **cudaFuncSetCacheConfig **
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid CacheConfig
///         + devices do not support CacheConfig
xe_result_t __xecall
  xeDeviceSetIntermediateCacheConfig(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred Last Level cache configuration for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads.
/// 
/// @remarks
///   _Analogues_
///     - **cudaFuncSetCacheConfig **
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid CacheConfig
///         + devices do not support CacheConfig
xe_result_t __xecall
  xeDeviceSetLastLevelCacheConfig(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    );

#endif // _XE_DEVICE_H
