/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_memory.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Memory
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/memory.yml
 * @endcond
 *
 */
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that is shared between the host and one or more
///        devices
/// 
/// @details
///     - Shared allocations share ownership between the host and one or more
///       devices.
///     - By default, shared allocations are visible to all devices supported by
///       the driver.
///     - A shared allocation can be restricted to be only visible to the host
///       and a single device by specifying a single device handle.
///     - The application may call this function from simultaneous threads.
/// 
/// @remarks
///   _Analogues_
///     - **cudaMallocManaged**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == hDevice
///         + nullptr == pptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDriverAllocSharedMem(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    xe_device_handle_t hDevice,                     ///< [in] handle of a device
    xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
    uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                    ///< must be less than the count returned from ::xeDeviceGetMemoryProperties
    xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** pptr                                     ///< [out] pointer to shared allocation
    )
{
    auto pfnAllocSharedMem = xe_lib::context.ddiTable.Driver.pfnAllocSharedMem;
    if( nullptr == pfnAllocSharedMem )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAllocSharedMem( hDriver, hDevice, device_flags, ordinal, host_flags, size, alignment, pptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory specific to a device
/// 
/// @details
///     - A device allocation is owned by a specific device.
///     - In general, a device allocation may only be accessed by the device
///       that owns it.
///     - The application may call this function from simultaneous threads.
/// 
/// @remarks
///   _Analogues_
///     - **cudaMalloc**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == hDevice
///         + nullptr == pptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDriverAllocDeviceMem(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                    ///< must be less than the count returned from ::xeDeviceGetMemoryProperties
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** pptr                                     ///< [out] pointer to device allocation
    )
{
    auto pfnAllocDeviceMem = xe_lib::context.ddiTable.Driver.pfnAllocDeviceMem;
    if( nullptr == pfnAllocDeviceMem )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAllocDeviceMem( hDriver, hDevice, flags, ordinal, size, alignment, pptr );
}

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
/// @remarks
///   _Analogues_
///     - **cudaHostAlloc**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == pptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDriverAllocHostMem(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** pptr                                     ///< [out] pointer to host allocation
    )
{
    auto pfnAllocHostMem = xe_lib::context.ddiTable.Driver.pfnAllocHostMem;
    if( nullptr == pfnAllocHostMem )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAllocHostMem( hDriver, flags, size, alignment, pptr );
}

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
/// @remarks
///   _Analogues_
///     - **cudaFree**
///     - **cudaFreeHost**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverFreeMem(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    void* ptr                                       ///< [in][release] pointer to memory to free
    )
{
    auto pfnFreeMem = xe_lib::context.ddiTable.Driver.pfnFreeMem;
    if( nullptr == pfnFreeMem )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnFreeMem( hDriver, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of a memory allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @remarks
///   _Analogues_
///     - **cuPointerGetAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == ptr
///         + nullptr == pMemProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetMemProperties(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] memory pointer to query
    xe_memory_allocation_properties_t* pMemProperties,  ///< [out] query result for memory allocation properties
    xe_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
    )
{
    auto pfnGetMemProperties = xe_lib::context.ddiTable.Driver.pfnGetMemProperties;
    if( nullptr == pfnGetMemProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemProperties( hDriver, ptr, pMemProperties, phDevice );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the base address and/or size of an allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @remarks
///   _Analogues_
///     - **cuMemGetAddressRange**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetMemAddressRange(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] memory pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    auto pfnGetMemAddressRange = xe_lib::context.ddiTable.Driver.pfnGetMemAddressRange;
    if( nullptr == pfnGetMemAddressRange )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemAddressRange( hDriver, ptr, pBase, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an IPC memory handle for the specified allocation in the
///        sending process
/// 
/// @details
///     - Takes a pointer to the base of a device memory allocation and exports
///       it for use in another process.
///     - The application may call this function from simultaneous threads.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcGetMemHandle**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == ptr
///         + nullptr == pIpcHandle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetMemIpcHandle(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    auto pfnGetMemIpcHandle = xe_lib::context.ddiTable.Driver.pfnGetMemIpcHandle;
    if( nullptr == pfnGetMemIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemIpcHandle( hDriver, ptr, pIpcHandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
///        process
/// 
/// @details
///     - Takes an IPC memory handle from a sending process and associates it
///       with a device pointer usable in this process.
///     - The device pointer in this process should not be freed with
///       ::xeDriverFreeMem, but rather with ::xeDriverCloseMemIpcHandle.
///     - The application may call this function from simultaneous threads.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcOpenMemHandle**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == hDevice
///         + nullptr == pptr
///         + invalid flags
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverOpenMemIpcHandle(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** pptr                                     ///< [out] pointer to device allocation in this process
    )
{
    auto pfnOpenMemIpcHandle = xe_lib::context.ddiTable.Driver.pfnOpenMemIpcHandle;
    if( nullptr == pfnOpenMemIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnOpenMemIpcHandle( hDriver, hDevice, handle, flags, pptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC memory handle in a receiving process
/// 
/// @details
///     - Closes an IPC memory handle by unmapping memory that was opened in
///       this process using ::xeDriverOpenMemIpcHandle.
///     - The application may **not** call this function from simultaneous
///       threads with the same pointer.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcCloseMemHandle**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverCloseMemIpcHandle(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr                                 ///< [in][release] pointer to device allocation in this process
    )
{
    auto pfnCloseMemIpcHandle = xe_lib::context.ddiTable.Driver.pfnCloseMemIpcHandle;
    if( nullptr == pfnCloseMemIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCloseMemIpcHandle( hDriver, ptr );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates memory that is shared between the host and one or more
    ///        devices
    /// 
    /// @details
    ///     - Shared allocations share ownership between the host and one or more
    ///       devices.
    ///     - By default, shared allocations are visible to all devices supported by
    ///       the driver.
    ///     - A shared allocation can be restricted to be only visible to the host
    ///       and a single device by specifying a single device handle.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaMallocManaged**
    /// 
    /// @returns
    ///     - void*: pointer to shared allocation
    /// 
    /// @throws result_t
    void* __xecall
    Driver::AllocSharedMem(
        Device* pDevice,                                ///< [in] pointer to a device
        device_mem_alloc_flag_t device_flags,           ///< [in] flags specifying additional device allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::xeDeviceGetMemoryProperties
        host_mem_alloc_flag_t host_flags,               ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::xeDriverAllocSharedMem(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            static_cast<xe_device_mem_alloc_flag_t>( device_flags ),
            ordinal,
            static_cast<xe_host_mem_alloc_flag_t>( host_flags ),
            size,
            alignment,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::AllocSharedMem" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates memory specific to a device
    /// 
    /// @details
    ///     - A device allocation is owned by a specific device.
    ///     - In general, a device allocation may only be accessed by the device
    ///       that owns it.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaMalloc**
    /// 
    /// @returns
    ///     - void*: pointer to device allocation
    /// 
    /// @throws result_t
    void* __xecall
    Driver::AllocDeviceMem(
        Device* pDevice,                                ///< [in] pointer to the device
        device_mem_alloc_flag_t flags,                  ///< [in] flags specifying additional allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::xeDeviceGetMemoryProperties
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::xeDriverAllocDeviceMem(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            static_cast<xe_device_mem_alloc_flag_t>( flags ),
            ordinal,
            size,
            alignment,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::AllocDeviceMem" );

        return pptr;
    }

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
    /// @remarks
    ///   _Analogues_
    ///     - **cudaHostAlloc**
    /// 
    /// @returns
    ///     - void*: pointer to host allocation
    /// 
    /// @throws result_t
    void* __xecall
    Driver::AllocHostMem(
        host_mem_alloc_flag_t flags,                    ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::xeDriverAllocHostMem(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            static_cast<xe_host_mem_alloc_flag_t>( flags ),
            size,
            alignment,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::AllocHostMem" );

        return pptr;
    }

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
    /// @remarks
    ///   _Analogues_
    ///     - **cudaFree**
    ///     - **cudaFreeHost**
    /// 
    /// @throws result_t
    void __xecall
    Driver::FreeMem(
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        auto result = static_cast<result_t>( ::xeDriverFreeMem(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::FreeMem" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of a memory allocation
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuPointerGetAttribute**
    /// 
    /// @returns
    ///     - memory_allocation_properties_t: query result for memory allocation properties
    ///     - Device*: device associated with this allocation
    /// 
    /// @throws result_t
    Driver::memory_allocation_properties_t __xecall
    Driver::GetMemProperties(
        const void* ptr,                                ///< [in] memory pointer to query
        Device** ppDevice                               ///< [out][optional] device associated with this allocation
        )
    {
        xe_memory_allocation_properties_t memProperties;

        xe_device_handle_t hDevice;

        auto result = static_cast<result_t>( ::xeDriverGetMemProperties(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            ptr,
            &memProperties,
            ( ppDevice ) ? &hDevice : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::GetMemProperties" );

        if( ppDevice )
            *ppDevice =  nullptr;

        try
        {
            if( ppDevice )
                *ppDevice =  xe_lib::context.deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hDevice ), this );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Driver::GetMemProperties" );
        }

        return *reinterpret_cast<memory_allocation_properties_t*>( &memProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves the base address and/or size of an allocation
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuMemGetAddressRange**
    /// 
    /// @throws result_t
    void __xecall
    Driver::GetMemAddressRange(
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        auto result = static_cast<result_t>( ::xeDriverGetMemAddressRange(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            ptr,
            pBase,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::GetMemAddressRange" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates an IPC memory handle for the specified allocation in the
    ///        sending process
    /// 
    /// @details
    ///     - Takes a pointer to the base of a device memory allocation and exports
    ///       it for use in another process.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcGetMemHandle**
    /// 
    /// @returns
    ///     - ipc_mem_handle_t: Returned IPC memory handle
    /// 
    /// @throws result_t
    ipc_mem_handle_t __xecall
    Driver::GetMemIpcHandle(
        const void* ptr                                 ///< [in] pointer to the device memory allocation
        )
    {
        xe_ipc_mem_handle_t ipcHandle;

        auto result = static_cast<result_t>( ::xeDriverGetMemIpcHandle(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            ptr,
            &ipcHandle ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::GetMemIpcHandle" );

        return *reinterpret_cast<ipc_mem_handle_t*>( &ipcHandle );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
    ///        process
    /// 
    /// @details
    ///     - Takes an IPC memory handle from a sending process and associates it
    ///       with a device pointer usable in this process.
    ///     - The device pointer in this process should not be freed with
    ///       ::xeDriverFreeMem, but rather with ::xeDriverCloseMemIpcHandle.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcOpenMemHandle**
    /// 
    /// @returns
    ///     - void*: pointer to device allocation in this process
    /// 
    /// @throws result_t
    void* __xecall
    Driver::OpenMemIpcHandle(
        Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC memory handle
        ipc_mem_handle_t handle,                        ///< [in] IPC memory handle
        ipc_memory_flag_t flags                         ///< [in] flags controlling the operation
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::xeDriverOpenMemIpcHandle(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            *reinterpret_cast<xe_ipc_mem_handle_t*>( &handle ),
            static_cast<xe_ipc_memory_flag_t>( flags ),
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::OpenMemIpcHandle" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC memory handle in a receiving process
    /// 
    /// @details
    ///     - Closes an IPC memory handle by unmapping memory that was opened in
    ///       this process using ::xeDriverOpenMemIpcHandle.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same pointer.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcCloseMemHandle**
    /// 
    /// @throws result_t
    void __xecall
    Driver::CloseMemIpcHandle(
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        auto result = static_cast<result_t>( ::xeDriverCloseMemIpcHandle(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::CloseMemIpcHandle" );
    }

} // namespace xe

namespace xe
{
} // namespace xe
