/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_api.hpp
 * @version v1.0-r0.9.277
 *
 */
#ifndef _ZE_API_HPP
#define _ZE_API_HPP
#if defined(__cplusplus)
#pragma once

// C API headers
#include "ze_api.h"

// standard headers
#include <stdint.h>
#include <string.h>
#include <exception>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>

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
#ifndef ZE_MAX_IPC_HANDLE_SIZE
/// @brief Maximum IPC handle size
#define ZE_MAX_IPC_HANDLE_SIZE  64
#endif // ZE_MAX_IPC_HANDLE_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_BIT
/// @brief Generic macro for enumerator bit masks
#define ZE_BIT( _i )  ( 1 << _i )
#endif // ZE_BIT

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief compiler-independent type
    using bool_t = uint8_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of a driver instance
    class Driver;
    struct _driver_handle_t;
    using driver_handle_t = _driver_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's device object
    class Device;
    struct _device_handle_t;
    using device_handle_t = _device_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command queue object
    class CommandQueue;
    struct _command_queue_handle_t;
    using command_queue_handle_t = _command_queue_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command list object
    class CommandList;
    struct _command_list_handle_t;
    using command_list_handle_t = _command_list_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's fence object
    class Fence;
    struct _fence_handle_t;
    using fence_handle_t = _fence_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's event pool object
    class EventPool;
    struct _event_pool_handle_t;
    using event_pool_handle_t = _event_pool_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's event object
    class Event;
    struct _event_handle_t;
    using event_handle_t = _event_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's image object
    class Image;
    struct _image_handle_t;
    using image_handle_t = _image_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's module object
    class Module;
    struct _module_handle_t;
    using module_handle_t = _module_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of module's build log object
    class ModuleBuildLog;
    struct _module_build_log_handle_t;
    using module_build_log_handle_t = _module_build_log_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's kernel object
    class Kernel;
    struct _kernel_handle_t;
    using kernel_handle_t = _kernel_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's sampler object
    class Sampler;
    struct _sampler_handle_t;
    using sampler_handle_t = _sampler_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief IPC handle to a memory allocation
    struct ipc_mem_handle_t
    {
        char data[ZE_MAX_IPC_HANDLE_SIZE];              ///< Opaque data representing an IPC handle

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief IPC handle to a event pool allocation
    struct ipc_event_pool_handle_t
    {
        char data[ZE_MAX_IPC_HANDLE_SIZE];              ///< Opaque data representing an IPC handle

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Defines Return/Error codes
    enum class result_t
    {
        SUCCESS = 0,                                    ///< [Core] success
        NOT_READY = 1,                                  ///< [Core] synchronization primitive not signaled
        ERROR_DEVICE_LOST = 0x70000001,                 ///< [Core] device hung, reset, was removed, or driver update occurred
        ERROR_OUT_OF_HOST_MEMORY,                       ///< [Core] insufficient host memory to satisfy call
        ERROR_OUT_OF_DEVICE_MEMORY,                     ///< [Core] insufficient device memory to satisfy call
        ERROR_MODULE_BUILD_FAILURE,                     ///< [Core] error occurred when building module, see build log for details
        ERROR_INSUFFICIENT_PERMISSIONS = 0x70010000,    ///< [Tools] access denied due to permission level
        ERROR_NOT_AVAILABLE,                            ///< [Tools] resource already in use and simultaneous access not allowed
        ERROR_UNINITIALIZED = 0x78000001,               ///< [Validation] driver is not initialized
        ERROR_UNSUPPORTED_VERSION,                      ///< [Validation] generic error code for unsupported versions
        ERROR_UNSUPPORTED_FEATURE,                      ///< [Validation] generic error code for unsupported features
        ERROR_INVALID_ARGUMENT,                         ///< [Validation] generic error code for invalid arguments
        ERROR_INVALID_NULL_HANDLE,                      ///< [Validation] handle argument is not valid
        ERROR_HANDLE_OBJECT_IN_USE,                     ///< [Validation] object pointed to by handle still in-use by device
        ERROR_INVALID_NULL_POINTER,                     ///< [Validation] pointer argument may not be nullptr
        ERROR_INVALID_SIZE,                             ///< [Validation] size argument is invalid (e.g., must not be zero)
        ERROR_UNSUPPORTED_SIZE,                         ///< [Validation] size argument is not supported by the device (e.g., too
                                                        ///< large)
        ERROR_UNSUPPORTED_ALIGNMENT,                    ///< [Validation] alignment argument is not supported by the device (e.g.,
                                                        ///< too small)
        ERROR_INVALID_SYNCHRONIZATION_OBJECT,           ///< [Validation] synchronization object in invalid state
        ERROR_INVALID_ENUMERATION,                      ///< [Validation] enumerator argument is not valid
        ERROR_UNSUPPORTED_ENUMERATION,                  ///< [Validation] enumerator argument is not supported by the device
        ERROR_UNSUPPORTED_IMAGE_FORMAT,                 ///< [Validation] image format is not supported by the device
        ERROR_INVALID_NATIVE_BINARY,                    ///< [Validation] native binary is not supported by the device
        ERROR_INVALID_GLOBAL_NAME,                      ///< [Validation] global variable is not found in the module
        ERROR_INVALID_KERNEL_NAME,                      ///< [Validation] kernel name is not found in the module
        ERROR_INVALID_FUNCTION_NAME,                    ///< [Validation] function name is not found in the module
        ERROR_INVALID_GROUP_SIZE_DIMENSION,             ///< [Validation] group size dimension is not valid for the kernel or
                                                        ///< device
        ERROR_INVALID_GLOBAL_WIDTH_DIMENSION,           ///< [Validation] global width dimension is not valid for the kernel or
                                                        ///< device
        ERROR_INVALID_KERNEL_ARGUMENT_INDEX,            ///< [Validation] kernel argument index is not valid for kernel
        ERROR_INVALID_KERNEL_ARGUMENT_SIZE,             ///< [Validation] kernel argument size does not match kernel
        ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE,           ///< [Validation] value of kernel attribute is not valid for the kernel or
                                                        ///< device
        ERROR_INVALID_COMMAND_LIST_TYPE,                ///< [Validation] command list type does not match command queue type
        ERROR_OVERLAPPING_REGIONS,                      ///< [Validation] copy operations do not support overlapping regions of
                                                        ///< memory
        ERROR_UNKNOWN = 0x7fffffff,                     ///< [Core] unknown or internal error

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ipc_mem_handle_t to std::string
    std::string to_string( const ipc_mem_handle_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ipc_event_pool_handle_t to std::string
    std::string to_string( const ipc_event_pool_handle_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts result_t to std::string
    std::string to_string( const result_t val );

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    class exception_t : public std::exception
    {
    protected:
        static std::string formatted( const result_t, const char*, const char*, const char* );

        const std::string _msg;
        const result_t _result;

    public:
        exception_t() = delete;

        exception_t( const result_t result, const char* file, const char* line, const char* func )
            : std::exception(),
            _msg( formatted(result, file, line, func) ),
            _result(result)
        {
        }

        const char* what() const noexcept { return _msg.c_str(); }
        result_t value() const noexcept { return _result; }
    };

} // namespace ze
#pragma endregion
#pragma region driver
///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DRIVER_UUID_SIZE
/// @brief Maximum driver universal unique id (UUID) size in bytes
#define ZE_MAX_DRIVER_UUID_SIZE  16
#endif // ZE_MAX_DRIVER_UUID_SIZE

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported initialization flags
    enum class init_flag_t
    {
        NONE = 0,                                       ///< default behavior
        GPU_ONLY = ZE_BIT(0),                           ///< only initialize GPU drivers

    };

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
    /// @throws result_t
    void __zecall
    Init(
        init_flag_t flags                               ///< [in] initialization flags
        );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Driver universal unique id (UUID)
    struct driver_uuid_t
    {
        uint8_t id[ZE_MAX_DRIVER_UUID_SIZE];            ///< Opaque data representing a driver UUID

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a driver instance handle
    class Driver
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported API versions
        /// 
        /// @details
        ///     - API versions contain major and minor attributes, use
        ///       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
        enum class api_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_driver_properties_t
        enum class properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_driver_ipc_properties_t
        enum class ipc_properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_mem_alloc_desc_t
        enum class device_mem_alloc_desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported memory allocation flags
        enum class device_mem_alloc_flag_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            BIAS_CACHED = ZE_BIT( 0 ),                      ///< device should cache allocation
            BIAS_UNCACHED = ZE_BIT( 1 ),                    ///< device should not cache allocation (UC)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_host_mem_alloc_desc_t
        enum class host_mem_alloc_desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported host memory allocation flags
        enum class host_mem_alloc_flag_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            BIAS_CACHED = ZE_BIT( 0 ),                      ///< host should cache allocation
            BIAS_UNCACHED = ZE_BIT( 1 ),                    ///< host should not cache allocation (UC)
            BIAS_WRITE_COMBINED = ZE_BIT( 2 ),              ///< host memory should be allocated write-combined (WC)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_memory_allocation_properties_t
        enum class memory_allocation_properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory allocation type
        enum class memory_type_t
        {
            UNKNOWN = 0,                                    ///< the memory pointed to is of unknown type
            HOST,                                           ///< the memory pointed to is a host allocation
            DEVICE,                                         ///< the memory pointed to is a device allocation
            SHARED,                                         ///< the memory pointed to is a shared ownership allocation

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported IPC memory flags
        enum class ipc_memory_flag_t
        {
            NONE = 0,                                       ///< No special flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Driver properties queried using ::zeDriverGetProperties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZE_DRIVER_PROPERTIES_VERSION_CURRENT
            driver_uuid_t uuid;                             ///< [out] universal unique identifier.
            uint32_t driverVersion;                         ///< [out] driver version
                                                            ///< The driver version is a non-zero, monotonically increasing value where
                                                            ///< higher values always indicate a more recent version.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief IPC properties queried using ::zeDriverGetIPCProperties
        struct ipc_properties_t
        {
            ipc_properties_version_t version = ipc_properties_version_t::CURRENT;   ///< [in] ::ZE_DRIVER_IPC_PROPERTIES_VERSION_CURRENT
            bool_t memsSupported;                           ///< [out] Supports passing memory allocations between processes. See
                                                            ///< ::::zeDriverGetMemIpcHandle.
            bool_t eventsSupported;                         ///< [out] Supports passing events between processes. See
                                                            ///< ::::zeEventPoolGetIpcHandle.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device mem alloc descriptor
        struct device_mem_alloc_desc_t
        {
            device_mem_alloc_desc_version_t version = device_mem_alloc_desc_version_t::CURRENT; ///< [in] ::ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT
            device_mem_alloc_flag_t flags = device_mem_alloc_flag_t::DEFAULT;   ///< [in] flags specifying additional allocation controls
            uint32_t ordinal = 0;                           ///< [in] ordinal of the device's local memory to allocate from;
                                                            ///< must be less than the count returned from ::zeDeviceGetMemoryProperties

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Host mem alloc descriptor
        struct host_mem_alloc_desc_t
        {
            host_mem_alloc_desc_version_t version = host_mem_alloc_desc_version_t::CURRENT; ///< [in] ::ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT
            host_mem_alloc_flag_t flags = host_mem_alloc_flag_t::DEFAULT;   ///< [in] flags specifying additional allocation controls

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory allocation properties queried using
        ///        ::zeDriverGetMemAllocProperties
        struct memory_allocation_properties_t
        {
            memory_allocation_properties_version_t version = memory_allocation_properties_version_t::CURRENT;   ///< [in] ::ZE_MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT
            memory_type_t type;                             ///< [out] type of allocated memory
            uint64_t id;                                    ///< [out] identifier for this allocation

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        driver_handle_t m_handle;                       ///< [in] handle of the driver instance

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Driver( void ) = delete;
        Driver( 
            driver_handle_t handle                          ///< [in] handle of the driver instance
            );

        ~Driver( void ) = default;

        Driver( Driver const& other ) = delete;
        void operator=( Driver const& other ) = delete;

        Driver( Driver&& other ) = delete;
        void operator=( Driver&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }

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
        /// @throws result_t
        static void __zecall
        Get(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                            ///< if count is zero, then the loader will update the value with the total
                                                            ///< number of drivers available.
                                                            ///< if count is non-zero, then the loader will only retrieve that number
                                                            ///< of drivers.
                                                            ///< if count is larger than the number of drivers available, then the
                                                            ///< loader will update the value with the correct number of drivers available.
            Driver** ppDrivers = nullptr                    ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the API version supported by the specified driver
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - api_version_t: api version
        /// 
        /// @throws result_t
        api_version_t __zecall
        GetApiVersion(
            void
            );

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
        /// @throws result_t
        void __zecall
        GetProperties(
            properties_t* pDriverProperties                 ///< [in,out] query result for driver properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves IPC attributes of the driver
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - ipc_properties_t: query result for IPC properties
        /// 
        /// @throws result_t
        ipc_properties_t __zecall
        GetIPCProperties(
            void
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
        /// @returns
        ///     - void*: pointer to extension function
        /// 
        /// @throws result_t
        void* __zecall
        GetExtensionFunctionAddress(
            const char* pFuncName                           ///< [in] name of the extension function
            );

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
        /// @returns
        ///     - void*: pointer to shared allocation
        /// 
        /// @throws result_t
        void* __zecall
        AllocSharedMem(
            const device_mem_alloc_desc_t* device_desc,     ///< [in] pointer to device mem alloc descriptor
            const host_mem_alloc_desc_t* host_desc,         ///< [in] pointer to host mem alloc descriptor
            size_t size,                                    ///< [in] size in bytes to allocate
            size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
            Device* pDevice = nullptr                       ///< [in][optional] device handle to associate with
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Allocates memory specific to a device
        /// 
        /// @details
        ///     - A device allocation is owned by a specific device.
        ///     - In general, a device allocation may only be accessed by the device
        ///       that owns it.
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - void*: pointer to device allocation
        /// 
        /// @throws result_t
        void* __zecall
        AllocDeviceMem(
            const device_mem_alloc_desc_t* device_desc,     ///< [in] pointer to device mem alloc descriptor
            size_t size,                                    ///< [in] size in bytes to allocate
            size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
            Device* pDevice                                 ///< [in] pointer to the device
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
        /// @returns
        ///     - void*: pointer to host allocation
        /// 
        /// @throws result_t
        void* __zecall
        AllocHostMem(
            const host_mem_alloc_desc_t* host_desc,         ///< [in] pointer to host mem alloc descriptor
            size_t size,                                    ///< [in] size in bytes to allocate
            size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
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
        /// @throws result_t
        void __zecall
        FreeMem(
            void* ptr                                       ///< [in][release] pointer to memory to free
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of a memory allocation
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - Device*: device associated with this allocation
        /// 
        /// @throws result_t
        void __zecall
        GetMemAllocProperties(
            const void* ptr,                                ///< [in] memory pointer to query
            memory_allocation_properties_t* pMemAllocProperties,///< [in,out] query result for memory allocation properties
            Device** ppDevice = nullptr                     ///< [out][optional] device associated with this allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves the base address and/or size of an allocation
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __zecall
        GetMemAddressRange(
            const void* ptr,                                ///< [in] memory pointer to query
            void** pBase = nullptr,                         ///< [in,out][optional] base address of the allocation
            size_t* pSize = nullptr                         ///< [in,out][optional] size of the allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates an IPC memory handle for the specified allocation in the
        ///        sending process
        /// 
        /// @details
        ///     - Takes a pointer to the base of a device memory allocation and exports
        ///       it for use in another process.
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - ipc_mem_handle_t: Returned IPC memory handle
        /// 
        /// @throws result_t
        ipc_mem_handle_t __zecall
        GetMemIpcHandle(
            const void* ptr                                 ///< [in] pointer to the device memory allocation
            );

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
        /// @returns
        ///     - void*: pointer to device allocation in this process
        /// 
        /// @throws result_t
        void* __zecall
        OpenMemIpcHandle(
            Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC memory handle
            ipc_mem_handle_t handle,                        ///< [in] IPC memory handle
            ipc_memory_flag_t flags                         ///< [in] flags controlling the operation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes an IPC memory handle in a receiving process
        /// 
        /// @details
        ///     - Closes an IPC memory handle by unmapping memory that was opened in
        ///       this process using ::zeDriverOpenMemIpcHandle.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same pointer.
        /// @throws result_t
        void __zecall
        CloseMemIpcHandle(
            const void* ptr                                 ///< [in][release] pointer to device allocation in this process
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts init_flag_t to std::string
    std::string to_string( const init_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts driver_uuid_t to std::string
    std::string to_string( const driver_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::api_version_t to std::string
    std::string to_string( const Driver::api_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::properties_version_t to std::string
    std::string to_string( const Driver::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::properties_t to std::string
    std::string to_string( const Driver::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_properties_version_t to std::string
    std::string to_string( const Driver::ipc_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_properties_t to std::string
    std::string to_string( const Driver::ipc_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_desc_version_t to std::string
    std::string to_string( const Driver::device_mem_alloc_desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_flag_t to std::string
    std::string to_string( const Driver::device_mem_alloc_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_desc_t to std::string
    std::string to_string( const Driver::device_mem_alloc_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_desc_version_t to std::string
    std::string to_string( const Driver::host_mem_alloc_desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_flag_t to std::string
    std::string to_string( const Driver::host_mem_alloc_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_desc_t to std::string
    std::string to_string( const Driver::host_mem_alloc_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_allocation_properties_version_t to std::string
    std::string to_string( const Driver::memory_allocation_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_type_t to std::string
    std::string to_string( const Driver::memory_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_allocation_properties_t to std::string
    std::string to_string( const Driver::memory_allocation_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_memory_flag_t to std::string
    std::string to_string( const Driver::ipc_memory_flag_t val );

} // namespace ze
#pragma endregion
#pragma region device
///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DEVICE_UUID_SIZE
/// @brief Maximum device universal unique id (UUID) size in bytes
#define ZE_MAX_DEVICE_UUID_SIZE  16
#endif // ZE_MAX_DEVICE_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DEVICE_NAME
/// @brief Maximum device name string size
#define ZE_MAX_DEVICE_NAME  256
#endif // ZE_MAX_DEVICE_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_SUBGROUPSIZE_COUNT
/// @brief Maximum number of subgroup sizes supported.
#define ZE_SUBGROUPSIZE_COUNT  8
#endif // ZE_SUBGROUPSIZE_COUNT

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_NATIVE_KERNEL_UUID_SIZE
/// @brief Maximum native kernel universal unique id (UUID) size in bytes
#define ZE_MAX_NATIVE_KERNEL_UUID_SIZE  16
#endif // ZE_MAX_NATIVE_KERNEL_UUID_SIZE

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Device universal unique id (UUID)
    struct device_uuid_t
    {
        uint8_t id[ZE_MAX_DEVICE_UUID_SIZE];            ///< Opaque data representing a device UUID

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a device
    class Device
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_properties_t
        enum class properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device types
        enum class type_t
        {
            GPU = 1,                                        ///< Graphics Processing Unit
            FPGA,                                           ///< Field Programmable Gate Array

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_compute_properties_t
        enum class compute_properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_kernel_properties_t
        enum class kernel_properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Floating Point capabilities
        /// 
        /// @details
        ///     - floating-point capabilities of the device.
        enum class fp_capabilities_t
        {
            FP_CAPS_NONE = 0,                               ///< None
            FP_CAPS_DENORM = ZE_BIT( 0 ),                   ///< Supports denorms
            FP_CAPS_INF_NAN = ZE_BIT( 1 ),                  ///< Supports INF and quiet NaNs
            FP_CAPS_ROUND_TO_NEAREST = ZE_BIT( 2 ),         ///< Supports rounding to nearest even rounding mode
            FP_CAPS_ROUND_TO_ZERO = ZE_BIT( 3 ),            ///< Supports rounding to zero.
            FP_CAPS_ROUND_TO_INF = ZE_BIT( 4 ),             ///< Supports rounding to both positive and negative INF.
            FP_CAPS_FMA = ZE_BIT( 5 ),                      ///< Supports IEEE754-2008 fused multiply-add.
            FP_CAPS_ROUNDED_DIVIDE_SQRT = ZE_BIT( 6 ),      ///< Supports rounding as defined by IEEE754 for divide and sqrt
                                                            ///< operations.
            FP_CAPS_SOFT_FLOAT = ZE_BIT( 7 ),               ///< Uses software implementation for basic floating-point operations.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_command_queue_group_properties_t
        enum class command_queue_group_properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_memory_properties_t
        enum class memory_properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_memory_access_properties_t
        enum class memory_access_properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory access capabilities
        /// 
        /// @details
        ///     - Supported access capabilities for different types of memory
        ///       allocations
        enum class memory_access_capabilities_t
        {
            MEMORY_ACCESS_NONE = 0,                         ///< Access not supported
            MEMORY_ACCESS = ZE_BIT( 0 ),                    ///< Supports load/store access
            MEMORY_ATOMIC_ACCESS = ZE_BIT( 1 ),             ///< Supports atomic access
            MEMORY_CONCURRENT_ACCESS = ZE_BIT( 2 ),         ///< Supports concurrent access
            MEMORY_CONCURRENT_ATOMIC_ACCESS = ZE_BIT( 3 ),  ///< Supports concurrent atomic access

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_cache_properties_t
        enum class cache_properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_image_properties_t
        enum class image_properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_p2p_properties_t
        enum class p2p_properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported Cache Config
        /// 
        /// @details
        ///     - Supported Cache Config (Default, Large SLM, Large Data Cache)
        enum class cache_config_t
        {
            DEFAULT = ZE_BIT( 0 ),                          ///< Default Config
            LARGE_SLM = ZE_BIT( 1 ),                        ///< Large SLM size
            LARGE_DATA = ZE_BIT( 2 ),                       ///< Large General Data size

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties queried using ::zeDeviceGetProperties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_PROPERTIES_VERSION_CURRENT
            type_t type;                                    ///< [out] generic device type
            uint32_t vendorId;                              ///< [out] vendor id from PCI configuration
            uint32_t deviceId;                              ///< [out] device id from PCI configuration
            device_uuid_t uuid;                             ///< [out] universal unique identifier.
            bool_t isSubdevice;                             ///< [out] If the device handle used for query represents a sub-device.
            uint32_t subdeviceId;                           ///< [out] sub-device id. Only valid if isSubdevice is true.
            uint32_t coreClockRate;                         ///< [out] Clock rate for device core.
            bool_t unifiedMemorySupported;                  ///< [out] Supports unified physical memory between Host and device.
            bool_t eccMemorySupported;                      ///< [out] Supports error correction memory access.
            bool_t onDemandPageFaultsSupported;             ///< [out] Supports on-demand page-faulting.
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

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device compute properties queried using ::zeDeviceGetComputeProperties
        struct compute_properties_t
        {
            compute_properties_version_t version = compute_properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT
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

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Native kernel universal unique id (UUID)
        struct native_kernel_uuid_t
        {
            uint8_t id[ZE_MAX_NATIVE_KERNEL_UUID_SIZE];     ///< Opaque data representing a native kernel UUID

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties queried using ::zeDeviceGetKernelProperties
        struct kernel_properties_t
        {
            kernel_properties_version_t version = kernel_properties_version_t::CURRENT; ///< [in] ::ZE_DEVICE_KERNEL_PROPERTIES_VERSION_CURRENT
            uint32_t spirvVersionSupported;                 ///< [out] Maximum supported SPIR-V version.
                                                            ///< Returns zero if SPIR-V is not supported.
                                                            ///< Contains major and minor attributes, use ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION.
            native_kernel_uuid_t nativeKernelSupported;     ///< [out] Compatibility UUID of supported native kernel.
                                                            ///< UUID may or may not be the same across driver release, devices, or
                                                            ///< operating systems.
                                                            ///< Application is responsible for ensuring UUID matches before creating
                                                            ///< module using
                                                            ///< previously created native kernel.
            bool_t fp16Supported;                           ///< [out] Supports 16-bit floating-point operations
            bool_t fp64Supported;                           ///< [out] Supports 64-bit floating-point operations
            bool_t int64AtomicsSupported;                   ///< [out] Supports 64-bit atomic operations
            bool_t dp4aSupported;                           ///< [out] Supports four component dot product and accumulate operations
            fp_capabilities_t halfFpCapabilities;           ///< [out] Capabilities for half-precision floating-point operations.
            fp_capabilities_t singleFpCapabilities;         ///< [out] Capabilities for single-precision floating-point operations.
            fp_capabilities_t doubleFpCapabilities;         ///< [out] Capabilities for double-precision floating-point operations.
            uint32_t maxArgumentsSize;                      ///< [out] Maximum kernel argument size that is supported.
            uint32_t printfBufferSize;                      ///< [out] Maximum size of internal buffer that holds output of printf
                                                            ///< calls from kernel.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Command queue group properties queried using
        ///        ::zeDeviceGetCommandQueueGroupProperties
        struct command_queue_group_properties_t
        {
            command_queue_group_properties_version_t version = command_queue_group_properties_version_t::CURRENT;   ///< [in] ::ZE_COMMAND_QUEUE_GROUP_PROPERTIES_VERSION_CURRENT
            bool_t computeSupported;                        ///< [out] command queue group supports enqueing compute commands.
            bool_t copySupported;                           ///< [out] command queue group supports enqueing copy commands.
            bool_t singleSliceSupported;                    ///< [out] command queue group supports reserving a single slice. 'slice'
                                                            ///< size is reported by ::ze_device_properties_t.
            bool_t cooperativeKernelsSupported;             ///< [out] command queue group supports cooperative kernels. See
                                                            ///< ::zeCommandListAppendLaunchCooperativeKernel for more details.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device local memory properties queried using
        ///        ::zeDeviceGetMemoryProperties
        struct memory_properties_t
        {
            memory_properties_version_t version = memory_properties_version_t::CURRENT; ///< [in] ::ZE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT
            uint32_t maxClockRate;                          ///< [out] Maximum clock rate for device memory.
            uint32_t maxBusWidth;                           ///< [out] Maximum bus width between device and memory.
            uint64_t totalSize;                             ///< [out] Total memory size in bytes.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device memory access properties queried using
        ///        ::zeDeviceGetMemoryAccessProperties
        struct memory_access_properties_t
        {
            memory_access_properties_version_t version = memory_access_properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT
            memory_access_capabilities_t hostAllocCapabilities; ///< [out] Bitfield describing host memory capabilities
            memory_access_capabilities_t deviceAllocCapabilities;   ///< [out] Bitfield describing device memory capabilities
            memory_access_capabilities_t sharedSingleDeviceAllocCapabilities;   ///< [out] Bitfield describing shared (single-device) memory capabilities
            memory_access_capabilities_t sharedCrossDeviceAllocCapabilities;///< [out] Bitfield describing shared (cross-device) memory capabilities
            memory_access_capabilities_t sharedSystemAllocCapabilities; ///< [out] Bitfield describing shared (system) memory capabilities

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device cache properties queried using ::zeDeviceGetCacheProperties
        struct cache_properties_t
        {
            cache_properties_version_t version = cache_properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT
            bool_t intermediateCacheControlSupported;       ///< [out] Support User control on Intermediate Cache (i.e. Resize SLM
                                                            ///< section vs Generic Cache)
            size_t intermediateCacheSize;                   ///< [out] Per-cache Intermediate Cache (L1/L2) size, in bytes
            uint32_t intermediateCachelineSize;             ///< [out] Cacheline size in bytes for intermediate cacheline (L1/L2).
            bool_t lastLevelCacheSizeControlSupported;      ///< [out] Support User control on Last Level Cache (i.e. Resize SLM
                                                            ///< section vs Generic Cache).
            size_t lastLevelCacheSize;                      ///< [out] Per-cache Last Level Cache (L3) size, in bytes
            uint32_t lastLevelCachelineSize;                ///< [out] Cacheline size in bytes for last-level cacheline (L3).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device image properties queried using ::zeDeviceGetComputeProperties
        struct image_properties_t
        {
            image_properties_version_t version = image_properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT
            bool_t supported;                               ///< [out] Supports reading and writing of images. See
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

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties queried using ::zeDeviceGetP2PProperties
        struct p2p_properties_t
        {
            p2p_properties_version_t version = p2p_properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_P2P_PROPERTIES_VERSION_CURRENT
            bool_t accessSupported;                         ///< [out] Supports access between peer devices.
            bool_t atomicsSupported;                        ///< [out] Supports atomics between peer devices.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        device_handle_t m_handle;                       ///< [in] handle of device object
        Driver* m_pDriver;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Device( void ) = delete;
        Device( 
            device_handle_t handle,                         ///< [in] handle of device object
            Driver* pDriver                                 ///< [in] pointer to owner object
            );

        ~Device( void ) = default;

        Device( Device const& other ) = delete;
        void operator=( Device const& other ) = delete;

        Device( Device&& other ) = delete;
        void operator=( Device&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDriver( void ) const { return m_pDriver; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves devices within a driver
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __zecall
        Get(
            Driver* pDriver,                                ///< [in] pointer to the driver instance
            uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of devices available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                            ///< if count is larger than the number of devices available, then the
                                                            ///< driver will update the value with the correct number of devices available.
            Device** ppDevices = nullptr                    ///< [in,out][optional][range(0, *pCount)] array of pointer to devices
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
        /// @throws result_t
        void __zecall
        GetSubDevices(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of sub-devices available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of sub-devices.
                                                            ///< if count is larger than the number of sub-devices available, then the
                                                            ///< driver will update the value with the correct number of sub-devices available.
            Device** ppSubdevices = nullptr                 ///< [in,out][optional][range(0, *pCount)] array of pointer to sub-devices
            );

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
        /// @throws result_t
        void __zecall
        GetProperties(
            properties_t* pDeviceProperties                 ///< [in,out] query result for device properties
            );

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
        /// @throws result_t
        void __zecall
        GetComputeProperties(
            compute_properties_t* pComputeProperties        ///< [in,out] query result for compute properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves kernel properties of the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetKernelProperties(
            kernel_properties_t* pKernelProperties          ///< [in,out] query result for kernel properties
            );

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
        /// @throws result_t
        void __zecall
        GetCommandQueueGroupProperties(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of command queue group properties available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< command queue group properties.
                                                            ///< if count is larger than the number of command queue group properties
                                                            ///< available, then the driver will update the value with the correct
                                                            ///< number of command queue group properties available.
            command_queue_group_properties_t* pCommandQueueGroupProperties = nullptr///< [in,out][optional][range(0, *pCount)] array of query results for
                                                            ///< command queue group properties
            );

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
        /// @throws result_t
        void __zecall
        GetMemoryProperties(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of memory properties available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< memory properties.
                                                            ///< if count is larger than the number of memory properties available,
                                                            ///< then the driver will update the value with the correct number of
                                                            ///< memory properties available.
            memory_properties_t* pMemProperties = nullptr   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                            ///< memory properties
            );

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
        /// @throws result_t
        void __zecall
        GetMemoryAccessProperties(
            memory_access_properties_t* pMemAccessProperties///< [in,out] query result for memory access properties
            );

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
        /// @throws result_t
        void __zecall
        GetCacheProperties(
            cache_properties_t* pCacheProperties            ///< [in,out] query result for cache properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves image properties of the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetImageProperties(
            image_properties_t* pImageProperties            ///< [in,out] query result for image properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves Peer-to-Peer properties between one device and a peer
        ///        devices
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetP2PProperties(
            Device* pPeerDevice,                            ///< [in] pointer to the peer device with the allocation
            p2p_properties_t* pP2PProperties                ///< [in,out] Peer-to-Peer properties between source and peer device
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
        /// @returns
        ///     - bool_t: returned access capability
        /// 
        /// @throws result_t
        bool_t __zecall
        CanAccessPeer(
            Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the preferred Last Level cache configuration for a device.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same device handle.
        /// @throws result_t
        void __zecall
        SetLastLevelCacheConfig(
            cache_config_t CacheConfig                      ///< [in] CacheConfig
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
        /// @throws result_t
        void __zecall
        SystemBarrier(
            void
            );

#if ZE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Registers OpenCL memory with 'One API'
        /// @returns
        ///     - void*: pointer to device allocation
        /// 
        /// @throws result_t
        void* __zecall
        RegisterCLMemory(
            cl_context context,                             ///< [in] the OpenCL context that created the memory
            cl_mem mem                                      ///< [in] the OpenCL memory to register
            );
#endif // ZE_ENABLE_OCL_INTEROP

#if ZE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Registers OpenCL program with 'One API'
        /// @returns
        ///     - Module*: pointer to handle of module object created
        /// 
        /// @throws result_t
        Module* __zecall
        RegisterCLProgram(
            cl_context context,                             ///< [in] the OpenCL context that created the program
            cl_program program                              ///< [in] the OpenCL program to register
            );
#endif // ZE_ENABLE_OCL_INTEROP

#if ZE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Registers OpenCL command queue with 'One API'
        /// @returns
        ///     - CommandQueue*: pointer to handle of command queue object created
        /// 
        /// @throws result_t
        CommandQueue* __zecall
        RegisterCLCommandQueue(
            cl_context context,                             ///< [in] the OpenCL context that created the command queue
            cl_command_queue command_queue                  ///< [in] the OpenCL command queue to register
            );
#endif // ZE_ENABLE_OCL_INTEROP

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Makes memory resident for the device.
        /// 
        /// @details
        ///     - If the application does not properly manage residency then the device
        ///       may experience unrecoverable page-faults.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        MakeMemoryResident(
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
        /// @throws result_t
        void __zecall
        EvictMemory(
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
        /// @throws result_t
        void __zecall
        MakeImageResident(
            Image* pImage                                   ///< [in] pointer to image to make resident
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
        /// @throws result_t
        void __zecall
        EvictImage(
            Image* pImage                                   ///< [in] pointer to image to make evict
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts device_uuid_t to std::string
    std::string to_string( const device_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::properties_version_t to std::string
    std::string to_string( const Device::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::type_t to std::string
    std::string to_string( const Device::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::properties_t to std::string
    std::string to_string( const Device::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::compute_properties_version_t to std::string
    std::string to_string( const Device::compute_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::compute_properties_t to std::string
    std::string to_string( const Device::compute_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::kernel_properties_version_t to std::string
    std::string to_string( const Device::kernel_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::native_kernel_uuid_t to std::string
    std::string to_string( const Device::native_kernel_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::fp_capabilities_t to std::string
    std::string to_string( const Device::fp_capabilities_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::kernel_properties_t to std::string
    std::string to_string( const Device::kernel_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::command_queue_group_properties_version_t to std::string
    std::string to_string( const Device::command_queue_group_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::command_queue_group_properties_t to std::string
    std::string to_string( const Device::command_queue_group_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_properties_version_t to std::string
    std::string to_string( const Device::memory_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_properties_t to std::string
    std::string to_string( const Device::memory_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_properties_version_t to std::string
    std::string to_string( const Device::memory_access_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_capabilities_t to std::string
    std::string to_string( const Device::memory_access_capabilities_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_properties_t to std::string
    std::string to_string( const Device::memory_access_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_properties_version_t to std::string
    std::string to_string( const Device::cache_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_properties_t to std::string
    std::string to_string( const Device::cache_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::image_properties_version_t to std::string
    std::string to_string( const Device::image_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::image_properties_t to std::string
    std::string to_string( const Device::image_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_properties_version_t to std::string
    std::string to_string( const Device::p2p_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_properties_t to std::string
    std::string to_string( const Device::p2p_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_config_t to std::string
    std::string to_string( const Device::cache_config_t val );

} // namespace ze
#pragma endregion
#pragma region cmdqueue
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command queue
    class CommandQueue
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_command_queue_desc_t
        enum class desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default behavior
            SINGLE_SLICE_ONLY = ZE_BIT(0),                  ///< command queue reserves and cannot comsume more than a single slice.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue modes
        enum class mode_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            SYNCHRONOUS,                                    ///< Device execution always completes immediately on execute;
                                                            ///< Host thread is blocked using wait on implicit synchronization object
            ASYNCHRONOUS,                                   ///< Device execution is scheduled and will complete in future;
                                                            ///< explicit synchronization object must be used to determine completeness

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue priorities
        enum class priority_t
        {
            NORMAL = 0,                                     ///< [default] normal priority
            LOW,                                            ///< lower priority than normal
            HIGH,                                           ///< higher priority than normal

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Command Queue descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT
            uint32_t ordinal;                               ///< [in] command queue group ordinal
            flag_t flags;                                   ///< [in] usage flags
            mode_t mode = mode_t::DEFAULT;                  ///< [in] operation mode
            priority_t priority = priority_t::NORMAL;       ///< [in] priority

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        command_queue_handle_t m_handle;                ///< [in] handle of command queue object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the command queue object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandQueue( void ) = delete;
        CommandQueue( 
            command_queue_handle_t handle,                  ///< [in] handle of command queue object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the command queue object
            );

        ~CommandQueue( void ) = default;

        CommandQueue( CommandQueue const& other ) = delete;
        void operator=( CommandQueue const& other ) = delete;

        CommandQueue( CommandQueue&& other ) = delete;
        void operator=( CommandQueue&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - CommandQueue*: pointer to handle of command queue object created
        /// 
        /// @throws result_t
        static CommandQueue* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device object
            const desc_t* desc                              ///< [in] pointer to command queue descriptor
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
        /// @throws result_t
        static void __zecall
        Destroy(
            CommandQueue* pCommandQueue                     ///< [in][release] pointer to command queue object to destroy
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
        /// @throws result_t
        void __zecall
        ExecuteCommandLists(
            uint32_t numCommandLists,                       ///< [in] number of command lists to execute
            CommandList** ppCommandLists,                   ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                            ///< to execute
            Fence* pFence = nullptr                         ///< [in][optional] pointer to the fence to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Synchronizes a command queue by waiting on the host.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t __zecall
        Synchronize(
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                            ///< returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                            ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                            ///< if UINT32_MAX, then function will not return until complete or device
                                                            ///< is lost.
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_version_t to std::string
    std::string to_string( const CommandQueue::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::flag_t to std::string
    std::string to_string( const CommandQueue::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::mode_t to std::string
    std::string to_string( const CommandQueue::mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::priority_t to std::string
    std::string to_string( const CommandQueue::priority_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_t to std::string
    std::string to_string( const CommandQueue::desc_t val );

} // namespace ze
#pragma endregion
#pragma region cmdlist
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_command_list_desc_t
        enum class desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command list creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default behavior
            RELAXED_ORDERING = ZE_BIT(0),                   ///< driver may reorder programs and copys between barriers and
                                                            ///< synchronization primitives.
                                                            ///< using this flag may increase Host overhead of ::zeCommandListClose.
                                                            ///< therefore, this flag should **not** be set for low-latency usage-models.
            MAXIMIZE_THROUGHPUT = ZE_BIT(1),                ///< driver may perform additional optimizations that increase dexecution
                                                            ///< throughput. 
                                                            ///< using this flag may increase Host overhead of ::zeCommandListClose and ::zeCommandQueueExecuteCommandLists.
                                                            ///< therefore, this flag should **not** be set for low-latency usage-models.
            EXPLICIT_ONLY = ZE_BIT(2),                      ///< command list should be optimized for submission to a single command
                                                            ///< queue and device engine.
                                                            ///< driver **must** disable any implicit optimizations for distributing
                                                            ///< work across multiple engines.
                                                            ///< this flag should be used when applications want full control over
                                                            ///< multi-engine submission and scheduling.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported memory advice hints
        enum class memory_advice_t
        {
            SET_READ_MOSTLY = 0,                            ///< hint that memory will be read from frequently and written to rarely
            CLEAR_READ_MOSTLY,                              ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_READ_MOSTLY
            SET_PREFERRED_LOCATION,                         ///< hint that the preferred memory location is the specified device
            CLEAR_PREFERRED_LOCATION,                       ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_PREFERRED_LOCATION
            SET_ACCESSED_BY,                                ///< hint that memory will be accessed by the specified device
            CLEAR_ACCESSED_BY,                              ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_ACCESSED_BY
            SET_NON_ATOMIC_MOSTLY,                          ///< hints that memory will mostly be accessed non-atomically
            CLEAR_NON_ATOMIC_MOSTLY,                        ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_NON_ATOMIC_MOSTLY
            BIAS_CACHED,                                    ///< hints that memory should be cached
            BIAS_UNCACHED,                                  ///< hints that memory should be not be cached

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Command List descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_COMMAND_LIST_DESC_VERSION_CURRENT
            uint32_t commandQueueGroupOrdinal;              ///< [in] command queue group ordinal to which this command list will be
                                                            ///< submitted
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copy region descriptor
        struct copy_region_t
        {
            uint32_t originX;                               ///< [in] The origin x offset for region in bytes
            uint32_t originY;                               ///< [in] The origin y offset for region in rows
            uint32_t originZ;                               ///< [in] The origin z offset for region in slices
            uint32_t width;                                 ///< [in] The region width relative to origin in bytes
            uint32_t height;                                ///< [in] The region height relative to origin in rows
            uint32_t depth;                                 ///< [in] The region depth relative to origin in slices. Set this to 0 for
                                                            ///< 2D copy.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Region descriptor
        struct image_region_t
        {
            uint32_t originX;                               ///< [in] The origin x offset for region in pixels
            uint32_t originY;                               ///< [in] The origin y offset for region in pixels
            uint32_t originZ;                               ///< [in] The origin z offset for region in pixels
            uint32_t width;                                 ///< [in] The region width relative to origin in pixels
            uint32_t height;                                ///< [in] The region height relative to origin in pixels
            uint32_t depth;                                 ///< [in] The region depth relative to origin. For 1D or 2D images, set
                                                            ///< this to 1.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel dispatch group count.
        struct group_count_t
        {
            uint32_t groupCountX = 0;                       ///< [in] number of thread groups in X dimension
            uint32_t groupCountY = 0;                       ///< [in] number of thread groups in Y dimension
            uint32_t groupCountZ = 0;                       ///< [in] number of thread groups in Z dimension

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        command_list_handle_t m_handle;                 ///< [in] handle of command list object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the command list object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandList( void ) = delete;
        CommandList( 
            command_list_handle_t handle,                   ///< [in] handle of command list object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the command list object
            );

        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - CommandList*: pointer to handle of command list object created
        /// 
        /// @throws result_t
        static CommandList* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device object
            const desc_t* desc                              ///< [in] pointer to command list descriptor
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
        /// @returns
        ///     - CommandList*: pointer to handle of command list object created
        /// 
        /// @throws result_t
        static CommandList* __zecall
        CreateImmediate(
            Device* pDevice,                                ///< [in] pointer to the device object
            const CommandQueue::desc_t* altdesc             ///< [in] pointer to command queue descriptor
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
        /// @throws result_t
        static void __zecall
        Destroy(
            CommandList* pCommandList                       ///< [in][release] pointer to command list object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes a command list; ready to be executed by a command queue.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        Close(
            void
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
        /// @throws result_t
        void __zecall
        Reset(
            void
            );

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
        /// @throws result_t
        void __zecall
        AppendBarrier(
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing barrier
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
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
        /// @throws result_t
        void __zecall
        AppendMemoryRangesBarrier(
            uint32_t numRanges,                             ///< [in] number of memory ranges
            const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
            const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing barrier
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before executing barrier
            );

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
        /// @throws result_t
        void __zecall
        AppendMemoryCopy(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            size_t size,                                    ///< [in] size in bytes to copy
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
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
        /// @throws result_t
        void __zecall
        AppendMemoryFill(
            void* ptr,                                      ///< [in] pointer to memory to initialize
            const void* pattern,                            ///< [in] pointer to value to initialize memory to
            size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
            size_t size,                                    ///< [in] size in bytes to initialize
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

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
        /// @throws result_t
        void __zecall
        AppendMemoryCopyRegion(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            const copy_region_t* dstRegion,                 ///< [in] pointer to destination region to copy to
            uint32_t dstPitch,                              ///< [in] destination pitch in bytes
            uint32_t dstSlicePitch,                         ///< [in] destination slice pitch in bytes. This is required for 3D region
                                                            ///< copies where ::ze_copy_region_t::depth is not 0, otherwise it's
                                                            ///< ignored.
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            const copy_region_t* srcRegion,                 ///< [in] pointer to source region to copy from
            uint32_t srcPitch,                              ///< [in] source pitch in bytes
            uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                            ///< copies where ::ze_copy_region_t::depth is not 0, otherwise it's
                                                            ///< ignored.
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
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
        /// @throws result_t
        void __zecall
        AppendImageCopy(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

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
        /// @throws result_t
        void __zecall
        AppendImageCopyRegion(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            const image_region_t* pDstRegion = nullptr,     ///< [in][optional] destination region descriptor
            const image_region_t* pSrcRegion = nullptr,     ///< [in][optional] source region descriptor
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
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
        /// @throws result_t
        void __zecall
        AppendImageCopyToMemory(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            const image_region_t* pSrcRegion = nullptr,     ///< [in][optional] source region descriptor
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
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
        /// @throws result_t
        void __zecall
        AppendImageCopyFromMemory(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            const image_region_t* pDstRegion = nullptr,     ///< [in][optional] destination region descriptor
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
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
        /// @throws result_t
        void __zecall
        AppendMemoryPrefetch(
            const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
            size_t size                                     ///< [in] size in bytes of the memory range to prefetch
            );

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
        /// @throws result_t
        void __zecall
        AppendMemAdvise(
            Device* pDevice,                                ///< [in] device associated with the memory advice
            const void* ptr,                                ///< [in] Pointer to the start of the memory range
            size_t size,                                    ///< [in] Size in bytes of the memory range
            memory_advice_t advice                          ///< [in] Memory advice for the memory range
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
        /// @throws result_t
        void __zecall
        AppendSignalEvent(
            Event* pEvent                                   ///< [in] pointer to the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends wait on event(s) on the device into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        AppendWaitOnEvents(
            uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
            Event** ppEvents                                ///< [in][range(0, numEvents)] pointer to the events to wait on before
                                                            ///< continuing
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
        /// @throws result_t
        void __zecall
        AppendEventReset(
            Event* pEvent                                   ///< [in] pointer to the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Launch kernel over one or more work groups.
        /// 
        /// @details
        ///     - This may **only** be called for a command list created with command
        ///       queue group ordinal that supports compute.
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        AppendLaunchKernel(
            Kernel* pKernel,                                ///< [in] pointer to the kernel object
            const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
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
        /// @throws result_t
        void __zecall
        AppendLaunchCooperativeKernel(
            Kernel* pKernel,                                ///< [in] pointer to the kernel object
            const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
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
        /// @throws result_t
        void __zecall
        AppendLaunchKernelIndirect(
            Kernel* pKernel,                                ///< [in] pointer to the kernel object
            const group_count_t* pLaunchArgumentsBuffer,    ///< [in] pointer to device buffer that will contain thread group launch
                                                            ///< arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
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
        /// @throws result_t
        void __zecall
        AppendLaunchMultipleKernelsIndirect(
            uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
            Kernel** ppKernels,                             ///< [in][range(0, numKernels)] handles of the kernel objects
            const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                            ///< number of kernels to launch; value must be less-than or equal-to
                                                            ///< numKernels
            const group_count_t* pLaunchArgumentsBuffer,    ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                            ///< a contiguous array of thread group launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_version_t to std::string
    std::string to_string( const CommandList::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::flag_t to std::string
    std::string to_string( const CommandList::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_t to std::string
    std::string to_string( const CommandList::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::copy_region_t to std::string
    std::string to_string( const CommandList::copy_region_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::image_region_t to std::string
    std::string to_string( const CommandList::image_region_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::memory_advice_t to std::string
    std::string to_string( const CommandList::memory_advice_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::group_count_t to std::string
    std::string to_string( const CommandList::group_count_t val );

} // namespace ze
#pragma endregion
#pragma region barrier
namespace ze
{
} // namespace ze

namespace ze
{
} // namespace ze
#pragma endregion
#pragma region cl_interop
namespace ze
{
} // namespace ze

namespace ze
{
} // namespace ze
#pragma endregion
#pragma region copy
namespace ze
{
} // namespace ze

namespace ze
{
} // namespace ze
#pragma endregion
#pragma region event
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for event pool
    class EventPool
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_event_pool_desc_t
        enum class desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported event pool creation flags
        enum class flag_t
        {
            DEFAULT = 0,                                    ///< signals and waits visible to the entire device and peer devices
            HOST_VISIBLE = ZE_BIT(0),                       ///< signals and waits are also visible to host
            IPC = ZE_BIT(1),                                ///< signals and waits may be shared across processes
            TIMESTAMP = ZE_BIT(2),                          ///< Indicates all events in pool will contain timestamp information that
                                                            ///< can be queried using ::zeEventGetTimestamp

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported timestamp types
        enum class event_timestamp_type_t
        {
            EVENT_TIMESTAMP_GLOBAL_START = 0,               ///< wall-clock time start in GPU clocks for event. Data is uint64_t.
            EVENT_TIMESTAMP_GLOBAL_END,                     ///< wall-clock time end in GPU clocks for event.Data is uint64_t.
            EVENT_TIMESTAMP_CONTEXT_START,                  ///< context time start in GPU clocks for event.  Only includes time while
                                                            ///< HW context is actively running on GPU. Data is uint64_t.
            EVENT_TIMESTAMP_CONTEXT_END,                    ///< context time end in GPU clocks for event.  Only includes time while HW
                                                            ///< context is actively running on GPU. Data is uint64_t.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event pool descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_EVENT_POOL_DESC_VERSION_CURRENT
            flag_t flags = flag_t::DEFAULT;                 ///< [in] creation flags
            uint32_t count;                                 ///< [in] number of events within the pool

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        event_pool_handle_t m_handle;                   ///< [in] handle of event pool object
        Driver* m_pDriver;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the event pool object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        EventPool( void ) = delete;
        EventPool( 
            event_pool_handle_t handle,                     ///< [in] handle of event pool object
            Driver* pDriver,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the event pool object
            );

        ~EventPool( void ) = default;

        EventPool( EventPool const& other ) = delete;
        void operator=( EventPool const& other ) = delete;

        EventPool( EventPool&& other ) = delete;
        void operator=( EventPool&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDriver( void ) const { return m_pDriver; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a pool for a set of event(s) for the driver
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - EventPool*: pointer handle of event pool object created
        /// 
        /// @throws result_t
        static EventPool* __zecall
        Create(
            Driver* pDriver,                                ///< [in] pointer to the driver instance
            const desc_t* desc,                             ///< [in] pointer to event pool descriptor
            uint32_t numDevices,                            ///< [in] number of device handles
            Device** ppDevices = nullptr                    ///< [in][optional][range(0, numDevices)] array of device handles which
                                                            ///< have visibility to the event pool.
                                                            ///< if nullptr, then event pool is visible to all devices supported by the
                                                            ///< driver instance.
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
        /// @throws result_t
        static void __zecall
        Destroy(
            EventPool* pEventPool                           ///< [in][release] pointer to event pool object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Gets an IPC event pool handle for the specified event handle that can
        ///        be shared with another process.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - ipc_event_pool_handle_t: Returned IPC event handle
        /// 
        /// @throws result_t
        ipc_event_pool_handle_t __zecall
        GetIpcHandle(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Opens an IPC event pool handle to retrieve an event pool handle from
        ///        another process.
        /// 
        /// @details
        ///     - The event handle in this process should not be freed with
        ///       ::zeEventPoolDestroy, but rather with ::zeEventPoolCloseIpcHandle.
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - EventPool*: pointer handle of event pool object created
        /// 
        /// @throws result_t
        static EventPool* __zecall
        OpenIpcHandle(
            Driver* pDriver,                                ///< [in] pointer to the driver to associate with the IPC event pool handle
            ipc_event_pool_handle_t pIpc                    ///< [in] IPC event handle
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes an IPC event handle in the current process.
        /// 
        /// @details
        ///     - Closes an IPC event handle by destroying events that were opened in
        ///       this process using ::zeEventPoolOpenIpcHandle.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same event pool handle.
        /// @throws result_t
        void __zecall
        CloseIpcHandle(
            void
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for event
    class Event
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_event_desc_t
        enum class desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported event scope flags
        enum class scope_flag_t
        {
            NONE = 0,                                       ///< execution synchronization only; no cache hierarchies are flushed or
                                                            ///< invalidated
            SUBDEVICE = ZE_BIT(0),                          ///< cache hierarchies are flushed or invalidated sufficient for local
                                                            ///< sub-device access
            DEVICE = ZE_BIT(1),                             ///< cache hierarchies are flushed or invalidated sufficient for global
                                                            ///< device access and peer device access
            HOST = ZE_BIT(2),                               ///< cache hierarchies are flushed or invalidated sufficient for device and
                                                            ///< host access

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_EVENT_DESC_VERSION_CURRENT
            uint32_t index;                                 ///< [in] index of the event within the pool; must be less-than the count
                                                            ///< specified during pool creation
            scope_flag_t signal = scope_flag_t::NONE;       ///< [in] defines the scope of relevant cache hierarchies to flush on a
                                                            ///< signal action before the event is triggered
            scope_flag_t wait = scope_flag_t::NONE;         ///< [in] defines the scope of relevant cache hierarchies to invalidate on
                                                            ///< a wait action after the event is complete

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        event_handle_t m_handle;                        ///< [in] handle of event object
        EventPool* m_pEventPool;                        ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the event object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Event( void ) = delete;
        Event( 
            event_handle_t handle,                          ///< [in] handle of event object
            EventPool* pEventPool,                          ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the event object
            );

        ~Event( void ) = default;

        Event( Event const& other ) = delete;
        void operator=( Event const& other ) = delete;

        Event( Event&& other ) = delete;
        void operator=( Event&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getEventpool( void ) const { return m_pEventPool; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Event*: pointer to handle of event object created
        /// 
        /// @throws result_t
        static Event* __zecall
        Create(
            EventPool* pEventPool,                          ///< [in] pointer to the event pool
            const desc_t* desc                              ///< [in] pointer to event descriptor
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
        /// @throws result_t
        static void __zecall
        Destroy(
            Event* pEvent                                   ///< [in][release] pointer to event object to destroy
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
        /// @throws result_t
        void __zecall
        HostSignal(
            void
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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t __zecall
        HostSynchronize(
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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t __zecall
        QueryStatus(
            void
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
        /// @throws result_t
        void __zecall
        HostReset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query timestamp information associated with an event. Event must come
        ///        from an event pool that was created using
        ///        ::ZE_EVENT_POOL_FLAG_TIMESTAMP flag.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetTimestamp(
            EventPool::event_timestamp_type_t timestampType,///< [in] specifies timestamp type to query for that is associated with
                                                            ///< hEvent.
            void* dstptr                                    ///< [in,out] pointer to memory for where timestamp will be written to. The
                                                            ///< size of timestamp is specified in the ::ze_event_timestamp_type_t
                                                            ///< definition.
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_version_t to std::string
    std::string to_string( const EventPool::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::flag_t to std::string
    std::string to_string( const EventPool::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_t to std::string
    std::string to_string( const EventPool::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::event_timestamp_type_t to std::string
    std::string to_string( const EventPool::event_timestamp_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_version_t to std::string
    std::string to_string( const Event::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::scope_flag_t to std::string
    std::string to_string( const Event::scope_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_t to std::string
    std::string to_string( const Event::desc_t val );

} // namespace ze
#pragma endregion
#pragma region fence
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for fence
    class Fence
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_fence_desc_t
        enum class desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported fence creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default behavior

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fence descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_FENCE_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        fence_handle_t m_handle;                        ///< [in] handle of fence object
        CommandQueue* m_pCommandQueue;                  ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the fence object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Fence( void ) = delete;
        Fence( 
            fence_handle_t handle,                          ///< [in] handle of fence object
            CommandQueue* pCommandQueue,                    ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the fence object
            );

        ~Fence( void ) = default;

        Fence( Fence const& other ) = delete;
        void operator=( Fence const& other ) = delete;

        Fence( Fence&& other ) = delete;
        void operator=( Fence&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getCommandqueue( void ) const { return m_pCommandQueue; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Fence*: pointer to handle of fence object created
        /// 
        /// @throws result_t
        static Fence* __zecall
        Create(
            CommandQueue* pCommandQueue,                    ///< [in] pointer to command queue
            const desc_t* desc                              ///< [in] pointer to fence descriptor
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
        /// @throws result_t
        static void __zecall
        Destroy(
            Fence* pFence                                   ///< [in][release] pointer to fence object to destroy
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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t __zecall
        HostSynchronize(
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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t __zecall
        QueryStatus(
            void
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
        /// @throws result_t
        void __zecall
        Reset(
            void
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_version_t to std::string
    std::string to_string( const Fence::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::flag_t to std::string
    std::string to_string( const Fence::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_t to std::string
    std::string to_string( const Fence::desc_t val );

} // namespace ze
#pragma endregion
#pragma region image
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for image
    class Image
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_image_desc_t
        enum class desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image creation flags
        enum class flag_t
        {
            PROGRAM_READ = ZE_BIT( 0 ),                     ///< programs will read contents
            PROGRAM_WRITE = ZE_BIT( 1 ),                    ///< programs will write contents
            BIAS_CACHED = ZE_BIT( 2 ),                      ///< device should cache contents
            BIAS_UNCACHED = ZE_BIT( 3 ),                    ///< device should not cache contents

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image types
        enum class type_t
        {
            _1D,                                            ///< 1D
            _1DARRAY,                                       ///< 1D array
            _2D,                                            ///< 2D
            _2DARRAY,                                       ///< 2D array
            _3D,                                            ///< 3D
            BUFFER,                                         ///< Buffer

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image format layouts
        enum class format_layout_t
        {
            _8,                                             ///< 8-bit single component layout
            _16,                                            ///< 16-bit single component layout
            _32,                                            ///< 32-bit single component layout
            _8_8,                                           ///< 2-component 8-bit layout
            _8_8_8_8,                                       ///< 4-component 8-bit layout
            _16_16,                                         ///< 2-component 16-bit layout
            _16_16_16_16,                                   ///< 4-component 16-bit layout
            _32_32,                                         ///< 2-component 32-bit layout
            _32_32_32_32,                                   ///< 4-component 32-bit layout
            _10_10_10_2,                                    ///< 4-component 10_10_10_2 layout
            _11_11_10,                                      ///< 3-component 11_11_10 layout
            _5_6_5,                                         ///< 3-component 5_6_5 layout
            _5_5_5_1,                                       ///< 4-component 5_5_5_1 layout
            _4_4_4_4,                                       ///< 4-component 4_4_4_4 layout
            Y8,                                             ///< Media Format: Y8. Format type and swizzle is ignored for this.
            NV12,                                           ///< Media Format: NV12. Format type and swizzle is ignored for this.
            YUYV,                                           ///< Media Format: YUYV. Format type and swizzle is ignored for this.
            VYUY,                                           ///< Media Format: VYUY. Format type and swizzle is ignored for this.
            YVYU,                                           ///< Media Format: YVYU. Format type and swizzle is ignored for this.
            UYVY,                                           ///< Media Format: UYVY. Format type and swizzle is ignored for this.
            AYUV,                                           ///< Media Format: AYUV. Format type and swizzle is ignored for this.
            YUAV,                                           ///< Media Format: YUAV. Format type and swizzle is ignored for this.
            P010,                                           ///< Media Format: P010. Format type and swizzle is ignored for this.
            Y410,                                           ///< Media Format: Y410. Format type and swizzle is ignored for this.
            P012,                                           ///< Media Format: P012. Format type and swizzle is ignored for this.
            Y16,                                            ///< Media Format: Y16. Format type and swizzle is ignored for this.
            P016,                                           ///< Media Format: P016. Format type and swizzle is ignored for this.
            Y216,                                           ///< Media Format: Y216. Format type and swizzle is ignored for this.
            P216,                                           ///< Media Format: P216. Format type and swizzle is ignored for this.
            P416,                                           ///< Media Format: P416. Format type and swizzle is ignored for this.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image format types
        enum class format_type_t
        {
            UINT,                                           ///< Unsigned integer
            SINT,                                           ///< Signed integer
            UNORM,                                          ///< Unsigned normalized integer
            SNORM,                                          ///< Signed normalized integer
            FLOAT,                                          ///< Float

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image format component swizzle into channel
        enum class format_swizzle_t
        {
            R,                                              ///< Red component
            G,                                              ///< Green component
            B,                                              ///< Blue component
            A,                                              ///< Alpha component
            _0,                                             ///< Zero
            _1,                                             ///< One
            X,                                              ///< Don't care

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_image_properties_t
        enum class properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported sampler filtering flags
        enum class sampler_filter_flags_t
        {
            NONE = 0,                                       ///< device does not support filtering
            POINT = ZE_BIT(0),                              ///< device supports point filtering
            LINEAR = ZE_BIT(1),                             ///< device supports linear filtering

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Image format descriptor
        struct format_desc_t
        {
            format_layout_t layout;                         ///< [in] image format component layout
            format_type_t type;                             ///< [in] image format type. Media formats can't be used for
                                                            ///< ::ZE_IMAGE_TYPE_BUFFER.
            format_swizzle_t x;                             ///< [in] image component swizzle into channel x
            format_swizzle_t y;                             ///< [in] image component swizzle into channel y
            format_swizzle_t z;                             ///< [in] image component swizzle into channel z
            format_swizzle_t w;                             ///< [in] image component swizzle into channel w

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Image descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_IMAGE_DESC_VERSION_CURRENT
            flag_t flags;                                   ///< [in] creation flags
            type_t type;                                    ///< [in] image type
            format_desc_t format;                           ///< [in] image format
            uint64_t width = 0;                             ///< [in] width in pixels for ::ze_image_type_t::1D/2D/3D and bytes for
                                                            ///< Buffer, see ::ze_device_image_properties_t::maxImageDims1D/2D/3D and
                                                            ///< maxImageBufferSize.
            uint32_t height = 0;                            ///< [in] height in pixels (2D or 3D only), see
                                                            ///< ::ze_device_image_properties_t::maxImageDims2D/3D
            uint32_t depth = 0;                             ///< [in] depth in pixels (3D only), see
                                                            ///< ::ze_device_image_properties_t::maxImageDims3D
            uint32_t arraylevels = 1;                       ///< [in] array levels (array types only), see
                                                            ///< ::ze_device_image_properties_t::maxImageArraySlices
            uint32_t miplevels = 0;                         ///< [in] mipmap levels (must be 0)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Image properties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZE_IMAGE_PROPERTIES_VERSION_CURRENT
            sampler_filter_flags_t samplerFilterFlags;      ///< [out] supported sampler filtering

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        image_handle_t m_handle;                        ///< [in] handle of image object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the image object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Image( void ) = delete;
        Image( 
            image_handle_t handle,                          ///< [in] handle of image object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the image object
            );

        ~Image( void ) = default;

        Image( Image const& other ) = delete;
        void operator=( Image const& other ) = delete;

        Image( Image&& other ) = delete;
        void operator=( Image&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves supported properties of an image.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - properties_t: pointer to image properties
        /// 
        /// @throws result_t
        static properties_t __zecall
        GetProperties(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc                              ///< [in] pointer to image descriptor
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
        /// @returns
        ///     - Image*: pointer to handle of image object created
        /// 
        /// @throws result_t
        static Image* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc                              ///< [in] pointer to image descriptor
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
        /// @throws result_t
        static void __zecall
        Destroy(
            Image* pImage                                   ///< [in][release] pointer to image object to destroy
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_version_t to std::string
    std::string to_string( const Image::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::flag_t to std::string
    std::string to_string( const Image::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::type_t to std::string
    std::string to_string( const Image::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_layout_t to std::string
    std::string to_string( const Image::format_layout_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_type_t to std::string
    std::string to_string( const Image::format_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_swizzle_t to std::string
    std::string to_string( const Image::format_swizzle_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_desc_t to std::string
    std::string to_string( const Image::format_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_t to std::string
    std::string to_string( const Image::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_version_t to std::string
    std::string to_string( const Image::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::sampler_filter_flags_t to std::string
    std::string to_string( const Image::sampler_filter_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_t to std::string
    std::string to_string( const Image::properties_t val );

} // namespace ze
#pragma endregion
#pragma region memory
namespace ze
{
} // namespace ze

namespace ze
{
} // namespace ze
#pragma endregion
#pragma region module
///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_KERNEL_NAME
/// @brief Maximum device name string size
#define ZE_MAX_KERNEL_NAME  256
#endif // ZE_MAX_KERNEL_NAME

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for module
    class Module
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_module_desc_t
        enum class desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported module creation input formats
        enum class format_t
        {
            IL_SPIRV = 0,                                   ///< Format is SPIRV IL format
            NATIVE,                                         ///< Format is device native format

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Specialization constants - User defined constants
        struct constants_t
        {
            uint32_t numConstants;                          ///< [in] Number of specialization constants.
            const uint32_t* pConstantIds;                   ///< [in] Pointer to array of IDs that is sized to numConstants.
            const uint64_t* pConstantValues;                ///< [in] Pointer to array of values that is sized to numConstants.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Module descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_MODULE_DESC_VERSION_CURRENT
            format_t format;                                ///< [in] Module format passed in with pInputModule
            size_t inputSize = 0;                           ///< [in] size of input IL or ISA from pInputModule.
            const uint8_t* pInputModule = nullptr;          ///< [in] pointer to IL or ISA
            const char* pBuildFlags = nullptr;              ///< [in] string containing compiler flags. See programming guide for build
                                                            ///< flags.
            const constants_t* pConstants = nullptr;        ///< [in] pointer to specialization constants. Valid only for SPIR-V input.
                                                            ///< This must be set to nullptr if no specialization constants are
                                                            ///< provided.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        module_handle_t m_handle;                       ///< [in] handle of module object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the module object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Module( void ) = delete;
        Module( 
            module_handle_t handle,                         ///< [in] handle of module object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the module object
            );

        ~Module( void ) = default;

        Module( Module const& other ) = delete;
        void operator=( Module const& other ) = delete;

        Module( Module&& other ) = delete;
        void operator=( Module&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Module*: pointer to handle of module object created
        ///     - ModuleBuildLog*: pointer to handle of module's build log.
        /// 
        /// @throws result_t
        static Module* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc,                             ///< [in] pointer to module descriptor
            ModuleBuildLog** ppBuildLog = nullptr           ///< [out][optional] pointer to pointer to module's build log.
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
        /// @throws result_t
        static void __zecall
        Destroy(
            Module* pModule                                 ///< [in][release] pointer to the module
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
        /// @throws result_t
        void __zecall
        GetNativeBinary(
            size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
            uint8_t* pModuleNativeBinary = nullptr          ///< [in,out][optional] byte pointer to native binary
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve global variable pointer from Module.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - void*: device visible pointer
        /// 
        /// @throws result_t
        void* __zecall
        GetGlobalPointer(
            const char* pGlobalName                         ///< [in] name of global variable in module
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve all kernel names in the module.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetKernelNames(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of names available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of names.
                                                            ///< if count is larger than the number of names available, then the driver
                                                            ///< will update the value with the correct number of names available.
            const char** pNames = nullptr                   ///< [in,out][optional][range(0, *pCount)] array of names of functions
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
        /// @returns
        ///     - void*: pointer to function.
        /// 
        /// @throws result_t
        void* __zecall
        GetFunctionPointer(
            const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for buildlog
    class ModuleBuildLog
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////
        module_build_log_handle_t m_handle;             ///< [in] handle of the buildlog object
        Module* m_pModule;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        ModuleBuildLog( void ) = delete;
        ModuleBuildLog( 
            module_build_log_handle_t handle,               ///< [in] handle of the buildlog object
            Module* pModule                                 ///< [in] pointer to owner object
            );

        ~ModuleBuildLog( void ) = default;

        ModuleBuildLog( ModuleBuildLog const& other ) = delete;
        void operator=( ModuleBuildLog const& other ) = delete;

        ModuleBuildLog( ModuleBuildLog&& other ) = delete;
        void operator=( ModuleBuildLog&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getModule( void ) const { return m_pModule; }

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
        /// @throws result_t
        static void __zecall
        Destroy(
            ModuleBuildLog* pModuleBuildLog                 ///< [in][release] pointer to the module build log object.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves text string for build log.
        /// 
        /// @details
        ///     - The caller can pass nullptr for pBuildLog when querying only for size.
        ///     - The caller must provide memory for build log.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetString(
            size_t* pSize,                                  ///< [in,out] size of build log string.
            char* pBuildLog = nullptr                       ///< [in,out][optional] pointer to null-terminated string of the log.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for kernel
    class Kernel
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_kernel_desc_t
        enum class desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported kernel creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default driver behavior
            FORCE_RESIDENCY,                                ///< force all device allocations to be resident during execution

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel attributes
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cl_kernel_exec_info**
        enum class attribute_t
        {
            KERNEL_ATTR_INDIRECT_HOST_ACCESS = 0,           ///< Indicates that the function accesses host allocations indirectly
                                                            ///< (default: false, type: bool_t)
            KERNEL_ATTR_INDIRECT_DEVICE_ACCESS,             ///< Indicates that the function accesses device allocations indirectly
                                                            ///< (default: false, type: bool_t)
            KERNEL_ATTR_INDIRECT_SHARED_ACCESS,             ///< Indicates that the function accesses shared allocations indirectly
                                                            ///< (default: false, type: bool_t)
            KERNEL_ATTR_SOURCE_ATTRIBUTE,                   ///< Declared kernel attributes (i.e. can be specified with __attribute__
                                                            ///< in runtime language). (type: char[]) Returned as a null-terminated
                                                            ///< string and each attribute is separated by a space.
                                                            ///< ::zeKernelSetAttribute is not supported for this.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_kernel_properties_t
        enum class properties_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_KERNEL_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags
            const char* pKernelName = nullptr;              ///< [in] null-terminated name of kernel in module

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel properties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZE_KERNEL_PROPERTIES_VERSION_CURRENT
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

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        kernel_handle_t m_handle;                       ///< [in] handle of kernel object
        Module* m_pModule;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the kernel object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Kernel( void ) = delete;
        Kernel( 
            kernel_handle_t handle,                         ///< [in] handle of kernel object
            Module* pModule,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the kernel object
            );

        ~Kernel( void ) = default;

        Kernel( Kernel const& other ) = delete;
        void operator=( Kernel const& other ) = delete;

        Kernel( Kernel&& other ) = delete;
        void operator=( Kernel&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getModule( void ) const { return m_pModule; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Create a kernel object from a module by name
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - Kernel*: handle of the Function object
        /// 
        /// @throws result_t
        static Kernel* __zecall
        Create(
            Module* pModule,                                ///< [in] pointer to the module
            const desc_t* desc                              ///< [in] pointer to kernel descriptor
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
        /// @throws result_t
        static void __zecall
        Destroy(
            Kernel* pKernel                                 ///< [in][release] pointer to the kernel object
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the preferred Intermediate cache configuration for a kernel.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same kernel handle.
        /// @throws result_t
        void __zecall
        SetIntermediateCacheConfig(
            Device::cache_config_t CacheConfig              ///< [in] CacheConfig
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
        /// @throws result_t
        void __zecall
        SetGroupSize(
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
        /// @returns
        ///     - uint32_t: recommended size of group for X dimension
        ///     - uint32_t: recommended size of group for Y dimension
        ///     - uint32_t: recommended size of group for Z dimension
        /// 
        /// @throws result_t
        std::tuple<uint32_t, uint32_t, uint32_t> __zecall
        SuggestGroupSize(
            uint32_t globalSizeX,                           ///< [in] global width for X dimension
            uint32_t globalSizeY,                           ///< [in] global width for Y dimension
            uint32_t globalSizeZ                            ///< [in] global width for Z dimension
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query a suggested max group count a cooperative kernel.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - uint32_t: recommended total group count.
        /// 
        /// @throws result_t
        uint32_t __zecall
        SuggestMaxCooperativeGroupCount(
            void
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
        /// @throws result_t
        void __zecall
        SetArgumentValue(
            uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
            size_t argSize,                                 ///< [in] size of argument type
            const void* pArgValue = nullptr                 ///< [in][optional] argument value represented as matching arg type. If
                                                            ///< null then argument value is considered null.
            );

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
        /// @throws result_t
        void __zecall
        SetAttribute(
            attribute_t attr,                               ///< [in] attribute to set
            uint32_t size,                                  ///< [in] size in bytes of kernel attribute value.
            const void* pValue = nullptr                    ///< [in][optional] pointer to attribute value.
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
        /// @throws result_t
        void __zecall
        GetAttribute(
            attribute_t attr,                               ///< [in] attribute to get. Documentation for ::ze_kernel_attribute_t for
                                                            ///< return type information for pValue.
            uint32_t* pSize,                                ///< [in,out] size in bytes needed for kernel attribute value. If pValue is
                                                            ///< nullptr then the size needed for pValue memory will be written to
                                                            ///< pSize. Only need to query size for arbitrary sized attributes.
            void* pValue = nullptr                          ///< [in,out][optional] pointer to attribute value result.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve kernel properties.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            properties_t* pKernelProperties                 ///< [in,out] query result for kernel properties.
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_version_t to std::string
    std::string to_string( const Module::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::format_t to std::string
    std::string to_string( const Module::format_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::constants_t to std::string
    std::string to_string( const Module::constants_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_t to std::string
    std::string to_string( const Module::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_version_t to std::string
    std::string to_string( const Kernel::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::flag_t to std::string
    std::string to_string( const Kernel::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_t to std::string
    std::string to_string( const Kernel::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::attribute_t to std::string
    std::string to_string( const Kernel::attribute_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::properties_version_t to std::string
    std::string to_string( const Kernel::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::properties_t to std::string
    std::string to_string( const Kernel::properties_t val );

} // namespace ze
#pragma endregion
#pragma region residency
namespace ze
{
} // namespace ze

namespace ze
{
} // namespace ze
#pragma endregion
#pragma region sampler
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief c++ wrapper for sampler
    class Sampler
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_sampler_desc_t
        enum class desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler addressing modes
        enum class address_mode_t
        {
            NONE = 0,                                       ///< No coordinate modifications for out-of-bounds image access.
            REPEAT,                                         ///< Out-of-bounds coordinates are wrapped back around.
            CLAMP,                                          ///< Out-of-bounds coordinates are clamped to edge.
            CLAMP_TO_BORDER,                                ///< Out-of-bounds coordinates are clamped to border color which is (0.0f,
                                                            ///< 0.0f, 0.0f, 0.0f) if image format swizzle contains alpha, otherwise
                                                            ///< (0.0f, 0.0f, 0.0f, 1.0f).
            MIRROR,                                         ///< Out-of-bounds coordinates are mirrored starting from edge.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler filtering modes
        enum class filter_mode_t
        {
            NEAREST = 0,                                    ///< No coordinate modifications for out of bounds image access.
            LINEAR,                                         ///< Out-of-bounds coordinates are wrapped back around.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_SAMPLER_DESC_VERSION_CURRENT
            address_mode_t addressMode = address_mode_t::NONE;  ///< [in] Sampler addressing mode to determine how out-of-bounds
                                                            ///< coordinates are handled.
            filter_mode_t filterMode = filter_mode_t::NEAREST;  ///< [in] Sampler filter mode to determine how samples are filtered.
            bool_t isNormalized = true;                     ///< [in] Are coordinates normalized [0, 1] or not.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sampler_handle_t m_handle;                      ///< [in] handle of the sample object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] sampler descriptor

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Sampler( void ) = delete;
        Sampler( 
            sampler_handle_t handle,                        ///< [in] handle of the sample object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] sampler descriptor
            );

        ~Sampler( void ) = default;

        Sampler( Sampler const& other ) = delete;
        void operator=( Sampler const& other ) = delete;

        Sampler( Sampler&& other ) = delete;
        void operator=( Sampler&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates sampler object.
        /// 
        /// @details
        ///     - The sampler can only be used on the device on which it was created.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - Sampler*: handle of the sampler
        /// 
        /// @throws result_t
        static Sampler* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc                              ///< [in] pointer to sampler descriptor
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
        /// @throws result_t
        static void __zecall
        Destroy(
            Sampler* pSampler                               ///< [in][release] pointer to the sampler
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_version_t to std::string
    std::string to_string( const Sampler::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::address_mode_t to std::string
    std::string to_string( const Sampler::address_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::filter_mode_t to std::string
    std::string to_string( const Sampler::filter_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_t to std::string
    std::string to_string( const Sampler::desc_t val );

} // namespace ze
#pragma endregion
#endif // defined(__cplusplus)
#endif // _ZE_API_HPP