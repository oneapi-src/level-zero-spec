"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

 @file zet.py
 @version v1.0-r0.9.276

 """
import platform
from ctypes import *
from enum import *

###############################################################################
__version__ = "1.0"

###############################################################################
## @brief Handle to a driver instance
class zet_driver_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of device object
class zet_device_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of command list object
class zet_command_list_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of module object
class zet_module_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of function object
class zet_kernel_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of metric group's object
class zet_metric_group_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of metric's object
class zet_metric_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of metric tracer's object
class zet_metric_tracer_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of metric query pool's object
class zet_metric_query_pool_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of metric query's object
class zet_metric_query_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of tracer object
class zet_tracer_handle_t(c_void_p):
    pass

###############################################################################
## @brief The API version.
ZET_DEBUG_API_VERSION = 1

###############################################################################
## @brief Debug session handle
class zet_debug_session_handle_t(c_void_p):
    pass

###############################################################################
## @brief Debug configuration: version 1
class zet_debug_config_v1_t(Structure):
    _fields_ = [
        ("pid", c_int)                                                  ## The host process identifier
    ]

###############################################################################
## @brief Debug configuration: version-dependent fields
class zet_debug_config_variants_t(Structure):
    _fields_ = [
        ("v1", zet_debug_config_v1_t)                                   ## Version 1
    ]

###############################################################################
## @brief Debug configuration
class zet_debug_config_t(Structure):
    _fields_ = [
        ("version", c_ushort),                                          ## The requested program debug API version
        ("variant", zet_debug_config_variants_t)                        ## Version-specific fields
    ]

###############################################################################
## @brief An infinite timeout.
ZET_DEBUG_TIMEOUT_INFINITE = 0xffffffffffffffffull

###############################################################################
## @brief Debug event flags.
class zet_debug_event_flags_v(IntEnum):
    DEBUG_EVENT_FLAG_NONE = 0                       ## No event flags
    DEBUG_EVENT_FLAG_STOPPED = ZE_BIT(0)            ## The reporting thread stopped

class zet_debug_event_flags_t(c_int):
    def __str__(self):
        return str(zet_debug_event_flags_v(value))


###############################################################################
## @brief Debug event types.
class zet_debug_event_type_v(IntEnum):
    DEBUG_EVENT_INVALID = 0                         ## The event is invalid
    DEBUG_EVENT_DETACHED = auto()                   ## The tool was detached
    DEBUG_EVENT_PROCESS_ENTRY = auto()              ## The debuggee process created command queues on the device
    DEBUG_EVENT_PROCESS_EXIT = auto()               ## The debuggee process destroyed all command queues on the device
    DEBUG_EVENT_MODULE_LOAD = auto()                ## An in-memory module was loaded onto the device
    DEBUG_EVENT_MODULE_UNLOAD = auto()              ## An in-memory module is about to get unloaded from the device
    DEBUG_EVENT_EXCEPTION = auto()                  ## The thread stopped due to a device exception

class zet_debug_event_type_t(c_int):
    def __str__(self):
        return str(zet_debug_event_type_v(value))


###############################################################################
## @brief Debug detach reason.
class zet_debug_detach_reason_v(IntEnum):
    DEBUG_DETACH_INVALID = 0                        ## The detach reason is not valid
    DEBUG_DETACH_HOST_EXIT = auto()                 ## The host process exited

class zet_debug_detach_reason_t(c_int):
    def __str__(self):
        return str(zet_debug_detach_reason_v(value))


###############################################################################
## @brief No thread on the device.
ZET_DEBUG_THREAD_NONE = 0xffffffffffffffffull

###############################################################################
## @brief All threads on the device.
ZET_DEBUG_THREAD_ALL = 0xfffffffffffffffeull

###############################################################################
## @brief Event information for ::ZET_DEBUG_EVENT_DETACHED
class zet_debug_event_info_detached_t(Structure):
    _fields_ = [
        ("reason", c_ubyte)                                             ## The detach reason
    ]

###############################################################################
## @brief Event information for ::ZET_DEBUG_EVENT_MODULE_LOAD/UNLOAD
class zet_debug_event_info_module_t(Structure):
    _fields_ = [
        ("moduleBegin", c_ulonglong),                                   ## The begin address of the in-memory module
        ("moduleEnd", c_ulonglong),                                     ## The end address of the in-memory module
        ("load", c_ulonglong)                                           ## The load address of the module on the device
    ]

###############################################################################
## @brief Event type specific information
class zet_debug_event_info_t(Structure):
    _fields_ = [
        ("detached", zet_debug_event_info_detached_t),                  ## type == ::ZET_DEBUG_EVENT_DETACHED
        ("module", zet_debug_event_info_module_t)                       ## type == ::ZET_DEBUG_EVENT_MODULE_LOAD/UNLOAD
    ]

###############################################################################
## @brief A debug event on the device.
class zet_debug_event_t(Structure):
    _fields_ = [
        ("type", c_ubyte),                                              ## The event type
        ("thread", c_ulonglong),                                        ## The thread reporting the event
        ("flags", c_ulonglong),                                         ## A bit-vector of ::zet_debug_event_flags_t
        ("info", zet_debug_event_info_t)                                ## Event type specific information
    ]

###############################################################################
## @brief Memory spaces for Intel Graphics devices.
class zet_debug_memory_space_intel_graphics_v(IntEnum):
    DEBUG_MEMORY_SPACE_GEN_DEFAULT = 0              ## default memory space (attribute may be omitted)
    DEBUG_MEMORY_SPACE_GEN_SLM = auto()             ## shared local memory space

class zet_debug_memory_space_intel_graphics_t(c_int):
    def __str__(self):
        return str(zet_debug_memory_space_intel_graphics_v(value))


###############################################################################
## @brief Register file types for Intel Graphics devices.
class zet_debug_state_intel_graphics_v(IntEnum):
    DEBUG_STATE_GEN_INVALID = 0                     ## An invalid register file
    DEBUG_STATE_GEN_GRF = auto()                    ## The general register file
    DEBUG_STATE_GEN_ACC = auto()                    ## The accumulator register file
    DEBUG_STATE_GEN_ADDR = auto()                   ## The address register file
    DEBUG_STATE_GEN_FLAG = auto()                   ## The flags register file

class zet_debug_state_intel_graphics_t(c_int):
    def __str__(self):
        return str(zet_debug_state_intel_graphics_v(value))


###############################################################################
## @brief A register file descriptor.
class zet_debug_state_section_t(Structure):
    _fields_ = [
        ("type", c_ushort),                                             ## The register file type type
        ("version", c_ushort),                                          ## The register file version
        ("size", c_ulong),                                              ## The size of the register file in bytes
        ("offset", c_ulonglong)                                         ## The offset into the register state area
    ]

###############################################################################
## @brief A register state descriptor.
class zet_debug_state_t(Structure):
    _fields_ = [
        ("size", c_ulong),                                              ## The size of the register state object in bytes
        ("headerSize", c_ubyte),                                        ## The size of the register state descriptor in bytes
        ("secSize", c_ubyte),                                           ## The size of the register file descriptors in bytes
        ("numSec", c_ushort)                                            ## The number of register file descriptors
    ]

###############################################################################
## @brief Maximum metric group name string size
ZET_MAX_METRIC_GROUP_NAME = 256

###############################################################################
## @brief Maximum metric group description string size
ZET_MAX_METRIC_GROUP_DESCRIPTION = 256

###############################################################################
## @brief Metric group sampling type
class zet_metric_group_sampling_type_v(IntEnum):
    EVENT_BASED = ZE_BIT(0)                         ## Event based sampling
    TIME_BASED = ZE_BIT(1)                          ## Time based sampling

class zet_metric_group_sampling_type_t(c_int):
    def __str__(self):
        return str(zet_metric_group_sampling_type_v(value))


###############################################################################
## @brief API version of ::zet_metric_group_properties_t
class zet_metric_group_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class zet_metric_group_properties_version_t(c_int):
    def __str__(self):
        return str(zet_metric_group_properties_version_v(value))


###############################################################################
## @brief Metric group properties queried using ::zetMetricGroupGetProperties
class zet_metric_group_properties_t(Structure):
    _fields_ = [
        ("version", zet_metric_group_properties_version_t),             ## [in] ::ZET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT
        ("name", c_char * ZET_MAX_METRIC_GROUP_NAME),                   ## [out] metric group name
        ("description", c_char * ZET_MAX_METRIC_GROUP_DESCRIPTION),     ## [out] metric group description
        ("samplingType", zet_metric_group_sampling_type_t),             ## [out] metric group sampling type
        ("domain", c_ulong),                                            ## [out] metric group domain number. Cannot use simultaneous metric
                                                                        ## groups from different domains.
        ("maxCommandQueueGroupOrdinal", c_ulong),                       ## [out] tracers and queries of this metric group cannot be submitted to
                                                                        ## a command queue group with a larger ordinal value.
                                                                        ## See ::ze_command_queue_desc_t for more information on how to specify
                                                                        ## the command queue's group ordinal.
        ("metricCount", c_ulong)                                        ## [out] metric count belonging to this group
    ]

###############################################################################
## @brief Metric types
class zet_metric_type_v(IntEnum):
    DURATION = auto()                               ## Metric type: duration
    EVENT = auto()                                  ## Metric type: event
    EVENT_WITH_RANGE = auto()                       ## Metric type: event with range
    THROUGHPUT = auto()                             ## Metric type: throughput
    TIMESTAMP = auto()                              ## Metric type: timestamp
    FLAG = auto()                                   ## Metric type: flag
    RATIO = auto()                                  ## Metric type: ratio
    RAW = auto()                                    ## Metric type: raw

class zet_metric_type_t(c_int):
    def __str__(self):
        return str(zet_metric_type_v(value))


###############################################################################
## @brief Supported value types
class zet_value_type_v(IntEnum):
    UINT32 = auto()                                 ## 32-bit unsigned-integer
    UINT64 = auto()                                 ## 64-bit unsigned-integer
    FLOAT32 = auto()                                ## 32-bit floating-point
    FLOAT64 = auto()                                ## 64-bit floating-point
    BOOL8 = auto()                                  ## 8-bit boolean

class zet_value_type_t(c_int):
    def __str__(self):
        return str(zet_value_type_v(value))


###############################################################################
## @brief Union of values
class zet_value_t(Structure):
    _fields_ = [
        ("ui32", c_ulong),                                              ## [out] 32-bit unsigned-integer
        ("ui64", c_ulonglong),                                          ## [out] 32-bit unsigned-integer
        ("fp32", c_float),                                              ## [out] 32-bit floating-point
        ("fp64", c_double),                                             ## [out] 64-bit floating-point
        ("b8", ze_bool_t)                                               ## [out] 8-bit boolean
    ]

###############################################################################
## @brief Typed value
class zet_typed_value_t(Structure):
    _fields_ = [
        ("type", zet_value_type_t),                                     ## [out] type of value
        ("value", zet_value_t)                                          ## [out] value
    ]

###############################################################################
## @brief Maximum metric name string size
ZET_MAX_METRIC_NAME = 256

###############################################################################
## @brief Maximum metric description string size
ZET_MAX_METRIC_DESCRIPTION = 256

###############################################################################
## @brief Maximum metric component string size
ZET_MAX_METRIC_COMPONENT = 256

###############################################################################
## @brief Maximum metric result units string size
ZET_MAX_METRIC_RESULT_UNITS = 256

###############################################################################
## @brief API version of ::zet_metric_properties_t
class zet_metric_properties_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class zet_metric_properties_version_t(c_int):
    def __str__(self):
        return str(zet_metric_properties_version_v(value))


###############################################################################
## @brief Metric properties queried using ::zetMetricGetProperties
class zet_metric_properties_t(Structure):
    _fields_ = [
        ("version", zet_metric_properties_version_t),                   ## [in] ::ZET_METRIC_PROPERTIES_VERSION_CURRENT
        ("name", c_char * ZET_MAX_METRIC_NAME),                         ## [out] metric name
        ("description", c_char * ZET_MAX_METRIC_DESCRIPTION),           ## [out] metric description
        ("component", c_char * ZET_MAX_METRIC_COMPONENT),               ## [out] metric component
        ("tierNumber", c_ulong),                                        ## [out] number of tier
        ("metricType", zet_metric_type_t),                              ## [out] metric type
        ("resultType", zet_value_type_t),                               ## [out] metric result type
        ("resultUnits", c_char * ZET_MAX_METRIC_RESULT_UNITS)           ## [out] metric result units
    ]

###############################################################################
## @brief API version of ::zet_metric_tracer_desc_t
class zet_metric_tracer_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class zet_metric_tracer_desc_version_t(c_int):
    def __str__(self):
        return str(zet_metric_tracer_desc_version_v(value))


###############################################################################
## @brief Metric tracer descriptor
class zet_metric_tracer_desc_t(Structure):
    _fields_ = [
        ("version", zet_metric_tracer_desc_version_t),                  ## [in] ::ZET_METRIC_TRACER_DESC_VERSION_CURRENT
        ("notifyEveryNReports", c_ulong),                               ## [in,out] number of collected reports after which notification event
                                                                        ## will be signalled
        ("samplingPeriod", c_ulong)                                     ## [in,out] tracer sampling period in nanoseconds
    ]

###############################################################################
## @brief API version of ::zet_metric_query_pool_desc_t
class zet_metric_query_pool_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class zet_metric_query_pool_desc_version_t(c_int):
    def __str__(self):
        return str(zet_metric_query_pool_desc_version_v(value))


###############################################################################
## @brief Metric query pool types
class zet_metric_query_pool_flag_v(IntEnum):
    PERFORMANCE = auto()                            ## Performance metric query pool.
    SKIP_EXECUTION = auto()                         ## Skips workload execution between begin/end calls.

class zet_metric_query_pool_flag_t(c_int):
    def __str__(self):
        return str(zet_metric_query_pool_flag_v(value))


###############################################################################
## @brief Metric query pool description
class zet_metric_query_pool_desc_t(Structure):
    _fields_ = [
        ("version", zet_metric_query_pool_desc_version_t),              ## [in] ::ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT
        ("flags", zet_metric_query_pool_flag_t),                        ## [in] Query pool type.
        ("count", c_ulong)                                              ## [in] Internal slots count within query pool object.
    ]

###############################################################################
## @brief Supported module debug info formats.
class zet_module_debug_info_format_v(IntEnum):
    ELF_DWARF = auto()                              ## Format is ELF/DWARF

class zet_module_debug_info_format_t(c_int):
    def __str__(self):
        return str(zet_module_debug_info_format_v(value))


###############################################################################
## @brief API version of ::zet_profile_info_t
class zet_profile_info_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class zet_profile_info_version_t(c_int):
    def __str__(self):
        return str(zet_profile_info_version_v(value))


###############################################################################
## @brief Supportted profile features
class zet_profile_flag_v(IntEnum):
    REGISTER_REALLOCATION = ZE_BIT(0)               ## request the compiler attempt to minimize register usage as much as
                                                    ## possible to allow for instrumentation
    FREE_REGISTER_INFO = ZE_BIT(1)                  ## request the compiler generate free register info

class zet_profile_flag_t(c_int):
    def __str__(self):
        return str(zet_profile_flag_v(value))


###############################################################################
## @brief Profiling meta-data for instrumentation
class zet_profile_info_t(Structure):
    _fields_ = [
        ("version", zet_profile_info_version_t),                        ## [in] ::ZET_PROFILE_INFO_VERSION_CURRENT
        ("flags", zet_profile_flag_t),                                  ## [out] indicates which flags were enabled during compilation
        ("numTokens", c_ulong)                                          ## [out] number of tokens immediately following this structure
    ]

###############################################################################
## @brief Supported profile token types
class zet_profile_token_type_v(IntEnum):
    FREE_REGISTER = auto()                          ## GRF info

class zet_profile_token_type_t(c_int):
    def __str__(self):
        return str(zet_profile_token_type_v(value))


###############################################################################
## @brief Profile free register token detailing unused registers in the current
##        function
class zet_profile_free_register_token_t(Structure):
    _fields_ = [
        ("type", zet_profile_token_type_t),                             ## [out] type of token
        ("size", c_ulong),                                              ## [out] total size of the token, in bytes
        ("count", c_ulong)                                              ## [out] number of register sequences immediately following this
                                                                        ## structure
    ]

###############################################################################
## @brief Profile register sequence detailing consecutive bytes, all of which
##        are unused
class zet_profile_register_sequence_t(Structure):
    _fields_ = [
        ("start", c_ulong),                                             ## [out] starting byte in the register table, representing the start of
                                                                        ## unused bytes in the current function
        ("count", c_ulong)                                              ## [out] number of consecutive bytes in the sequence, starting from start
    ]

###############################################################################
## @brief Alias the existing callbacks definition for 'core' callbacks
class zet_core_callbacks_t(ze_callbacks_t):
    pass

###############################################################################
## @brief API version of ::zet_tracer_desc_t
class zet_tracer_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class zet_tracer_desc_version_t(c_int):
    def __str__(self):
        return str(zet_tracer_desc_version_v(value))


###############################################################################
## @brief Tracer descriptor
class zet_tracer_desc_t(Structure):
    _fields_ = [
        ("version", zet_tracer_desc_version_t),                         ## [in] ::ZET_TRACER_DESC_VERSION_CURRENT
        ("pUserData", c_void_p)                                         ## [in] pointer passed to every tracer's callbacks
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
## @brief Function-pointer for zetDeviceActivateMetricGroups
if __use_win_types:
    _zetDeviceActivateMetricGroups_t = WINFUNCTYPE( ze_result_t, zet_device_handle_t, c_ulong, POINTER(zet_metric_group_handle_t) )
else:
    _zetDeviceActivateMetricGroups_t = CFUNCTYPE( ze_result_t, zet_device_handle_t, c_ulong, POINTER(zet_metric_group_handle_t) )


###############################################################################
## @brief Table of Device functions pointers
class _zet_device_dditable_t(Structure):
    _fields_ = [
        ("pfnActivateMetricGroups", c_void_p)                           ## _zetDeviceActivateMetricGroups_t
    ]

###############################################################################
## @brief Function-pointer for zetCommandListAppendMetricTracerMarker
if __use_win_types:
    _zetCommandListAppendMetricTracerMarker_t = WINFUNCTYPE( ze_result_t, zet_command_list_handle_t, zet_metric_tracer_handle_t, c_ulong )
else:
    _zetCommandListAppendMetricTracerMarker_t = CFUNCTYPE( ze_result_t, zet_command_list_handle_t, zet_metric_tracer_handle_t, c_ulong )

###############################################################################
## @brief Function-pointer for zetCommandListAppendMetricQueryBegin
if __use_win_types:
    _zetCommandListAppendMetricQueryBegin_t = WINFUNCTYPE( ze_result_t, zet_command_list_handle_t, zet_metric_query_handle_t )
else:
    _zetCommandListAppendMetricQueryBegin_t = CFUNCTYPE( ze_result_t, zet_command_list_handle_t, zet_metric_query_handle_t )

###############################################################################
## @brief Function-pointer for zetCommandListAppendMetricQueryEnd
if __use_win_types:
    _zetCommandListAppendMetricQueryEnd_t = WINFUNCTYPE( ze_result_t, zet_command_list_handle_t, zet_metric_query_handle_t, ze_event_handle_t )
else:
    _zetCommandListAppendMetricQueryEnd_t = CFUNCTYPE( ze_result_t, zet_command_list_handle_t, zet_metric_query_handle_t, ze_event_handle_t )

###############################################################################
## @brief Function-pointer for zetCommandListAppendMetricMemoryBarrier
if __use_win_types:
    _zetCommandListAppendMetricMemoryBarrier_t = WINFUNCTYPE( ze_result_t, zet_command_list_handle_t )
else:
    _zetCommandListAppendMetricMemoryBarrier_t = CFUNCTYPE( ze_result_t, zet_command_list_handle_t )


###############################################################################
## @brief Table of CommandList functions pointers
class _zet_command_list_dditable_t(Structure):
    _fields_ = [
        ("pfnAppendMetricTracerMarker", c_void_p),                      ## _zetCommandListAppendMetricTracerMarker_t
        ("pfnAppendMetricQueryBegin", c_void_p),                        ## _zetCommandListAppendMetricQueryBegin_t
        ("pfnAppendMetricQueryEnd", c_void_p),                          ## _zetCommandListAppendMetricQueryEnd_t
        ("pfnAppendMetricMemoryBarrier", c_void_p)                      ## _zetCommandListAppendMetricMemoryBarrier_t
    ]

###############################################################################
## @brief Function-pointer for zetModuleGetDebugInfo
if __use_win_types:
    _zetModuleGetDebugInfo_t = WINFUNCTYPE( ze_result_t, zet_module_handle_t, zet_module_debug_info_format_t, POINTER(c_size_t), POINTER(c_ubyte) )
else:
    _zetModuleGetDebugInfo_t = CFUNCTYPE( ze_result_t, zet_module_handle_t, zet_module_debug_info_format_t, POINTER(c_size_t), POINTER(c_ubyte) )


###############################################################################
## @brief Table of Module functions pointers
class _zet_module_dditable_t(Structure):
    _fields_ = [
        ("pfnGetDebugInfo", c_void_p)                                   ## _zetModuleGetDebugInfo_t
    ]

###############################################################################
## @brief Function-pointer for zetKernelGetProfileInfo
if __use_win_types:
    _zetKernelGetProfileInfo_t = WINFUNCTYPE( ze_result_t, zet_kernel_handle_t, POINTER(zet_profile_info_t) )
else:
    _zetKernelGetProfileInfo_t = CFUNCTYPE( ze_result_t, zet_kernel_handle_t, POINTER(zet_profile_info_t) )


###############################################################################
## @brief Table of Kernel functions pointers
class _zet_kernel_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProfileInfo", c_void_p)                                 ## _zetKernelGetProfileInfo_t
    ]

###############################################################################
## @brief Function-pointer for zetMetricGroupGet
if __use_win_types:
    _zetMetricGroupGet_t = WINFUNCTYPE( ze_result_t, zet_device_handle_t, POINTER(c_ulong), POINTER(zet_metric_group_handle_t) )
else:
    _zetMetricGroupGet_t = CFUNCTYPE( ze_result_t, zet_device_handle_t, POINTER(c_ulong), POINTER(zet_metric_group_handle_t) )

###############################################################################
## @brief Function-pointer for zetMetricGroupGetProperties
if __use_win_types:
    _zetMetricGroupGetProperties_t = WINFUNCTYPE( ze_result_t, zet_metric_group_handle_t, POINTER(zet_metric_group_properties_t) )
else:
    _zetMetricGroupGetProperties_t = CFUNCTYPE( ze_result_t, zet_metric_group_handle_t, POINTER(zet_metric_group_properties_t) )

###############################################################################
## @brief Function-pointer for zetMetricGroupCalculateMetricValues
if __use_win_types:
    _zetMetricGroupCalculateMetricValues_t = WINFUNCTYPE( ze_result_t, zet_metric_group_handle_t, c_size_t, POINTER(c_ubyte), POINTER(c_ulong), POINTER(zet_typed_value_t) )
else:
    _zetMetricGroupCalculateMetricValues_t = CFUNCTYPE( ze_result_t, zet_metric_group_handle_t, c_size_t, POINTER(c_ubyte), POINTER(c_ulong), POINTER(zet_typed_value_t) )


###############################################################################
## @brief Table of MetricGroup functions pointers
class _zet_metric_group_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _zetMetricGroupGet_t
        ("pfnGetProperties", c_void_p),                                 ## _zetMetricGroupGetProperties_t
        ("pfnCalculateMetricValues", c_void_p)                          ## _zetMetricGroupCalculateMetricValues_t
    ]

###############################################################################
## @brief Function-pointer for zetMetricGet
if __use_win_types:
    _zetMetricGet_t = WINFUNCTYPE( ze_result_t, zet_metric_group_handle_t, POINTER(c_ulong), POINTER(zet_metric_handle_t) )
else:
    _zetMetricGet_t = CFUNCTYPE( ze_result_t, zet_metric_group_handle_t, POINTER(c_ulong), POINTER(zet_metric_handle_t) )

###############################################################################
## @brief Function-pointer for zetMetricGetProperties
if __use_win_types:
    _zetMetricGetProperties_t = WINFUNCTYPE( ze_result_t, zet_metric_handle_t, POINTER(zet_metric_properties_t) )
else:
    _zetMetricGetProperties_t = CFUNCTYPE( ze_result_t, zet_metric_handle_t, POINTER(zet_metric_properties_t) )


###############################################################################
## @brief Table of Metric functions pointers
class _zet_metric_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _zetMetricGet_t
        ("pfnGetProperties", c_void_p)                                  ## _zetMetricGetProperties_t
    ]

###############################################################################
## @brief Function-pointer for zetMetricTracerOpen
if __use_win_types:
    _zetMetricTracerOpen_t = WINFUNCTYPE( ze_result_t, zet_device_handle_t, zet_metric_group_handle_t, POINTER(zet_metric_tracer_desc_t), ze_event_handle_t, POINTER(zet_metric_tracer_handle_t) )
else:
    _zetMetricTracerOpen_t = CFUNCTYPE( ze_result_t, zet_device_handle_t, zet_metric_group_handle_t, POINTER(zet_metric_tracer_desc_t), ze_event_handle_t, POINTER(zet_metric_tracer_handle_t) )

###############################################################################
## @brief Function-pointer for zetMetricTracerClose
if __use_win_types:
    _zetMetricTracerClose_t = WINFUNCTYPE( ze_result_t, zet_metric_tracer_handle_t )
else:
    _zetMetricTracerClose_t = CFUNCTYPE( ze_result_t, zet_metric_tracer_handle_t )

###############################################################################
## @brief Function-pointer for zetMetricTracerReadData
if __use_win_types:
    _zetMetricTracerReadData_t = WINFUNCTYPE( ze_result_t, zet_metric_tracer_handle_t, c_ulong, POINTER(c_size_t), POINTER(c_ubyte) )
else:
    _zetMetricTracerReadData_t = CFUNCTYPE( ze_result_t, zet_metric_tracer_handle_t, c_ulong, POINTER(c_size_t), POINTER(c_ubyte) )


###############################################################################
## @brief Table of MetricTracer functions pointers
class _zet_metric_tracer_dditable_t(Structure):
    _fields_ = [
        ("pfnOpen", c_void_p),                                          ## _zetMetricTracerOpen_t
        ("pfnClose", c_void_p),                                         ## _zetMetricTracerClose_t
        ("pfnReadData", c_void_p)                                       ## _zetMetricTracerReadData_t
    ]

###############################################################################
## @brief Function-pointer for zetMetricQueryPoolCreate
if __use_win_types:
    _zetMetricQueryPoolCreate_t = WINFUNCTYPE( ze_result_t, zet_device_handle_t, zet_metric_group_handle_t, POINTER(zet_metric_query_pool_desc_t), POINTER(zet_metric_query_pool_handle_t) )
else:
    _zetMetricQueryPoolCreate_t = CFUNCTYPE( ze_result_t, zet_device_handle_t, zet_metric_group_handle_t, POINTER(zet_metric_query_pool_desc_t), POINTER(zet_metric_query_pool_handle_t) )

###############################################################################
## @brief Function-pointer for zetMetricQueryPoolDestroy
if __use_win_types:
    _zetMetricQueryPoolDestroy_t = WINFUNCTYPE( ze_result_t, zet_metric_query_pool_handle_t )
else:
    _zetMetricQueryPoolDestroy_t = CFUNCTYPE( ze_result_t, zet_metric_query_pool_handle_t )


###############################################################################
## @brief Table of MetricQueryPool functions pointers
class _zet_metric_query_pool_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zetMetricQueryPoolCreate_t
        ("pfnDestroy", c_void_p)                                        ## _zetMetricQueryPoolDestroy_t
    ]

###############################################################################
## @brief Function-pointer for zetMetricQueryCreate
if __use_win_types:
    _zetMetricQueryCreate_t = WINFUNCTYPE( ze_result_t, zet_metric_query_pool_handle_t, c_ulong, POINTER(zet_metric_query_handle_t) )
else:
    _zetMetricQueryCreate_t = CFUNCTYPE( ze_result_t, zet_metric_query_pool_handle_t, c_ulong, POINTER(zet_metric_query_handle_t) )

###############################################################################
## @brief Function-pointer for zetMetricQueryDestroy
if __use_win_types:
    _zetMetricQueryDestroy_t = WINFUNCTYPE( ze_result_t, zet_metric_query_handle_t )
else:
    _zetMetricQueryDestroy_t = CFUNCTYPE( ze_result_t, zet_metric_query_handle_t )

###############################################################################
## @brief Function-pointer for zetMetricQueryReset
if __use_win_types:
    _zetMetricQueryReset_t = WINFUNCTYPE( ze_result_t, zet_metric_query_handle_t )
else:
    _zetMetricQueryReset_t = CFUNCTYPE( ze_result_t, zet_metric_query_handle_t )

###############################################################################
## @brief Function-pointer for zetMetricQueryGetData
if __use_win_types:
    _zetMetricQueryGetData_t = WINFUNCTYPE( ze_result_t, zet_metric_query_handle_t, POINTER(c_size_t), POINTER(c_ubyte) )
else:
    _zetMetricQueryGetData_t = CFUNCTYPE( ze_result_t, zet_metric_query_handle_t, POINTER(c_size_t), POINTER(c_ubyte) )


###############################################################################
## @brief Table of MetricQuery functions pointers
class _zet_metric_query_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zetMetricQueryCreate_t
        ("pfnDestroy", c_void_p),                                       ## _zetMetricQueryDestroy_t
        ("pfnReset", c_void_p),                                         ## _zetMetricQueryReset_t
        ("pfnGetData", c_void_p)                                        ## _zetMetricQueryGetData_t
    ]

###############################################################################
## @brief Function-pointer for zetTracerCreate
if __use_win_types:
    _zetTracerCreate_t = WINFUNCTYPE( ze_result_t, zet_driver_handle_t, POINTER(zet_tracer_desc_t), POINTER(zet_tracer_handle_t) )
else:
    _zetTracerCreate_t = CFUNCTYPE( ze_result_t, zet_driver_handle_t, POINTER(zet_tracer_desc_t), POINTER(zet_tracer_handle_t) )

###############################################################################
## @brief Function-pointer for zetTracerDestroy
if __use_win_types:
    _zetTracerDestroy_t = WINFUNCTYPE( ze_result_t, zet_tracer_handle_t )
else:
    _zetTracerDestroy_t = CFUNCTYPE( ze_result_t, zet_tracer_handle_t )

###############################################################################
## @brief Function-pointer for zetTracerSetPrologues
if __use_win_types:
    _zetTracerSetPrologues_t = WINFUNCTYPE( ze_result_t, zet_tracer_handle_t, POINTER(zet_core_callbacks_t) )
else:
    _zetTracerSetPrologues_t = CFUNCTYPE( ze_result_t, zet_tracer_handle_t, POINTER(zet_core_callbacks_t) )

###############################################################################
## @brief Function-pointer for zetTracerSetEpilogues
if __use_win_types:
    _zetTracerSetEpilogues_t = WINFUNCTYPE( ze_result_t, zet_tracer_handle_t, POINTER(zet_core_callbacks_t) )
else:
    _zetTracerSetEpilogues_t = CFUNCTYPE( ze_result_t, zet_tracer_handle_t, POINTER(zet_core_callbacks_t) )

###############################################################################
## @brief Function-pointer for zetTracerSetEnabled
if __use_win_types:
    _zetTracerSetEnabled_t = WINFUNCTYPE( ze_result_t, zet_tracer_handle_t, ze_bool_t )
else:
    _zetTracerSetEnabled_t = CFUNCTYPE( ze_result_t, zet_tracer_handle_t, ze_bool_t )


###############################################################################
## @brief Table of Tracer functions pointers
class _zet_tracer_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zetTracerCreate_t
        ("pfnDestroy", c_void_p),                                       ## _zetTracerDestroy_t
        ("pfnSetPrologues", c_void_p),                                  ## _zetTracerSetPrologues_t
        ("pfnSetEpilogues", c_void_p),                                  ## _zetTracerSetEpilogues_t
        ("pfnSetEnabled", c_void_p)                                     ## _zetTracerSetEnabled_t
    ]

###############################################################################
## @brief Function-pointer for zetDebugAttach
if __use_win_types:
    _zetDebugAttach_t = WINFUNCTYPE( ze_result_t, zet_device_handle_t, POINTER(zet_debug_config_t), POINTER(zet_debug_session_handle_t) )
else:
    _zetDebugAttach_t = CFUNCTYPE( ze_result_t, zet_device_handle_t, POINTER(zet_debug_config_t), POINTER(zet_debug_session_handle_t) )

###############################################################################
## @brief Function-pointer for zetDebugDetach
if __use_win_types:
    _zetDebugDetach_t = WINFUNCTYPE( ze_result_t, zet_debug_session_handle_t )
else:
    _zetDebugDetach_t = CFUNCTYPE( ze_result_t, zet_debug_session_handle_t )

###############################################################################
## @brief Function-pointer for zetDebugGetNumThreads
if __use_win_types:
    _zetDebugGetNumThreads_t = WINFUNCTYPE( ze_result_t, zet_debug_session_handle_t, POINTER(c_ulonglong) )
else:
    _zetDebugGetNumThreads_t = CFUNCTYPE( ze_result_t, zet_debug_session_handle_t, POINTER(c_ulonglong) )

###############################################################################
## @brief Function-pointer for zetDebugReadEvent
if __use_win_types:
    _zetDebugReadEvent_t = WINFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong, c_size_t, c_void_p )
else:
    _zetDebugReadEvent_t = CFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong, c_size_t, c_void_p )

###############################################################################
## @brief Function-pointer for zetDebugInterrupt
if __use_win_types:
    _zetDebugInterrupt_t = WINFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong )
else:
    _zetDebugInterrupt_t = CFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong )

###############################################################################
## @brief Function-pointer for zetDebugResume
if __use_win_types:
    _zetDebugResume_t = WINFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong )
else:
    _zetDebugResume_t = CFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong )

###############################################################################
## @brief Function-pointer for zetDebugReadMemory
if __use_win_types:
    _zetDebugReadMemory_t = WINFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong, c_int, c_ulonglong, c_size_t, c_void_p )
else:
    _zetDebugReadMemory_t = CFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong, c_int, c_ulonglong, c_size_t, c_void_p )

###############################################################################
## @brief Function-pointer for zetDebugWriteMemory
if __use_win_types:
    _zetDebugWriteMemory_t = WINFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong, c_int, c_ulonglong, c_size_t, c_void_p )
else:
    _zetDebugWriteMemory_t = CFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong, c_int, c_ulonglong, c_size_t, c_void_p )

###############################################################################
## @brief Function-pointer for zetDebugReadState
if __use_win_types:
    _zetDebugReadState_t = WINFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong, c_ulonglong, c_size_t, c_void_p )
else:
    _zetDebugReadState_t = CFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong, c_ulonglong, c_size_t, c_void_p )

###############################################################################
## @brief Function-pointer for zetDebugWriteState
if __use_win_types:
    _zetDebugWriteState_t = WINFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong, c_ulonglong, c_size_t, c_void_p )
else:
    _zetDebugWriteState_t = CFUNCTYPE( ze_result_t, zet_debug_session_handle_t, c_ulonglong, c_ulonglong, c_size_t, c_void_p )


###############################################################################
## @brief Table of Debug functions pointers
class _zet_debug_dditable_t(Structure):
    _fields_ = [
        ("pfnAttach", c_void_p),                                        ## _zetDebugAttach_t
        ("pfnDetach", c_void_p),                                        ## _zetDebugDetach_t
        ("pfnGetNumThreads", c_void_p),                                 ## _zetDebugGetNumThreads_t
        ("pfnReadEvent", c_void_p),                                     ## _zetDebugReadEvent_t
        ("pfnInterrupt", c_void_p),                                     ## _zetDebugInterrupt_t
        ("pfnResume", c_void_p),                                        ## _zetDebugResume_t
        ("pfnReadMemory", c_void_p),                                    ## _zetDebugReadMemory_t
        ("pfnWriteMemory", c_void_p),                                   ## _zetDebugWriteMemory_t
        ("pfnReadState", c_void_p),                                     ## _zetDebugReadState_t
        ("pfnWriteState", c_void_p)                                     ## _zetDebugWriteState_t
    ]

###############################################################################
class _zet_dditable_t(Structure):
    _fields_ = [
        ("Device", _zet_device_dditable_t),
        ("CommandList", _zet_command_list_dditable_t),
        ("Module", _zet_module_dditable_t),
        ("Kernel", _zet_kernel_dditable_t),
        ("MetricGroup", _zet_metric_group_dditable_t),
        ("Metric", _zet_metric_dditable_t),
        ("MetricTracer", _zet_metric_tracer_dditable_t),
        ("MetricQueryPool", _zet_metric_query_pool_dditable_t),
        ("MetricQuery", _zet_metric_query_dditable_t),
        ("Tracer", _zet_tracer_dditable_t),
        ("Debug", _zet_debug_dditable_t)
    ]

###############################################################################
## @brief zet device-driver interfaces
class ZET_DDI:
    def __init__(self, version : ze_api_version_t):
        # load the xe_loader library
        if "Windows" == platform.uname()[0]:
            self.__dll = WinDLL("ze_loader.dll")
        else:
            self.__dll = CDLL("ze_loader.so")

        # fill the ddi tables
        self.__dditable = _zet_dditable_t()

        # call driver to get function pointers
        _Device = _zet_device_dditable_t()
        r = ze_result_v(self.__dll.zetGetDeviceProcAddrTable(version, byref(_Device)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Device = _Device

        # attach function interface to function address
        self.zetDeviceActivateMetricGroups = _zetDeviceActivateMetricGroups_t(self.__dditable.Device.pfnActivateMetricGroups)

        # call driver to get function pointers
        _CommandList = _zet_command_list_dditable_t()
        r = ze_result_v(self.__dll.zetGetCommandListProcAddrTable(version, byref(_CommandList)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.CommandList = _CommandList

        # attach function interface to function address
        self.zetCommandListAppendMetricTracerMarker = _zetCommandListAppendMetricTracerMarker_t(self.__dditable.CommandList.pfnAppendMetricTracerMarker)
        self.zetCommandListAppendMetricQueryBegin = _zetCommandListAppendMetricQueryBegin_t(self.__dditable.CommandList.pfnAppendMetricQueryBegin)
        self.zetCommandListAppendMetricQueryEnd = _zetCommandListAppendMetricQueryEnd_t(self.__dditable.CommandList.pfnAppendMetricQueryEnd)
        self.zetCommandListAppendMetricMemoryBarrier = _zetCommandListAppendMetricMemoryBarrier_t(self.__dditable.CommandList.pfnAppendMetricMemoryBarrier)

        # call driver to get function pointers
        _Module = _zet_module_dditable_t()
        r = ze_result_v(self.__dll.zetGetModuleProcAddrTable(version, byref(_Module)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Module = _Module

        # attach function interface to function address
        self.zetModuleGetDebugInfo = _zetModuleGetDebugInfo_t(self.__dditable.Module.pfnGetDebugInfo)

        # call driver to get function pointers
        _Kernel = _zet_kernel_dditable_t()
        r = ze_result_v(self.__dll.zetGetKernelProcAddrTable(version, byref(_Kernel)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Kernel = _Kernel

        # attach function interface to function address
        self.zetKernelGetProfileInfo = _zetKernelGetProfileInfo_t(self.__dditable.Kernel.pfnGetProfileInfo)

        # call driver to get function pointers
        _MetricGroup = _zet_metric_group_dditable_t()
        r = ze_result_v(self.__dll.zetGetMetricGroupProcAddrTable(version, byref(_MetricGroup)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.MetricGroup = _MetricGroup

        # attach function interface to function address
        self.zetMetricGroupGet = _zetMetricGroupGet_t(self.__dditable.MetricGroup.pfnGet)
        self.zetMetricGroupGetProperties = _zetMetricGroupGetProperties_t(self.__dditable.MetricGroup.pfnGetProperties)
        self.zetMetricGroupCalculateMetricValues = _zetMetricGroupCalculateMetricValues_t(self.__dditable.MetricGroup.pfnCalculateMetricValues)

        # call driver to get function pointers
        _Metric = _zet_metric_dditable_t()
        r = ze_result_v(self.__dll.zetGetMetricProcAddrTable(version, byref(_Metric)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Metric = _Metric

        # attach function interface to function address
        self.zetMetricGet = _zetMetricGet_t(self.__dditable.Metric.pfnGet)
        self.zetMetricGetProperties = _zetMetricGetProperties_t(self.__dditable.Metric.pfnGetProperties)

        # call driver to get function pointers
        _MetricTracer = _zet_metric_tracer_dditable_t()
        r = ze_result_v(self.__dll.zetGetMetricTracerProcAddrTable(version, byref(_MetricTracer)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.MetricTracer = _MetricTracer

        # attach function interface to function address
        self.zetMetricTracerOpen = _zetMetricTracerOpen_t(self.__dditable.MetricTracer.pfnOpen)
        self.zetMetricTracerClose = _zetMetricTracerClose_t(self.__dditable.MetricTracer.pfnClose)
        self.zetMetricTracerReadData = _zetMetricTracerReadData_t(self.__dditable.MetricTracer.pfnReadData)

        # call driver to get function pointers
        _MetricQueryPool = _zet_metric_query_pool_dditable_t()
        r = ze_result_v(self.__dll.zetGetMetricQueryPoolProcAddrTable(version, byref(_MetricQueryPool)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.MetricQueryPool = _MetricQueryPool

        # attach function interface to function address
        self.zetMetricQueryPoolCreate = _zetMetricQueryPoolCreate_t(self.__dditable.MetricQueryPool.pfnCreate)
        self.zetMetricQueryPoolDestroy = _zetMetricQueryPoolDestroy_t(self.__dditable.MetricQueryPool.pfnDestroy)

        # call driver to get function pointers
        _MetricQuery = _zet_metric_query_dditable_t()
        r = ze_result_v(self.__dll.zetGetMetricQueryProcAddrTable(version, byref(_MetricQuery)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.MetricQuery = _MetricQuery

        # attach function interface to function address
        self.zetMetricQueryCreate = _zetMetricQueryCreate_t(self.__dditable.MetricQuery.pfnCreate)
        self.zetMetricQueryDestroy = _zetMetricQueryDestroy_t(self.__dditable.MetricQuery.pfnDestroy)
        self.zetMetricQueryReset = _zetMetricQueryReset_t(self.__dditable.MetricQuery.pfnReset)
        self.zetMetricQueryGetData = _zetMetricQueryGetData_t(self.__dditable.MetricQuery.pfnGetData)

        # call driver to get function pointers
        _Tracer = _zet_tracer_dditable_t()
        r = ze_result_v(self.__dll.zetGetTracerProcAddrTable(version, byref(_Tracer)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Tracer = _Tracer

        # attach function interface to function address
        self.zetTracerCreate = _zetTracerCreate_t(self.__dditable.Tracer.pfnCreate)
        self.zetTracerDestroy = _zetTracerDestroy_t(self.__dditable.Tracer.pfnDestroy)
        self.zetTracerSetPrologues = _zetTracerSetPrologues_t(self.__dditable.Tracer.pfnSetPrologues)
        self.zetTracerSetEpilogues = _zetTracerSetEpilogues_t(self.__dditable.Tracer.pfnSetEpilogues)
        self.zetTracerSetEnabled = _zetTracerSetEnabled_t(self.__dditable.Tracer.pfnSetEnabled)

        # call driver to get function pointers
        _Debug = _zet_debug_dditable_t()
        r = ze_result_v(self.__dll.zetGetDebugProcAddrTable(version, byref(_Debug)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Debug = _Debug

        # attach function interface to function address
        self.zetDebugAttach = _zetDebugAttach_t(self.__dditable.Debug.pfnAttach)
        self.zetDebugDetach = _zetDebugDetach_t(self.__dditable.Debug.pfnDetach)
        self.zetDebugGetNumThreads = _zetDebugGetNumThreads_t(self.__dditable.Debug.pfnGetNumThreads)
        self.zetDebugReadEvent = _zetDebugReadEvent_t(self.__dditable.Debug.pfnReadEvent)
        self.zetDebugInterrupt = _zetDebugInterrupt_t(self.__dditable.Debug.pfnInterrupt)
        self.zetDebugResume = _zetDebugResume_t(self.__dditable.Debug.pfnResume)
        self.zetDebugReadMemory = _zetDebugReadMemory_t(self.__dditable.Debug.pfnReadMemory)
        self.zetDebugWriteMemory = _zetDebugWriteMemory_t(self.__dditable.Debug.pfnWriteMemory)
        self.zetDebugReadState = _zetDebugReadState_t(self.__dditable.Debug.pfnReadState)
        self.zetDebugWriteState = _zetDebugWriteState_t(self.__dditable.Debug.pfnWriteState)

        # success!
