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
* @brief C++ wrapper of Intel Xe Driver APIs for Device
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
#if XE_ENABLE_OCL_INTEROP
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceRegisterCLMemory
    inline void Device::RegisterCLMemory(
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem,                                     ///< [in] the OpenCL memory to register
        void** ptr                                      ///< [out] pointer to device allocation
        )
    {
        // auto result = ::xeDeviceRegisterCLMemory( handle, context, mem, ptr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::RegisterCLMemory");
    }
#endif // XE_ENABLE_OCL_INTEROP

#if XE_ENABLE_OCL_INTEROP
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceRegisterCLProgram
    inline void Device::RegisterCLProgram(
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program,                             ///< [in] the OpenCL program to register
        module_handle_t* phModule                       ///< [out] pointer to handle of module object created
        )
    {
        // auto result = ::xeDeviceRegisterCLProgram( handle, context, program, phModule );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::RegisterCLProgram");
    }
#endif // XE_ENABLE_OCL_INTEROP

#if XE_ENABLE_OCL_INTEROP
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceRegisterCLCommandQueue
    inline void Device::RegisterCLCommandQueue(
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
        command_queue_handle_t* phCommandQueue          ///< [out] pointer to handle of command queue object created
        )
    {
        // auto result = ::xeDeviceRegisterCLCommandQueue( handle, context, command_queue, phCommandQueue );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::RegisterCLCommandQueue");
    }
#endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateCommandGraph
    inline void Device::CreateCommandGraph(
        const command_graph_desc_t* desc,               ///< [in] pointer to command graph descriptor
        command_graph_handle_t* phCommandGraph          ///< [out] pointer to handle of command graph object created
        )
    {
        // auto result = ::xeDeviceCreateCommandGraph( handle, desc, phCommandGraph );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateCommandGraph");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateCommandList
    inline void Device::CreateCommandList(
        const command_list_desc_t* desc,                ///< [in] pointer to command list descriptor
        command_list_handle_t* phCommandList            ///< [out] pointer to handle of command list object created
        )
    {
        // auto result = ::xeDeviceCreateCommandList( handle, desc, phCommandList );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateCommandList");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCopyCommandList
    inline void Device::CopyCommandList(
        command_list_handle_t hCommandList,             ///< [in] handle to command list to copy
        command_list_handle_t* phCommandList            ///< [out] pointer to handle of command list object created
        )
    {
        // auto result = ::xeDeviceCopyCommandList( handle, hCommandList, phCommandList );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CopyCommandList");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateCommandQueue
    inline void Device::CreateCommandQueue(
        const command_queue_desc_t* desc,               ///< [in] pointer to command queue descriptor
        command_queue_handle_t* phCommandQueue          ///< [out] pointer to handle of command queue object created
        )
    {
        // auto result = ::xeDeviceCreateCommandQueue( handle, desc, phCommandQueue );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateCommandQueue");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetSubDevice
    inline void Device::GetSubDevice(
        uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
        device_handle_t* phSubDevice                    ///< [out] pointer to handle of sub-device object.
        )
    {
        // auto result = ::xeDeviceGetSubDevice( handle, ordinal, phSubDevice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetSubDevice");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetApiVersion
    inline void Device::GetApiVersion(
        api_version_t* version                          ///< [out] api version
        )
    {
        // auto result = ::xeDeviceGetApiVersion( handle, version );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetApiVersion");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetProperties
    inline void Device::GetProperties(
        device_properties_t* pDeviceProperties          ///< [out] query result for device properties
        )
    {
        // auto result = ::xeDeviceGetProperties( handle, pDeviceProperties );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetComputeProperties
    inline void Device::GetComputeProperties(
        device_compute_properties_t* pComputeProperties ///< [out] query result for compute properties
        )
    {
        // auto result = ::xeDeviceGetComputeProperties( handle, pComputeProperties );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetComputeProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceGetMemoryProperties
    inline void Device::GetMemoryProperties(
        device_memory_properties_t* pMemProperties      ///< [out] query result for compute properties
        )
    {
        // auto result = ::xeDeviceGetMemoryProperties( handle, pMemProperties );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetMemoryProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCanAccessPeer
    inline void Device::CanAccessPeer(
        device_handle_t hPeerDevice,                    ///< [in] handle of the peer device with the allocation
        bool* value                                     ///< [out] returned access capability
        )
    {
        // auto result = ::xeDeviceCanAccessPeer( handle, hPeerDevice, value );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CanAccessPeer");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceSetIntermediateCacheConfig
    inline void Device::SetIntermediateCacheConfig(
        cache_config_t CacheConfig                      ///< [in] CacheConfig
        )
    {
        // auto result = ::xeDeviceSetIntermediateCacheConfig( handle, CacheConfig );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::SetIntermediateCacheConfig");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceSetLastLevelCacheConfig
    inline void Device::SetLastLevelCacheConfig(
        cache_config_t CacheConfig                      ///< [in] CacheConfig
        )
    {
        // auto result = ::xeDeviceSetLastLevelCacheConfig( handle, CacheConfig );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::SetLastLevelCacheConfig");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateEvent
    inline void Device::CreateEvent(
        const event_desc_t* desc,                       ///< [in] pointer to event descriptor
        event_handle_t* phEvent                         ///< [out] pointer to handle of event object created
        )
    {
        // auto result = ::xeDeviceCreateEvent( handle, desc, phEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateEvent");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDevicePlaceEvent
    inline void Device::PlaceEvent(
        const event_desc_t* desc,                       ///< [in] pointer to event descriptor
        void* ptr,                                      ///< [in] pointer to the device pointer where the event should be placed
        event_handle_t* phEvent                         ///< [out] pointer to handle of event object created
        )
    {
        // auto result = ::xeDevicePlaceEvent( handle, desc, ptr, phEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::PlaceEvent");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateImage
    inline void Device::CreateImage(
        const image_desc_t* desc,                       ///< [in] pointer to image descriptor
        image_handle_t* phImage                         ///< [out] pointer to handle of image object created
        )
    {
        // auto result = ::xeDeviceCreateImage( handle, desc, phImage );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateImage");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateModule
    inline void Device::CreateModule(
        const module_desc_t* pDesc,                     ///< [in] pointer to module descriptor
        module_handle_t* phModule,                      ///< [out] pointer to handle of module object created
        module_build_log_handle_t* phBuildLog           ///< [out][optional] pointer to handle of module's build log.
        )
    {
        // auto result = ::xeDeviceCreateModule( handle, pDesc, phModule, phBuildLog );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateModule");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceMakeMemoryResident
    inline void Device::MakeMemoryResident(
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        // auto result = ::xeDeviceMakeMemoryResident( handle, ptr, size );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::MakeMemoryResident");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceEvictMemory
    inline void Device::EvictMemory(
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        // auto result = ::xeDeviceEvictMemory( handle, ptr, size );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::EvictMemory");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceMakeImageResident
    inline void Device::MakeImageResident(
        image_handle_t hImage                           ///< [in] handle of image to make resident
        )
    {
        // auto result = ::xeDeviceMakeImageResident( handle, hImage );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::MakeImageResident");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceEvictImage
    inline void Device::EvictImage(
        image_handle_t hImage                           ///< [in] handle of image to make evict
        )
    {
        // auto result = ::xeDeviceEvictImage( handle, hImage );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::EvictImage");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateSampler
    inline void Device::CreateSampler(
        const sampler_desc_t* pDesc,                    ///< [in] pointer to sampler descriptor
        sampler_handle_t* phSampler                     ///< [out] handle of the sampler
        )
    {
        // auto result = ::xeDeviceCreateSampler( handle, pDesc, phSampler );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateSampler");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDeviceCreateSemaphore
    inline void Device::CreateSemaphore(
        const semaphore_desc_t* desc,                   ///< [in] pointer to semaphore descriptor
        semaphore_handle_t* phSemaphore                 ///< [out] pointer to handle of semaphore object created
        )
    {
        // auto result = ::xeDeviceCreateSemaphore( handle, desc, phSemaphore );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CreateSemaphore");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_DEVICE_INL
