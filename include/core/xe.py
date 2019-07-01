"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

 @file xe.py

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
def XE_MAKE_VERSION( _major, _minor ):
    return (( _major << 16 )|( _minor & 0x0000ffff))

###############################################################################
## @brief Extracts 'One API' API major version
def XE_MAJOR_VERSION( _ver ):
    return ( _ver >> 16 )

###############################################################################
## @brief Extracts 'One API' API minor version
def XE_MINOR_VERSION( _ver ):
    return ( _ver & 0x0000ffff )

###############################################################################
## @brief Calling convention for all API functions
# __xecall not required for python

###############################################################################
## @brief Microsoft-specific dllexport storage-class attribute
# __xedllexport not required for python

###############################################################################
## @brief Disable OpenCL interoperability functions if not explicitly defined
XE_ENABLE_OCL_INTEROP = 0

###############################################################################
## @brief compiler-independent type
class xe_bool_t(c_ubyte):
    pass

###############################################################################
## @brief Handle of driver's device group object
class xe_device_group_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's device object
class xe_device_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's command queue object
class xe_command_queue_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's command list object
class xe_command_list_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's fence object
class xe_fence_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's event pool object
class xe_event_pool_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's event object
class xe_event_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's image object
class xe_image_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's module object
class xe_module_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of module's build log object
class xe_module_build_log_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's function object
class xe_function_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's sampler object
class xe_sampler_handle_t(c_void_p):
    pass

###############################################################################
## @brief IPC handle to a memory allocation
class xe_ipc_mem_handle_t(c_void_p):
    pass

###############################################################################
## @brief IPC handle to a event pool allocation
class xe_ipc_event_pool_handle_t(c_void_p):
    pass

###############################################################################
## @brief Generic macro for enumerator bit masks
def XE_BIT( _i ):
    return ( 1 << _i )

###############################################################################
## @brief Defines Return/Error codes
## 
## @remarks
##   _Analogues_
##     - **CUresult**
class xe_result_v(IntEnum):
    SUCCESS = 0                                     ## success
    NOT_READY = 1                                   ## synchronization primitive not signaled
    ERROR_UNINITIALIZED = auto()                    ## driver is not initialized
    ERROR_DEVICE_LOST = auto()                      ## device hung, reset, was removed, or driver update occurred
    ERROR_UNSUPPORTED = auto()                      ## device does not support feature requested
    ERROR_INVALID_ARGUMENT = auto()                 ## invalid argument provided
    ERROR_OUT_OF_HOST_MEMORY = auto()               ## insufficient host memory to satisfy call
    ERROR_OUT_OF_DEVICE_MEMORY = auto()             ## insufficient device memory to satisfy call
    ERROR_MODULE_BUILD_FAILURE = auto()             ## error in building module
    ERROR_UNKNOWN = 0x7fffffff                      ## unknown or internal error

class xe_result_t(c_int):
    def __str__(self):
        return str(xe_result_v(value))


###############################################################################
## @brief Supported initialization flags
class xe_init_flag_v(IntEnum):
    NONE = 0                                        ## default behavior
    GPU_ONLY = XE_BIT(0)                            ## only initialize GPU drivers

class xe_init_flag_t(c_int):
    def __str__(self):
        return str(xe_init_flag_v(value))


###############################################################################
## @brief Supported API versions
## 
## @details
##     - API versions contain major and minor attributes, use
##       ::XE_MAJOR_VERSION and ::XE_MINOR_VERSION
class xe_api_version_v(IntEnum):
    _1_0 = XE_MAKE_VERSION( 1, 0 )                  ## 1.0

class xe_api_version_t(c_int):
    def __str__(self):
        return str(xe_api_version_v(value))


###############################################################################
## @brief API version of ::xe_device_properties_t
class xe_device_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_device_properties_version_t(c_int):
    def __str__(self):
        return str(xe_device_properties_version_v(value))


###############################################################################
## @brief Maximum device uuid size in bytes
XE_MAX_UUID_SIZE = 16

###############################################################################
## @brief Supported device types
class xe_device_type_v(IntEnum):
    GPU = 1                                         ## Graphics Processing Unit
    FPGA = auto()                                   ## Field Programmable Gate Array

class xe_device_type_t(c_int):
    def __str__(self):
        return str(xe_device_type_v(value))


###############################################################################
## @brief Device universal unique id (UUID)
class xe_device_uuid_t(Structure):
    _fields_ = [
        ("id", c_ubyte * XE_MAX_UUID_SIZE)                              ## [out] device universal unique id
    ]

###############################################################################
## @brief Maximum device name string size
XE_MAX_DEVICE_NAME = 256

###############################################################################
## @brief Device properties queried using ::xeDeviceGroupGetDeviceProperties
class xe_device_properties_t(Structure):
    _fields_ = [
        ("version", xe_device_properties_version_t),                    ## [in] ::XE_DEVICE_PROPERTIES_VERSION_CURRENT
        ("type", xe_device_type_t),                                     ## [out] generic device type
        ("vendorId", c_ulong),                                          ## [out] vendor id from PCI configuration
        ("deviceId", c_ulong),                                          ## [out] device id from PCI configuration
        ("uuid", xe_device_uuid_t),                                     ## [out] universal unique identifier.
        ("isSubdevice", xe_bool_t),                                     ## [out] If the device handle used for query represents a sub-device.
        ("subdeviceId", c_ulong),                                       ## [out] sub-device id. Only valid if isSubdevice is true.
        ("coreClockRate", c_ulong),                                     ## [out] Clock rate for device core.
        ("unifiedMemorySupported", xe_bool_t),                          ## [out] Supports unified physical memory between Host and device.
        ("onDemandPageFaultsSupported", xe_bool_t),                     ## [out] Supports on-demand page-faulting.
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
        ("name", c_char * XE_MAX_DEVICE_NAME)                           ## [out] Device name
    ]

###############################################################################
## @brief API version of ::xe_device_compute_properties_t
class xe_device_compute_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_device_compute_properties_version_t(c_int):
    def __str__(self):
        return str(xe_device_compute_properties_version_v(value))


###############################################################################
## @brief Maximum number of subgroup sizes supported.
XE_SUBGROUPSIZE_COUNT = 8

###############################################################################
## @brief Device compute properties queried using
##        ::xeDeviceGroupGetComputeProperties
class xe_device_compute_properties_t(Structure):
    _fields_ = [
        ("version", xe_device_compute_properties_version_t),            ## [in] ::XE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT
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
        ("subGroupSizes", c_ulong * XE_SUBGROUPSIZE_COUNT)              ## [out] Size group sizes supported.
    ]

###############################################################################
## @brief API version of ::xe_device_memory_properties_t
class xe_device_memory_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_device_memory_properties_version_t(c_int):
    def __str__(self):
        return str(xe_device_memory_properties_version_v(value))


###############################################################################
## @brief Device local memory properties queried using
##        ::xeDeviceGroupGetMemoryProperties
class xe_device_memory_properties_t(Structure):
    _fields_ = [
        ("version", xe_device_memory_properties_version_t),             ## [in] ::XE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT
        ("maxClockRate", c_ulong),                                      ## [out] Maximum clock rate for device memory.
        ("maxBusWidth", c_ulong),                                       ## [out] Maximum bus width between device and memory.
        ("totalSize", c_ulonglong)                                      ## [out] Total memory size in bytes.
    ]

###############################################################################
## @brief API version of ::xe_device_memory_access_properties_t
class xe_device_memory_access_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_device_memory_access_properties_version_t(c_int):
    def __str__(self):
        return str(xe_device_memory_access_properties_version_v(value))


###############################################################################
## @brief Memory access capabilities
## 
## @details
##     - Supported access capabilities for different types of memory
##       allocations
class xe_memory_access_capabilities_v(IntEnum):
    MEMORY_ACCESS_NONE = 0                          ## Access not supported
    MEMORY_ACCESS = XE_BIT( 0 )                     ## Supports load/store access
    MEMORY_ATOMIC_ACCESS = XE_BIT( 1 )              ## Supports atomic access
    MEMORY_CONCURRENT_ACCESS = XE_BIT( 2 )          ## Supports concurrent access
    MEMORY_CONCURRENT_ATOMIC_ACCESS = XE_BIT( 3 )   ## Supports concurrent atomic access

class xe_memory_access_capabilities_t(c_int):
    def __str__(self):
        return str(xe_memory_access_capabilities_v(value))


###############################################################################
## @brief Device memory access properties queried using
##        ::xeDeviceGroupGetMemoryAccessProperties
class xe_device_memory_access_properties_t(Structure):
    _fields_ = [
        ("version", xe_device_memory_access_properties_version_t),      ## [in] ::XE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT
        ("hostAllocCapabilities", xe_memory_access_capabilities_t),     ## [out] Bitfield describing host memory capabilities
        ("deviceAllocCapabilities", xe_memory_access_capabilities_t),   ## [out] Bitfield describing device memory capabilities
        ("sharedSingleDeviceAllocCapabilities", xe_memory_access_capabilities_t),   ## [out] Bitfield describing shared (single-device) memory capabilities
        ("sharedCrossDeviceAllocCapabilities", xe_memory_access_capabilities_t),## [out] Bitfield describing shared (cross-device) memory capabilities
        ("sharedSystemAllocCapabilities", xe_memory_access_capabilities_t)  ## [out] Bitfield describing shared (system) memory capabilities
    ]

###############################################################################
## @brief API version of ::xe_device_cache_properties_t
class xe_device_cache_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_device_cache_properties_version_t(c_int):
    def __str__(self):
        return str(xe_device_cache_properties_version_v(value))


###############################################################################
## @brief Device cache properties queried using
##        ::xeDeviceGroupGetCacheProperties
class xe_device_cache_properties_t(Structure):
    _fields_ = [
        ("version", xe_device_cache_properties_version_t),              ## [in] ::XE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT
        ("intermediateCacheControlSupported", xe_bool_t),               ## [out] Support User control on Intermediate Cache (i.e. Resize SLM
                                                                        ## section vs Generic Cache)
        ("intermediateCacheSize", c_size_t),                            ## [out] Per-cache Intermediate Cache (L1/L2) size, in bytes
        ("lastLevelCacheSizeControlSupported", xe_bool_t),              ## [out] Support User control on Last Level Cache (i.e. Resize SLM
                                                                        ## section vs Generic Cache).
        ("lastLevelCacheSize", c_size_t)                                ## [out] Per-cache Last Level Cache (L3) size, in bytes
    ]

###############################################################################
## @brief API version of ::xe_device_image_properties_t
class xe_device_image_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_device_image_properties_version_t(c_int):
    def __str__(self):
        return str(xe_device_image_properties_version_v(value))


###############################################################################
## @brief Device image properties queried using
##        ::xeDeviceGroupGetComputeProperties
class xe_device_image_properties_t(Structure):
    _fields_ = [
        ("version", xe_device_image_properties_version_t),              ## [in] ::XE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT
        ("supported", xe_bool_t),                                       ## [out] Supports reading and writing of images. See
                                                                        ## ::::xeImageGetProperties for format-specific capabilities.
        ("maxImageDims1D", c_ulong),                                    ## [out] Maximum image dimensions for 1D resources.
        ("maxImageDims2D", c_ulong),                                    ## [out] Maximum image dimensions for 2D resources.
        ("maxImageDims3D", c_ulong),                                    ## [out] Maximum image dimensions for 3D resources.
        ("maxImageArraySlices", c_ulong)                                ## [out] Maximum image array slices
    ]

###############################################################################
## @brief API version of ::xe_device_ipc_properties_t
class xe_device_ipc_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_device_ipc_properties_version_t(c_int):
    def __str__(self):
        return str(xe_device_ipc_properties_version_v(value))


###############################################################################
## @brief Device IPC properties queried using ::xeDeviceGroupGetIPCProperties
class xe_device_ipc_properties_t(Structure):
    _fields_ = [
        ("version", xe_device_ipc_properties_version_t),                ## [in] ::XE_DEVICE_IPC_PROPERTIES_VERSION_CURRENT
        ("memsSupported", xe_bool_t),                                   ## [out] Supports passing memory allocations between processes. See
                                                                        ## ::::xeDeviceGroupGetMemIpcHandle.
        ("eventsSupported", xe_bool_t)                                  ## [out] Supports passing events between processes. See
                                                                        ## ::::xeEventPoolGetIpcHandle.
    ]

