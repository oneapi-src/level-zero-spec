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
* @file xe_device.cpp
*
* @brief Intel Xe Driver APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/device.yml
* @endcond
*
******************************************************************************/
#include "../include/xe_device.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Reports the number of devices
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetCount**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER - "nullptr for count"
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDriverGetDeviceCount(
    uint32_t* count                                 ///< [out] number of devices available
    )
{
    // @todo: check_return(nullptr == count, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns a handle to the device object
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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDriverGetDevice(
    uint32_t ordinal,                               ///< [in] ordinal of device to retrieve
    xe_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    )
{
    // @todo: check_return(nullptr == phDevice, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the device
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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetApiVersion(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_api_version_t* version                       ///< [out] api version
    )
{
    // @todo: check_return(nullptr == version, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of the device
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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    )
{
    // @todo: check_return(nullptr == pDeviceProperties, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves compute attributes of the device
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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetComputeProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    )
{
    // @todo: check_return(nullptr == pComputeProperties, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves memory attributes of the device
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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetMemoryProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    )
{
    // @todo: check_return(nullptr == pMemProperties, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves link properties between source and destination devices.
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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetLinkProperties(
    uint32_t srcOrdinal,                            ///< [in] source device ordinal
    uint32_t dstOrdinal,                            ///< [in] destination device ordinal
    xe_device_link_properties_t* pLinkProperties    ///< [out] link properties between source and destination devices
    )
{
    // @todo: check_return(nullptr == pLinkProperties, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries if one device can directly access peer device allocations
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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceCanAccessPeer(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device performing the access
    const xe_device_handle_t hPeerDevice,           ///< [in] handle of the peer device with the allocation
    bool* value                                     ///< [out] returned access capability
    )
{
    // @todo: check_return(nullptr == value, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Enables direct access to peer device allocations
/// 
/// @details
///     - The access is uni-directional and only enables access from the device
///       to allocations on the peer device.
///     - A separate call is required to enable access from the peer device to
///       this device.
///     - @todo Ben: document any limits on number of active p2p connections
///       @todo Ben: document behavior if link is already enabled
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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceEnablePeerAccess(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device performing the access
    const xe_device_handle_t hPeerDevice            ///< [in] handle of the peer device
    )
{

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Disables direct access to peer device allocations
/// 
/// @details
///     - @todo Ben: document behavior if link is not enabled
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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceDisablePeerAccess(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device performing the access
    const xe_device_handle_t hPeerDevice            ///< [in] handle of the peer device
    )
{

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

