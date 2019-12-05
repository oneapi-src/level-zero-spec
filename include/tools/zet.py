"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

 @file zet.py

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
## @brief Handle for accessing System Resource Management features of a device
class zet_sysman_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device power domain
class zet_sysman_pwr_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device frequency domain
class zet_sysman_freq_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device engine group
class zet_sysman_engine_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device standby control
class zet_sysman_standby_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device firmware
class zet_sysman_firmware_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device memory module
class zet_sysman_mem_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman fabric port
class zet_sysman_fabric_port_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device temperature sensor
class zet_sysman_temp_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device power supply
class zet_sysman_psu_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device fan
class zet_sysman_fan_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device LED
class zet_sysman_led_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device RAS error set
class zet_sysman_ras_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device diagnostics test suite
class zet_sysman_diag_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device event
class zet_sysman_event_handle_t(c_void_p):
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
    DEBUG_EVENT_FLAG_STOPPED = (1 << 0)             ## The reporting thread stopped

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
## @brief API version of Sysman
class zet_sysman_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class zet_sysman_version_t(c_int):
    def __str__(self):
        return str(zet_sysman_version_v(value))


###############################################################################
## @brief Maximum number of characters in string properties.
ZET_STRING_PROPERTY_SIZE = 64

###############################################################################
## @brief Types of accelerator engines
class zet_engine_type_v(IntEnum):
    OTHER = 0                                       ## Undefined types of accelerators.
    COMPUTE = auto()                                ## Engines that process compute kernels.
    _3D = auto()                                    ## Engines that process 3D content
    MEDIA = auto()                                  ## Engines that process media workloads
    DMA = auto()                                    ## Engines that copy blocks of data

class zet_engine_type_t(c_int):
    def __str__(self):
        return str(zet_engine_type_v(value))


###############################################################################
## @brief Device properties
class zet_sysman_properties_t(Structure):
    _fields_ = [
        ("core", ze_device_properties_t),                               ## [out] Core device properties
        ("numSubdevices", c_ulong),                                     ## [out] Number of sub-devices
        ("serialNumber", c_int8_t * ZET_STRING_PROPERTY_SIZE),          ## [out] Manufacturing serial number (NULL terminated string value)
        ("boardNumber", c_int8_t * ZET_STRING_PROPERTY_SIZE),           ## [out] Manufacturing board number (NULL terminated string value)
        ("brandName", c_int8_t * ZET_STRING_PROPERTY_SIZE),             ## [out] Brand name of the device (NULL terminated string value)
        ("modelName", c_int8_t * ZET_STRING_PROPERTY_SIZE),             ## [out] Model name of the device (NULL terminated string value)
        ("vendorName", c_int8_t * ZET_STRING_PROPERTY_SIZE),            ## [out] Vendor name of the device (NULL terminated string value)
        ("driverVersion", c_int8_t * ZET_STRING_PROPERTY_SIZE)          ## [out] Installed driver version (NULL terminated string value)
    ]

###############################################################################
## @brief Scheduler mode
class zet_sched_mode_v(IntEnum):
    TIMEOUT = 0                                     ## Multiple applications or contexts are submitting work to the hardware.
                                                    ## When higher priority work arrives, the scheduler attempts to pause the
                                                    ## current executing work within some timeout interval, then submits the
                                                    ## other work.
    TIMESLICE = auto()                              ## The scheduler attempts to fairly timeslice hardware execution time
                                                    ## between multiple contexts submitting work to the hardware
                                                    ## concurrently.
    EXCLUSIVE = auto()                              ## Any application or context can run indefinitely on the hardware
                                                    ## without being preempted or terminated. All pending work for other
                                                    ## contexts must wait until the running context completes with no further
                                                    ## submitted work.
    COMPUTE_UNIT_DEBUG = auto()                     ## Scheduler ensures that submission of workloads to the hardware is
                                                    ## optimized for compute unit debugging.

class zet_sched_mode_t(c_int):
    def __str__(self):
        return str(zet_sched_mode_v(value))


###############################################################################
## @brief Disable forward progress guard timeout.
ZET_SCHED_WATCHDOG_DISABLE = (~(0ULL))

###############################################################################
## @brief Configuration for timeout scheduler mode (::ZET_SCHED_MODE_TIMEOUT)
class zet_sched_timeout_properties_t(Structure):
    _fields_ = [
        ("watchdogTimeout", c_ulonglong)                                ## [in,out] The maximum time in microseconds that the scheduler will wait
                                                                        ## for a batch of work submitted to a hardware engine to complete or to
                                                                        ## be preempted so as to run another context.
                                                                        ## If this time is exceeded, the hardware engine is reset and the context terminated.
                                                                        ## If set to ::ZET_SCHED_WATCHDOG_DISABLE, a running workload can run as
                                                                        ## long as it wants without being terminated, but preemption attempts to
                                                                        ## run other contexts are permitted but not enforced.
    ]

###############################################################################
## @brief Configuration for timeslice scheduler mode
##        (::ZET_SCHED_MODE_TIMESLICE)
class zet_sched_timeslice_properties_t(Structure):
    _fields_ = [
        ("interval", c_ulonglong),                                      ## [in,out] The average interval in microseconds that a submission for a
                                                                        ## context will run on a hardware engine before being preempted out to
                                                                        ## run a pending submission for another context.
        ("yieldTimeout", c_ulonglong)                                   ## [in,out] The maximum time in microseconds that the scheduler will wait
                                                                        ## to preempt a workload running on an engine before deciding to reset
                                                                        ## the hardware engine and terminating the associated context.
    ]

###############################################################################
## @brief Contains information about a process that has an open connection with
##        this device
## 
## @details
##     - The application can use the process ID to query the OS for the owner
##       and the path to the executable.
class zet_process_state_t(Structure):
    _fields_ = [
        ("processId", c_ulong),                                         ## [out] Host OS process ID.
        ("memSize", c_int64_t),                                         ## [out] Device memory size in bytes allocated by this process (may not
                                                                        ## necessarily be resident on the device at the time of reading).
        ("engines", c_int64_t)                                          ## [out] Bitfield of accelerator engines being used by this process (or
                                                                        ## 1<<::zet_engine_type_t together).
    ]

###############################################################################
## @brief Device repair status
class zet_repair_status_v(IntEnum):
    UNSUPPORTED = 0                                 ## The device does not support in-field repairs.
    NOT_PERFORMED = auto()                          ## The device has never been repaired.
    PERFORMED = auto()                              ## The device has been repaired.

class zet_repair_status_t(c_int):
    def __str__(self):
        return str(zet_repair_status_v(value))


###############################################################################
## @brief PCI address
class zet_pci_address_t(Structure):
    _fields_ = [
        ("domain", c_ulong),                                            ## [out] BDF domain
        ("bus", c_ulong),                                               ## [out] BDF bus
        ("device", c_ulong),                                            ## [out] BDF device
        ("function", c_ulong)                                           ## [out] BDF function
    ]

###############################################################################
## @brief PCI speed
class zet_pci_speed_t(Structure):
    _fields_ = [
        ("gen", c_ulong),                                               ## [out] The link generation
        ("width", c_ulong),                                             ## [out] The number of lanes
        ("maxBandwidth", c_ulonglong),                                  ## [out] The maximum bandwidth in bytes/sec
        ("maxPacketSize", c_ulong)                                      ## [out] Maximum packet size in bytes.
    ]

###############################################################################
## @brief Static PCI properties
class zet_pci_properties_t(Structure):
    _fields_ = [
        ("address", zet_pci_address_t),                                 ## [out] The BDF address
        ("numBars", c_ulong),                                           ## [out] The number of configured bars
        ("maxSpeed", zet_pci_speed_t)                                   ## [out] Fastest port configuration supported by the device.
    ]

###############################################################################
## @brief PCI link status
class zet_pci_link_status_v(IntEnum):
    GREEN = 0                                       ## The link is up and operating as expected
    YELLOW = auto()                                 ## The link is up but has quality and/or bandwidth degradation
    RED = auto()                                    ## The link has stability issues and preventing workloads making forward
                                                    ## progress

class zet_pci_link_status_t(c_int):
    def __str__(self):
        return str(zet_pci_link_status_v(value))


###############################################################################
## @brief PCI link quality degradation reasons
class zet_pci_link_qual_issues_v(IntEnum):
    NONE = 0                                        ## There are no quality issues with the link at this time
    REPLAYS = ZE_BIT( 0 )                           ## An significant number of replays are occurring
    SPEED = ZE_BIT( 1 )                             ## There is a degradation in the maximum bandwidth of the link

class zet_pci_link_qual_issues_t(c_int):
    def __str__(self):
        return str(zet_pci_link_qual_issues_v(value))


###############################################################################
## @brief PCI link stability issues
class zet_pci_link_stab_issues_v(IntEnum):
    NONE = 0                                        ## There are no connection stability issues at this time
    RETRAINING = ZE_BIT( 0 )                        ## Link retraining has occurred to deal with quality issues

class zet_pci_link_stab_issues_t(c_int):
    def __str__(self):
        return str(zet_pci_link_stab_issues_v(value))


###############################################################################
## @brief Dynamic PCI state
class zet_pci_state_t(Structure):
    _fields_ = [
        ("status", zet_pci_link_status_t),                              ## [out] The current status of the port
        ("qualityIssues", zet_pci_link_qual_issues_t),                  ## [out] If status is ::ZET_PCI_LINK_STATUS_YELLOW, this gives a bitfield
                                                                        ## of quality issues that have been detected
        ("stabilityIssues", zet_pci_link_stab_issues_t),                ## [out] If status is ::ZET_PCI_LINK_STATUS_RED, this gives a bitfield of
                                                                        ## reasons for the connection instability
        ("speed", zet_pci_speed_t)                                      ## [out] The current port configure speed
    ]

###############################################################################
## @brief PCI bar types
class zet_pci_bar_type_v(IntEnum):
    CONFIG = 0                                      ## PCI configuration space
    MMIO = auto()                                   ## MMIO registers
    VRAM = auto()                                   ## VRAM aperture
    ROM = auto()                                    ## ROM aperture
    VGA_IO = auto()                                 ## Legacy VGA IO ports
    VGA_MEM = auto()                                ## Legacy VGA memory
    INDIRECT_IO = auto()                            ## Indirect IO port access
    INDIRECT_MEM = auto()                           ## Indirect memory access
    OTHER = auto()                                  ## Other type of PCI bar

class zet_pci_bar_type_t(c_int):
    def __str__(self):
        return str(zet_pci_bar_type_v(value))


###############################################################################
## @brief Properties of a pci bar
class zet_pci_bar_properties_t(Structure):
    _fields_ = [
        ("type", zet_pci_bar_type_t),                                   ## [out] The type of bar
        ("base", c_ulonglong),                                          ## [out] Base address of the bar.
        ("size", c_ulonglong)                                           ## [out] Size of the bar.
    ]

###############################################################################
## @brief PCI stats counters
## 
## @details
##     - Percent throughput is calculated by taking two snapshots (s1, s2) and
##       using the equation: %bw = 10^6 * ((s2.rxCounter - s1.rxCounter) +
##       (s2.txCounter - s1.txCounter)) / (s2.maxBandwidth * (s2.timestamp -
##       s1.timestamp))
##     - Percent replays is calculated by taking two snapshots (s1, s2) and
##       using the equation: %replay = 10^6 * (s2.replayCounter -
##       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
class zet_pci_stats_t(Structure):
    _fields_ = [
        ("timestamp", c_ulonglong),                                     ## [out] Monotonic timestamp counter in microseconds when the measurement
                                                                        ## was made.
                                                                        ## No assumption should be made about the absolute value of the timestamp.
                                                                        ## It should only be used to calculate delta time between two snapshots
                                                                        ## of the same structure.
                                                                        ## Never take the delta of this timestamp with the timestamp from a
                                                                        ## different structure.
        ("replayCounter", c_ulonglong),                                 ## [out] Monotonic counter for the number of replay packets
        ("packetCounter", c_ulonglong),                                 ## [out] Monotonic counter for the number of packets
        ("rxCounter", c_ulonglong),                                     ## [out] Monotonic counter for the number of bytes received
        ("txCounter", c_ulonglong),                                     ## [out] Monotonic counter for the number of bytes transmitted (including
                                                                        ## replays)
        ("maxBandwidth", c_ulonglong)                                   ## [out] The maximum bandwidth in bytes/sec under the current
                                                                        ## configuration
    ]

###############################################################################
## @brief Properties related to device power settings
class zet_power_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Software can change the power limits of this domain assuming the
                                                                        ## user has permissions.
        ("isEnergyThresholdSupported", ze_bool_t),                      ## [out] Indicates if this power domain supports the energy threshold
                                                                        ## event (::ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED).
        ("maxLimit", c_ulong)                                           ## [out] The maximum power limit in milliwatts that can be requested.
    ]