###############################################################################
## @brief API version of ::xe_device_p2p_properties_t
class xe_device_p2p_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_device_p2p_properties_version_t(c_int):
    def __str__(self):
        return str(xe_device_p2p_properties_version_v(value))


###############################################################################
## @brief Device properties queried using ::xeDeviceGetP2PProperties
class xe_device_p2p_properties_t(Structure):
    _fields_ = [
        ("version", xe_device_p2p_properties_version_t),                ## [in] ::XE_DEVICE_P2P_PROPERTIES_VERSION_CURRENT
        ("accessSupported", xe_bool_t),                                 ## [out] Supports access between peer devices.
        ("atomicsSupported", xe_bool_t)                                 ## [out] Supports atomics between peer devices.
    ]

###############################################################################
## @brief Supported Cache Config
## 
## @details
##     - Supported Cache Config (Default, Large SLM, Large Data Cache)
class xe_cache_config_v(IntEnum):
    DEFAULT = XE_BIT( 0 )                           ## Default Config
    LARGE_SLM = XE_BIT( 1 )                         ## Large SLM size
    LARGE_DATA = XE_BIT( 2 )                        ## Large General Data size

class xe_cache_config_t(c_int):
    def __str__(self):
        return str(xe_cache_config_v(value))


###############################################################################
## @brief API version of ::xe_command_queue_desc_t
class xe_command_queue_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_command_queue_desc_version_t(c_int):
    def __str__(self):
        return str(xe_command_queue_desc_version_v(value))


###############################################################################
## @brief Supported command queue flags
class xe_command_queue_flag_v(IntEnum):
    NONE = 0                                        ## default behavior
    COPY_ONLY = XE_BIT(0)                           ## command queue only supports enqueing copy-only command lists
    LOGICAL_ONLY = XE_BIT(1)                        ## command queue is not tied to a physical command queue; driver may
                                                    ## dynamically assign based on usage
    SINGLE_SLICE_ONLY = XE_BIT(2)                   ## command queue reserves and cannot comsume more than a single slice.
                                                    ## 'slice' size is device-specific.  cannot be combined with COPY_ONLY.

class xe_command_queue_flag_t(c_int):
    def __str__(self):
        return str(xe_command_queue_flag_v(value))


###############################################################################
## @brief Supported command queue modes
class xe_command_queue_mode_v(IntEnum):
    DEFAULT = 0                                     ## implicit default behavior; uses driver-based heuristics
    SYNCHRONOUS = auto()                            ## Device execution always completes immediately on execute;
                                                    ## Host thread is blocked using wait on implicit synchronization object
    ASYNCHRONOUS = auto()                           ## Device execution is scheduled and will complete in future;
                                                    ## explicit synchronization object must be used to determine completeness

class xe_command_queue_mode_t(c_int):
    def __str__(self):
        return str(xe_command_queue_mode_v(value))


###############################################################################
## @brief Supported command queue priorities
class xe_command_queue_priority_v(IntEnum):
    NORMAL = 0                                      ## [default] normal priority
    LOW = auto()                                    ## lower priority than normal
    HIGH = auto()                                   ## higher priority than normal

class xe_command_queue_priority_t(c_int):
    def __str__(self):
        return str(xe_command_queue_priority_v(value))


###############################################################################
## @brief Command Queue descriptor
class xe_command_queue_desc_t(Structure):
    _fields_ = [
        ("version", xe_command_queue_desc_version_t),                   ## [in] ::XE_COMMAND_QUEUE_DESC_VERSION_CURRENT
        ("flags", xe_command_queue_flag_t),                             ## [in] creation flags
        ("mode", xe_command_queue_mode_t),                              ## [in] operation mode
        ("priority", xe_command_queue_priority_t),                      ## [in] priority
        ("ordinal", c_ulong)                                            ## [in] if logical-only flag is set, then will be ignored;
                                                                        ## else-if copy-only flag is set, then must be less than ::xe_device_properties_t.numAsyncCopyEngines;
                                                                        ## otherwise must be less than
                                                                        ## ::xe_device_properties_t.numAsyncComputeEngines. When using sub-devices
                                                                        ## the ::xe_device_properties_t.numAsyncComputeEngines must be queried
                                                                        ## from the sub-device being used.
    ]

###############################################################################
## @brief API version of ::xe_command_list_desc_t
class xe_command_list_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_command_list_desc_version_t(c_int):
    def __str__(self):
        return str(xe_command_list_desc_version_v(value))


###############################################################################
## @brief Supported command list creation flags
class xe_command_list_flag_v(IntEnum):
    NONE = 0                                        ## default behavior
    COPY_ONLY = XE_BIT(0)                           ## command list **only** contains copy operations (and synchronization primitives).
                                                    ## this command list may **only** be submitted to a command queue created
                                                    ## with ::XE_COMMAND_QUEUE_FLAG_COPY_ONLY.
    RELAXED_ORDERING = XE_BIT(1)                    ## driver may reorder programs and copys between barriers and
                                                    ## synchronization primitives.
                                                    ## using this flag may increase Host overhead of ::xeCommandListClose.
                                                    ## therefore, this flag should **not** be set for low-latency usage-models.
    MAXIMIZE_THROUGHPUT = XE_BIT(2)                 ## driver may perform additional optimizations that increase dexecution
                                                    ## throughput. 
                                                    ## using this flag may increase Host overhead of ::xeCommandListClose and ::xeCommandQueueExecuteCommandLists.
                                                    ## therefore, this flag should **not** be set for low-latency usage-models.
    EXPLICIT_ONLY = XE_BIT(3)                       ## command list should be optimized for submission to a single command
                                                    ## queue and device engine.
                                                    ## driver **must** disable any implicit optimizations for distributing
                                                    ## work across multiple engines.
                                                    ## this flag should be used when applications want full control over
                                                    ## multi-engine submission and scheduling.

class xe_command_list_flag_t(c_int):
    def __str__(self):
        return str(xe_command_list_flag_v(value))


###############################################################################
## @brief Command List descriptor
class xe_command_list_desc_t(Structure):
    _fields_ = [
        ("version", xe_command_list_desc_version_t),                    ## [in] ::XE_COMMAND_LIST_DESC_VERSION_CURRENT
        ("flags", xe_command_list_flag_t)                               ## [in] creation flags
    ]

###############################################################################
## @brief Supported command list parameters
class xe_command_list_parameter_v(IntEnum):
    TBD = auto()                                    ## TBD

class xe_command_list_parameter_t(c_int):
    def __str__(self):
        return str(xe_command_list_parameter_v(value))


###############################################################################
## @brief Copy region descriptor
class xe_copy_region_t(Structure):
    _fields_ = [
        ("originX", c_ulong),                                           ## [in] The origin x offset for region in bytes
        ("originY", c_ulong),                                           ## [in] The origin y offset for region in rows
        ("width", c_ulong),                                             ## [in] The region width relative to origin in bytes
        ("height", c_ulong)                                             ## [in] The region height relative to origin in rows
    ]

###############################################################################
## @brief Region descriptor
class xe_image_region_t(Structure):
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
class xe_memory_advice_v(IntEnum):
    SET_READ_MOSTLY = 0                             ## hint that memory will be read from frequently and written to rarely
    CLEAR_READ_MOSTLY = auto()                      ## removes the affect of ::XE_MEMORY_ADVICE_SET_READ_MOSTLY
    SET_PREFERRED_LOCATION = auto()                 ## hint that the preferred memory location is the specified device
    CLEAR_PREFERRED_LOCATION = auto()               ## removes the affect of ::XE_MEMORY_ADVICE_SET_PREFERRED_LOCATION
    SET_ACCESSED_BY = auto()                        ## hint that memory will be accessed by the specified device
    CLEAR_ACCESSED_BY = auto()                      ## removes the affect of ::XE_MEMORY_ADVICE_SET_ACCESSED_BY
    SET_NON_ATOMIC_MOSTLY = auto()                  ## hints that memory will mostly be accessed non-atomically
    CLEAR_NON_ATOMIC_MOSTLY = auto()                ## removes the affect of ::XE_MEMORY_ADVICE_SET_NON_ATOMIC_MOSTLY
    BIAS_CACHED = auto()                            ## hints that memory should be cached
    BIAS_UNCACHED = auto()                          ## hints that memory should be not be cached

class xe_memory_advice_t(c_int):
    def __str__(self):
        return str(xe_memory_advice_v(value))


###############################################################################
## @brief API version of ::xe_event_pool_desc_t
class xe_event_pool_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_event_pool_desc_version_t(c_int):
    def __str__(self):
        return str(xe_event_pool_desc_version_v(value))


###############################################################################
## @brief Supported event pool creation flags
class xe_event_pool_flag_v(IntEnum):
    DEFAULT = 0                                     ## signals and waits visible to the entire device and peer devices
    HOST_VISIBLE = XE_BIT(0)                        ## signals and waits are also visible to host
    IPC = XE_BIT(1)                                 ## signals and waits may be shared across processes

class xe_event_pool_flag_t(c_int):
    def __str__(self):
        return str(xe_event_pool_flag_v(value))


###############################################################################
## @brief Event pool descriptor
class xe_event_pool_desc_t(Structure):
    _fields_ = [
        ("version", xe_event_pool_desc_version_t),                      ## [in] ::XE_EVENT_POOL_DESC_VERSION_CURRENT
        ("flags", xe_event_pool_flag_t),                                ## [in] creation flags
        ("count", c_ulong)                                              ## [in] number of events within the pool
    ]

###############################################################################
## @brief API version of ::xe_event_desc_t
class xe_event_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_event_desc_version_t(c_int):
    def __str__(self):
        return str(xe_event_desc_version_v(value))


###############################################################################
## @brief Supported event scope flags
class xe_event_scope_flag_v(IntEnum):
    NONE = 0                                        ## execution synchronization only; no cache hierarchies are flushed or
                                                    ## invalidated
    SUBDEVICE = XE_BIT(0)                           ## cache hierarchies are flushed or invalidated sufficient for local
                                                    ## sub-device access
    DEVICE = XE_BIT(1)                              ## cache hierarchies are flushed or invalidated sufficient for global
                                                    ## device access and peer device access
    HOST = XE_BIT(2)                                ## cache hierarchies are flushed or invalidated sufficient for device and
                                                    ## host access

class xe_event_scope_flag_t(c_int):
    def __str__(self):
        return str(xe_event_scope_flag_v(value))


###############################################################################
## @brief Event descriptor
class xe_event_desc_t(Structure):
    _fields_ = [
        ("version", xe_event_desc_version_t),                           ## [in] ::XE_EVENT_DESC_VERSION_CURRENT
        ("index", c_ulong),                                             ## [in] index of the event within the pool; must be less-than the count
                                                                        ## specified during pool creation
        ("signal", xe_event_scope_flag_t),                              ## [in] defines the scope of relevant cache hierarchies to flush on a
                                                                        ## signal action before the event is triggered
        ("wait", xe_event_scope_flag_t)                                 ## [in] defines the scope of relevant cache hierarchies to invalidate on
                                                                        ## a wait action after the event is complete
    ]

###############################################################################
## @brief API version of ::xe_fence_desc_t
class xe_fence_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_fence_desc_version_t(c_int):
    def __str__(self):
        return str(xe_fence_desc_version_v(value))


###############################################################################
## @brief Supported fence creation flags
class xe_fence_flag_v(IntEnum):
    NONE = 0                                        ## default behavior

class xe_fence_flag_t(c_int):
    def __str__(self):
        return str(xe_fence_flag_v(value))


###############################################################################
## @brief Fence descriptor
class xe_fence_desc_t(Structure):
    _fields_ = [
        ("version", xe_fence_desc_version_t),                           ## [in] ::XE_FENCE_DESC_VERSION_CURRENT
        ("flags", xe_fence_flag_t)                                      ## [in] creation flags
    ]

###############################################################################
## @brief API version of ::xe_image_desc_t
class xe_image_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_image_desc_version_t(c_int):
    def __str__(self):
        return str(xe_image_desc_version_v(value))


