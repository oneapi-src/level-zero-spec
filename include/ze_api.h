/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_api.h
 * @version v1.0-r0.9.277
 *
 */
#ifndef _ZE_API_H
#define _ZE_API_H
#if defined(__cplusplus)
#pragma once
#endif

// standard headers
#include <stdint.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

#pragma region common
///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAKE_VERSION
/// @brief Generates generic 'One API' API versions
#define ZE_MAKE_VERSION( _major, _minor )  (( _major << 16 )|( _minor & 0x0000ffff))
#endif // ZE_MAKE_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAJOR_VERSION
/// @brief Extracts 'One API' API major version
#define ZE_MAJOR_VERSION( _ver )  ( _ver >> 16 )
#endif // ZE_MAJOR_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MINOR_VERSION
/// @brief Extracts 'One API' API minor version
#define ZE_MINOR_VERSION( _ver )  ( _ver & 0x0000ffff )
#endif // ZE_MINOR_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef __zecall
#if defined(_WIN32)
/// @brief Calling convention for all API functions
#define __zecall  __cdecl
#else
#define __zecall  
#endif // defined(_WIN32)
#endif // __zecall

///////////////////////////////////////////////////////////////////////////////
#ifndef __ze_api_export
#if defined(_WIN32)
/// @brief Microsoft-specific dllexport storage-class attribute
#define __ze_api_export  __declspec(dllexport)
#else
#define __ze_api_export  
#endif // defined(_WIN32)
#endif // __ze_api_export

///////////////////////////////////////////////////////////////////////////////
#ifndef __zedllexport
#if defined(_WIN32)
/// @brief Microsoft-specific dllexport storage-class attribute
#define __zedllexport  __declspec(dllexport)
#endif // defined(_WIN32)
#endif // __zedllexport

///////////////////////////////////////////////////////////////////////////////
#ifndef __zedllexport
#if __GNUC__ >= 4
/// @brief GCC-specific dllexport storage-class attribute
#define __zedllexport  __attribute__ ((visibility ("default")))
#else
#define __zedllexport  
#endif // __GNUC__ >= 4
#endif // __zedllexport

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_ENABLE_OCL_INTEROP
#if !defined(ZE_ENABLE_OCL_INTEROP)
/// @brief Disable OpenCL interoperability functions if not explicitly defined
#define ZE_ENABLE_OCL_INTEROP  0
#endif // !defined(ZE_ENABLE_OCL_INTEROP)
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief compiler-independent type
typedef uint8_t ze_bool_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of a driver instance
typedef struct _ze_driver_handle_t *ze_driver_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's device object
typedef struct _ze_device_handle_t *ze_device_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's command queue object
typedef struct _ze_command_queue_handle_t *ze_command_queue_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's command list object
typedef struct _ze_command_list_handle_t *ze_command_list_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's fence object
typedef struct _ze_fence_handle_t *ze_fence_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's event pool object
typedef struct _ze_event_pool_handle_t *ze_event_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's event object
typedef struct _ze_event_handle_t *ze_event_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's image object
typedef struct _ze_image_handle_t *ze_image_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's module object
typedef struct _ze_module_handle_t *ze_module_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of module's build log object
typedef struct _ze_module_build_log_handle_t *ze_module_build_log_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's kernel object
typedef struct _ze_kernel_handle_t *ze_kernel_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's sampler object
typedef struct _ze_sampler_handle_t *ze_sampler_handle_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_IPC_HANDLE_SIZE
/// @brief Maximum IPC handle size
#define ZE_MAX_IPC_HANDLE_SIZE  64
#endif // ZE_MAX_IPC_HANDLE_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief IPC handle to a memory allocation
typedef struct _ze_ipc_mem_handle_t
{
    char data[ZE_MAX_IPC_HANDLE_SIZE];              ///< Opaque data representing an IPC handle

} ze_ipc_mem_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief IPC handle to a event pool allocation
typedef struct _ze_ipc_event_pool_handle_t
{
    char data[ZE_MAX_IPC_HANDLE_SIZE];              ///< Opaque data representing an IPC handle

} ze_ipc_event_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_BIT
/// @brief Generic macro for enumerator bit masks
#define ZE_BIT( _i )  ( 1 << _i )
#endif // ZE_BIT

///////////////////////////////////////////////////////////////////////////////
/// @brief Defines Return/Error codes
typedef enum _ze_result_t
{
    ZE_RESULT_SUCCESS = 0,                          ///< [Core] success
    ZE_RESULT_NOT_READY = 1,                        ///< [Core] synchronization primitive not signaled
    ZE_RESULT_ERROR_DEVICE_LOST = 0x70000001,       ///< [Core] device hung, reset, was removed, or driver update occurred
    ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY,             ///< [Core] insufficient host memory to satisfy call
    ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY,           ///< [Core] insufficient device memory to satisfy call
    ZE_RESULT_ERROR_MODULE_BUILD_FAILURE,           ///< [Core] error occurred when building module, see build log for details
    ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS = 0x70010000,  ///< [Tools] access denied due to permission level
    ZE_RESULT_ERROR_NOT_AVAILABLE,                  ///< [Tools] resource already in use and simultaneous access not allowed
    ZE_RESULT_ERROR_UNINITIALIZED = 0x78000001,     ///< [Validation] driver is not initialized
    ZE_RESULT_ERROR_UNSUPPORTED_VERSION,            ///< [Validation] generic error code for unsupported versions
    ZE_RESULT_ERROR_UNSUPPORTED_FEATURE,            ///< [Validation] generic error code for unsupported features
    ZE_RESULT_ERROR_INVALID_ARGUMENT,               ///< [Validation] generic error code for invalid arguments
    ZE_RESULT_ERROR_INVALID_NULL_HANDLE,            ///< [Validation] handle argument is not valid
    ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE,           ///< [Validation] object pointed to by handle still in-use by device
    ZE_RESULT_ERROR_INVALID_NULL_POINTER,           ///< [Validation] pointer argument may not be nullptr
    ZE_RESULT_ERROR_INVALID_SIZE,                   ///< [Validation] size argument is invalid (e.g., must not be zero)
    ZE_RESULT_ERROR_UNSUPPORTED_SIZE,               ///< [Validation] size argument is not supported by the device (e.g., too
                                                    ///< large)
    ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT,          ///< [Validation] alignment argument is not supported by the device (e.g.,
                                                    ///< too small)
    ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT, ///< [Validation] synchronization object in invalid state
    ZE_RESULT_ERROR_INVALID_ENUMERATION,            ///< [Validation] enumerator argument is not valid
    ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION,        ///< [Validation] enumerator argument is not supported by the device
    ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT,       ///< [Validation] image format is not supported by the device
    ZE_RESULT_ERROR_INVALID_NATIVE_BINARY,          ///< [Validation] native binary is not supported by the device
    ZE_RESULT_ERROR_INVALID_GLOBAL_NAME,            ///< [Validation] global variable is not found in the module
    ZE_RESULT_ERROR_INVALID_KERNEL_NAME,            ///< [Validation] kernel name is not found in the module
    ZE_RESULT_ERROR_INVALID_FUNCTION_NAME,          ///< [Validation] function name is not found in the module
    ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION,   ///< [Validation] group size dimension is not valid for the kernel or
                                                    ///< device
    ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION, ///< [Validation] global width dimension is not valid for the kernel or
                                                    ///< device
    ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX,  ///< [Validation] kernel argument index is not valid for kernel
    ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE,   ///< [Validation] kernel argument size does not match kernel
    ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE, ///< [Validation] value of kernel attribute is not valid for the kernel or
                                                    ///< device
    ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE,      ///< [Validation] command list type does not match command queue type
    ZE_RESULT_ERROR_OVERLAPPING_REGIONS,            ///< [Validation] copy operations do not support overlapping regions of
                                                    ///< memory
    ZE_RESULT_ERROR_UNKNOWN = 0x7fffffff,           ///< [Core] unknown or internal error

} ze_result_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_ipc_mem_handle_t
typedef struct _ze_ipc_mem_handle_t ze_ipc_mem_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_ipc_event_pool_handle_t
typedef struct _ze_ipc_event_pool_handle_t ze_ipc_event_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_driver_uuid_t
typedef struct _ze_driver_uuid_t ze_driver_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_driver_properties_t
typedef struct _ze_driver_properties_t ze_driver_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_driver_ipc_properties_t
typedef struct _ze_driver_ipc_properties_t ze_driver_ipc_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_uuid_t
typedef struct _ze_device_uuid_t ze_device_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_properties_t
typedef struct _ze_device_properties_t ze_device_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_compute_properties_t
typedef struct _ze_device_compute_properties_t ze_device_compute_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_native_kernel_uuid_t
typedef struct _ze_native_kernel_uuid_t ze_native_kernel_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_kernel_properties_t
typedef struct _ze_device_kernel_properties_t ze_device_kernel_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_command_queue_group_properties_t
typedef struct _ze_command_queue_group_properties_t ze_command_queue_group_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_memory_properties_t
typedef struct _ze_device_memory_properties_t ze_device_memory_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_memory_access_properties_t
typedef struct _ze_device_memory_access_properties_t ze_device_memory_access_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_cache_properties_t
typedef struct _ze_device_cache_properties_t ze_device_cache_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_image_properties_t
typedef struct _ze_device_image_properties_t ze_device_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_p2p_properties_t
typedef struct _ze_device_p2p_properties_t ze_device_p2p_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_command_queue_desc_t
typedef struct _ze_command_queue_desc_t ze_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_command_list_desc_t
typedef struct _ze_command_list_desc_t ze_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_copy_region_t
typedef struct _ze_copy_region_t ze_copy_region_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_image_region_t
typedef struct _ze_image_region_t ze_image_region_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_event_pool_desc_t
typedef struct _ze_event_pool_desc_t ze_event_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_event_desc_t
typedef struct _ze_event_desc_t ze_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_fence_desc_t
typedef struct _ze_fence_desc_t ze_fence_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_image_format_desc_t
typedef struct _ze_image_format_desc_t ze_image_format_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_image_desc_t
typedef struct _ze_image_desc_t ze_image_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_image_properties_t
typedef struct _ze_image_properties_t ze_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_mem_alloc_desc_t
typedef struct _ze_device_mem_alloc_desc_t ze_device_mem_alloc_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_host_mem_alloc_desc_t
typedef struct _ze_host_mem_alloc_desc_t ze_host_mem_alloc_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_memory_allocation_properties_t
typedef struct _ze_memory_allocation_properties_t ze_memory_allocation_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_module_constants_t
typedef struct _ze_module_constants_t ze_module_constants_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_module_desc_t
typedef struct _ze_module_desc_t ze_module_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_kernel_desc_t
typedef struct _ze_kernel_desc_t ze_kernel_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_kernel_properties_t
typedef struct _ze_kernel_properties_t ze_kernel_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_group_count_t
typedef struct _ze_group_count_t ze_group_count_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_sampler_desc_t
typedef struct _ze_sampler_desc_t ze_sampler_desc_t;


#pragma endregion
#pragma region driver
///////////////////////////////////////////////////////////////////////////////
/// @brief Supported initialization flags
typedef enum _ze_init_flag_t
{
    ZE_INIT_FLAG_NONE = 0,                          ///< default behavior
    ZE_INIT_FLAG_GPU_ONLY = ZE_BIT(0),              ///< only initialize GPU drivers

} ze_init_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the 'One API' driver and must be called before any other
///        API function
/// 
/// @details
///     - If this function is not called then all other functions will return
///       ::ZE_RESULT_ERROR_UNINITIALIZED.
///     - Only one instance of a driver per process will be initialized.
///     - This function is thread-safe for scenarios where multiple libraries
///       may initialize the driver simultaneously.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + flags
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
__ze_api_export ze_result_t __zecall
zeInit(
    ze_init_flag_t flags                            ///< [in] initialization flags
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zeDriverGet(
    uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                    ///< if count is zero, then the loader will update the value with the total
                                                    ///< number of drivers available.
                                                    ///< if count is non-zero, then the loader will only retrieve that number
                                                    ///< of drivers.
                                                    ///< if count is larger than the number of drivers available, then the
                                                    ///< loader will update the value with the correct number of drivers available.
    ze_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported API versions
/// 
/// @details
///     - API versions contain major and minor attributes, use
///       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
typedef enum _ze_api_version_t
{
    ZE_API_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),   ///< 1.0
    ZE_API_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< latest known version

} ze_api_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the specified driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == version`
__ze_api_export ze_result_t __zecall
zeDriverGetApiVersion(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_api_version_t* version                       ///< [out] api version
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_driver_properties_t
typedef enum _ze_driver_properties_version_t
{
    ZE_DRIVER_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ), ///< version 1.0
    ZE_DRIVER_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ), ///< latest known version

} ze_driver_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DRIVER_UUID_SIZE
/// @brief Maximum driver universal unique id (UUID) size in bytes
#define ZE_MAX_DRIVER_UUID_SIZE  16
#endif // ZE_MAX_DRIVER_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Driver universal unique id (UUID)
typedef struct _ze_driver_uuid_t
{
    uint8_t id[ZE_MAX_DRIVER_UUID_SIZE];            ///< Opaque data representing a driver UUID

} ze_driver_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Driver properties queried using ::zeDriverGetProperties
typedef struct _ze_driver_properties_t
{
    ze_driver_properties_version_t version;         ///< [in] ::ZE_DRIVER_PROPERTIES_VERSION_CURRENT
    ze_driver_uuid_t uuid;                          ///< [out] universal unique identifier.
    uint32_t driverVersion;                         ///< [out] driver version
                                                    ///< The driver version is a non-zero, monotonically increasing value where
                                                    ///< higher values always indicate a more recent version.

} ze_driver_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves properties of the driver.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clGetPlatformInfo**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDriverProperties`
__ze_api_export ze_result_t __zecall
zeDriverGetProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_driver_ipc_properties_t
typedef enum _ze_driver_ipc_properties_version_t
{
    ZE_DRIVER_IPC_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ), ///< version 1.0
    ZE_DRIVER_IPC_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ), ///< latest known version

} ze_driver_ipc_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief IPC properties queried using ::zeDriverGetIPCProperties
typedef struct _ze_driver_ipc_properties_t
{
    ze_driver_ipc_properties_version_t version;     ///< [in] ::ZE_DRIVER_IPC_PROPERTIES_VERSION_CURRENT
    ze_bool_t memsSupported;                        ///< [out] Supports passing memory allocations between processes. See
                                                    ///< ::::zeDriverGetMemIpcHandle.
    ze_bool_t eventsSupported;                      ///< [out] Supports passing events between processes. See
                                                    ///< ::::zeEventPoolGetIpcHandle.

} ze_driver_ipc_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves IPC attributes of the driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pIPCProperties`
__ze_api_export ze_result_t __zecall
zeDriverGetIPCProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves an extension function for the specified driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clGetExtensionFunctionAddressForPlatform**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFuncName`
///         + `nullptr == pfunc`
__ze_api_export ze_result_t __zecall
zeDriverGetExtensionFunctionAddress(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const char* pFuncName,                          ///< [in] name of the extension function
    void** pfunc                                    ///< [out] pointer to extension function
    );

#pragma endregion
#pragma region device
///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves devices within a driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zeDeviceGet(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of devices available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                    ///< if count is larger than the number of devices available, then the
                                                    ///< driver will update the value with the correct number of devices available.
    ze_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a sub-device from a device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clCreateSubDevices
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zeDeviceGetSubDevices(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of sub-devices available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of sub-devices.
                                                    ///< if count is larger than the number of sub-devices available, then the
                                                    ///< driver will update the value with the correct number of sub-devices available.
    ze_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_properties_t
typedef enum _ze_device_properties_version_t
{
    ZE_DEVICE_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ), ///< version 1.0
    ZE_DEVICE_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ), ///< latest known version

} ze_device_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported device types
typedef enum _ze_device_type_t
{
    ZE_DEVICE_TYPE_GPU = 1,                         ///< Graphics Processing Unit
    ZE_DEVICE_TYPE_FPGA,                            ///< Field Programmable Gate Array

} ze_device_type_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DEVICE_UUID_SIZE
/// @brief Maximum device universal unique id (UUID) size in bytes
#define ZE_MAX_DEVICE_UUID_SIZE  16
#endif // ZE_MAX_DEVICE_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Device universal unique id (UUID)
typedef struct _ze_device_uuid_t
{
    uint8_t id[ZE_MAX_DEVICE_UUID_SIZE];            ///< Opaque data representing a device UUID

} ze_device_uuid_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DEVICE_NAME
/// @brief Maximum device name string size
#define ZE_MAX_DEVICE_NAME  256
#endif // ZE_MAX_DEVICE_NAME

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using ::zeDeviceGetProperties
typedef struct _ze_device_properties_t
{
    ze_device_properties_version_t version;         ///< [in] ::ZE_DEVICE_PROPERTIES_VERSION_CURRENT
    ze_device_type_t type;                          ///< [out] generic device type
    uint32_t vendorId;                              ///< [out] vendor id from PCI configuration
    uint32_t deviceId;                              ///< [out] device id from PCI configuration
    ze_device_uuid_t uuid;                          ///< [out] universal unique identifier.
    ze_bool_t isSubdevice;                          ///< [out] If the device handle used for query represents a sub-device.
    uint32_t subdeviceId;                           ///< [out] sub-device id. Only valid if isSubdevice is true.
    uint32_t coreClockRate;                         ///< [out] Clock rate for device core.
    ze_bool_t unifiedMemorySupported;               ///< [out] Supports unified physical memory between Host and device.
    ze_bool_t eccMemorySupported;                   ///< [out] Supports error correction memory access.
    ze_bool_t onDemandPageFaultsSupported;          ///< [out] Supports on-demand page-faulting.
    uint32_t maxHardwareContexts;                   ///< [out] Maximum number of logical hardware contexts.
    uint32_t maxCommandQueuePriority;               ///< [out] Maximum priority for command queues. Higher value is higher
                                                    ///< priority.
    uint32_t numThreadsPerEU;                       ///< [out] Number of threads per EU.
    uint32_t physicalEUSimdWidth;                   ///< [out] The physical EU simd width.
    uint32_t numEUsPerSubslice;                     ///< [out] Number of EUs per sub-slice.
    uint32_t numSubslicesPerSlice;                  ///< [out] Number of sub-slices per slice.
    uint32_t numSlices;                             ///< [out] Number of slices.
    uint64_t timerResolution;                       ///< [out] Returns the resolution of device timer in nanoseconds used for
                                                    ///< profiling, timestamps, etc.
    char name[ZE_MAX_DEVICE_NAME];                  ///< [out] Device name

} ze_device_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves properties of the device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDeviceProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_compute_properties_t
typedef enum _ze_device_compute_properties_version_t
{
    ZE_DEVICE_COMPUTE_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ), ///< version 1.0
    ZE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ), ///< latest known version

} ze_device_compute_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_SUBGROUPSIZE_COUNT
/// @brief Maximum number of subgroup sizes supported.
#define ZE_SUBGROUPSIZE_COUNT  8
#endif // ZE_SUBGROUPSIZE_COUNT

