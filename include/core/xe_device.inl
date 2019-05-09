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
* @file xe_device.inl
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/device.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_DEVICE_INL
#define _XE_DEVICE_INL
#if defined(__cplusplus)
#pragma once
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_device.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Device::Device( 
        Driver* pDriver,                                ///< pointer to parent object
        device_handle_t handle                          ///< handle of device object
        ) :
        m_pDriver( pDriver ),
        m_handle( handle )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetCount
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
    ///     - uint32_t: number of devices available
    /// 
    /// @throws result_t
    inline uint32_t 
    Device::GetCount(
        void
        )
    {
        // auto result = ::xeDeviceGetCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetCount");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGet
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
    ///     - Device: pointer to handle of device object created
    /// 
    /// @throws result_t
    inline Device* 
    Device::Get(
        uint32_t ordinal                                ///< [in] The device index in the range of [0, ::DeviceGetCount]
        )
    {
        // auto result = ::xeDeviceGet( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::Get");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetSubDevice
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
    ///     - Device: pointer to handle of sub-device object.
    /// 
    /// @throws result_t
    inline Device* 
    Device::GetSubDevice(
        uint32_t ordinal                                ///< [in] ordinal of sub-device to retrieve
        )
    {
        // auto result = ::xeDeviceGetSubDevice( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetSubDevice");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetApiVersion
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
    ///     - api_version_t: api version
    /// 
    /// @throws result_t
    inline Device::api_version_t 
    Device::GetApiVersion(
        void
        )
    {
        // auto result = ::xeDeviceGetApiVersion( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetApiVersion");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetProperties
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
    ///     - properties_t: query result for device properties
    /// 
    /// @throws result_t
    inline Device::properties_t 
    Device::GetProperties(
        void
        )
    {
        // auto result = ::xeDeviceGetProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetComputeProperties
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
    ///     - compute_properties_t: query result for compute properties
    /// 
    /// @throws result_t
    inline Device::compute_properties_t 
    Device::GetComputeProperties(
        void
        )
    {
        // auto result = ::xeDeviceGetComputeProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetComputeProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetMemoryProperties
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
    ///     - memory_properties_t: query result for compute properties
    /// 
    /// @throws result_t
    inline Device::memory_properties_t 
    Device::GetMemoryProperties(
        void
        )
    {
        // auto result = ::xeDeviceGetMemoryProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetMemoryProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetP2PProperties
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
    ///     - p2p_properties_t: Peer-to-Peer properties between source and peer device
    /// 
    /// @throws result_t
    inline Device::p2p_properties_t 
    Device::GetP2PProperties(
        Device* hPeerDevice                             ///< [in] handle of the peer device with the allocation
        )
    {
        // auto result = ::xeDeviceGetP2PProperties( handle, hPeerDevice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetP2PProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCanAccessPeer
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
    ///     - bool_t: returned access capability
    /// 
    /// @throws result_t
    inline bool_t 
    Device::CanAccessPeer(
        Device* hPeerDevice                             ///< [in] handle of the peer device with the allocation
        )
    {
        // auto result = ::xeDeviceCanAccessPeer( handle, hPeerDevice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CanAccessPeer");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceSetIntermediateCacheConfig
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaFuncSetCacheConfig **
    /// 
    /// @throws result_t
    inline void 
    Device::SetIntermediateCacheConfig(
        cache_config_t CacheConfig                      ///< [in] CacheConfig
        )
    {
        // auto result = ::xeDeviceSetIntermediateCacheConfig( handle, CacheConfig );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::SetIntermediateCacheConfig");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceSetLastLevelCacheConfig
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaFuncSetCacheConfig **
    /// 
    /// @throws result_t
    inline void 
    Device::SetLastLevelCacheConfig(
        cache_config_t CacheConfig                      ///< [in] CacheConfig
        )
    {
        // auto result = ::xeDeviceSetLastLevelCacheConfig( handle, CacheConfig );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::SetLastLevelCacheConfig");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceSystemBarrier
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
    /// @throws result_t
    inline void 
    Device::SystemBarrier(
        void
        )
    {
        // auto result = ::xeDeviceSystemBarrier( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::SystemBarrier");
    }

    ///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
    /// @brief C++ wrapper for ::xeDeviceRegisterCLMemory
    /// 
    /// @returns
    ///     - void*: pointer to device allocation
    /// 
    /// @throws result_t
    inline void* 
    Device::RegisterCLMemory(
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem                                      ///< [in] the OpenCL memory to register
        )
    {
        // auto result = ::xeDeviceRegisterCLMemory( handle, context, mem );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::RegisterCLMemory");
    }
#endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
    /// @brief C++ wrapper for ::xeDeviceRegisterCLProgram
    /// 
    /// @returns
    ///     - Module: pointer to handle of module object created
    /// 
    /// @throws result_t
    inline Module* 
    Device::RegisterCLProgram(
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program                              ///< [in] the OpenCL program to register
        )
    {
        // auto result = ::xeDeviceRegisterCLProgram( handle, context, program );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::RegisterCLProgram");
    }
#endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
    /// @brief C++ wrapper for ::xeDeviceRegisterCLCommandQueue
    /// 
    /// @returns
    ///     - CommandQueue: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    inline CommandQueue* 
    Device::RegisterCLCommandQueue(
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue                  ///< [in] the OpenCL command queue to register
        )
    {
        // auto result = ::xeDeviceRegisterCLCommandQueue( handle, context, command_queue );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::RegisterCLCommandQueue");
    }
#endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceMakeMemoryResident
    /// 
    /// @details
    ///     - If the application does not properly manage residency then the device
    ///       may experience unrecoverable page-faults.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    Device::MakeMemoryResident(
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        // auto result = ::xeDeviceMakeMemoryResident( handle, ptr, size );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::MakeMemoryResident");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceEvictMemory
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the memory before it is evicted
    ///     - Memory is always implicitly evicted if it is resident when freed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    Device::EvictMemory(
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        // auto result = ::xeDeviceEvictMemory( handle, ptr, size );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::EvictMemory");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceMakeImageResident
    /// 
    /// @details
    ///     - If the application does not properly manage residency then the device
    ///       may experience unrecoverable page-faults.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    Device::MakeImageResident(
        Image* hImage                                   ///< [in] handle of image to make resident
        )
    {
        // auto result = ::xeDeviceMakeImageResident( handle, hImage );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::MakeImageResident");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceEvictImage
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the memory before it is evicted
    ///     - An image is always implicitly evicted if it is resident when
    ///       destroyed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    Device::EvictImage(
        Image* hImage                                   ///< [in] handle of image to make evict
        )
    {
        // auto result = ::xeDeviceEvictImage( handle, hImage );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::EvictImage");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_DEVICE_INL
