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
******************************************************************************/
#ifndef _XE_DEVICE_H
#define _XE_DEVICE_H
#if defined( __cplusplus )
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Reports the number of devices
/// @remarks _Analogues:_
///     - **cuDeviceGetCount**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr for count
xe_result_t __xecall
  xeDeviceGetCount(
    uint32_t* count                 ///< [out] number of devices available
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns a handle to the device object
/// @remarks _Analogues:_
///     - **cuDeviceGet**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + ordinal is out of range reported by ::xeDeviceGetCount
///         + nullptr for phDevice
xe_result_t __xecall
  xeDeviceGet( 
    uint32_t ordinal,               ///< [in] ordinal of device to retrieve
    xe_device_handle_t* phDevice    ///< [out] pointer to handle of device object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported API versions
/// @details API versions contain major and minor attributes,
///     use XE_MAJOR_VERSION and XE_MINOR_VERSION
XE_DECLARE_ENUM( xe_api_version_t )
{
    XE_API_VERSION_1_0 = XE_MAKE_VERSION( 1, 0 )    ///< 1.0
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the device
/// @remarks _Analogues:_
///     - **cuCtxGetApiVersion**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for version
xe_result_t __xecall
  xeDeviceGetApiVersion(
    xe_device_handle_t hDevice,     ///< [in] handle of the device object
    xe_api_version_t* version       ///< [out] api version
    );


///////////////////////////////////////////////////////////////////////////////
#define XE_MAX_DEVICE_NAME 256

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using xeGetDeviceProperties()
typedef struct _xe_device_properties_t
{
    uint32_t vendorId;                    ///< [out] vendor id from PCI configuration
    uint32_t deviceId;                    ///< [out] device id from PCI configuration
    uint32_t coreClockRate;               ///< [out] Clock rate for device core.
    uint32_t memClockRate;                ///< [out] Clock rate for device global memory
    uint32_t memGlobalBusWidth;           ///< [out] Bus width between core and memory.
    uint32_t totalLocalMemSize;           ///< [out] Total memory size in MB.
    uint32_t l2CacheSize;                 ///< [out] Device L2 size
    uint32_t numAsyncComputeEngines;      ///< [out] Num asynchronous compute engines
    uint32_t numComputeCores;             ///< [out] Num compute cores
 
    char device_name[XE_MAX_DEVICE_NAME]; ///< [out] device name

} xe_device_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device compute propertiess queried using xeGetDeviceComputeProperties()
typedef struct _xe_device_compute_properties_t
{
    uint32_t MaxThreadsPerGroup;          ///< [out] Max threads per compute group
    uint32_t MaxGroupDimX;                ///< [out] Max threads for X dimension in group
    uint32_t MaxGroupDimY;                ///< [out] Max threads for Y dimension in group
    uint32_t MaxGroupDimZ;                ///< [out] Max threads for Z dimension in group
    uint32_t MaxDispatchDimX;             ///< [out] Max thread groups dispatched for x dimension
    uint32_t MaxDipsatchDimY;             ///< [out] Max thread groups dispatched for y dimension
    uint32_t MaxDispatchDimZ;             ///< [out] Max thread groups dispatched for z dimension
    uint32_t MaxSharedLocalMemory;        ///< [out] Max shared local memory per group. @todo Should this be in device props?
    uint32_t MaxGroupRegisters;           ///< [out] Max physical registers available per group
    uint32_t WarpSize;                    ///< [out] Max threads that can be executed in lock-step.
} xe_device_compute_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device compute propertiess queried using xeGetDeviceMemoryProperties()
typedef struct _xe_device_memory_properties_t
{
    bool     isIntegrated;              ///< [out] Host and device share same physical memory.
    bool     hasSharedVirtualMemory;    ///< [out] Supports shared virtual memory (SVM)
    uint32_t MaxResourceDims1D;         ///< [out] Maximum resource dimensions for 1D resources.
    uint32_t MaxResourceDims2D;         ///< [out] Maximum resource dimensions for 2D resources.
    uint32_t MaxResourceDims3D;         ///< [out] Maximum resource dimensions for 3D resources.
    uint32_t MaxResourceArraySlices;    ///< [out] Maximum resource array slices
} xe_device_memory_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of the device
/// @remarks _Analogues:_
///     - **cuDeviceGetAttribute**
///     - cuDeviceGetName
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + XE framework has not been initialized.
///         + nullptr for provided for properties
xe_result_t __xecall
    xeGetDeviceProperties(
        xe_device_handle_t hDevice,                 ///< [in] handle of the device object
        xe_device_properties_t* pDeviceProperties   ///< [out] query result for device properties
    );


///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves compute attributes of the device
/// @remarks _Analogues:_
///     - **cuDeviceGetAttribute**
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + XE framework has not been initialized.
///         + nullptr for provided for properties
xe_result_t __xecall
    xeGetDeviceComputeProperties(
        xe_device_handle_t hDevice,                        ///< [in] handle of the device object
        xe_device_compute_properties_t* pComputeProperties ///< [out] query result for compute properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves memory attributes of the device
/// @remarks _Analogues:_
///     - **cuDeviceGetAttribute**
///     - cuDeviceTotalMem
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + XE framework has not been initialized.
///         + nullptr for provided for properties
xe_result_t __xecall
    xeGetDeviceMemoryProperties(
        xe_device_handle_t hDevice,                        ///< [in] handle of the device object
        xe_device_memory_properties_t* pMemProperties      ///< [out] query result for compute properties
    );

#endif // _XE_DEVICE_H