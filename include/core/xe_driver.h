/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_driver.h
 *
 * @brief Intel 'One API' Level-Zero APIs
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/driver.yml
 * @endcond
 *
 */
#ifndef _XE_DRIVER_H
#define _XE_DRIVER_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported initialization flags
typedef enum _xe_init_flag_t
{
    XE_INIT_FLAG_NONE = 0,                          ///< default behavior
    XE_INIT_FLAG_GPU_ONLY = XE_BIT(0),              ///< only initialize GPU drivers

} xe_init_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the 'One API' driver and must be called before any other
///        API function
/// 
/// @details
///     - If this function is not called then all other functions will return
///       ::XE_RESULT_ERROR_UNINITIALIZED.
///     - Only one instance of a driver per process will be initialized.
///     - This function is thread-safe for scenarios where multiple libraries
///       may initialize the driver simultaneously.
/// 
/// @remarks
///   _Analogues_
///     - **cuInit**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for flags
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
xe_result_t __xecall
xeInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves driver instances
/// 
/// @details
///     - A driver represents a collection of physical devices.
///     - The application may pass nullptr for pDrivers when only querying the
///       number of drivers.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetPlatformIDs
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeGetDrivers(
    uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                    ///< if count is zero, then the loader will update the value with the total
                                                    ///< number of drivers available.
                                                    ///< if count is non-zero, then the loader will only retrieve that number
                                                    ///< of drivers.
                                                    ///< if count is larger than the number of drivers available, then the
                                                    ///< loader will update the value with the correct number of drivers available.
    xe_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the driver version for the specified driver
/// 
/// @details
///     - The driver version is a non-zero, monotonically increasing value where
///       higher values always indicate a more recent version.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDriverGetVersion**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == version
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetDriverVersion(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t* version                               ///< [out] driver version
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
/// @brief Returns the API version supported by the specified driver
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
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDrivers
///         + nullptr == version
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetApiVersion(
    xe_driver_handle_t hDrivers,                    ///< [in] handle of the driver instance
    xe_api_version_t* version                       ///< [out] api version
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_driver_ipc_properties_t
typedef enum _xe_driver_ipc_properties_version_t
{
    XE_DRIVER_IPC_PROPERTIES_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ), ///< version 1.0

} xe_driver_ipc_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief IPC properties queried using ::xeDriverGetIPCProperties
typedef struct _xe_driver_ipc_properties_t
{
    xe_driver_ipc_properties_version_t version;     ///< [in] ::XE_DRIVER_IPC_PROPERTIES_VERSION_CURRENT
    xe_bool_t memsSupported;                        ///< [out] Supports passing memory allocations between processes. See
                                                    ///< ::::xeDriverGetMemIpcHandle.
    xe_bool_t eventsSupported;                      ///< [out] Supports passing events between processes. See
                                                    ///< ::::xeEventPoolGetIpcHandle.

} xe_driver_ipc_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves IPC attributes of the driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == pIPCProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetIPCProperties(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    xe_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves devices within a driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGet**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetDevices(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of devices available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                    ///< if count is larger than the number of devices available, then the
                                                    ///< driver will update the value with the correct number of devices available.
    xe_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_DRIVER_H