###############################################################################
## @brief Energy counter snapshot
## 
## @details
##     - Average power is calculated by taking two snapshots (s1, s2) and using
##       the equation: PowerWatts = (s2.energy - s1.energy) / (s2.timestamp -
##       s1.timestamp)
class zet_power_energy_counter_t(Structure):
    _fields_ = [
        ("energy", c_ulonglong),                                        ## [out] The monotonic energy counter in microjoules.
        ("timestamp", c_ulonglong)                                      ## [out] Microsecond timestamp when energy was captured.
                                                                        ## No assumption should be made about the absolute value of the timestamp.
                                                                        ## It should only be used to calculate delta time between two snapshots
                                                                        ## of the same structure.
                                                                        ## Never take the delta of this timestamp with the timestamp from a
                                                                        ## different structure.
    ]

###############################################################################
## @brief Sustained power limits
## 
## @details
##     - The power controller (Punit) will throttle the operating frequency if
##       the power averaged over a window (typically seconds) exceeds this
##       limit.
class zet_power_sustained_limit_t(Structure):
    _fields_ = [
        ("enabled", ze_bool_t),                                         ## [in,out] indicates if the limit is enabled (true) or ignored (false)
        ("power", c_ulong),                                             ## [in,out] power limit in milliwatts
        ("interval", c_ulong)                                           ## [in,out] power averaging window (Tau) in milliseconds
    ]

###############################################################################
## @brief Burst power limit
## 
## @details
##     - The power controller (Punit) will throttle the operating frequency of
##       the device if the power averaged over a few milliseconds exceeds a
##       limit known as PL2. Typically PL2 > PL1 so that it permits the
##       frequency to burst higher for short periods than would be otherwise
##       permitted by PL1.
class zet_power_burst_limit_t(Structure):
    _fields_ = [
        ("enabled", ze_bool_t),                                         ## [in,out] indicates if the limit is enabled (true) or ignored (false)
        ("power", c_ulong)                                              ## [in,out] power limit in milliwatts
    ]

###############################################################################
## @brief Peak power limit
## 
## @details
##     - The power controller (Punit) will preemptively throttle the operating
##       frequency of the device when the instantaneous power exceeds this
##       limit. The limit is known as PL4. It expresses the maximum power that
##       can be drawn from the power supply.
##     - If this power limit is removed or set too high, the power supply will
##       generate an interrupt when it detects an overcurrent condition and the
##       power controller will throttle the device frequencies down to min. It
##       is thus better to tune the PL4 value in order to avoid such
##       excursions.
class zet_power_peak_limit_t(Structure):
    _fields_ = [
        ("powerAC", c_ulong),                                           ## [in,out] power limit in milliwatts for the AC power source.
        ("powerDC", c_ulong)                                            ## [in,out] power limit in milliwatts for the DC power source. This is
                                                                        ## ignored if the product does not have a battery.
    ]

###############################################################################
## @brief Energy threshold
## 
## @details
##     - .
class zet_energy_threshold_t(Structure):
    _fields_ = [
        ("enable", ze_bool_t),                                          ## [in,out] Indicates if the energy threshold is enabled.
        ("threshold", c_double),                                        ## [in,out] The energy threshold in Joules. Will be 0.0 if no threshold
                                                                        ## has been set.
        ("processId", c_ulong)                                          ## [in,out] The host process ID that set the energy threshold. Will be -1
                                                                        ## if no threshold has been set.
    ]

###############################################################################
## @brief Frequency domains.
class zet_freq_domain_v(IntEnum):
    GPU = 0                                         ## GPU Core Domain.
    MEMORY = auto()                                 ## Local Memory Domain.

class zet_freq_domain_t(c_int):
    def __str__(self):
        return str(zet_freq_domain_v(value))


###############################################################################
## @brief Frequency properties
## 
## @details
##     - Indicates if this frequency domain can be overclocked (if true,
##       functions such as ::zetSysmanFrequencyOcSetConfig() are supported).
##     - The min/max hardware frequencies are specified for non-overclock
##       configurations. For overclock configurations, use
##       ::zetSysmanFrequencyOcGetConfig() to determine the maximum frequency
##       that can be requested.
##     - If step is non-zero, the available frequencies are (min, min + step,
##       min + 2xstep, ..., max). Otherwise, call
##       ::zetSysmanFrequencyGetAvailableClocks() to get the list of
##       frequencies that can be requested.
class zet_freq_properties_t(Structure):
    _fields_ = [
        ("type", zet_freq_domain_t),                                    ## [out] The hardware block that this frequency domain controls (GPU,
                                                                        ## memory, ...)
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can control the frequency of this domain
                                                                        ## assuming the user has permissions
        ("isThrottleEventSupported", ze_bool_t),                        ## [out] Indicates if software can register to receive event
                                                                        ## ::ZET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED
        ("min", c_double),                                              ## [out] The minimum hardware clock frequency in units of MHz
        ("max", c_double),                                              ## [out] The maximum non-overclock hardware clock frequency in units of
                                                                        ## MHz.
        ("step", c_double)                                              ## [out] The minimum step-size for clock frequencies in units of MHz. The
                                                                        ## hardware will clamp intermediate frequencies to lowest multiplier of
                                                                        ## this number.
    ]

###############################################################################
## @brief Frequency range between which the hardware can operate.
class zet_freq_range_t(Structure):
    _fields_ = [
        ("min", c_double),                                              ## [in,out] The min frequency in MHz below which hardware frequency
                                                                        ## management will not request frequencies. Setting to 0 will use the
                                                                        ## hardware default value.
        ("max", c_double)                                               ## [in,out] The max frequency in MHz above which hardware frequency
                                                                        ## management will not request frequencies. Setting to 0 will use the
                                                                        ## hardware default value.
    ]

###############################################################################
## @brief Frequency throttle reasons
class zet_freq_throttle_reasons_v(IntEnum):
    NONE = 0                                        ## frequency not throttled
    AVE_PWR_CAP = ZE_BIT( 0 )                       ## frequency throttled due to average power excursion (PL1)
    BURST_PWR_CAP = ZE_BIT( 1 )                     ## frequency throttled due to burst power excursion (PL2)
    CURRENT_LIMIT = ZE_BIT( 2 )                     ## frequency throttled due to current excursion (PL4)
    THERMAL_LIMIT = ZE_BIT( 3 )                     ## frequency throttled due to thermal excursion (T > TjMax)
    PSU_ALERT = ZE_BIT( 4 )                         ## frequency throttled due to power supply assertion
    SW_RANGE = ZE_BIT( 5 )                          ## frequency throttled due to software supplied frequency range
    HW_RANGE = ZE_BIT( 6 )                          ## frequency throttled due to a sub block that has a lower frequency
                                                    ## range when it receives clocks

class zet_freq_throttle_reasons_t(c_int):
    def __str__(self):
        return str(zet_freq_throttle_reasons_v(value))


###############################################################################
## @brief Frequency state
class zet_freq_state_t(Structure):
    _fields_ = [
        ("request", c_double),                                          ## [out] The current frequency request in MHz.
        ("tdp", c_double),                                              ## [out] The maximum frequency in MHz supported under the current TDP
                                                                        ## conditions
        ("efficient", c_double),                                        ## [out] The efficient minimum frequency in MHz
        ("actual", c_double),                                           ## [out] The resolved frequency in MHz
        ("throttleReasons", c_ulong)                                    ## [out] The reasons that the frequency is being limited by the hardware
                                                                        ## (Bitfield of ::zet_freq_throttle_reasons_t).
    ]

###############################################################################
## @brief Frequency throttle time snapshot
## 
## @details
##     - Percent time throttled is calculated by taking two snapshots (s1, s2)
##       and using the equation: %throttled = (s2.throttleTime -
##       s1.throttleTime) / (s2.timestamp - s1.timestamp)
class zet_freq_throttle_time_t(Structure):
    _fields_ = [
        ("throttleTime", c_ulonglong),                                  ## [out] The monotonic counter of time in microseconds that the frequency
                                                                        ## has been limited by the hardware.
        ("timestamp", c_ulonglong)                                      ## [out] Microsecond timestamp when throttleTime was captured.
                                                                        ## No assumption should be made about the absolute value of the timestamp.
                                                                        ## It should only be used to calculate delta time between two snapshots
                                                                        ## of the same structure.
                                                                        ## Never take the delta of this timestamp with the timestamp from a
                                                                        ## different structure.
    ]

###############################################################################
## @brief Overclocking modes
class zet_oc_mode_v(IntEnum):
    OFF = 0                                         ## Overclocking if off - hardware is running using factory default
                                                    ## voltages/frequencies.
    OVERRIDE = auto()                               ## Overclock override mode - In this mode, a fixed user-supplied voltage
                                                    ## is applied independent of the frequency request. The maximum permitted
                                                    ## frequency can also be increased.
    INTERPOLATIVE = auto()                          ## Overclock interpolative mode - In this mode, the voltage/frequency
                                                    ## curve can be extended with a new voltage/frequency point that will be
                                                    ## interpolated. The existing voltage/frequency points can also be offset
                                                    ## (up or down) by a fixed voltage.

class zet_oc_mode_t(c_int):
    def __str__(self):
        return str(zet_oc_mode_v(value))


###############################################################################
## @brief Overclocking properties
## 
## @details
##     - Provides all the overclocking capabilities and properties supported by
##       the device for the frequency domain.
class zet_oc_capabilities_t(Structure):
    _fields_ = [
        ("isOcSupported", ze_bool_t),                                   ## [out] Indicates if any overclocking features are supported on this
                                                                        ## frequency domain.
        ("maxFactoryDefaultFrequency", c_double),                       ## [out] Factory default non-overclock maximum frequency in Mhz.
        ("maxFactoryDefaultVoltage", c_double),                         ## [out] Factory default voltage used for the non-overclock maximum
                                                                        ## frequency in MHz.
        ("maxOcFrequency", c_double),                                   ## [out] Maximum hardware overclocking frequency limit in Mhz.
        ("minOcVoltageOffset", c_double),                               ## [out] The minimum voltage offset that can be applied to the
                                                                        ## voltage/frequency curve. Note that this number can be negative.
        ("maxOcVoltageOffset", c_double),                               ## [out] The maximum voltage offset that can be applied to the
                                                                        ## voltage/frequency curve.
        ("maxOcVoltage", c_double),                                     ## [out] The maximum overclock voltage that hardware supports.
        ("isTjMaxSupported", ze_bool_t),                                ## [out] Indicates if the maximum temperature limit (TjMax) can be
                                                                        ## changed for this frequency domain.
        ("isIccMaxSupported", ze_bool_t),                               ## [out] Indicates if the maximum current (IccMax) can be changed for
                                                                        ## this frequency domain.
        ("isHighVoltModeCapable", ze_bool_t),                           ## [out] Indicates if this frequency domains supports a feature to set
                                                                        ## very high voltages.
        ("isHighVoltModeEnabled", ze_bool_t)                            ## [out] Indicates if very high voltages are permitted on this frequency
                                                                        ## domain.
    ]

###############################################################################
## @brief Overclocking configuration
## 
## @details
##     - Overclock settings
class zet_oc_config_t(Structure):
    _fields_ = [
        ("mode", zet_oc_mode_t),                                        ## [in,out] Overclock Mode ::zet_oc_mode_t.
        ("frequency", c_double),                                        ## [in,out] Overclocking Frequency in MHz. This cannot be greater than
                                                                        ## ::zet_oc_capabilities_t.maxOcFrequency.
        ("voltageTarget", c_double),                                    ## [in,out] Overclock voltage in Volts. This cannot be greater than
                                                                        ## ::zet_oc_capabilities_t.maxOcVoltage.
        ("voltageOffset", c_double)                                     ## [in,out] This voltage offset is applied to all points on the
                                                                        ## voltage/frequency curve, include the new overclock voltageTarget. It
                                                                        ## can be in the range (::zet_oc_capabilities_t.minOcVoltageOffset,
                                                                        ## ::zet_oc_capabilities_t.maxOcVoltageOffset).
    ]

###############################################################################
## @brief Accelerator engine groups
class zet_engine_group_v(IntEnum):
    ALL = 0                                         ## Access information about all engines combined.
    COMPUTE_ALL = auto()                            ## Access information about all compute engines combined.
    MEDIA_ALL = auto()                              ## Access information about all media engines combined.
    COPY_ALL = auto()                               ## Access information about all copy (blitter) engines combined.

class zet_engine_group_t(c_int):
    def __str__(self):
        return str(zet_engine_group_v(value))


###############################################################################
## @brief Engine group properties
class zet_engine_properties_t(Structure):
    _fields_ = [
        ("type", zet_engine_group_t),                                   ## [out] The engine group
        ("engines", c_int64_t),                                         ## [out] Bitfield of accelerator engines counted by this group.
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
    ]

###############################################################################
## @brief Engine activity counters
## 
## @details
##     - Percent utilization is calculated by taking two snapshots (s1, s2) and
##       using the equation: %util = (s2.activeTime - s1.activeTime) /
##       (s2.timestamp - s1.timestamp)
class zet_engine_stats_t(Structure):
    _fields_ = [
        ("activeTime", c_ulonglong),                                    ## [out] Monotonic counter for time in microseconds that this resource is
                                                                        ## actively running workloads.
        ("timestamp", c_ulonglong)                                      ## [out] Monotonic timestamp counter in microseconds when activeTime
                                                                        ## counter was sampled.
                                                                        ## No assumption should be made about the absolute value of the timestamp.
                                                                        ## It should only be used to calculate delta time between two snapshots
                                                                        ## of the same structure.
                                                                        ## Never take the delta of this timestamp with the timestamp from a
                                                                        ## different structure.
    ]

