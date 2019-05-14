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
#include "xe_api.hpp"
#include "xe_api.h"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates memory that is shared between the host and one or more
    ///        devices
    /// 
    /// @details
    ///     - Shared allocations share ownership between the host and one or more
    ///       devices.
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
    Context::AllocSharedMem(
        Device* pDevice,                                ///< [in] pointer to the device
        device_mem_alloc_flag_t device_flags,           ///< [in] flags specifying additional device allocation controls
        host_mem_alloc_flag_t host_flags,               ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        // auto result = ::xeContextAllocSharedMem( handle, pDevice, device_flags, host_flags, size, alignment );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::AllocSharedMem");

        return (void*)0;
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
    Context::AllocDeviceMem(
        Device* pDevice,                                ///< [in] pointer to the device
        device_mem_alloc_flag_t flags,                  ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        // auto result = ::xeContextAllocDeviceMem( handle, pDevice, flags, size, alignment );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::AllocDeviceMem");

        return (void*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates host memory
    /// 
    /// @details
    ///     - A host allocation is owned by the host process.
    ///     - Host allocations are accessible by the host and all devices.
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
    Context::AllocHostMem(
        host_mem_alloc_flag_t flags,                    ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        // auto result = ::xeContextAllocHostMem( handle, flags, size, alignment );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::AllocHostMem");

        return (void*)0;
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
    Context::FreeMem(
        const void* ptr                                 ///< [in] pointer to memory to free
        )
    {
        // auto result = ::xeContextFreeMem( handle, ptr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::FreeMem");
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
    ///     - memory_allocation_properties_t: Query result for memory allocation properties
    /// 
    /// @throws result_t
    Context::memory_allocation_properties_t __xecall
    Context::GetMemProperties(
        const void* ptr                                 ///< [in] Pointer to query
        )
    {
        // auto result = ::xeContextGetMemProperties( handle, ptr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::GetMemProperties");

        return memory_allocation_properties_t{};
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
    Context::GetMemAddressRange(
        const void* ptr,                                ///< [in] Pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        // auto result = ::xeContextGetMemAddressRange( handle, ptr, pBase, pSize );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::GetMemAddressRange");
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
    Context::GetMemIpcHandle(
        Context* pContext,                              ///< [in] pointer to context
        const void* ptr                                 ///< [in] Pointer to the device memory allocation
        )
    {
        // auto result = ::xeContextGetMemIpcHandle( handle, pContext, ptr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::GetMemIpcHandle");

        return ipc_mem_handle_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
    ///        process
    /// 
    /// @details
    ///     - Takes an IPC memory handle from a sending process and associates it
    ///       with a device pointer usable in this process.
    ///     - The device pointer in this process should not be freed with
    ///       ::ContextFreeMem, but rather with ::ContextCloseMemIpcHandle.
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
    Context::OpenMemIpcHandle(
        Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC memory handle
        ipc_mem_handle_t handle,                        ///< [in] IPC memory handle
        ipc_memory_flag_t flags                         ///< [in] flags controlling the operation
        )
    {
        // auto result = ::xeContextOpenMemIpcHandle( handle, pDevice, handle, flags );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::OpenMemIpcHandle");

        return (void*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC memory handle in a receiving process
    /// 
    /// @details
    ///     - Closes an IPC memory handle by unmapping memory that was opened in
    ///       this process using ::ContextOpenMemIpcHandle.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same pointer.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcCloseMemHandle**
    /// 
    /// @throws result_t
    void __xecall
    Context::CloseMemIpcHandle(
        const void* ptr                                 ///< [in] pointer to device allocation in this process
        )
    {
        // auto result = ::xeContextCloseMemIpcHandle( handle, ptr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::CloseMemIpcHandle");
    }

#ifdef _DEBUG
#endif // _DEBUG
} // namespace xe
