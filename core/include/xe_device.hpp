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
* @file xe_device.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/device.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_DEVICE_HPP
#define _XE_DEVICE_HPP
#if defined(__cplusplus)
#pragma once
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device
    class Device
    {
    protected:
        ::xe_device_handle_t handle;                      ///< handle of device object

    public:
        auto getHandle( void ) const { return handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_api_version_t
        enum class api_version_t
        {
            _1_0 = XE_MAKE_VERSION( 1, 0 ),                 ///< 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_device_properties_version_t
        enum class device_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_device_compute_properties_version_t
        enum class device_compute_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_device_memory_properties_version_t
        enum class device_memory_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_memory_access_capabilities_t
        enum class memory_access_capabilities_t
        {
            MEMORY_ACCESS = XE_BIT( 0 ),                    ///< Supports load/store access
            MEMORY_ATOMIC_ACCESS = XE_BIT( 1 ),             ///< Supports atomic access
            MEMORY_CONCURRENT_ACCESS = XE_BIT( 2 ),         ///< Supports concurrent access
            MEMORY_CONCURRENT_ATOMIC_ACCESS = XE_BIT( 3 ),  ///< Supports concurrent atomic access

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_device_p2p_properties_version_t
        enum class device_p2p_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_cache_config_t
        enum class cache_config_t
        {
            DEFAULT = XE_BIT( 0 ),                          ///< Default Config
            LARGE_SLM = XE_BIT( 1 ),                        ///< Large SLM size
            LARGE_DATA = XE_BIT( 2 ),                       ///< Large General Data size

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_device_uuid_t
        struct device_uuid_t
        {
            uint8_t id[XE_MAX_UUID_SIZE];                   ///< [out] device universal unique id

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_device_properties_t
        struct device_properties_t
        {
            device_properties_version_t version = device_properties_version_t::CURRENT; ///< [in] ::DEVICE_PROPERTIES_VERSION_CURRENT
            uint32_t vendorId;                              ///< [out] vendor id from PCI configuration
            uint32_t deviceId;                              ///< [out] device id from PCI configuration
            uint32_t subdeviceId;                           ///< [out] Subdevice id. Only valid if isSubdevice is true.
            device_uuid_t uuid;                             ///< [out] unique id for device.
            bool_t isSubdevice;                             ///< [out] Is this a subdevice.
            uint32_t numSubDevices;                         ///< [out] Number of sub-devices.
            uint32_t coreClockRate;                         ///< [out] Clock rate for device core.
            uint32_t memClockRate;                          ///< [out] Clock rate for device global memory
            uint32_t memGlobalBusWidth;                     ///< [out] Bus width between core and memory.
            uint64_t totalLocalMemSize;                     ///< [out] Total memory size in bytes.
            uint32_t maxCommandQueues;                      ///< [out] Maximum number of logical command queues.
            uint32_t numAsyncComputeEngines;                ///< [out] Number of asynchronous compute engines
            uint32_t numAsyncCopyEngines;                   ///< [out] Number of asynchronous copy engines
            uint32_t maxCommandQueuePriority;               ///< [out] Maximum priority for command queues. Higher value is higher
                                                            ///< priority.
            uint32_t numThreadsPerEU;                       ///< [out] Number of threads per EU.
            uint32_t physicalEUSimdWidth;                   ///< [out] The physical EU simd width.
            uint32_t numEUsPerSubslice;                     ///< [out] Number of EUs per sub-slice.
            uint32_t numSubslicesPerSlice;                  ///< [out] Number of sub-slices per slice.
            uint32_t numSlicesPerTile;                      ///< [out] Number of slices per tile.
            uint32_t numTiles;                              ///< [out] Number of tiles for this device.
            char name[XE_MAX_DEVICE_NAME];                  ///< [out] Device name

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_device_compute_properties_t
        struct device_compute_properties_t
        {
            device_compute_properties_version_t version = device_compute_properties_version_t::CURRENT; ///< [in] ::DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT
            uint32_t maxThreadsPerGroup;                    ///< [out] Maximum threads per compute group
            uint32_t maxGroupSizeX;                         ///< [out] Maximum items for X dimension in group
            uint32_t maxGroupSizeY;                         ///< [out] Maximum items for Y dimension in group
            uint32_t maxGroupSizeZ;                         ///< [out] Maximum items for Z dimension in group
            uint32_t maxGroupCountX;                        ///< [out] Maximum groups that can be launched for x dimension
            uint32_t maxGroupCountY;                        ///< [out] Maximum groups that can be launched for y dimension
            uint32_t maxGroupCountZ;                        ///< [out] Maximum groups that can be launched for z dimension
            uint32_t maxSharedLocalMemory;                  ///< [out] Maximum shared local memory per group.
            uint32_t maxGroupRegisters;                     ///< [out] Maximum physical registers available per group
            uint32_t numSubGroupSizes;                      ///< [out] Number of subgroup sizes supported. This indicates number of
                                                            ///< entries in subGroupSizes.
            uint32_t subGroupSizes[XE_SUBGROUPSIZE_COUNT];  ///< [out] Size group sizes supported.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_device_memory_properties_t
        struct device_memory_properties_t
        {
            device_memory_properties_version_t version = device_memory_properties_version_t::CURRENT;   ///< [in] ::DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT
            bool_t unifiedMemory;                           ///< [out] Host and device share same physical memory.
            bool_t onDemandPageFaults;                      ///< [out] Device supports on-demand page-faulting.
            uint32_t maxImageDims1D;                        ///< [out] Maximum image dimensions for 1D resources.
            uint32_t maxImageDims2D;                        ///< [out] Maximum image dimensions for 2D resources.
            uint32_t maxImageDims3D;                        ///< [out] Maximum image dimensions for 3D resources.
            uint32_t maxImageArraySlices;                   ///< [out] Maximum image array slices
            memory_access_capabilities_t hostAllocCapabilities; ///< [out] Bitfield describing host memory capabilities
            memory_access_capabilities_t deviceAllocCapabilities;   ///< [out] Bitfield describing device memory capabilities
            memory_access_capabilities_t sharedAllocCapabilities;   ///< [out] Bitfield describing shared memory capabilities
            memory_access_capabilities_t sharedCrossDeviceAllocCapabilities;///< [out] Bitfield describing shared (cross-device) memory capabilities
            memory_access_capabilities_t sharedSystemDeviceAllocCapabilities;   ///< [out] Bitfield describing shared (system) memory capabilities
            uint32_t intermediateCacheSize;                 ///< [out] Per-cache Intermediate Cache (L1/L2) size, in bytes
            bool_t intermediateCacheControl;                ///< [out] Support User control on Intermediate Cache (i.e. Resize SLM
                                                            ///< section vs Generic Cache)
            uint32_t lastLevelCacheSize;                    ///< [out] Per-cache Last Level Cache (L3) size, in bytes
            bool_t lastLevelCacheSizeControl;               ///< [out] Support User control on Last Level Cache (i.e. Resize SLM
                                                            ///< section vs Generic Cache).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_device_p2p_properties_t
        struct device_p2p_properties_t
        {
            device_p2p_properties_version_t version = device_p2p_properties_version_t::CURRENT; ///< [in] ::DEVICE_P2P_PROPERTIES_VERSION_CURRENT
            bool_t isP2PSupported;                          ///< [out] Is P2P access supported between two devices
            bool_t isAtomicsSupported;                      ///< [out] Are atomics supported between two devices

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceSystemBarrier
        /// @throws result_t
        inline void
        SystemBarrier(
            void
            );

#if XE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceRegisterCLMemory
        /// @returns
        ///     - void*: pointer to device allocation
        /// 
        /// @throws result_t
        inline void*
        RegisterCLMemory(
            cl_context context,                             ///< [in] the OpenCL context that created the memory
            cl_mem mem                                      ///< [in] the OpenCL memory to register
            );
#endif // XE_ENABLE_OCL_INTEROP

#if XE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceRegisterCLProgram
        /// @returns
        ///     - ::module_handle_t: pointer to handle of module object created
        /// 
        /// @throws result_t
        inline module_handle_t
        RegisterCLProgram(
            cl_context context,                             ///< [in] the OpenCL context that created the program
            cl_program program                              ///< [in] the OpenCL program to register
            );
#endif // XE_ENABLE_OCL_INTEROP

#if XE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceRegisterCLCommandQueue
        /// @returns
        ///     - ::command_queue_handle_t: pointer to handle of command queue object created
        /// 
        /// @throws result_t
        inline command_queue_handle_t
        RegisterCLCommandQueue(
            cl_context context,                             ///< [in] the OpenCL context that created the command queue
            cl_command_queue command_queue                  ///< [in] the OpenCL command queue to register
            );
#endif // XE_ENABLE_OCL_INTEROP

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetCount
        /// @returns
        ///     - uint32_t: number of devices available
        /// 
        /// @throws result_t
        inline static uint32_t
        GetCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGet
        /// @returns
        ///     - ::device_handle_t: pointer to handle of device object created
        /// 
        /// @throws result_t
        inline static device_handle_t
        Get(
            uint32_t ordinal                                ///< [in] The device index in the range of [0, ::DeviceGetCount]
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetSubDevice
        /// @returns
        ///     - ::device_handle_t: pointer to handle of sub-device object.
        /// 
        /// @throws result_t
        inline device_handle_t
        GetSubDevice(
            uint32_t ordinal                                ///< [in] ordinal of sub-device to retrieve
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetApiVersion
        /// @returns
        ///     - ::api_version_t: api version
        /// 
        /// @throws result_t
        inline api_version_t
        GetApiVersion(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetProperties
        /// @returns
        ///     - ::device_properties_t: query result for device properties
        /// 
        /// @throws result_t
        inline device_properties_t
        GetProperties(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetComputeProperties
        /// @returns
        ///     - ::device_compute_properties_t: query result for compute properties
        /// 
        /// @throws result_t
        inline device_compute_properties_t
        GetComputeProperties(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetMemoryProperties
        /// @returns
        ///     - ::device_memory_properties_t: query result for compute properties
        /// 
        /// @throws result_t
        inline device_memory_properties_t
        GetMemoryProperties(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetP2PProperties
        /// @returns
        ///     - ::device_p2p_properties_t: Peer-to-Peer properties between source and peer device
        /// 
        /// @throws result_t
        inline device_p2p_properties_t
        GetP2PProperties(
            device_handle_t hPeerDevice                     ///< [in] handle of the peer device with the allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceCanAccessPeer
        /// @returns
        ///     - ::bool_t: returned access capability
        /// 
        /// @throws result_t
        inline bool_t
        CanAccessPeer(
            device_handle_t hPeerDevice                     ///< [in] handle of the peer device with the allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceSetIntermediateCacheConfig
        /// @throws result_t
        inline void
        SetIntermediateCacheConfig(
            cache_config_t CacheConfig                      ///< [in] CacheConfig
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceSetLastLevelCacheConfig
        /// @throws result_t
        inline void
        SetLastLevelCacheConfig(
            cache_config_t CacheConfig                      ///< [in] CacheConfig
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceMakeMemoryResident
        /// @throws result_t
        inline void
        MakeMemoryResident(
            void* ptr,                                      ///< [in] pointer to memory to make resident
            size_t size                                     ///< [in] size in bytes to make resident
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceEvictMemory
        /// @throws result_t
        inline void
        EvictMemory(
            void* ptr,                                      ///< [in] pointer to memory to evict
            size_t size                                     ///< [in] size in bytes to evict
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceMakeImageResident
        /// @throws result_t
        inline void
        MakeImageResident(
            image_handle_t hImage                           ///< [in] handle of image to make resident
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceEvictImage
        /// @throws result_t
        inline void
        EvictImage(
            image_handle_t hImage                           ///< [in] handle of image to make evict
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_DEVICE_HPP
