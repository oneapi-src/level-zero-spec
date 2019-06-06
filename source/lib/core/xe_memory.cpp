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
* @file xe_memory.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Memory
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/memory.yml
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that is shared between the host and one or more
///        devices
/// 
/// @details
///     - Shared allocations share ownership between the host and one or more
///       devices.
///     - By default, shared allocations are visible to all devices in the
///       device group.
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
///         + nullptr == hDeviceGroup
///         + nullptr == hDevice
///         + nullptr == ptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDeviceGroupAllocSharedMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of a device
    xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
    uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                    ///< must be less than the count returned from ::xeDeviceGroupGetMemoryProperties
    xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to shared allocation
    )
{
    auto pfnAllocSharedMem = xe_lib::lib.ddiTable.DeviceGroup.pfnAllocSharedMem;

#if _DEBUG
    if( nullptr == pfnAllocSharedMem )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAllocSharedMem( hDeviceGroup, hDevice, device_flags, ordinal, host_flags, size, alignment, ptr );
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
///         + nullptr == hDeviceGroup
///         + nullptr == hDevice
///         + nullptr == ptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDeviceGroupAllocDeviceMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                    ///< must be less than the count returned from ::xeDeviceGroupGetMemoryProperties
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    auto pfnAllocDeviceMem = xe_lib::lib.ddiTable.DeviceGroup.pfnAllocDeviceMem;

#if _DEBUG
    if( nullptr == pfnAllocDeviceMem )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAllocDeviceMem( hDeviceGroup, hDevice, flags, ordinal, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates host memory
/// 
/// @details
///     - A host allocation is owned by the host process.
///     - Host allocations are accessible by the host and all devices within the
///       device group.
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
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDeviceGroupAllocHostMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    )
{
    auto pfnAllocHostMem = xe_lib::lib.ddiTable.DeviceGroup.pfnAllocHostMem;

#if _DEBUG
    if( nullptr == pfnAllocHostMem )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAllocHostMem( hDeviceGroup, flags, size, alignment, ptr );
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
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupFreeMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr                                 ///< [in][release] pointer to memory to free
    )
{
    auto pfnFreeMem = xe_lib::lib.ddiTable.DeviceGroup.pfnFreeMem;

#if _DEBUG
    if( nullptr == pfnFreeMem )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnFreeMem( hDeviceGroup, ptr );
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
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///         + nullptr == pMemProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetMemProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] memory pointer to query
    xe_memory_allocation_properties_t* pMemProperties,  ///< [out] query result for memory allocation properties
    xe_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
    )
{
    auto pfnGetMemProperties = xe_lib::lib.ddiTable.DeviceGroup.pfnGetMemProperties;

#if _DEBUG
    if( nullptr == pfnGetMemProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetMemProperties( hDeviceGroup, ptr, pMemProperties, phDevice );
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
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetMemAddressRange(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] memory pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    auto pfnGetMemAddressRange = xe_lib::lib.ddiTable.DeviceGroup.pfnGetMemAddressRange;

#if _DEBUG
    if( nullptr == pfnGetMemAddressRange )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetMemAddressRange( hDeviceGroup, ptr, pBase, pSize );
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
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///         + nullptr == pIpcHandle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetMemIpcHandle(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    auto pfnGetMemIpcHandle = xe_lib::lib.ddiTable.DeviceGroup.pfnGetMemIpcHandle;

#if _DEBUG
    if( nullptr == pfnGetMemIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetMemIpcHandle( hDeviceGroup, ptr, pIpcHandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
///        process
/// 
/// @details
///     - Takes an IPC memory handle from a sending process and associates it
///       with a device pointer usable in this process.
///     - The device pointer in this process should not be freed with
///       ::xeDeviceGroupFreeMem, but rather with
///       ::xeDeviceGroupCloseMemIpcHandle.
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
///         + nullptr == hDeviceGroup
///         + nullptr == hDevice
///         + nullptr == handle
///         + nullptr == ptr
///         + invalid flags
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupOpenMemIpcHandle(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** ptr                                      ///< [out] pointer to device allocation in this process
    )
{
    auto pfnOpenMemIpcHandle = xe_lib::lib.ddiTable.DeviceGroup.pfnOpenMemIpcHandle;

#if _DEBUG
    if( nullptr == pfnOpenMemIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnOpenMemIpcHandle( hDeviceGroup, hDevice, handle, flags, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC memory handle in a receiving process
/// 
/// @details
///     - Closes an IPC memory handle by unmapping memory that was opened in
///       this process using ::xeDeviceGroupOpenMemIpcHandle.
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
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupCloseMemIpcHandle(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr                                 ///< [in][release] pointer to device allocation in this process
    )
{
    auto pfnCloseMemIpcHandle = xe_lib::lib.ddiTable.DeviceGroup.pfnCloseMemIpcHandle;

#if _DEBUG
    if( nullptr == pfnCloseMemIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCloseMemIpcHandle( hDeviceGroup, ptr );
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
    ///     - By default, shared allocations are visible to all devices in the
    ///       device group.
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
    DeviceGroup::AllocSharedMem(
        Device* pDevice,                                ///< [in] pointer to a device
        device_mem_alloc_flag_t device_flags,           ///< [in] flags specifying additional device allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::DeviceGroupGetMemoryProperties
        host_mem_alloc_flag_t host_flags,               ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::xeDeviceGroupAllocSharedMem(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            static_cast<xe_device_mem_alloc_flag_t>( device_flags ),
            ordinal,
            static_cast<xe_host_mem_alloc_flag_t>( host_flags ),
            size,
            alignment,
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::AllocSharedMem" );

        return ptr;
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
    DeviceGroup::AllocDeviceMem(
        Device* pDevice,                                ///< [in] pointer to the device
        device_mem_alloc_flag_t flags,                  ///< [in] flags specifying additional allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::DeviceGroupGetMemoryProperties
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::xeDeviceGroupAllocDeviceMem(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            static_cast<xe_device_mem_alloc_flag_t>( flags ),
            ordinal,
            size,
            alignment,
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::AllocDeviceMem" );

        return ptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates host memory
    /// 
    /// @details
    ///     - A host allocation is owned by the host process.
    ///     - Host allocations are accessible by the host and all devices within the
    ///       device group.
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
    DeviceGroup::AllocHostMem(
        host_mem_alloc_flag_t flags,                    ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::xeDeviceGroupAllocHostMem(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            static_cast<xe_host_mem_alloc_flag_t>( flags ),
            size,
            alignment,
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::AllocHostMem" );

        return ptr;
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
    DeviceGroup::FreeMem(
        const void* ptr                                 ///< [in][release] pointer to memory to free
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGroupFreeMem(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::FreeMem" );
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
    DeviceGroup::memory_allocation_properties_t __xecall
    DeviceGroup::GetMemProperties(
        const void* ptr,                                ///< [in] memory pointer to query
        Device** ppDevice                               ///< [out][optional] device associated with this allocation
        )
    {
        xe_memory_allocation_properties_t memProperties;

        xe_device_handle_t hDevice;

        auto result = static_cast<result_t>( ::xeDeviceGroupGetMemProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            ptr,
            &memProperties,
            ( ppDevice ) ? &hDevice : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetMemProperties" );

        if( ppDevice )
            *ppDevice =  nullptr;

        try
        {
            if( ppDevice )
                for( auto& pDevice : m_devices )
                    if( reinterpret_cast<device_handle_t>( hDevice ) == pDevice->getHandle() )
                        *ppDevice = pDevice.get();
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetMemProperties" );
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
    DeviceGroup::GetMemAddressRange(
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGroupGetMemAddressRange(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            ptr,
            pBase,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetMemAddressRange" );
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
    DeviceGroup::GetMemIpcHandle(
        const void* ptr                                 ///< [in] pointer to the device memory allocation
        )
    {
        xe_ipc_mem_handle_t ipcHandle;

        auto result = static_cast<result_t>( ::xeDeviceGroupGetMemIpcHandle(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            ptr,
            &ipcHandle ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetMemIpcHandle" );

        return reinterpret_cast<ipc_mem_handle_t>( ipcHandle );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
    ///        process
    /// 
    /// @details
    ///     - Takes an IPC memory handle from a sending process and associates it
    ///       with a device pointer usable in this process.
    ///     - The device pointer in this process should not be freed with
    ///       ::DeviceGroupFreeMem, but rather with ::DeviceGroupCloseMemIpcHandle.
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
    DeviceGroup::OpenMemIpcHandle(
        Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC memory handle
        ipc_mem_handle_t handle,                        ///< [in] IPC memory handle
        ipc_memory_flag_t flags                         ///< [in] flags controlling the operation
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::xeDeviceGroupOpenMemIpcHandle(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<xe_ipc_mem_handle_t>( handle ),
            static_cast<xe_ipc_memory_flag_t>( flags ),
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::OpenMemIpcHandle" );

        return ptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC memory handle in a receiving process
    /// 
    /// @details
    ///     - Closes an IPC memory handle by unmapping memory that was opened in
    ///       this process using ::DeviceGroupOpenMemIpcHandle.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same pointer.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcCloseMemHandle**
    /// 
    /// @throws result_t
    void __xecall
    DeviceGroup::CloseMemIpcHandle(
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGroupCloseMemIpcHandle(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::CloseMemIpcHandle" );
    }

} // namespace xe

namespace xe
{
} // namespace xe