###############################################################################
## @brief Supported image creation flags
class xe_image_flag_v(IntEnum):
    PROGRAM_READ = XE_BIT( 0 )                      ## programs will read contents
    PROGRAM_WRITE = XE_BIT( 1 )                     ## programs will write contents
    BIAS_CACHED = XE_BIT( 2 )                       ## device should cache contents
    BIAS_UNCACHED = XE_BIT( 3 )                     ## device should not cache contents

class xe_image_flag_t(c_int):
    def __str__(self):
        return str(xe_image_flag_v(value))


###############################################################################
## @brief Supported image types
class xe_image_type_v(IntEnum):
    _1D = auto()                                    ## 1D
    _1DARRAY = auto()                               ## 1D array
    _2D = auto()                                    ## 2D
    _2DARRAY = auto()                               ## 2D array
    _3D = auto()                                    ## 3D

class xe_image_type_t(c_int):
    def __str__(self):
        return str(xe_image_type_v(value))


###############################################################################
## @brief Supported image format layouts
class xe_image_format_layout_v(IntEnum):
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

class xe_image_format_layout_t(c_int):
    def __str__(self):
        return str(xe_image_format_layout_v(value))


###############################################################################
## @brief Supported image format types
class xe_image_format_type_v(IntEnum):
    UINT = auto()                                   ## Unsigned integer
    SINT = auto()                                   ## Signed integer
    UNORM = auto()                                  ## Unsigned normalized integer
    SNORM = auto()                                  ## Signed normalized integer
    FLOAT = auto()                                  ## Float

class xe_image_format_type_t(c_int):
    def __str__(self):
        return str(xe_image_format_type_v(value))


###############################################################################
## @brief Supported image format component swizzle into channel
class xe_image_format_swizzle_v(IntEnum):
    R = auto()                                      ## Red component
    G = auto()                                      ## Green component
    B = auto()                                      ## Blue component
    A = auto()                                      ## Alpha component
    _0 = auto()                                     ## Zero
    _1 = auto()                                     ## One
    X = auto()                                      ## Don't care

class xe_image_format_swizzle_t(c_int):
    def __str__(self):
        return str(xe_image_format_swizzle_v(value))


###############################################################################
## @brief Image format descriptor
class xe_image_format_desc_t(Structure):
    _fields_ = [
        ("layout", xe_image_format_layout_t),                           ## [in] image format component layout
        ("type", xe_image_format_type_t),                               ## [in] image format type
        ("x", xe_image_format_swizzle_t),                               ## [in] image component swizzle into channel x
        ("y", xe_image_format_swizzle_t),                               ## [in] image component swizzle into channel y
        ("z", xe_image_format_swizzle_t),                               ## [in] image component swizzle into channel z
        ("w", xe_image_format_swizzle_t)                                ## [in] image component swizzle into channel w
    ]

###############################################################################
## @brief Image descriptor
class xe_image_desc_t(Structure):
    _fields_ = [
        ("version", xe_image_desc_version_t),                           ## [in] ::XE_IMAGE_DESC_VERSION_CURRENT
        ("flags", xe_image_flag_t),                                     ## [in] creation flags
        ("type", xe_image_type_t),                                      ## [in] image type
        ("format", xe_image_format_desc_t),                             ## [in] image format
        ("width", c_size_t),                                            ## [in] width in pixels, see
                                                                        ## ::xe_device_image_properties_t::maxImageDims1D/2D/3D
        ("height", c_size_t),                                           ## [in] height in pixels (2D or 3D only), see
                                                                        ## ::xe_device_image_properties_t::maxImageDims2D/3D
        ("depth", c_size_t),                                            ## [in] depth in pixels (3D only), see
                                                                        ## ::xe_device_image_properties_t::maxImageDims3D
        ("arraylevels", c_size_t),                                      ## [in] array levels (array types only), see
                                                                        ## ::xe_device_image_properties_t::maxImageArraySlices
        ("miplevels", c_size_t)                                         ## [in] mipmap levels (must be 0)
    ]

###############################################################################
## @brief API version of ::xe_image_properties_t
class xe_image_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_image_properties_version_t(c_int):
    def __str__(self):
        return str(xe_image_properties_version_v(value))


###############################################################################
## @brief Supported sampler filtering flags
class xe_image_sampler_filter_flags_v(IntEnum):
    NONE = 0                                        ## device does not support filtering
    POINT = XE_BIT(0)                               ## device supports point filtering
    LINEAR = XE_BIT(1)                              ## device supports linear filtering

class xe_image_sampler_filter_flags_t(c_int):
    def __str__(self):
        return str(xe_image_sampler_filter_flags_v(value))


###############################################################################
## @brief Image properties
class xe_image_properties_t(Structure):
    _fields_ = [
        ("version", xe_image_properties_version_t),                     ## [in] ::XE_IMAGE_PROPERTIES_VERSION_CURRENT
        ("samplerFilterFlags", xe_image_sampler_filter_flags_t)         ## [out] supported sampler filtering
    ]

###############################################################################
## @brief Supported device memory allocation flags
class xe_device_mem_alloc_flag_v(IntEnum):
    DEFAULT = 0                                     ## implicit default behavior; uses driver-based heuristics
    BIAS_CACHED = XE_BIT( 0 )                       ## device should cache allocation
    BIAS_UNCACHED = XE_BIT( 1 )                     ## device should not cache allocation (UC)

class xe_device_mem_alloc_flag_t(c_int):
    def __str__(self):
        return str(xe_device_mem_alloc_flag_v(value))


###############################################################################
## @brief Supported host memory allocation flags
class xe_host_mem_alloc_flag_v(IntEnum):
    DEFAULT = 0                                     ## implicit default behavior; uses driver-based heuristics
    BIAS_CACHED = XE_BIT( 0 )                       ## host should cache allocation
    BIAS_UNCACHED = XE_BIT( 1 )                     ## host should not cache allocation (UC)
    BIAS_WRITE_COMBINED = XE_BIT( 2 )               ## host memory should be allocated write-combined (WC)

class xe_host_mem_alloc_flag_t(c_int):
    def __str__(self):
        return str(xe_host_mem_alloc_flag_v(value))


###############################################################################
## @brief API version of ::xe_memory_allocation_properties_t
class xe_memory_allocation_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_memory_allocation_properties_version_t(c_int):
    def __str__(self):
        return str(xe_memory_allocation_properties_version_v(value))


###############################################################################
## @brief Memory allocation type
class xe_memory_type_v(IntEnum):
    UNKNOWN = 0                                     ## the memory pointed to is of unknown type
    HOST = auto()                                   ## the memory pointed to is a host allocation
    DEVICE = auto()                                 ## the memory pointed to is a device allocation
    SHARED = auto()                                 ## the memory pointed to is a shared ownership allocation

class xe_memory_type_t(c_int):
    def __str__(self):
        return str(xe_memory_type_v(value))


###############################################################################
## @brief Memory allocation properties queried using
##        ::xeDeviceGroupGetMemProperties
class xe_memory_allocation_properties_t(Structure):
    _fields_ = [
        ("version", xe_memory_allocation_properties_version_t),         ## [in] ::XE_MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT
        ("type", xe_memory_type_t),                                     ## [out] type of allocated memory
        ("id", c_ulonglong)                                             ## [out] identifier for this allocation
    ]

###############################################################################
## @brief Supported IPC memory flags
class xe_ipc_memory_flag_v(IntEnum):
    NONE = 0                                        ## No special flags

class xe_ipc_memory_flag_t(c_int):
    def __str__(self):
        return str(xe_ipc_memory_flag_v(value))


###############################################################################
## @brief API version of ::xe_module_desc_t
class xe_module_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_module_desc_version_t(c_int):
    def __str__(self):
        return str(xe_module_desc_version_v(value))


###############################################################################
## @brief Supported module creation input formats
class xe_module_format_v(IntEnum):
    IL_SPIRV = 0                                    ## Format is SPIRV IL format
    NATIVE = auto()                                 ## Format is device native format

class xe_module_format_t(c_int):
    def __str__(self):
        return str(xe_module_format_v(value))


###############################################################################
## @brief Module descriptor
class xe_module_desc_t(Structure):
    _fields_ = [
        ("version", xe_module_desc_version_t),                          ## [in] ::XE_MODULE_DESC_VERSION_CURRENT
        ("format", xe_module_format_t),                                 ## [in] Module format passed in with pInputModule
        ("inputSize", c_size_t),                                        ## [in] size of input IL or ISA from pInputModule.
        ("pInputModule", POINTER(c_ubyte)),                             ## [in] pointer to IL or ISA
        ("pBuildFlags", POINTER(c_char))                                ## [in] string containing compiler flags. See programming guide for build
                                                                        ## flags.
    ]

###############################################################################
## @brief API version of ::xe_function_desc_t
class xe_function_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_function_desc_version_t(c_int):
    def __str__(self):
        return str(xe_function_desc_version_v(value))


###############################################################################
## @brief Supported function creation flags
class xe_function_flag_v(IntEnum):
    NONE = 0                                        ## default driver behavior
    FORCE_RESIDENCY = auto()                        ## force all device allocations to be resident during execution

class xe_function_flag_t(c_int):
    def __str__(self):
        return str(xe_function_flag_v(value))


###############################################################################
## @brief Function descriptor
class xe_function_desc_t(Structure):
    _fields_ = [
        ("version", xe_function_desc_version_t),                        ## [in] ::XE_FUNCTION_DESC_VERSION_CURRENT
        ("flags", xe_function_flag_t),                                  ## [in] creation flags
        ("pFunctionName", POINTER(c_char))                              ## [in] null-terminated name of function in Module
    ]

###############################################################################
## @brief Function attributes
## 
## @remarks
##   _Analogues_
##     - **cl_kernel_exec_info**
class xe_function_set_attribute_v(IntEnum):
    FUNCTION_SET_ATTR_INDIRECT_HOST_ACCESS = 0      ## Indicates that the function accesses host allocations indirectly
                                                    ## (default: false)
    FUNCTION_SET_ATTR_INDIRECT_DEVICE_ACCESS = auto()   ## Indicates that the function accesses device allocations indirectly
                                                    ## (default: false)
    FUNCTION_SET_ATTR_INDIRECT_SHARED_ACCESS = auto()   ## Indicates that the function accesses shared allocations indirectly
                                                    ## (default: false)

class xe_function_set_attribute_t(c_int):
    def __str__(self):
        return str(xe_function_set_attribute_v(value))


###############################################################################
## @brief Function attributes
## 
## @remarks
##   _Analogues_
##     - **CUfunction_attribute**
class xe_function_get_attribute_v(IntEnum):
    FUNCTION_GET_ATTR_MAX_REGS_USED = 0             ## Maximum device registers used for this function
    FUNCTION_GET_ATTR_NUM_THREAD_DIMENSIONS = auto()## Maximum dimensions for group for this function
    FUNCTION_GET_ATTR_MAX_SHARED_MEM_SIZE = auto()  ## Maximum shared memory required for this function
    FUNCTION_GET_ATTR_HAS_SPILL_FILL = auto()       ## Function required spill/fills.
    FUNCTION_GET_ATTR_HAS_BARRIERS = auto()         ## Function contains barriers.
    FUNCTION_GET_ATTR_HAS_DPAS = auto()             ## Function contains DPAs.

class xe_function_get_attribute_t(c_int):
    def __str__(self):
        return str(xe_function_get_attribute_v(value))


###############################################################################
## @brief Function thread group dimensions.
class xe_thread_group_dimensions_t(Structure):
    _fields_ = [
        ("groupCountX", c_ulong),                                       ## [in] size of thread group in X dimension
        ("groupCountY", c_ulong),                                       ## [in] size of thread group in Y dimension
        ("groupCountZ", c_ulong)                                        ## [in] size of thread group in Z dimension
    ]

###############################################################################
## @brief type definition for host function pointers used with
##        ::xeCommandListAppendLaunchHostFunction
## 
## @details
##     - The application may call this function from simultaneous threads.
##     - The implementation of this function should be lock-free.
class xe_host_pfn_t(c_void_p):
    pass

###############################################################################
## @brief API version of ::xe_sampler_desc_t
class xe_sampler_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xe_sampler_desc_version_t(c_int):
    def __str__(self):
        return str(xe_sampler_desc_version_v(value))


