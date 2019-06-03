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
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_MAX_UUID_SIZE
/// @brief Maximum device uuid size in bytes
#define XE_MAX_UUID_SIZE  16
#endif // XE_MAX_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_MAX_DEVICE_NAME
/// @brief Maximum device name string size
#define XE_MAX_DEVICE_NAME  256
#endif // XE_MAX_DEVICE_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_SUBGROUPSIZE_COUNT
/// @brief Maximum number of subgroup sizes supported.
#define XE_SUBGROUPSIZE_COUNT  8
#endif // XE_SUBGROUPSIZE_COUNT

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device group
    class DeviceGroup
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported API versions
        /// 
        /// @details
        ///     - API versions contain major and minor attributes, use ::MAJOR_VERSION
        ///       and ::MINOR_VERSION
        enum class api_version_t
        {
            _1_0 = XE_MAKE_VERSION( 1, 0 ),                 ///< 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::device_properties_t
        enum class device_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device types
        enum class device_type_t
        {
            GPU = 1,                                        ///< Graphics Processing Unit
            FPGA,                                           ///< Field Programmable Gate Array

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::device_compute_properties_t
        enum class device_compute_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::device_memory_properties_t
        enum class device_memory_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

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
            MEMORY_ACCESS = XE_BIT( 0 ),                    ///< Supports load/store access
            MEMORY_ATOMIC_ACCESS = XE_BIT( 1 ),             ///< Supports atomic access
            MEMORY_CONCURRENT_ACCESS = XE_BIT( 2 ),         ///< Supports concurrent access
            MEMORY_CONCURRENT_ATOMIC_ACCESS = XE_BIT( 3 ),  ///< Supports concurrent atomic access

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device memory allocation flags
        enum class device_mem_alloc_flag_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            BIAS_CACHED = XE_BIT( 0 ),                      ///< device should cache allocation
            BIAS_UNCACHED = XE_BIT( 1 ),                    ///< device should not cache allocation (UC)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported host memory allocation flags
        enum class host_mem_alloc_flag_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            BIAS_CACHED = XE_BIT( 0 ),                      ///< host should cache allocation
            BIAS_UNCACHED = XE_BIT( 1 ),                    ///< host should not cache allocation (UC)
            BIAS_WRITE_COMBINED = XE_BIT( 2 ),              ///< host memory should be allocated write-combined (WC)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::memory_allocation_properties_t
        enum class memory_allocation_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

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
        /// @brief Device universal unique id (UUID)
        struct device_uuid_t
        {
            uint8_t id[XE_MAX_UUID_SIZE];                   ///< [out] device universal unique id

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties queried using ::DeviceGroupGetProperties
        struct device_properties_t
        {
            device_properties_version_t version = device_properties_version_t::CURRENT; ///< [in] ::DEVICE_PROPERTIES_VERSION_CURRENT
            device_type_t type;                             ///< [out] generic device type
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
        /// @brief Device compute properties queried using
        ///        ::DeviceGroupGetComputeProperties
        struct device_compute_properties_t
        {
            device_compute_properties_version_t version = device_compute_properties_version_t::CURRENT; ///< [in] ::DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT
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
            uint32_t subGroupSizes[XE_SUBGROUPSIZE_COUNT];  ///< [out] Size group sizes supported.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device memory properties queried using
        ///        ::DeviceGroupGetMemoryProperties
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
            memory_access_capabilities_t sharedSingleDeviceAllocCapabilities;   ///< [out] Bitfield describing shared (single-device) memory capabilities
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
        /// @brief Memory allocation properties queried using
        ///        ::DeviceGroupGetMemProperties
        struct memory_allocation_properties_t
        {
            memory_allocation_properties_version_t version = memory_allocation_properties_version_t::CURRENT;   ///< [in] ::MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT
            memory_type_t type;                             ///< [out] type of allocated memory
            uint64_t id;                                    ///< [out] identifier for this allocation

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        device_group_handle_t m_handle;                 ///< [in] handle of device group object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        DeviceGroup( void ) = delete;
        DeviceGroup( 
            device_group_handle_t handle                    ///< [in] handle of device group object
            );

        ~DeviceGroup( void ) = default;

        DeviceGroup( DeviceGroup const& other ) = delete;
        void operator=( DeviceGroup const& other ) = delete;

        DeviceGroup( DeviceGroup&& other ) = delete;
        void operator=( DeviceGroup&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves device groups
        /// 
        /// @details
        ///     - A device group represents a collection of physical, homogeneous
        ///       devices.
        ///     - The application may pass nullptr for pDeviceGroups when only querying
        ///       the number of device groups.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clGetDeviceIDs
        /// @throws result_t
        static void __xecall
        Get(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of device groups available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< device groups.
            DeviceGroup** ppDeviceGroups = nullptr          ///< [in,out][optional][range(0, *pCount)] array of pointer to device
                                                            ///< groups
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current version of the installed driver for the specified
        ///        device group.
        /// 
        /// @details
        ///     - The driver version is a non-zero, monotonically increasing value where
        ///       higher values always indicate a more recent version.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuDriverGetVersion**
        /// @returns
        ///     - uint32_t: driver version
        /// 
        /// @throws result_t
        uint32_t __xecall
        GetDriverVersion(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the API version supported by the device group
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuCtxGetApiVersion**
        /// @returns
        ///     - api_version_t: api version
        /// 
        /// @throws result_t
        api_version_t __xecall
        GetApiVersion(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of the device
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
        /// @returns
        ///     - device_properties_t: query result for device properties
        /// 
        /// @throws result_t
        device_properties_t __xecall
        GetProperties(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves compute attributes of the device group
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuDeviceGetAttribute**
        ///     - clGetDeviceInfo
        /// @returns
        ///     - device_compute_properties_t: query result for compute properties
        /// 
        /// @throws result_t
        device_compute_properties_t __xecall
        GetComputeProperties(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves memory attributes of the device
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
        /// @returns
        ///     - device_memory_properties_t: query result for compute properties
        /// 
        /// @throws result_t
        device_memory_properties_t __xecall
        GetMemoryProperties(
            void
            );

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
        /// @returns
        ///     - void*: pointer to shared allocation
        /// 
        /// @throws result_t
        void* __xecall
        AllocSharedMem(
            Device* pDevice,                                ///< [in] pointer to a device
            device_mem_alloc_flag_t device_flags,           ///< [in] flags specifying additional device allocation controls
            host_mem_alloc_flag_t host_flags,               ///< [in] flags specifying additional host allocation controls
            size_t size,                                    ///< [in] size in bytes to allocate
            size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
            );

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
        /// @returns
        ///     - void*: pointer to device allocation
        /// 
        /// @throws result_t
        void* __xecall
        AllocDeviceMem(
            Device* pDevice,                                ///< [in] pointer to the device
            device_mem_alloc_flag_t flags,                  ///< [in] flags specifying additional allocation controls
            size_t size,                                    ///< [in] size in bytes to allocate
            size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
            );

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
        /// @returns
        ///     - void*: pointer to host allocation
        /// 
        /// @throws result_t
        void* __xecall
        AllocHostMem(
            host_mem_alloc_flag_t flags,                    ///< [in] flags specifying additional allocation controls
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
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cudaFree**
        ///     - **cudaFreeHost**
        /// @throws result_t
        void __xecall
        FreeMem(
            const void* ptr                                 ///< [in][release] pointer to memory to free
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of a memory allocation
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuPointerGetAttribute**
        /// @returns
        ///     - memory_allocation_properties_t: query result for memory allocation properties
        ///     - Device*: device associated with this allocation
        /// 
        /// @throws result_t
        memory_allocation_properties_t __xecall
        GetMemProperties(
            const void* ptr,                                ///< [in] memory pointer to query
            Device** ppDevice = nullptr                     ///< [out][optional] device associated with this allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves the base address and/or size of an allocation
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuMemGetAddressRange**
        /// @throws result_t
        void __xecall
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
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuIpcGetMemHandle**
        /// @returns
        ///     - ipc_mem_handle_t: Returned IPC memory handle
        /// 
        /// @throws result_t
        ipc_mem_handle_t __xecall
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
        ///       ::DeviceGroupFreeMem, but rather with ::DeviceGroupCloseMemIpcHandle.
        ///     - The application may call this function from simultaneous threads.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuIpcOpenMemHandle**
        /// @returns
        ///     - void*: pointer to device allocation in this process
        /// 
        /// @throws result_t
        void* __xecall
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
        ///       this process using ::DeviceGroupOpenMemIpcHandle.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same pointer.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuIpcCloseMemHandle**
        /// @throws result_t
        void __xecall
        CloseMemIpcHandle(
            const void* ptr                                 ///< [in][release] pointer to device allocation in this process
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device
    class Device
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::device_p2p_properties_t
        enum class p2p_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported Cache Config
        /// 
        /// @details
        ///     - Supported Cache Config (Default, Large SLM, Large Data Cache)
        enum class cache_config_t
        {
            DEFAULT = XE_BIT( 0 ),                          ///< Default Config
            LARGE_SLM = XE_BIT( 1 ),                        ///< Large SLM size
            LARGE_DATA = XE_BIT( 2 ),                       ///< Large General Data size

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties queried using ::DeviceGetP2PProperties
        struct p2p_properties_t
        {
            p2p_properties_version_t version = p2p_properties_version_t::CURRENT;   ///< [in] ::DEVICE_P2P_PROPERTIES_VERSION_CURRENT
            bool_t isP2PSupported;                          ///< [out] Is P2P access supported between two devices
            bool_t isAtomicsSupported;                      ///< [out] Are atomics supported between two devices

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        device_handle_t m_handle;                       ///< [in] handle of device object
        DeviceGroup* m_pDeviceGroup;                    ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Device( void ) = delete;
        Device( 
            device_handle_t handle,                         ///< [in] handle of device object
            DeviceGroup* pDeviceGroup                       ///< [in] pointer to owner object
            );

        ~Device( void ) = default;

        Device( Device const& other ) = delete;
        void operator=( Device const& other ) = delete;

        Device( Device&& other ) = delete;
        void operator=( Device&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevicegroup( void ) const { return m_pDeviceGroup; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves devices within a device group
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuDeviceGet**
        /// @throws result_t
        static void __xecall
        Get(
            DeviceGroup* pDeviceGroup,                      ///< [in] pointer to the device group object
            uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of device groups available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< device groups.
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
        /// @returns
        ///     - Device*: pointer to handle of sub-device object.
        /// 
        /// @throws result_t
        Device* __xecall
        GetSubDevice(
            uint32_t ordinal                                ///< [in] ordinal of sub-device to retrieve; must be less than
                                                            ///< ::device_properties_t::numSubDevices
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves Peer-to-Peer properties between one device and a peer
        ///        devices
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cudaDeviceGetP2PAttribute**
        /// @returns
        ///     - p2p_properties_t: Peer-to-Peer properties between source and peer device
        /// 
        /// @throws result_t
        p2p_properties_t __xecall
        GetP2PProperties(
            Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
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
        ///         + If both device and remote device are connected by a scale-up
        ///           fabric then true, if pci-e then false.
        ///         + If both sub-device and remote parent device (and vice-versa) are
        ///           connected by a scale-up fabric then true, if pci-e then false.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cudaDeviceCanAccessPeer**
        /// @returns
        ///     - bool_t: returned access capability
        /// 
        /// @throws result_t
        bool_t __xecall
        CanAccessPeer(
            Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the preferred Intermediate cache configuration for a device.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same device handle.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cudaFuncSetCacheConfig **
        /// @throws result_t
        void __xecall
        SetIntermediateCacheConfig(
            cache_config_t CacheConfig                      ///< [in] CacheConfig
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the preferred Last Level cache configuration for a device.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same device handle.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cudaFuncSetCacheConfig **
        /// @throws result_t
        void __xecall
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
        void __xecall
        SystemBarrier(
            void
            );

#if XE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Registers OpenCL memory with Xe::
        /// @returns
        ///     - void*: pointer to device allocation
        /// 
        /// @throws result_t
        void* __xecall
        RegisterCLMemory(
            cl_context context,                             ///< [in] the OpenCL context that created the memory
            cl_mem mem                                      ///< [in] the OpenCL memory to register
            );
#endif // XE_ENABLE_OCL_INTEROP

#if XE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Registers OpenCL program with Xe::
        /// @returns
        ///     - Module*: pointer to handle of module object created
        /// 
        /// @throws result_t
        Module* __xecall
        RegisterCLProgram(
            cl_context context,                             ///< [in] the OpenCL context that created the program
            cl_program program                              ///< [in] the OpenCL program to register
            );
#endif // XE_ENABLE_OCL_INTEROP

#if XE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Registers OpenCL command queue with Xe::
        /// @returns
        ///     - CommandQueue*: pointer to handle of command queue object created
        /// 
        /// @throws result_t
        CommandQueue* __xecall
        RegisterCLCommandQueue(
            cl_context context,                             ///< [in] the OpenCL context that created the command queue
            cl_command_queue command_queue                  ///< [in] the OpenCL command queue to register
            );
#endif // XE_ENABLE_OCL_INTEROP

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Makes memory resident for the device.
        /// 
        /// @details
        ///     - If the application does not properly manage residency then the device
        ///       may experience unrecoverable page-faults.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
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
        void __xecall
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
        void __xecall
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
        void __xecall
        EvictImage(
            Image* pImage                                   ///< [in] pointer to image to make evict
            );

    };

} // namespace xe

#ifdef _DEBUG
namespace std
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::api_version_t to std::string
    string to_string( const xe::DeviceGroup::api_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::device_properties_version_t to std::string
    string to_string( const xe::DeviceGroup::device_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::device_type_t to std::string
    string to_string( const xe::DeviceGroup::device_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::device_uuid_t to std::string
    string to_string( const xe::DeviceGroup::device_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::device_properties_t to std::string
    string to_string( const xe::DeviceGroup::device_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::device_compute_properties_version_t to std::string
    string to_string( const xe::DeviceGroup::device_compute_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::device_compute_properties_t to std::string
    string to_string( const xe::DeviceGroup::device_compute_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::device_memory_properties_version_t to std::string
    string to_string( const xe::DeviceGroup::device_memory_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::memory_access_capabilities_t to std::string
    string to_string( const xe::DeviceGroup::memory_access_capabilities_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::device_memory_properties_t to std::string
    string to_string( const xe::DeviceGroup::device_memory_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::device_mem_alloc_flag_t to std::string
    string to_string( const xe::DeviceGroup::device_mem_alloc_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::host_mem_alloc_flag_t to std::string
    string to_string( const xe::DeviceGroup::host_mem_alloc_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::memory_allocation_properties_version_t to std::string
    string to_string( const xe::DeviceGroup::memory_allocation_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::memory_type_t to std::string
    string to_string( const xe::DeviceGroup::memory_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::memory_allocation_properties_t to std::string
    string to_string( const xe::DeviceGroup::memory_allocation_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::DeviceGroup::ipc_memory_flag_t to std::string
    string to_string( const xe::DeviceGroup::ipc_memory_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Device::p2p_properties_version_t to std::string
    string to_string( const xe::Device::p2p_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Device::p2p_properties_t to std::string
    string to_string( const xe::Device::p2p_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Device::cache_config_t to std::string
    string to_string( const xe::Device::cache_config_t val );

} // namespace std
#endif // _DEBUG
#endif // defined(__cplusplus)
#endif // _XE_DEVICE_HPP