###############################################################################
## @brief Standby hardware components
class zet_standby_type_v(IntEnum):
    GLOBAL = 0                                      ## Control the overall standby policy of the device/sub-device

class zet_standby_type_t(c_int):
    def __str__(self):
        return str(zet_standby_type_v(value))


###############################################################################
## @brief Standby hardware component properties
class zet_standby_properties_t(Structure):
    _fields_ = [
        ("type", zet_standby_type_t),                                   ## [out] Which standby hardware component this controls
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
    ]

###############################################################################
## @brief Standby promotion modes
class zet_standby_promo_mode_v(IntEnum):
    DEFAULT = 0                                     ## Best compromise between performance and energy savings.
    NEVER = auto()                                  ## The device/component will never shutdown. This can improve performance
                                                    ## but uses more energy.

class zet_standby_promo_mode_t(c_int):
    def __str__(self):
        return str(zet_standby_promo_mode_v(value))


###############################################################################
## @brief Firmware properties
class zet_firmware_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can flash the firmware assuming the user
                                                                        ## has permissions
        ("name", c_int8_t * ZET_STRING_PROPERTY_SIZE),                  ## [out] NULL terminated string value
        ("version", c_int8_t * ZET_STRING_PROPERTY_SIZE)                ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Memory module types
class zet_mem_type_v(IntEnum):
    HBM = 0                                         ## HBM memory
    DDR = auto()                                    ## DDR memory
    SRAM = auto()                                   ## SRAM memory
    L1 = auto()                                     ## L1 cache
    L3 = auto()                                     ## L3 cache
    GRF = auto()                                    ## Execution unit register file
    SLM = auto()                                    ## Execution unit shared local memory

class zet_mem_type_t(c_int):
    def __str__(self):
        return str(zet_mem_type_v(value))


###############################################################################
## @brief Memory health
class zet_mem_health_v(IntEnum):
    OK = 0                                          ## All memory channels are healthy
    DEGRADED = auto()                               ## Excessive correctable errors have been detected on one or more
                                                    ## channels. Device should be reset.
    CRITICAL = auto()                               ## Operating with reduced memory to cover banks with too many
                                                    ## uncorrectable errors.
    REPLACE = auto()                                ## Device should be replaced due to excessive uncorrectable errors.

class zet_mem_health_t(c_int):
    def __str__(self):
        return str(zet_mem_health_v(value))


###############################################################################
## @brief Memory properties
class zet_mem_properties_t(Structure):
    _fields_ = [
        ("type", zet_mem_type_t),                                       ## [out] The memory type
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("physicalSize", c_ulonglong)                                   ## [out] Physical memory size in bytes
    ]

###############################################################################
## @brief Memory state - health, allocated
## 
## @details
##     - Percent allocation is given by 100 * allocatedSize / maxSize.
##     - Percent free is given by 100 * (maxSize - allocatedSize) / maxSize.
class zet_mem_state_t(Structure):
    _fields_ = [
        ("health", zet_mem_health_t),                                   ## [out] Indicates the health of the memory
        ("allocatedSize", c_ulonglong),                                 ## [out] The total allocated bytes
        ("maxSize", c_ulonglong)                                        ## [out] The total allocatable memory in bytes (can be less than
                                                                        ## ::zet_mem_properties_t.physicalSize)
    ]

###############################################################################
## @brief Memory bandwidth
## 
## @details
##     - Percent bandwidth is calculated by taking two snapshots (s1, s2) and
##       using the equation: %bw = 10^6 * ((s2.readCounter - s1.readCounter) +
##       (s2.writeCounter - s1.writeCounter)) / (s2.maxBandwidth *
##       (s2.timestamp - s1.timestamp))
class zet_mem_bandwidth_t(Structure):
    _fields_ = [
        ("readCounter", c_ulonglong),                                   ## [out] Total bytes read from memory
        ("writeCounter", c_ulonglong),                                  ## [out] Total bytes written to memory
        ("maxBandwidth", c_ulonglong),                                  ## [out] Current maximum bandwidth in units of bytes/sec
        ("timestamp", c_ulonglong)                                      ## [out] The timestamp when these measurements were sampled.
                                                                        ## No assumption should be made about the absolute value of the timestamp.
                                                                        ## It should only be used to calculate delta time between two snapshots
                                                                        ## of the same structure.
                                                                        ## Never take the delta of this timestamp with the timestamp from a
                                                                        ## different structure.
    ]

###############################################################################
## @brief Maximum Fabric port model string size
ZET_MAX_FABRIC_PORT_MODEL_SIZE = 256

###############################################################################
## @brief Maximum fabric port uuid size in bytes
ZET_MAX_FABRIC_PORT_UUID_SIZE = 72

###############################################################################
## @brief Maximum size of the buffer that will return information about link
##        types
ZET_MAX_FABRIC_LINK_TYPE_SIZE = 256

###############################################################################
## @brief Fabric port status
class zet_fabric_port_status_v(IntEnum):
    GREEN = 0                                       ## The port is up and operating as expected
    YELLOW = auto()                                 ## The port is up but has quality and/or bandwidth degradation
    RED = auto()                                    ## Port connection instabilities are preventing workloads making forward
                                                    ## progress
    BLACK = auto()                                  ## The port is configured down

class zet_fabric_port_status_t(c_int):
    def __str__(self):
        return str(zet_fabric_port_status_v(value))


###############################################################################
## @brief Fabric port quality degradation reasons
class zet_fabric_port_qual_issues_v(IntEnum):
    NONE = 0                                        ## There are no quality issues with the link at this time
    FEC = ZE_BIT( 0 )                               ## Excessive FEC (forward error correction) are occurring
    LTP_CRC = ZE_BIT( 1 )                           ## Excessive LTP CRC failure induced replays are occurring
    SPEED = ZE_BIT( 2 )                             ## There is a degradation in the maximum bandwidth of the port

class zet_fabric_port_qual_issues_t(c_int):
    def __str__(self):
        return str(zet_fabric_port_qual_issues_v(value))


###############################################################################
## @brief Fabric port stability issues
class zet_fabric_port_stab_issues_v(IntEnum):
    NONE = 0                                        ## There are no connection stability issues at this time
    TOO_MANY_REPLAYS = ZE_BIT( 0 )                  ## Sequential replay failure is inducing link retraining
    NO_CONNECT = ZE_BIT( 1 )                        ## A connection was never able to be established through the link
    FLAPPING = ZE_BIT( 2 )                          ## The port is flapping

class zet_fabric_port_stab_issues_t(c_int):
    def __str__(self):
        return str(zet_fabric_port_stab_issues_v(value))


###############################################################################
## @brief Fabric port universal unique id (UUID)
class zet_fabric_port_uuid_t(Structure):
    _fields_ = [
        ("id", c_ubyte * ZET_MAX_FABRIC_PORT_UUID_SIZE)                 ## [out] Frabric port universal unique id
    ]

###############################################################################
## @brief Fabric port speed in one direction
class zet_fabric_port_speed_t(Structure):
    _fields_ = [
        ("bitRate", c_ulonglong),                                       ## [out] Bits/sec that the link is operating at
        ("width", c_ulong),                                             ## [out] The number of lanes
        ("maxBandwidth", c_ulonglong)                                   ## [out] The maximum bandwidth in bytes/sec
    ]

###############################################################################
## @brief Fabric port properties
class zet_fabric_port_properties_t(Structure):
    _fields_ = [
        ("model", c_int8_t * ZET_MAX_FABRIC_PORT_MODEL_SIZE),           ## [out] Description of port technology
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the port is located on a sub-device; false means that
                                                                        ## the port is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("portUuid", zet_fabric_port_uuid_t),                           ## [out] The port universal unique id
        ("maxRxSpeed", zet_fabric_port_speed_t),                        ## [out] Maximum bandwidth supported by the receive side of the port
        ("maxTxSpeed", zet_fabric_port_speed_t)                         ## [out] Maximum bandwidth supported by the transmit side of the port
    ]

###############################################################################
## @brief Provides information about the fabric link attached to a port
class zet_fabric_link_type_t(Structure):
    _fields_ = [
        ("desc", c_int8_t * ZET_MAX_FABRIC_LINK_TYPE_SIZE)              ## [out] This provides a textural description of a link attached to a
                                                                        ## port. It contains the following information:
                                                                        ## - Link material
                                                                        ## - Link technology
                                                                        ## - Cable manufacturer
                                                                        ## - Temperature
                                                                        ## - Power
                                                                        ## - Attachment type:
                                                                        ##    - Disconnected
                                                                        ##    - Hardwired/fixed/etched connector
                                                                        ##    - Active copper
                                                                        ##    - QSOP
                                                                        ##    - AOC
    ]

###############################################################################
## @brief Fabric port configuration
class zet_fabric_port_config_t(Structure):
    _fields_ = [
        ("enabled", ze_bool_t),                                         ## [in,out] Port is configured up/down
        ("beaconing", ze_bool_t)                                        ## [in,out] Beaconing is configured on/off
    ]

###############################################################################
## @brief Fabric port state
class zet_fabric_port_state_t(Structure):
    _fields_ = [
        ("status", zet_fabric_port_status_t),                           ## [out] The current status of the port
        ("qualityIssues", zet_fabric_port_qual_issues_t),               ## [out] If status is ::ZET_FABRIC_PORT_STATUS_YELLOW, this gives a
                                                                        ## bitfield of quality issues that have been detected
        ("stabilityIssues", zet_fabric_port_stab_issues_t),             ## [out] If status is ::ZET_FABRIC_PORT_STATUS_RED, this gives a bitfield
                                                                        ## of reasons for the connection instability
        ("rxSpeed", zet_fabric_port_speed_t),                           ## [out] Current maximum receive speed
        ("txSpeed", zet_fabric_port_speed_t)                            ## [out] Current maximum transmit speed
    ]

###############################################################################
## @brief Fabric port throughput
## 
## @details
##     - Percent throughput is calculated by taking two snapshots (s1, s2) and
##       using the equation:
##     -     %rx_bandwidth = 10^6 * (s2.rxCounter - s1.rxCounter) /
##       (s2.rxMaxBandwidth * (s2.timestamp - s1.timestamp))
##     -     %tx_bandwidth = 10^6 * (s2.txCounter - s1.txCounter) /
##       (s2.txMaxBandwidth * (s2.timestamp - s1.timestamp))
class zet_fabric_port_throughput_t(Structure):
    _fields_ = [
        ("timestamp", c_ulonglong),                                     ## [out] Monotonic timestamp counter in microseconds when the measurement
                                                                        ## was made.
                                                                        ## No assumption should be made about the absolute value of the timestamp.
                                                                        ## It should only be used to calculate delta time between two snapshots
                                                                        ## of the same structure.
                                                                        ## Never take the delta of this timestamp with the timestamp from a
                                                                        ## different structure.
        ("rxCounter", c_ulonglong),                                     ## [out] Monotonic counter for the number of bytes received
        ("txCounter", c_ulonglong),                                     ## [out] Monotonic counter for the number of bytes transmitted
        ("rxMaxBandwidth", c_ulonglong),                                ## [out] The current maximum bandwidth in bytes/sec for receiving packats
        ("txMaxBandwidth", c_ulonglong)                                 ## [out] The current maximum bandwidth in bytes/sec for transmitting
                                                                        ## packets
    ]

###############################################################################
## @brief Temperature sensors
class zet_temp_sensors_v(IntEnum):
    GLOBAL = 0                                      ## The maximum temperature across all device sensors
    GPU = auto()                                    ## The maximum temperature across all sensors in the GPU
    MEMORY = auto()                                 ## The maximum temperature across all sensors in the local memory

class zet_temp_sensors_t(c_int):
    def __str__(self):
        return str(zet_temp_sensors_v(value))


###############################################################################
## @brief Temperature sensor properties
class zet_temp_properties_t(Structure):
    _fields_ = [
        ("type", zet_temp_sensors_t),                                   ## [out] Which part of the device the temperature sensor measures
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("isCriticalTempSupported", ze_bool_t),                         ## [out] Indicates if the critical temperature event
                                                                        ## ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL is supported
        ("isThreshold1Supported", ze_bool_t),                           ## [out] Indicates if the temperature threshold 1 event
                                                                        ## ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 is supported
        ("isThreshold2Supported", ze_bool_t)                            ## [out] Indicates if the temperature threshold 2 event
                                                                        ## ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 is supported
    ]

###############################################################################
## @brief Temperature sensor threshold
class zet_temp_threshold_t(Structure):
    _fields_ = [
        ("enableLowToHigh", ze_bool_t),                                 ## [in,out] Trigger an event when the temperature crosses from below the
                                                                        ## threshold to above.
        ("enableHighToLow", ze_bool_t),                                 ## [in,out] Trigger an event when the temperature crosses from above the
                                                                        ## threshold to below.
        ("threshold", c_double)                                         ## [in,out] The threshold in degrees Celcius.
    ]