###############################################################################
## @brief Sampler addressing modes
class xe_sampler_address_mode_v(IntEnum):
    NONE = 0                                        ## No coordinate modifications for out-of-bounds image access.
    REPEAT = auto()                                 ## Out-of-bounds coordinates are wrapped back around.
    CLAMP = auto()                                  ## Out-of-bounds coordinates are clamped to edge.
    MIRROR = auto()                                 ## Out-of-bounds coordinates are mirrored starting from edge.

class xe_sampler_address_mode_t(c_int):
    def __str__(self):
        return str(xe_sampler_address_mode_v(value))


###############################################################################
## @brief Sampler filtering modes
class xe_sampler_filter_mode_v(IntEnum):
    NEAREST = 0                                     ## No coordinate modifications for out of bounds image access.
    LINEAR = auto()                                 ## Out-of-bounds coordinates are wrapped back around.

class xe_sampler_filter_mode_t(c_int):
    def __str__(self):
        return str(xe_sampler_filter_mode_v(value))


###############################################################################
## @brief Sampler descriptor
class xe_sampler_desc_t(Structure):
    _fields_ = [
        ("version", xe_sampler_desc_version_t),                         ## [in] ::XE_SAMPLER_DESC_VERSION_CURRENT
        ("addressMode", xe_sampler_address_mode_t),                     ## [in] Sampler addressing mode to determine how out-of-bounds
                                                                        ## coordinates are handled.
        ("filterMode", xe_sampler_filter_mode_t),                       ## [in] Sampler filter mode to determine how samples are filtered.
        ("isNormalized", xe_bool_t)                                     ## [in] Are coordinates normalized [0, 1] or not.
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
## @brief Function-pointer for xeInit
if __use_win_types:
    _xeInit_t = WINFUNCTYPE( xe_result_t, xe_init_flag_t )
else:
    _xeInit_t = CFUNCTYPE( xe_result_t, xe_init_flag_t )


###############################################################################
## @brief Table of Global functions pointers
class _xe_global_dditable_t(Structure):
    _fields_ = [
        ("pfnInit", c_void_p)                                           ## _xeInit_t
    ]

###############################################################################
## @brief Function-pointer for xeDeviceGet
if __use_win_types:
    _xeDeviceGet_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(c_ulong), POINTER(xe_device_handle_t) )
else:
    _xeDeviceGet_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(c_ulong), POINTER(xe_device_handle_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGetSubDevices
if __use_win_types:
    _xeDeviceGetSubDevices_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(c_ulong), POINTER(xe_device_handle_t) )
else:
    _xeDeviceGetSubDevices_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(c_ulong), POINTER(xe_device_handle_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGetP2PProperties
if __use_win_types:
    _xeDeviceGetP2PProperties_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, xe_device_handle_t, POINTER(xe_device_p2p_properties_t) )
else:
    _xeDeviceGetP2PProperties_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, xe_device_handle_t, POINTER(xe_device_p2p_properties_t) )

###############################################################################
## @brief Function-pointer for xeDeviceCanAccessPeer
if __use_win_types:
    _xeDeviceCanAccessPeer_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, xe_device_handle_t, POINTER(xe_bool_t) )
else:
    _xeDeviceCanAccessPeer_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, xe_device_handle_t, POINTER(xe_bool_t) )

###############################################################################
## @brief Function-pointer for xeDeviceSetIntermediateCacheConfig
if __use_win_types:
    _xeDeviceSetIntermediateCacheConfig_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, xe_cache_config_t )
else:
    _xeDeviceSetIntermediateCacheConfig_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, xe_cache_config_t )

###############################################################################
## @brief Function-pointer for xeDeviceSetLastLevelCacheConfig
if __use_win_types:
    _xeDeviceSetLastLevelCacheConfig_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, xe_cache_config_t )
else:
    _xeDeviceSetLastLevelCacheConfig_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, xe_cache_config_t )

###############################################################################
## @brief Function-pointer for xeDeviceSystemBarrier
if __use_win_types:
    _xeDeviceSystemBarrier_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t )
else:
    _xeDeviceSystemBarrier_t = CFUNCTYPE( xe_result_t, xe_device_handle_t )

###############################################################################
## @brief Function-pointer for xeDeviceRegisterCLMemory

###############################################################################
## @brief Function-pointer for xeDeviceRegisterCLProgram

###############################################################################
## @brief Function-pointer for xeDeviceRegisterCLCommandQueue

###############################################################################
## @brief Function-pointer for xeDeviceMakeMemoryResident
if __use_win_types:
    _xeDeviceMakeMemoryResident_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, c_void_p, c_size_t )
else:
    _xeDeviceMakeMemoryResident_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, c_void_p, c_size_t )

###############################################################################
## @brief Function-pointer for xeDeviceEvictMemory
if __use_win_types:
    _xeDeviceEvictMemory_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, c_void_p, c_size_t )
else:
    _xeDeviceEvictMemory_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, c_void_p, c_size_t )

###############################################################################
## @brief Function-pointer for xeDeviceMakeImageResident
if __use_win_types:
    _xeDeviceMakeImageResident_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, xe_image_handle_t )
else:
    _xeDeviceMakeImageResident_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, xe_image_handle_t )

###############################################################################
## @brief Function-pointer for xeDeviceEvictImage
if __use_win_types:
    _xeDeviceEvictImage_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, xe_image_handle_t )
else:
    _xeDeviceEvictImage_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, xe_image_handle_t )


###############################################################################
## @brief Table of Device functions pointers
class _xe_device_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _xeDeviceGet_t
        ("pfnGetSubDevices", c_void_p),                                 ## _xeDeviceGetSubDevices_t
        ("pfnGetP2PProperties", c_void_p),                              ## _xeDeviceGetP2PProperties_t
        ("pfnCanAccessPeer", c_void_p),                                 ## _xeDeviceCanAccessPeer_t
        ("pfnSetIntermediateCacheConfig", c_void_p),                    ## _xeDeviceSetIntermediateCacheConfig_t
        ("pfnSetLastLevelCacheConfig", c_void_p),                       ## _xeDeviceSetLastLevelCacheConfig_t
        ("pfnSystemBarrier", c_void_p),                                 ## _xeDeviceSystemBarrier_t
        ("pfnMakeMemoryResident", c_void_p),                            ## _xeDeviceMakeMemoryResident_t
        ("pfnEvictMemory", c_void_p),                                   ## _xeDeviceEvictMemory_t
        ("pfnMakeImageResident", c_void_p),                             ## _xeDeviceMakeImageResident_t
        ("pfnEvictImage", c_void_p)                                     ## _xeDeviceEvictImage_t
    ]

###############################################################################
## @brief Function-pointer for xeDeviceGroupGet
if __use_win_types:
    _xeDeviceGroupGet_t = WINFUNCTYPE( xe_result_t, POINTER(c_ulong), POINTER(xe_device_group_handle_t) )
else:
    _xeDeviceGroupGet_t = CFUNCTYPE( xe_result_t, POINTER(c_ulong), POINTER(xe_device_group_handle_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetDriverVersion
if __use_win_types:
    _xeDeviceGroupGetDriverVersion_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(c_ulong) )
else:
    _xeDeviceGroupGetDriverVersion_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetApiVersion
if __use_win_types:
    _xeDeviceGroupGetApiVersion_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_api_version_t) )
else:
    _xeDeviceGroupGetApiVersion_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_api_version_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetDeviceProperties
if __use_win_types:
    _xeDeviceGroupGetDeviceProperties_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_properties_t) )
else:
    _xeDeviceGroupGetDeviceProperties_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_properties_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetComputeProperties
if __use_win_types:
    _xeDeviceGroupGetComputeProperties_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_compute_properties_t) )
else:
    _xeDeviceGroupGetComputeProperties_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_compute_properties_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetMemoryProperties
if __use_win_types:
    _xeDeviceGroupGetMemoryProperties_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(c_ulong), POINTER(xe_device_memory_properties_t) )
else:
    _xeDeviceGroupGetMemoryProperties_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(c_ulong), POINTER(xe_device_memory_properties_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetMemoryAccessProperties
if __use_win_types:
    _xeDeviceGroupGetMemoryAccessProperties_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_memory_access_properties_t) )
else:
    _xeDeviceGroupGetMemoryAccessProperties_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_memory_access_properties_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetCacheProperties
if __use_win_types:
    _xeDeviceGroupGetCacheProperties_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_cache_properties_t) )
else:
    _xeDeviceGroupGetCacheProperties_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_cache_properties_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetImageProperties
if __use_win_types:
    _xeDeviceGroupGetImageProperties_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_image_properties_t) )
else:
    _xeDeviceGroupGetImageProperties_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_image_properties_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetIPCProperties
if __use_win_types:
    _xeDeviceGroupGetIPCProperties_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_ipc_properties_t) )
else:
    _xeDeviceGroupGetIPCProperties_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_device_ipc_properties_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupAllocSharedMem
if __use_win_types:
    _xeDeviceGroupAllocSharedMem_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, xe_device_handle_t, xe_device_mem_alloc_flag_t, c_ulong, xe_host_mem_alloc_flag_t, c_size_t, c_size_t, POINTER(c_void_p) )
else:
    _xeDeviceGroupAllocSharedMem_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, xe_device_handle_t, xe_device_mem_alloc_flag_t, c_ulong, xe_host_mem_alloc_flag_t, c_size_t, c_size_t, POINTER(c_void_p) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupAllocDeviceMem
if __use_win_types:
    _xeDeviceGroupAllocDeviceMem_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, xe_device_handle_t, xe_device_mem_alloc_flag_t, c_ulong, c_size_t, c_size_t, POINTER(c_void_p) )
else:
    _xeDeviceGroupAllocDeviceMem_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, xe_device_handle_t, xe_device_mem_alloc_flag_t, c_ulong, c_size_t, c_size_t, POINTER(c_void_p) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupAllocHostMem
if __use_win_types:
    _xeDeviceGroupAllocHostMem_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, xe_host_mem_alloc_flag_t, c_size_t, c_size_t, POINTER(c_void_p) )
else:
    _xeDeviceGroupAllocHostMem_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, xe_host_mem_alloc_flag_t, c_size_t, c_size_t, POINTER(c_void_p) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupFreeMem
if __use_win_types:
    _xeDeviceGroupFreeMem_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, c_void_p )
else:
    _xeDeviceGroupFreeMem_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, c_void_p )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetMemProperties
if __use_win_types:
    _xeDeviceGroupGetMemProperties_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, c_void_p, POINTER(xe_memory_allocation_properties_t), POINTER(xe_device_handle_t) )
else:
    _xeDeviceGroupGetMemProperties_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, c_void_p, POINTER(xe_memory_allocation_properties_t), POINTER(xe_device_handle_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetMemAddressRange
if __use_win_types:
    _xeDeviceGroupGetMemAddressRange_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, c_void_p, POINTER(c_void_p), POINTER(c_size_t) )
else:
    _xeDeviceGroupGetMemAddressRange_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, c_void_p, POINTER(c_void_p), POINTER(c_size_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupGetMemIpcHandle
if __use_win_types:
    _xeDeviceGroupGetMemIpcHandle_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, c_void_p, POINTER(xe_ipc_mem_handle_t) )
else:
    _xeDeviceGroupGetMemIpcHandle_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, c_void_p, POINTER(xe_ipc_mem_handle_t) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupOpenMemIpcHandle
if __use_win_types:
    _xeDeviceGroupOpenMemIpcHandle_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, xe_device_handle_t, xe_ipc_mem_handle_t, xe_ipc_memory_flag_t, POINTER(c_void_p) )
else:
    _xeDeviceGroupOpenMemIpcHandle_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, xe_device_handle_t, xe_ipc_mem_handle_t, xe_ipc_memory_flag_t, POINTER(c_void_p) )

###############################################################################
## @brief Function-pointer for xeDeviceGroupCloseMemIpcHandle
if __use_win_types:
    _xeDeviceGroupCloseMemIpcHandle_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, c_void_p )
else:
    _xeDeviceGroupCloseMemIpcHandle_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, c_void_p )


