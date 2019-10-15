"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

 @file ze.py

 @cond DEV
 DO NOT EDIT: generated from /scripts/templates/libddi.py.mako
 @endcond

"""
import platform
from ctypes import *
from enum import *

###############################################################################
__version__ = "1.0"

###############################################################################
## @brief Generates generic 'One API' API versions
def ZE_MAKE_VERSION( _major, _minor ):
    return (( _major << 16 )|( _minor & 0x0000ffff))

###############################################################################
## @brief Extracts 'One API' API major version
def ZE_MAJOR_VERSION( _ver ):
    return ( _ver >> 16 )

###############################################################################
## @brief Extracts 'One API' API minor version
def ZE_MINOR_VERSION( _ver ):
    return ( _ver & 0x0000ffff )

###############################################################################
## @brief Calling convention for all API functions
# __zecall not required for python

###############################################################################
## @brief Microsoft-specific dllexport storage-class attribute
# __zedllexport not required for python

###############################################################################
## @brief Disable OpenCL interoperability functions if not explicitly defined
ZE_ENABLE_OCL_INTEROP = 0

###############################################################################
## @brief compiler-independent type
class ze_bool_t(c_ubyte):
    pass

###############################################################################
## @brief Handle of a driver instance
class ze_driver_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's device object
class ze_device_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's command queue object
class ze_command_queue_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's command list object
class ze_command_list_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's fence object
class ze_fence_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's event pool object
class ze_event_pool_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's event object
class ze_event_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's image object
class ze_image_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's module object
class ze_module_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of module's build log object
class ze_module_build_log_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's kernel object
class ze_kernel_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's sampler object
class ze_sampler_handle_t(c_void_p):
    pass

###############################################################################
## @brief Maximum IPC handle size
ZE_MAX_IPC_HANDLE_SIZE = 64

###############################################################################
## @brief IPC handle to a memory allocation
class ze_ipc_mem_handle_t(Structure):
    _fields_ = [
        ("data", c_char * ZE_MAX_IPC_HANDLE_SIZE)                       ## Opaque data representing an IPC handle
    ]

###############################################################################
## @brief IPC handle to a event pool allocation
class ze_ipc_event_pool_handle_t(Structure):
    _fields_ = [
        ("data", c_char * ZE_MAX_IPC_HANDLE_SIZE)                       ## Opaque data representing an IPC handle
    ]

###############################################################################
## @brief Generic macro for enumerator bit masks
def ZE_BIT( _i ):
    return ( 1 << _i )

###############################################################################
## @brief Defines Return/Error codes
## 
## @remarks
##   _Analogues_
##     - **CUresult**
class ze_result_v(IntEnum):
    SUCCESS = 0                                     ## success
    NOT_READY = 1                                   ## synchronization primitive not signaled
    ERROR_UNINITIALIZED = auto()                    ## driver is not initialized
    ERROR_DEVICE_LOST = auto()                      ## device hung, reset, was removed, or driver update occurred
    ERROR_UNSUPPORTED = auto()                      ## device does not support feature requested
    ERROR_INVALID_ARGUMENT = auto()                 ## invalid argument provided
    ERROR_OUT_OF_HOST_MEMORY = auto()               ## insufficient host memory to satisfy call
    ERROR_OUT_OF_DEVICE_MEMORY = auto()             ## insufficient device memory to satisfy call
    ERROR_MODULE_BUILD_FAILURE = auto()             ## error in building module
    ERROR_INSUFFICENT_PERMISSIONS = auto()          ## access denied
    ERROR_DEVICE_IS_IN_USE = auto()                 ## the device is already in use
    ERROR_ARRAY_SIZE_TOO_SMALL = auto()             ## an array argument doesn't have enough storage
    ERROR_DEVICE_ACCESS = auto()                    ## there was a problem accessing device data
    ERROR_UNKNOWN = 0x7fffffff                      ## unknown or internal error

class ze_result_t(c_int):
    def __str__(self):
        return str(ze_result_v(value))


###############################################################################
## @brief Supported initialization flags
class ze_init_flag_v(IntEnum):
    NONE = 0                                        ## default behavior
    GPU_ONLY = ZE_BIT(0)                            ## only initialize GPU drivers

class ze_init_flag_t(c_int):
    def __str__(self):
        return str(ze_init_flag_v(value))


###############################################################################
## @brief Supported API versions
## 
## @details
##     - API versions contain major and minor attributes, use
##       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
class ze_api_version_v(IntEnum):
    _1_0 = ZE_MAKE_VERSION( 1, 0 )                  ## 1.0

class ze_api_version_t(c_int):
    def __str__(self):
        return str(ze_api_version_v(value))


###############################################################################
## @brief API version of ::ze_driver_ipc_properties_t
class ze_driver_ipc_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_driver_ipc_properties_version_t(c_int):
    def __str__(self):
        return str(ze_driver_ipc_properties_version_v(value))


###############################################################################
## @brief IPC properties queried using ::zeDriverGetIPCProperties
class ze_driver_ipc_properties_t(Structure):
    _fields_ = [
        ("version", ze_driver_ipc_properties_version_t),                ## [in] ::ZE_DRIVER_IPC_PROPERTIES_VERSION_CURRENT
        ("memsSupported", ze_bool_t),                                   ## [out] Supports passing memory allocations between processes. See
                                                                        ## ::::zeDriverGetMemIpcHandle.
        ("eventsSupported", ze_bool_t)                                  ## [out] Supports passing events between processes. See
                                                                        ## ::::zeEventPoolGetIpcHandle.
    ]

###############################################################################
## @brief API version of ::ze_device_properties_t
class ze_device_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_device_properties_version_t(c_int):
    def __str__(self):
        return str(ze_device_properties_version_v(value))


###############################################################################
## @brief Maximum device uuid size in bytes
ZE_MAX_UUID_SIZE = 16

###############################################################################
## @brief Supported device types
class ze_device_type_v(IntEnum):
    GPU = 1                                         ## Graphics Processing Unit
    FPGA = auto()                                   ## Field Programmable Gate Array

class ze_device_type_t(c_int):
    def __str__(self):
        return str(ze_device_type_v(value))


###############################################################################
## @brief Device universal unique id (UUID)
class ze_device_uuid_t(Structure):
    _fields_ = [
        ("id", c_ubyte * ZE_MAX_UUID_SIZE)                              ## [out] device universal unique id
    ]

###############################################################################
## @brief Maximum device name string size
ZE_MAX_DEVICE_NAME = 256

###############################################################################
## @brief Device properties queried using ::zeDeviceGetProperties
class ze_device_properties_t(Structure):
    _fields_ = [
        ("version", ze_device_properties_version_t),                    ## [in] ::ZE_DEVICE_PROPERTIES_VERSION_CURRENT
        ("type", ze_device_type_t),                                     ## [out] generic device type
        ("vendorId", c_ulong),                                          ## [out] vendor id from PCI configuration
        ("deviceId", c_ulong),                                          ## [out] device id from PCI configuration
        ("uuid", ze_device_uuid_t),                                     ## [out] universal unique identifier.
        ("isSubdevice", ze_bool_t),                                     ## [out] If the device handle used for query represents a sub-device.
        ("subdeviceId", c_ulong),                                       ## [out] sub-device id. Only valid if isSubdevice is true.
        ("coreClockRate", c_ulong),                                     ## [out] Clock rate for device core.
        ("unifiedMemorySupported", ze_bool_t),                          ## [out] Supports unified physical memory between Host and device.
        ("onDemandPageFaultsSupported", ze_bool_t),                     ## [out] Supports on-demand page-faulting.
        ("maxCommandQueues", c_ulong),                                  ## [out] Maximum number of logical command queues.
        ("numAsyncComputeEngines", c_ulong),                            ## [out] Number of asynchronous compute engines
        ("numAsyncCopyEngines", c_ulong),                               ## [out] Number of asynchronous copy engines
        ("maxCommandQueuePriority", c_ulong),                           ## [out] Maximum priority for command queues. Higher value is higher
                                                                        ## priority.
        ("numThreadsPerEU", c_ulong),                                   ## [out] Number of threads per EU.
        ("physicalEUSimdWidth", c_ulong),                               ## [out] The physical EU simd width.
        ("numEUsPerSubslice", c_ulong),                                 ## [out] Number of EUs per sub-slice.
        ("numSubslicesPerSlice", c_ulong),                              ## [out] Number of sub-slices per slice.
        ("numSlicesPerTile", c_ulong),                                  ## [out] Number of slices per tile.
        ("numTiles", c_ulong),                                          ## [out] Number of tiles.
        ("name", c_char * ZE_MAX_DEVICE_NAME)                           ## [out] Device name
    ]

###############################################################################
## @brief API version of ::ze_device_compute_properties_t
class ze_device_compute_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_device_compute_properties_version_t(c_int):
    def __str__(self):
        return str(ze_device_compute_properties_version_v(value))


###############################################################################
## @brief Maximum number of subgroup sizes supported.
ZE_SUBGROUPSIZE_COUNT = 8

###############################################################################
## @brief Device compute properties queried using ::zeDeviceGetComputeProperties
class ze_device_compute_properties_t(Structure):
    _fields_ = [
        ("version", ze_device_compute_properties_version_t),            ## [in] ::ZE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT
        ("maxTotalGroupSize", c_ulong),                                 ## [out] Maximum items per compute group. (maxGroupSizeX * maxGroupSizeY
                                                                        ## * maxGroupSizeZ) <= maxTotalGroupSize
        ("maxGroupSizeX", c_ulong),                                     ## [out] Maximum items for X dimension in group
        ("maxGroupSizeY", c_ulong),                                     ## [out] Maximum items for Y dimension in group
        ("maxGroupSizeZ", c_ulong),                                     ## [out] Maximum items for Z dimension in group
        ("maxGroupCountX", c_ulong),                                    ## [out] Maximum groups that can be launched for x dimension
        ("maxGroupCountY", c_ulong),                                    ## [out] Maximum groups that can be launched for y dimension
        ("maxGroupCountZ", c_ulong),                                    ## [out] Maximum groups that can be launched for z dimension
        ("maxSharedLocalMemory", c_ulong),                              ## [out] Maximum shared local memory per group.
        ("numSubGroupSizes", c_ulong),                                  ## [out] Number of subgroup sizes supported. This indicates number of
                                                                        ## entries in subGroupSizes.
        ("subGroupSizes", c_ulong * ZE_SUBGROUPSIZE_COUNT)              ## [out] Size group sizes supported.
    ]

###############################################################################
## @brief API version of ::ze_device_memory_properties_t
class ze_device_memory_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_device_memory_properties_version_t(c_int):
    def __str__(self):
        return str(ze_device_memory_properties_version_v(value))


###############################################################################
## @brief Device local memory properties queried using
##        ::zeDeviceGetMemoryProperties
class ze_device_memory_properties_t(Structure):
    _fields_ = [
        ("version", ze_device_memory_properties_version_t),             ## [in] ::ZE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT
        ("maxClockRate", c_ulong),                                      ## [out] Maximum clock rate for device memory.
        ("maxBusWidth", c_ulong),                                       ## [out] Maximum bus width between device and memory.
        ("totalSize", c_ulonglong)                                      ## [out] Total memory size in bytes.
    ]

###############################################################################
## @brief API version of ::ze_device_memory_access_properties_t
class ze_device_memory_access_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_device_memory_access_properties_version_t(c_int):
    def __str__(self):
        return str(ze_device_memory_access_properties_version_v(value))


###############################################################################
## @brief Memory access capabilities
## 
## @details
##     - Supported access capabilities for different types of memory
##       allocations
class ze_memory_access_capabilities_v(IntEnum):
    MEMORY_ACCESS_NONE = 0                          ## Access not supported
    MEMORY_ACCESS = ZE_BIT( 0 )                     ## Supports load/store access
    MEMORY_ATOMIC_ACCESS = ZE_BIT( 1 )              ## Supports atomic access
    MEMORY_CONCURRENT_ACCESS = ZE_BIT( 2 )          ## Supports concurrent access
    MEMORY_CONCURRENT_ATOMIC_ACCESS = ZE_BIT( 3 )   ## Supports concurrent atomic access

class ze_memory_access_capabilities_t(c_int):
    def __str__(self):
        return str(ze_memory_access_capabilities_v(value))


###############################################################################
## @brief Device memory access properties queried using
##        ::zeDeviceGetMemoryAccessProperties
class ze_device_memory_access_properties_t(Structure):
    _fields_ = [
        ("version", ze_device_memory_access_properties_version_t),      ## [in] ::ZE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT
        ("hostAllocCapabilities", ze_memory_access_capabilities_t),     ## [out] Bitfield describing host memory capabilities
        ("deviceAllocCapabilities", ze_memory_access_capabilities_t),   ## [out] Bitfield describing device memory capabilities
        ("sharedSingleDeviceAllocCapabilities", ze_memory_access_capabilities_t),   ## [out] Bitfield describing shared (single-device) memory capabilities
        ("sharedCrossDeviceAllocCapabilities", ze_memory_access_capabilities_t),## [out] Bitfield describing shared (cross-device) memory capabilities
        ("sharedSystemAllocCapabilities", ze_memory_access_capabilities_t)  ## [out] Bitfield describing shared (system) memory capabilities
    ]

###############################################################################
## @brief API version of ::ze_device_cache_properties_t
class ze_device_cache_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_device_cache_properties_version_t(c_int):
    def __str__(self):
        return str(ze_device_cache_properties_version_v(value))


###############################################################################
## @brief Device cache properties queried using ::zeDeviceGetCacheProperties
class ze_device_cache_properties_t(Structure):
    _fields_ = [
        ("version", ze_device_cache_properties_version_t),              ## [in] ::ZE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT
        ("intermediateCacheControlSupported", ze_bool_t),               ## [out] Support User control on Intermediate Cache (i.e. Resize SLM
                                                                        ## section vs Generic Cache)
        ("intermediateCacheSize", c_size_t),                            ## [out] Per-cache Intermediate Cache (L1/L2) size, in bytes
        ("lastLevelCacheSizeControlSupported", ze_bool_t),              ## [out] Support User control on Last Level Cache (i.e. Resize SLM
                                                                        ## section vs Generic Cache).
        ("lastLevelCacheSize", c_size_t)                                ## [out] Per-cache Last Level Cache (L3) size, in bytes
    ]

###############################################################################
## @brief API version of ::ze_device_image_properties_t
class ze_device_image_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_device_image_properties_version_t(c_int):
    def __str__(self):
        return str(ze_device_image_properties_version_v(value))


###############################################################################
## @brief Device image properties queried using ::zeDeviceGetComputeProperties
class ze_device_image_properties_t(Structure):
    _fields_ = [
        ("version", ze_device_image_properties_version_t),              ## [in] ::ZE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT
        ("supported", ze_bool_t),                                       ## [out] Supports reading and writing of images. See
                                                                        ## ::::zeImageGetProperties for format-specific capabilities.
        ("maxImageDims1D", c_ulong),                                    ## [out] Maximum image dimensions for 1D resources.
        ("maxImageDims2D", c_ulong),                                    ## [out] Maximum image dimensions for 2D resources.
        ("maxImageDims3D", c_ulong),                                    ## [out] Maximum image dimensions for 3D resources.
        ("maxImageArraySlices", c_ulong)                                ## [out] Maximum image array slices
    ]

###############################################################################
## @brief API version of ::ze_device_p2p_properties_t
class ze_device_p2p_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_device_p2p_properties_version_t(c_int):
    def __str__(self):
        return str(ze_device_p2p_properties_version_v(value))


###############################################################################
## @brief Device properties queried using ::zeDeviceGetP2PProperties
class ze_device_p2p_properties_t(Structure):
    _fields_ = [
        ("version", ze_device_p2p_properties_version_t),                ## [in] ::ZE_DEVICE_P2P_PROPERTIES_VERSION_CURRENT
        ("accessSupported", ze_bool_t),                                 ## [out] Supports access between peer devices.
        ("atomicsSupported", ze_bool_t)                                 ## [out] Supports atomics between peer devices.
    ]

###############################################################################
## @brief Supported Cache Config
## 
## @details
##     - Supported Cache Config (Default, Large SLM, Large Data Cache)
class ze_cache_config_v(IntEnum):
    DEFAULT = ZE_BIT( 0 )                           ## Default Config
    LARGE_SLM = ZE_BIT( 1 )                         ## Large SLM size
    LARGE_DATA = ZE_BIT( 2 )                        ## Large General Data size

class ze_cache_config_t(c_int):
    def __str__(self):
        return str(ze_cache_config_v(value))


###############################################################################
## @brief API version of ::ze_command_queue_desc_t
class ze_command_queue_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_command_queue_desc_version_t(c_int):
    def __str__(self):
        return str(ze_command_queue_desc_version_v(value))


###############################################################################
## @brief Supported command queue flags
class ze_command_queue_flag_v(IntEnum):
    NONE = 0                                        ## default behavior
    COPY_ONLY = ZE_BIT(0)                           ## command queue only supports enqueing copy-only command lists
    LOGICAL_ONLY = ZE_BIT(1)                        ## command queue is not tied to a physical command queue; driver may
                                                    ## dynamically assign based on usage
    SINGLE_SLICE_ONLY = ZE_BIT(2)                   ## command queue reserves and cannot comsume more than a single slice.
                                                    ## 'slice' size is device-specific.  cannot be combined with COPY_ONLY.
    SUPPORTS_COOPERATIVE_KERNELS = ZE_BIT(3)        ## command queue supports command list with cooperative kernels. See
                                                    ## ::zeCommandListAppendLaunchCooperativeKernel for more details. cannot
                                                    ## be combined with COPY_ONLY.

class ze_command_queue_flag_t(c_int):
    def __str__(self):
        return str(ze_command_queue_flag_v(value))


###############################################################################
## @brief Supported command queue modes
class ze_command_queue_mode_v(IntEnum):
    DEFAULT = 0                                     ## implicit default behavior; uses driver-based heuristics
    SYNCHRONOUS = auto()                            ## Device execution always completes immediately on execute;
                                                    ## Host thread is blocked using wait on implicit synchronization object
    ASYNCHRONOUS = auto()                           ## Device execution is scheduled and will complete in future;
                                                    ## explicit synchronization object must be used to determine completeness

class ze_command_queue_mode_t(c_int):
    def __str__(self):
        return str(ze_command_queue_mode_v(value))


###############################################################################
## @brief Supported command queue priorities
class ze_command_queue_priority_v(IntEnum):
    NORMAL = 0                                      ## [default] normal priority
    LOW = auto()                                    ## lower priority than normal
    HIGH = auto()                                   ## higher priority than normal

class ze_command_queue_priority_t(c_int):
    def __str__(self):
        return str(ze_command_queue_priority_v(value))


###############################################################################
## @brief Command Queue descriptor
class ze_command_queue_desc_t(Structure):
    _fields_ = [
        ("version", ze_command_queue_desc_version_t),                   ## [in] ::ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT
        ("flags", ze_command_queue_flag_t),                             ## [in] creation flags
        ("mode", ze_command_queue_mode_t),                              ## [in] operation mode
        ("priority", ze_command_queue_priority_t),                      ## [in] priority
        ("ordinal", c_ulong)                                            ## [in] if logical-only flag is set, then will be ignored;
                                                                        ## if supports-cooperative-kernels is set, then may be ignored;
                                                                        ## else-if copy-only flag is set, then must be less than ::ze_device_properties_t.numAsyncCopyEngines;
                                                                        ## otherwise must be less than
                                                                        ## ::ze_device_properties_t.numAsyncComputeEngines. When using sub-devices
                                                                        ## the ::ze_device_properties_t.numAsyncComputeEngines must be queried
                                                                        ## from the sub-device being used.
    ]

###############################################################################
## @brief API version of ::ze_command_list_desc_t
class ze_command_list_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_command_list_desc_version_t(c_int):
    def __str__(self):
        return str(ze_command_list_desc_version_v(value))


###############################################################################
## @brief Supported command list creation flags
class ze_command_list_flag_v(IntEnum):
    NONE = 0                                        ## default behavior
    COPY_ONLY = ZE_BIT(0)                           ## command list **only** contains copy operations (and synchronization primitives).
                                                    ## this command list may **only** be submitted to a command queue created
                                                    ## with ::ZE_COMMAND_QUEUE_FLAG_COPY_ONLY.
    RELAXED_ORDERING = ZE_BIT(1)                    ## driver may reorder programs and copys between barriers and
                                                    ## synchronization primitives.
                                                    ## using this flag may increase Host overhead of ::zeCommandListClose.
                                                    ## therefore, this flag should **not** be set for low-latency usage-models.
    MAXIMIZE_THROUGHPUT = ZE_BIT(2)                 ## driver may perform additional optimizations that increase dexecution
                                                    ## throughput. 
                                                    ## using this flag may increase Host overhead of ::zeCommandListClose and ::zeCommandQueueExecuteCommandLists.
                                                    ## therefore, this flag should **not** be set for low-latency usage-models.
    EXPLICIT_ONLY = ZE_BIT(3)                       ## command list should be optimized for submission to a single command
                                                    ## queue and device engine.
                                                    ## driver **must** disable any implicit optimizations for distributing
                                                    ## work across multiple engines.
                                                    ## this flag should be used when applications want full control over
                                                    ## multi-engine submission and scheduling.

class ze_command_list_flag_t(c_int):
    def __str__(self):
        return str(ze_command_list_flag_v(value))


###############################################################################
## @brief Command List descriptor
class ze_command_list_desc_t(Structure):
    _fields_ = [
        ("version", ze_command_list_desc_version_t),                    ## [in] ::ZE_COMMAND_LIST_DESC_VERSION_CURRENT
        ("flags", ze_command_list_flag_t)                               ## [in] creation flags
    ]

###############################################################################
## @brief Copy region descriptor
class ze_copy_region_t(Structure):
    _fields_ = [
        ("originX", c_ulong),                                           ## [in] The origin x offset for region in bytes
        ("originY", c_ulong),                                           ## [in] The origin y offset for region in rows
        ("width", c_ulong),                                             ## [in] The region width relative to origin in bytes
        ("height", c_ulong)                                             ## [in] The region height relative to origin in rows
    ]

###############################################################################
## @brief Region descriptor
class ze_image_region_t(Structure):
    _fields_ = [
        ("originX", c_ulong),                                           ## [in] The origin x offset for region in pixels
        ("originY", c_ulong),                                           ## [in] The origin y offset for region in pixels
        ("originZ", c_ulong),                                           ## [in] The origin z offset for region in pixels
        ("width", c_ulong),                                             ## [in] The region width relative to origin in pixels
        ("height", c_ulong),                                            ## [in] The region height relative to origin in pixels
        ("depth", c_ulong)                                              ## [in] The region depth relative to origin. For 1D or 2D images, set
                                                                        ## this to 1.
    ]

###############################################################################
## @brief Supported memory advice hints
class ze_memory_advice_v(IntEnum):
    SET_READ_MOSTLY = 0                             ## hint that memory will be read from frequently and written to rarely
    CLEAR_READ_MOSTLY = auto()                      ## removes the affect of ::ZE_MEMORY_ADVICE_SET_READ_MOSTLY
    SET_PREFERRED_LOCATION = auto()                 ## hint that the preferred memory location is the specified device
    CLEAR_PREFERRED_LOCATION = auto()               ## removes the affect of ::ZE_MEMORY_ADVICE_SET_PREFERRED_LOCATION
    SET_ACCESSED_BY = auto()                        ## hint that memory will be accessed by the specified device
    CLEAR_ACCESSED_BY = auto()                      ## removes the affect of ::ZE_MEMORY_ADVICE_SET_ACCESSED_BY
    SET_NON_ATOMIC_MOSTLY = auto()                  ## hints that memory will mostly be accessed non-atomically
    CLEAR_NON_ATOMIC_MOSTLY = auto()                ## removes the affect of ::ZE_MEMORY_ADVICE_SET_NON_ATOMIC_MOSTLY
    BIAS_CACHED = auto()                            ## hints that memory should be cached
    BIAS_UNCACHED = auto()                          ## hints that memory should be not be cached

class ze_memory_advice_t(c_int):
    def __str__(self):
        return str(ze_memory_advice_v(value))


###############################################################################
## @brief API version of ::ze_event_pool_desc_t
class ze_event_pool_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_event_pool_desc_version_t(c_int):
    def __str__(self):
        return str(ze_event_pool_desc_version_v(value))


###############################################################################
## @brief Supported event pool creation flags
class ze_event_pool_flag_v(IntEnum):
    DEFAULT = 0                                     ## signals and waits visible to the entire device and peer devices
    HOST_VISIBLE = ZE_BIT(0)                        ## signals and waits are also visible to host
    IPC = ZE_BIT(1)                                 ## signals and waits may be shared across processes

class ze_event_pool_flag_t(c_int):
    def __str__(self):
        return str(ze_event_pool_flag_v(value))


###############################################################################
## @brief Event pool descriptor
class ze_event_pool_desc_t(Structure):
    _fields_ = [
        ("version", ze_event_pool_desc_version_t),                      ## [in] ::ZE_EVENT_POOL_DESC_VERSION_CURRENT
        ("flags", ze_event_pool_flag_t),                                ## [in] creation flags
        ("count", c_ulong)                                              ## [in] number of events within the pool
    ]

###############################################################################
## @brief API version of ::ze_event_desc_t
class ze_event_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_event_desc_version_t(c_int):
    def __str__(self):
        return str(ze_event_desc_version_v(value))


###############################################################################
## @brief Supported event scope flags
class ze_event_scope_flag_v(IntEnum):
    NONE = 0                                        ## execution synchronization only; no cache hierarchies are flushed or
                                                    ## invalidated
    SUBDEVICE = ZE_BIT(0)                           ## cache hierarchies are flushed or invalidated sufficient for local
                                                    ## sub-device access
    DEVICE = ZE_BIT(1)                              ## cache hierarchies are flushed or invalidated sufficient for global
                                                    ## device access and peer device access
    HOST = ZE_BIT(2)                                ## cache hierarchies are flushed or invalidated sufficient for device and
                                                    ## host access

class ze_event_scope_flag_t(c_int):
    def __str__(self):
        return str(ze_event_scope_flag_v(value))


###############################################################################
## @brief Event descriptor
class ze_event_desc_t(Structure):
    _fields_ = [
        ("version", ze_event_desc_version_t),                           ## [in] ::ZE_EVENT_DESC_VERSION_CURRENT
        ("index", c_ulong),                                             ## [in] index of the event within the pool; must be less-than the count
                                                                        ## specified during pool creation
        ("signal", ze_event_scope_flag_t),                              ## [in] defines the scope of relevant cache hierarchies to flush on a
                                                                        ## signal action before the event is triggered
        ("wait", ze_event_scope_flag_t)                                 ## [in] defines the scope of relevant cache hierarchies to invalidate on
                                                                        ## a wait action after the event is complete
    ]

###############################################################################
## @brief API version of ::ze_fence_desc_t
class ze_fence_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_fence_desc_version_t(c_int):
    def __str__(self):
        return str(ze_fence_desc_version_v(value))


###############################################################################
## @brief Supported fence creation flags
class ze_fence_flag_v(IntEnum):
    NONE = 0                                        ## default behavior

class ze_fence_flag_t(c_int):
    def __str__(self):
        return str(ze_fence_flag_v(value))


###############################################################################
## @brief Fence descriptor
class ze_fence_desc_t(Structure):
    _fields_ = [
        ("version", ze_fence_desc_version_t),                           ## [in] ::ZE_FENCE_DESC_VERSION_CURRENT
        ("flags", ze_fence_flag_t)                                      ## [in] creation flags
    ]

###############################################################################
## @brief API version of ::ze_image_desc_t
class ze_image_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_image_desc_version_t(c_int):
    def __str__(self):
        return str(ze_image_desc_version_v(value))


###############################################################################
## @brief Supported image creation flags
class ze_image_flag_v(IntEnum):
    PROGRAM_READ = ZE_BIT( 0 )                      ## programs will read contents
    PROGRAM_WRITE = ZE_BIT( 1 )                     ## programs will write contents
    BIAS_CACHED = ZE_BIT( 2 )                       ## device should cache contents
    BIAS_UNCACHED = ZE_BIT( 3 )                     ## device should not cache contents

class ze_image_flag_t(c_int):
    def __str__(self):
        return str(ze_image_flag_v(value))


###############################################################################
## @brief Supported image types
class ze_image_type_v(IntEnum):
    _1D = auto()                                    ## 1D
    _1DARRAY = auto()                               ## 1D array
    _2D = auto()                                    ## 2D
    _2DARRAY = auto()                               ## 2D array
    _3D = auto()                                    ## 3D

class ze_image_type_t(c_int):
    def __str__(self):
        return str(ze_image_type_v(value))


###############################################################################
## @brief Supported image format layouts
class ze_image_format_layout_v(IntEnum):
    _8 = auto()                                     ## 8-bit single component layout
    _16 = auto()                                    ## 16-bit single component layout
    _32 = auto()                                    ## 32-bit single component layout
    _8_8 = auto()                                   ## 2-component 8-bit layout
    _8_8_8_8 = auto()                               ## 4-component 8-bit layout
    _16_16 = auto()                                 ## 2-component 16-bit layout
    _16_16_16_16 = auto()                           ## 4-component 16-bit layout
    _32_32 = auto()                                 ## 2-component 32-bit layout
    _32_32_32_32 = auto()                           ## 4-component 32-bit layout
    _10_10_10_2 = auto()                            ## 4-component 10_10_10_2 layout
    _11_11_10 = auto()                              ## 3-component 11_11_10 layout
    _5_6_5 = auto()                                 ## 3-component 5_6_5 layout
    _5_5_5_1 = auto()                               ## 4-component 5_5_5_1 layout
    _4_4_4_4 = auto()                               ## 4-component 4_4_4_4 layout
    Y8 = auto()                                     ## Media Format: Y8. Format type and swizzle is ignored for this.
    NV12 = auto()                                   ## Media Format: NV12. Format type and swizzle is ignored for this.
    YUYV = auto()                                   ## Media Format: YUYV. Format type and swizzle is ignored for this.
    VYUY = auto()                                   ## Media Format: VYUY. Format type and swizzle is ignored for this.
    YVYU = auto()                                   ## Media Format: YVYU. Format type and swizzle is ignored for this.
    UYVY = auto()                                   ## Media Format: UYVY. Format type and swizzle is ignored for this.
    AYUV = auto()                                   ## Media Format: AYUV. Format type and swizzle is ignored for this.
    YUAV = auto()                                   ## Media Format: YUAV. Format type and swizzle is ignored for this.
    P010 = auto()                                   ## Media Format: P010. Format type and swizzle is ignored for this.
    Y410 = auto()                                   ## Media Format: Y410. Format type and swizzle is ignored for this.
    P012 = auto()                                   ## Media Format: P012. Format type and swizzle is ignored for this.
    Y16 = auto()                                    ## Media Format: Y16. Format type and swizzle is ignored for this.
    P016 = auto()                                   ## Media Format: P016. Format type and swizzle is ignored for this.
    Y216 = auto()                                   ## Media Format: Y216. Format type and swizzle is ignored for this.
    P216 = auto()                                   ## Media Format: P216. Format type and swizzle is ignored for this.
    P416 = auto()                                   ## Media Format: P416. Format type and swizzle is ignored for this.

class ze_image_format_layout_t(c_int):
    def __str__(self):
        return str(ze_image_format_layout_v(value))


###############################################################################
## @brief Supported image format types
class ze_image_format_type_v(IntEnum):
    UINT = auto()                                   ## Unsigned integer
    SINT = auto()                                   ## Signed integer
    UNORM = auto()                                  ## Unsigned normalized integer
    SNORM = auto()                                  ## Signed normalized integer
    FLOAT = auto()                                  ## Float

class ze_image_format_type_t(c_int):
    def __str__(self):
        return str(ze_image_format_type_v(value))


###############################################################################
## @brief Supported image format component swizzle into channel
class ze_image_format_swizzle_v(IntEnum):
    R = auto()                                      ## Red component
    G = auto()                                      ## Green component
    B = auto()                                      ## Blue component
    A = auto()                                      ## Alpha component
    _0 = auto()                                     ## Zero
    _1 = auto()                                     ## One
    X = auto()                                      ## Don't care

class ze_image_format_swizzle_t(c_int):
    def __str__(self):
        return str(ze_image_format_swizzle_v(value))


###############################################################################
## @brief Image format descriptor
class ze_image_format_desc_t(Structure):
    _fields_ = [
        ("layout", ze_image_format_layout_t),                           ## [in] image format component layout
        ("type", ze_image_format_type_t),                               ## [in] image format type
        ("x", ze_image_format_swizzle_t),                               ## [in] image component swizzle into channel x
        ("y", ze_image_format_swizzle_t),                               ## [in] image component swizzle into channel y
        ("z", ze_image_format_swizzle_t),                               ## [in] image component swizzle into channel z
        ("w", ze_image_format_swizzle_t)                                ## [in] image component swizzle into channel w
    ]

###############################################################################
## @brief Image descriptor
class ze_image_desc_t(Structure):
    _fields_ = [
        ("version", ze_image_desc_version_t),                           ## [in] ::ZE_IMAGE_DESC_VERSION_CURRENT
        ("flags", ze_image_flag_t),                                     ## [in] creation flags
        ("type", ze_image_type_t),                                      ## [in] image type
        ("format", ze_image_format_desc_t),                             ## [in] image format
        ("width", c_ulong),                                             ## [in] width in pixels, see
                                                                        ## ::ze_device_image_properties_t::maxImageDims1D/2D/3D
        ("height", c_ulong),                                            ## [in] height in pixels (2D or 3D only), see
                                                                        ## ::ze_device_image_properties_t::maxImageDims2D/3D
        ("depth", c_ulong),                                             ## [in] depth in pixels (3D only), see
                                                                        ## ::ze_device_image_properties_t::maxImageDims3D
        ("arraylevels", c_ulong),                                       ## [in] array levels (array types only), see
                                                                        ## ::ze_device_image_properties_t::maxImageArraySlices
        ("miplevels", c_ulong)                                          ## [in] mipmap levels (must be 0)
    ]

###############################################################################
## @brief API version of ::ze_image_properties_t
class ze_image_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_image_properties_version_t(c_int):
    def __str__(self):
        return str(ze_image_properties_version_v(value))


###############################################################################
## @brief Supported sampler filtering flags
class ze_image_sampler_filter_flags_v(IntEnum):
    NONE = 0                                        ## device does not support filtering
    POINT = ZE_BIT(0)                               ## device supports point filtering
    LINEAR = ZE_BIT(1)                              ## device supports linear filtering

class ze_image_sampler_filter_flags_t(c_int):
    def __str__(self):
        return str(ze_image_sampler_filter_flags_v(value))


###############################################################################
## @brief Image properties
class ze_image_properties_t(Structure):
    _fields_ = [
        ("version", ze_image_properties_version_t),                     ## [in] ::ZE_IMAGE_PROPERTIES_VERSION_CURRENT
        ("samplerFilterFlags", ze_image_sampler_filter_flags_t)         ## [out] supported sampler filtering
    ]

###############################################################################
## @brief Supported memory allocation flags
class ze_device_mem_alloc_flag_v(IntEnum):
    DEFAULT = 0                                     ## implicit default behavior; uses driver-based heuristics
    BIAS_CACHED = ZE_BIT( 0 )                       ## device should cache allocation
    BIAS_UNCACHED = ZE_BIT( 1 )                     ## device should not cache allocation (UC)

class ze_device_mem_alloc_flag_t(c_int):
    def __str__(self):
        return str(ze_device_mem_alloc_flag_v(value))


###############################################################################
## @brief Supported host memory allocation flags
class ze_host_mem_alloc_flag_v(IntEnum):
    DEFAULT = 0                                     ## implicit default behavior; uses driver-based heuristics
    BIAS_CACHED = ZE_BIT( 0 )                       ## host should cache allocation
    BIAS_UNCACHED = ZE_BIT( 1 )                     ## host should not cache allocation (UC)
    BIAS_WRITE_COMBINED = ZE_BIT( 2 )               ## host memory should be allocated write-combined (WC)

class ze_host_mem_alloc_flag_t(c_int):
    def __str__(self):
        return str(ze_host_mem_alloc_flag_v(value))


###############################################################################
## @brief API version of ::ze_memory_allocation_properties_t
class ze_memory_allocation_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_memory_allocation_properties_version_t(c_int):
    def __str__(self):
        return str(ze_memory_allocation_properties_version_v(value))


###############################################################################
## @brief Memory allocation type
class ze_memory_type_v(IntEnum):
    UNKNOWN = 0                                     ## the memory pointed to is of unknown type
    HOST = auto()                                   ## the memory pointed to is a host allocation
    DEVICE = auto()                                 ## the memory pointed to is a device allocation
    SHARED = auto()                                 ## the memory pointed to is a shared ownership allocation

class ze_memory_type_t(c_int):
    def __str__(self):
        return str(ze_memory_type_v(value))


###############################################################################
## @brief Memory allocation properties queried using
##        ::zeDriverGetMemAllocProperties
class ze_memory_allocation_properties_t(Structure):
    _fields_ = [
        ("version", ze_memory_allocation_properties_version_t),         ## [in] ::ZE_MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT
        ("type", ze_memory_type_t),                                     ## [out] type of allocated memory
        ("id", c_ulonglong)                                             ## [out] identifier for this allocation
    ]

###############################################################################
## @brief Supported IPC memory flags
class ze_ipc_memory_flag_v(IntEnum):
    NONE = 0                                        ## No special flags

class ze_ipc_memory_flag_t(c_int):
    def __str__(self):
        return str(ze_ipc_memory_flag_v(value))


###############################################################################
## @brief API version of ::ze_module_desc_t
class ze_module_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_module_desc_version_t(c_int):
    def __str__(self):
        return str(ze_module_desc_version_v(value))


###############################################################################
## @brief Supported module creation input formats
class ze_module_format_v(IntEnum):
    IL_SPIRV = 0                                    ## Format is SPIRV IL format
    NATIVE = auto()                                 ## Format is device native format

class ze_module_format_t(c_int):
    def __str__(self):
        return str(ze_module_format_v(value))


###############################################################################
## @brief Specialization constants - User defined constants
class ze_module_constants_t(Structure):
    _fields_ = [
        ("numConstants", c_ulong),                                      ## [in] Number of specialization constants.
        ("pConstantIds", POINTER(c_ulong)),                             ## [in] Pointer to array of IDs that is sized to numConstants.
        ("pConstantValues", POINTER(c_ulonglong))                       ## [in] Pointer to array of values that is sized to numConstants.
    ]

###############################################################################
## @brief Module descriptor
class ze_module_desc_t(Structure):
    _fields_ = [
        ("version", ze_module_desc_version_t),                          ## [in] ::ZE_MODULE_DESC_VERSION_CURRENT
        ("format", ze_module_format_t),                                 ## [in] Module format passed in with pInputModule
        ("inputSize", c_size_t),                                        ## [in] size of input IL or ISA from pInputModule.
        ("pInputModule", POINTER(c_ubyte)),                             ## [in] pointer to IL or ISA
        ("pBuildFlags", POINTER(c_char)),                               ## [in] string containing compiler flags. See programming guide for build
                                                                        ## flags.
        ("pConstants", POINTER(ze_module_constants_t))                  ## [in] pointer to specialization constants. Valid only for SPIR-V input.
    ]

###############################################################################
## @brief API version of ::ze_kernel_desc_t
class ze_kernel_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_kernel_desc_version_t(c_int):
    def __str__(self):
        return str(ze_kernel_desc_version_v(value))


###############################################################################
## @brief Supported kernel creation flags
class ze_kernel_flag_v(IntEnum):
    NONE = 0                                        ## default driver behavior
    FORCE_RESIDENCY = auto()                        ## force all device allocations to be resident during execution

class ze_kernel_flag_t(c_int):
    def __str__(self):
        return str(ze_kernel_flag_v(value))


###############################################################################
## @brief Kernel descriptor
class ze_kernel_desc_t(Structure):
    _fields_ = [
        ("version", ze_kernel_desc_version_t),                          ## [in] ::ZE_KERNEL_DESC_VERSION_CURRENT
        ("flags", ze_kernel_flag_t),                                    ## [in] creation flags
        ("pKernelName", POINTER(c_char))                                ## [in] null-terminated name of kernel in module
    ]

###############################################################################
## @brief Kernel attributes
## 
## @remarks
##   _Analogues_
##     - **cl_kernel_exec_info**
class ze_kernel_set_attribute_v(IntEnum):
    KERNEL_SET_ATTR_INDIRECT_HOST_ACCESS = 0        ## Indicates that the function accesses host allocations indirectly
                                                    ## (default: false)
    KERNEL_SET_ATTR_INDIRECT_DEVICE_ACCESS = auto() ## Indicates that the function accesses device allocations indirectly
                                                    ## (default: false)
    KERNEL_SET_ATTR_INDIRECT_SHARED_ACCESS = auto() ## Indicates that the function accesses shared allocations indirectly
                                                    ## (default: false)

class ze_kernel_set_attribute_t(c_int):
    def __str__(self):
        return str(ze_kernel_set_attribute_v(value))


###############################################################################
## @brief Kernel attributes
## 
## @remarks
##   _Analogues_
##     - **CUfunction_attribute**
class ze_kernel_get_attribute_v(IntEnum):
    KERNEL_GET_ATTR_MAX_REGS_USED = 0               ## Maximum device registers used for this kernel
    KERNEL_GET_ATTR_NUM_THREAD_DIMENSIONS = auto()  ## Maximum dimensions for group for this kernel
    KERNEL_GET_ATTR_MAX_SHARED_MEM_SIZE = auto()    ## Maximum shared memory required for this kernel
    KERNEL_GET_ATTR_HAS_SPILL_FILL = auto()         ## Kernel required spill/fills
    KERNEL_GET_ATTR_HAS_BARRIERS = auto()           ## Kernel contains barriers
    KERNEL_GET_ATTR_HAS_DPAS = auto()               ## Kernel contains DPAS

class ze_kernel_get_attribute_t(c_int):
    def __str__(self):
        return str(ze_kernel_get_attribute_v(value))


###############################################################################
## @brief Kernel thread group dimensions.
class ze_thread_group_dimensions_t(Structure):
    _fields_ = [
        ("groupCountX", c_ulong),                                       ## [in] size of thread group in X dimension
        ("groupCountY", c_ulong),                                       ## [in] size of thread group in Y dimension
        ("groupCountZ", c_ulong)                                        ## [in] size of thread group in Z dimension
    ]

###############################################################################
## @brief type definition for host function pointers used with
##        ::zeCommandListAppendLaunchHostFunction
## 
## @details
##     - The application may call this function from simultaneous threads.
##     - The implementation of this function should be lock-free.
class ze_host_pfn_t(c_void_p):
    pass

###############################################################################
## @brief API version of ::ze_sampler_desc_t
class ze_sampler_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class ze_sampler_desc_version_t(c_int):
    def __str__(self):
        return str(ze_sampler_desc_version_v(value))


###############################################################################
## @brief Sampler addressing modes
class ze_sampler_address_mode_v(IntEnum):
    NONE = 0                                        ## No coordinate modifications for out-of-bounds image access.
    REPEAT = auto()                                 ## Out-of-bounds coordinates are wrapped back around.
    CLAMP = auto()                                  ## Out-of-bounds coordinates are clamped to edge.
    MIRROR = auto()                                 ## Out-of-bounds coordinates are mirrored starting from edge.

class ze_sampler_address_mode_t(c_int):
    def __str__(self):
        return str(ze_sampler_address_mode_v(value))


###############################################################################
## @brief Sampler filtering modes
class ze_sampler_filter_mode_v(IntEnum):
    NEAREST = 0                                     ## No coordinate modifications for out of bounds image access.
    LINEAR = auto()                                 ## Out-of-bounds coordinates are wrapped back around.

class ze_sampler_filter_mode_t(c_int):
    def __str__(self):
        return str(ze_sampler_filter_mode_v(value))


###############################################################################
## @brief Sampler descriptor
class ze_sampler_desc_t(Structure):
    _fields_ = [
        ("version", ze_sampler_desc_version_t),                         ## [in] ::ZE_SAMPLER_DESC_VERSION_CURRENT
        ("addressMode", ze_sampler_address_mode_t),                     ## [in] Sampler addressing mode to determine how out-of-bounds
                                                                        ## coordinates are handled.
        ("filterMode", ze_sampler_filter_mode_t),                       ## [in] Sampler filter mode to determine how samples are filtered.
        ("isNormalized", ze_bool_t)                                     ## [in] Are coordinates normalized [0, 1] or not.
    ]

###############################################################################
"""
class cl_context(c_void_p):
    pass