###############################################################################
## @brief Temperature configuration - which events should be triggered and the
##        trigger conditions.
class zet_temp_config_t(Structure):
    _fields_ = [
        ("enableCritical", ze_bool_t),                                  ## [in,out] Indicates if event ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL
                                                                        ## should be triggered by the driver.
        ("threshold1", zet_temp_threshold_t),                           ## [in,out] Configuration controlling if and when event
                                                                        ## ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 should be triggered by the
                                                                        ## driver.
        ("threshold2", zet_temp_threshold_t),                           ## [in,out] Configuration controlling if and when event
                                                                        ## ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 should be triggered by the
                                                                        ## driver.
        ("processId", c_ulong)                                          ## [out] Host processId that set this configuration (ignored when setting
                                                                        ## the configuration).
    ]

###############################################################################
## @brief PSU voltage status
class zet_psu_voltage_status_v(IntEnum):
    NORMAL = 0                                      ## No unusual voltages have been detected
    OVER = auto()                                   ## Over-voltage has occurred
    UNDER = auto()                                  ## Under-voltage has occurred

class zet_psu_voltage_status_t(c_int):
    def __str__(self):
        return str(zet_psu_voltage_status_v(value))


###############################################################################
## @brief Static properties of the power supply
class zet_psu_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can control the PSU assuming the user has
                                                                        ## permissions
        ("haveFan", ze_bool_t),                                         ## [out] True if the power supply has a fan
        ("ampLimit", c_ulong)                                           ## [out] The maximum electrical current in amperes that can be drawn
    ]

###############################################################################
## @brief Dynamic state of the power supply
class zet_psu_state_t(Structure):
    _fields_ = [
        ("voltStatus", zet_psu_voltage_status_t),                       ## [out] The current PSU voltage status
        ("fanFailed", ze_bool_t),                                       ## [out] Indicates if the fan has failed
        ("temperature", c_ulong),                                       ## [out] Read the current heatsink temperature in degrees Celsius.
        ("current", c_ulong)                                            ## [out] The amps being drawn in amperes
    ]

###############################################################################
## @brief Fan resource speed mode
class zet_fan_speed_mode_v(IntEnum):
    DEFAULT = 0                                     ## The fan speed is operating using the hardware default settings
    FIXED = auto()                                  ## The fan speed is currently set to a fixed value
    TABLE = auto()                                  ## The fan speed is currently controlled dynamically by hardware based on
                                                    ## a temp/speed table

class zet_fan_speed_mode_t(c_int):
    def __str__(self):
        return str(zet_fan_speed_mode_v(value))


###############################################################################
## @brief Fan speed units
class zet_fan_speed_units_v(IntEnum):
    RPM = 0                                         ## The fan speed is in units of revolutions per minute (rpm)
    PERCENT = auto()                                ## The fan speed is a percentage of the maximum speed of the fan

class zet_fan_speed_units_t(c_int):
    def __str__(self):
        return str(zet_fan_speed_units_v(value))


###############################################################################
## @brief Fan temperature/speed pair
class zet_fan_temp_speed_t(Structure):
    _fields_ = [
        ("temperature", c_ulong),                                       ## [in,out] Temperature in degrees Celsius.
        ("speed", c_ulong),                                             ## [in,out] The speed of the fan
        ("units", zet_fan_speed_units_t)                                ## [in,out] The units of the member speed
    ]

###############################################################################
## @brief Maximum number of fan temperature/speed pairs in the fan speed table.
ZET_FAN_TEMP_SPEED_PAIR_COUNT = 32

###############################################################################
## @brief Fan properties
class zet_fan_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can control the fan speed assuming the
                                                                        ## user has permissions
        ("maxSpeed", c_ulong),                                          ## [out] The maximum RPM of the fan
        ("maxPoints", c_ulong)                                          ## [out] The maximum number of points in the fan temp/speed table
    ]

###############################################################################
## @brief Fan configuration
class zet_fan_config_t(Structure):
    _fields_ = [
        ("mode", zet_fan_speed_mode_t),                                 ## [in,out] The fan speed mode (fixed, temp-speed table)
        ("speed", c_ulong),                                             ## [in,out] The fixed fan speed setting
        ("speedUnits", zet_fan_speed_units_t),                          ## [in,out] The units of the fixed fan speed setting
        ("numPoints", c_ulong),                                         ## [in,out] The number of valid points in the fan speed table
        ("table", zet_fan_temp_speed_t * ZET_FAN_TEMP_SPEED_PAIR_COUNT) ## [in,out] Array of temperature/fan speed pairs
    ]

###############################################################################
## @brief LED properties
class zet_led_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can control the LED assuming the user has
                                                                        ## permissions
        ("haveRGB", ze_bool_t)                                          ## [out] Indicates if the LED is RGB capable
    ]

###############################################################################
## @brief LED state
class zet_led_state_t(Structure):
    _fields_ = [
        ("isOn", ze_bool_t),                                            ## [in,out] Indicates if the LED is on or off
        ("red", c_ubyte),                                               ## [in,out][range(0, 255)] The LED red value
        ("green", c_ubyte),                                             ## [in,out][range(0, 255)] The LED green value
        ("blue", c_ubyte)                                               ## [in,out][range(0, 255)] The LED blue value
    ]

###############################################################################
## @brief RAS error type
class zet_ras_error_type_v(IntEnum):
    CORRECTABLE = 0                                 ## Errors were corrected by hardware
    UNCORRECTABLE = auto()                          ## Error were not corrected

class zet_ras_error_type_t(c_int):
    def __str__(self):
        return str(zet_ras_error_type_v(value))


###############################################################################
## @brief RAS properties
class zet_ras_properties_t(Structure):
    _fields_ = [
        ("type", zet_ras_error_type_t),                                 ## [out] The type of RAS error
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
    ]

###############################################################################
## @brief RAS error details
class zet_ras_details_t(Structure):
    _fields_ = [
        ("numResets", c_ulonglong),                                     ## [out] The number of device resets that have taken place
        ("numProgrammingErrors", c_ulonglong),                          ## [out] The number of hardware exceptions generated by the way workloads
                                                                        ## have programmed the hardware
        ("numDriverErrors", c_ulonglong),                               ## [out] The number of low level driver communication errors have
                                                                        ## occurred
        ("numComputeErrors", c_ulonglong),                              ## [out] The number of errors that have occurred in the compute
                                                                        ## accelerator hardware
        ("numNonComputeErrors", c_ulonglong),                           ## [out] The number of errors that have occurred in the fixed-function
                                                                        ## accelerator hardware
        ("numCacheErrors", c_ulonglong),                                ## [out] The number of errors that have occurred in caches
                                                                        ## (L1/L3/register file/shared local memory/sampler)
        ("numDisplayErrors", c_ulonglong)                               ## [out] The number of errors that have occurred in the display
    ]

###############################################################################
## @brief RAS error configuration - thresholds used for triggering RAS events
##        (::ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS,
##        ::ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS)
## 
## @details
##     - The driver maintains a total counter which is updated every time a
##       hardware block covered by the corresponding RAS error set notifies
##       that an error has occurred. When this total count goes above the
##       totalThreshold specified below, a RAS event is triggered.
##     - The driver also maintains a counter for each category of RAS error
##       (see ::zet_ras_details_t for a breakdown). Each time a hardware block
##       of that category notifies that an error has occurred, that
##       corresponding category counter is updated. When it goes above the
##       threshold specified in detailedThresholds, a RAS event is triggered.
class zet_ras_config_t(Structure):
    _fields_ = [
        ("totalThreshold", c_ulonglong),                                ## [in,out] If the total RAS errors exceeds this threshold, the event
                                                                        ## will be triggered. A value of 0ULL disables triggering the event based
                                                                        ## on the total counter.
        ("detailedThresholds", zet_ras_details_t),                      ## [in,out] If the RAS errors for each category exceed the threshold for
                                                                        ## that category, the event will be triggered. A value of 0ULL will
                                                                        ## disable an event being triggered for that category.
        ("processId", c_ulong)                                          ## [out] Host processId that set this configuration (ignored when setting
                                                                        ## the configuration).
    ]

###############################################################################
## @brief Event types
class zet_sysman_event_type_v(IntEnum):
    NONE = 0                                        ## Specifies no events
    DEVICE_RESET = ZE_BIT( 0 )                      ## Event is triggered when the driver is going to reset the device
    DEVICE_SLEEP_STATE_ENTER = ZE_BIT( 1 )          ## Event is triggered when the driver is about to put the device into a
                                                    ## deep sleep state
    DEVICE_SLEEP_STATE_EXIT = ZE_BIT( 2 )           ## Event is triggered when the driver is waking the device up from a deep
                                                    ## sleep state
    FREQ_THROTTLED = ZE_BIT( 3 )                    ## Event is triggered when the frequency starts being throttled
    ENERGY_THRESHOLD_CROSSED = ZE_BIT( 4 )          ## Event is triggered when the energy consumption threshold is reached
                                                    ## (use ::zetSysmanPowerSetEnergyThreshold() to configure).
    TEMP_CRITICAL = ZE_BIT( 5 )                     ## Event is triggered when the critical temperature is reached (use
                                                    ## ::zetSysmanTemperatureSetConfig() to configure - disabled by default).
    TEMP_THRESHOLD1 = ZE_BIT( 6 )                   ## Event is triggered when the temperature crosses threshold 1 (use
                                                    ## ::zetSysmanTemperatureSetConfig() to configure - disabled by default).
    TEMP_THRESHOLD2 = ZE_BIT( 7 )                   ## Event is triggered when the temperature crosses threshold 2 (use
                                                    ## ::zetSysmanTemperatureSetConfig() to configure - disabled by default).
    MEM_HEALTH = ZE_BIT( 8 )                        ## Event is triggered when the health of device memory changes.
    FABRIC_PORT_HEALTH = ZE_BIT( 9 )                ## Event is triggered when the health of fabric ports change.
    PCI_LINK_HEALTH = ZE_BIT( 10 )                  ## Event is triggered when the health of the PCI link changes.
    RAS_CORRECTABLE_ERRORS = ZE_BIT( 11 )           ## Event is triggered when accelerator RAS correctable errors cross
                                                    ## thresholds (use ::zetSysmanRasSetConfig() to configure - disabled by
                                                    ## default).
    RAS_UNCORRECTABLE_ERRORS = ZE_BIT( 12 )         ## Event is triggered when accelerator RAS uncorrectable errors cross
                                                    ## thresholds (use ::zetSysmanRasSetConfig() to configure - disabled by
                                                    ## default).
    ALL = (~0)                                      ## Specifies all events

class zet_sysman_event_type_t(c_int):
    def __str__(self):
        return str(zet_sysman_event_type_v(value))


###############################################################################
## @brief Event configuration for a device
class zet_event_config_t(Structure):
    _fields_ = [
        ("registered", c_ulong)                                         ## [in,out] List of registered events (Bitfield of events
                                                                        ## ::zet_sysman_event_type_t). ::ZET_SYSMAN_EVENT_TYPE_NONE indicates
                                                                        ## there are no registered events. ::ZET_SYSMAN_EVENT_TYPE_ALL indicates
                                                                        ## that all events are registered.
    ]

###############################################################################
## @brief Don't wait - just check if there are any new events
ZET_EVENT_WAIT_NONE = 0x0

###############################################################################
## @brief Wait infinitely for events to arrive.
ZET_EVENT_WAIT_INFINITE = 0xFFFFFFFF

###############################################################################
## @brief Diagnostic test suite type
class zet_diag_type_v(IntEnum):
    SCAN = 0                                        ## Run SCAN diagnostics
    ARRAY = auto()                                  ## Run Array diagnostics

class zet_diag_type_t(c_int):
    def __str__(self):
        return str(zet_diag_type_v(value))


###############################################################################
## @brief Diagnostic results
class zet_diag_result_v(IntEnum):
    NO_ERRORS = 0                                   ## Diagnostic completed without finding errors to repair
    ABORT = auto()                                  ## Diagnostic had problems running tests
    FAIL_CANT_REPAIR = auto()                       ## Diagnostic had problems setting up repairs
    REBOOT_FOR_REPAIR = auto()                      ## Diagnostics found errors, setup for repair and reboot is required to
                                                    ## complete the process

class zet_diag_result_t(c_int):
    def __str__(self):
        return str(zet_diag_result_v(value))


###############################################################################
## @brief Diagnostic test index to use for the very first test.
ZET_DIAG_FIRST_TEST_INDEX = 0x0

###############################################################################
## @brief Diagnostic test index to use for the very last test.
ZET_DIAG_LAST_TEST_INDEX = 0xFFFFFFFF

###############################################################################
## @brief Diagnostic test
class zet_diag_test_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [out] Index of the test
        ("name", c_char * ZET_STRING_PROPERTY_SIZE)                     ## [out] Name of the test
    ]

###############################################################################
## @brief Diagnostics test suite properties
class zet_diag_properties_t(Structure):
    _fields_ = [
        ("type", zet_diag_type_t),                                      ## [out] The type of diagnostics test suite
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("name", c_char * ZET_STRING_PROPERTY_SIZE),                    ## [out] Name of the diagnostics test suite
        ("haveTests", ze_bool_t)                                        ## [out] Indicates if this test suite has individual tests which can be
                                                                        ## run separately (use the function $SysmanDiagnosticsGetTests() to get
                                                                        ## the list of these tests)
    ]

###############################################################################
## @brief Alias the existing callbacks definition for 'core' callbacks
class zet_core_callbacks_t(ze_callbacks_t):
    pass