###############################################################################
## @brief Table of DeviceGroup functions pointers
class _xe_device_group_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _xeDeviceGroupGet_t
        ("pfnGetDriverVersion", c_void_p),                              ## _xeDeviceGroupGetDriverVersion_t
        ("pfnGetApiVersion", c_void_p),                                 ## _xeDeviceGroupGetApiVersion_t
        ("pfnGetDeviceProperties", c_void_p),                           ## _xeDeviceGroupGetDeviceProperties_t
        ("pfnGetComputeProperties", c_void_p),                          ## _xeDeviceGroupGetComputeProperties_t
        ("pfnGetMemoryProperties", c_void_p),                           ## _xeDeviceGroupGetMemoryProperties_t
        ("pfnGetMemoryAccessProperties", c_void_p),                     ## _xeDeviceGroupGetMemoryAccessProperties_t
        ("pfnGetCacheProperties", c_void_p),                            ## _xeDeviceGroupGetCacheProperties_t
        ("pfnGetImageProperties", c_void_p),                            ## _xeDeviceGroupGetImageProperties_t
        ("pfnGetIPCProperties", c_void_p),                              ## _xeDeviceGroupGetIPCProperties_t
        ("pfnAllocSharedMem", c_void_p),                                ## _xeDeviceGroupAllocSharedMem_t
        ("pfnAllocDeviceMem", c_void_p),                                ## _xeDeviceGroupAllocDeviceMem_t
        ("pfnAllocHostMem", c_void_p),                                  ## _xeDeviceGroupAllocHostMem_t
        ("pfnFreeMem", c_void_p),                                       ## _xeDeviceGroupFreeMem_t
        ("pfnGetMemProperties", c_void_p),                              ## _xeDeviceGroupGetMemProperties_t
        ("pfnGetMemAddressRange", c_void_p),                            ## _xeDeviceGroupGetMemAddressRange_t
        ("pfnGetMemIpcHandle", c_void_p),                               ## _xeDeviceGroupGetMemIpcHandle_t
        ("pfnOpenMemIpcHandle", c_void_p),                              ## _xeDeviceGroupOpenMemIpcHandle_t
        ("pfnCloseMemIpcHandle", c_void_p)                              ## _xeDeviceGroupCloseMemIpcHandle_t
    ]

###############################################################################
## @brief Function-pointer for xeCommandQueueCreate
if __use_win_types:
    _xeCommandQueueCreate_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_command_queue_desc_t), POINTER(xe_command_queue_handle_t) )
else:
    _xeCommandQueueCreate_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_command_queue_desc_t), POINTER(xe_command_queue_handle_t) )

###############################################################################
## @brief Function-pointer for xeCommandQueueDestroy
if __use_win_types:
    _xeCommandQueueDestroy_t = WINFUNCTYPE( xe_result_t, xe_command_queue_handle_t )
else:
    _xeCommandQueueDestroy_t = CFUNCTYPE( xe_result_t, xe_command_queue_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandQueueExecuteCommandLists
if __use_win_types:
    _xeCommandQueueExecuteCommandLists_t = WINFUNCTYPE( xe_result_t, xe_command_queue_handle_t, c_ulong, POINTER(xe_command_list_handle_t), xe_fence_handle_t )
else:
    _xeCommandQueueExecuteCommandLists_t = CFUNCTYPE( xe_result_t, xe_command_queue_handle_t, c_ulong, POINTER(xe_command_list_handle_t), xe_fence_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandQueueSynchronize
if __use_win_types:
    _xeCommandQueueSynchronize_t = WINFUNCTYPE( xe_result_t, xe_command_queue_handle_t, c_ulong )
else:
    _xeCommandQueueSynchronize_t = CFUNCTYPE( xe_result_t, xe_command_queue_handle_t, c_ulong )


###############################################################################
## @brief Table of CommandQueue functions pointers
class _xe_command_queue_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xeCommandQueueCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xeCommandQueueDestroy_t
        ("pfnExecuteCommandLists", c_void_p),                           ## _xeCommandQueueExecuteCommandLists_t
        ("pfnSynchronize", c_void_p)                                    ## _xeCommandQueueSynchronize_t
    ]

###############################################################################
## @brief Function-pointer for xeCommandListCreate
if __use_win_types:
    _xeCommandListCreate_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_command_list_desc_t), POINTER(xe_command_list_handle_t) )
else:
    _xeCommandListCreate_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_command_list_desc_t), POINTER(xe_command_list_handle_t) )

###############################################################################
## @brief Function-pointer for xeCommandListCreateImmediate
if __use_win_types:
    _xeCommandListCreateImmediate_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_command_queue_desc_t), POINTER(xe_command_list_handle_t) )
else:
    _xeCommandListCreateImmediate_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_command_queue_desc_t), POINTER(xe_command_list_handle_t) )

###############################################################################
## @brief Function-pointer for xeCommandListDestroy
if __use_win_types:
    _xeCommandListDestroy_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t )
else:
    _xeCommandListDestroy_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListClose
if __use_win_types:
    _xeCommandListClose_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t )
else:
    _xeCommandListClose_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListReset
if __use_win_types:
    _xeCommandListReset_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t )
else:
    _xeCommandListReset_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListSetParameter
if __use_win_types:
    _xeCommandListSetParameter_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_command_list_parameter_t, c_ulong )
else:
    _xeCommandListSetParameter_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_command_list_parameter_t, c_ulong )

###############################################################################
## @brief Function-pointer for xeCommandListGetParameter
if __use_win_types:
    _xeCommandListGetParameter_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_command_list_parameter_t, POINTER(c_ulong) )
else:
    _xeCommandListGetParameter_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_command_list_parameter_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xeCommandListResetParameters
if __use_win_types:
    _xeCommandListResetParameters_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t )
else:
    _xeCommandListResetParameters_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendBarrier
if __use_win_types:
    _xeCommandListAppendBarrier_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )
else:
    _xeCommandListAppendBarrier_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )

###############################################################################
## @brief Function-pointer for xeCommandListAppendMemoryRangesBarrier
if __use_win_types:
    _xeCommandListAppendMemoryRangesBarrier_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_ulong, POINTER(c_size_t), POINTER(c_void_p), xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )
else:
    _xeCommandListAppendMemoryRangesBarrier_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_ulong, POINTER(c_size_t), POINTER(c_void_p), xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )

###############################################################################
## @brief Function-pointer for xeCommandListAppendMemoryCopy
if __use_win_types:
    _xeCommandListAppendMemoryCopy_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_void_p, c_void_p, c_size_t, xe_event_handle_t )
else:
    _xeCommandListAppendMemoryCopy_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_void_p, c_void_p, c_size_t, xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendMemorySet
if __use_win_types:
    _xeCommandListAppendMemorySet_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_void_p, c_int, c_size_t, xe_event_handle_t )
else:
    _xeCommandListAppendMemorySet_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_void_p, c_int, c_size_t, xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendMemoryCopyRegion
if __use_win_types:
    _xeCommandListAppendMemoryCopyRegion_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_void_p, POINTER(xe_copy_region_t), c_ulong, c_void_p, POINTER(xe_copy_region_t), c_ulong, xe_event_handle_t )
else:
    _xeCommandListAppendMemoryCopyRegion_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_void_p, POINTER(xe_copy_region_t), c_ulong, c_void_p, POINTER(xe_copy_region_t), c_ulong, xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendImageCopy
if __use_win_types:
    _xeCommandListAppendImageCopy_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_image_handle_t, xe_image_handle_t, xe_event_handle_t )
else:
    _xeCommandListAppendImageCopy_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_image_handle_t, xe_image_handle_t, xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendImageCopyRegion
if __use_win_types:
    _xeCommandListAppendImageCopyRegion_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_image_handle_t, xe_image_handle_t, POINTER(xe_image_region_t), POINTER(xe_image_region_t), xe_event_handle_t )
else:
    _xeCommandListAppendImageCopyRegion_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_image_handle_t, xe_image_handle_t, POINTER(xe_image_region_t), POINTER(xe_image_region_t), xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendImageCopyToMemory
if __use_win_types:
    _xeCommandListAppendImageCopyToMemory_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_void_p, xe_image_handle_t, POINTER(xe_image_region_t), xe_event_handle_t )
else:
    _xeCommandListAppendImageCopyToMemory_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_void_p, xe_image_handle_t, POINTER(xe_image_region_t), xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendImageCopyFromMemory
if __use_win_types:
    _xeCommandListAppendImageCopyFromMemory_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_image_handle_t, c_void_p, POINTER(xe_image_region_t), xe_event_handle_t )
else:
    _xeCommandListAppendImageCopyFromMemory_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_image_handle_t, c_void_p, POINTER(xe_image_region_t), xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendMemoryPrefetch
if __use_win_types:
    _xeCommandListAppendMemoryPrefetch_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_void_p, c_size_t )
else:
    _xeCommandListAppendMemoryPrefetch_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_void_p, c_size_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendMemAdvise
if __use_win_types:
    _xeCommandListAppendMemAdvise_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_device_handle_t, c_void_p, c_size_t, xe_memory_advice_t )
else:
    _xeCommandListAppendMemAdvise_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_device_handle_t, c_void_p, c_size_t, xe_memory_advice_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendSignalEvent
if __use_win_types:
    _xeCommandListAppendSignalEvent_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_event_handle_t )
else:
    _xeCommandListAppendSignalEvent_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendWaitOnEvents
if __use_win_types:
    _xeCommandListAppendWaitOnEvents_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_ulong, POINTER(xe_event_handle_t) )
else:
    _xeCommandListAppendWaitOnEvents_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_ulong, POINTER(xe_event_handle_t) )

###############################################################################
## @brief Function-pointer for xeCommandListAppendEventReset
if __use_win_types:
    _xeCommandListAppendEventReset_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_event_handle_t )
else:
    _xeCommandListAppendEventReset_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeCommandListAppendLaunchFunction
if __use_win_types:
    _xeCommandListAppendLaunchFunction_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_function_handle_t, POINTER(xe_thread_group_dimensions_t), xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )
else:
    _xeCommandListAppendLaunchFunction_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_function_handle_t, POINTER(xe_thread_group_dimensions_t), xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )

###############################################################################
## @brief Function-pointer for xeCommandListAppendLaunchFunctionIndirect
if __use_win_types:
    _xeCommandListAppendLaunchFunctionIndirect_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_function_handle_t, POINTER(xe_thread_group_dimensions_t), xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )
else:
    _xeCommandListAppendLaunchFunctionIndirect_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_function_handle_t, POINTER(xe_thread_group_dimensions_t), xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )

###############################################################################
## @brief Function-pointer for xeCommandListAppendLaunchMultipleFunctionsIndirect
if __use_win_types:
    _xeCommandListAppendLaunchMultipleFunctionsIndirect_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_ulong, POINTER(xe_function_handle_t), POINTER(c_ulong), POINTER(xe_thread_group_dimensions_t), xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )
else:
    _xeCommandListAppendLaunchMultipleFunctionsIndirect_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, c_ulong, POINTER(xe_function_handle_t), POINTER(c_ulong), POINTER(xe_thread_group_dimensions_t), xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )

###############################################################################
## @brief Function-pointer for xeCommandListAppendLaunchHostFunction
if __use_win_types:
    _xeCommandListAppendLaunchHostFunction_t = WINFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_host_pfn_t, c_void_p, xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )
else:
    _xeCommandListAppendLaunchHostFunction_t = CFUNCTYPE( xe_result_t, xe_command_list_handle_t, xe_host_pfn_t, c_void_p, xe_event_handle_t, c_ulong, POINTER(xe_event_handle_t) )


