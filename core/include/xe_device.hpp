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
* @brief C++ wrapper of Intel Xe Driver APIs for Device
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
        /// @brief C++ version for ::xe_command_graph_desc_version_t
        enum class command_graph_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_graph_flag_t
        enum class command_graph_flag_t
        {
            NONE = 0,                                       ///< default behavior

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_list_desc_version_t
        enum class command_list_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_list_flag_t
        enum class command_list_flag_t
        {
            NONE = 0,                                       ///< default behavior
            COPY_ONLY = XE_BIT(0),                          ///< command list **only** contains copy operations (and synchronization
                                                            ///< primitives)
            RELAXED_ORDERING = XE_BIT(1),                   ///< driver may reorder programs and copys between barriers and
                                                            ///< synchronization primitives
            LOW_LATENCY = XE_BIT(2),                        ///< driver should optimize for immediate submission to a command queue
            CROSS_DEVICE = XE_BIT(3),                       ///< command list can be shared with another device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_queue_desc_version_t
        enum class command_queue_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_queue_flag_t
        enum class command_queue_flag_t
        {
            NONE = 0,                                       ///< default behavior
            COPY_ONLY = XE_BIT(0),                          ///< command queue only supports enqueing copy-only command lists
            LOGICAL_ONLY = XE_BIT(1),                       ///< command queue is not tied to a physical command queue; driver may
                                                            ///< dynamically assign based on usage
            SINGLE_SLICE_ONLY = XE_BIT(2),                  ///< command queue reserves and cannot comsume more than a single slice'
                                                            ///< 'slice' size is device-specific.  cannot be combined with COPY_ONLY.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_queue_mode_t
        enum class command_queue_mode_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            SYNCHRONOUS,                                    ///< GPU execution always completes immediately on enqueue; CPU thread is
                                                            ///< blocked using wait on implicit synchronization object
            ASYNCHRONOUS,                                   ///< GPU execution is scheduled and will complete in future; explicit
                                                            ///< synchronization object must be used to determine completeness

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_queue_priority_t
        enum class command_queue_priority_t
        {
            NORMAL = 0,                                     ///< [default] normal priority
            LOW,                                            ///< lower priority than normal
            HIGH,                                           ///< higher priority than normal

        };

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
        /// @brief C++ version for ::xe_device_link_properties_version_t
        enum class device_link_properties_version_t
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
        /// @brief C++ version for ::xe_event_desc_version_t
        enum class event_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_event_flag_t
        enum class event_flag_t
        {
            NONE = 0,                                       ///< signals and waits only within the same device
            HOST_TO_DEVICE = XE_BIT(0),                     ///< signals from host, waits on device
            DEVICE_TO_HOST = XE_BIT(1),                     ///< signals from device, waits on host
            DEVICE_TO_DEVICE = XE_BIT(2),                   ///< signals from device, waits on another device
            IPC = XE_BIT(3),                                ///< signals and waits may occur across processes
            TIMESTAMP = XE_BIT(4),                          ///< supports time-based queries
            PERFORMANCE_METRICS = XE_BIT(5),                ///< supports performance metrics (MDAPI)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_desc_version_t
        enum class image_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_flag_t
        enum class image_flag_t
        {
            PROGRAM_READ = XE_BIT( 0 ),                     ///< programs will read contents
            PROGRAM_WRITE = XE_BIT( 1 ),                    ///< programs will write contents
            BIAS_CACHED = XE_BIT( 2 ),                      ///< device should cache contents
            BIAS_UNCACHED = XE_BIT( 3 ),                    ///< device should not cache contents

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_type_t
        enum class image_type_t
        {
            _1D,                                            ///< 1D
            _1DARRAY,                                       ///< 1D array
            _2D,                                            ///< 2D
            _2DARRAY,                                       ///< 2D array
            _3D,                                            ///< 3D

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_format_t
        enum class image_format_t
        {
            UINT8,                                          ///< 8-bit unsigned integer
            UINT16,                                         ///< 16-bit unsigned integer
            UINT32,                                         ///< 32-bit unsigned integer
            SINT8,                                          ///< 8-bit signed integer
            SINT16,                                         ///< 16-bit signed integer
            SINT32,                                         ///< 32-bit signed integer
            FLOAT16,                                        ///< 16-bit float
            FLOAT32,                                        ///< 32-bit float

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_module_desc_version_t
        enum class module_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_module_format_t
        enum class module_format_t
        {
            IL_SPIRV = 0,                                   ///< Format is SPIRV IL format
            NATIVE,                                         ///< Format is device native format

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_sampler_desc_version_t
        enum class sampler_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_sampler_address_mode_t
        enum class sampler_address_mode_t
        {
            NONE = 0,                                       ///< No coordinate modifications for out-of-bounds image access.
            REPEAT,                                         ///< Out-of-bounds coordinates are wrapped back around.
            CLAMP,                                          ///< Out-of-bounds coordinates are clamped to edge.
            MIRROR,                                         ///< Out-of-bounds coordinates are mirrored starting from edge.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_sampler_filter_mode_t
        enum class sampler_filter_mode_t
        {
            NEAREST = 0,                                    ///< No coordinate modifications for out of bounds image access.
            LINEAR,                                         ///< Out-of-bounds coordinates are wrapped back around.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_graph_desc_t
        struct command_graph_desc_t
        {
            command_graph_desc_version_t version = command_graph_desc_version_t::CURRENT;   ///< [in] ::COMMAND_GRAPH_DESC_VERSION_CURRENT
            command_graph_flag_t flags = command_graph_flag_t::NONE;///< [in] creation flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_list_desc_t
        struct command_list_desc_t
        {
            command_list_desc_version_t version = command_list_desc_version_t::CURRENT; ///< [in] ::COMMAND_LIST_DESC_VERSION_CURRENT
            command_list_flag_t flags = command_list_flag_t::NONE;  ///< [in] creation flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_queue_desc_t
        struct command_queue_desc_t
        {
            command_queue_desc_version_t version = command_queue_desc_version_t::CURRENT;   ///< [in] ::COMMAND_QUEUE_DESC_VERSION_CURRENT
            command_queue_flag_t flags = command_queue_flag_t::NONE;///< [in] creation flags
            command_queue_mode_t mode = command_queue_mode_t::DEFAULT;  ///< [in] operation mode
            command_queue_priority_t priority = command_queue_priority_t::NORMAL;   ///< [in] priority
            uint32_t ordinal = 0;                           ///< [in] if logical-only flag is set, then must be 0; else-if copy-only
                                                            ///< flag is set, then must be less than
                                                            ///< ::device_properties_t.numAsyncCopyEngines; otherwise must be less than
                                                            ///< ::device_properties_t.numAsyncComputeEngines. When using sub-devices
                                                            ///< the ::device_properties_t.numAsyncComputeEngines must be queried from
                                                            ///< the sub-device being used.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_device_properties_t
        struct device_properties_t
        {
            device_properties_version_t version = device_properties_version_t::CURRENT; ///< [in] ::DEVICE_PROPERTIES_VERSION_CURRENT
            uint32_t vendorId;                              ///< [out] vendor id from PCI configuration
            uint32_t deviceId;                              ///< [out] device id from PCI configuration
            uint32_t subdeviceId;                           ///< [out] Subdevice id. Only valid if isSubdevice is true.
            bool_t isSubdevice;                             ///< [out] Is this a subdevice.
            uint32_t numSubDevices;                         ///< [out] Number of sub-devices.
            uint32_t coreClockRate;                         ///< [out] Clock rate for device core.
            uint32_t memClockRate;                          ///< [out] Clock rate for device global memory
            uint32_t memGlobalBusWidth;                     ///< [out] Bus width between core and memory.
            uint64_t totalLocalMemSize;                     ///< [out] Total memory size in bytes.
            uint32_t numAsyncComputeEngines;                ///< [out] Number of asynchronous compute engines
            uint32_t numAsyncCopyEngines;                   ///< [out] Number of asynchronous copy engines
            uint32_t numComputeCores;                       ///< [out] Number of compute cores
            uint32_t maxCommandQueuePriority;               ///< [out] Maximum priority for command queues. Higher value is higher
                                                            ///< priority.
            uint32_t numThreadsPerEU;                       ///< [out] Number of threads per EU.
            uint32_t numEUsPerDSS;                          ///< [out] Number of EUs per dual sub-slice.
            uint32_t numDSSPerSlice;                        ///< [out] Number of dual sub-slices per slice.
            uint32_t numSlicesPerTile;                      ///< [out] Number of slices per tile.
            uint32_t numTiles;                              ///< [out] Number of tiles for this device.
            char device_name[XE_MAX_DEVICE_NAME];           ///< [out] Device name

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
            uint32_t maxGroupCountX;                        ///< [out] Maximum groups that can be dispatched for x dimension
            uint32_t maxGroupCountY;                        ///< [out] Maximum groups that can be dispatched for y dimension
            uint32_t maxGroupCountZ;                        ///< [out] Maximum groups that can be dispatched for z dimension
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
        /// @brief C++ version for ::xe_device_link_properties_t
        struct device_link_properties_t
        {
            device_link_properties_version_t version = device_link_properties_version_t::CURRENT;   ///< [in] ::DEVICE_LINK_PROPERTIES_VERSION_CURRENT
            bool_t isP2PSupported;                          ///< [out] Is P2P access supported across link
            bool_t isAtomicsSupported;                      ///< [out] Are atomics supported across link
            uint32_t performanceRank;                       ///< [out] Relative performance rank of link.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_event_desc_t
        struct event_desc_t
        {
            event_desc_version_t version = event_desc_version_t::CURRENT;   ///< [in] ::EVENT_DESC_VERSION_CURRENT
            event_flag_t flags = event_flag_t::NONE;        ///< [in] creation flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_desc_t
        struct image_desc_t
        {
            image_desc_version_t version = image_desc_version_t::CURRENT;   ///< [in] ::IMAGE_DESC_VERSION_CURRENT
            image_flag_t flags;                             ///< [in] creation flags
            image_type_t type;                              ///< [in] image type
            image_format_t format;                          ///< [in] image channel format
            uint32_t numChannels = 1;                       ///< [in] number of channels per pixel [1,4]
            size_t width = 0;                               ///< [in] width in pixels, see
                                                            ///< ::device_memory_properties_t::maxImageDims1D/2D/3D
            size_t height = 0;                              ///< [in] height in pixels (2D or 3D only), see
                                                            ///< ::device_memory_properties_t::maxImageDims2D/3D
            size_t depth = 0;                               ///< [in] depth in pixels (3D only), see
                                                            ///< ::device_memory_properties_t::maxImageDims3D
            size_t arraylevels = 1;                         ///< [in] array levels (array types only), see
                                                            ///< ::device_memory_properties_t::maxImageArraySlices
            size_t miplevels = 0;                           ///< [in] mipmap levels (must be 0)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_module_desc_t
        struct module_desc_t
        {
            module_desc_version_t version = module_desc_version_t::CURRENT; ///< [in] ::MODULE_DESC_VERSION_CURRENT
            module_format_t format;                         ///< [in] Module format passed in with pInputModule
            size_t inputSize = 0;                           ///< [in] size of input IL or ISA from pInputModule.
            const char* pInputModule = nullptr;             ///< [in] pointer to IL or ISA
            const char* pBuildFlags = nullptr;              ///< [in] string containing compiler flags. See documentation for build
                                                            ///< flags.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_sampler_desc_t
        struct sampler_desc_t
        {
            sampler_desc_version_t version = sampler_desc_version_t::CURRENT;   ///< [in] ::SAMPLER_DESC_VERSION_CURRENT
            sampler_address_mode_t addressMode = sampler_address_mode_t::NONE;  ///< [in] Sampler addressing mode to determine how out-of-bounds
                                                            ///< coordinates are handled.
            sampler_filter_mode_t filterMode = sampler_filter_mode_t::NEAREST;  ///< [in] Sampler filter mode to determine how samples are filtered.
            bool_t isNormalized = true;                     ///< [in] Are coordinates normalized [0, 1] or not.

        };

#if XE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceRegisterCLMemory
        inline void RegisterCLMemory(
            cl_context context,                             ///< [in] the OpenCL context that created the memory
            cl_mem mem,                                     ///< [in] the OpenCL memory to register
            void** ptr                                      ///< [out] pointer to device allocation
            );
#endif // XE_ENABLE_OCL_INTEROP

#if XE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceRegisterCLProgram
        inline void RegisterCLProgram(
            cl_context context,                             ///< [in] the OpenCL context that created the program
            cl_program program,                             ///< [in] the OpenCL program to register
            module_handle_t* phModule                       ///< [out] pointer to handle of module object created
            );
#endif // XE_ENABLE_OCL_INTEROP

#if XE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceRegisterCLCommandQueue
        inline void RegisterCLCommandQueue(
            cl_context context,                             ///< [in] the OpenCL context that created the command queue
            cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
            command_queue_handle_t* phCommandQueue          ///< [out] pointer to handle of command queue object created
            );
#endif // XE_ENABLE_OCL_INTEROP

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceCreateCommandGraph
        inline void CreateCommandGraph(
            const command_graph_desc_t* desc,               ///< [in] pointer to command graph descriptor
            command_graph_handle_t* phCommandGraph          ///< [out] pointer to handle of command graph object created
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceCreateCommandList
        inline void CreateCommandList(
            const command_list_desc_t* desc,                ///< [in] pointer to command list descriptor
            command_list_handle_t* phCommandList            ///< [out] pointer to handle of command list object created
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceCopyCommandList
        inline void CopyCommandList(
            command_list_handle_t hCommandList,             ///< [in] handle to command list to copy
            command_list_handle_t* phCommandList            ///< [out] pointer to handle of command list object created
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceCreateCommandQueue
        inline void CreateCommandQueue(
            const command_queue_desc_t* desc,               ///< [in] pointer to command queue descriptor
            command_queue_handle_t* phCommandQueue          ///< [out] pointer to handle of command queue object created
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetSubDevice
        inline void GetSubDevice(
            uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
            device_handle_t* phSubDevice                    ///< [out] pointer to handle of sub-device object.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetApiVersion
        inline void GetApiVersion(
            api_version_t* version                          ///< [out] api version
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetProperties
        inline void GetProperties(
            device_properties_t* pDeviceProperties          ///< [out] query result for device properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetComputeProperties
        inline void GetComputeProperties(
            device_compute_properties_t* pComputeProperties ///< [out] query result for compute properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceGetMemoryProperties
        inline void GetMemoryProperties(
            device_memory_properties_t* pMemProperties      ///< [out] query result for compute properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceCanAccessPeer
        inline void CanAccessPeer(
            device_handle_t hPeerDevice,                    ///< [in] handle of the peer device with the allocation
            bool_t* value                                   ///< [out] returned access capability
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceSetIntermediateCacheConfig
        inline void SetIntermediateCacheConfig(
            cache_config_t CacheConfig                      ///< [in] CacheConfig
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceSetLastLevelCacheConfig
        inline void SetLastLevelCacheConfig(
            cache_config_t CacheConfig                      ///< [in] CacheConfig
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceCreateEvent
        inline void CreateEvent(
            const event_desc_t* desc,                       ///< [in] pointer to event descriptor
            event_handle_t* phEvent                         ///< [out] pointer to handle of event object created
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDevicePlaceEvent
        inline void PlaceEvent(
            const event_desc_t* desc,                       ///< [in] pointer to event descriptor
            void* ptr,                                      ///< [in] pointer to the device pointer where the event should be placed
            event_handle_t* phEvent                         ///< [out] pointer to handle of event object created
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceCreateImage
        inline void CreateImage(
            const image_desc_t* desc,                       ///< [in] pointer to image descriptor
            image_handle_t* phImage                         ///< [out] pointer to handle of image object created
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceCreateModule
        inline void CreateModule(
            const module_desc_t* pDesc,                     ///< [in] pointer to module descriptor
            module_handle_t* phModule,                      ///< [out] pointer to handle of module object created
            module_build_log_handle_t* phBuildLog           ///< [out][optional] pointer to handle of module's build log.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceMakeMemoryResident
        inline void MakeMemoryResident(
            void* ptr,                                      ///< [in] pointer to memory to make resident
            size_t size                                     ///< [in] size in bytes to make resident
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceEvictMemory
        inline void EvictMemory(
            void* ptr,                                      ///< [in] pointer to memory to evict
            size_t size                                     ///< [in] size in bytes to evict
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceMakeImageResident
        inline void MakeImageResident(
            image_handle_t hImage                           ///< [in] handle of image to make resident
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceEvictImage
        inline void EvictImage(
            image_handle_t hImage                           ///< [in] handle of image to make evict
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDeviceCreateSampler
        inline void CreateSampler(
            const sampler_desc_t* pDesc,                    ///< [in] pointer to sampler descriptor
            sampler_handle_t* phSampler                     ///< [out] handle of the sampler
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_DEVICE_HPP