///////////////////////////////////////////////////////////////////////////////
/// @brief Device compute properties queried using ::zeDeviceGetComputeProperties
typedef struct _ze_device_compute_properties_t
{
    ze_device_compute_properties_version_t version; ///< [in] ::ZE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT
    uint32_t maxTotalGroupSize;                     ///< [out] Maximum items per compute group. (maxGroupSizeX * maxGroupSizeY
                                                    ///< * maxGroupSizeZ) <= maxTotalGroupSize
    uint32_t maxGroupSizeX;                         ///< [out] Maximum items for X dimension in group
    uint32_t maxGroupSizeY;                         ///< [out] Maximum items for Y dimension in group
    uint32_t maxGroupSizeZ;                         ///< [out] Maximum items for Z dimension in group
    uint32_t maxGroupCountX;                        ///< [out] Maximum groups that can be launched for x dimension
    uint32_t maxGroupCountY;                        ///< [out] Maximum groups that can be launched for y dimension
    uint32_t maxGroupCountZ;                        ///< [out] Maximum groups that can be launched for z dimension
    uint32_t maxSharedLocalMemory;                  ///< [out] Maximum shared local memory per group.
    uint32_t numSubGroupSizes;                      ///< [out] Number of subgroup sizes supported. This indicates number of
                                                    ///< entries in subGroupSizes.
    uint32_t subGroupSizes[ZE_SUBGROUPSIZE_COUNT];  ///< [out] Size group sizes supported.

} ze_device_compute_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves compute properties of the device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pComputeProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetComputeProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_kernel_properties_t
typedef enum _ze_device_kernel_properties_version_t
{
    ZE_DEVICE_KERNEL_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),  ///< version 1.0
    ZE_DEVICE_KERNEL_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),  ///< latest known version

} ze_device_kernel_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_NATIVE_KERNEL_UUID_SIZE
/// @brief Maximum native kernel universal unique id (UUID) size in bytes
#define ZE_MAX_NATIVE_KERNEL_UUID_SIZE  16
#endif // ZE_MAX_NATIVE_KERNEL_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Native kernel universal unique id (UUID)
typedef struct _ze_native_kernel_uuid_t
{
    uint8_t id[ZE_MAX_NATIVE_KERNEL_UUID_SIZE];     ///< Opaque data representing a native kernel UUID

} ze_native_kernel_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Floating Point capabilities
/// 
/// @details
///     - floating-point capabilities of the device.
typedef enum _ze_fp_capabilities_t
{
    ZE_FP_CAPS_NONE = 0,                            ///< None
    ZE_FP_CAPS_DENORM = ZE_BIT( 0 ),                ///< Supports denorms
    ZE_FP_CAPS_INF_NAN = ZE_BIT( 1 ),               ///< Supports INF and quiet NaNs
    ZE_FP_CAPS_ROUND_TO_NEAREST = ZE_BIT( 2 ),      ///< Supports rounding to nearest even rounding mode
    ZE_FP_CAPS_ROUND_TO_ZERO = ZE_BIT( 3 ),         ///< Supports rounding to zero.
    ZE_FP_CAPS_ROUND_TO_INF = ZE_BIT( 4 ),          ///< Supports rounding to both positive and negative INF.
    ZE_FP_CAPS_FMA = ZE_BIT( 5 ),                   ///< Supports IEEE754-2008 fused multiply-add.
    ZE_FP_CAPS_ROUNDED_DIVIDE_SQRT = ZE_BIT( 6 ),   ///< Supports rounding as defined by IEEE754 for divide and sqrt
                                                    ///< operations.
    ZE_FP_CAPS_SOFT_FLOAT = ZE_BIT( 7 ),            ///< Uses software implementation for basic floating-point operations.

} ze_fp_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using ::zeDeviceGetKernelProperties
typedef struct _ze_device_kernel_properties_t
{
    ze_device_kernel_properties_version_t version;  ///< [in] ::ZE_DEVICE_KERNEL_PROPERTIES_VERSION_CURRENT
    uint32_t spirvVersionSupported;                 ///< [out] Maximum supported SPIR-V version.
                                                    ///< Returns zero if SPIR-V is not supported.
                                                    ///< Contains major and minor attributes, use ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION.
    ze_native_kernel_uuid_t nativeKernelSupported;  ///< [out] Compatibility UUID of supported native kernel.
                                                    ///< UUID may or may not be the same across driver release, devices, or
                                                    ///< operating systems.
                                                    ///< Application is responsible for ensuring UUID matches before creating
                                                    ///< module using
                                                    ///< previously created native kernel.
    ze_bool_t fp16Supported;                        ///< [out] Supports 16-bit floating-point operations
    ze_bool_t fp64Supported;                        ///< [out] Supports 64-bit floating-point operations
    ze_bool_t int64AtomicsSupported;                ///< [out] Supports 64-bit atomic operations
    ze_bool_t dp4aSupported;                        ///< [out] Supports four component dot product and accumulate operations
    ze_fp_capabilities_t halfFpCapabilities;        ///< [out] Capabilities for half-precision floating-point operations.
    ze_fp_capabilities_t singleFpCapabilities;      ///< [out] Capabilities for single-precision floating-point operations.
    ze_fp_capabilities_t doubleFpCapabilities;      ///< [out] Capabilities for double-precision floating-point operations.
    uint32_t maxArgumentsSize;                      ///< [out] Maximum kernel argument size that is supported.
    uint32_t printfBufferSize;                      ///< [out] Maximum size of internal buffer that holds output of printf
                                                    ///< calls from kernel.

} ze_device_kernel_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves kernel properties of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pKernelProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetKernelProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_kernel_properties_t* pKernelProperties///< [in,out] query result for kernel properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_command_queue_group_properties_t
typedef enum _ze_command_queue_group_properties_version_t
{
    ZE_COMMAND_QUEUE_GROUP_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),///< version 1.0
    ZE_COMMAND_QUEUE_GROUP_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),///< latest known version

} ze_command_queue_group_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command queue group properties queried using
///        ::zeDeviceGetCommandQueueGroupProperties
typedef struct _ze_command_queue_group_properties_t
{
    ze_command_queue_group_properties_version_t version;///< [in] ::ZE_COMMAND_QUEUE_GROUP_PROPERTIES_VERSION_CURRENT
    ze_bool_t computeSupported;                     ///< [out] command queue group supports enqueing compute commands.
    ze_bool_t copySupported;                        ///< [out] command queue group supports enqueing copy commands.
    ze_bool_t singleSliceSupported;                 ///< [out] command queue group supports reserving a single slice. 'slice'
                                                    ///< size is reported by ::ze_device_properties_t.
    ze_bool_t cooperativeKernelsSupported;          ///< [out] command queue group supports cooperative kernels. See
                                                    ///< ::zeCommandListAppendLaunchCooperativeKernel for more details.

} ze_command_queue_group_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves command queue group properties of the device.
/// 
/// @details
///     - Properties are reported for each physical command queue type supported
///       by the device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkGetPhysicalDeviceQueueFamilyProperties**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zeDeviceGetCommandQueueGroupProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of command queue group properties available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< command queue group properties.
                                                    ///< if count is larger than the number of command queue group properties
                                                    ///< available, then the driver will update the value with the correct
                                                    ///< number of command queue group properties available.
    ze_command_queue_group_properties_t* pCommandQueueGroupProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< command queue group properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_memory_properties_t
typedef enum _ze_device_memory_properties_version_t
{
    ZE_DEVICE_MEMORY_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),  ///< version 1.0
    ZE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),  ///< latest known version

} ze_device_memory_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device local memory properties queried using
///        ::zeDeviceGetMemoryProperties
typedef struct _ze_device_memory_properties_t
{
    ze_device_memory_properties_version_t version;  ///< [in] ::ZE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT
    uint32_t maxClockRate;                          ///< [out] Maximum clock rate for device memory.
    uint32_t maxBusWidth;                           ///< [out] Maximum bus width between device and memory.
    uint64_t totalSize;                             ///< [out] Total memory size in bytes.

} ze_device_memory_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves local memory properties of the device.
/// 
/// @details
///     - Properties are reported for each physical memory type supported by the
///       device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zeDeviceGetMemoryProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of memory properties available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< memory properties.
                                                    ///< if count is larger than the number of memory properties available,
                                                    ///< then the driver will update the value with the correct number of
                                                    ///< memory properties available.
    ze_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< memory properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_memory_access_properties_t