###############################################################################
## @brief Alias the existing callbacks definition for 'experimental' callbacks
class zet_experimental_callbacks_t(zex_callbacks_t):
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
## @brief Function-pointer for zetInit
if __use_win_types:
    _zetInit_t = WINFUNCTYPE( ze_result_t, ze_init_flag_t )
else:
    _zetInit_t = CFUNCTYPE( ze_result_t, ze_init_flag_t )


###############################################################################
## @brief Table of Global functions pointers
class _zet_global_dditable_t(Structure):
    _fields_ = [
        ("pfnInit", c_void_p)                                           ## _zetInit_t
    ]

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
## @brief Function-pointer for zetModuleGetKernelNames
if __use_win_types:
    _zetModuleGetKernelNames_t = WINFUNCTYPE( ze_result_t, zet_module_handle_t, POINTER(c_ulong), POINTER(c_char*) )
else:
    _zetModuleGetKernelNames_t = CFUNCTYPE( ze_result_t, zet_module_handle_t, POINTER(c_ulong), POINTER(c_char*) )


###############################################################################
## @brief Table of Module functions pointers
class _zet_module_dditable_t(Structure):
    _fields_ = [
        ("pfnGetDebugInfo", c_void_p),                                  ## _zetModuleGetDebugInfo_t
        ("pfnGetKernelNames", c_void_p)                                 ## _zetModuleGetKernelNames_t
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
    _zetTracerSetPrologues_t = WINFUNCTYPE( ze_result_t, zet_tracer_handle_t, POINTER(zet_core_callbacks_t), POINTER(zet_experimental_callbacks_t) )
else:
    _zetTracerSetPrologues_t = CFUNCTYPE( ze_result_t, zet_tracer_handle_t, POINTER(zet_core_callbacks_t), POINTER(zet_experimental_callbacks_t) )

###############################################################################
## @brief Function-pointer for zetTracerSetEpilogues
if __use_win_types:
    _zetTracerSetEpilogues_t = WINFUNCTYPE( ze_result_t, zet_tracer_handle_t, POINTER(zet_core_callbacks_t), POINTER(zet_experimental_callbacks_t) )
else:
    _zetTracerSetEpilogues_t = CFUNCTYPE( ze_result_t, zet_tracer_handle_t, POINTER(zet_core_callbacks_t), POINTER(zet_experimental_callbacks_t) )

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
## @brief Function-pointer for zetSysmanGet
if __use_win_types:
    _zetSysmanGet_t = WINFUNCTYPE( ze_result_t, zet_device_handle_t, zet_sysman_version_t, POINTER(zet_sysman_handle_t) )
else:
    _zetSysmanGet_t = CFUNCTYPE( ze_result_t, zet_device_handle_t, zet_sysman_version_t, POINTER(zet_sysman_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanDeviceGetProperties
if __use_win_types:
    _zetSysmanDeviceGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_sysman_properties_t) )
else:
    _zetSysmanDeviceGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_sysman_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanSchedulerGetSupportedModes
if __use_win_types:
    _zetSysmanSchedulerGetSupportedModes_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sched_mode_t) )
else:
    _zetSysmanSchedulerGetSupportedModes_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sched_mode_t) )

###############################################################################
## @brief Function-pointer for zetSysmanSchedulerGetCurrentMode
if __use_win_types:
    _zetSysmanSchedulerGetCurrentMode_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_sched_mode_t) )
else:
    _zetSysmanSchedulerGetCurrentMode_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_sched_mode_t) )

###############################################################################
## @brief Function-pointer for zetSysmanSchedulerGetTimeoutModeProperties
if __use_win_types:
    _zetSysmanSchedulerGetTimeoutModeProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, ze_bool_t, POINTER(zet_sched_timeout_properties_t) )
else:
    _zetSysmanSchedulerGetTimeoutModeProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, ze_bool_t, POINTER(zet_sched_timeout_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanSchedulerGetTimesliceModeProperties
if __use_win_types:
    _zetSysmanSchedulerGetTimesliceModeProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, ze_bool_t, POINTER(zet_sched_timeslice_properties_t) )
else:
    _zetSysmanSchedulerGetTimesliceModeProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, ze_bool_t, POINTER(zet_sched_timeslice_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanSchedulerSetTimeoutMode
if __use_win_types:
    _zetSysmanSchedulerSetTimeoutMode_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_sched_timeout_properties_t), POINTER(ze_bool_t) )
else:
    _zetSysmanSchedulerSetTimeoutMode_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_sched_timeout_properties_t), POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zetSysmanSchedulerSetTimesliceMode
if __use_win_types:
    _zetSysmanSchedulerSetTimesliceMode_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_sched_timeslice_properties_t), POINTER(ze_bool_t) )
else:
    _zetSysmanSchedulerSetTimesliceMode_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_sched_timeslice_properties_t), POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zetSysmanSchedulerSetExclusiveMode
if __use_win_types:
    _zetSysmanSchedulerSetExclusiveMode_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(ze_bool_t) )
else:
    _zetSysmanSchedulerSetExclusiveMode_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zetSysmanSchedulerSetComputeUnitDebugMode
if __use_win_types:
    _zetSysmanSchedulerSetComputeUnitDebugMode_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(ze_bool_t) )
else:
    _zetSysmanSchedulerSetComputeUnitDebugMode_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zetSysmanProcessesGetState
if __use_win_types:
    _zetSysmanProcessesGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_process_state_t) )
else:
    _zetSysmanProcessesGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_process_state_t) )

###############################################################################
## @brief Function-pointer for zetSysmanDeviceReset
if __use_win_types:
    _zetSysmanDeviceReset_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t )
else:
    _zetSysmanDeviceReset_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t )

###############################################################################
## @brief Function-pointer for zetSysmanDeviceGetRepairStatus
if __use_win_types:
    _zetSysmanDeviceGetRepairStatus_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_repair_status_t) )
else:
    _zetSysmanDeviceGetRepairStatus_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_repair_status_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPciGetProperties
if __use_win_types:
    _zetSysmanPciGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_pci_properties_t) )
else:
    _zetSysmanPciGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_pci_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPciGetState
if __use_win_types:
    _zetSysmanPciGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_pci_state_t) )
else:
    _zetSysmanPciGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_pci_state_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPciGetBarProperties
if __use_win_types:
    _zetSysmanPciGetBarProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, c_ulong, POINTER(zet_pci_bar_properties_t) )
else:
    _zetSysmanPciGetBarProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, c_ulong, POINTER(zet_pci_bar_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPciGetStats
if __use_win_types:
    _zetSysmanPciGetStats_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_pci_stats_t) )
else:
    _zetSysmanPciGetStats_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_pci_stats_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPowerGet
if __use_win_types:
    _zetSysmanPowerGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_pwr_handle_t) )
else:
    _zetSysmanPowerGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_pwr_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGet
if __use_win_types:
    _zetSysmanFrequencyGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_freq_handle_t) )
else:
    _zetSysmanFrequencyGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_freq_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanEngineGet
if __use_win_types:
    _zetSysmanEngineGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_engine_handle_t) )
else:
    _zetSysmanEngineGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_engine_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanStandbyGet
if __use_win_types:
    _zetSysmanStandbyGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_standby_handle_t) )
else:
    _zetSysmanStandbyGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_standby_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFirmwareGet
if __use_win_types:
    _zetSysmanFirmwareGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_firmware_handle_t) )
else:
    _zetSysmanFirmwareGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_firmware_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanMemoryGet
if __use_win_types:
    _zetSysmanMemoryGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_mem_handle_t) )
else:
    _zetSysmanMemoryGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_mem_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFabricPortGet
if __use_win_types:
    _zetSysmanFabricPortGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_fabric_port_handle_t) )
else:
    _zetSysmanFabricPortGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_fabric_port_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanTemperatureGet
if __use_win_types:
    _zetSysmanTemperatureGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_temp_handle_t) )
else:
    _zetSysmanTemperatureGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_temp_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPsuGet
if __use_win_types:
    _zetSysmanPsuGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_psu_handle_t) )
else:
    _zetSysmanPsuGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_psu_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFanGet
if __use_win_types:
    _zetSysmanFanGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_fan_handle_t) )
else:
    _zetSysmanFanGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_fan_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanLedGet
if __use_win_types:
    _zetSysmanLedGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_led_handle_t) )
else:
    _zetSysmanLedGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_led_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanRasGet
if __use_win_types:
    _zetSysmanRasGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_ras_handle_t) )
else:
    _zetSysmanRasGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_ras_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanEventGet
if __use_win_types:
    _zetSysmanEventGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_sysman_event_handle_t) )
else:
    _zetSysmanEventGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_sysman_event_handle_t) )

###############################################################################
## @brief Function-pointer for zetSysmanDiagnosticsGet
if __use_win_types:
    _zetSysmanDiagnosticsGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_diag_handle_t) )
else:
    _zetSysmanDiagnosticsGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_diag_handle_t) )


###############################################################################
## @brief Table of Sysman functions pointers
class _zet_sysman_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _zetSysmanGet_t
        ("pfnDeviceGetProperties", c_void_p),                           ## _zetSysmanDeviceGetProperties_t
        ("pfnSchedulerGetSupportedModes", c_void_p),                    ## _zetSysmanSchedulerGetSupportedModes_t
        ("pfnSchedulerGetCurrentMode", c_void_p),                       ## _zetSysmanSchedulerGetCurrentMode_t
        ("pfnSchedulerGetTimeoutModeProperties", c_void_p),             ## _zetSysmanSchedulerGetTimeoutModeProperties_t
        ("pfnSchedulerGetTimesliceModeProperties", c_void_p),           ## _zetSysmanSchedulerGetTimesliceModeProperties_t
        ("pfnSchedulerSetTimeoutMode", c_void_p),                       ## _zetSysmanSchedulerSetTimeoutMode_t
        ("pfnSchedulerSetTimesliceMode", c_void_p),                     ## _zetSysmanSchedulerSetTimesliceMode_t
        ("pfnSchedulerSetExclusiveMode", c_void_p),                     ## _zetSysmanSchedulerSetExclusiveMode_t
        ("pfnSchedulerSetComputeUnitDebugMode", c_void_p),              ## _zetSysmanSchedulerSetComputeUnitDebugMode_t
        ("pfnProcessesGetState", c_void_p),                             ## _zetSysmanProcessesGetState_t
        ("pfnDeviceReset", c_void_p),                                   ## _zetSysmanDeviceReset_t
        ("pfnDeviceGetRepairStatus", c_void_p),                         ## _zetSysmanDeviceGetRepairStatus_t
        ("pfnPciGetProperties", c_void_p),                              ## _zetSysmanPciGetProperties_t
        ("pfnPciGetState", c_void_p),                                   ## _zetSysmanPciGetState_t
        ("pfnPciGetBarProperties", c_void_p),                           ## _zetSysmanPciGetBarProperties_t
        ("pfnPciGetStats", c_void_p),                                   ## _zetSysmanPciGetStats_t
        ("pfnPowerGet", c_void_p),                                      ## _zetSysmanPowerGet_t
        ("pfnFrequencyGet", c_void_p),                                  ## _zetSysmanFrequencyGet_t
        ("pfnEngineGet", c_void_p),                                     ## _zetSysmanEngineGet_t
        ("pfnStandbyGet", c_void_p),                                    ## _zetSysmanStandbyGet_t
        ("pfnFirmwareGet", c_void_p),                                   ## _zetSysmanFirmwareGet_t
        ("pfnMemoryGet", c_void_p),                                     ## _zetSysmanMemoryGet_t
        ("pfnFabricPortGet", c_void_p),                                 ## _zetSysmanFabricPortGet_t
        ("pfnTemperatureGet", c_void_p),                                ## _zetSysmanTemperatureGet_t
        ("pfnPsuGet", c_void_p),                                        ## _zetSysmanPsuGet_t
        ("pfnFanGet", c_void_p),                                        ## _zetSysmanFanGet_t
        ("pfnLedGet", c_void_p),                                        ## _zetSysmanLedGet_t
        ("pfnRasGet", c_void_p),                                        ## _zetSysmanRasGet_t
        ("pfnEventGet", c_void_p),                                      ## _zetSysmanEventGet_t
        ("pfnDiagnosticsGet", c_void_p)                                 ## _zetSysmanDiagnosticsGet_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanPowerGetProperties
if __use_win_types:
    _zetSysmanPowerGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_properties_t) )
else:
    _zetSysmanPowerGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPowerGetEnergyCounter
if __use_win_types:
    _zetSysmanPowerGetEnergyCounter_t = WINFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_energy_counter_t) )
else:
    _zetSysmanPowerGetEnergyCounter_t = CFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_energy_counter_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPowerGetLimits
if __use_win_types:
    _zetSysmanPowerGetLimits_t = WINFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_sustained_limit_t), POINTER(zet_power_burst_limit_t), POINTER(zet_power_peak_limit_t) )
else:
    _zetSysmanPowerGetLimits_t = CFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_sustained_limit_t), POINTER(zet_power_burst_limit_t), POINTER(zet_power_peak_limit_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPowerSetLimits
if __use_win_types:
    _zetSysmanPowerSetLimits_t = WINFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_sustained_limit_t), POINTER(zet_power_burst_limit_t), POINTER(zet_power_peak_limit_t) )