###############################################################################
## @brief Table of CommandList functions pointers
class _xe_command_list_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xeCommandListCreate_t
        ("pfnCreateImmediate", c_void_p),                               ## _xeCommandListCreateImmediate_t
        ("pfnDestroy", c_void_p),                                       ## _xeCommandListDestroy_t
        ("pfnClose", c_void_p),                                         ## _xeCommandListClose_t
        ("pfnReset", c_void_p),                                         ## _xeCommandListReset_t
        ("pfnSetParameter", c_void_p),                                  ## _xeCommandListSetParameter_t
        ("pfnGetParameter", c_void_p),                                  ## _xeCommandListGetParameter_t
        ("pfnResetParameters", c_void_p),                               ## _xeCommandListResetParameters_t
        ("pfnAppendBarrier", c_void_p),                                 ## _xeCommandListAppendBarrier_t
        ("pfnAppendMemoryRangesBarrier", c_void_p),                     ## _xeCommandListAppendMemoryRangesBarrier_t
        ("pfnAppendMemoryCopy", c_void_p),                              ## _xeCommandListAppendMemoryCopy_t
        ("pfnAppendMemorySet", c_void_p),                               ## _xeCommandListAppendMemorySet_t
        ("pfnAppendMemoryCopyRegion", c_void_p),                        ## _xeCommandListAppendMemoryCopyRegion_t
        ("pfnAppendImageCopy", c_void_p),                               ## _xeCommandListAppendImageCopy_t
        ("pfnAppendImageCopyRegion", c_void_p),                         ## _xeCommandListAppendImageCopyRegion_t
        ("pfnAppendImageCopyToMemory", c_void_p),                       ## _xeCommandListAppendImageCopyToMemory_t
        ("pfnAppendImageCopyFromMemory", c_void_p),                     ## _xeCommandListAppendImageCopyFromMemory_t
        ("pfnAppendMemoryPrefetch", c_void_p),                          ## _xeCommandListAppendMemoryPrefetch_t
        ("pfnAppendMemAdvise", c_void_p),                               ## _xeCommandListAppendMemAdvise_t
        ("pfnAppendSignalEvent", c_void_p),                             ## _xeCommandListAppendSignalEvent_t
        ("pfnAppendWaitOnEvents", c_void_p),                            ## _xeCommandListAppendWaitOnEvents_t
        ("pfnAppendEventReset", c_void_p),                              ## _xeCommandListAppendEventReset_t
        ("pfnAppendLaunchFunction", c_void_p),                          ## _xeCommandListAppendLaunchFunction_t
        ("pfnAppendLaunchFunctionIndirect", c_void_p),                  ## _xeCommandListAppendLaunchFunctionIndirect_t
        ("pfnAppendLaunchMultipleFunctionsIndirect", c_void_p),         ## _xeCommandListAppendLaunchMultipleFunctionsIndirect_t
        ("pfnAppendLaunchHostFunction", c_void_p)                       ## _xeCommandListAppendLaunchHostFunction_t
    ]

###############################################################################
## @brief Function-pointer for xeFenceCreate
if __use_win_types:
    _xeFenceCreate_t = WINFUNCTYPE( xe_result_t, xe_command_queue_handle_t, POINTER(xe_fence_desc_t), POINTER(xe_fence_handle_t) )
else:
    _xeFenceCreate_t = CFUNCTYPE( xe_result_t, xe_command_queue_handle_t, POINTER(xe_fence_desc_t), POINTER(xe_fence_handle_t) )

###############################################################################
## @brief Function-pointer for xeFenceDestroy
if __use_win_types:
    _xeFenceDestroy_t = WINFUNCTYPE( xe_result_t, xe_fence_handle_t )
else:
    _xeFenceDestroy_t = CFUNCTYPE( xe_result_t, xe_fence_handle_t )

###############################################################################
## @brief Function-pointer for xeFenceHostSynchronize
if __use_win_types:
    _xeFenceHostSynchronize_t = WINFUNCTYPE( xe_result_t, xe_fence_handle_t, c_ulong )
else:
    _xeFenceHostSynchronize_t = CFUNCTYPE( xe_result_t, xe_fence_handle_t, c_ulong )

###############################################################################
## @brief Function-pointer for xeFenceQueryStatus
if __use_win_types:
    _xeFenceQueryStatus_t = WINFUNCTYPE( xe_result_t, xe_fence_handle_t )
else:
    _xeFenceQueryStatus_t = CFUNCTYPE( xe_result_t, xe_fence_handle_t )

###############################################################################
## @brief Function-pointer for xeFenceReset
if __use_win_types:
    _xeFenceReset_t = WINFUNCTYPE( xe_result_t, xe_fence_handle_t )
else:
    _xeFenceReset_t = CFUNCTYPE( xe_result_t, xe_fence_handle_t )


###############################################################################
## @brief Table of Fence functions pointers
class _xe_fence_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xeFenceCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xeFenceDestroy_t
        ("pfnHostSynchronize", c_void_p),                               ## _xeFenceHostSynchronize_t
        ("pfnQueryStatus", c_void_p),                                   ## _xeFenceQueryStatus_t
        ("pfnReset", c_void_p)                                          ## _xeFenceReset_t
    ]

###############################################################################
## @brief Function-pointer for xeEventPoolCreate
if __use_win_types:
    _xeEventPoolCreate_t = WINFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_event_pool_desc_t), c_ulong, POINTER(xe_device_handle_t), POINTER(xe_event_pool_handle_t) )
else:
    _xeEventPoolCreate_t = CFUNCTYPE( xe_result_t, xe_device_group_handle_t, POINTER(xe_event_pool_desc_t), c_ulong, POINTER(xe_device_handle_t), POINTER(xe_event_pool_handle_t) )

###############################################################################
## @brief Function-pointer for xeEventPoolDestroy
if __use_win_types:
    _xeEventPoolDestroy_t = WINFUNCTYPE( xe_result_t, xe_event_pool_handle_t )
else:
    _xeEventPoolDestroy_t = CFUNCTYPE( xe_result_t, xe_event_pool_handle_t )

###############################################################################
## @brief Function-pointer for xeEventPoolGetIpcHandle
if __use_win_types:
    _xeEventPoolGetIpcHandle_t = WINFUNCTYPE( xe_result_t, xe_event_pool_handle_t, POINTER(xe_ipc_event_pool_handle_t) )
else:
    _xeEventPoolGetIpcHandle_t = CFUNCTYPE( xe_result_t, xe_event_pool_handle_t, POINTER(xe_ipc_event_pool_handle_t) )

###############################################################################
## @brief Function-pointer for xeEventPoolOpenIpcHandle
if __use_win_types:
    _xeEventPoolOpenIpcHandle_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, xe_ipc_event_pool_handle_t, POINTER(xe_event_pool_handle_t) )
else:
    _xeEventPoolOpenIpcHandle_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, xe_ipc_event_pool_handle_t, POINTER(xe_event_pool_handle_t) )

###############################################################################
## @brief Function-pointer for xeEventPoolCloseIpcHandle
if __use_win_types:
    _xeEventPoolCloseIpcHandle_t = WINFUNCTYPE( xe_result_t, xe_event_pool_handle_t )
else:
    _xeEventPoolCloseIpcHandle_t = CFUNCTYPE( xe_result_t, xe_event_pool_handle_t )


###############################################################################
## @brief Table of EventPool functions pointers
class _xe_event_pool_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xeEventPoolCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xeEventPoolDestroy_t
        ("pfnGetIpcHandle", c_void_p),                                  ## _xeEventPoolGetIpcHandle_t
        ("pfnOpenIpcHandle", c_void_p),                                 ## _xeEventPoolOpenIpcHandle_t
        ("pfnCloseIpcHandle", c_void_p)                                 ## _xeEventPoolCloseIpcHandle_t
    ]

###############################################################################
## @brief Function-pointer for xeEventCreate
if __use_win_types:
    _xeEventCreate_t = WINFUNCTYPE( xe_result_t, xe_event_pool_handle_t, POINTER(xe_event_desc_t), POINTER(xe_event_handle_t) )
else:
    _xeEventCreate_t = CFUNCTYPE( xe_result_t, xe_event_pool_handle_t, POINTER(xe_event_desc_t), POINTER(xe_event_handle_t) )

###############################################################################
## @brief Function-pointer for xeEventDestroy
if __use_win_types:
    _xeEventDestroy_t = WINFUNCTYPE( xe_result_t, xe_event_handle_t )
else:
    _xeEventDestroy_t = CFUNCTYPE( xe_result_t, xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeEventHostSignal
if __use_win_types:
    _xeEventHostSignal_t = WINFUNCTYPE( xe_result_t, xe_event_handle_t )
else:
    _xeEventHostSignal_t = CFUNCTYPE( xe_result_t, xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeEventHostSynchronize
if __use_win_types:
    _xeEventHostSynchronize_t = WINFUNCTYPE( xe_result_t, xe_event_handle_t, c_ulong )
else:
    _xeEventHostSynchronize_t = CFUNCTYPE( xe_result_t, xe_event_handle_t, c_ulong )

###############################################################################
## @brief Function-pointer for xeEventQueryStatus
if __use_win_types:
    _xeEventQueryStatus_t = WINFUNCTYPE( xe_result_t, xe_event_handle_t )
else:
    _xeEventQueryStatus_t = CFUNCTYPE( xe_result_t, xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xeEventReset
if __use_win_types:
    _xeEventReset_t = WINFUNCTYPE( xe_result_t, xe_event_handle_t )
else:
    _xeEventReset_t = CFUNCTYPE( xe_result_t, xe_event_handle_t )


###############################################################################
## @brief Table of Event functions pointers
class _xe_event_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xeEventCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xeEventDestroy_t
        ("pfnHostSignal", c_void_p),                                    ## _xeEventHostSignal_t
        ("pfnHostSynchronize", c_void_p),                               ## _xeEventHostSynchronize_t
        ("pfnQueryStatus", c_void_p),                                   ## _xeEventQueryStatus_t
        ("pfnReset", c_void_p)                                          ## _xeEventReset_t
    ]

###############################################################################
## @brief Function-pointer for xeImageGetProperties
if __use_win_types:
    _xeImageGetProperties_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_image_desc_t), POINTER(xe_image_properties_t) )
else:
    _xeImageGetProperties_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_image_desc_t), POINTER(xe_image_properties_t) )

###############################################################################
## @brief Function-pointer for xeImageCreate
if __use_win_types:
    _xeImageCreate_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_image_desc_t), POINTER(xe_image_handle_t) )
else:
    _xeImageCreate_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_image_desc_t), POINTER(xe_image_handle_t) )

###############################################################################
## @brief Function-pointer for xeImageDestroy
if __use_win_types:
    _xeImageDestroy_t = WINFUNCTYPE( xe_result_t, xe_image_handle_t )
else:
    _xeImageDestroy_t = CFUNCTYPE( xe_result_t, xe_image_handle_t )


###############################################################################
## @brief Table of Image functions pointers
class _xe_image_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xeImageGetProperties_t
        ("pfnCreate", c_void_p),                                        ## _xeImageCreate_t
        ("pfnDestroy", c_void_p)                                        ## _xeImageDestroy_t
    ]

###############################################################################
## @brief Function-pointer for xeModuleCreate
if __use_win_types:
    _xeModuleCreate_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_module_desc_t), POINTER(xe_module_handle_t), POINTER(xe_module_build_log_handle_t) )
else:
    _xeModuleCreate_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_module_desc_t), POINTER(xe_module_handle_t), POINTER(xe_module_build_log_handle_t) )

###############################################################################
## @brief Function-pointer for xeModuleDestroy
if __use_win_types:
    _xeModuleDestroy_t = WINFUNCTYPE( xe_result_t, xe_module_handle_t )
else:
    _xeModuleDestroy_t = CFUNCTYPE( xe_result_t, xe_module_handle_t )

###############################################################################
## @brief Function-pointer for xeModuleGetNativeBinary
if __use_win_types:
    _xeModuleGetNativeBinary_t = WINFUNCTYPE( xe_result_t, xe_module_handle_t, POINTER(c_size_t), POINTER(c_ubyte) )
else:
    _xeModuleGetNativeBinary_t = CFUNCTYPE( xe_result_t, xe_module_handle_t, POINTER(c_size_t), POINTER(c_ubyte) )

###############################################################################
## @brief Function-pointer for xeModuleGetGlobalPointer
if __use_win_types:
    _xeModuleGetGlobalPointer_t = WINFUNCTYPE( xe_result_t, xe_module_handle_t, POINTER(c_char), POINTER(c_void_p) )
else:
    _xeModuleGetGlobalPointer_t = CFUNCTYPE( xe_result_t, xe_module_handle_t, POINTER(c_char), POINTER(c_void_p) )

###############################################################################
## @brief Function-pointer for xeModuleGetFunctionPointer
if __use_win_types:
    _xeModuleGetFunctionPointer_t = WINFUNCTYPE( xe_result_t, xe_module_handle_t, POINTER(c_char), POINTER(c_void_p) )
else:
    _xeModuleGetFunctionPointer_t = CFUNCTYPE( xe_result_t, xe_module_handle_t, POINTER(c_char), POINTER(c_void_p) )


