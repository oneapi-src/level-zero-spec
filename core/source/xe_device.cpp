/**************************************************************************//**
* INTEL CONFIDENTIAL  
* Copyright 2019  
* Intel Corporation All Rights Reserved.  
*
* @cond DEV
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
* @endcond
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == count
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDriverGetDeviceCount(
    uint32_t* count                                 ///< [out] number of devices available
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == count, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {5c7c465fde2ab4523bf907a3b46343641d9b73a17c0e20334834e54d19ef5103}

    // @todo: insert <code> here

    /// @end   {5c7c465fde2ab4523bf907a3b46343641d9b73a17c0e20334834e54d19ef5103}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve 
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == pUniqueIds
///         + invalid unique id.
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDriverGetDeviceUniqueIds(
    uint32_t count,                                 ///< [in] size of device unique ids array. Typically, this will be
                                                    ///< ${x}DeviceGetCount.
    uint32_t* pUniqueIds                            ///< [out] pointer to an array of unique ids for devices. Caller must
                                                    ///< supply array.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == pUniqueIds, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {c26ed99dfec278253de324f242d61516b146acd882d0894d8208cfed698fd1d1}

    // @todo: insert <code> here

    /// @end   {c26ed99dfec278253de324f242d61516b146acd882d0894d8208cfed698fd1d1}
    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == phDevice
///         + ordinal is out of range reported by ::xeDriverGetDeviceCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDriverGetDevice(
    uint32_t uniqueId,                              ///< [in] unique id of device to retrieve. Use ${x}DriverGetDeviceUniqueIds
                                                    ///< to obtain a unique Id.
    xe_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == phDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {0fcaea081072b19126b15d5ddf6bf62c8c5a75b8647a0176af861cfb0adb1697}

    // @todo: insert <code> here

    /// @end   {0fcaea081072b19126b15d5ddf6bf62c8c5a75b8647a0176af861cfb0adb1697}
    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == phSubDevice
///         + ordinal is out of range reported by device properties.
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetSubDevice(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
    xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phSubDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {17a42ce94be984870ef7258c30474c488c4cdd342ac215c9c027a55dcd8613ff}

    // @todo: insert <code> here

    /// @end   {17a42ce94be984870ef7258c30474c488c4cdd342ac215c9c027a55dcd8613ff}
    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == version
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetApiVersion(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_api_version_t* version                       ///< [out] api version
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == version, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {fc64199c044234983739580abae3a91240008f47d57127d41cd69cd49b4fb013}

    // @todo: insert <code> here

    /// @end   {fc64199c044234983739580abae3a91240008f47d57127d41cd69cd49b4fb013}
    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pDeviceProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pDeviceProperties, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {3db75068efff2256a55cef1327ecc78abc4667e68c27a09621c6312ae779c145}

    // @todo: insert <code> here

    /// @end   {3db75068efff2256a55cef1327ecc78abc4667e68c27a09621c6312ae779c145}
    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pComputeProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetComputeProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pComputeProperties, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {7f1420ab7455a639874a23c83d2643e649a65a1340bad17572fed4071c94142b}

    // @todo: insert <code> here

    /// @end   {7f1420ab7455a639874a23c83d2643e649a65a1340bad17572fed4071c94142b}
    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pMemProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetMemoryProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pMemProperties, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {4909cbc4cbb7ee86da7ec399f394605d2c5a91e06cd283a9989a58012b7752f0}

    // @todo: insert <code> here

    /// @end   {4909cbc4cbb7ee86da7ec399f394605d2c5a91e06cd283a9989a58012b7752f0}
    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == pLinkProperties
///         + invalid ordinal. Use ::xeDriverGetDeviceCount for valid range.
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceGetLinkProperties(
    uint32_t srcOrdinal,                            ///< [in] source device ordinal
    uint32_t dstOrdinal,                            ///< [in] destination device ordinal
    xe_device_link_properties_t* pLinkProperties    ///< [out] link properties between source and destination devices
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == pLinkProperties, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {ec34167e970021b312559839b8f4105aaa14c088f77586203eb745f4b6784d1b}

    // @todo: insert <code> here

    /// @end   {ec34167e970021b312559839b8f4105aaa14c088f77586203eb745f4b6784d1b}
    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == hPeerDevice
///         + nullptr == value
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceCanAccessPeer(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    bool* value                                     ///< [out] returned access capability
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hPeerDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == value, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {e77d453d30dc6017ed8b9d0d0d5dd6597a4ca30fa37cac35a99658310d7bba4e}

    // @todo: insert <code> here

    /// @end   {e77d453d30dc6017ed8b9d0d0d5dd6597a4ca30fa37cac35a99658310d7bba4e}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred Intermediate cache configuration for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @remarks
///   _Analogues_
///     - **cudaFuncSetCacheConfig **
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + devices do not support CacheConfig
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceSetIntermediateCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {b2e59b50895488ecaf51f53a705eb7dbae91b1f1d903390571066aa20cc9f588}

    // @todo: insert <code> here

    /// @end   {b2e59b50895488ecaf51f53a705eb7dbae91b1f1d903390571066aa20cc9f588}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred Last Level cache configuration for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @remarks
///   _Analogues_
///     - **cudaFuncSetCacheConfig **
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + devices do not support CacheConfig
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceSetLastLevelCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {821981d67b82ce6c7da51cab0dc27d5dad640e710ef2244156e7a8a345e83e24}

    // @todo: insert <code> here

    /// @end   {821981d67b82ce6c7da51cab0dc27d5dad640e710ef2244156e7a8a345e83e24}
    return XE_RESULT_SUCCESS;
}

