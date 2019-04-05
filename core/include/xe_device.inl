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
#include "xe_device.hpp"

namespace xe
{
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
    ///     - ::module_handle_t: pointer to handle of module object created
    /// 
    /// @throws result_t
    inline module_handle_t 
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
    ///     - ::command_queue_handle_t: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    inline command_queue_handle_t 
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
    /// @brief C++ wrapper for ::xeDeviceCreateCommandList
    /// 
    /// @details
    ///     - The command list is created in the 'open' state.
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - ::command_list_handle_t: pointer to handle of command list object created
    /// 
    /// @throws result_t
    inline command_list_handle_t 
    Device::CreateCommandList(
        const command_list_desc_t* desc                 ///< [in] pointer to command list descriptor
        )
    {
        // auto result = ::xeDeviceCreateCommandList( handle, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateCommandList");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateCommandQueue
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clCreateCommandQueue**
    ///     - cuCtxCreate
    ///     - cuCtxGetCurrent
    /// 
    /// @returns
    ///     - ::command_queue_handle_t: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    inline command_queue_handle_t 
    Device::CreateCommandQueue(
        const command_queue_desc_t* desc                ///< [in] pointer to command queue descriptor
        )
    {
        // auto result = ::xeDeviceCreateCommandQueue( handle, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateCommandQueue");
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
    ///     - ::device_handle_t: pointer to handle of sub-device object.
    /// 
    /// @throws result_t
    inline device_handle_t 
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
    ///     - ::api_version_t: api version
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
    ///     - ::device_properties_t: query result for device properties
    /// 
    /// @throws result_t
    inline Device::device_properties_t 
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
    ///     - ::device_compute_properties_t: query result for compute properties
    /// 
    /// @throws result_t
    inline Device::device_compute_properties_t 
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
    ///     - ::device_memory_properties_t: query result for compute properties
    /// 
    /// @throws result_t
    inline Device::device_memory_properties_t 
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
    ///     - ::device_p2p_properties_t: Peer-to-Peer properties between source and peer device
    /// 
    /// @throws result_t
    inline Device::device_p2p_properties_t 
    Device::GetP2PProperties(
        device_handle_t hPeerDevice                     ///< [in] handle of the peer device with the allocation
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
    ///     - ::bool_t: returned access capability
    /// 
    /// @throws result_t
    inline bool_t 
    Device::CanAccessPeer(
        device_handle_t hPeerDevice                     ///< [in] handle of the peer device with the allocation
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
    /// @brief C++ wrapper for ::xeDeviceCreateEventPool
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - ::event_pool_handle_t: pointer handle of event pool object created
    /// 
    /// @throws result_t
    inline event_pool_handle_t 
    Device::CreateEventPool(
        const event_pool_desc_t* desc                   ///< [in] pointer to event pool descriptor
        )
    {
        // auto result = ::xeDeviceCreateEventPool( handle, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateEventPool");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetImageProperties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - ::image_properties_t: pointer to image properties
    /// 
    /// @throws result_t
    inline Device::image_properties_t 
    Device::GetImageProperties(
        const image_desc_t* desc                        ///< [in] pointer to image descriptor
        )
    {
        // auto result = ::xeDeviceGetImageProperties( handle, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetImageProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateImage
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clCreateImage
    /// 
    /// @returns
    ///     - ::image_handle_t: pointer to handle of image object created
    /// 
    /// @throws result_t
    inline image_handle_t 
    Device::CreateImage(
        const image_desc_t* desc                        ///< [in] pointer to image descriptor
        )
    {
        // auto result = ::xeDeviceCreateImage( handle, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateImage");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateModule
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - This function will create and compile the module object.
    ///     - A build log can optionally be returned to the caller. Caller is
    ///       responsible for destroying build log using ::ModuleBuildLogDestroy
    ///     - Device memory will be allocated for module during creation.
    ///     - A module can be created directly from native binary format.
    ///     - A native binary object can be retrieved from a module using
    ///       ::ModuleGetNativeBinary. This can be cached to disk and to create new
    ///       modules.
    ///     - The following build options are supported:
    ///         + "--opt-disable" - Disable optimizations
    ///         + "--opt-greater-than-4GB-buffer-required" - Use 64-bit offset
    ///           calculations for buffers.
    ///         + "--opt-large-register-file" - Increase number of registers
    ///           available to threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleLoad**
    /// 
    /// @returns
    ///     - ::module_handle_t: pointer to handle of module object created
    ///     - ::module_build_log_handle_t: pointer to handle of module's build log.
    /// 
    /// @throws result_t
    inline std::tuple<module_handle_t, module_build_log_handle_t> 
    Device::CreateModule(
        const module_desc_t* pDesc                      ///< [in] pointer to module descriptor
        )
    {
        // auto result = ::xeDeviceCreateModule( handle, pDesc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateModule");
    }

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
        image_handle_t hImage                           ///< [in] handle of image to make resident
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
        image_handle_t hImage                           ///< [in] handle of image to make evict
        )
    {
        // auto result = ::xeDeviceEvictImage( handle, hImage );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::EvictImage");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateSampler
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuTexObjectCreate**
    /// 
    /// @returns
    ///     - ::sampler_handle_t: handle of the sampler
    /// 
    /// @throws result_t
    inline sampler_handle_t 
    Device::CreateSampler(
        const sampler_desc_t* pDesc                     ///< [in] pointer to sampler descriptor
        )
    {
        // auto result = ::xeDeviceCreateSampler( handle, pDesc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateSampler");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_DEVICE_INL