###############################################################################
## @brief Table of Module functions pointers
class _xe_module_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xeModuleCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xeModuleDestroy_t
        ("pfnGetNativeBinary", c_void_p),                               ## _xeModuleGetNativeBinary_t
        ("pfnGetGlobalPointer", c_void_p),                              ## _xeModuleGetGlobalPointer_t
        ("pfnGetFunctionPointer", c_void_p)                             ## _xeModuleGetFunctionPointer_t
    ]

###############################################################################
## @brief Function-pointer for xeModuleBuildLogDestroy
if __use_win_types:
    _xeModuleBuildLogDestroy_t = WINFUNCTYPE( xe_result_t, xe_module_build_log_handle_t )
else:
    _xeModuleBuildLogDestroy_t = CFUNCTYPE( xe_result_t, xe_module_build_log_handle_t )

###############################################################################
## @brief Function-pointer for xeModuleBuildLogGetString
if __use_win_types:
    _xeModuleBuildLogGetString_t = WINFUNCTYPE( xe_result_t, xe_module_build_log_handle_t, POINTER(c_size_t), POINTER(c_char) )
else:
    _xeModuleBuildLogGetString_t = CFUNCTYPE( xe_result_t, xe_module_build_log_handle_t, POINTER(c_size_t), POINTER(c_char) )


###############################################################################
## @brief Table of ModuleBuildLog functions pointers
class _xe_module_build_log_dditable_t(Structure):
    _fields_ = [
        ("pfnDestroy", c_void_p),                                       ## _xeModuleBuildLogDestroy_t
        ("pfnGetString", c_void_p)                                      ## _xeModuleBuildLogGetString_t
    ]

###############################################################################
## @brief Function-pointer for xeFunctionCreate
if __use_win_types:
    _xeFunctionCreate_t = WINFUNCTYPE( xe_result_t, xe_module_handle_t, POINTER(xe_function_desc_t), POINTER(xe_function_handle_t) )
else:
    _xeFunctionCreate_t = CFUNCTYPE( xe_result_t, xe_module_handle_t, POINTER(xe_function_desc_t), POINTER(xe_function_handle_t) )

###############################################################################
## @brief Function-pointer for xeFunctionDestroy
if __use_win_types:
    _xeFunctionDestroy_t = WINFUNCTYPE( xe_result_t, xe_function_handle_t )
else:
    _xeFunctionDestroy_t = CFUNCTYPE( xe_result_t, xe_function_handle_t )

###############################################################################
## @brief Function-pointer for xeFunctionSetGroupSize
if __use_win_types:
    _xeFunctionSetGroupSize_t = WINFUNCTYPE( xe_result_t, xe_function_handle_t, c_ulong, c_ulong, c_ulong )
else:
    _xeFunctionSetGroupSize_t = CFUNCTYPE( xe_result_t, xe_function_handle_t, c_ulong, c_ulong, c_ulong )

###############################################################################
## @brief Function-pointer for xeFunctionSuggestGroupSize
if __use_win_types:
    _xeFunctionSuggestGroupSize_t = WINFUNCTYPE( xe_result_t, xe_function_handle_t, c_ulong, c_ulong, c_ulong, POINTER(c_ulong), POINTER(c_ulong), POINTER(c_ulong) )
else:
    _xeFunctionSuggestGroupSize_t = CFUNCTYPE( xe_result_t, xe_function_handle_t, c_ulong, c_ulong, c_ulong, POINTER(c_ulong), POINTER(c_ulong), POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xeFunctionSetArgumentValue
if __use_win_types:
    _xeFunctionSetArgumentValue_t = WINFUNCTYPE( xe_result_t, xe_function_handle_t, c_ulong, c_size_t, c_void_p )
else:
    _xeFunctionSetArgumentValue_t = CFUNCTYPE( xe_result_t, xe_function_handle_t, c_ulong, c_size_t, c_void_p )

###############################################################################
## @brief Function-pointer for xeFunctionSetAttribute
if __use_win_types:
    _xeFunctionSetAttribute_t = WINFUNCTYPE( xe_result_t, xe_function_handle_t, xe_function_set_attribute_t, c_ulong )
else:
    _xeFunctionSetAttribute_t = CFUNCTYPE( xe_result_t, xe_function_handle_t, xe_function_set_attribute_t, c_ulong )

###############################################################################
## @brief Function-pointer for xeFunctionGetAttribute
if __use_win_types:
    _xeFunctionGetAttribute_t = WINFUNCTYPE( xe_result_t, xe_function_handle_t, xe_function_get_attribute_t, POINTER(c_ulong) )
else:
    _xeFunctionGetAttribute_t = CFUNCTYPE( xe_result_t, xe_function_handle_t, xe_function_get_attribute_t, POINTER(c_ulong) )


###############################################################################
## @brief Table of Function functions pointers
class _xe_function_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xeFunctionCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xeFunctionDestroy_t
        ("pfnSetGroupSize", c_void_p),                                  ## _xeFunctionSetGroupSize_t
        ("pfnSuggestGroupSize", c_void_p),                              ## _xeFunctionSuggestGroupSize_t
        ("pfnSetArgumentValue", c_void_p),                              ## _xeFunctionSetArgumentValue_t
        ("pfnSetAttribute", c_void_p),                                  ## _xeFunctionSetAttribute_t
        ("pfnGetAttribute", c_void_p)                                   ## _xeFunctionGetAttribute_t
    ]

###############################################################################
## @brief Function-pointer for xeSamplerCreate
if __use_win_types:
    _xeSamplerCreate_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_sampler_desc_t), POINTER(xe_sampler_handle_t) )
else:
    _xeSamplerCreate_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xe_sampler_desc_t), POINTER(xe_sampler_handle_t) )

###############################################################################
## @brief Function-pointer for xeSamplerDestroy
if __use_win_types:
    _xeSamplerDestroy_t = WINFUNCTYPE( xe_result_t, xe_sampler_handle_t )
else:
    _xeSamplerDestroy_t = CFUNCTYPE( xe_result_t, xe_sampler_handle_t )


###############################################################################
## @brief Table of Sampler functions pointers
class _xe_sampler_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xeSamplerCreate_t
        ("pfnDestroy", c_void_p)                                        ## _xeSamplerDestroy_t
    ]

###############################################################################
class _xe_dditable_t(Structure):
    _fields_ = [
        ("Global", _xe_global_dditable_t),
        ("Device", _xe_device_dditable_t),
        ("DeviceGroup", _xe_device_group_dditable_t),
        ("CommandQueue", _xe_command_queue_dditable_t),
        ("CommandList", _xe_command_list_dditable_t),
        ("Fence", _xe_fence_dditable_t),
        ("EventPool", _xe_event_pool_dditable_t),
        ("Event", _xe_event_dditable_t),
        ("Image", _xe_image_dditable_t),
        ("Module", _xe_module_dditable_t),
        ("ModuleBuildLog", _xe_module_build_log_dditable_t),
        ("Function", _xe_function_dditable_t),
        ("Sampler", _xe_sampler_dditable_t)
    ]