else:
    _zetSysmanPowerSetLimits_t = CFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_sustained_limit_t), POINTER(zet_power_burst_limit_t), POINTER(zet_power_peak_limit_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPowerGetEnergyThreshold
if __use_win_types:
    _zetSysmanPowerGetEnergyThreshold_t = WINFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_energy_threshold_t) )
else:
    _zetSysmanPowerGetEnergyThreshold_t = CFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_energy_threshold_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPowerSetEnergyThreshold
if __use_win_types:
    _zetSysmanPowerSetEnergyThreshold_t = WINFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, c_double )
else:
    _zetSysmanPowerSetEnergyThreshold_t = CFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, c_double )


###############################################################################
## @brief Table of SysmanPower functions pointers
class _zet_sysman_power_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanPowerGetProperties_t
        ("pfnGetEnergyCounter", c_void_p),                              ## _zetSysmanPowerGetEnergyCounter_t
        ("pfnGetLimits", c_void_p),                                     ## _zetSysmanPowerGetLimits_t
        ("pfnSetLimits", c_void_p),                                     ## _zetSysmanPowerSetLimits_t
        ("pfnGetEnergyThreshold", c_void_p),                            ## _zetSysmanPowerGetEnergyThreshold_t
        ("pfnSetEnergyThreshold", c_void_p)                             ## _zetSysmanPowerSetEnergyThreshold_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetProperties
if __use_win_types:
    _zetSysmanFrequencyGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_properties_t) )
else:
    _zetSysmanFrequencyGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetAvailableClocks
if __use_win_types:
    _zetSysmanFrequencyGetAvailableClocks_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(c_ulong), POINTER(c_double) )
else:
    _zetSysmanFrequencyGetAvailableClocks_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(c_ulong), POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetRange
if __use_win_types:
    _zetSysmanFrequencyGetRange_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_range_t) )
else:
    _zetSysmanFrequencyGetRange_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_range_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencySetRange
if __use_win_types:
    _zetSysmanFrequencySetRange_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_range_t) )
else:
    _zetSysmanFrequencySetRange_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_range_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetState
if __use_win_types:
    _zetSysmanFrequencyGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_state_t) )
else:
    _zetSysmanFrequencyGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_state_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetThrottleTime
if __use_win_types:
    _zetSysmanFrequencyGetThrottleTime_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_throttle_time_t) )
else:
    _zetSysmanFrequencyGetThrottleTime_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_throttle_time_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyOcGetCapabilities
if __use_win_types:
    _zetSysmanFrequencyOcGetCapabilities_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_capabilities_t) )
else:
    _zetSysmanFrequencyOcGetCapabilities_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_capabilities_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyOcGetConfig
if __use_win_types:
    _zetSysmanFrequencyOcGetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_config_t) )
else:
    _zetSysmanFrequencyOcGetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyOcSetConfig
if __use_win_types:
    _zetSysmanFrequencyOcSetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_config_t), POINTER(ze_bool_t) )
else:
    _zetSysmanFrequencyOcSetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_config_t), POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyOcGetIccMax
if __use_win_types:
    _zetSysmanFrequencyOcGetIccMax_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(c_double) )
else:
    _zetSysmanFrequencyOcGetIccMax_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyOcSetIccMax
if __use_win_types:
    _zetSysmanFrequencyOcSetIccMax_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, c_double )
else:
    _zetSysmanFrequencyOcSetIccMax_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, c_double )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyOcGetTjMax
if __use_win_types:
    _zetSysmanFrequencyOcGetTjMax_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(c_double) )
else:
    _zetSysmanFrequencyOcGetTjMax_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyOcSetTjMax
if __use_win_types:
    _zetSysmanFrequencyOcSetTjMax_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, c_double )
else:
    _zetSysmanFrequencyOcSetTjMax_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, c_double )


###############################################################################
## @brief Table of SysmanFrequency functions pointers
class _zet_sysman_frequency_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanFrequencyGetProperties_t
        ("pfnGetAvailableClocks", c_void_p),                            ## _zetSysmanFrequencyGetAvailableClocks_t
        ("pfnGetRange", c_void_p),                                      ## _zetSysmanFrequencyGetRange_t
        ("pfnSetRange", c_void_p),                                      ## _zetSysmanFrequencySetRange_t
        ("pfnGetState", c_void_p),                                      ## _zetSysmanFrequencyGetState_t
        ("pfnGetThrottleTime", c_void_p),                               ## _zetSysmanFrequencyGetThrottleTime_t
        ("pfnOcGetCapabilities", c_void_p),                             ## _zetSysmanFrequencyOcGetCapabilities_t
        ("pfnOcGetConfig", c_void_p),                                   ## _zetSysmanFrequencyOcGetConfig_t
        ("pfnOcSetConfig", c_void_p),                                   ## _zetSysmanFrequencyOcSetConfig_t
        ("pfnOcGetIccMax", c_void_p),                                   ## _zetSysmanFrequencyOcGetIccMax_t
        ("pfnOcSetIccMax", c_void_p),                                   ## _zetSysmanFrequencyOcSetIccMax_t
        ("pfnOcGetTjMax", c_void_p),                                    ## _zetSysmanFrequencyOcGetTjMax_t
        ("pfnOcSetTjMax", c_void_p)                                     ## _zetSysmanFrequencyOcSetTjMax_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanEngineGetProperties
if __use_win_types:
    _zetSysmanEngineGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_engine_handle_t, POINTER(zet_engine_properties_t) )
else:
    _zetSysmanEngineGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_engine_handle_t, POINTER(zet_engine_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanEngineGetActivity
if __use_win_types:
    _zetSysmanEngineGetActivity_t = WINFUNCTYPE( ze_result_t, zet_sysman_engine_handle_t, POINTER(zet_engine_stats_t) )
else:
    _zetSysmanEngineGetActivity_t = CFUNCTYPE( ze_result_t, zet_sysman_engine_handle_t, POINTER(zet_engine_stats_t) )


###############################################################################
## @brief Table of SysmanEngine functions pointers
class _zet_sysman_engine_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanEngineGetProperties_t
        ("pfnGetActivity", c_void_p)                                    ## _zetSysmanEngineGetActivity_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanStandbyGetProperties
if __use_win_types:
    _zetSysmanStandbyGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_standby_handle_t, POINTER(zet_standby_properties_t) )
else:
    _zetSysmanStandbyGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_standby_handle_t, POINTER(zet_standby_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanStandbyGetMode
if __use_win_types:
    _zetSysmanStandbyGetMode_t = WINFUNCTYPE( ze_result_t, zet_sysman_standby_handle_t, POINTER(zet_standby_promo_mode_t) )
else:
    _zetSysmanStandbyGetMode_t = CFUNCTYPE( ze_result_t, zet_sysman_standby_handle_t, POINTER(zet_standby_promo_mode_t) )

###############################################################################
## @brief Function-pointer for zetSysmanStandbySetMode
if __use_win_types:
    _zetSysmanStandbySetMode_t = WINFUNCTYPE( ze_result_t, zet_sysman_standby_handle_t, zet_standby_promo_mode_t )
else:
    _zetSysmanStandbySetMode_t = CFUNCTYPE( ze_result_t, zet_sysman_standby_handle_t, zet_standby_promo_mode_t )


###############################################################################
## @brief Table of SysmanStandby functions pointers
class _zet_sysman_standby_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanStandbyGetProperties_t
        ("pfnGetMode", c_void_p),                                       ## _zetSysmanStandbyGetMode_t
        ("pfnSetMode", c_void_p)                                        ## _zetSysmanStandbySetMode_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanFirmwareGetProperties
if __use_win_types:
    _zetSysmanFirmwareGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_firmware_handle_t, POINTER(zet_firmware_properties_t) )
else:
    _zetSysmanFirmwareGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_firmware_handle_t, POINTER(zet_firmware_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFirmwareGetChecksum
if __use_win_types:
    _zetSysmanFirmwareGetChecksum_t = WINFUNCTYPE( ze_result_t, zet_sysman_firmware_handle_t, POINTER(c_ulong) )
else:
    _zetSysmanFirmwareGetChecksum_t = CFUNCTYPE( ze_result_t, zet_sysman_firmware_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for zetSysmanFirmwareFlash
if __use_win_types:
    _zetSysmanFirmwareFlash_t = WINFUNCTYPE( ze_result_t, zet_sysman_firmware_handle_t, c_void_p, c_ulong )
else:
    _zetSysmanFirmwareFlash_t = CFUNCTYPE( ze_result_t, zet_sysman_firmware_handle_t, c_void_p, c_ulong )


###############################################################################
## @brief Table of SysmanFirmware functions pointers
class _zet_sysman_firmware_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanFirmwareGetProperties_t
        ("pfnGetChecksum", c_void_p),                                   ## _zetSysmanFirmwareGetChecksum_t
        ("pfnFlash", c_void_p)                                          ## _zetSysmanFirmwareFlash_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanMemoryGetProperties
if __use_win_types:
    _zetSysmanMemoryGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_mem_handle_t, POINTER(zet_mem_properties_t) )
else:
    _zetSysmanMemoryGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_mem_handle_t, POINTER(zet_mem_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanMemoryGetState
if __use_win_types:
    _zetSysmanMemoryGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_mem_handle_t, POINTER(zet_mem_state_t) )
else:
    _zetSysmanMemoryGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_mem_handle_t, POINTER(zet_mem_state_t) )

###############################################################################
## @brief Function-pointer for zetSysmanMemoryGetBandwidth
if __use_win_types:
    _zetSysmanMemoryGetBandwidth_t = WINFUNCTYPE( ze_result_t, zet_sysman_mem_handle_t, POINTER(zet_mem_bandwidth_t) )
else:
    _zetSysmanMemoryGetBandwidth_t = CFUNCTYPE( ze_result_t, zet_sysman_mem_handle_t, POINTER(zet_mem_bandwidth_t) )


###############################################################################
## @brief Table of SysmanMemory functions pointers
class _zet_sysman_memory_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanMemoryGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _zetSysmanMemoryGetState_t
        ("pfnGetBandwidth", c_void_p)                                   ## _zetSysmanMemoryGetBandwidth_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanFabricPortGetProperties
if __use_win_types:
    _zetSysmanFabricPortGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, POINTER(zet_fabric_port_properties_t) )
else:
    _zetSysmanFabricPortGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, POINTER(zet_fabric_port_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFabricPortGetLinkType
if __use_win_types:
    _zetSysmanFabricPortGetLinkType_t = WINFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, ze_bool_t, POINTER(zet_fabric_link_type_t) )
else:
    _zetSysmanFabricPortGetLinkType_t = CFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, ze_bool_t, POINTER(zet_fabric_link_type_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFabricPortGetConfig
if __use_win_types:
    _zetSysmanFabricPortGetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, POINTER(zet_fabric_port_config_t) )
else:
    _zetSysmanFabricPortGetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, POINTER(zet_fabric_port_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFabricPortSetConfig
if __use_win_types:
    _zetSysmanFabricPortSetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, POINTER(zet_fabric_port_config_t) )
else:
    _zetSysmanFabricPortSetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, POINTER(zet_fabric_port_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFabricPortGetState
if __use_win_types:
    _zetSysmanFabricPortGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, POINTER(zet_fabric_port_state_t) )
else:
    _zetSysmanFabricPortGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, POINTER(zet_fabric_port_state_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFabricPortGetThroughput
if __use_win_types:
    _zetSysmanFabricPortGetThroughput_t = WINFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, POINTER(zet_fabric_port_throughput_t) )
else:
    _zetSysmanFabricPortGetThroughput_t = CFUNCTYPE( ze_result_t, zet_sysman_fabric_port_handle_t, POINTER(zet_fabric_port_throughput_t) )


###############################################################################
## @brief Table of SysmanFabricPort functions pointers
class _zet_sysman_fabric_port_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanFabricPortGetProperties_t
        ("pfnGetLinkType", c_void_p),                                   ## _zetSysmanFabricPortGetLinkType_t
        ("pfnGetConfig", c_void_p),                                     ## _zetSysmanFabricPortGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zetSysmanFabricPortSetConfig_t
        ("pfnGetState", c_void_p),                                      ## _zetSysmanFabricPortGetState_t
        ("pfnGetThroughput", c_void_p)                                  ## _zetSysmanFabricPortGetThroughput_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanTemperatureGetProperties
if __use_win_types:
    _zetSysmanTemperatureGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(zet_temp_properties_t) )
else:
    _zetSysmanTemperatureGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(zet_temp_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanTemperatureGetConfig
if __use_win_types:
    _zetSysmanTemperatureGetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(zet_temp_config_t) )
else:
    _zetSysmanTemperatureGetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(zet_temp_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanTemperatureSetConfig
if __use_win_types:
    _zetSysmanTemperatureSetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(zet_temp_config_t) )
else:
    _zetSysmanTemperatureSetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(zet_temp_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanTemperatureGetState
if __use_win_types:
    _zetSysmanTemperatureGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(c_double) )
else:
    _zetSysmanTemperatureGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(c_double) )


