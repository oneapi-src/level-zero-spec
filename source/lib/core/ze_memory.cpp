/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_memory.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Memory
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/memory.yml
 * @endcond
 *
 */
#include "ze_lib.h"

extern "C" {

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
/// @remarks
///   _Analogues_
///     - **cudaMallocManaged**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == pptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
ze_result_t __zecall
zeDriverAllocSharedMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
    uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                    ///< must be less than the count returned from ::zeDeviceGetMemoryProperties
    ze_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    ze_device_handle_t hDevice,                     ///< [in][optional] device handle to associate with
    void** pptr                                     ///< [out] pointer to shared allocation
    )
{
    auto pfnAllocSharedMem = ze_lib::context.ddiTable.Driver.pfnAllocSharedMem;
    if( nullptr == pfnAllocSharedMem )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnAllocSharedMem( hDriver, device_flags, ordinal, host_flags, size, alignment, hDevice, pptr );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == hDevice
///         + nullptr == pptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
ze_result_t __zecall
zeDriverAllocDeviceMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                    ///< must be less than the count returned from ::zeDeviceGetMemoryProperties
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    void** pptr                                     ///< [out] pointer to device allocation
    )
{
    auto pfnAllocDeviceMem = ze_lib::context.ddiTable.Driver.pfnAllocDeviceMem;
    if( nullptr == pfnAllocDeviceMem )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnAllocDeviceMem( hDriver, flags, ordinal, size, alignment, hDevice, pptr );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == pptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
ze_result_t __zecall
zeDriverAllocHostMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** pptr                                     ///< [out] pointer to host allocation
    )
{
    auto pfnAllocHostMem = ze_lib::context.ddiTable.Driver.pfnAllocHostMem;
    if( nullptr == pfnAllocHostMem )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == ptr
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeDriverFreeMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    void* ptr                                       ///< [in][release] pointer to memory to free
    )
{
    auto pfnFreeMem = ze_lib::context.ddiTable.Driver.pfnFreeMem;
    if( nullptr == pfnFreeMem )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == ptr
///         + nullptr == pMemAllocProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeDriverGetMemAllocProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] memory pointer to query
    ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
    ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
    )
{
    auto pfnGetMemAllocProperties = ze_lib::context.ddiTable.Driver.pfnGetMemAllocProperties;
    if( nullptr == pfnGetMemAllocProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemAllocProperties( hDriver, ptr, pMemAllocProperties, phDevice );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == ptr
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeDriverGetMemAddressRange(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] memory pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    auto pfnGetMemAddressRange = ze_lib::context.ddiTable.Driver.pfnGetMemAddressRange;
    if( nullptr == pfnGetMemAddressRange )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == ptr
///         + nullptr == pIpcHandle
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeDriverGetMemIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] pointer to the device memory allocation
    ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    auto pfnGetMemIpcHandle = ze_lib::context.ddiTable.Driver.pfnGetMemIpcHandle;
    if( nullptr == pfnGetMemIpcHandle )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///       ::zeDriverFreeMem, but rather with ::zeDriverCloseMemIpcHandle.
///     - The application may call this function from simultaneous threads.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcOpenMemHandle**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == hDevice
///         + nullptr == pptr
///         + invalid flags
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeDriverOpenMemIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    ze_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** pptr                                     ///< [out] pointer to device allocation in this process
    )
{
    auto pfnOpenMemIpcHandle = ze_lib::context.ddiTable.Driver.pfnOpenMemIpcHandle;
    if( nullptr == pfnOpenMemIpcHandle )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnOpenMemIpcHandle( hDriver, hDevice, handle, flags, pptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC memory handle in a receiving process
/// 
/// @details
///     - Closes an IPC memory handle by unmapping memory that was opened in
///       this process using ::zeDriverOpenMemIpcHandle.
///     - The application may **not** call this function from simultaneous
///       threads with the same pointer.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcCloseMemHandle**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == ptr
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeDriverCloseMemIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr                                 ///< [in][release] pointer to device allocation in this process
    )
{
    auto pfnCloseMemIpcHandle = ze_lib::context.ddiTable.Driver.pfnCloseMemIpcHandle;
    if( nullptr == pfnCloseMemIpcHandle )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnCloseMemIpcHandle( hDriver, ptr );
}

} // extern "C"