###############################################################################
## @brief xe device-driver interfaces
class XE_DDI:
    def __init__(self, version : xe_api_version_t):
        # load the xe_loader library
        if "Windows" == platform.uname()[0]:
            self.__dll = WinDLL("xe_loader.dll")
        else:
            self.__dll = CDLL("xe_loader.so")

        # fill the ddi tables
        self.__dditable = _xe_dditable_t()

        # call driver to get function pointers
        _Global = _xe_global_dditable_t()
        r = xe_result_v(self.__dll.xeGetGlobalProcAddrTable(version, byref(_Global)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Global = _Global

        # attach function interface to function address
        self.xeInit = _xeInit_t(self.__dditable.Global.pfnInit)

        # call driver to get function pointers
        _Device = _xe_device_dditable_t()
        r = xe_result_v(self.__dll.xeGetDeviceProcAddrTable(version, byref(_Device)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Device = _Device

        # attach function interface to function address
        self.xeDeviceGet = _xeDeviceGet_t(self.__dditable.Device.pfnGet)
        self.xeDeviceGetSubDevices = _xeDeviceGetSubDevices_t(self.__dditable.Device.pfnGetSubDevices)
        self.xeDeviceGetP2PProperties = _xeDeviceGetP2PProperties_t(self.__dditable.Device.pfnGetP2PProperties)
        self.xeDeviceCanAccessPeer = _xeDeviceCanAccessPeer_t(self.__dditable.Device.pfnCanAccessPeer)
        self.xeDeviceSetIntermediateCacheConfig = _xeDeviceSetIntermediateCacheConfig_t(self.__dditable.Device.pfnSetIntermediateCacheConfig)
        self.xeDeviceSetLastLevelCacheConfig = _xeDeviceSetLastLevelCacheConfig_t(self.__dditable.Device.pfnSetLastLevelCacheConfig)
        self.xeDeviceSystemBarrier = _xeDeviceSystemBarrier_t(self.__dditable.Device.pfnSystemBarrier)
        self.xeDeviceMakeMemoryResident = _xeDeviceMakeMemoryResident_t(self.__dditable.Device.pfnMakeMemoryResident)
        self.xeDeviceEvictMemory = _xeDeviceEvictMemory_t(self.__dditable.Device.pfnEvictMemory)
        self.xeDeviceMakeImageResident = _xeDeviceMakeImageResident_t(self.__dditable.Device.pfnMakeImageResident)
        self.xeDeviceEvictImage = _xeDeviceEvictImage_t(self.__dditable.Device.pfnEvictImage)

        # call driver to get function pointers
        _DeviceGroup = _xe_device_group_dditable_t()
        r = xe_result_v(self.__dll.xeGetDeviceGroupProcAddrTable(version, byref(_DeviceGroup)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.DeviceGroup = _DeviceGroup

        # attach function interface to function address
        self.xeDeviceGroupGet = _xeDeviceGroupGet_t(self.__dditable.DeviceGroup.pfnGet)
        self.xeDeviceGroupGetDriverVersion = _xeDeviceGroupGetDriverVersion_t(self.__dditable.DeviceGroup.pfnGetDriverVersion)
        self.xeDeviceGroupGetApiVersion = _xeDeviceGroupGetApiVersion_t(self.__dditable.DeviceGroup.pfnGetApiVersion)
        self.xeDeviceGroupGetDeviceProperties = _xeDeviceGroupGetDeviceProperties_t(self.__dditable.DeviceGroup.pfnGetDeviceProperties)
        self.xeDeviceGroupGetComputeProperties = _xeDeviceGroupGetComputeProperties_t(self.__dditable.DeviceGroup.pfnGetComputeProperties)
        self.xeDeviceGroupGetMemoryProperties = _xeDeviceGroupGetMemoryProperties_t(self.__dditable.DeviceGroup.pfnGetMemoryProperties)
        self.xeDeviceGroupGetMemoryAccessProperties = _xeDeviceGroupGetMemoryAccessProperties_t(self.__dditable.DeviceGroup.pfnGetMemoryAccessProperties)
        self.xeDeviceGroupGetCacheProperties = _xeDeviceGroupGetCacheProperties_t(self.__dditable.DeviceGroup.pfnGetCacheProperties)
        self.xeDeviceGroupGetImageProperties = _xeDeviceGroupGetImageProperties_t(self.__dditable.DeviceGroup.pfnGetImageProperties)
        self.xeDeviceGroupGetIPCProperties = _xeDeviceGroupGetIPCProperties_t(self.__dditable.DeviceGroup.pfnGetIPCProperties)
        self.xeDeviceGroupAllocSharedMem = _xeDeviceGroupAllocSharedMem_t(self.__dditable.DeviceGroup.pfnAllocSharedMem)
        self.xeDeviceGroupAllocDeviceMem = _xeDeviceGroupAllocDeviceMem_t(self.__dditable.DeviceGroup.pfnAllocDeviceMem)
        self.xeDeviceGroupAllocHostMem = _xeDeviceGroupAllocHostMem_t(self.__dditable.DeviceGroup.pfnAllocHostMem)
        self.xeDeviceGroupFreeMem = _xeDeviceGroupFreeMem_t(self.__dditable.DeviceGroup.pfnFreeMem)
        self.xeDeviceGroupGetMemProperties = _xeDeviceGroupGetMemProperties_t(self.__dditable.DeviceGroup.pfnGetMemProperties)
        self.xeDeviceGroupGetMemAddressRange = _xeDeviceGroupGetMemAddressRange_t(self.__dditable.DeviceGroup.pfnGetMemAddressRange)
        self.xeDeviceGroupGetMemIpcHandle = _xeDeviceGroupGetMemIpcHandle_t(self.__dditable.DeviceGroup.pfnGetMemIpcHandle)
        self.xeDeviceGroupOpenMemIpcHandle = _xeDeviceGroupOpenMemIpcHandle_t(self.__dditable.DeviceGroup.pfnOpenMemIpcHandle)
        self.xeDeviceGroupCloseMemIpcHandle = _xeDeviceGroupCloseMemIpcHandle_t(self.__dditable.DeviceGroup.pfnCloseMemIpcHandle)

        # call driver to get function pointers
        _CommandQueue = _xe_command_queue_dditable_t()
        r = xe_result_v(self.__dll.xeGetCommandQueueProcAddrTable(version, byref(_CommandQueue)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.CommandQueue = _CommandQueue

        # attach function interface to function address
        self.xeCommandQueueCreate = _xeCommandQueueCreate_t(self.__dditable.CommandQueue.pfnCreate)
        self.xeCommandQueueDestroy = _xeCommandQueueDestroy_t(self.__dditable.CommandQueue.pfnDestroy)
        self.xeCommandQueueExecuteCommandLists = _xeCommandQueueExecuteCommandLists_t(self.__dditable.CommandQueue.pfnExecuteCommandLists)
        self.xeCommandQueueSynchronize = _xeCommandQueueSynchronize_t(self.__dditable.CommandQueue.pfnSynchronize)

        # call driver to get function pointers
        _CommandList = _xe_command_list_dditable_t()
        r = xe_result_v(self.__dll.xeGetCommandListProcAddrTable(version, byref(_CommandList)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.CommandList = _CommandList

        # attach function interface to function address
        self.xeCommandListCreate = _xeCommandListCreate_t(self.__dditable.CommandList.pfnCreate)
        self.xeCommandListCreateImmediate = _xeCommandListCreateImmediate_t(self.__dditable.CommandList.pfnCreateImmediate)
        self.xeCommandListDestroy = _xeCommandListDestroy_t(self.__dditable.CommandList.pfnDestroy)
        self.xeCommandListClose = _xeCommandListClose_t(self.__dditable.CommandList.pfnClose)
        self.xeCommandListReset = _xeCommandListReset_t(self.__dditable.CommandList.pfnReset)
        self.xeCommandListSetParameter = _xeCommandListSetParameter_t(self.__dditable.CommandList.pfnSetParameter)
        self.xeCommandListGetParameter = _xeCommandListGetParameter_t(self.__dditable.CommandList.pfnGetParameter)
        self.xeCommandListResetParameters = _xeCommandListResetParameters_t(self.__dditable.CommandList.pfnResetParameters)
        self.xeCommandListAppendBarrier = _xeCommandListAppendBarrier_t(self.__dditable.CommandList.pfnAppendBarrier)
        self.xeCommandListAppendMemoryRangesBarrier = _xeCommandListAppendMemoryRangesBarrier_t(self.__dditable.CommandList.pfnAppendMemoryRangesBarrier)
        self.xeCommandListAppendMemoryCopy = _xeCommandListAppendMemoryCopy_t(self.__dditable.CommandList.pfnAppendMemoryCopy)
        self.xeCommandListAppendMemorySet = _xeCommandListAppendMemorySet_t(self.__dditable.CommandList.pfnAppendMemorySet)
        self.xeCommandListAppendMemoryCopyRegion = _xeCommandListAppendMemoryCopyRegion_t(self.__dditable.CommandList.pfnAppendMemoryCopyRegion)
        self.xeCommandListAppendImageCopy = _xeCommandListAppendImageCopy_t(self.__dditable.CommandList.pfnAppendImageCopy)
        self.xeCommandListAppendImageCopyRegion = _xeCommandListAppendImageCopyRegion_t(self.__dditable.CommandList.pfnAppendImageCopyRegion)
        self.xeCommandListAppendImageCopyToMemory = _xeCommandListAppendImageCopyToMemory_t(self.__dditable.CommandList.pfnAppendImageCopyToMemory)
        self.xeCommandListAppendImageCopyFromMemory = _xeCommandListAppendImageCopyFromMemory_t(self.__dditable.CommandList.pfnAppendImageCopyFromMemory)
        self.xeCommandListAppendMemoryPrefetch = _xeCommandListAppendMemoryPrefetch_t(self.__dditable.CommandList.pfnAppendMemoryPrefetch)
        self.xeCommandListAppendMemAdvise = _xeCommandListAppendMemAdvise_t(self.__dditable.CommandList.pfnAppendMemAdvise)
        self.xeCommandListAppendSignalEvent = _xeCommandListAppendSignalEvent_t(self.__dditable.CommandList.pfnAppendSignalEvent)
        self.xeCommandListAppendWaitOnEvents = _xeCommandListAppendWaitOnEvents_t(self.__dditable.CommandList.pfnAppendWaitOnEvents)
        self.xeCommandListAppendEventReset = _xeCommandListAppendEventReset_t(self.__dditable.CommandList.pfnAppendEventReset)
        self.xeCommandListAppendLaunchFunction = _xeCommandListAppendLaunchFunction_t(self.__dditable.CommandList.pfnAppendLaunchFunction)
        self.xeCommandListAppendLaunchFunctionIndirect = _xeCommandListAppendLaunchFunctionIndirect_t(self.__dditable.CommandList.pfnAppendLaunchFunctionIndirect)
        self.xeCommandListAppendLaunchMultipleFunctionsIndirect = _xeCommandListAppendLaunchMultipleFunctionsIndirect_t(self.__dditable.CommandList.pfnAppendLaunchMultipleFunctionsIndirect)
        self.xeCommandListAppendLaunchHostFunction = _xeCommandListAppendLaunchHostFunction_t(self.__dditable.CommandList.pfnAppendLaunchHostFunction)

        # call driver to get function pointers
        _Fence = _xe_fence_dditable_t()
        r = xe_result_v(self.__dll.xeGetFenceProcAddrTable(version, byref(_Fence)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Fence = _Fence

        # attach function interface to function address
        self.xeFenceCreate = _xeFenceCreate_t(self.__dditable.Fence.pfnCreate)
        self.xeFenceDestroy = _xeFenceDestroy_t(self.__dditable.Fence.pfnDestroy)
        self.xeFenceHostSynchronize = _xeFenceHostSynchronize_t(self.__dditable.Fence.pfnHostSynchronize)
        self.xeFenceQueryStatus = _xeFenceQueryStatus_t(self.__dditable.Fence.pfnQueryStatus)
        self.xeFenceReset = _xeFenceReset_t(self.__dditable.Fence.pfnReset)

        # call driver to get function pointers
        _EventPool = _xe_event_pool_dditable_t()
        r = xe_result_v(self.__dll.xeGetEventPoolProcAddrTable(version, byref(_EventPool)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.EventPool = _EventPool

        # attach function interface to function address
        self.xeEventPoolCreate = _xeEventPoolCreate_t(self.__dditable.EventPool.pfnCreate)
        self.xeEventPoolDestroy = _xeEventPoolDestroy_t(self.__dditable.EventPool.pfnDestroy)
        self.xeEventPoolGetIpcHandle = _xeEventPoolGetIpcHandle_t(self.__dditable.EventPool.pfnGetIpcHandle)
        self.xeEventPoolOpenIpcHandle = _xeEventPoolOpenIpcHandle_t(self.__dditable.EventPool.pfnOpenIpcHandle)
        self.xeEventPoolCloseIpcHandle = _xeEventPoolCloseIpcHandle_t(self.__dditable.EventPool.pfnCloseIpcHandle)

        # call driver to get function pointers
        _Event = _xe_event_dditable_t()
        r = xe_result_v(self.__dll.xeGetEventProcAddrTable(version, byref(_Event)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Event = _Event

        # attach function interface to function address
        self.xeEventCreate = _xeEventCreate_t(self.__dditable.Event.pfnCreate)
        self.xeEventDestroy = _xeEventDestroy_t(self.__dditable.Event.pfnDestroy)
        self.xeEventHostSignal = _xeEventHostSignal_t(self.__dditable.Event.pfnHostSignal)
        self.xeEventHostSynchronize = _xeEventHostSynchronize_t(self.__dditable.Event.pfnHostSynchronize)
        self.xeEventQueryStatus = _xeEventQueryStatus_t(self.__dditable.Event.pfnQueryStatus)
        self.xeEventReset = _xeEventReset_t(self.__dditable.Event.pfnReset)

        # call driver to get function pointers
        _Image = _xe_image_dditable_t()
        r = xe_result_v(self.__dll.xeGetImageProcAddrTable(version, byref(_Image)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Image = _Image

        # attach function interface to function address
        self.xeImageGetProperties = _xeImageGetProperties_t(self.__dditable.Image.pfnGetProperties)
        self.xeImageCreate = _xeImageCreate_t(self.__dditable.Image.pfnCreate)
        self.xeImageDestroy = _xeImageDestroy_t(self.__dditable.Image.pfnDestroy)

        # call driver to get function pointers
        _Module = _xe_module_dditable_t()
        r = xe_result_v(self.__dll.xeGetModuleProcAddrTable(version, byref(_Module)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Module = _Module

        # attach function interface to function address
        self.xeModuleCreate = _xeModuleCreate_t(self.__dditable.Module.pfnCreate)
        self.xeModuleDestroy = _xeModuleDestroy_t(self.__dditable.Module.pfnDestroy)
        self.xeModuleGetNativeBinary = _xeModuleGetNativeBinary_t(self.__dditable.Module.pfnGetNativeBinary)
        self.xeModuleGetGlobalPointer = _xeModuleGetGlobalPointer_t(self.__dditable.Module.pfnGetGlobalPointer)
        self.xeModuleGetFunctionPointer = _xeModuleGetFunctionPointer_t(self.__dditable.Module.pfnGetFunctionPointer)

        # call driver to get function pointers
        _ModuleBuildLog = _xe_module_build_log_dditable_t()
        r = xe_result_v(self.__dll.xeGetModuleBuildLogProcAddrTable(version, byref(_ModuleBuildLog)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.ModuleBuildLog = _ModuleBuildLog

        # attach function interface to function address
        self.xeModuleBuildLogDestroy = _xeModuleBuildLogDestroy_t(self.__dditable.ModuleBuildLog.pfnDestroy)
        self.xeModuleBuildLogGetString = _xeModuleBuildLogGetString_t(self.__dditable.ModuleBuildLog.pfnGetString)

        # call driver to get function pointers
        _Function = _xe_function_dditable_t()
        r = xe_result_v(self.__dll.xeGetFunctionProcAddrTable(version, byref(_Function)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Function = _Function

        # attach function interface to function address
        self.xeFunctionCreate = _xeFunctionCreate_t(self.__dditable.Function.pfnCreate)
        self.xeFunctionDestroy = _xeFunctionDestroy_t(self.__dditable.Function.pfnDestroy)
        self.xeFunctionSetGroupSize = _xeFunctionSetGroupSize_t(self.__dditable.Function.pfnSetGroupSize)
        self.xeFunctionSuggestGroupSize = _xeFunctionSuggestGroupSize_t(self.__dditable.Function.pfnSuggestGroupSize)
        self.xeFunctionSetArgumentValue = _xeFunctionSetArgumentValue_t(self.__dditable.Function.pfnSetArgumentValue)
        self.xeFunctionSetAttribute = _xeFunctionSetAttribute_t(self.__dditable.Function.pfnSetAttribute)
        self.xeFunctionGetAttribute = _xeFunctionGetAttribute_t(self.__dditable.Function.pfnGetAttribute)

        # call driver to get function pointers
        _Sampler = _xe_sampler_dditable_t()
        r = xe_result_v(self.__dll.xeGetSamplerProcAddrTable(version, byref(_Sampler)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Sampler = _Sampler

        # attach function interface to function address
        self.xeSamplerCreate = _xeSamplerCreate_t(self.__dditable.Sampler.pfnCreate)
        self.xeSamplerDestroy = _xeSamplerDestroy_t(self.__dditable.Sampler.pfnDestroy)

        # success!