###############################################################################
## @brief Table of SysmanTemperature functions pointers
class _zet_sysman_temperature_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanTemperatureGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zetSysmanTemperatureGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zetSysmanTemperatureSetConfig_t
        ("pfnGetState", c_void_p)                                       ## _zetSysmanTemperatureGetState_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanPsuGetProperties
if __use_win_types:
    _zetSysmanPsuGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_psu_handle_t, POINTER(zet_psu_properties_t) )
else:
    _zetSysmanPsuGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_psu_handle_t, POINTER(zet_psu_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPsuGetState
if __use_win_types:
    _zetSysmanPsuGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_psu_handle_t, POINTER(zet_psu_state_t) )
else:
    _zetSysmanPsuGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_psu_handle_t, POINTER(zet_psu_state_t) )


###############################################################################
## @brief Table of SysmanPsu functions pointers
class _zet_sysman_psu_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanPsuGetProperties_t
        ("pfnGetState", c_void_p)                                       ## _zetSysmanPsuGetState_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanFanGetProperties
if __use_win_types:
    _zetSysmanFanGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_fan_handle_t, POINTER(zet_fan_properties_t) )
else:
    _zetSysmanFanGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_fan_handle_t, POINTER(zet_fan_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFanGetConfig
if __use_win_types:
    _zetSysmanFanGetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_fan_handle_t, POINTER(zet_fan_config_t) )
else:
    _zetSysmanFanGetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_fan_handle_t, POINTER(zet_fan_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFanSetConfig
if __use_win_types:
    _zetSysmanFanSetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_fan_handle_t, POINTER(zet_fan_config_t) )
else:
    _zetSysmanFanSetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_fan_handle_t, POINTER(zet_fan_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFanGetState
if __use_win_types:
    _zetSysmanFanGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_fan_handle_t, zet_fan_speed_units_t, POINTER(c_ulong) )
else:
    _zetSysmanFanGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_fan_handle_t, zet_fan_speed_units_t, POINTER(c_ulong) )


###############################################################################
## @brief Table of SysmanFan functions pointers
class _zet_sysman_fan_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanFanGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zetSysmanFanGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zetSysmanFanSetConfig_t
        ("pfnGetState", c_void_p)                                       ## _zetSysmanFanGetState_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanLedGetProperties
if __use_win_types:
    _zetSysmanLedGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_led_handle_t, POINTER(zet_led_properties_t) )
else:
    _zetSysmanLedGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_led_handle_t, POINTER(zet_led_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanLedGetState
if __use_win_types:
    _zetSysmanLedGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_led_handle_t, POINTER(zet_led_state_t) )
else:
    _zetSysmanLedGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_led_handle_t, POINTER(zet_led_state_t) )

###############################################################################
## @brief Function-pointer for zetSysmanLedSetState
if __use_win_types:
    _zetSysmanLedSetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_led_handle_t, POINTER(zet_led_state_t) )
else:
    _zetSysmanLedSetState_t = CFUNCTYPE( ze_result_t, zet_sysman_led_handle_t, POINTER(zet_led_state_t) )


###############################################################################
## @brief Table of SysmanLed functions pointers
class _zet_sysman_led_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanLedGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _zetSysmanLedGetState_t
        ("pfnSetState", c_void_p)                                       ## _zetSysmanLedSetState_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanRasGetProperties
if __use_win_types:
    _zetSysmanRasGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_ras_handle_t, POINTER(zet_ras_properties_t) )
else:
    _zetSysmanRasGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_ras_handle_t, POINTER(zet_ras_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanRasGetConfig
if __use_win_types:
    _zetSysmanRasGetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_ras_handle_t, POINTER(zet_ras_config_t) )
else:
    _zetSysmanRasGetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_ras_handle_t, POINTER(zet_ras_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanRasSetConfig
if __use_win_types:
    _zetSysmanRasSetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_ras_handle_t, POINTER(zet_ras_config_t) )
else:
    _zetSysmanRasSetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_ras_handle_t, POINTER(zet_ras_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanRasGetState
if __use_win_types:
    _zetSysmanRasGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_ras_handle_t, ze_bool_t, POINTER(c_ulonglong), POINTER(zet_ras_details_t) )
else:
    _zetSysmanRasGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_ras_handle_t, ze_bool_t, POINTER(c_ulonglong), POINTER(zet_ras_details_t) )


###############################################################################
## @brief Table of SysmanRas functions pointers
class _zet_sysman_ras_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanRasGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zetSysmanRasGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zetSysmanRasSetConfig_t
        ("pfnGetState", c_void_p)                                       ## _zetSysmanRasGetState_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanDiagnosticsGetProperties
if __use_win_types:
    _zetSysmanDiagnosticsGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_diag_handle_t, POINTER(zet_diag_properties_t) )
else:
    _zetSysmanDiagnosticsGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_diag_handle_t, POINTER(zet_diag_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanDiagnosticsGetTests
if __use_win_types:
    _zetSysmanDiagnosticsGetTests_t = WINFUNCTYPE( ze_result_t, zet_sysman_diag_handle_t, POINTER(c_ulong), POINTER(zet_diag_test_t) )
else:
    _zetSysmanDiagnosticsGetTests_t = CFUNCTYPE( ze_result_t, zet_sysman_diag_handle_t, POINTER(c_ulong), POINTER(zet_diag_test_t) )

###############################################################################
## @brief Function-pointer for zetSysmanDiagnosticsRunTests
if __use_win_types:
    _zetSysmanDiagnosticsRunTests_t = WINFUNCTYPE( ze_result_t, zet_sysman_diag_handle_t, c_ulong, c_ulong, POINTER(zet_diag_result_t) )
else:
    _zetSysmanDiagnosticsRunTests_t = CFUNCTYPE( ze_result_t, zet_sysman_diag_handle_t, c_ulong, c_ulong, POINTER(zet_diag_result_t) )


###############################################################################
## @brief Table of SysmanDiagnostics functions pointers
class _zet_sysman_diagnostics_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanDiagnosticsGetProperties_t
        ("pfnGetTests", c_void_p),                                      ## _zetSysmanDiagnosticsGetTests_t
        ("pfnRunTests", c_void_p)                                       ## _zetSysmanDiagnosticsRunTests_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanEventGetConfig
if __use_win_types:
    _zetSysmanEventGetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_event_handle_t, POINTER(zet_event_config_t) )
else:
    _zetSysmanEventGetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_event_handle_t, POINTER(zet_event_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanEventSetConfig
if __use_win_types:
    _zetSysmanEventSetConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_event_handle_t, POINTER(zet_event_config_t) )
else:
    _zetSysmanEventSetConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_event_handle_t, POINTER(zet_event_config_t) )

###############################################################################
## @brief Function-pointer for zetSysmanEventGetState
if __use_win_types:
    _zetSysmanEventGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_event_handle_t, ze_bool_t, POINTER(c_ulong) )
else:
    _zetSysmanEventGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_event_handle_t, ze_bool_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for zetSysmanEventListen
if __use_win_types:
    _zetSysmanEventListen_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, c_ulong, c_ulong, POINTER(zet_sysman_event_handle_t), POINTER(c_ulong) )
else:
    _zetSysmanEventListen_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, c_ulong, c_ulong, POINTER(zet_sysman_event_handle_t), POINTER(c_ulong) )