typedef enum _ze_device_memory_access_properties_version_t
{
    ZE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0
    ZE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< latest known version

} ze_device_memory_access_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory access capabilities
/// 
/// @details
///     - Supported access capabilities for different types of memory
///       allocations
typedef enum _ze_memory_access_capabilities_t
{
    ZE_MEMORY_ACCESS_NONE = 0,                      ///< Access not supported
    ZE_MEMORY_ACCESS = ZE_BIT( 0 ),                 ///< Supports load/store access
    ZE_MEMORY_ATOMIC_ACCESS = ZE_BIT( 1 ),          ///< Supports atomic access
    ZE_MEMORY_CONCURRENT_ACCESS = ZE_BIT( 2 ),      ///< Supports concurrent access
    ZE_MEMORY_CONCURRENT_ATOMIC_ACCESS = ZE_BIT( 3 ),   ///< Supports concurrent atomic access

} ze_memory_access_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device memory access properties queried using
///        ::zeDeviceGetMemoryAccessProperties
typedef struct _ze_device_memory_access_properties_t
{
    ze_device_memory_access_properties_version_t version;   ///< [in] ::ZE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT
    ze_memory_access_capabilities_t hostAllocCapabilities;  ///< [out] Bitfield describing host memory capabilities
    ze_memory_access_capabilities_t deviceAllocCapabilities;///< [out] Bitfield describing device memory capabilities
    ze_memory_access_capabilities_t sharedSingleDeviceAllocCapabilities;///< [out] Bitfield describing shared (single-device) memory capabilities
    ze_memory_access_capabilities_t sharedCrossDeviceAllocCapabilities; ///< [out] Bitfield describing shared (cross-device) memory capabilities
    ze_memory_access_capabilities_t sharedSystemAllocCapabilities;  ///< [out] Bitfield describing shared (system) memory capabilities

} ze_device_memory_access_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves memory access properties of the device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMemAccessProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetMemoryAccessProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_cache_properties_t
typedef enum _ze_device_cache_properties_version_t
{
    ZE_DEVICE_CACHE_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0
    ZE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< latest known version

} ze_device_cache_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device cache properties queried using ::zeDeviceGetCacheProperties
typedef struct _ze_device_cache_properties_t
{
    ze_device_cache_properties_version_t version;   ///< [in] ::ZE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT
    ze_bool_t intermediateCacheControlSupported;    ///< [out] Support User control on Intermediate Cache (i.e. Resize SLM
                                                    ///< section vs Generic Cache)
    size_t intermediateCacheSize;                   ///< [out] Per-cache Intermediate Cache (L1/L2) size, in bytes
    uint32_t intermediateCachelineSize;             ///< [out] Cacheline size in bytes for intermediate cacheline (L1/L2).
    ze_bool_t lastLevelCacheSizeControlSupported;   ///< [out] Support User control on Last Level Cache (i.e. Resize SLM
                                                    ///< section vs Generic Cache).
    size_t lastLevelCacheSize;                      ///< [out] Per-cache Last Level Cache (L3) size, in bytes
    uint32_t lastLevelCachelineSize;                ///< [out] Cacheline size in bytes for last-level cacheline (L3).

} ze_device_cache_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves cache properties of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCacheProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetCacheProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_cache_properties_t* pCacheProperties  ///< [in,out] query result for cache properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_image_properties_t
typedef enum _ze_device_image_properties_version_t
{
    ZE_DEVICE_IMAGE_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0
    ZE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< latest known version

} ze_device_image_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device image properties queried using ::zeDeviceGetComputeProperties
typedef struct _ze_device_image_properties_t
{
    ze_device_image_properties_version_t version;   ///< [in] ::ZE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT
    ze_bool_t supported;                            ///< [out] Supports reading and writing of images. See
                                                    ///< ::::zeImageGetProperties for format-specific capabilities.
    uint32_t maxImageDims1D;                        ///< [out] Maximum image dimensions for 1D resources.
    uint32_t maxImageDims2D;                        ///< [out] Maximum image dimensions for 2D resources.
    uint32_t maxImageDims3D;                        ///< [out] Maximum image dimensions for 3D resources.
    uint64_t maxImageBufferSize;                    ///< [out] Maximum image buffer size in bytes.
    uint32_t maxImageArraySlices;                   ///< [out] Maximum image array slices
    uint32_t maxSamplers;                           ///< [out] Max samplers that can be used in kernel.
    uint32_t maxReadImageArgs;                      ///< [out] Returns the maximum number of simultaneous image objects that
                                                    ///< can be read from by a kernel.
    uint32_t maxWriteImageArgs;                     ///< [out] Returns the maximum number of simultaneous image objects that
                                                    ///< can be written to by a kernel.

} ze_device_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves image properties of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImageProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetImageProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_p2p_properties_t
typedef enum _ze_device_p2p_properties_version_t
{
    ZE_DEVICE_P2P_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ), ///< version 1.0
    ZE_DEVICE_P2P_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ), ///< latest known version

} ze_device_p2p_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using ::zeDeviceGetP2PProperties
typedef struct _ze_device_p2p_properties_t
{
    ze_device_p2p_properties_version_t version;     ///< [in] ::ZE_DEVICE_P2P_PROPERTIES_VERSION_CURRENT
    ze_bool_t accessSupported;                      ///< [out] Supports access between peer devices.
    ze_bool_t atomicsSupported;                     ///< [out] Supports atomics between peer devices.

} ze_device_p2p_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves Peer-to-Peer properties between one device and a peer
///        devices
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hPeerDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pP2PProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetP2PProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries if one device can directly access peer device allocations
/// 
/// @details
///     - Any device can access any other device within a node through a
///       scale-up fabric.
///     - The following are conditions for CanAccessPeer query.
///         + If both device and peer device are the same then return true.
///         + If both sub-device and peer sub-device are the same then return
///           true.
///         + If both are sub-devices and share the same parent device then
///           return true.
///         + If both device and remote device are connected by a direct or
///           indirect scale-up fabric or over PCIe (same root complex or shared
///           PCIe switch) then true.
///         + If both sub-device and remote parent device (and vice-versa) are
///           connected by a direct or indirect scale-up fabric or over PCIe
///           (same root complex or shared PCIe switch) then true.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hPeerDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == value`
__ze_api_export ze_result_t __zecall
zeDeviceCanAccessPeer(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    ze_bool_t* value                                ///< [out] returned access capability
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported Cache Config
/// 
/// @details
///     - Supported Cache Config (Default, Large SLM, Large Data Cache)
typedef enum _ze_cache_config_t
{
    ZE_CACHE_CONFIG_DEFAULT = ZE_BIT( 0 ),          ///< Default Config
    ZE_CACHE_CONFIG_LARGE_SLM = ZE_BIT( 1 ),        ///< Large SLM size
    ZE_CACHE_CONFIG_LARGE_DATA = ZE_BIT( 2 ),       ///< Large General Data size

} ze_cache_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred Last Level cache configuration for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + CacheConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
__ze_api_export ze_result_t __zecall
zeDeviceSetLastLevelCacheConfig(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device 
    ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
    );

#pragma endregion
#pragma region cmdqueue
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_command_queue_desc_t
typedef enum _ze_command_queue_desc_version_t
{
    ZE_COMMAND_QUEUE_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),///< version 1.0
    ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),///< latest known version

} ze_command_queue_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue flags
typedef enum _ze_command_queue_flag_t
{
    ZE_COMMAND_QUEUE_FLAG_NONE = 0,                 ///< default behavior
    ZE_COMMAND_QUEUE_FLAG_SINGLE_SLICE_ONLY = ZE_BIT(0),///< command queue reserves and cannot comsume more than a single slice.

} ze_command_queue_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue modes
typedef enum _ze_command_queue_mode_t
{
    ZE_COMMAND_QUEUE_MODE_DEFAULT = 0,              ///< implicit default behavior; uses driver-based heuristics
    ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS,              ///< Device execution always completes immediately on execute;
                                                    ///< Host thread is blocked using wait on implicit synchronization object
    ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS,             ///< Device execution is scheduled and will complete in future;
                                                    ///< explicit synchronization object must be used to determine completeness

} ze_command_queue_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue priorities
typedef enum _ze_command_queue_priority_t
{
    ZE_COMMAND_QUEUE_PRIORITY_NORMAL = 0,           ///< [default] normal priority
    ZE_COMMAND_QUEUE_PRIORITY_LOW,                  ///< lower priority than normal
    ZE_COMMAND_QUEUE_PRIORITY_HIGH,                 ///< higher priority than normal

} ze_command_queue_priority_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue descriptor
typedef struct _ze_command_queue_desc_t
{
    ze_command_queue_desc_version_t version;        ///< [in] ::ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT
    uint32_t ordinal;                               ///< [in] command queue group ordinal
    ze_command_queue_flag_t flags;                  ///< [in] usage flags
    ze_command_queue_mode_t mode;                   ///< [in] operation mode
    ze_command_queue_priority_t priority;           ///< [in] priority

} ze_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue on the device.
/// 
/// @details
///     - The command queue can only be used on the device on which it was
///       created.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateCommandQueue**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phCommandQueue`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///         + desc->mode
///         + desc->priority
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeCommandQueueCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the command queue before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this command queue
///     - The application may **not** call this function from simultaneous
///       threads with the same command queue handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseCommandQueue**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeCommandQueueDestroy(
    ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Executes a command list in a command queue.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkQueueSubmit
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phCommandLists`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `0 == numCommandLists`
///     - ::ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandQueueExecuteCommandLists(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to execute
    ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                    ///< to execute
    ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Synchronizes a command queue by waiting on the host.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_NOT_READY
///         + timeout expired
__ze_api_export ze_result_t __zecall
zeCommandQueueSynchronize(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                    ///< returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                    ///< if UINT32_MAX, then function will not return until complete or device
                                                    ///< is lost.
    );

#pragma endregion
#pragma region cmdlist
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_command_list_desc_t
typedef enum _ze_command_list_desc_version_t
{
    ZE_COMMAND_LIST_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ), ///< version 1.0
    ZE_COMMAND_LIST_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ), ///< latest known version

} ze_command_list_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command list creation flags
typedef enum _ze_command_list_flag_t
{
    ZE_COMMAND_LIST_FLAG_NONE = 0,                  ///< default behavior
    ZE_COMMAND_LIST_FLAG_RELAXED_ORDERING = ZE_BIT(0),  ///< driver may reorder programs and copys between barriers and
                                                    ///< synchronization primitives.
                                                    ///< using this flag may increase Host overhead of ::zeCommandListClose.
                                                    ///< therefore, this flag should **not** be set for low-latency usage-models.
    ZE_COMMAND_LIST_FLAG_MAXIMIZE_THROUGHPUT = ZE_BIT(1),   ///< driver may perform additional optimizations that increase dexecution
                                                    ///< throughput. 
                                                    ///< using this flag may increase Host overhead of ::zeCommandListClose and ::zeCommandQueueExecuteCommandLists.
                                                    ///< therefore, this flag should **not** be set for low-latency usage-models.
    ZE_COMMAND_LIST_FLAG_EXPLICIT_ONLY = ZE_BIT(2), ///< command list should be optimized for submission to a single command
                                                    ///< queue and device engine.
                                                    ///< driver **must** disable any implicit optimizations for distributing
                                                    ///< work across multiple engines.
                                                    ///< this flag should be used when applications want full control over
                                                    ///< multi-engine submission and scheduling.

} ze_command_list_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command List descriptor
typedef struct _ze_command_list_desc_t
{
    ze_command_list_desc_version_t version;         ///< [in] ::ZE_COMMAND_LIST_DESC_VERSION_CURRENT
    uint32_t commandQueueGroupOrdinal;              ///< [in] command queue group ordinal to which this command list will be
                                                    ///< submitted
    ze_command_list_flag_t flags;                   ///< [in] creation flags

} ze_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list on the device for submitting commands to any
///        command queue.
/// 
/// @details
///     - The command list can only be used on the device on which it was
///       created.
///     - The command list is created in the 'open' state.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phCommandList`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeCommandListCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list on the device with an implicit command queue
///        for immediate submission of commands.
/// 
/// @details
///     - The command list can only be used on the device on which it was
///       created.
///     - The command list is created in the 'open' state and never needs to be
///       closed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == altdesc`
///         + `nullptr == phCommandList`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT < altdesc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + altdesc->flags
///         + altdesc->mode
///         + altdesc->priority
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeCommandListCreateImmediate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command list.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the command list before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this command list.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeCommandListDestroy(
    ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes a command list; ready to be executed by a command queue.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
__ze_api_export ze_result_t __zecall
zeCommandListClose(
    ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a command list to initial (empty) state; ready for appending
///        commands.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the command list before it is reset
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
__ze_api_export ze_result_t __zecall
zeCommandListReset(
    ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    );

#pragma endregion
#pragma region barrier
///////////////////////////////////////////////////////////////////////////////
/// @brief Appends an execution and global memory barrier into a command list.
/// 
/// @details
///     - If numWaitEvents is zero, then all previous commands are completed
///       prior to the execution of the barrier.
///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
///       signaled prior to the execution of the barrier.
///     - This command blocks all following commands from beginning until the
///       execution of the barrier completes.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkCmdPipelineBarrier**
///     - clEnqueueBarrierWithWaitList
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendBarrier(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a global memory ranges barrier into a command list.
/// 
/// @details
///     - If numWaitEvents is zero, then all previous commands are completed
///       prior to the execution of the barrier.
///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
///       signaled prior to the execution of the barrier.
///     - This command blocks all following commands from beginning until the
///       execution of the barrier completes.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRangeSizes`
///         + `nullptr == pRanges`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendMemoryRangesBarrier(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numRanges,                             ///< [in] number of memory ranges
    const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
    const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Ensures in-bound writes to the device are globally observable.
/// 
/// @details
///     - This is a special-case system level barrier that can be used to ensure
///       global observability of writes; typically needed after a producer
///       (e.g., NIC) performs direct writes to the device's memory (e.g.,
///       Direct RDMA writes).  This is typically required when the memory
///       corresponding to the writes is subsequently accessed from a remote
///       device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
__ze_api_export ze_result_t __zecall
zeDeviceSystemBarrier(
    ze_device_handle_t hDevice                      ///< [in] handle of the device
    );

#pragma endregion
#pragma region cl_interop
///////////////////////////////////////////////////////////////////////////////
#if ZE_ENABLE_OCL_INTEROP
/// @brief Registers OpenCL memory with 'One API'
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDeviceRegisterCLMemory(
    ze_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the memory
    cl_mem mem,                                     ///< [in] the OpenCL memory to register
    void** ptr                                      ///< [out] pointer to device allocation
    );
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if ZE_ENABLE_OCL_INTEROP
/// @brief Registers OpenCL program with 'One API'
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phModule`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDeviceRegisterCLProgram(
    ze_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the program
    cl_program program,                             ///< [in] the OpenCL program to register
    ze_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    );
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if ZE_ENABLE_OCL_INTEROP
/// @brief Registers OpenCL command queue with 'One API'
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phCommandQueue`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDeviceRegisterCLCommandQueue(
    ze_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the command queue
    cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
    ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    );
#endif // ZE_ENABLE_OCL_INTEROP

#pragma endregion
#pragma region copy
///////////////////////////////////////////////////////////////////////////////
/// @brief Copies host, device, or shared memory.
/// 
/// @details
///     - The memory pointed to by both srcptr and dstptr must be accessible by
///       the device on which the command list is created.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyBuffer**
///     - **clEnqueueReadBuffer**
///     - **clEnqueueWriteBuffer**
///     - **clEnqueueSVMMemcpy**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///         + `nullptr == srcptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendMemoryCopy(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size,                                    ///< [in] size in bytes to copy
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Initializes host, device, or shared memory.
/// 
/// @details
///     - The memory pointed to by dstptr must be accessible by the device on
///       which the command list is created.
///     - The value to initialize memory to is described by the pattern and the
///       pattern size.
///     - The pattern size must be a power of two.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueFillBuffer**
///     - **clEnqueueSVMMemFill**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pattern`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendMemoryFill(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* ptr,                                      ///< [in] pointer to memory to initialize
    const void* pattern,                            ///< [in] pointer to value to initialize memory to
    size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
    size_t size,                                    ///< [in] size in bytes to initialize
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copy region descriptor
typedef struct _ze_copy_region_t
{
    uint32_t originX;                               ///< [in] The origin x offset for region in bytes
    uint32_t originY;                               ///< [in] The origin y offset for region in rows
    uint32_t originZ;                               ///< [in] The origin z offset for region in slices
    uint32_t width;                                 ///< [in] The region width relative to origin in bytes
    uint32_t height;                                ///< [in] The region height relative to origin in rows
    uint32_t depth;                                 ///< [in] The region depth relative to origin in slices. Set this to 0 for
                                                    ///< 2D copy.

} ze_copy_region_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a region from a 2D or 3D array of host, device, or shared
///        memory.
/// 
/// @details
///     - The memory pointed to by both srcptr and dstptr must be accessible by
///       the device on which the command list is created.
///     - The region width, height, and depth for both src and dst must be same.
///       The origins can be different.
///     - The src and dst regions cannot be overlapping.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///         + `nullptr == dstRegion`
///         + `nullptr == srcptr`
///         + `nullptr == srcRegion`
///     - ::ZE_RESULT_ERROR_OVERLAPPING_REGIONS
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendMemoryCopyRegion(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const ze_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
    uint32_t dstPitch,                              ///< [in] destination pitch in bytes
    uint32_t dstSlicePitch,                         ///< [in] destination slice pitch in bytes. This is required for 3D region
                                                    ///< copies where ::ze_copy_region_t::depth is not 0, otherwise it's
                                                    ///< ignored.
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
    uint32_t srcPitch,                              ///< [in] source pitch in bytes
    uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                    ///< copies where ::ze_copy_region_t::depth is not 0, otherwise it's
                                                    ///< ignored.
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a image.
/// 
/// @details
///     - Images format descriptors for both source and destination images must
///       be the same.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyImage**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hDstImage`
///         + `nullptr == hSrcImage`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendImageCopy(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Region descriptor
typedef struct _ze_image_region_t
{
    uint32_t originX;                               ///< [in] The origin x offset for region in pixels
    uint32_t originY;                               ///< [in] The origin y offset for region in pixels
    uint32_t originZ;                               ///< [in] The origin z offset for region in pixels
    uint32_t width;                                 ///< [in] The region width relative to origin in pixels
    uint32_t height;                                ///< [in] The region height relative to origin in pixels
    uint32_t depth;                                 ///< [in] The region depth relative to origin. For 1D or 2D images, set
                                                    ///< this to 1.

} ze_image_region_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a region of a image to another image.
/// 
/// @details
///     - The region width and height for both src and dst must be same. The
///       origins can be different.
///     - The src and dst regions cannot be overlapping.
///     - Images format descriptors for both source and destination images must
///       be the same.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hDstImage`
///         + `nullptr == hSrcImage`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_OVERLAPPING_REGIONS
__ze_api_export ze_result_t __zecall
zeCommandListAppendImageCopyRegion(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
    const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies from a image to device or shared memory.
/// 
/// @details
///     - The memory pointed to by dstptr must be accessible by the device on
///       which the command list is created.
///     - Media formats are not supported for this function.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueReadImage
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hSrcImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendImageCopyToMemory(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies to a image from device or shared memory.
/// 
/// @details
///     - The memory pointed to by srcptr must be accessible by the device on
///       which the command list is created.
///     - Media formats are not supported for this function.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueWriteImage
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hDstImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == srcptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendImageCopyFromMemory(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Asynchronously prefetches shared memory to the device associated with
///        the specified command list
/// 
/// @details
///     - This is a hint to improve performance only and is not required for
///       correctness.
///     - Only prefetching to the device associated with the specified command
///       list is supported.
///       Prefetching to the host or to a peer device is not supported.
///     - Prefetching may not be supported for all allocation types for all devices.
///       If memory prefetching is not supported for the specified memory range
///       the prefetch hint may be ignored.
///     - Prefetching may only be supported at a device-specific granularity,
///       such as at a page boundary.
///       In this case, the memory range may be expanded such that the start and
///       end of the range satisfy granularity requirements.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueSVMMigrateMem
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
__ze_api_export ze_result_t __zecall
zeCommandListAppendMemoryPrefetch(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
    size_t size                                     ///< [in] size in bytes of the memory range to prefetch
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported memory advice hints
typedef enum _ze_memory_advice_t
{
    ZE_MEMORY_ADVICE_SET_READ_MOSTLY = 0,           ///< hint that memory will be read from frequently and written to rarely
    ZE_MEMORY_ADVICE_CLEAR_READ_MOSTLY,             ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_READ_MOSTLY
    ZE_MEMORY_ADVICE_SET_PREFERRED_LOCATION,        ///< hint that the preferred memory location is the specified device
    ZE_MEMORY_ADVICE_CLEAR_PREFERRED_LOCATION,      ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_PREFERRED_LOCATION
    ZE_MEMORY_ADVICE_SET_ACCESSED_BY,               ///< hint that memory will be accessed by the specified device
    ZE_MEMORY_ADVICE_CLEAR_ACCESSED_BY,             ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_ACCESSED_BY
    ZE_MEMORY_ADVICE_SET_NON_ATOMIC_MOSTLY,         ///< hints that memory will mostly be accessed non-atomically
    ZE_MEMORY_ADVICE_CLEAR_NON_ATOMIC_MOSTLY,       ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_NON_ATOMIC_MOSTLY
    ZE_MEMORY_ADVICE_BIAS_CACHED,                   ///< hints that memory should be cached
    ZE_MEMORY_ADVICE_BIAS_UNCACHED,                 ///< hints that memory should be not be cached

} ze_memory_advice_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides advice about the use of a shared memory range
/// 
/// @details
///     - Memory advice is a performance hint only and is not required for
///       functional correctness.
///     - Memory advice can be used to override driver heuristics to explicitly
///       control shared memory behavior.
///     - Not all memory advice hints may be supported for all allocation types
///       for all devices.
///       If a memory advice hint is not supported by the device it will be ignored.
///     - Memory advice may only be supported at a device-specific granularity,
///       such as at a page boundary.
///       In this case, the memory range may be expanded such that the start and
///       end of the range satisfy granularity requirements.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + advice
__ze_api_export ze_result_t __zecall
zeCommandListAppendMemAdvise(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    );

#pragma endregion
#pragma region event
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_event_pool_desc_t
typedef enum _ze_event_pool_desc_version_t
{
    ZE_EVENT_POOL_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0
    ZE_EVENT_POOL_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< latest known version

} ze_event_pool_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported event pool creation flags
typedef enum _ze_event_pool_flag_t
{
    ZE_EVENT_POOL_FLAG_DEFAULT = 0,                 ///< signals and waits visible to the entire device and peer devices
    ZE_EVENT_POOL_FLAG_HOST_VISIBLE = ZE_BIT(0),    ///< signals and waits are also visible to host
    ZE_EVENT_POOL_FLAG_IPC = ZE_BIT(1),             ///< signals and waits may be shared across processes
    ZE_EVENT_POOL_FLAG_TIMESTAMP = ZE_BIT(2),       ///< Indicates all events in pool will contain timestamp information that
                                                    ///< can be queried using ::zeEventGetTimestamp

} ze_event_pool_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event pool descriptor
typedef struct _ze_event_pool_desc_t
{
    ze_event_pool_desc_version_t version;           ///< [in] ::ZE_EVENT_POOL_DESC_VERSION_CURRENT
    ze_event_pool_flag_t flags;                     ///< [in] creation flags
    uint32_t count;                                 ///< [in] number of events within the pool

} ze_event_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a pool for a set of event(s) for the driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phEventPool`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_EVENT_POOL_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeEventPoolCreate(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const ze_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
    uint32_t numDevices,                            ///< [in] number of device handles
    ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                    ///< have visibility to the event pool.
                                                    ///< if nullptr, then event pool is visible to all devices supported by the
                                                    ///< driver instance.
    ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event pool object.
/// 
/// @details
///     - The application is responsible for destroying all event handles
///       created from the pool before destroying the pool itself
///     - The application is responsible for making sure the device is not
///       currently referencing the any event within the pool before it is
///       deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this event pool
///     - The application may **not** call this function from simultaneous
///       threads with the same event pool handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeEventPoolDestroy(
    ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_event_desc_t
typedef enum _ze_event_desc_version_t
{
    ZE_EVENT_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),///< version 1.0
    ZE_EVENT_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),///< latest known version

} ze_event_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported event scope flags
typedef enum _ze_event_scope_flag_t
{
    ZE_EVENT_SCOPE_FLAG_NONE = 0,                   ///< execution synchronization only; no cache hierarchies are flushed or
                                                    ///< invalidated
    ZE_EVENT_SCOPE_FLAG_SUBDEVICE = ZE_BIT(0),      ///< cache hierarchies are flushed or invalidated sufficient for local
                                                    ///< sub-device access
    ZE_EVENT_SCOPE_FLAG_DEVICE = ZE_BIT(1),         ///< cache hierarchies are flushed or invalidated sufficient for global
                                                    ///< device access and peer device access
    ZE_EVENT_SCOPE_FLAG_HOST = ZE_BIT(2),           ///< cache hierarchies are flushed or invalidated sufficient for device and
                                                    ///< host access

} ze_event_scope_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event descriptor
typedef struct _ze_event_desc_t
{
    ze_event_desc_version_t version;                ///< [in] ::ZE_EVENT_DESC_VERSION_CURRENT
    uint32_t index;                                 ///< [in] index of the event within the pool; must be less-than the count
                                                    ///< specified during pool creation
    ze_event_scope_flag_t signal;                   ///< [in] defines the scope of relevant cache hierarchies to flush on a
                                                    ///< signal action before the event is triggered
    ze_event_scope_flag_t wait;                     ///< [in] defines the scope of relevant cache hierarchies to invalidate on
                                                    ///< a wait action after the event is complete

} ze_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event on the device.
/// 
/// @details
///     - Multiple events cannot be created using the same location within the
///       same pool.
///     - The application may **not** call this function from simultaneous
///       threads with the same event pool handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateUserEvent**
///     - vkCreateEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phEvent`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_EVENT_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->signal
///         + desc->wait
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
__ze_api_export ze_result_t __zecall
zeEventCreate(
    ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event object.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the event before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this event
///     - The application may **not** call this function from simultaneous
///       threads with the same event handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseEvent**
///     - vkDestroyEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeEventDestroy(
    ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets an IPC event pool handle for the specified event handle that can
///        be shared with another process.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phIpc`
__ze_api_export ze_result_t __zecall
zeEventPoolGetIpcHandle(
    ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
    ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC event pool handle to retrieve an event pool handle from
///        another process.
/// 
/// @details
///     - The event handle in this process should not be freed with
///       ::zeEventPoolDestroy, but rather with ::zeEventPoolCloseIpcHandle.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEventPool`
__ze_api_export ze_result_t __zecall
zeEventPoolOpenIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver to associate with the IPC event pool handle
    ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
    ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC event handle in the current process.
/// 
/// @details
///     - Closes an IPC event handle by destroying events that were opened in
///       this process using ::zeEventPoolOpenIpcHandle.
///     - The application may **not** call this function from simultaneous
///       threads with the same event pool handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
__ze_api_export ze_result_t __zecall
zeEventPoolCloseIpcHandle(
    ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a signal of the event from the device into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clSetUserEventStatus**
///     - vkCmdSetEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendSignalEvent(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends wait on event(s) on the device into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvents`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendWaitOnEvents(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
    ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handle of the events to wait on before
                                                    ///< continuing
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Signals a event from host.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clSetUserEventStatus
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeEventHostSignal(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on an event to be signaled.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clWaitForEvents
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_NOT_READY
///         + timeout expired
__ze_api_export ze_result_t __zecall
zeEventHostSynchronize(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                    ///< if UINT32_MAX, then function will not return until complete or device
                                                    ///< is lost.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries an event object's status.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clGetEventInfo**
///     - vkGetEventStatus
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_NOT_READY
///         + not signaled
__ze_api_export ze_result_t __zecall
zeEventQueryStatus(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset an event back to not signaled state
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkResetEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendEventReset(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset an event back to not signaled state
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkResetEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeEventHostReset(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported timestamp types
typedef enum _ze_event_timestamp_type_t
{
    ZE_EVENT_TIMESTAMP_GLOBAL_START = 0,            ///< wall-clock time start in GPU clocks for event. Data is uint64_t.
    ZE_EVENT_TIMESTAMP_GLOBAL_END,                  ///< wall-clock time end in GPU clocks for event.Data is uint64_t.
    ZE_EVENT_TIMESTAMP_CONTEXT_START,               ///< context time start in GPU clocks for event.  Only includes time while
                                                    ///< HW context is actively running on GPU. Data is uint64_t.
    ZE_EVENT_TIMESTAMP_CONTEXT_END,                 ///< context time end in GPU clocks for event.  Only includes time while HW
                                                    ///< context is actively running on GPU. Data is uint64_t.

} ze_event_timestamp_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Query timestamp information associated with an event. Event must come
///        from an event pool that was created using
///        ::ZE_EVENT_POOL_FLAG_TIMESTAMP flag.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + timestampType
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeEventGetTimestamp(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    ze_event_timestamp_type_t timestampType,        ///< [in] specifies timestamp type to query for that is associated with
                                                    ///< hEvent.
    void* dstptr                                    ///< [in,out] pointer to memory for where timestamp will be written to. The
                                                    ///< size of timestamp is specified in the ::ze_event_timestamp_type_t
                                                    ///< definition.
    );

#pragma endregion
#pragma region fence
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_fence_desc_t
typedef enum _ze_fence_desc_version_t
{
    ZE_FENCE_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),///< version 1.0
    ZE_FENCE_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),///< latest known version

} ze_fence_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported fence creation flags
typedef enum _ze_fence_flag_t
{
    ZE_FENCE_FLAG_NONE = 0,                         ///< default behavior

} ze_fence_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fence descriptor
typedef struct _ze_fence_desc_t
{
    ze_fence_desc_version_t version;                ///< [in] ::ZE_FENCE_DESC_VERSION_CURRENT
    ze_fence_flag_t flags;                          ///< [in] creation flags

} ze_fence_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a fence object on the device's command queue.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkCreateFence**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phFence`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_FENCE_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeFenceCreate(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a fence object.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the fence before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this fence
///     - The application may **not** call this function from simultaneous
///       threads with the same fence handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkDestroyFence**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFence`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeFenceDestroy(
    ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on a fence to be signaled.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkWaitForFences**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFence`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_NOT_READY
///         + timeout expired
__ze_api_export ze_result_t __zecall
zeFenceHostSynchronize(
    ze_fence_handle_t hFence,                       ///< [in] handle of the fence
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                    ///< if UINT32_MAX, then function will not return until complete or device
                                                    ///< is lost.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries a fence object's status.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkGetFenceStatus**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFence`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_NOT_READY
///         + not signaled
__ze_api_export ze_result_t __zecall
zeFenceQueryStatus(
    ze_fence_handle_t hFence                        ///< [in] handle of the fence
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a fence back to the not signaled state.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkResetFences**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFence`
__ze_api_export ze_result_t __zecall
zeFenceReset(
    ze_fence_handle_t hFence                        ///< [in] handle of the fence
    );

#pragma endregion
#pragma region image
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_image_desc_t
typedef enum _ze_image_desc_version_t
{
    ZE_IMAGE_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),///< version 1.0
    ZE_IMAGE_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),///< latest known version

} ze_image_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image creation flags
typedef enum _ze_image_flag_t
{
    ZE_IMAGE_FLAG_PROGRAM_READ = ZE_BIT( 0 ),       ///< programs will read contents
    ZE_IMAGE_FLAG_PROGRAM_WRITE = ZE_BIT( 1 ),      ///< programs will write contents
    ZE_IMAGE_FLAG_BIAS_CACHED = ZE_BIT( 2 ),        ///< device should cache contents
    ZE_IMAGE_FLAG_BIAS_UNCACHED = ZE_BIT( 3 ),      ///< device should not cache contents

} ze_image_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image types
typedef enum _ze_image_type_t
{
    ZE_IMAGE_TYPE_1D,                               ///< 1D
    ZE_IMAGE_TYPE_1DARRAY,                          ///< 1D array
    ZE_IMAGE_TYPE_2D,                               ///< 2D
    ZE_IMAGE_TYPE_2DARRAY,                          ///< 2D array
    ZE_IMAGE_TYPE_3D,                               ///< 3D
    ZE_IMAGE_TYPE_BUFFER,                           ///< Buffer

} ze_image_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image format layouts
typedef enum _ze_image_format_layout_t
{
    ZE_IMAGE_FORMAT_LAYOUT_8,                       ///< 8-bit single component layout
    ZE_IMAGE_FORMAT_LAYOUT_16,                      ///< 16-bit single component layout
    ZE_IMAGE_FORMAT_LAYOUT_32,                      ///< 32-bit single component layout
    ZE_IMAGE_FORMAT_LAYOUT_8_8,                     ///< 2-component 8-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_8_8_8_8,                 ///< 4-component 8-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_16_16,                   ///< 2-component 16-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_16_16_16_16,             ///< 4-component 16-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_32_32,                   ///< 2-component 32-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_32_32_32_32,             ///< 4-component 32-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_10_10_10_2,              ///< 4-component 10_10_10_2 layout
    ZE_IMAGE_FORMAT_LAYOUT_11_11_10,                ///< 3-component 11_11_10 layout
    ZE_IMAGE_FORMAT_LAYOUT_5_6_5,                   ///< 3-component 5_6_5 layout
    ZE_IMAGE_FORMAT_LAYOUT_5_5_5_1,                 ///< 4-component 5_5_5_1 layout
    ZE_IMAGE_FORMAT_LAYOUT_4_4_4_4,                 ///< 4-component 4_4_4_4 layout
    ZE_IMAGE_FORMAT_LAYOUT_Y8,                      ///< Media Format: Y8. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_NV12,                    ///< Media Format: NV12. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_YUYV,                    ///< Media Format: YUYV. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_VYUY,                    ///< Media Format: VYUY. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_YVYU,                    ///< Media Format: YVYU. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_UYVY,                    ///< Media Format: UYVY. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_AYUV,                    ///< Media Format: AYUV. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_P010,                    ///< Media Format: P010. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_Y410,                    ///< Media Format: Y410. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_P012,                    ///< Media Format: P012. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_Y16,                     ///< Media Format: Y16. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_P016,                    ///< Media Format: P016. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_Y216,                    ///< Media Format: Y216. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_P216,                    ///< Media Format: P216. Format type and swizzle is ignored for this.

} ze_image_format_layout_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image format types
typedef enum _ze_image_format_type_t
{
    ZE_IMAGE_FORMAT_TYPE_UINT,                      ///< Unsigned integer
    ZE_IMAGE_FORMAT_TYPE_SINT,                      ///< Signed integer
    ZE_IMAGE_FORMAT_TYPE_UNORM,                     ///< Unsigned normalized integer
    ZE_IMAGE_FORMAT_TYPE_SNORM,                     ///< Signed normalized integer
    ZE_IMAGE_FORMAT_TYPE_FLOAT,                     ///< Float

} ze_image_format_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image format component swizzle into channel
typedef enum _ze_image_format_swizzle_t
{
    ZE_IMAGE_FORMAT_SWIZZLE_R,                      ///< Red component
    ZE_IMAGE_FORMAT_SWIZZLE_G,                      ///< Green component
    ZE_IMAGE_FORMAT_SWIZZLE_B,                      ///< Blue component
    ZE_IMAGE_FORMAT_SWIZZLE_A,                      ///< Alpha component
    ZE_IMAGE_FORMAT_SWIZZLE_0,                      ///< Zero
    ZE_IMAGE_FORMAT_SWIZZLE_1,                      ///< One
    ZE_IMAGE_FORMAT_SWIZZLE_X,                      ///< Don't care

} ze_image_format_swizzle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Image format descriptor
typedef struct _ze_image_format_desc_t
{
    ze_image_format_layout_t layout;                ///< [in] image format component layout
    ze_image_format_type_t type;                    ///< [in] image format type. Media formats can't be used for
                                                    ///< ::ZE_IMAGE_TYPE_BUFFER.
    ze_image_format_swizzle_t x;                    ///< [in] image component swizzle into channel x
    ze_image_format_swizzle_t y;                    ///< [in] image component swizzle into channel y
    ze_image_format_swizzle_t z;                    ///< [in] image component swizzle into channel z
    ze_image_format_swizzle_t w;                    ///< [in] image component swizzle into channel w

} ze_image_format_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Image descriptor
typedef struct _ze_image_desc_t
{
    ze_image_desc_version_t version;                ///< [in] ::ZE_IMAGE_DESC_VERSION_CURRENT
    ze_image_flag_t flags;                          ///< [in] creation flags
    ze_image_type_t type;                           ///< [in] image type
    ze_image_format_desc_t format;                  ///< [in] image format
    uint64_t width;                                 ///< [in] width in pixels for ::ze_image_type_t::1D/2D/3D and bytes for
                                                    ///< Buffer, see ::ze_device_image_properties_t::maxImageDims1D/2D/3D and
                                                    ///< maxImageBufferSize.
    uint32_t height;                                ///< [in] height in pixels (2D or 3D only), see
                                                    ///< ::ze_device_image_properties_t::maxImageDims2D/3D
    uint32_t depth;                                 ///< [in] depth in pixels (3D only), see
                                                    ///< ::ze_device_image_properties_t::maxImageDims3D
    uint32_t arraylevels;                           ///< [in] array levels (array types only), see
                                                    ///< ::ze_device_image_properties_t::maxImageArraySlices
    uint32_t miplevels;                             ///< [in] mipmap levels (must be 0)

} ze_image_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_image_properties_t
typedef enum _ze_image_properties_version_t
{
    ZE_IMAGE_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),  ///< version 1.0
    ZE_IMAGE_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),  ///< latest known version

} ze_image_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported sampler filtering flags
typedef enum _ze_image_sampler_filter_flags_t
{
    ZE_IMAGE_SAMPLER_FILTER_FLAGS_NONE = 0,         ///< device does not support filtering
    ZE_IMAGE_SAMPLER_FILTER_FLAGS_POINT = ZE_BIT(0),///< device supports point filtering
    ZE_IMAGE_SAMPLER_FILTER_FLAGS_LINEAR = ZE_BIT(1),   ///< device supports linear filtering

} ze_image_sampler_filter_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Image properties
typedef struct _ze_image_properties_t
{
    ze_image_properties_version_t version;          ///< [in] ::ZE_IMAGE_PROPERTIES_VERSION_CURRENT
    ze_image_sampler_filter_flags_t samplerFilterFlags; ///< [out] supported sampler filtering

} ze_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves supported properties of an image.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == pImageProperties`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_IMAGE_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///         + desc->type
__ze_api_export ze_result_t __zecall
zeImageGetProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a image object on the device.
/// 
/// @details
///     - The image is only visible to the device on which it was created.
///     - The image can be copied to another device using the
///       ::::zeCommandListAppendImageCopy functions.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clCreateImage
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phImage`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_IMAGE_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///         + desc->type
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeImageCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a image object.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the image before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this image
///     - The application may **not** call this function from simultaneous
///       threads with the same image handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeImageDestroy(
    ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
    );

#pragma endregion
#pragma region memory
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_mem_alloc_desc_t
typedef enum _ze_device_mem_alloc_desc_version_t
{
    ZE_DEVICE_MEM_ALLOC_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ), ///< version 1.0
    ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ), ///< latest known version

} ze_device_mem_alloc_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported memory allocation flags
typedef enum _ze_device_mem_alloc_flag_t
{
    ZE_DEVICE_MEM_ALLOC_FLAG_DEFAULT = 0,           ///< implicit default behavior; uses driver-based heuristics
    ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_CACHED = ZE_BIT( 0 ), ///< device should cache allocation
    ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_UNCACHED = ZE_BIT( 1 ),   ///< device should not cache allocation (UC)

} ze_device_mem_alloc_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device mem alloc descriptor
typedef struct _ze_device_mem_alloc_desc_t
{
    ze_device_mem_alloc_desc_version_t version;     ///< [in] ::ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT
    ze_device_mem_alloc_flag_t flags;               ///< [in] flags specifying additional allocation controls
    uint32_t ordinal;                               ///< [in] ordinal of the device's local memory to allocate from;
                                                    ///< must be less than the count returned from ::zeDeviceGetMemoryProperties

} ze_device_mem_alloc_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_host_mem_alloc_desc_t
typedef enum _ze_host_mem_alloc_desc_version_t
{
    ZE_HOST_MEM_ALLOC_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0
    ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< latest known version

} ze_host_mem_alloc_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported host memory allocation flags
typedef enum _ze_host_mem_alloc_flag_t
{
    ZE_HOST_MEM_ALLOC_FLAG_DEFAULT = 0,             ///< implicit default behavior; uses driver-based heuristics
    ZE_HOST_MEM_ALLOC_FLAG_BIAS_CACHED = ZE_BIT( 0 ),   ///< host should cache allocation
    ZE_HOST_MEM_ALLOC_FLAG_BIAS_UNCACHED = ZE_BIT( 1 ), ///< host should not cache allocation (UC)
    ZE_HOST_MEM_ALLOC_FLAG_BIAS_WRITE_COMBINED = ZE_BIT( 2 ),   ///< host memory should be allocated write-combined (WC)

} ze_host_mem_alloc_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Host mem alloc descriptor
typedef struct _ze_host_mem_alloc_desc_t
{
    ze_host_mem_alloc_desc_version_t version;       ///< [in] ::ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT
    ze_host_mem_alloc_flag_t flags;                 ///< [in] flags specifying additional allocation controls

} ze_host_mem_alloc_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that is shared between the host and one or more
///        devices
/// 
/// @details
///     - Shared allocations share ownership between the host and one or more
///       devices.
///     - Shared allocations may optionally be associated with a device by
///       passing a handle to the device.
///     - Devices supporting only single-device shared access capabilities may
///       access shared memory associated with the device.
///       For these devices, ownership of the allocation is shared between the
///       host and the associated device only.
///     - Passing nullptr as the device handle does not associate the shared
///       allocation with any device.
///       For allocations with no associated device, ownership of the allocation
///       is shared between the host and all devices supporting cross-device
///       shared access capabilities.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == device_desc`
///         + `nullptr == host_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT < device_desc->version`
///         + `::ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT < host_desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + device_desc->flags
///         + host_desc->flags
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDriverAllocSharedMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device mem alloc descriptor
    const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host mem alloc descriptor
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    ze_device_handle_t hDevice,                     ///< [in][optional] device handle to associate with
    void** pptr                                     ///< [out] pointer to shared allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory specific to a device
/// 
/// @details
///     - A device allocation is owned by a specific device.
///     - In general, a device allocation may only be accessed by the device
///       that owns it.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == device_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT < device_desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + device_desc->flags
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDriverAllocDeviceMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device mem alloc descriptor
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    void** pptr                                     ///< [out] pointer to device allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates host memory
/// 
/// @details
///     - A host allocation is owned by the host process.
///     - Host allocations are accessible by the host and all devices within the
///       driver driver.
///     - Host allocations are frequently used as staging areas to transfer data
///       to or from devices.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == host_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT < host_desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + host_desc->flags
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDriverAllocHostMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host mem alloc descriptor
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** pptr                                     ///< [out] pointer to host allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated host memory, device memory, or shared memory
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the memory before it is freed
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this memory
///     - The application may **not** call this function from simultaneous
///       threads with the same pointer.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
__ze_api_export ze_result_t __zecall
zeDriverFreeMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    void* ptr                                       ///< [in][release] pointer to memory to free
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_memory_allocation_properties_t
typedef enum _ze_memory_allocation_properties_version_t
{
    ZE_MEMORY_ALLOCATION_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),  ///< version 1.0
    ZE_MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),  ///< latest known version

} ze_memory_allocation_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory allocation type
typedef enum _ze_memory_type_t
{
    ZE_MEMORY_TYPE_UNKNOWN = 0,                     ///< the memory pointed to is of unknown type
    ZE_MEMORY_TYPE_HOST,                            ///< the memory pointed to is a host allocation
    ZE_MEMORY_TYPE_DEVICE,                          ///< the memory pointed to is a device allocation
    ZE_MEMORY_TYPE_SHARED,                          ///< the memory pointed to is a shared ownership allocation

} ze_memory_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory allocation properties queried using
///        ::zeDriverGetMemAllocProperties
typedef struct _ze_memory_allocation_properties_t
{
    ze_memory_allocation_properties_version_t version;  ///< [in] ::ZE_MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT
    ze_memory_type_t type;                          ///< [out] type of allocated memory
    uint64_t id;                                    ///< [out] identifier for this allocation

} ze_memory_allocation_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of a memory allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pMemAllocProperties`
__ze_api_export ze_result_t __zecall
zeDriverGetMemAllocProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] memory pointer to query
    ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
    ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the base address and/or size of an allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
__ze_api_export ze_result_t __zecall
zeDriverGetMemAddressRange(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] memory pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an IPC memory handle for the specified allocation in the
///        sending process
/// 
/// @details
///     - Takes a pointer to the base of a device memory allocation and exports
///       it for use in another process.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pIpcHandle`
__ze_api_export ze_result_t __zecall
zeDriverGetMemIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] pointer to the device memory allocation
    ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported IPC memory flags
typedef enum _ze_ipc_memory_flag_t
{
    ZE_IPC_MEMORY_FLAG_NONE = 0,                    ///< No special flags

} ze_ipc_memory_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
///        process
/// 
/// @details
///     - Takes an IPC memory handle from a sending process and associates it
///       with a device pointer usable in this process.
///     - The device pointer in this process should not be freed with
///       ::zeDriverFreeMem, but rather with ::zeDriverCloseMemIpcHandle.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + flags
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pptr`
__ze_api_export ze_result_t __zecall
zeDriverOpenMemIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    ze_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** pptr                                     ///< [out] pointer to device allocation in this process
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC memory handle in a receiving process
/// 
/// @details
///     - Closes an IPC memory handle by unmapping memory that was opened in
///       this process using ::zeDriverOpenMemIpcHandle.
///     - The application may **not** call this function from simultaneous
///       threads with the same pointer.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
__ze_api_export ze_result_t __zecall
zeDriverCloseMemIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr                                 ///< [in][release] pointer to device allocation in this process
    );

#pragma endregion
#pragma region module
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_module_desc_t
typedef enum _ze_module_desc_version_t
{
    ZE_MODULE_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0
    ZE_MODULE_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< latest known version

} ze_module_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported module creation input formats
typedef enum _ze_module_format_t
{
    ZE_MODULE_FORMAT_IL_SPIRV = 0,                  ///< Format is SPIRV IL format
    ZE_MODULE_FORMAT_NATIVE,                        ///< Format is device native format

} ze_module_format_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Specialization constants - User defined constants
typedef struct _ze_module_constants_t
{
    uint32_t numConstants;                          ///< [in] Number of specialization constants.
    const uint32_t* pConstantIds;                   ///< [in] Pointer to array of IDs that is sized to numConstants.
    const uint64_t* pConstantValues;                ///< [in] Pointer to array of values that is sized to numConstants.

} ze_module_constants_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Module descriptor
typedef struct _ze_module_desc_t
{
    ze_module_desc_version_t version;               ///< [in] ::ZE_MODULE_DESC_VERSION_CURRENT
    ze_module_format_t format;                      ///< [in] Module format passed in with pInputModule
    size_t inputSize;                               ///< [in] size of input IL or ISA from pInputModule.
    const uint8_t* pInputModule;                    ///< [in] pointer to IL or ISA
    const char* pBuildFlags;                        ///< [in] string containing compiler flags. See programming guide for build
                                                    ///< flags.
    const ze_module_constants_t* pConstants;        ///< [in] pointer to specialization constants. Valid only for SPIR-V input.
                                                    ///< This must be set to nullptr if no specialization constants are
                                                    ///< provided.

} ze_module_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates module object from an input IL or native binary.
/// 
/// @details
///     - Compiles the module for execution on the device.
///     - The module can only be used on the device on which it was created.
///     - The module can be copied to other devices within the same driver
///       instance by using ::zeModuleGetNativeBinary.
///     - The following build options are supported:
///         + "-ze-opt-disable" - Disable optimizations
///         + "-ze-opt-greater-than-4GB-buffer-required" - Use 64-bit offset
///           calculations for buffers.
///         + "-ze-opt-large-register-file" - Increase number of registers
///           available to threads.
///     - A build log can optionally be returned to the caller. The caller is
///       responsible for destroying build log using ::zeModuleBuildLogDestroy.
///     - The module descriptor constants are only supported for SPIR-V
///       specialization constants.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pInputModule`
///         + `nullptr == desc->pBuildFlags`
///         + `nullptr == desc->pConstants`
///         + `nullptr == phModule`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_MODULE_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->format
///     - ::ZE_RESULT_ERROR_INVALID_NATIVE_BINARY
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `0 == desc->inputSize`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_MODULE_BUILD_FAILURE
__ze_api_export ze_result_t __zecall
zeModuleCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
    ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the module before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this module
///     - The application may **not** call this function from simultaneous
///       threads with the same module handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeModuleDestroy(
    ze_module_handle_t hModule                      ///< [in][release] handle of the module
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module build log object
/// 
/// @details
///     - The implementation of this function will immediately free all Host
///       allocations associated with this object
///     - The application may **not** call this function from simultaneous
///       threads with the same build log handle.
///     - The implementation of this function should be lock-free.
///     - This function can be called before or after ::zeModuleDestroy for the
///       associated module.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModuleBuildLog`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeModuleBuildLogDestroy(
    ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves text string for build log.
/// 
/// @details
///     - The caller can pass nullptr for pBuildLog when querying only for size.
///     - The caller must provide memory for build log.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModuleBuildLog`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
__ze_api_export ze_result_t __zecall
zeModuleBuildLogGetString(
    ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [in,out] size of build log string.
    char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve native binary from Module.
/// 
/// @details
///     - The native binary output can be cached to disk and new modules can be
///       later constructed from the cached copy.
///     - The native binary will retain debugging information that is associated
///       with a module.
///     - The caller can pass nullptr for pModuleNativeBinary when querying only
///       for size.
///     - The implementation will copy the native binary into a buffer supplied
///       by the caller.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
__ze_api_export ze_result_t __zecall
zeModuleGetNativeBinary(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve global variable pointer from Module.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pGlobalName`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_INVALID_GLOBAL_NAME
__ze_api_export ze_result_t __zecall
zeModuleGetGlobalPointer(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pGlobalName,                        ///< [in] name of global variable in module
    void** pptr                                     ///< [out] device visible pointer
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve all kernel names in the module.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zeModuleGetKernelNames(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of names available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of names.
                                                    ///< if count is larger than the number of names available, then the driver
                                                    ///< will update the value with the correct number of names available.
    const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_kernel_desc_t
typedef enum _ze_kernel_desc_version_t
{
    ZE_KERNEL_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0
    ZE_KERNEL_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< latest known version

} ze_kernel_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported kernel creation flags
typedef enum _ze_kernel_flag_t
{
    ZE_KERNEL_FLAG_NONE = 0,                        ///< default driver behavior
    ZE_KERNEL_FLAG_FORCE_RESIDENCY,                 ///< force all device allocations to be resident during execution

} ze_kernel_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Kernel descriptor
typedef struct _ze_kernel_desc_t
{
    ze_kernel_desc_version_t version;               ///< [in] ::ZE_KERNEL_DESC_VERSION_CURRENT
    ze_kernel_flag_t flags;                         ///< [in] creation flags
    const char* pKernelName;                        ///< [in] null-terminated name of kernel in module

} ze_kernel_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Create a kernel object from a module by name
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pKernelName`
///         + `nullptr == phKernel`
///         + `nullptr == desc->pKernelName`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_KERNEL_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_NAME
__ze_api_export ze_result_t __zecall
zeKernelCreate(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
    ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a kernel object
/// 
/// @details
///     - All kernels must be destroyed before the module is destroyed.
///     - The application is responsible for making sure the device is not
///       currently referencing the kernel before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this kernel
///     - The application may **not** call this function from simultaneous
///       threads with the same kernel handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeKernelDestroy(
    ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve a function pointer from a module by name
/// 
/// @details
///     - The function pointer is unique for the device on which the module was
///       created.
///     - The function pointer is no longer valid if module is destroyed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFunctionName`
///         + `nullptr == pfnFunction`
///     - ::ZE_RESULT_ERROR_INVALID_FUNCTION_NAME
__ze_api_export ze_result_t __zecall
zeModuleGetFunctionPointer(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
    void** pfnFunction                              ///< [out] pointer to function.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set group size for a kernel
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same kernel handle.
///     - The implementation of this function should be lock-free.
///     - The implementation will copy the group size information into a command
///       list when the function is appended.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION
__ze_api_export ze_result_t __zecall
zeKernelSetGroupSize(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested group size for a kernel given a global size for each
///        dimension.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - This function ignores the group size that is set using
///       ::zeKernelSetGroupSize.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == groupSizeX`
///         + `nullptr == groupSizeY`
///         + `nullptr == groupSizeZ`
///     - ::ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION
__ze_api_export ze_result_t __zecall
zeKernelSuggestGroupSize(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t globalSizeX,                           ///< [in] global width for X dimension
    uint32_t globalSizeY,                           ///< [in] global width for Y dimension
    uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
    uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
    uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
    uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested max group count a cooperative kernel.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == totalGroupCount`
__ze_api_export ze_result_t __zecall
zeKernelSuggestMaxCooperativeGroupCount(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t* totalGroupCount                       ///< [out] recommended total group count.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set kernel argument used on kernel launch.
/// 
/// @details
///     - This function may **not** be called from simultaneous threads with the
///       same function handle.
///     - The implementation of this function should be lock-free.
///     - The implementation will copy the arguments into a command list when
///       the function is appended.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE
__ze_api_export ze_result_t __zecall
zeKernelSetArgumentValue(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Kernel attributes
/// 
/// @remarks
///   _Analogues_
///     - **cl_kernel_exec_info**
typedef enum _ze_kernel_attribute_t
{
    ZE_KERNEL_ATTR_INDIRECT_HOST_ACCESS = 0,        ///< Indicates that the function accesses host allocations indirectly
                                                    ///< (default: false, type: bool_t)
    ZE_KERNEL_ATTR_INDIRECT_DEVICE_ACCESS,          ///< Indicates that the function accesses device allocations indirectly
                                                    ///< (default: false, type: bool_t)
    ZE_KERNEL_ATTR_INDIRECT_SHARED_ACCESS,          ///< Indicates that the function accesses shared allocations indirectly
                                                    ///< (default: false, type: bool_t)
    ZE_KERNEL_ATTR_SOURCE_ATTRIBUTE,                ///< Declared kernel attributes (i.e. can be specified with __attribute__
                                                    ///< in runtime language). (type: char[]) Returned as a null-terminated
                                                    ///< string and each attribute is separated by a space.
                                                    ///< ::zeKernelSetAttribute is not supported for this.

} ze_kernel_attribute_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets a kernel attribute
/// 
/// @details
///     - This function may **not** be called from simultaneous threads with the
///       same function handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clSetKernelExecInfo**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + attr
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE
__ze_api_export ze_result_t __zecall
zeKernelSetAttribute(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_kernel_attribute_t attr,                     ///< [in] attribute to set
    uint32_t size,                                  ///< [in] size in bytes of kernel attribute value.
    const void* pValue                              ///< [in][optional] pointer to attribute value.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets a kernel attribute
/// 
/// @details
///     - This function may **not** be called from simultaneous threads with the
///       same function handle.
///     - The implementation of this function should be lock-free.
///     - The caller sets pValue to nullptr when querying only for size.
///     - The caller must provide memory for pValue querying when querying size.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + attr
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE
__ze_api_export ze_result_t __zecall
zeKernelGetAttribute(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_kernel_attribute_t attr,                     ///< [in] attribute to get. Documentation for ::ze_kernel_attribute_t for
                                                    ///< return type information for pValue.
    uint32_t* pSize,                                ///< [in,out] size in bytes needed for kernel attribute value. If pValue is
                                                    ///< nullptr then the size needed for pValue memory will be written to
                                                    ///< pSize. Only need to query size for arbitrary sized attributes.
    void* pValue                                    ///< [in,out][optional] pointer to attribute value result.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred Intermediate cache configuration for a kernel.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same kernel handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + CacheConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
__ze_api_export ze_result_t __zecall
zeKernelSetIntermediateCacheConfig(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_kernel_properties_t
typedef enum _ze_kernel_properties_version_t
{
    ZE_KERNEL_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ), ///< version 1.0
    ZE_KERNEL_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ), ///< latest known version

} ze_kernel_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_KERNEL_NAME
/// @brief Maximum device name string size
#define ZE_MAX_KERNEL_NAME  256
#endif // ZE_MAX_KERNEL_NAME

///////////////////////////////////////////////////////////////////////////////
/// @brief Kernel properties
typedef struct _ze_kernel_properties_t
{
    ze_kernel_properties_version_t version;         ///< [in] ::ZE_KERNEL_PROPERTIES_VERSION_CURRENT
    char name[ZE_MAX_KERNEL_NAME];                  ///< [out] Kernel name
    uint32_t numKernelArgs;                         ///< [out] number of kernel arguments.
    uint32_t requiredGroupSizeX;                    ///< [out] required group size in the X dimension,
                                                    ///< or zero if there is no required group size
    uint32_t requiredGroupSizeY;                    ///< [out] required group size in the Y dimension,
                                                    ///< or zero if there is no required group size
    uint32_t requiredGroupSizeZ;                    ///< [out] required group size in the Z dimension,
                                                    ///< or zero if there is no required group size
    uint32_t requiredNumSubGroups;                  ///< [out] required number of subgroups per thread group,
                                                    ///< or zero if there is no required number of subgroups
    uint32_t requiredSubgroupSize;                  ///< [out] required subgroup size,
                                                    ///< or zero if there is no required subgroup size
    uint32_t maxSubgroupSize;                       ///< [out] maximum subgroup size
    uint32_t maxNumSubgroups;                       ///< [out] maximum number of subgroups per work group
    uint32_t localMemSize;                          ///< [out] local memory size used by each thread.
    uint32_t privateMemSize;                        ///< [out] private memory size allocated by compiler used by each thread.

} ze_kernel_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve kernel properties.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pKernelProperties`
__ze_api_export ze_result_t __zecall
zeKernelGetProperties(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Kernel dispatch group count.
typedef struct _ze_group_count_t
{
    uint32_t groupCountX;                           ///< [in] number of thread groups in X dimension
    uint32_t groupCountY;                           ///< [in] number of thread groups in Y dimension
    uint32_t groupCountZ;                           ///< [in] number of thread groups in Z dimension

} ze_group_count_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel over one or more work groups.
/// 
/// @details
///     - This may **only** be called for a command list created with command
///       queue group ordinal that supports compute.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLaunchFuncArgs`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendLaunchKernel(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel cooperatively over one or more work groups.
/// 
/// @details
///     - This may **only** be called for a command list created with command
///       queue group ordinal that supports compute.
///     - This may only be used for a command list that are submitted to command
///       queue with cooperative flag set.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
///     - Use ::zeKernelSuggestMaxCooperativeGroupCount to recommend max group
///       count for device for cooperative functions that device supports.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLaunchFuncArgs`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendLaunchCooperativeKernel(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel over one or more work groups using indirect arguments.
/// 
/// @details
///     - The launch arguments need to be device visible.
///     - The launch arguments buffer may not be reused until the function has
///       completed on the device.
///     - This may **only** be called for a command list created with command
///       queue group ordinal that supports compute.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLaunchArgumentsBuffer`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendLaunchKernelIndirect(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                    ///< arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch multiple kernels over one or more work groups using an array of
///        indirect arguments.
/// 
/// @details
///     - The array of launch arguments need to be device visible.
///     - The array of launch arguments buffer may not be reused until the
///       kernel has completed on the device.
///     - This may **only** be called for a command list created with command
///       queue group ordinal that supports compute.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phKernels`
///         + `nullptr == pCountBuffer`
///         + `nullptr == pLaunchArgumentsBuffer`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandListAppendLaunchMultipleKernelsIndirect(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
    ze_kernel_handle_t* phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
    const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                    ///< number of kernels to launch; value must be less-than or equal-to
                                                    ///< numKernels
    const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                    ///< a contiguous array of thread group launch arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    );

#pragma endregion
#pragma region residency
///////////////////////////////////////////////////////////////////////////////
/// @brief Makes memory resident for the device.
/// 
/// @details
///     - If the application does not properly manage residency then the device
///       may experience unrecoverable page-faults.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDeviceMakeMemoryResident(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allows memory to be evicted from the device.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the memory before it is evicted
///     - Memory is always implicitly evicted if it is resident when freed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDeviceEvictMemory(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to evict
    size_t size                                     ///< [in] size in bytes to evict
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Makes image resident for the device.
/// 
/// @details
///     - If the application does not properly manage residency then the device
///       may experience unrecoverable page-faults.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDeviceMakeImageResident(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_image_handle_t hImage                        ///< [in] handle of image to make resident
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allows image to be evicted from the device.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the memory before it is evicted
///     - An image is always implicitly evicted if it is resident when
///       destroyed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDeviceEvictImage(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_image_handle_t hImage                        ///< [in] handle of image to make evict
    );

#pragma endregion
#pragma region sampler
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_sampler_desc_t
typedef enum _ze_sampler_desc_version_t
{
    ZE_SAMPLER_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),  ///< version 1.0
    ZE_SAMPLER_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),  ///< latest known version

} ze_sampler_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sampler addressing modes
typedef enum _ze_sampler_address_mode_t
{
    ZE_SAMPLER_ADDRESS_MODE_NONE = 0,               ///< No coordinate modifications for out-of-bounds image access.
    ZE_SAMPLER_ADDRESS_MODE_REPEAT,                 ///< Out-of-bounds coordinates are wrapped back around.
    ZE_SAMPLER_ADDRESS_MODE_CLAMP,                  ///< Out-of-bounds coordinates are clamped to edge.
    ZE_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,        ///< Out-of-bounds coordinates are clamped to border color which is (0.0f,
                                                    ///< 0.0f, 0.0f, 0.0f) if image format swizzle contains alpha, otherwise
                                                    ///< (0.0f, 0.0f, 0.0f, 1.0f).
    ZE_SAMPLER_ADDRESS_MODE_MIRROR,                 ///< Out-of-bounds coordinates are mirrored starting from edge.

} ze_sampler_address_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sampler filtering modes
typedef enum _ze_sampler_filter_mode_t
{
    ZE_SAMPLER_FILTER_MODE_NEAREST = 0,             ///< No coordinate modifications for out of bounds image access.
    ZE_SAMPLER_FILTER_MODE_LINEAR,                  ///< Out-of-bounds coordinates are wrapped back around.

} ze_sampler_filter_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sampler descriptor
typedef struct _ze_sampler_desc_t
{
    ze_sampler_desc_version_t version;              ///< [in] ::ZE_SAMPLER_DESC_VERSION_CURRENT
    ze_sampler_address_mode_t addressMode;          ///< [in] Sampler addressing mode to determine how out-of-bounds
                                                    ///< coordinates are handled.
    ze_sampler_filter_mode_t filterMode;            ///< [in] Sampler filter mode to determine how samples are filtered.
    ze_bool_t isNormalized;                         ///< [in] Are coordinates normalized [0, 1] or not.

} ze_sampler_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates sampler object.
/// 
/// @details
///     - The sampler can only be used on the device on which it was created.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phSampler`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_SAMPLER_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->addressMode
///         + desc->filterMode
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
__ze_api_export ze_result_t __zecall
zeSamplerCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
    ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys sampler object
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the sampler before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this module
///     - The application may **not** call this function from simultaneous
///       threads with the same sampler handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSampler`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeSamplerDestroy(
    ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
    );

#pragma endregion
#pragma region callbacks
///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeInit 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_init_params_t
{
    ze_init_flag_t* pflags;
} ze_init_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeInit 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnInitCb_t)(
    ze_init_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global callback functions pointers
typedef struct _ze_global_callbacks_t
{
    ze_pfnInitCb_t                                                  pfnInitCb;
} ze_global_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_get_params_t
{
    uint32_t** ppCount;
    ze_driver_handle_t** pphDrivers;
} ze_driver_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverGetCb_t)(
    ze_driver_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverGetApiVersion 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_get_api_version_params_t
{
    ze_driver_handle_t* phDriver;
    ze_api_version_t** pversion;
} ze_driver_get_api_version_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverGetApiVersion 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverGetApiVersionCb_t)(
    ze_driver_get_api_version_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_get_properties_params_t
{
    ze_driver_handle_t* phDriver;
    ze_driver_properties_t** ppDriverProperties;
} ze_driver_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverGetPropertiesCb_t)(
    ze_driver_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverGetIPCProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_get_ipc_properties_params_t
{
    ze_driver_handle_t* phDriver;
    ze_driver_ipc_properties_t** ppIPCProperties;
} ze_driver_get_ipc_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverGetIPCProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverGetIPCPropertiesCb_t)(
    ze_driver_get_ipc_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverGetExtensionFunctionAddress 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_get_extension_function_address_params_t
{
    ze_driver_handle_t* phDriver;
    const char** ppFuncName;
    void*** ppfunc;
} ze_driver_get_extension_function_address_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverGetExtensionFunctionAddress 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverGetExtensionFunctionAddressCb_t)(
    ze_driver_get_extension_function_address_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverAllocSharedMem 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_alloc_shared_mem_params_t
{
    ze_driver_handle_t* phDriver;
    const ze_device_mem_alloc_desc_t** pdevice_desc;
    const ze_host_mem_alloc_desc_t** phost_desc;
    size_t* psize;
    size_t* palignment;
    ze_device_handle_t* phDevice;
    void*** ppptr;
} ze_driver_alloc_shared_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverAllocSharedMem 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverAllocSharedMemCb_t)(
    ze_driver_alloc_shared_mem_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverAllocDeviceMem 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_alloc_device_mem_params_t
{
    ze_driver_handle_t* phDriver;
    const ze_device_mem_alloc_desc_t** pdevice_desc;
    size_t* psize;
    size_t* palignment;
    ze_device_handle_t* phDevice;
    void*** ppptr;
} ze_driver_alloc_device_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverAllocDeviceMem 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverAllocDeviceMemCb_t)(
    ze_driver_alloc_device_mem_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverAllocHostMem 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_alloc_host_mem_params_t
{
    ze_driver_handle_t* phDriver;
    const ze_host_mem_alloc_desc_t** phost_desc;
    size_t* psize;
    size_t* palignment;
    void*** ppptr;
} ze_driver_alloc_host_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverAllocHostMem 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverAllocHostMemCb_t)(
    ze_driver_alloc_host_mem_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverFreeMem 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_free_mem_params_t
{
    ze_driver_handle_t* phDriver;
    void** pptr;
} ze_driver_free_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverFreeMem 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverFreeMemCb_t)(
    ze_driver_free_mem_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverGetMemAllocProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_get_mem_alloc_properties_params_t
{
    ze_driver_handle_t* phDriver;
    const void** pptr;
    ze_memory_allocation_properties_t** ppMemAllocProperties;
    ze_device_handle_t** pphDevice;
} ze_driver_get_mem_alloc_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverGetMemAllocProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverGetMemAllocPropertiesCb_t)(
    ze_driver_get_mem_alloc_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverGetMemAddressRange 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_get_mem_address_range_params_t
{
    ze_driver_handle_t* phDriver;
    const void** pptr;
    void*** ppBase;
    size_t** ppSize;
} ze_driver_get_mem_address_range_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverGetMemAddressRange 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverGetMemAddressRangeCb_t)(
    ze_driver_get_mem_address_range_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverGetMemIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_get_mem_ipc_handle_params_t
{
    ze_driver_handle_t* phDriver;
    const void** pptr;
    ze_ipc_mem_handle_t** ppIpcHandle;
} ze_driver_get_mem_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverGetMemIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverGetMemIpcHandleCb_t)(
    ze_driver_get_mem_ipc_handle_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverOpenMemIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_open_mem_ipc_handle_params_t
{
    ze_driver_handle_t* phDriver;
    ze_device_handle_t* phDevice;
    ze_ipc_mem_handle_t* phandle;
    ze_ipc_memory_flag_t* pflags;
    void*** ppptr;
} ze_driver_open_mem_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverOpenMemIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverOpenMemIpcHandleCb_t)(
    ze_driver_open_mem_ipc_handle_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverCloseMemIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_driver_close_mem_ipc_handle_params_t
{
    ze_driver_handle_t* phDriver;
    const void** pptr;
} ze_driver_close_mem_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverCloseMemIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDriverCloseMemIpcHandleCb_t)(
    ze_driver_close_mem_ipc_handle_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Driver callback functions pointers
typedef struct _ze_driver_callbacks_t
{
    ze_pfnDriverGetCb_t                                             pfnGetCb;
    ze_pfnDriverGetApiVersionCb_t                                   pfnGetApiVersionCb;
    ze_pfnDriverGetPropertiesCb_t                                   pfnGetPropertiesCb;
    ze_pfnDriverGetIPCPropertiesCb_t                                pfnGetIPCPropertiesCb;
    ze_pfnDriverGetExtensionFunctionAddressCb_t                     pfnGetExtensionFunctionAddressCb;
    ze_pfnDriverAllocSharedMemCb_t                                  pfnAllocSharedMemCb;
    ze_pfnDriverAllocDeviceMemCb_t                                  pfnAllocDeviceMemCb;
    ze_pfnDriverAllocHostMemCb_t                                    pfnAllocHostMemCb;
    ze_pfnDriverFreeMemCb_t                                         pfnFreeMemCb;
    ze_pfnDriverGetMemAllocPropertiesCb_t                           pfnGetMemAllocPropertiesCb;
    ze_pfnDriverGetMemAddressRangeCb_t                              pfnGetMemAddressRangeCb;
    ze_pfnDriverGetMemIpcHandleCb_t                                 pfnGetMemIpcHandleCb;
    ze_pfnDriverOpenMemIpcHandleCb_t                                pfnOpenMemIpcHandleCb;
    ze_pfnDriverCloseMemIpcHandleCb_t                               pfnCloseMemIpcHandleCb;
} ze_driver_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_params_t
{
    ze_driver_handle_t* phDriver;
    uint32_t** ppCount;
    ze_device_handle_t** pphDevices;
} ze_device_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetCb_t)(
    ze_device_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetSubDevices 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_sub_devices_params_t
{
    ze_device_handle_t* phDevice;
    uint32_t** ppCount;
    ze_device_handle_t** pphSubdevices;
} ze_device_get_sub_devices_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetSubDevices 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetSubDevicesCb_t)(
    ze_device_get_sub_devices_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_properties_params_t
{
    ze_device_handle_t* phDevice;
    ze_device_properties_t** ppDeviceProperties;
} ze_device_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetPropertiesCb_t)(
    ze_device_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetComputeProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_compute_properties_params_t
{
    ze_device_handle_t* phDevice;
    ze_device_compute_properties_t** ppComputeProperties;
} ze_device_get_compute_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetComputeProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetComputePropertiesCb_t)(
    ze_device_get_compute_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetKernelProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_kernel_properties_params_t
{
    ze_device_handle_t* phDevice;
    ze_device_kernel_properties_t** ppKernelProperties;
} ze_device_get_kernel_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetKernelProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetKernelPropertiesCb_t)(
    ze_device_get_kernel_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetCommandQueueGroupProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_command_queue_group_properties_params_t
{
    ze_device_handle_t* phDevice;
    uint32_t** ppCount;
    ze_command_queue_group_properties_t** ppCommandQueueGroupProperties;
} ze_device_get_command_queue_group_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetCommandQueueGroupProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetCommandQueueGroupPropertiesCb_t)(
    ze_device_get_command_queue_group_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetMemoryProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_memory_properties_params_t
{
    ze_device_handle_t* phDevice;
    uint32_t** ppCount;
    ze_device_memory_properties_t** ppMemProperties;
} ze_device_get_memory_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetMemoryProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetMemoryPropertiesCb_t)(
    ze_device_get_memory_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetMemoryAccessProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_memory_access_properties_params_t
{
    ze_device_handle_t* phDevice;
    ze_device_memory_access_properties_t** ppMemAccessProperties;
} ze_device_get_memory_access_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetMemoryAccessProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetMemoryAccessPropertiesCb_t)(
    ze_device_get_memory_access_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetCacheProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_cache_properties_params_t
{
    ze_device_handle_t* phDevice;
    ze_device_cache_properties_t** ppCacheProperties;
} ze_device_get_cache_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetCacheProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetCachePropertiesCb_t)(
    ze_device_get_cache_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetImageProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_image_properties_params_t
{
    ze_device_handle_t* phDevice;
    ze_device_image_properties_t** ppImageProperties;
} ze_device_get_image_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetImageProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetImagePropertiesCb_t)(
    ze_device_get_image_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetP2PProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_get_p2_p_properties_params_t
{
    ze_device_handle_t* phDevice;
    ze_device_handle_t* phPeerDevice;
    ze_device_p2p_properties_t** ppP2PProperties;
} ze_device_get_p2_p_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetP2PProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceGetP2PPropertiesCb_t)(
    ze_device_get_p2_p_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceCanAccessPeer 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_can_access_peer_params_t
{
    ze_device_handle_t* phDevice;
    ze_device_handle_t* phPeerDevice;
    ze_bool_t** pvalue;
} ze_device_can_access_peer_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceCanAccessPeer 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceCanAccessPeerCb_t)(
    ze_device_can_access_peer_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceSetLastLevelCacheConfig 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_set_last_level_cache_config_params_t
{
    ze_device_handle_t* phDevice;
    ze_cache_config_t* pCacheConfig;
} ze_device_set_last_level_cache_config_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceSetLastLevelCacheConfig 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceSetLastLevelCacheConfigCb_t)(
    ze_device_set_last_level_cache_config_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceSystemBarrier 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_system_barrier_params_t
{
    ze_device_handle_t* phDevice;
} ze_device_system_barrier_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceSystemBarrier 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceSystemBarrierCb_t)(
    ze_device_system_barrier_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceRegisterCLMemory 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
#if ZE_ENABLE_OCL_INTEROP
typedef struct _ze_device_register_cl_memory_params_t
{
    ze_device_handle_t* phDevice;
    cl_context* pcontext;
    cl_mem* pmem;
    void*** pptr;
} ze_device_register_cl_memory_params_t;
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceRegisterCLMemory 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
#if ZE_ENABLE_OCL_INTEROP
typedef void (__zecall *ze_pfnDeviceRegisterCLMemoryCb_t)(
    ze_device_register_cl_memory_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceRegisterCLProgram 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
#if ZE_ENABLE_OCL_INTEROP
typedef struct _ze_device_register_cl_program_params_t
{
    ze_device_handle_t* phDevice;
    cl_context* pcontext;
    cl_program* pprogram;
    ze_module_handle_t** pphModule;
} ze_device_register_cl_program_params_t;
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceRegisterCLProgram 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
#if ZE_ENABLE_OCL_INTEROP
typedef void (__zecall *ze_pfnDeviceRegisterCLProgramCb_t)(
    ze_device_register_cl_program_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceRegisterCLCommandQueue 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
#if ZE_ENABLE_OCL_INTEROP
typedef struct _ze_device_register_cl_command_queue_params_t
{
    ze_device_handle_t* phDevice;
    cl_context* pcontext;
    cl_command_queue* pcommand_queue;
    ze_command_queue_handle_t** pphCommandQueue;
} ze_device_register_cl_command_queue_params_t;
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceRegisterCLCommandQueue 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
#if ZE_ENABLE_OCL_INTEROP
typedef void (__zecall *ze_pfnDeviceRegisterCLCommandQueueCb_t)(
    ze_device_register_cl_command_queue_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceMakeMemoryResident 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_make_memory_resident_params_t
{
    ze_device_handle_t* phDevice;
    void** pptr;
    size_t* psize;
} ze_device_make_memory_resident_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceMakeMemoryResident 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceMakeMemoryResidentCb_t)(
    ze_device_make_memory_resident_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceEvictMemory 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_evict_memory_params_t
{
    ze_device_handle_t* phDevice;
    void** pptr;
    size_t* psize;
} ze_device_evict_memory_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceEvictMemory 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceEvictMemoryCb_t)(
    ze_device_evict_memory_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceMakeImageResident 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_make_image_resident_params_t
{
    ze_device_handle_t* phDevice;
    ze_image_handle_t* phImage;
} ze_device_make_image_resident_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceMakeImageResident 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceMakeImageResidentCb_t)(
    ze_device_make_image_resident_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceEvictImage 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_device_evict_image_params_t
{
    ze_device_handle_t* phDevice;
    ze_image_handle_t* phImage;
} ze_device_evict_image_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceEvictImage 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnDeviceEvictImageCb_t)(
    ze_device_evict_image_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device callback functions pointers
typedef struct _ze_device_callbacks_t
{
    ze_pfnDeviceGetCb_t                                             pfnGetCb;
    ze_pfnDeviceGetSubDevicesCb_t                                   pfnGetSubDevicesCb;
    ze_pfnDeviceGetPropertiesCb_t                                   pfnGetPropertiesCb;
    ze_pfnDeviceGetComputePropertiesCb_t                            pfnGetComputePropertiesCb;
    ze_pfnDeviceGetKernelPropertiesCb_t                             pfnGetKernelPropertiesCb;
    ze_pfnDeviceGetCommandQueueGroupPropertiesCb_t                  pfnGetCommandQueueGroupPropertiesCb;
    ze_pfnDeviceGetMemoryPropertiesCb_t                             pfnGetMemoryPropertiesCb;
    ze_pfnDeviceGetMemoryAccessPropertiesCb_t                       pfnGetMemoryAccessPropertiesCb;
    ze_pfnDeviceGetCachePropertiesCb_t                              pfnGetCachePropertiesCb;
    ze_pfnDeviceGetImagePropertiesCb_t                              pfnGetImagePropertiesCb;
    ze_pfnDeviceGetP2PPropertiesCb_t                                pfnGetP2PPropertiesCb;
    ze_pfnDeviceCanAccessPeerCb_t                                   pfnCanAccessPeerCb;
    ze_pfnDeviceSetLastLevelCacheConfigCb_t                         pfnSetLastLevelCacheConfigCb;
    ze_pfnDeviceSystemBarrierCb_t                                   pfnSystemBarrierCb;
#if ZE_ENABLE_OCL_INTEROP
    ze_pfnDeviceRegisterCLMemoryCb_t                                pfnRegisterCLMemoryCb;
#else
    void*                                                           pfnRegisterCLMemoryCb;
#endif // ZE_ENABLE_OCL_INTEROP
#if ZE_ENABLE_OCL_INTEROP
    ze_pfnDeviceRegisterCLProgramCb_t                               pfnRegisterCLProgramCb;
#else
    void*                                                           pfnRegisterCLProgramCb;
#endif // ZE_ENABLE_OCL_INTEROP
#if ZE_ENABLE_OCL_INTEROP
    ze_pfnDeviceRegisterCLCommandQueueCb_t                          pfnRegisterCLCommandQueueCb;
#else
    void*                                                           pfnRegisterCLCommandQueueCb;
#endif // ZE_ENABLE_OCL_INTEROP
    ze_pfnDeviceMakeMemoryResidentCb_t                              pfnMakeMemoryResidentCb;
    ze_pfnDeviceEvictMemoryCb_t                                     pfnEvictMemoryCb;
    ze_pfnDeviceMakeImageResidentCb_t                               pfnMakeImageResidentCb;
    ze_pfnDeviceEvictImageCb_t                                      pfnEvictImageCb;
} ze_device_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandQueueCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_queue_create_params_t
{
    ze_device_handle_t* phDevice;
    const ze_command_queue_desc_t** pdesc;
    ze_command_queue_handle_t** pphCommandQueue;
} ze_command_queue_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandQueueCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandQueueCreateCb_t)(
    ze_command_queue_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandQueueDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_queue_destroy_params_t
{
    ze_command_queue_handle_t* phCommandQueue;
} ze_command_queue_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandQueueDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandQueueDestroyCb_t)(
    ze_command_queue_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandQueueExecuteCommandLists 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_queue_execute_command_lists_params_t
{
    ze_command_queue_handle_t* phCommandQueue;
    uint32_t* pnumCommandLists;
    ze_command_list_handle_t** pphCommandLists;
    ze_fence_handle_t* phFence;
} ze_command_queue_execute_command_lists_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandQueueExecuteCommandLists 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandQueueExecuteCommandListsCb_t)(
    ze_command_queue_execute_command_lists_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandQueueSynchronize 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_queue_synchronize_params_t
{
    ze_command_queue_handle_t* phCommandQueue;
    uint32_t* ptimeout;
} ze_command_queue_synchronize_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandQueueSynchronize 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandQueueSynchronizeCb_t)(
    ze_command_queue_synchronize_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandQueue callback functions pointers
typedef struct _ze_command_queue_callbacks_t
{
    ze_pfnCommandQueueCreateCb_t                                    pfnCreateCb;
    ze_pfnCommandQueueDestroyCb_t                                   pfnDestroyCb;
    ze_pfnCommandQueueExecuteCommandListsCb_t                       pfnExecuteCommandListsCb;
    ze_pfnCommandQueueSynchronizeCb_t                               pfnSynchronizeCb;
} ze_command_queue_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_create_params_t
{
    ze_device_handle_t* phDevice;
    const ze_command_list_desc_t** pdesc;
    ze_command_list_handle_t** pphCommandList;
} ze_command_list_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListCreateCb_t)(
    ze_command_list_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListCreateImmediate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_create_immediate_params_t
{
    ze_device_handle_t* phDevice;
    const ze_command_queue_desc_t** paltdesc;
    ze_command_list_handle_t** pphCommandList;
} ze_command_list_create_immediate_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListCreateImmediate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListCreateImmediateCb_t)(
    ze_command_list_create_immediate_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_destroy_params_t
{
    ze_command_list_handle_t* phCommandList;
} ze_command_list_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListDestroyCb_t)(
    ze_command_list_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListClose 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_close_params_t
{
    ze_command_list_handle_t* phCommandList;
} ze_command_list_close_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListClose 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListCloseCb_t)(
    ze_command_list_close_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListReset 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_reset_params_t
{
    ze_command_list_handle_t* phCommandList;
} ze_command_list_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListReset 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListResetCb_t)(
    ze_command_list_reset_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendBarrier 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_barrier_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    ze_event_handle_t** pphWaitEvents;
} ze_command_list_append_barrier_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendBarrier 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendBarrierCb_t)(
    ze_command_list_append_barrier_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendMemoryRangesBarrier 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_memory_ranges_barrier_params_t
{
    ze_command_list_handle_t* phCommandList;
    uint32_t* pnumRanges;
    const size_t** ppRangeSizes;
    const void*** ppRanges;
    ze_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    ze_event_handle_t** pphWaitEvents;
} ze_command_list_append_memory_ranges_barrier_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendMemoryRangesBarrier 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendMemoryRangesBarrierCb_t)(
    ze_command_list_append_memory_ranges_barrier_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendMemoryCopy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_memory_copy_params_t
{
    ze_command_list_handle_t* phCommandList;
    void** pdstptr;
    const void** psrcptr;
    size_t* psize;
    ze_event_handle_t* phEvent;
} ze_command_list_append_memory_copy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendMemoryCopy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendMemoryCopyCb_t)(
    ze_command_list_append_memory_copy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendMemoryFill 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_memory_fill_params_t
{
    ze_command_list_handle_t* phCommandList;
    void** pptr;
    const void** ppattern;
    size_t* ppattern_size;
    size_t* psize;
    ze_event_handle_t* phEvent;
} ze_command_list_append_memory_fill_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendMemoryFill 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendMemoryFillCb_t)(
    ze_command_list_append_memory_fill_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendMemoryCopyRegion 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_memory_copy_region_params_t
{
    ze_command_list_handle_t* phCommandList;
    void** pdstptr;
    const ze_copy_region_t** pdstRegion;
    uint32_t* pdstPitch;
    uint32_t* pdstSlicePitch;
    const void** psrcptr;
    const ze_copy_region_t** psrcRegion;
    uint32_t* psrcPitch;
    uint32_t* psrcSlicePitch;
    ze_event_handle_t* phEvent;
} ze_command_list_append_memory_copy_region_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendMemoryCopyRegion 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendMemoryCopyRegionCb_t)(
    ze_command_list_append_memory_copy_region_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendImageCopy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_image_copy_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_image_handle_t* phDstImage;
    ze_image_handle_t* phSrcImage;
    ze_event_handle_t* phEvent;
} ze_command_list_append_image_copy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendImageCopy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendImageCopyCb_t)(
    ze_command_list_append_image_copy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendImageCopyRegion 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_image_copy_region_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_image_handle_t* phDstImage;
    ze_image_handle_t* phSrcImage;
    const ze_image_region_t** ppDstRegion;
    const ze_image_region_t** ppSrcRegion;
    ze_event_handle_t* phEvent;
} ze_command_list_append_image_copy_region_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendImageCopyRegion 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendImageCopyRegionCb_t)(
    ze_command_list_append_image_copy_region_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendImageCopyToMemory 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_image_copy_to_memory_params_t
{
    ze_command_list_handle_t* phCommandList;
    void** pdstptr;
    ze_image_handle_t* phSrcImage;
    const ze_image_region_t** ppSrcRegion;
    ze_event_handle_t* phEvent;
} ze_command_list_append_image_copy_to_memory_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendImageCopyToMemory 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendImageCopyToMemoryCb_t)(
    ze_command_list_append_image_copy_to_memory_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendImageCopyFromMemory 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_image_copy_from_memory_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_image_handle_t* phDstImage;
    const void** psrcptr;
    const ze_image_region_t** ppDstRegion;
    ze_event_handle_t* phEvent;
} ze_command_list_append_image_copy_from_memory_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendImageCopyFromMemory 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendImageCopyFromMemoryCb_t)(
    ze_command_list_append_image_copy_from_memory_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendMemoryPrefetch 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_memory_prefetch_params_t
{
    ze_command_list_handle_t* phCommandList;
    const void** pptr;
    size_t* psize;
} ze_command_list_append_memory_prefetch_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendMemoryPrefetch 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendMemoryPrefetchCb_t)(
    ze_command_list_append_memory_prefetch_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendMemAdvise 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_mem_advise_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_device_handle_t* phDevice;
    const void** pptr;
    size_t* psize;
    ze_memory_advice_t* padvice;
} ze_command_list_append_mem_advise_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendMemAdvise 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendMemAdviseCb_t)(
    ze_command_list_append_mem_advise_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendSignalEvent 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_signal_event_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_event_handle_t* phEvent;
} ze_command_list_append_signal_event_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendSignalEvent 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendSignalEventCb_t)(
    ze_command_list_append_signal_event_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendWaitOnEvents 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_wait_on_events_params_t
{
    ze_command_list_handle_t* phCommandList;
    uint32_t* pnumEvents;
    ze_event_handle_t** pphEvents;
} ze_command_list_append_wait_on_events_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendWaitOnEvents 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendWaitOnEventsCb_t)(
    ze_command_list_append_wait_on_events_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendEventReset 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_event_reset_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_event_handle_t* phEvent;
} ze_command_list_append_event_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendEventReset 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendEventResetCb_t)(
    ze_command_list_append_event_reset_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendLaunchKernel 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_launch_kernel_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_kernel_handle_t* phKernel;
    const ze_group_count_t** ppLaunchFuncArgs;
    ze_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    ze_event_handle_t** pphWaitEvents;
} ze_command_list_append_launch_kernel_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendLaunchKernel 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendLaunchKernelCb_t)(
    ze_command_list_append_launch_kernel_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendLaunchCooperativeKernel 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_launch_cooperative_kernel_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_kernel_handle_t* phKernel;
    const ze_group_count_t** ppLaunchFuncArgs;
    ze_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    ze_event_handle_t** pphWaitEvents;
} ze_command_list_append_launch_cooperative_kernel_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendLaunchCooperativeKernel 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendLaunchCooperativeKernelCb_t)(
    ze_command_list_append_launch_cooperative_kernel_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendLaunchKernelIndirect 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_launch_kernel_indirect_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_kernel_handle_t* phKernel;
    const ze_group_count_t** ppLaunchArgumentsBuffer;
    ze_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    ze_event_handle_t** pphWaitEvents;
} ze_command_list_append_launch_kernel_indirect_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendLaunchKernelIndirect 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendLaunchKernelIndirectCb_t)(
    ze_command_list_append_launch_kernel_indirect_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendLaunchMultipleKernelsIndirect 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_command_list_append_launch_multiple_kernels_indirect_params_t
{
    ze_command_list_handle_t* phCommandList;
    uint32_t* pnumKernels;
    ze_kernel_handle_t** pphKernels;
    const uint32_t** ppCountBuffer;
    const ze_group_count_t** ppLaunchArgumentsBuffer;
    ze_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    ze_event_handle_t** pphWaitEvents;
} ze_command_list_append_launch_multiple_kernels_indirect_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendLaunchMultipleKernelsIndirect 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnCommandListAppendLaunchMultipleKernelsIndirectCb_t)(
    ze_command_list_append_launch_multiple_kernels_indirect_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList callback functions pointers
typedef struct _ze_command_list_callbacks_t
{
    ze_pfnCommandListCreateCb_t                                     pfnCreateCb;
    ze_pfnCommandListCreateImmediateCb_t                            pfnCreateImmediateCb;
    ze_pfnCommandListDestroyCb_t                                    pfnDestroyCb;
    ze_pfnCommandListCloseCb_t                                      pfnCloseCb;
    ze_pfnCommandListResetCb_t                                      pfnResetCb;
    ze_pfnCommandListAppendBarrierCb_t                              pfnAppendBarrierCb;
    ze_pfnCommandListAppendMemoryRangesBarrierCb_t                  pfnAppendMemoryRangesBarrierCb;
    ze_pfnCommandListAppendMemoryCopyCb_t                           pfnAppendMemoryCopyCb;
    ze_pfnCommandListAppendMemoryFillCb_t                           pfnAppendMemoryFillCb;
    ze_pfnCommandListAppendMemoryCopyRegionCb_t                     pfnAppendMemoryCopyRegionCb;
    ze_pfnCommandListAppendImageCopyCb_t                            pfnAppendImageCopyCb;
    ze_pfnCommandListAppendImageCopyRegionCb_t                      pfnAppendImageCopyRegionCb;
    ze_pfnCommandListAppendImageCopyToMemoryCb_t                    pfnAppendImageCopyToMemoryCb;
    ze_pfnCommandListAppendImageCopyFromMemoryCb_t                  pfnAppendImageCopyFromMemoryCb;
    ze_pfnCommandListAppendMemoryPrefetchCb_t                       pfnAppendMemoryPrefetchCb;
    ze_pfnCommandListAppendMemAdviseCb_t                            pfnAppendMemAdviseCb;
    ze_pfnCommandListAppendSignalEventCb_t                          pfnAppendSignalEventCb;
    ze_pfnCommandListAppendWaitOnEventsCb_t                         pfnAppendWaitOnEventsCb;
    ze_pfnCommandListAppendEventResetCb_t                           pfnAppendEventResetCb;
    ze_pfnCommandListAppendLaunchKernelCb_t                         pfnAppendLaunchKernelCb;
    ze_pfnCommandListAppendLaunchCooperativeKernelCb_t              pfnAppendLaunchCooperativeKernelCb;
    ze_pfnCommandListAppendLaunchKernelIndirectCb_t                 pfnAppendLaunchKernelIndirectCb;
    ze_pfnCommandListAppendLaunchMultipleKernelsIndirectCb_t        pfnAppendLaunchMultipleKernelsIndirectCb;
} ze_command_list_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFenceCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_fence_create_params_t
{
    ze_command_queue_handle_t* phCommandQueue;
    const ze_fence_desc_t** pdesc;
    ze_fence_handle_t** pphFence;
} ze_fence_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFenceCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnFenceCreateCb_t)(
    ze_fence_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFenceDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_fence_destroy_params_t
{
    ze_fence_handle_t* phFence;
} ze_fence_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFenceDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnFenceDestroyCb_t)(
    ze_fence_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFenceHostSynchronize 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_fence_host_synchronize_params_t
{
    ze_fence_handle_t* phFence;
    uint32_t* ptimeout;
} ze_fence_host_synchronize_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFenceHostSynchronize 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnFenceHostSynchronizeCb_t)(
    ze_fence_host_synchronize_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFenceQueryStatus 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_fence_query_status_params_t
{
    ze_fence_handle_t* phFence;
} ze_fence_query_status_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFenceQueryStatus 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnFenceQueryStatusCb_t)(
    ze_fence_query_status_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFenceReset 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_fence_reset_params_t
{
    ze_fence_handle_t* phFence;
} ze_fence_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFenceReset 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnFenceResetCb_t)(
    ze_fence_reset_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Fence callback functions pointers
typedef struct _ze_fence_callbacks_t
{
    ze_pfnFenceCreateCb_t                                           pfnCreateCb;
    ze_pfnFenceDestroyCb_t                                          pfnDestroyCb;
    ze_pfnFenceHostSynchronizeCb_t                                  pfnHostSynchronizeCb;
    ze_pfnFenceQueryStatusCb_t                                      pfnQueryStatusCb;
    ze_pfnFenceResetCb_t                                            pfnResetCb;
} ze_fence_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventPoolCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_pool_create_params_t
{
    ze_driver_handle_t* phDriver;
    const ze_event_pool_desc_t** pdesc;
    uint32_t* pnumDevices;
    ze_device_handle_t** pphDevices;
    ze_event_pool_handle_t** pphEventPool;
} ze_event_pool_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventPoolCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventPoolCreateCb_t)(
    ze_event_pool_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventPoolDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_pool_destroy_params_t
{
    ze_event_pool_handle_t* phEventPool;
} ze_event_pool_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventPoolDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventPoolDestroyCb_t)(
    ze_event_pool_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventPoolGetIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_pool_get_ipc_handle_params_t
{
    ze_event_pool_handle_t* phEventPool;
    ze_ipc_event_pool_handle_t** pphIpc;
} ze_event_pool_get_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventPoolGetIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventPoolGetIpcHandleCb_t)(
    ze_event_pool_get_ipc_handle_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventPoolOpenIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_pool_open_ipc_handle_params_t
{
    ze_driver_handle_t* phDriver;
    ze_ipc_event_pool_handle_t* phIpc;
    ze_event_pool_handle_t** pphEventPool;
} ze_event_pool_open_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventPoolOpenIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventPoolOpenIpcHandleCb_t)(
    ze_event_pool_open_ipc_handle_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventPoolCloseIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_pool_close_ipc_handle_params_t
{
    ze_event_pool_handle_t* phEventPool;
} ze_event_pool_close_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventPoolCloseIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventPoolCloseIpcHandleCb_t)(
    ze_event_pool_close_ipc_handle_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of EventPool callback functions pointers
typedef struct _ze_event_pool_callbacks_t
{
    ze_pfnEventPoolCreateCb_t                                       pfnCreateCb;
    ze_pfnEventPoolDestroyCb_t                                      pfnDestroyCb;
    ze_pfnEventPoolGetIpcHandleCb_t                                 pfnGetIpcHandleCb;
    ze_pfnEventPoolOpenIpcHandleCb_t                                pfnOpenIpcHandleCb;
    ze_pfnEventPoolCloseIpcHandleCb_t                               pfnCloseIpcHandleCb;
} ze_event_pool_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_create_params_t
{
    ze_event_pool_handle_t* phEventPool;
    const ze_event_desc_t** pdesc;
    ze_event_handle_t** pphEvent;
} ze_event_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventCreateCb_t)(
    ze_event_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_destroy_params_t
{
    ze_event_handle_t* phEvent;
} ze_event_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventDestroyCb_t)(
    ze_event_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventHostSignal 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_host_signal_params_t
{
    ze_event_handle_t* phEvent;
} ze_event_host_signal_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventHostSignal 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventHostSignalCb_t)(
    ze_event_host_signal_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventHostSynchronize 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_host_synchronize_params_t
{
    ze_event_handle_t* phEvent;
    uint32_t* ptimeout;
} ze_event_host_synchronize_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventHostSynchronize 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventHostSynchronizeCb_t)(
    ze_event_host_synchronize_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventQueryStatus 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_query_status_params_t
{
    ze_event_handle_t* phEvent;
} ze_event_query_status_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventQueryStatus 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventQueryStatusCb_t)(
    ze_event_query_status_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventHostReset 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_host_reset_params_t
{
    ze_event_handle_t* phEvent;
} ze_event_host_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventHostReset 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventHostResetCb_t)(
    ze_event_host_reset_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventGetTimestamp 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_event_get_timestamp_params_t
{
    ze_event_handle_t* phEvent;
    ze_event_timestamp_type_t* ptimestampType;
    void** pdstptr;
} ze_event_get_timestamp_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventGetTimestamp 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnEventGetTimestampCb_t)(
    ze_event_get_timestamp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Event callback functions pointers
typedef struct _ze_event_callbacks_t
{
    ze_pfnEventCreateCb_t                                           pfnCreateCb;
    ze_pfnEventDestroyCb_t                                          pfnDestroyCb;
    ze_pfnEventHostSignalCb_t                                       pfnHostSignalCb;
    ze_pfnEventHostSynchronizeCb_t                                  pfnHostSynchronizeCb;
    ze_pfnEventQueryStatusCb_t                                      pfnQueryStatusCb;
    ze_pfnEventHostResetCb_t                                        pfnHostResetCb;
    ze_pfnEventGetTimestampCb_t                                     pfnGetTimestampCb;
} ze_event_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeImageGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_image_get_properties_params_t
{
    ze_device_handle_t* phDevice;
    const ze_image_desc_t** pdesc;
    ze_image_properties_t** ppImageProperties;
} ze_image_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeImageGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnImageGetPropertiesCb_t)(
    ze_image_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeImageCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_image_create_params_t
{
    ze_device_handle_t* phDevice;
    const ze_image_desc_t** pdesc;
    ze_image_handle_t** pphImage;
} ze_image_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeImageCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnImageCreateCb_t)(
    ze_image_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeImageDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_image_destroy_params_t
{
    ze_image_handle_t* phImage;
} ze_image_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeImageDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnImageDestroyCb_t)(
    ze_image_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Image callback functions pointers
typedef struct _ze_image_callbacks_t
{
    ze_pfnImageGetPropertiesCb_t                                    pfnGetPropertiesCb;
    ze_pfnImageCreateCb_t                                           pfnCreateCb;
    ze_pfnImageDestroyCb_t                                          pfnDestroyCb;
} ze_image_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeModuleCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_module_create_params_t
{
    ze_device_handle_t* phDevice;
    const ze_module_desc_t** pdesc;
    ze_module_handle_t** pphModule;
    ze_module_build_log_handle_t** pphBuildLog;
} ze_module_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeModuleCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnModuleCreateCb_t)(
    ze_module_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeModuleDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_module_destroy_params_t
{
    ze_module_handle_t* phModule;
} ze_module_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeModuleDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnModuleDestroyCb_t)(
    ze_module_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeModuleGetNativeBinary 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_module_get_native_binary_params_t
{
    ze_module_handle_t* phModule;
    size_t** ppSize;
    uint8_t** ppModuleNativeBinary;
} ze_module_get_native_binary_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeModuleGetNativeBinary 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnModuleGetNativeBinaryCb_t)(
    ze_module_get_native_binary_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeModuleGetGlobalPointer 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_module_get_global_pointer_params_t
{
    ze_module_handle_t* phModule;
    const char** ppGlobalName;
    void*** ppptr;
} ze_module_get_global_pointer_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeModuleGetGlobalPointer 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnModuleGetGlobalPointerCb_t)(
    ze_module_get_global_pointer_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeModuleGetKernelNames 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_module_get_kernel_names_params_t
{
    ze_module_handle_t* phModule;
    uint32_t** ppCount;
    const char*** ppNames;
} ze_module_get_kernel_names_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeModuleGetKernelNames 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnModuleGetKernelNamesCb_t)(
    ze_module_get_kernel_names_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeModuleGetFunctionPointer 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_module_get_function_pointer_params_t
{
    ze_module_handle_t* phModule;
    const char** ppFunctionName;
    void*** ppfnFunction;
} ze_module_get_function_pointer_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeModuleGetFunctionPointer 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnModuleGetFunctionPointerCb_t)(
    ze_module_get_function_pointer_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module callback functions pointers
typedef struct _ze_module_callbacks_t
{
    ze_pfnModuleCreateCb_t                                          pfnCreateCb;
    ze_pfnModuleDestroyCb_t                                         pfnDestroyCb;
    ze_pfnModuleGetNativeBinaryCb_t                                 pfnGetNativeBinaryCb;
    ze_pfnModuleGetGlobalPointerCb_t                                pfnGetGlobalPointerCb;
    ze_pfnModuleGetKernelNamesCb_t                                  pfnGetKernelNamesCb;
    ze_pfnModuleGetFunctionPointerCb_t                              pfnGetFunctionPointerCb;
} ze_module_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeModuleBuildLogDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_module_build_log_destroy_params_t
{
    ze_module_build_log_handle_t* phModuleBuildLog;
} ze_module_build_log_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeModuleBuildLogDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnModuleBuildLogDestroyCb_t)(
    ze_module_build_log_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeModuleBuildLogGetString 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_module_build_log_get_string_params_t
{
    ze_module_build_log_handle_t* phModuleBuildLog;
    size_t** ppSize;
    char** ppBuildLog;
} ze_module_build_log_get_string_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeModuleBuildLogGetString 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnModuleBuildLogGetStringCb_t)(
    ze_module_build_log_get_string_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of ModuleBuildLog callback functions pointers
typedef struct _ze_module_build_log_callbacks_t
{
    ze_pfnModuleBuildLogDestroyCb_t                                 pfnDestroyCb;
    ze_pfnModuleBuildLogGetStringCb_t                               pfnGetStringCb;
} ze_module_build_log_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_kernel_create_params_t
{
    ze_module_handle_t* phModule;
    const ze_kernel_desc_t** pdesc;
    ze_kernel_handle_t** pphKernel;
} ze_kernel_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnKernelCreateCb_t)(
    ze_kernel_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_kernel_destroy_params_t
{
    ze_kernel_handle_t* phKernel;
} ze_kernel_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnKernelDestroyCb_t)(
    ze_kernel_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelSetIntermediateCacheConfig 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_kernel_set_intermediate_cache_config_params_t
{
    ze_kernel_handle_t* phKernel;
    ze_cache_config_t* pCacheConfig;
} ze_kernel_set_intermediate_cache_config_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelSetIntermediateCacheConfig 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnKernelSetIntermediateCacheConfigCb_t)(
    ze_kernel_set_intermediate_cache_config_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelSetGroupSize 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_kernel_set_group_size_params_t
{
    ze_kernel_handle_t* phKernel;
    uint32_t* pgroupSizeX;
    uint32_t* pgroupSizeY;
    uint32_t* pgroupSizeZ;
} ze_kernel_set_group_size_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelSetGroupSize 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnKernelSetGroupSizeCb_t)(
    ze_kernel_set_group_size_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelSuggestGroupSize 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_kernel_suggest_group_size_params_t
{
    ze_kernel_handle_t* phKernel;
    uint32_t* pglobalSizeX;
    uint32_t* pglobalSizeY;
    uint32_t* pglobalSizeZ;
    uint32_t** pgroupSizeX;
    uint32_t** pgroupSizeY;
    uint32_t** pgroupSizeZ;
} ze_kernel_suggest_group_size_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelSuggestGroupSize 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnKernelSuggestGroupSizeCb_t)(
    ze_kernel_suggest_group_size_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelSuggestMaxCooperativeGroupCount 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_kernel_suggest_max_cooperative_group_count_params_t
{
    ze_kernel_handle_t* phKernel;
    uint32_t** ptotalGroupCount;
} ze_kernel_suggest_max_cooperative_group_count_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelSuggestMaxCooperativeGroupCount 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnKernelSuggestMaxCooperativeGroupCountCb_t)(
    ze_kernel_suggest_max_cooperative_group_count_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelSetArgumentValue 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_kernel_set_argument_value_params_t
{
    ze_kernel_handle_t* phKernel;
    uint32_t* pargIndex;
    size_t* pargSize;
    const void** ppArgValue;
} ze_kernel_set_argument_value_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelSetArgumentValue 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnKernelSetArgumentValueCb_t)(
    ze_kernel_set_argument_value_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelSetAttribute 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_kernel_set_attribute_params_t
{
    ze_kernel_handle_t* phKernel;
    ze_kernel_attribute_t* pattr;
    uint32_t* psize;
    const void** ppValue;
} ze_kernel_set_attribute_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelSetAttribute 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnKernelSetAttributeCb_t)(
    ze_kernel_set_attribute_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelGetAttribute 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_kernel_get_attribute_params_t
{
    ze_kernel_handle_t* phKernel;
    ze_kernel_attribute_t* pattr;
    uint32_t** ppSize;
    void** ppValue;
} ze_kernel_get_attribute_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelGetAttribute 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnKernelGetAttributeCb_t)(
    ze_kernel_get_attribute_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_kernel_get_properties_params_t
{
    ze_kernel_handle_t* phKernel;
    ze_kernel_properties_t** ppKernelProperties;
} ze_kernel_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnKernelGetPropertiesCb_t)(
    ze_kernel_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Kernel callback functions pointers
typedef struct _ze_kernel_callbacks_t
{
    ze_pfnKernelCreateCb_t                                          pfnCreateCb;
    ze_pfnKernelDestroyCb_t                                         pfnDestroyCb;
    ze_pfnKernelSetIntermediateCacheConfigCb_t                      pfnSetIntermediateCacheConfigCb;
    ze_pfnKernelSetGroupSizeCb_t                                    pfnSetGroupSizeCb;
    ze_pfnKernelSuggestGroupSizeCb_t                                pfnSuggestGroupSizeCb;
    ze_pfnKernelSuggestMaxCooperativeGroupCountCb_t                 pfnSuggestMaxCooperativeGroupCountCb;
    ze_pfnKernelSetArgumentValueCb_t                                pfnSetArgumentValueCb;
    ze_pfnKernelSetAttributeCb_t                                    pfnSetAttributeCb;
    ze_pfnKernelGetAttributeCb_t                                    pfnGetAttributeCb;
    ze_pfnKernelGetPropertiesCb_t                                   pfnGetPropertiesCb;
} ze_kernel_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeSamplerCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_sampler_create_params_t
{
    ze_device_handle_t* phDevice;
    const ze_sampler_desc_t** pdesc;
    ze_sampler_handle_t** pphSampler;
} ze_sampler_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeSamplerCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnSamplerCreateCb_t)(
    ze_sampler_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeSamplerDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _ze_sampler_destroy_params_t
{
    ze_sampler_handle_t* phSampler;
} ze_sampler_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeSamplerDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *ze_pfnSamplerDestroyCb_t)(
    ze_sampler_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sampler callback functions pointers
typedef struct _ze_sampler_callbacks_t
{
    ze_pfnSamplerCreateCb_t                                         pfnCreateCb;
    ze_pfnSamplerDestroyCb_t                                        pfnDestroyCb;
} ze_sampler_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all callbacks
typedef struct _ze_callbacks_t
{
    ze_global_callbacks_t               Global;
    ze_driver_callbacks_t               Driver;
    ze_device_callbacks_t               Device;
    ze_command_queue_callbacks_t        CommandQueue;
    ze_command_list_callbacks_t         CommandList;
    ze_fence_callbacks_t                Fence;
    ze_event_pool_callbacks_t           EventPool;
    ze_event_callbacks_t                Event;
    ze_image_callbacks_t                Image;
    ze_module_callbacks_t               Module;
    ze_module_build_log_callbacks_t     ModuleBuildLog;
    ze_kernel_callbacks_t               Kernel;
    ze_sampler_callbacks_t              Sampler;
} ze_callbacks_t;

#pragma endregion

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_API_H