class cl_program(c_void_p):
    pass

class cl_mem(c_void_p):
    pass

class cl_command_queue(c_void_p):
    pass
"""

###############################################################################
__use_win_types = "Windows" == platform.uname()[0]

###############################################################################
## @brief Function-pointer for zeInit
if __use_win_types:
    _zeInit_t = WINFUNCTYPE( ze_result_t, ze_init_flag_t )
else:
    _zeInit_t = CFUNCTYPE( ze_result_t, ze_init_flag_t )


###############################################################################
## @brief Table of Global functions pointers
class _ze_global_dditable_t(Structure):
    _fields_ = [
        ("pfnInit", c_void_p)                                           ## _zeInit_t
    ]

###############################################################################
## @brief Function-pointer for zeDeviceGet
if __use_win_types:
    _zeDeviceGet_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, POINTER(c_ulong), POINTER(ze_device_handle_t) )
else:
    _zeDeviceGet_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, POINTER(c_ulong), POINTER(ze_device_handle_t) )

###############################################################################
## @brief Function-pointer for zeDeviceGetSubDevices
if __use_win_types:
    _zeDeviceGetSubDevices_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(c_ulong), POINTER(ze_device_handle_t) )
else:
    _zeDeviceGetSubDevices_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(c_ulong), POINTER(ze_device_handle_t) )

###############################################################################
## @brief Function-pointer for zeDeviceGetProperties
if __use_win_types:
    _zeDeviceGetProperties_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_device_properties_t) )
else:
    _zeDeviceGetProperties_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_device_properties_t) )

###############################################################################
## @brief Function-pointer for zeDeviceGetComputeProperties
if __use_win_types:
    _zeDeviceGetComputeProperties_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_device_compute_properties_t) )
else:
    _zeDeviceGetComputeProperties_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_device_compute_properties_t) )

###############################################################################
## @brief Function-pointer for zeDeviceGetMemoryProperties
if __use_win_types:
    _zeDeviceGetMemoryProperties_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(c_ulong), POINTER(ze_device_memory_properties_t) )
else:
    _zeDeviceGetMemoryProperties_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(c_ulong), POINTER(ze_device_memory_properties_t) )

###############################################################################
## @brief Function-pointer for zeDeviceGetMemoryAccessProperties
if __use_win_types:
    _zeDeviceGetMemoryAccessProperties_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_device_memory_access_properties_t) )
else:
    _zeDeviceGetMemoryAccessProperties_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_device_memory_access_properties_t) )

###############################################################################
## @brief Function-pointer for zeDeviceGetCacheProperties
if __use_win_types:
    _zeDeviceGetCacheProperties_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_device_cache_properties_t) )
else:
    _zeDeviceGetCacheProperties_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_device_cache_properties_t) )

###############################################################################
## @brief Function-pointer for zeDeviceGetImageProperties
if __use_win_types:
    _zeDeviceGetImageProperties_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_device_image_properties_t) )
else:
    _zeDeviceGetImageProperties_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_device_image_properties_t) )

###############################################################################
## @brief Function-pointer for zeDeviceGetP2PProperties
if __use_win_types:
    _zeDeviceGetP2PProperties_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, ze_device_handle_t, POINTER(ze_device_p2p_properties_t) )
else:
    _zeDeviceGetP2PProperties_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, ze_device_handle_t, POINTER(ze_device_p2p_properties_t) )

###############################################################################
## @brief Function-pointer for zeDeviceCanAccessPeer
if __use_win_types:
    _zeDeviceCanAccessPeer_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, ze_device_handle_t, POINTER(ze_bool_t) )
else:
    _zeDeviceCanAccessPeer_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, ze_device_handle_t, POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zeDeviceSetLastLevelCacheConfig
if __use_win_types:
    _zeDeviceSetLastLevelCacheConfig_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, ze_cache_config_t )
else:
    _zeDeviceSetLastLevelCacheConfig_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, ze_cache_config_t )

###############################################################################
## @brief Function-pointer for zeDeviceSystemBarrier
if __use_win_types:
    _zeDeviceSystemBarrier_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t )
else:
    _zeDeviceSystemBarrier_t = CFUNCTYPE( ze_result_t, ze_device_handle_t )

###############################################################################
## @brief Function-pointer for zeDeviceRegisterCLMemory

###############################################################################
## @brief Function-pointer for zeDeviceRegisterCLProgram

###############################################################################
## @brief Function-pointer for zeDeviceRegisterCLCommandQueue

###############################################################################
## @brief Function-pointer for zeDeviceMakeMemoryResident
if __use_win_types:
    _zeDeviceMakeMemoryResident_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, c_void_p, c_size_t )
else:
    _zeDeviceMakeMemoryResident_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, c_void_p, c_size_t )

###############################################################################
## @brief Function-pointer for zeDeviceEvictMemory
if __use_win_types:
    _zeDeviceEvictMemory_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, c_void_p, c_size_t )
else:
    _zeDeviceEvictMemory_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, c_void_p, c_size_t )

###############################################################################
## @brief Function-pointer for zeDeviceMakeImageResident
if __use_win_types:
    _zeDeviceMakeImageResident_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, ze_image_handle_t )
else:
    _zeDeviceMakeImageResident_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, ze_image_handle_t )

###############################################################################
## @brief Function-pointer for zeDeviceEvictImage
if __use_win_types:
    _zeDeviceEvictImage_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, ze_image_handle_t )
else:
    _zeDeviceEvictImage_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, ze_image_handle_t )


###############################################################################
## @brief Table of Device functions pointers
class _ze_device_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _zeDeviceGet_t
        ("pfnGetSubDevices", c_void_p),                                 ## _zeDeviceGetSubDevices_t
        ("pfnGetProperties", c_void_p),                                 ## _zeDeviceGetProperties_t
        ("pfnGetComputeProperties", c_void_p),                          ## _zeDeviceGetComputeProperties_t
        ("pfnGetMemoryProperties", c_void_p),                           ## _zeDeviceGetMemoryProperties_t
        ("pfnGetMemoryAccessProperties", c_void_p),                     ## _zeDeviceGetMemoryAccessProperties_t
        ("pfnGetCacheProperties", c_void_p),                            ## _zeDeviceGetCacheProperties_t
        ("pfnGetImageProperties", c_void_p),                            ## _zeDeviceGetImageProperties_t
        ("pfnGetP2PProperties", c_void_p),                              ## _zeDeviceGetP2PProperties_t
        ("pfnCanAccessPeer", c_void_p),                                 ## _zeDeviceCanAccessPeer_t
        ("pfnSetLastLevelCacheConfig", c_void_p),                       ## _zeDeviceSetLastLevelCacheConfig_t
        ("pfnSystemBarrier", c_void_p),                                 ## _zeDeviceSystemBarrier_t
        ("pfnMakeMemoryResident", c_void_p),                            ## _zeDeviceMakeMemoryResident_t
        ("pfnEvictMemory", c_void_p),                                   ## _zeDeviceEvictMemory_t
        ("pfnMakeImageResident", c_void_p),                             ## _zeDeviceMakeImageResident_t
        ("pfnEvictImage", c_void_p)                                     ## _zeDeviceEvictImage_t
    ]

###############################################################################
## @brief Function-pointer for zeDriverGet
if __use_win_types:
    _zeDriverGet_t = WINFUNCTYPE( ze_result_t, POINTER(c_ulong), POINTER(ze_driver_handle_t) )
else:
    _zeDriverGet_t = CFUNCTYPE( ze_result_t, POINTER(c_ulong), POINTER(ze_driver_handle_t) )

###############################################################################
## @brief Function-pointer for zeDriverGetDriverVersion
if __use_win_types:
    _zeDriverGetDriverVersion_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, POINTER(c_ulong) )
else:
    _zeDriverGetDriverVersion_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for zeDriverGetApiVersion
if __use_win_types:
    _zeDriverGetApiVersion_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, POINTER(ze_api_version_t) )
else:
    _zeDriverGetApiVersion_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, POINTER(ze_api_version_t) )

###############################################################################
## @brief Function-pointer for zeDriverGetIPCProperties
if __use_win_types:
    _zeDriverGetIPCProperties_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, POINTER(ze_driver_ipc_properties_t) )
else:
    _zeDriverGetIPCProperties_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, POINTER(ze_driver_ipc_properties_t) )

###############################################################################
## @brief Function-pointer for zeDriverAllocSharedMem
if __use_win_types:
    _zeDriverAllocSharedMem_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, ze_device_handle_t, ze_device_mem_alloc_flag_t, c_ulong, ze_host_mem_alloc_flag_t, c_size_t, c_size_t, POINTER(c_void_p) )
else:
    _zeDriverAllocSharedMem_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, ze_device_handle_t, ze_device_mem_alloc_flag_t, c_ulong, ze_host_mem_alloc_flag_t, c_size_t, c_size_t, POINTER(c_void_p) )

###############################################################################
## @brief Function-pointer for zeDriverAllocDeviceMem
if __use_win_types:
    _zeDriverAllocDeviceMem_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, ze_device_handle_t, ze_device_mem_alloc_flag_t, c_ulong, c_size_t, c_size_t, POINTER(c_void_p) )
else:
    _zeDriverAllocDeviceMem_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, ze_device_handle_t, ze_device_mem_alloc_flag_t, c_ulong, c_size_t, c_size_t, POINTER(c_void_p) )

###############################################################################
## @brief Function-pointer for zeDriverAllocHostMem
if __use_win_types:
    _zeDriverAllocHostMem_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, ze_host_mem_alloc_flag_t, c_size_t, c_size_t, POINTER(c_void_p) )
else:
    _zeDriverAllocHostMem_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, ze_host_mem_alloc_flag_t, c_size_t, c_size_t, POINTER(c_void_p) )

###############################################################################
## @brief Function-pointer for zeDriverFreeMem
if __use_win_types:
    _zeDriverFreeMem_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, c_void_p )
else:
    _zeDriverFreeMem_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, c_void_p )

###############################################################################
## @brief Function-pointer for zeDriverGetMemAllocProperties
if __use_win_types:
    _zeDriverGetMemAllocProperties_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, c_void_p, POINTER(ze_memory_allocation_properties_t), POINTER(ze_device_handle_t) )
else:
    _zeDriverGetMemAllocProperties_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, c_void_p, POINTER(ze_memory_allocation_properties_t), POINTER(ze_device_handle_t) )

###############################################################################
## @brief Function-pointer for zeDriverGetMemAddressRange
if __use_win_types:
    _zeDriverGetMemAddressRange_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, c_void_p, POINTER(c_void_p), POINTER(c_size_t) )
else:
    _zeDriverGetMemAddressRange_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, c_void_p, POINTER(c_void_p), POINTER(c_size_t) )

###############################################################################
## @brief Function-pointer for zeDriverGetMemIpcHandle
if __use_win_types:
    _zeDriverGetMemIpcHandle_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, c_void_p, POINTER(ze_ipc_mem_handle_t) )
else:
    _zeDriverGetMemIpcHandle_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, c_void_p, POINTER(ze_ipc_mem_handle_t) )

###############################################################################
## @brief Function-pointer for zeDriverOpenMemIpcHandle
if __use_win_types:
    _zeDriverOpenMemIpcHandle_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, ze_device_handle_t, ze_ipc_mem_handle_t, ze_ipc_memory_flag_t, POINTER(c_void_p) )
else:
    _zeDriverOpenMemIpcHandle_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, ze_device_handle_t, ze_ipc_mem_handle_t, ze_ipc_memory_flag_t, POINTER(c_void_p) )

###############################################################################
## @brief Function-pointer for zeDriverCloseMemIpcHandle
if __use_win_types:
    _zeDriverCloseMemIpcHandle_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, c_void_p )
else:
    _zeDriverCloseMemIpcHandle_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, c_void_p )


###############################################################################
## @brief Table of Driver functions pointers
class _ze_driver_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _zeDriverGet_t
        ("pfnGetDriverVersion", c_void_p),                              ## _zeDriverGetDriverVersion_t
        ("pfnGetApiVersion", c_void_p),                                 ## _zeDriverGetApiVersion_t
        ("pfnGetIPCProperties", c_void_p),                              ## _zeDriverGetIPCProperties_t
        ("pfnAllocSharedMem", c_void_p),                                ## _zeDriverAllocSharedMem_t
        ("pfnAllocDeviceMem", c_void_p),                                ## _zeDriverAllocDeviceMem_t
        ("pfnAllocHostMem", c_void_p),                                  ## _zeDriverAllocHostMem_t
        ("pfnFreeMem", c_void_p),                                       ## _zeDriverFreeMem_t
        ("pfnGetMemAllocProperties", c_void_p),                         ## _zeDriverGetMemAllocProperties_t
        ("pfnGetMemAddressRange", c_void_p),                            ## _zeDriverGetMemAddressRange_t
        ("pfnGetMemIpcHandle", c_void_p),                               ## _zeDriverGetMemIpcHandle_t
        ("pfnOpenMemIpcHandle", c_void_p),                              ## _zeDriverOpenMemIpcHandle_t
        ("pfnCloseMemIpcHandle", c_void_p)                              ## _zeDriverCloseMemIpcHandle_t
    ]

###############################################################################
## @brief Function-pointer for zeCommandQueueCreate
if __use_win_types:
    _zeCommandQueueCreate_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_command_queue_desc_t), POINTER(ze_command_queue_handle_t) )
else:
    _zeCommandQueueCreate_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_command_queue_desc_t), POINTER(ze_command_queue_handle_t) )

###############################################################################
## @brief Function-pointer for zeCommandQueueDestroy
if __use_win_types:
    _zeCommandQueueDestroy_t = WINFUNCTYPE( ze_result_t, ze_command_queue_handle_t )
else:
    _zeCommandQueueDestroy_t = CFUNCTYPE( ze_result_t, ze_command_queue_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandQueueExecuteCommandLists
if __use_win_types:
    _zeCommandQueueExecuteCommandLists_t = WINFUNCTYPE( ze_result_t, ze_command_queue_handle_t, c_ulong, POINTER(ze_command_list_handle_t), ze_fence_handle_t )
else:
    _zeCommandQueueExecuteCommandLists_t = CFUNCTYPE( ze_result_t, ze_command_queue_handle_t, c_ulong, POINTER(ze_command_list_handle_t), ze_fence_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandQueueSynchronize
if __use_win_types:
    _zeCommandQueueSynchronize_t = WINFUNCTYPE( ze_result_t, ze_command_queue_handle_t, c_ulong )
else:
    _zeCommandQueueSynchronize_t = CFUNCTYPE( ze_result_t, ze_command_queue_handle_t, c_ulong )


###############################################################################
## @brief Table of CommandQueue functions pointers
class _ze_command_queue_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zeCommandQueueCreate_t
        ("pfnDestroy", c_void_p),                                       ## _zeCommandQueueDestroy_t
        ("pfnExecuteCommandLists", c_void_p),                           ## _zeCommandQueueExecuteCommandLists_t
        ("pfnSynchronize", c_void_p)                                    ## _zeCommandQueueSynchronize_t
    ]

###############################################################################
## @brief Function-pointer for zeCommandListCreate
if __use_win_types:
    _zeCommandListCreate_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_command_list_desc_t), POINTER(ze_command_list_handle_t) )
else:
    _zeCommandListCreate_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_command_list_desc_t), POINTER(ze_command_list_handle_t) )

###############################################################################
## @brief Function-pointer for zeCommandListCreateImmediate
if __use_win_types:
    _zeCommandListCreateImmediate_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_command_queue_desc_t), POINTER(ze_command_list_handle_t) )
else:
    _zeCommandListCreateImmediate_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_command_queue_desc_t), POINTER(ze_command_list_handle_t) )

###############################################################################
## @brief Function-pointer for zeCommandListDestroy
if __use_win_types:
    _zeCommandListDestroy_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t )
else:
    _zeCommandListDestroy_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListClose
if __use_win_types:
    _zeCommandListClose_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t )
else:
    _zeCommandListClose_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListReset
if __use_win_types:
    _zeCommandListReset_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t )
else:
    _zeCommandListReset_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendBarrier
if __use_win_types:
    _zeCommandListAppendBarrier_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )
else:
    _zeCommandListAppendBarrier_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )

###############################################################################
## @brief Function-pointer for zeCommandListAppendMemoryRangesBarrier
if __use_win_types:
    _zeCommandListAppendMemoryRangesBarrier_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_ulong, POINTER(c_size_t), POINTER(c_void_p), ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )
else:
    _zeCommandListAppendMemoryRangesBarrier_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_ulong, POINTER(c_size_t), POINTER(c_void_p), ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )

###############################################################################
## @brief Function-pointer for zeCommandListAppendMemoryCopy
if __use_win_types:
    _zeCommandListAppendMemoryCopy_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_void_p, c_void_p, c_size_t, ze_event_handle_t )
else:
    _zeCommandListAppendMemoryCopy_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_void_p, c_void_p, c_size_t, ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendMemorySet
if __use_win_types:
    _zeCommandListAppendMemorySet_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_void_p, c_int, c_size_t, ze_event_handle_t )
else:
    _zeCommandListAppendMemorySet_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_void_p, c_int, c_size_t, ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendMemoryCopyRegion
if __use_win_types:
    _zeCommandListAppendMemoryCopyRegion_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_void_p, POINTER(ze_copy_region_t), c_ulong, c_void_p, POINTER(ze_copy_region_t), c_ulong, ze_event_handle_t )
else:
    _zeCommandListAppendMemoryCopyRegion_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_void_p, POINTER(ze_copy_region_t), c_ulong, c_void_p, POINTER(ze_copy_region_t), c_ulong, ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendImageCopy
if __use_win_types:
    _zeCommandListAppendImageCopy_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_image_handle_t, ze_image_handle_t, ze_event_handle_t )
else:
    _zeCommandListAppendImageCopy_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_image_handle_t, ze_image_handle_t, ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendImageCopyRegion
if __use_win_types:
    _zeCommandListAppendImageCopyRegion_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_image_handle_t, ze_image_handle_t, POINTER(ze_image_region_t), POINTER(ze_image_region_t), ze_event_handle_t )
else:
    _zeCommandListAppendImageCopyRegion_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_image_handle_t, ze_image_handle_t, POINTER(ze_image_region_t), POINTER(ze_image_region_t), ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendImageCopyToMemory
if __use_win_types:
    _zeCommandListAppendImageCopyToMemory_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_void_p, ze_image_handle_t, POINTER(ze_image_region_t), ze_event_handle_t )
else:
    _zeCommandListAppendImageCopyToMemory_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_void_p, ze_image_handle_t, POINTER(ze_image_region_t), ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendImageCopyFromMemory
if __use_win_types:
    _zeCommandListAppendImageCopyFromMemory_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_image_handle_t, c_void_p, POINTER(ze_image_region_t), ze_event_handle_t )
else:
    _zeCommandListAppendImageCopyFromMemory_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_image_handle_t, c_void_p, POINTER(ze_image_region_t), ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendMemoryPrefetch
if __use_win_types:
    _zeCommandListAppendMemoryPrefetch_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_void_p, c_size_t )
else:
    _zeCommandListAppendMemoryPrefetch_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_void_p, c_size_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendMemAdvise
if __use_win_types:
    _zeCommandListAppendMemAdvise_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_device_handle_t, c_void_p, c_size_t, ze_memory_advice_t )
else:
    _zeCommandListAppendMemAdvise_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_device_handle_t, c_void_p, c_size_t, ze_memory_advice_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendSignalEvent
if __use_win_types:
    _zeCommandListAppendSignalEvent_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_event_handle_t )
else:
    _zeCommandListAppendSignalEvent_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendWaitOnEvents
if __use_win_types:
    _zeCommandListAppendWaitOnEvents_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_ulong, POINTER(ze_event_handle_t) )
else:
    _zeCommandListAppendWaitOnEvents_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_ulong, POINTER(ze_event_handle_t) )

###############################################################################
## @brief Function-pointer for zeCommandListAppendEventReset
if __use_win_types:
    _zeCommandListAppendEventReset_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_event_handle_t )
else:
    _zeCommandListAppendEventReset_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeCommandListAppendLaunchKernel
if __use_win_types:
    _zeCommandListAppendLaunchKernel_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_kernel_handle_t, POINTER(ze_thread_group_dimensions_t), ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )
else:
    _zeCommandListAppendLaunchKernel_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_kernel_handle_t, POINTER(ze_thread_group_dimensions_t), ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )

###############################################################################
## @brief Function-pointer for zeCommandListAppendLaunchCooperativeKernel
if __use_win_types:
    _zeCommandListAppendLaunchCooperativeKernel_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_kernel_handle_t, POINTER(ze_thread_group_dimensions_t), ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )
else:
    _zeCommandListAppendLaunchCooperativeKernel_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_kernel_handle_t, POINTER(ze_thread_group_dimensions_t), ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )

###############################################################################
## @brief Function-pointer for zeCommandListAppendLaunchKernelIndirect
if __use_win_types:
    _zeCommandListAppendLaunchKernelIndirect_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_kernel_handle_t, POINTER(ze_thread_group_dimensions_t), ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )
else:
    _zeCommandListAppendLaunchKernelIndirect_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_kernel_handle_t, POINTER(ze_thread_group_dimensions_t), ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )

###############################################################################
## @brief Function-pointer for zeCommandListAppendLaunchMultipleKernelsIndirect
if __use_win_types:
    _zeCommandListAppendLaunchMultipleKernelsIndirect_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_ulong, POINTER(ze_kernel_handle_t), POINTER(c_ulong), POINTER(ze_thread_group_dimensions_t), ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )
else:
    _zeCommandListAppendLaunchMultipleKernelsIndirect_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, c_ulong, POINTER(ze_kernel_handle_t), POINTER(c_ulong), POINTER(ze_thread_group_dimensions_t), ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )

###############################################################################
## @brief Function-pointer for zeCommandListAppendLaunchHostFunction
if __use_win_types:
    _zeCommandListAppendLaunchHostFunction_t = WINFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_host_pfn_t, c_void_p, ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )
else:
    _zeCommandListAppendLaunchHostFunction_t = CFUNCTYPE( ze_result_t, ze_command_list_handle_t, ze_host_pfn_t, c_void_p, ze_event_handle_t, c_ulong, POINTER(ze_event_handle_t) )


###############################################################################
## @brief Table of CommandList functions pointers
class _ze_command_list_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zeCommandListCreate_t
        ("pfnCreateImmediate", c_void_p),                               ## _zeCommandListCreateImmediate_t
        ("pfnDestroy", c_void_p),                                       ## _zeCommandListDestroy_t
        ("pfnClose", c_void_p),                                         ## _zeCommandListClose_t
        ("pfnReset", c_void_p),                                         ## _zeCommandListReset_t
        ("pfnAppendBarrier", c_void_p),                                 ## _zeCommandListAppendBarrier_t
        ("pfnAppendMemoryRangesBarrier", c_void_p),                     ## _zeCommandListAppendMemoryRangesBarrier_t
        ("pfnAppendMemoryCopy", c_void_p),                              ## _zeCommandListAppendMemoryCopy_t
        ("pfnAppendMemorySet", c_void_p),                               ## _zeCommandListAppendMemorySet_t
        ("pfnAppendMemoryCopyRegion", c_void_p),                        ## _zeCommandListAppendMemoryCopyRegion_t
        ("pfnAppendImageCopy", c_void_p),                               ## _zeCommandListAppendImageCopy_t
        ("pfnAppendImageCopyRegion", c_void_p),                         ## _zeCommandListAppendImageCopyRegion_t
        ("pfnAppendImageCopyToMemory", c_void_p),                       ## _zeCommandListAppendImageCopyToMemory_t
        ("pfnAppendImageCopyFromMemory", c_void_p),                     ## _zeCommandListAppendImageCopyFromMemory_t
        ("pfnAppendMemoryPrefetch", c_void_p),                          ## _zeCommandListAppendMemoryPrefetch_t
        ("pfnAppendMemAdvise", c_void_p),                               ## _zeCommandListAppendMemAdvise_t
        ("pfnAppendSignalEvent", c_void_p),                             ## _zeCommandListAppendSignalEvent_t
        ("pfnAppendWaitOnEvents", c_void_p),                            ## _zeCommandListAppendWaitOnEvents_t
        ("pfnAppendEventReset", c_void_p),                              ## _zeCommandListAppendEventReset_t
        ("pfnAppendLaunchKernel", c_void_p),                            ## _zeCommandListAppendLaunchKernel_t
        ("pfnAppendLaunchCooperativeKernel", c_void_p),                 ## _zeCommandListAppendLaunchCooperativeKernel_t
        ("pfnAppendLaunchKernelIndirect", c_void_p),                    ## _zeCommandListAppendLaunchKernelIndirect_t
        ("pfnAppendLaunchMultipleKernelsIndirect", c_void_p),           ## _zeCommandListAppendLaunchMultipleKernelsIndirect_t
        ("pfnAppendLaunchHostFunction", c_void_p)                       ## _zeCommandListAppendLaunchHostFunction_t
    ]

###############################################################################
## @brief Function-pointer for zeFenceCreate
if __use_win_types:
    _zeFenceCreate_t = WINFUNCTYPE( ze_result_t, ze_command_queue_handle_t, POINTER(ze_fence_desc_t), POINTER(ze_fence_handle_t) )
else:
    _zeFenceCreate_t = CFUNCTYPE( ze_result_t, ze_command_queue_handle_t, POINTER(ze_fence_desc_t), POINTER(ze_fence_handle_t) )

###############################################################################
## @brief Function-pointer for zeFenceDestroy
if __use_win_types:
    _zeFenceDestroy_t = WINFUNCTYPE( ze_result_t, ze_fence_handle_t )
else:
    _zeFenceDestroy_t = CFUNCTYPE( ze_result_t, ze_fence_handle_t )

###############################################################################
## @brief Function-pointer for zeFenceHostSynchronize
if __use_win_types:
    _zeFenceHostSynchronize_t = WINFUNCTYPE( ze_result_t, ze_fence_handle_t, c_ulong )
else:
    _zeFenceHostSynchronize_t = CFUNCTYPE( ze_result_t, ze_fence_handle_t, c_ulong )

###############################################################################
## @brief Function-pointer for zeFenceQueryStatus
if __use_win_types:
    _zeFenceQueryStatus_t = WINFUNCTYPE( ze_result_t, ze_fence_handle_t )
else:
    _zeFenceQueryStatus_t = CFUNCTYPE( ze_result_t, ze_fence_handle_t )

###############################################################################
## @brief Function-pointer for zeFenceReset
if __use_win_types:
    _zeFenceReset_t = WINFUNCTYPE( ze_result_t, ze_fence_handle_t )
else:
    _zeFenceReset_t = CFUNCTYPE( ze_result_t, ze_fence_handle_t )


###############################################################################
## @brief Table of Fence functions pointers
class _ze_fence_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zeFenceCreate_t
        ("pfnDestroy", c_void_p),                                       ## _zeFenceDestroy_t
        ("pfnHostSynchronize", c_void_p),                               ## _zeFenceHostSynchronize_t
        ("pfnQueryStatus", c_void_p),                                   ## _zeFenceQueryStatus_t
        ("pfnReset", c_void_p)                                          ## _zeFenceReset_t
    ]

###############################################################################
## @brief Function-pointer for zeEventPoolCreate
if __use_win_types:
    _zeEventPoolCreate_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, POINTER(ze_event_pool_desc_t), c_ulong, POINTER(ze_device_handle_t), POINTER(ze_event_pool_handle_t) )
else:
    _zeEventPoolCreate_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, POINTER(ze_event_pool_desc_t), c_ulong, POINTER(ze_device_handle_t), POINTER(ze_event_pool_handle_t) )

###############################################################################
## @brief Function-pointer for zeEventPoolDestroy
if __use_win_types:
    _zeEventPoolDestroy_t = WINFUNCTYPE( ze_result_t, ze_event_pool_handle_t )
else:
    _zeEventPoolDestroy_t = CFUNCTYPE( ze_result_t, ze_event_pool_handle_t )

###############################################################################
## @brief Function-pointer for zeEventPoolGetIpcHandle
if __use_win_types:
    _zeEventPoolGetIpcHandle_t = WINFUNCTYPE( ze_result_t, ze_event_pool_handle_t, POINTER(ze_ipc_event_pool_handle_t) )
else:
    _zeEventPoolGetIpcHandle_t = CFUNCTYPE( ze_result_t, ze_event_pool_handle_t, POINTER(ze_ipc_event_pool_handle_t) )

###############################################################################
## @brief Function-pointer for zeEventPoolOpenIpcHandle
if __use_win_types:
    _zeEventPoolOpenIpcHandle_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, ze_ipc_event_pool_handle_t, POINTER(ze_event_pool_handle_t) )
else:
    _zeEventPoolOpenIpcHandle_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, ze_ipc_event_pool_handle_t, POINTER(ze_event_pool_handle_t) )

###############################################################################
## @brief Function-pointer for zeEventPoolCloseIpcHandle
if __use_win_types:
    _zeEventPoolCloseIpcHandle_t = WINFUNCTYPE( ze_result_t, ze_event_pool_handle_t )
else:
    _zeEventPoolCloseIpcHandle_t = CFUNCTYPE( ze_result_t, ze_event_pool_handle_t )


###############################################################################
## @brief Table of EventPool functions pointers
class _ze_event_pool_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zeEventPoolCreate_t
        ("pfnDestroy", c_void_p),                                       ## _zeEventPoolDestroy_t
        ("pfnGetIpcHandle", c_void_p),                                  ## _zeEventPoolGetIpcHandle_t
        ("pfnOpenIpcHandle", c_void_p),                                 ## _zeEventPoolOpenIpcHandle_t
        ("pfnCloseIpcHandle", c_void_p)                                 ## _zeEventPoolCloseIpcHandle_t
    ]

###############################################################################
## @brief Function-pointer for zeEventCreate
if __use_win_types:
    _zeEventCreate_t = WINFUNCTYPE( ze_result_t, ze_event_pool_handle_t, POINTER(ze_event_desc_t), POINTER(ze_event_handle_t) )
else:
    _zeEventCreate_t = CFUNCTYPE( ze_result_t, ze_event_pool_handle_t, POINTER(ze_event_desc_t), POINTER(ze_event_handle_t) )

###############################################################################
## @brief Function-pointer for zeEventDestroy
if __use_win_types:
    _zeEventDestroy_t = WINFUNCTYPE( ze_result_t, ze_event_handle_t )
else:
    _zeEventDestroy_t = CFUNCTYPE( ze_result_t, ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeEventHostSignal
if __use_win_types:
    _zeEventHostSignal_t = WINFUNCTYPE( ze_result_t, ze_event_handle_t )
else:
    _zeEventHostSignal_t = CFUNCTYPE( ze_result_t, ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeEventHostSynchronize
if __use_win_types:
    _zeEventHostSynchronize_t = WINFUNCTYPE( ze_result_t, ze_event_handle_t, c_ulong )
else:
    _zeEventHostSynchronize_t = CFUNCTYPE( ze_result_t, ze_event_handle_t, c_ulong )

###############################################################################
## @brief Function-pointer for zeEventQueryStatus
if __use_win_types:
    _zeEventQueryStatus_t = WINFUNCTYPE( ze_result_t, ze_event_handle_t )
else:
    _zeEventQueryStatus_t = CFUNCTYPE( ze_result_t, ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zeEventReset
if __use_win_types:
    _zeEventReset_t = WINFUNCTYPE( ze_result_t, ze_event_handle_t )
else:
    _zeEventReset_t = CFUNCTYPE( ze_result_t, ze_event_handle_t )


###############################################################################
## @brief Table of Event functions pointers
class _ze_event_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zeEventCreate_t
        ("pfnDestroy", c_void_p),                                       ## _zeEventDestroy_t
        ("pfnHostSignal", c_void_p),                                    ## _zeEventHostSignal_t
        ("pfnHostSynchronize", c_void_p),                               ## _zeEventHostSynchronize_t
        ("pfnQueryStatus", c_void_p),                                   ## _zeEventQueryStatus_t
        ("pfnReset", c_void_p)                                          ## _zeEventReset_t
    ]

###############################################################################
## @brief Function-pointer for zeImageGetProperties
if __use_win_types:
    _zeImageGetProperties_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_image_desc_t), POINTER(ze_image_properties_t) )
else:
    _zeImageGetProperties_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_image_desc_t), POINTER(ze_image_properties_t) )

###############################################################################
## @brief Function-pointer for zeImageCreate
if __use_win_types:
    _zeImageCreate_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_image_desc_t), POINTER(ze_image_handle_t) )
else:
    _zeImageCreate_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_image_desc_t), POINTER(ze_image_handle_t) )

###############################################################################
## @brief Function-pointer for zeImageDestroy
if __use_win_types:
    _zeImageDestroy_t = WINFUNCTYPE( ze_result_t, ze_image_handle_t )
else:
    _zeImageDestroy_t = CFUNCTYPE( ze_result_t, ze_image_handle_t )


###############################################################################
## @brief Table of Image functions pointers
class _ze_image_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zeImageGetProperties_t
        ("pfnCreate", c_void_p),                                        ## _zeImageCreate_t
        ("pfnDestroy", c_void_p)                                        ## _zeImageDestroy_t
    ]

###############################################################################
## @brief Function-pointer for zeModuleCreate
if __use_win_types:
    _zeModuleCreate_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_module_desc_t), POINTER(ze_module_handle_t), POINTER(ze_module_build_log_handle_t) )
else:
    _zeModuleCreate_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_module_desc_t), POINTER(ze_module_handle_t), POINTER(ze_module_build_log_handle_t) )

###############################################################################
## @brief Function-pointer for zeModuleDestroy
if __use_win_types:
    _zeModuleDestroy_t = WINFUNCTYPE( ze_result_t, ze_module_handle_t )
else:
    _zeModuleDestroy_t = CFUNCTYPE( ze_result_t, ze_module_handle_t )

###############################################################################
## @brief Function-pointer for zeModuleGetNativeBinary
if __use_win_types:
    _zeModuleGetNativeBinary_t = WINFUNCTYPE( ze_result_t, ze_module_handle_t, POINTER(c_size_t), POINTER(c_ubyte) )
else:
    _zeModuleGetNativeBinary_t = CFUNCTYPE( ze_result_t, ze_module_handle_t, POINTER(c_size_t), POINTER(c_ubyte) )

###############################################################################
## @brief Function-pointer for zeModuleGetGlobalPointer
if __use_win_types:
    _zeModuleGetGlobalPointer_t = WINFUNCTYPE( ze_result_t, ze_module_handle_t, POINTER(c_char), POINTER(c_void_p) )
else:
    _zeModuleGetGlobalPointer_t = CFUNCTYPE( ze_result_t, ze_module_handle_t, POINTER(c_char), POINTER(c_void_p) )

###############################################################################
## @brief Function-pointer for zeModuleGetFunctionPointer
if __use_win_types:
    _zeModuleGetFunctionPointer_t = WINFUNCTYPE( ze_result_t, ze_module_handle_t, POINTER(c_char), POINTER(c_void_p) )
else:
    _zeModuleGetFunctionPointer_t = CFUNCTYPE( ze_result_t, ze_module_handle_t, POINTER(c_char), POINTER(c_void_p) )


###############################################################################
## @brief Table of Module functions pointers
class _ze_module_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zeModuleCreate_t
        ("pfnDestroy", c_void_p),                                       ## _zeModuleDestroy_t
        ("pfnGetNativeBinary", c_void_p),                               ## _zeModuleGetNativeBinary_t
        ("pfnGetGlobalPointer", c_void_p),                              ## _zeModuleGetGlobalPointer_t
        ("pfnGetFunctionPointer", c_void_p)                             ## _zeModuleGetFunctionPointer_t
    ]

###############################################################################
## @brief Function-pointer for zeModuleBuildLogDestroy
if __use_win_types:
    _zeModuleBuildLogDestroy_t = WINFUNCTYPE( ze_result_t, ze_module_build_log_handle_t )
else:
    _zeModuleBuildLogDestroy_t = CFUNCTYPE( ze_result_t, ze_module_build_log_handle_t )

###############################################################################
## @brief Function-pointer for zeModuleBuildLogGetString
if __use_win_types:
    _zeModuleBuildLogGetString_t = WINFUNCTYPE( ze_result_t, ze_module_build_log_handle_t, POINTER(c_size_t), POINTER(c_char) )
else:
    _zeModuleBuildLogGetString_t = CFUNCTYPE( ze_result_t, ze_module_build_log_handle_t, POINTER(c_size_t), POINTER(c_char) )


###############################################################################
## @brief Table of ModuleBuildLog functions pointers
class _ze_module_build_log_dditable_t(Structure):
    _fields_ = [
        ("pfnDestroy", c_void_p),                                       ## _zeModuleBuildLogDestroy_t
        ("pfnGetString", c_void_p)                                      ## _zeModuleBuildLogGetString_t
    ]

###############################################################################
## @brief Function-pointer for zeKernelCreate
if __use_win_types:
    _zeKernelCreate_t = WINFUNCTYPE( ze_result_t, ze_module_handle_t, POINTER(ze_kernel_desc_t), POINTER(ze_kernel_handle_t) )
else:
    _zeKernelCreate_t = CFUNCTYPE( ze_result_t, ze_module_handle_t, POINTER(ze_kernel_desc_t), POINTER(ze_kernel_handle_t) )

###############################################################################
## @brief Function-pointer for zeKernelDestroy
if __use_win_types:
    _zeKernelDestroy_t = WINFUNCTYPE( ze_result_t, ze_kernel_handle_t )
else:
    _zeKernelDestroy_t = CFUNCTYPE( ze_result_t, ze_kernel_handle_t )

###############################################################################
## @brief Function-pointer for zeKernelSetIntermediateCacheConfig
if __use_win_types:
    _zeKernelSetIntermediateCacheConfig_t = WINFUNCTYPE( ze_result_t, ze_kernel_handle_t, ze_cache_config_t )
else:
    _zeKernelSetIntermediateCacheConfig_t = CFUNCTYPE( ze_result_t, ze_kernel_handle_t, ze_cache_config_t )

###############################################################################
## @brief Function-pointer for zeKernelSetGroupSize
if __use_win_types:
    _zeKernelSetGroupSize_t = WINFUNCTYPE( ze_result_t, ze_kernel_handle_t, c_ulong, c_ulong, c_ulong )
else:
    _zeKernelSetGroupSize_t = CFUNCTYPE( ze_result_t, ze_kernel_handle_t, c_ulong, c_ulong, c_ulong )

###############################################################################
## @brief Function-pointer for zeKernelSuggestGroupSize
if __use_win_types:
    _zeKernelSuggestGroupSize_t = WINFUNCTYPE( ze_result_t, ze_kernel_handle_t, c_ulong, c_ulong, c_ulong, POINTER(c_ulong), POINTER(c_ulong), POINTER(c_ulong) )
else:
    _zeKernelSuggestGroupSize_t = CFUNCTYPE( ze_result_t, ze_kernel_handle_t, c_ulong, c_ulong, c_ulong, POINTER(c_ulong), POINTER(c_ulong), POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for zeKernelSuggestMaxCooperativeGroupCount
if __use_win_types:
    _zeKernelSuggestMaxCooperativeGroupCount_t = WINFUNCTYPE( ze_result_t, ze_kernel_handle_t, POINTER(c_ulong), POINTER(c_ulong), POINTER(c_ulong) )
else:
    _zeKernelSuggestMaxCooperativeGroupCount_t = CFUNCTYPE( ze_result_t, ze_kernel_handle_t, POINTER(c_ulong), POINTER(c_ulong), POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for zeKernelSetArgumentValue
if __use_win_types:
    _zeKernelSetArgumentValue_t = WINFUNCTYPE( ze_result_t, ze_kernel_handle_t, c_ulong, c_size_t, c_void_p )
else:
    _zeKernelSetArgumentValue_t = CFUNCTYPE( ze_result_t, ze_kernel_handle_t, c_ulong, c_size_t, c_void_p )

###############################################################################
## @brief Function-pointer for zeKernelSetAttribute
if __use_win_types:
    _zeKernelSetAttribute_t = WINFUNCTYPE( ze_result_t, ze_kernel_handle_t, ze_kernel_set_attribute_t, c_ulong )
else:
    _zeKernelSetAttribute_t = CFUNCTYPE( ze_result_t, ze_kernel_handle_t, ze_kernel_set_attribute_t, c_ulong )

###############################################################################
## @brief Function-pointer for zeKernelGetAttribute
if __use_win_types:
    _zeKernelGetAttribute_t = WINFUNCTYPE( ze_result_t, ze_kernel_handle_t, ze_kernel_get_attribute_t, POINTER(c_ulong) )
else:
    _zeKernelGetAttribute_t = CFUNCTYPE( ze_result_t, ze_kernel_handle_t, ze_kernel_get_attribute_t, POINTER(c_ulong) )


###############################################################################
## @brief Table of Kernel functions pointers
class _ze_kernel_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zeKernelCreate_t
        ("pfnDestroy", c_void_p),                                       ## _zeKernelDestroy_t
        ("pfnSetIntermediateCacheConfig", c_void_p),                    ## _zeKernelSetIntermediateCacheConfig_t
        ("pfnSetGroupSize", c_void_p),                                  ## _zeKernelSetGroupSize_t
        ("pfnSuggestGroupSize", c_void_p),                              ## _zeKernelSuggestGroupSize_t
        ("pfnSuggestMaxCooperativeGroupCount", c_void_p),               ## _zeKernelSuggestMaxCooperativeGroupCount_t
        ("pfnSetArgumentValue", c_void_p),                              ## _zeKernelSetArgumentValue_t
        ("pfnSetAttribute", c_void_p),                                  ## _zeKernelSetAttribute_t
        ("pfnGetAttribute", c_void_p)                                   ## _zeKernelGetAttribute_t
    ]

###############################################################################
## @brief Function-pointer for zeSamplerCreate
if __use_win_types:
    _zeSamplerCreate_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_sampler_desc_t), POINTER(ze_sampler_handle_t) )
else:
    _zeSamplerCreate_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(ze_sampler_desc_t), POINTER(ze_sampler_handle_t) )

###############################################################################
## @brief Function-pointer for zeSamplerDestroy
if __use_win_types:
    _zeSamplerDestroy_t = WINFUNCTYPE( ze_result_t, ze_sampler_handle_t )
else:
    _zeSamplerDestroy_t = CFUNCTYPE( ze_result_t, ze_sampler_handle_t )


###############################################################################
## @brief Table of Sampler functions pointers
class _ze_sampler_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zeSamplerCreate_t
        ("pfnDestroy", c_void_p)                                        ## _zeSamplerDestroy_t
    ]

###############################################################################
class _ze_dditable_t(Structure):
    _fields_ = [
        ("Global", _ze_global_dditable_t),
        ("Device", _ze_device_dditable_t),
        ("Driver", _ze_driver_dditable_t),
        ("CommandQueue", _ze_command_queue_dditable_t),
        ("CommandList", _ze_command_list_dditable_t),
        ("Fence", _ze_fence_dditable_t),
        ("EventPool", _ze_event_pool_dditable_t),
        ("Event", _ze_event_dditable_t),
        ("Image", _ze_image_dditable_t),
        ("Module", _ze_module_dditable_t),
        ("ModuleBuildLog", _ze_module_build_log_dditable_t),
        ("Kernel", _ze_kernel_dditable_t),
        ("Sampler", _ze_sampler_dditable_t)
    ]

###############################################################################
## @brief ze device-driver interfaces
class ZE_DDI:
    def __init__(self, version : ze_api_version_t):
        # load the xe_loader library
        if "Windows" == platform.uname()[0]:
            self.__dll = WinDLL("ze_loader.dll")
        else:
            self.__dll = CDLL("ze_loader.so")

        # fill the ddi tables
        self.__dditable = _ze_dditable_t()

        # call driver to get function pointers
        _Global = _ze_global_dditable_t()
        r = ze_result_v(self.__dll.zeGetGlobalProcAddrTable(version, byref(_Global)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Global = _Global

        # attach function interface to function address
        self.zeInit = _zeInit_t(self.__dditable.Global.pfnInit)

        # call driver to get function pointers
        _Device = _ze_device_dditable_t()
        r = ze_result_v(self.__dll.zeGetDeviceProcAddrTable(version, byref(_Device)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Device = _Device

        # attach function interface to function address
        self.zeDeviceGet = _zeDeviceGet_t(self.__dditable.Device.pfnGet)
        self.zeDeviceGetSubDevices = _zeDeviceGetSubDevices_t(self.__dditable.Device.pfnGetSubDevices)
        self.zeDeviceGetProperties = _zeDeviceGetProperties_t(self.__dditable.Device.pfnGetProperties)
        self.zeDeviceGetComputeProperties = _zeDeviceGetComputeProperties_t(self.__dditable.Device.pfnGetComputeProperties)
        self.zeDeviceGetMemoryProperties = _zeDeviceGetMemoryProperties_t(self.__dditable.Device.pfnGetMemoryProperties)
        self.zeDeviceGetMemoryAccessProperties = _zeDeviceGetMemoryAccessProperties_t(self.__dditable.Device.pfnGetMemoryAccessProperties)
        self.zeDeviceGetCacheProperties = _zeDeviceGetCacheProperties_t(self.__dditable.Device.pfnGetCacheProperties)
        self.zeDeviceGetImageProperties = _zeDeviceGetImageProperties_t(self.__dditable.Device.pfnGetImageProperties)
        self.zeDeviceGetP2PProperties = _zeDeviceGetP2PProperties_t(self.__dditable.Device.pfnGetP2PProperties)
        self.zeDeviceCanAccessPeer = _zeDeviceCanAccessPeer_t(self.__dditable.Device.pfnCanAccessPeer)
        self.zeDeviceSetLastLevelCacheConfig = _zeDeviceSetLastLevelCacheConfig_t(self.__dditable.Device.pfnSetLastLevelCacheConfig)
        self.zeDeviceSystemBarrier = _zeDeviceSystemBarrier_t(self.__dditable.Device.pfnSystemBarrier)
        self.zeDeviceMakeMemoryResident = _zeDeviceMakeMemoryResident_t(self.__dditable.Device.pfnMakeMemoryResident)
        self.zeDeviceEvictMemory = _zeDeviceEvictMemory_t(self.__dditable.Device.pfnEvictMemory)
        self.zeDeviceMakeImageResident = _zeDeviceMakeImageResident_t(self.__dditable.Device.pfnMakeImageResident)
        self.zeDeviceEvictImage = _zeDeviceEvictImage_t(self.__dditable.Device.pfnEvictImage)

        # call driver to get function pointers
        _Driver = _ze_driver_dditable_t()
        r = ze_result_v(self.__dll.zeGetDriverProcAddrTable(version, byref(_Driver)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Driver = _Driver

        # attach function interface to function address
        self.zeDriverGet = _zeDriverGet_t(self.__dditable.Driver.pfnGet)
        self.zeDriverGetDriverVersion = _zeDriverGetDriverVersion_t(self.__dditable.Driver.pfnGetDriverVersion)
        self.zeDriverGetApiVersion = _zeDriverGetApiVersion_t(self.__dditable.Driver.pfnGetApiVersion)
        self.zeDriverGetIPCProperties = _zeDriverGetIPCProperties_t(self.__dditable.Driver.pfnGetIPCProperties)
        self.zeDriverAllocSharedMem = _zeDriverAllocSharedMem_t(self.__dditable.Driver.pfnAllocSharedMem)
        self.zeDriverAllocDeviceMem = _zeDriverAllocDeviceMem_t(self.__dditable.Driver.pfnAllocDeviceMem)
        self.zeDriverAllocHostMem = _zeDriverAllocHostMem_t(self.__dditable.Driver.pfnAllocHostMem)
        self.zeDriverFreeMem = _zeDriverFreeMem_t(self.__dditable.Driver.pfnFreeMem)
        self.zeDriverGetMemAllocProperties = _zeDriverGetMemAllocProperties_t(self.__dditable.Driver.pfnGetMemAllocProperties)
        self.zeDriverGetMemAddressRange = _zeDriverGetMemAddressRange_t(self.__dditable.Driver.pfnGetMemAddressRange)
        self.zeDriverGetMemIpcHandle = _zeDriverGetMemIpcHandle_t(self.__dditable.Driver.pfnGetMemIpcHandle)
        self.zeDriverOpenMemIpcHandle = _zeDriverOpenMemIpcHandle_t(self.__dditable.Driver.pfnOpenMemIpcHandle)
        self.zeDriverCloseMemIpcHandle = _zeDriverCloseMemIpcHandle_t(self.__dditable.Driver.pfnCloseMemIpcHandle)

        # call driver to get function pointers
        _CommandQueue = _ze_command_queue_dditable_t()
        r = ze_result_v(self.__dll.zeGetCommandQueueProcAddrTable(version, byref(_CommandQueue)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.CommandQueue = _CommandQueue

        # attach function interface to function address
        self.zeCommandQueueCreate = _zeCommandQueueCreate_t(self.__dditable.CommandQueue.pfnCreate)
        self.zeCommandQueueDestroy = _zeCommandQueueDestroy_t(self.__dditable.CommandQueue.pfnDestroy)
        self.zeCommandQueueExecuteCommandLists = _zeCommandQueueExecuteCommandLists_t(self.__dditable.CommandQueue.pfnExecuteCommandLists)
        self.zeCommandQueueSynchronize = _zeCommandQueueSynchronize_t(self.__dditable.CommandQueue.pfnSynchronize)

        # call driver to get function pointers
        _CommandList = _ze_command_list_dditable_t()
        r = ze_result_v(self.__dll.zeGetCommandListProcAddrTable(version, byref(_CommandList)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.CommandList = _CommandList

        # attach function interface to function address
        self.zeCommandListCreate = _zeCommandListCreate_t(self.__dditable.CommandList.pfnCreate)
        self.zeCommandListCreateImmediate = _zeCommandListCreateImmediate_t(self.__dditable.CommandList.pfnCreateImmediate)
        self.zeCommandListDestroy = _zeCommandListDestroy_t(self.__dditable.CommandList.pfnDestroy)
        self.zeCommandListClose = _zeCommandListClose_t(self.__dditable.CommandList.pfnClose)
        self.zeCommandListReset = _zeCommandListReset_t(self.__dditable.CommandList.pfnReset)
        self.zeCommandListAppendBarrier = _zeCommandListAppendBarrier_t(self.__dditable.CommandList.pfnAppendBarrier)
        self.zeCommandListAppendMemoryRangesBarrier = _zeCommandListAppendMemoryRangesBarrier_t(self.__dditable.CommandList.pfnAppendMemoryRangesBarrier)
        self.zeCommandListAppendMemoryCopy = _zeCommandListAppendMemoryCopy_t(self.__dditable.CommandList.pfnAppendMemoryCopy)
        self.zeCommandListAppendMemorySet = _zeCommandListAppendMemorySet_t(self.__dditable.CommandList.pfnAppendMemorySet)
        self.zeCommandListAppendMemoryCopyRegion = _zeCommandListAppendMemoryCopyRegion_t(self.__dditable.CommandList.pfnAppendMemoryCopyRegion)
        self.zeCommandListAppendImageCopy = _zeCommandListAppendImageCopy_t(self.__dditable.CommandList.pfnAppendImageCopy)
        self.zeCommandListAppendImageCopyRegion = _zeCommandListAppendImageCopyRegion_t(self.__dditable.CommandList.pfnAppendImageCopyRegion)
        self.zeCommandListAppendImageCopyToMemory = _zeCommandListAppendImageCopyToMemory_t(self.__dditable.CommandList.pfnAppendImageCopyToMemory)
        self.zeCommandListAppendImageCopyFromMemory = _zeCommandListAppendImageCopyFromMemory_t(self.__dditable.CommandList.pfnAppendImageCopyFromMemory)
        self.zeCommandListAppendMemoryPrefetch = _zeCommandListAppendMemoryPrefetch_t(self.__dditable.CommandList.pfnAppendMemoryPrefetch)
        self.zeCommandListAppendMemAdvise = _zeCommandListAppendMemAdvise_t(self.__dditable.CommandList.pfnAppendMemAdvise)
        self.zeCommandListAppendSignalEvent = _zeCommandListAppendSignalEvent_t(self.__dditable.CommandList.pfnAppendSignalEvent)
        self.zeCommandListAppendWaitOnEvents = _zeCommandListAppendWaitOnEvents_t(self.__dditable.CommandList.pfnAppendWaitOnEvents)
        self.zeCommandListAppendEventReset = _zeCommandListAppendEventReset_t(self.__dditable.CommandList.pfnAppendEventReset)
        self.zeCommandListAppendLaunchKernel = _zeCommandListAppendLaunchKernel_t(self.__dditable.CommandList.pfnAppendLaunchKernel)
        self.zeCommandListAppendLaunchCooperativeKernel = _zeCommandListAppendLaunchCooperativeKernel_t(self.__dditable.CommandList.pfnAppendLaunchCooperativeKernel)
        self.zeCommandListAppendLaunchKernelIndirect = _zeCommandListAppendLaunchKernelIndirect_t(self.__dditable.CommandList.pfnAppendLaunchKernelIndirect)
        self.zeCommandListAppendLaunchMultipleKernelsIndirect = _zeCommandListAppendLaunchMultipleKernelsIndirect_t(self.__dditable.CommandList.pfnAppendLaunchMultipleKernelsIndirect)
        self.zeCommandListAppendLaunchHostFunction = _zeCommandListAppendLaunchHostFunction_t(self.__dditable.CommandList.pfnAppendLaunchHostFunction)

        # call driver to get function pointers
        _Fence = _ze_fence_dditable_t()
        r = ze_result_v(self.__dll.zeGetFenceProcAddrTable(version, byref(_Fence)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Fence = _Fence

        # attach function interface to function address
        self.zeFenceCreate = _zeFenceCreate_t(self.__dditable.Fence.pfnCreate)
        self.zeFenceDestroy = _zeFenceDestroy_t(self.__dditable.Fence.pfnDestroy)
        self.zeFenceHostSynchronize = _zeFenceHostSynchronize_t(self.__dditable.Fence.pfnHostSynchronize)
        self.zeFenceQueryStatus = _zeFenceQueryStatus_t(self.__dditable.Fence.pfnQueryStatus)
        self.zeFenceReset = _zeFenceReset_t(self.__dditable.Fence.pfnReset)

        # call driver to get function pointers
        _EventPool = _ze_event_pool_dditable_t()
        r = ze_result_v(self.__dll.zeGetEventPoolProcAddrTable(version, byref(_EventPool)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.EventPool = _EventPool

        # attach function interface to function address
        self.zeEventPoolCreate = _zeEventPoolCreate_t(self.__dditable.EventPool.pfnCreate)
        self.zeEventPoolDestroy = _zeEventPoolDestroy_t(self.__dditable.EventPool.pfnDestroy)
        self.zeEventPoolGetIpcHandle = _zeEventPoolGetIpcHandle_t(self.__dditable.EventPool.pfnGetIpcHandle)
        self.zeEventPoolOpenIpcHandle = _zeEventPoolOpenIpcHandle_t(self.__dditable.EventPool.pfnOpenIpcHandle)
        self.zeEventPoolCloseIpcHandle = _zeEventPoolCloseIpcHandle_t(self.__dditable.EventPool.pfnCloseIpcHandle)

        # call driver to get function pointers
        _Event = _ze_event_dditable_t()
        r = ze_result_v(self.__dll.zeGetEventProcAddrTable(version, byref(_Event)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Event = _Event

        # attach function interface to function address
        self.zeEventCreate = _zeEventCreate_t(self.__dditable.Event.pfnCreate)
        self.zeEventDestroy = _zeEventDestroy_t(self.__dditable.Event.pfnDestroy)
        self.zeEventHostSignal = _zeEventHostSignal_t(self.__dditable.Event.pfnHostSignal)
        self.zeEventHostSynchronize = _zeEventHostSynchronize_t(self.__dditable.Event.pfnHostSynchronize)
        self.zeEventQueryStatus = _zeEventQueryStatus_t(self.__dditable.Event.pfnQueryStatus)
        self.zeEventReset = _zeEventReset_t(self.__dditable.Event.pfnReset)

        # call driver to get function pointers
        _Image = _ze_image_dditable_t()
        r = ze_result_v(self.__dll.zeGetImageProcAddrTable(version, byref(_Image)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Image = _Image

        # attach function interface to function address
        self.zeImageGetProperties = _zeImageGetProperties_t(self.__dditable.Image.pfnGetProperties)
        self.zeImageCreate = _zeImageCreate_t(self.__dditable.Image.pfnCreate)
        self.zeImageDestroy = _zeImageDestroy_t(self.__dditable.Image.pfnDestroy)

        # call driver to get function pointers
        _Module = _ze_module_dditable_t()
        r = ze_result_v(self.__dll.zeGetModuleProcAddrTable(version, byref(_Module)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Module = _Module

        # attach function interface to function address
        self.zeModuleCreate = _zeModuleCreate_t(self.__dditable.Module.pfnCreate)
        self.zeModuleDestroy = _zeModuleDestroy_t(self.__dditable.Module.pfnDestroy)
        self.zeModuleGetNativeBinary = _zeModuleGetNativeBinary_t(self.__dditable.Module.pfnGetNativeBinary)
        self.zeModuleGetGlobalPointer = _zeModuleGetGlobalPointer_t(self.__dditable.Module.pfnGetGlobalPointer)
        self.zeModuleGetFunctionPointer = _zeModuleGetFunctionPointer_t(self.__dditable.Module.pfnGetFunctionPointer)

        # call driver to get function pointers
        _ModuleBuildLog = _ze_module_build_log_dditable_t()
        r = ze_result_v(self.__dll.zeGetModuleBuildLogProcAddrTable(version, byref(_ModuleBuildLog)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.ModuleBuildLog = _ModuleBuildLog

        # attach function interface to function address
        self.zeModuleBuildLogDestroy = _zeModuleBuildLogDestroy_t(self.__dditable.ModuleBuildLog.pfnDestroy)
        self.zeModuleBuildLogGetString = _zeModuleBuildLogGetString_t(self.__dditable.ModuleBuildLog.pfnGetString)

        # call driver to get function pointers
        _Kernel = _ze_kernel_dditable_t()
        r = ze_result_v(self.__dll.zeGetKernelProcAddrTable(version, byref(_Kernel)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Kernel = _Kernel

        # attach function interface to function address
        self.zeKernelCreate = _zeKernelCreate_t(self.__dditable.Kernel.pfnCreate)
        self.zeKernelDestroy = _zeKernelDestroy_t(self.__dditable.Kernel.pfnDestroy)
        self.zeKernelSetIntermediateCacheConfig = _zeKernelSetIntermediateCacheConfig_t(self.__dditable.Kernel.pfnSetIntermediateCacheConfig)
        self.zeKernelSetGroupSize = _zeKernelSetGroupSize_t(self.__dditable.Kernel.pfnSetGroupSize)
        self.zeKernelSuggestGroupSize = _zeKernelSuggestGroupSize_t(self.__dditable.Kernel.pfnSuggestGroupSize)
        self.zeKernelSuggestMaxCooperativeGroupCount = _zeKernelSuggestMaxCooperativeGroupCount_t(self.__dditable.Kernel.pfnSuggestMaxCooperativeGroupCount)
        self.zeKernelSetArgumentValue = _zeKernelSetArgumentValue_t(self.__dditable.Kernel.pfnSetArgumentValue)
        self.zeKernelSetAttribute = _zeKernelSetAttribute_t(self.__dditable.Kernel.pfnSetAttribute)
        self.zeKernelGetAttribute = _zeKernelGetAttribute_t(self.__dditable.Kernel.pfnGetAttribute)

        # call driver to get function pointers
        _Sampler = _ze_sampler_dditable_t()
        r = ze_result_v(self.__dll.zeGetSamplerProcAddrTable(version, byref(_Sampler)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Sampler = _Sampler

        # attach function interface to function address
        self.zeSamplerCreate = _zeSamplerCreate_t(self.__dditable.Sampler.pfnCreate)
        self.zeSamplerDestroy = _zeSamplerDestroy_t(self.__dditable.Sampler.pfnDestroy)

        # success!