###############################################################################
## @brief Table of SysmanEvent functions pointers
class _zet_sysman_event_dditable_t(Structure):
    _fields_ = [
        ("pfnGetConfig", c_void_p),                                     ## _zetSysmanEventGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zetSysmanEventSetConfig_t
        ("pfnGetState", c_void_p),                                      ## _zetSysmanEventGetState_t
        ("pfnListen", c_void_p)                                         ## _zetSysmanEventListen_t
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
        ("Global", _zet_global_dditable_t),
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
        ("Sysman", _zet_sysman_dditable_t),
        ("SysmanPower", _zet_sysman_power_dditable_t),
        ("SysmanFrequency", _zet_sysman_frequency_dditable_t),
        ("SysmanEngine", _zet_sysman_engine_dditable_t),
        ("SysmanStandby", _zet_sysman_standby_dditable_t),
        ("SysmanFirmware", _zet_sysman_firmware_dditable_t),
        ("SysmanMemory", _zet_sysman_memory_dditable_t),
        ("SysmanFabricPort", _zet_sysman_fabric_port_dditable_t),
        ("SysmanTemperature", _zet_sysman_temperature_dditable_t),
        ("SysmanPsu", _zet_sysman_psu_dditable_t),
        ("SysmanFan", _zet_sysman_fan_dditable_t),
        ("SysmanLed", _zet_sysman_led_dditable_t),
        ("SysmanRas", _zet_sysman_ras_dditable_t),
        ("SysmanDiagnostics", _zet_sysman_diagnostics_dditable_t),
        ("SysmanEvent", _zet_sysman_event_dditable_t),
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
        _Global = _zet_global_dditable_t()
        r = ze_result_v(self.__dll.zetGetGlobalProcAddrTable(version, byref(_Global)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Global = _Global

        # attach function interface to function address
        self.zetInit = _zetInit_t(self.__dditable.Global.pfnInit)

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
        self.zetModuleGetKernelNames = _zetModuleGetKernelNames_t(self.__dditable.Module.pfnGetKernelNames)

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
        _Sysman = _zet_sysman_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanProcAddrTable(version, byref(_Sysman)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Sysman = _Sysman

        # attach function interface to function address
        self.zetSysmanGet = _zetSysmanGet_t(self.__dditable.Sysman.pfnGet)
        self.zetSysmanDeviceGetProperties = _zetSysmanDeviceGetProperties_t(self.__dditable.Sysman.pfnDeviceGetProperties)
        self.zetSysmanSchedulerGetSupportedModes = _zetSysmanSchedulerGetSupportedModes_t(self.__dditable.Sysman.pfnSchedulerGetSupportedModes)
        self.zetSysmanSchedulerGetCurrentMode = _zetSysmanSchedulerGetCurrentMode_t(self.__dditable.Sysman.pfnSchedulerGetCurrentMode)
        self.zetSysmanSchedulerGetTimeoutModeProperties = _zetSysmanSchedulerGetTimeoutModeProperties_t(self.__dditable.Sysman.pfnSchedulerGetTimeoutModeProperties)
        self.zetSysmanSchedulerGetTimesliceModeProperties = _zetSysmanSchedulerGetTimesliceModeProperties_t(self.__dditable.Sysman.pfnSchedulerGetTimesliceModeProperties)
        self.zetSysmanSchedulerSetTimeoutMode = _zetSysmanSchedulerSetTimeoutMode_t(self.__dditable.Sysman.pfnSchedulerSetTimeoutMode)
        self.zetSysmanSchedulerSetTimesliceMode = _zetSysmanSchedulerSetTimesliceMode_t(self.__dditable.Sysman.pfnSchedulerSetTimesliceMode)
        self.zetSysmanSchedulerSetExclusiveMode = _zetSysmanSchedulerSetExclusiveMode_t(self.__dditable.Sysman.pfnSchedulerSetExclusiveMode)
        self.zetSysmanSchedulerSetComputeUnitDebugMode = _zetSysmanSchedulerSetComputeUnitDebugMode_t(self.__dditable.Sysman.pfnSchedulerSetComputeUnitDebugMode)
        self.zetSysmanProcessesGetState = _zetSysmanProcessesGetState_t(self.__dditable.Sysman.pfnProcessesGetState)
        self.zetSysmanDeviceReset = _zetSysmanDeviceReset_t(self.__dditable.Sysman.pfnDeviceReset)
        self.zetSysmanDeviceGetRepairStatus = _zetSysmanDeviceGetRepairStatus_t(self.__dditable.Sysman.pfnDeviceGetRepairStatus)
        self.zetSysmanPciGetProperties = _zetSysmanPciGetProperties_t(self.__dditable.Sysman.pfnPciGetProperties)
        self.zetSysmanPciGetState = _zetSysmanPciGetState_t(self.__dditable.Sysman.pfnPciGetState)
        self.zetSysmanPciGetBarProperties = _zetSysmanPciGetBarProperties_t(self.__dditable.Sysman.pfnPciGetBarProperties)
        self.zetSysmanPciGetStats = _zetSysmanPciGetStats_t(self.__dditable.Sysman.pfnPciGetStats)
        self.zetSysmanPowerGet = _zetSysmanPowerGet_t(self.__dditable.Sysman.pfnPowerGet)
        self.zetSysmanFrequencyGet = _zetSysmanFrequencyGet_t(self.__dditable.Sysman.pfnFrequencyGet)
        self.zetSysmanEngineGet = _zetSysmanEngineGet_t(self.__dditable.Sysman.pfnEngineGet)
        self.zetSysmanStandbyGet = _zetSysmanStandbyGet_t(self.__dditable.Sysman.pfnStandbyGet)
        self.zetSysmanFirmwareGet = _zetSysmanFirmwareGet_t(self.__dditable.Sysman.pfnFirmwareGet)
        self.zetSysmanMemoryGet = _zetSysmanMemoryGet_t(self.__dditable.Sysman.pfnMemoryGet)
        self.zetSysmanFabricPortGet = _zetSysmanFabricPortGet_t(self.__dditable.Sysman.pfnFabricPortGet)
        self.zetSysmanTemperatureGet = _zetSysmanTemperatureGet_t(self.__dditable.Sysman.pfnTemperatureGet)
        self.zetSysmanPsuGet = _zetSysmanPsuGet_t(self.__dditable.Sysman.pfnPsuGet)
        self.zetSysmanFanGet = _zetSysmanFanGet_t(self.__dditable.Sysman.pfnFanGet)
        self.zetSysmanLedGet = _zetSysmanLedGet_t(self.__dditable.Sysman.pfnLedGet)
        self.zetSysmanRasGet = _zetSysmanRasGet_t(self.__dditable.Sysman.pfnRasGet)
        self.zetSysmanEventGet = _zetSysmanEventGet_t(self.__dditable.Sysman.pfnEventGet)
        self.zetSysmanDiagnosticsGet = _zetSysmanDiagnosticsGet_t(self.__dditable.Sysman.pfnDiagnosticsGet)

        # call driver to get function pointers
        _SysmanPower = _zet_sysman_power_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanPowerProcAddrTable(version, byref(_SysmanPower)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanPower = _SysmanPower

        # attach function interface to function address
        self.zetSysmanPowerGetProperties = _zetSysmanPowerGetProperties_t(self.__dditable.SysmanPower.pfnGetProperties)
        self.zetSysmanPowerGetEnergyCounter = _zetSysmanPowerGetEnergyCounter_t(self.__dditable.SysmanPower.pfnGetEnergyCounter)
        self.zetSysmanPowerGetLimits = _zetSysmanPowerGetLimits_t(self.__dditable.SysmanPower.pfnGetLimits)
        self.zetSysmanPowerSetLimits = _zetSysmanPowerSetLimits_t(self.__dditable.SysmanPower.pfnSetLimits)
        self.zetSysmanPowerGetEnergyThreshold = _zetSysmanPowerGetEnergyThreshold_t(self.__dditable.SysmanPower.pfnGetEnergyThreshold)
        self.zetSysmanPowerSetEnergyThreshold = _zetSysmanPowerSetEnergyThreshold_t(self.__dditable.SysmanPower.pfnSetEnergyThreshold)

        # call driver to get function pointers
        _SysmanFrequency = _zet_sysman_frequency_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanFrequencyProcAddrTable(version, byref(_SysmanFrequency)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFrequency = _SysmanFrequency

        # attach function interface to function address
        self.zetSysmanFrequencyGetProperties = _zetSysmanFrequencyGetProperties_t(self.__dditable.SysmanFrequency.pfnGetProperties)
        self.zetSysmanFrequencyGetAvailableClocks = _zetSysmanFrequencyGetAvailableClocks_t(self.__dditable.SysmanFrequency.pfnGetAvailableClocks)
        self.zetSysmanFrequencyGetRange = _zetSysmanFrequencyGetRange_t(self.__dditable.SysmanFrequency.pfnGetRange)
        self.zetSysmanFrequencySetRange = _zetSysmanFrequencySetRange_t(self.__dditable.SysmanFrequency.pfnSetRange)
        self.zetSysmanFrequencyGetState = _zetSysmanFrequencyGetState_t(self.__dditable.SysmanFrequency.pfnGetState)
        self.zetSysmanFrequencyGetThrottleTime = _zetSysmanFrequencyGetThrottleTime_t(self.__dditable.SysmanFrequency.pfnGetThrottleTime)
        self.zetSysmanFrequencyOcGetCapabilities = _zetSysmanFrequencyOcGetCapabilities_t(self.__dditable.SysmanFrequency.pfnOcGetCapabilities)
        self.zetSysmanFrequencyOcGetConfig = _zetSysmanFrequencyOcGetConfig_t(self.__dditable.SysmanFrequency.pfnOcGetConfig)
        self.zetSysmanFrequencyOcSetConfig = _zetSysmanFrequencyOcSetConfig_t(self.__dditable.SysmanFrequency.pfnOcSetConfig)
        self.zetSysmanFrequencyOcGetIccMax = _zetSysmanFrequencyOcGetIccMax_t(self.__dditable.SysmanFrequency.pfnOcGetIccMax)
        self.zetSysmanFrequencyOcSetIccMax = _zetSysmanFrequencyOcSetIccMax_t(self.__dditable.SysmanFrequency.pfnOcSetIccMax)
        self.zetSysmanFrequencyOcGetTjMax = _zetSysmanFrequencyOcGetTjMax_t(self.__dditable.SysmanFrequency.pfnOcGetTjMax)
        self.zetSysmanFrequencyOcSetTjMax = _zetSysmanFrequencyOcSetTjMax_t(self.__dditable.SysmanFrequency.pfnOcSetTjMax)

        # call driver to get function pointers
        _SysmanEngine = _zet_sysman_engine_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanEngineProcAddrTable(version, byref(_SysmanEngine)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanEngine = _SysmanEngine

        # attach function interface to function address
        self.zetSysmanEngineGetProperties = _zetSysmanEngineGetProperties_t(self.__dditable.SysmanEngine.pfnGetProperties)
        self.zetSysmanEngineGetActivity = _zetSysmanEngineGetActivity_t(self.__dditable.SysmanEngine.pfnGetActivity)

        # call driver to get function pointers
        _SysmanStandby = _zet_sysman_standby_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanStandbyProcAddrTable(version, byref(_SysmanStandby)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanStandby = _SysmanStandby

        # attach function interface to function address
        self.zetSysmanStandbyGetProperties = _zetSysmanStandbyGetProperties_t(self.__dditable.SysmanStandby.pfnGetProperties)
        self.zetSysmanStandbyGetMode = _zetSysmanStandbyGetMode_t(self.__dditable.SysmanStandby.pfnGetMode)
        self.zetSysmanStandbySetMode = _zetSysmanStandbySetMode_t(self.__dditable.SysmanStandby.pfnSetMode)

        # call driver to get function pointers
        _SysmanFirmware = _zet_sysman_firmware_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanFirmwareProcAddrTable(version, byref(_SysmanFirmware)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFirmware = _SysmanFirmware

        # attach function interface to function address
        self.zetSysmanFirmwareGetProperties = _zetSysmanFirmwareGetProperties_t(self.__dditable.SysmanFirmware.pfnGetProperties)
        self.zetSysmanFirmwareGetChecksum = _zetSysmanFirmwareGetChecksum_t(self.__dditable.SysmanFirmware.pfnGetChecksum)
        self.zetSysmanFirmwareFlash = _zetSysmanFirmwareFlash_t(self.__dditable.SysmanFirmware.pfnFlash)

        # call driver to get function pointers
        _SysmanMemory = _zet_sysman_memory_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanMemoryProcAddrTable(version, byref(_SysmanMemory)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanMemory = _SysmanMemory

        # attach function interface to function address
        self.zetSysmanMemoryGetProperties = _zetSysmanMemoryGetProperties_t(self.__dditable.SysmanMemory.pfnGetProperties)
        self.zetSysmanMemoryGetState = _zetSysmanMemoryGetState_t(self.__dditable.SysmanMemory.pfnGetState)
        self.zetSysmanMemoryGetBandwidth = _zetSysmanMemoryGetBandwidth_t(self.__dditable.SysmanMemory.pfnGetBandwidth)

        # call driver to get function pointers
        _SysmanFabricPort = _zet_sysman_fabric_port_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanFabricPortProcAddrTable(version, byref(_SysmanFabricPort)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFabricPort = _SysmanFabricPort

        # attach function interface to function address
        self.zetSysmanFabricPortGetProperties = _zetSysmanFabricPortGetProperties_t(self.__dditable.SysmanFabricPort.pfnGetProperties)
        self.zetSysmanFabricPortGetLinkType = _zetSysmanFabricPortGetLinkType_t(self.__dditable.SysmanFabricPort.pfnGetLinkType)
        self.zetSysmanFabricPortGetConfig = _zetSysmanFabricPortGetConfig_t(self.__dditable.SysmanFabricPort.pfnGetConfig)
        self.zetSysmanFabricPortSetConfig = _zetSysmanFabricPortSetConfig_t(self.__dditable.SysmanFabricPort.pfnSetConfig)
        self.zetSysmanFabricPortGetState = _zetSysmanFabricPortGetState_t(self.__dditable.SysmanFabricPort.pfnGetState)
        self.zetSysmanFabricPortGetThroughput = _zetSysmanFabricPortGetThroughput_t(self.__dditable.SysmanFabricPort.pfnGetThroughput)

        # call driver to get function pointers
        _SysmanTemperature = _zet_sysman_temperature_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanTemperatureProcAddrTable(version, byref(_SysmanTemperature)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanTemperature = _SysmanTemperature

        # attach function interface to function address
        self.zetSysmanTemperatureGetProperties = _zetSysmanTemperatureGetProperties_t(self.__dditable.SysmanTemperature.pfnGetProperties)
        self.zetSysmanTemperatureGetConfig = _zetSysmanTemperatureGetConfig_t(self.__dditable.SysmanTemperature.pfnGetConfig)
        self.zetSysmanTemperatureSetConfig = _zetSysmanTemperatureSetConfig_t(self.__dditable.SysmanTemperature.pfnSetConfig)
        self.zetSysmanTemperatureGetState = _zetSysmanTemperatureGetState_t(self.__dditable.SysmanTemperature.pfnGetState)

        # call driver to get function pointers
        _SysmanPsu = _zet_sysman_psu_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanPsuProcAddrTable(version, byref(_SysmanPsu)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanPsu = _SysmanPsu

        # attach function interface to function address
        self.zetSysmanPsuGetProperties = _zetSysmanPsuGetProperties_t(self.__dditable.SysmanPsu.pfnGetProperties)
        self.zetSysmanPsuGetState = _zetSysmanPsuGetState_t(self.__dditable.SysmanPsu.pfnGetState)

        # call driver to get function pointers
        _SysmanFan = _zet_sysman_fan_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanFanProcAddrTable(version, byref(_SysmanFan)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFan = _SysmanFan

        # attach function interface to function address
        self.zetSysmanFanGetProperties = _zetSysmanFanGetProperties_t(self.__dditable.SysmanFan.pfnGetProperties)
        self.zetSysmanFanGetConfig = _zetSysmanFanGetConfig_t(self.__dditable.SysmanFan.pfnGetConfig)
        self.zetSysmanFanSetConfig = _zetSysmanFanSetConfig_t(self.__dditable.SysmanFan.pfnSetConfig)
        self.zetSysmanFanGetState = _zetSysmanFanGetState_t(self.__dditable.SysmanFan.pfnGetState)

        # call driver to get function pointers
        _SysmanLed = _zet_sysman_led_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanLedProcAddrTable(version, byref(_SysmanLed)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanLed = _SysmanLed

        # attach function interface to function address
        self.zetSysmanLedGetProperties = _zetSysmanLedGetProperties_t(self.__dditable.SysmanLed.pfnGetProperties)
        self.zetSysmanLedGetState = _zetSysmanLedGetState_t(self.__dditable.SysmanLed.pfnGetState)
        self.zetSysmanLedSetState = _zetSysmanLedSetState_t(self.__dditable.SysmanLed.pfnSetState)

        # call driver to get function pointers
        _SysmanRas = _zet_sysman_ras_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanRasProcAddrTable(version, byref(_SysmanRas)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanRas = _SysmanRas

        # attach function interface to function address
        self.zetSysmanRasGetProperties = _zetSysmanRasGetProperties_t(self.__dditable.SysmanRas.pfnGetProperties)
        self.zetSysmanRasGetConfig = _zetSysmanRasGetConfig_t(self.__dditable.SysmanRas.pfnGetConfig)
        self.zetSysmanRasSetConfig = _zetSysmanRasSetConfig_t(self.__dditable.SysmanRas.pfnSetConfig)
        self.zetSysmanRasGetState = _zetSysmanRasGetState_t(self.__dditable.SysmanRas.pfnGetState)

        # call driver to get function pointers
        _SysmanDiagnostics = _zet_sysman_diagnostics_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanDiagnosticsProcAddrTable(version, byref(_SysmanDiagnostics)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanDiagnostics = _SysmanDiagnostics

        # attach function interface to function address
        self.zetSysmanDiagnosticsGetProperties = _zetSysmanDiagnosticsGetProperties_t(self.__dditable.SysmanDiagnostics.pfnGetProperties)
        self.zetSysmanDiagnosticsGetTests = _zetSysmanDiagnosticsGetTests_t(self.__dditable.SysmanDiagnostics.pfnGetTests)
        self.zetSysmanDiagnosticsRunTests = _zetSysmanDiagnosticsRunTests_t(self.__dditable.SysmanDiagnostics.pfnRunTests)

        # call driver to get function pointers
        _SysmanEvent = _zet_sysman_event_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanEventProcAddrTable(version, byref(_SysmanEvent)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanEvent = _SysmanEvent

        # attach function interface to function address
        self.zetSysmanEventGetConfig = _zetSysmanEventGetConfig_t(self.__dditable.SysmanEvent.pfnGetConfig)
        self.zetSysmanEventSetConfig = _zetSysmanEventSetConfig_t(self.__dditable.SysmanEvent.pfnSetConfig)
        self.zetSysmanEventGetState = _zetSysmanEventGetState_t(self.__dditable.SysmanEvent.pfnGetState)
        self.zetSysmanEventListen = _zetSysmanEventListen_t(self.__dditable.SysmanEvent.pfnListen)

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