namespace ze
{
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
    /// @remarks
    ///   _Analogues_
    ///     - **cudaMallocManaged**
    /// 
    /// @returns
    ///     - void*: pointer to shared allocation
    /// 
    /// @throws result_t
    void* __zecall
    Driver::AllocSharedMem(
        device_mem_alloc_flag_t device_flags,           ///< [in] flags specifying additional device allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::zeDeviceGetMemoryProperties
        host_mem_alloc_flag_t host_flags,               ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        Device* pDevice                                 ///< [in][optional] device handle to associate with
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeDriverAllocSharedMem(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            static_cast<ze_device_mem_alloc_flag_t>( device_flags ),
            ordinal,
            static_cast<ze_host_mem_alloc_flag_t>( host_flags ),
            size,
            alignment,
            ( pDevice ) ? reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ) : nullptr,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::AllocSharedMem" );

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
    void* __zecall
    Driver::AllocDeviceMem(
        device_mem_alloc_flag_t flags,                  ///< [in] flags specifying additional allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::zeDeviceGetMemoryProperties
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        Device* pDevice                                 ///< [in] pointer to the device
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeDriverAllocDeviceMem(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            static_cast<ze_device_mem_alloc_flag_t>( flags ),
            ordinal,
            size,
            alignment,
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::AllocDeviceMem" );

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
    void* __zecall
    Driver::AllocHostMem(
        host_mem_alloc_flag_t flags,                    ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeDriverAllocHostMem(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            static_cast<ze_host_mem_alloc_flag_t>( flags ),
            size,
            alignment,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::AllocHostMem" );

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
    void __zecall
    Driver::FreeMem(
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        auto result = static_cast<result_t>( ::zeDriverFreeMem(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::FreeMem" );
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
    ///     - Device*: device associated with this allocation
    /// 
    /// @throws result_t
    void __zecall
    Driver::GetMemAllocProperties(
        const void* ptr,                                ///< [in] memory pointer to query
        memory_allocation_properties_t* pMemAllocProperties,///< [in,out] query result for memory allocation properties
        Device** ppDevice                               ///< [out][optional] device associated with this allocation
        )
    {
        ze_device_handle_t hDevice;

        auto result = static_cast<result_t>( ::zeDriverGetMemAllocProperties(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            ptr,
            reinterpret_cast<ze_memory_allocation_properties_t*>( pMemAllocProperties ),
            ( ppDevice ) ? &hDevice : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetMemAllocProperties" );

        if( ppDevice )
            *ppDevice =  nullptr;

        try
        {
            if( ppDevice )
                *ppDevice =  ze_lib::context.deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hDevice ), this );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Driver::GetMemAllocProperties" );
        }
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
    void __zecall
    Driver::GetMemAddressRange(
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        auto result = static_cast<result_t>( ::zeDriverGetMemAddressRange(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            ptr,
            pBase,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetMemAddressRange" );
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
    ipc_mem_handle_t __zecall
    Driver::GetMemIpcHandle(
        const void* ptr                                 ///< [in] pointer to the device memory allocation
        )
    {
        ze_ipc_mem_handle_t ipcHandle;

        auto result = static_cast<result_t>( ::zeDriverGetMemIpcHandle(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            ptr,
            &ipcHandle ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetMemIpcHandle" );

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
    ///       ::zeDriverFreeMem, but rather with ::zeDriverCloseMemIpcHandle.
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
    void* __zecall
    Driver::OpenMemIpcHandle(
        Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC memory handle
        ipc_mem_handle_t handle,                        ///< [in] IPC memory handle
        ipc_memory_flag_t flags                         ///< [in] flags controlling the operation
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeDriverOpenMemIpcHandle(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            *reinterpret_cast<ze_ipc_mem_handle_t*>( &handle ),
            static_cast<ze_ipc_memory_flag_t>( flags ),
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::OpenMemIpcHandle" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC memory handle in a receiving process
    /// 
    /// @details
    ///     - Closes an IPC memory handle by unmapping memory that was opened in
    ///       this process using ::zeDriverOpenMemIpcHandle.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same pointer.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcCloseMemHandle**
    /// 
    /// @throws result_t
    void __zecall
    Driver::CloseMemIpcHandle(
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        auto result = static_cast<result_t>( ::zeDriverCloseMemIpcHandle(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::CloseMemIpcHandle" );
    }

} // namespace ze

namespace ze
{
} // namespace ze
