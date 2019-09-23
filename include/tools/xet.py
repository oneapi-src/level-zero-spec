"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

 @file xet.py

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
class xet_driver_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of device object
class xet_device_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of command list object
class xet_command_list_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of module object
class xet_module_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of function object
class xet_function_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of metric group's object
class xet_metric_group_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of metric's object
class xet_metric_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of metric tracer's object
class xet_metric_tracer_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of metric query pool's object
class xet_metric_query_pool_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of metric query's object
class xet_metric_query_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of tracer object
class xet_tracer_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for accessing System Resource Management features of a device
class xet_sysman_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device power domain
class xet_sysman_pwr_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device frequency domain
class xet_sysman_freq_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device engine group
class xet_sysman_engine_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device standby control
class xet_sysman_standby_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device firmware
class xet_sysman_firmware_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device memory module
class xet_sysman_mem_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device connectivity switch
class xet_sysman_link_switch_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device connectivity port
class xet_sysman_link_port_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device temperature sensor
class xet_sysman_temp_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device power supply
class xet_sysman_psu_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device fan
class xet_sysman_fan_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device LED
class xet_sysman_led_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device RAS error set
class xet_sysman_ras_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device diagnostics test suite
class xet_sysman_diag_handle_t(c_void_p):
    pass

###############################################################################
## @brief Maximum metric group name string size
XET_MAX_METRIC_GROUP_NAME = 256

###############################################################################
## @brief Maximum metric group description string size
XET_MAX_METRIC_GROUP_DESCRIPTION = 256

###############################################################################
## @brief Metric group sampling type
class xet_metric_group_sampling_type_v(IntEnum):
    EVENT_BASED = XE_BIT(0)                         ## Event based sampling
    TIME_BASED = XE_BIT(1)                          ## Time based sampling

class xet_metric_group_sampling_type_t(c_int):
    def __str__(self):
        return str(xet_metric_group_sampling_type_v(value))


###############################################################################
## @brief API version of ::xet_metric_group_properties_t
class xet_metric_group_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xet_metric_group_properties_version_t(c_int):
    def __str__(self):
        return str(xet_metric_group_properties_version_v(value))


###############################################################################
## @brief Metric group properties queried using ::xetMetricGroupGetProperties
class xet_metric_group_properties_t(Structure):
    _fields_ = [
        ("version", xet_metric_group_properties_version_t),             ## [in] ::XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT
        ("name", c_char * XET_MAX_METRIC_GROUP_NAME),                   ## [out] metric group name
        ("description", c_char * XET_MAX_METRIC_GROUP_DESCRIPTION),     ## [out] metric group description
        ("samplingType", xet_metric_group_sampling_type_t),             ## [out] metric group sampling type
        ("domain", c_ulong),                                            ## [out] metric group domain number. Cannot use simultaneous metric
                                                                        ## groups from different domains.
        ("metricCount", c_ulong)                                        ## [out] metric count belonging to this group
    ]

###############################################################################
## @brief Metric types
class xet_metric_type_v(IntEnum):
    DURATION = auto()                               ## Metric type: duration
    EVENT = auto()                                  ## Metric type: event
    EVENT_WITH_RANGE = auto()                       ## Metric type: event with range
    THROUGHPUT = auto()                             ## Metric type: throughput
    TIMESTAMP = auto()                              ## Metric type: timestamp
    FLAG = auto()                                   ## Metric type: flag
    RATIO = auto()                                  ## Metric type: ratio
    RAW = auto()                                    ## Metric type: raw

class xet_metric_type_t(c_int):
    def __str__(self):
        return str(xet_metric_type_v(value))


###############################################################################
## @brief Supported value types
class xet_value_type_v(IntEnum):
    UINT32 = auto()                                 ## 32-bit unsigned-integer
    UINT64 = auto()                                 ## 64-bit unsigned-integer
    FLOAT32 = auto()                                ## 32-bit floating-point
    FLOAT64 = auto()                                ## 64-bit floating-point
    BOOL8 = auto()                                  ## 8-bit boolean

class xet_value_type_t(c_int):
    def __str__(self):
        return str(xet_value_type_v(value))


###############################################################################
## @brief Union of values
class xet_value_t(Structure):
    _fields_ = [
        ("ui32", c_ulong),                                              ## [out] 32-bit unsigned-integer
        ("ui64", c_ulonglong),                                          ## [out] 32-bit unsigned-integer
        ("fp32", c_float),                                              ## [out] 32-bit floating-point
        ("fp64", c_double),                                             ## [out] 64-bit floating-point
        ("b8", xe_bool_t)                                               ## [out] 8-bit boolean
    ]

###############################################################################
## @brief Typed value
class xet_typed_value_t(Structure):
    _fields_ = [
        ("type", xet_value_type_t),                                     ## [out] type of value
        ("value", xet_value_t)                                          ## [out] value
    ]

###############################################################################
## @brief Maximum metric name string size
XET_MAX_METRIC_NAME = 256

###############################################################################
## @brief Maximum metric description string size
XET_MAX_METRIC_DESCRIPTION = 256

###############################################################################
## @brief Maximum metric component string size
XET_MAX_METRIC_COMPONENT = 256

###############################################################################
## @brief Maximum metric result units string size
XET_MAX_METRIC_RESULT_UNITS = 256

###############################################################################
## @brief API version of ::xet_metric_properties_t
class xet_metric_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xet_metric_properties_version_t(c_int):
    def __str__(self):
        return str(xet_metric_properties_version_v(value))


###############################################################################
## @brief Metric properties queried using ::xetMetricGetProperties
class xet_metric_properties_t(Structure):
    _fields_ = [
        ("version", xet_metric_properties_version_t),                   ## [in] ::XET_METRIC_PROPERTIES_VERSION_CURRENT
        ("name", c_char * XET_MAX_METRIC_NAME),                         ## [out] metric name
        ("description", c_char * XET_MAX_METRIC_DESCRIPTION),           ## [out] metric description
        ("component", c_char * XET_MAX_METRIC_COMPONENT),               ## [out] metric component
        ("tierNumber", c_ulong),                                        ## [out] number of tier
        ("metricType", xet_metric_type_t),                              ## [out] metric type
        ("resultType", xet_value_type_t),                               ## [out] metric result type
        ("resultUnits", c_char * XET_MAX_METRIC_RESULT_UNITS)           ## [out] metric result units
    ]

###############################################################################
## @brief API version of ::xet_metric_tracer_desc_t
class xet_metric_tracer_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xet_metric_tracer_desc_version_t(c_int):
    def __str__(self):
        return str(xet_metric_tracer_desc_version_v(value))


###############################################################################
## @brief Metric tracer descriptor
class xet_metric_tracer_desc_t(Structure):
    _fields_ = [
        ("version", xet_metric_tracer_desc_version_t),                  ## [in] ::XET_METRIC_TRACER_DESC_VERSION_CURRENT
        ("notifyEveryNReports", c_ulong),                               ## [in,out] number of collected reports after which notification event
                                                                        ## will be signalled
        ("samplingPeriod", c_ulong)                                     ## [in,out] tracer sampling period in nanoseconds
    ]

###############################################################################
## @brief API version of ::xet_metric_query_pool_desc_t
class xet_metric_query_pool_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xet_metric_query_pool_desc_version_t(c_int):
    def __str__(self):
        return str(xet_metric_query_pool_desc_version_v(value))


###############################################################################
## @brief Metric query pool types
class xet_metric_query_pool_flag_v(IntEnum):
    PERFORMANCE = auto()                            ## Performance metric query pool.
    SKIP_EXECUTION = auto()                         ## Skips workload execution between begin/end calls.

class xet_metric_query_pool_flag_t(c_int):
    def __str__(self):
        return str(xet_metric_query_pool_flag_v(value))


###############################################################################
## @brief Metric query pool description
class xet_metric_query_pool_desc_t(Structure):
    _fields_ = [
        ("version", xet_metric_query_pool_desc_version_t),              ## [in] ::XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT
        ("flags", xet_metric_query_pool_flag_t),                        ## [in] Query pool type.
        ("count", c_ulong)                                              ## [in] Internal slots count within query pool object.
    ]

###############################################################################
## @brief Supported module debug info formats.
class xet_module_debug_info_format_v(IntEnum):
    ELF_DWARF = auto()                              ## Format is ELF/DWARF

class xet_module_debug_info_format_t(c_int):
    def __str__(self):
        return str(xet_module_debug_info_format_v(value))


###############################################################################
## @brief API version of ::xet_profile_info_t
class xet_profile_info_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xet_profile_info_version_t(c_int):
    def __str__(self):
        return str(xet_profile_info_version_v(value))


###############################################################################
## @brief Supportted profile features
class xet_profile_flag_v(IntEnum):
    REGISTER_REALLOCATION = XE_BIT(0)               ## request the compiler attempt to minimize register usage as much as
                                                    ## possible to allow for instrumentation
    FREE_REGISTER_INFO = XE_BIT(1)                  ## request the compiler generate free register info

class xet_profile_flag_t(c_int):
    def __str__(self):
        return str(xet_profile_flag_v(value))


###############################################################################
## @brief Profiling meta-data for instrumentation
class xet_profile_info_t(Structure):
    _fields_ = [
        ("version", xet_profile_info_version_t),                        ## [in] ::XET_PROFILE_INFO_VERSION_CURRENT
        ("flags", xet_profile_flag_t),                                  ## [out] indicates which flags were enabled during compilation
        ("numTokens", c_ulong)                                          ## [out] number of tokens immediately following this structure
    ]

###############################################################################
## @brief Supported profile token types
class xet_profile_token_type_v(IntEnum):
    FREE_REGISTER = auto()                          ## GRF info

class xet_profile_token_type_t(c_int):
    def __str__(self):
        return str(xet_profile_token_type_v(value))


###############################################################################
## @brief Profile free register token detailing unused registers in the current
##        function
class xet_profile_free_register_token_t(Structure):
    _fields_ = [
        ("type", xet_profile_token_type_t),                             ## [out] type of token
        ("size", c_ulong),                                              ## [out] total size of the token, in bytes
        ("count", c_ulong)                                              ## [out] number of register sequences immediately following this
                                                                        ## structure
    ]

###############################################################################
## @brief Profile register sequence detailing consecutive bytes, all of which
##        are unused
class xet_profile_register_sequence_t(Structure):
    _fields_ = [
        ("start", c_ulong),                                             ## [out] starting byte in the register table, representing the start of
                                                                        ## unused bytes in the current function
        ("count", c_ulong)                                              ## [out] number of consecutive bytes in the sequence, starting from start
    ]

###############################################################################
## @brief API version of SMI
class xet_sysman_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xet_sysman_version_t(c_int):
    def __str__(self):
        return str(xet_sysman_version_v(value))


###############################################################################
## @brief Maximum number of characters in string properties.
XET_STRING_PROPERTY_SIZE = 32

###############################################################################
## @brief Device properties
class xet_sysman_properties_t(Structure):
    _fields_ = [
        ("core", xe_device_properties_t),                               ## [out] Core device properties
        ("numSubdevices", c_ulong),                                     ## [out] Number of sub-devices
        ("serialNumber", c_int8_t * XET_STRING_PROPERTY_SIZE),          ## [out] Manufacturing serial number (NULL terminated string value)
        ("boardNumber", c_int8_t * XET_STRING_PROPERTY_SIZE),           ## [out] Manufacturing board number (NULL terminated string value)
        ("brandName", c_int8_t * XET_STRING_PROPERTY_SIZE),             ## [out] Brand name of the device (NULL terminated string value)
        ("modelName", c_int8_t * XET_STRING_PROPERTY_SIZE),             ## [out] Model name of the device (NULL terminated string value)
        ("vendorName", c_int8_t * XET_STRING_PROPERTY_SIZE),            ## [out] Vendor name of the device (NULL terminated string value)
        ("driverVersion", c_int8_t * XET_STRING_PROPERTY_SIZE)          ## [out] Installed driver version (NULL terminated string value)
    ]

###############################################################################
## @brief Scheduler mode
class xet_sched_mode_v(IntEnum):
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
    SINGLE_CMDQUEUE = auto()                        ## Only a single command queue can execute work at a given time. Work is
                                                    ## permitted to run as long as needed without enforcing any scheduler
                                                    ## fairness policies.

class xet_sched_mode_t(c_int):
    def __str__(self):
        return str(xet_sched_mode_v(value))


###############################################################################
## @brief Disable forward progress guard timeout.
XET_SCHED_WATCHDOG_DISABLE = (~(0ULL))

###############################################################################
## @brief Configuration for timeout scheduler mode (::XET_SCHED_MODE_TIMEOUT)
class xet_sched_timeout_properties_t(Structure):
    _fields_ = [
        ("watchdogTimeout", c_ulonglong)                                ## [in,out] The maximum time in microseconds that the scheduler will wait
                                                                        ## for a batch of work submitted to a hardware engine to complete or to
                                                                        ## be preempted so as to run another context.
                                                                        ## If this time is exceeded, the hardware engine is reset and the context terminated.
                                                                        ## If set to ::XET_SCHED_WATCHDOG_DISABLE, a running workload can run as
                                                                        ## long as it wants without being terminated, but preemption attempts to
                                                                        ## run other contexts are permitted but not enforced.
    ]

###############################################################################
## @brief Configuration for timeslice scheduler mode
##        (::XET_SCHED_MODE_TIMESLICE)
class xet_sched_timeslice_properties_t(Structure):
    _fields_ = [
        ("interval", c_ulonglong),                                      ## [in,out] The average interval in microseconds that a submission for a
                                                                        ## context will run on a hardware engine before being preempted out to
                                                                        ## run a pending submission for another context.
        ("yieldTimeout", c_ulonglong)                                   ## [in,out] The maximum time in microseconds that the scheduler will wait
                                                                        ## to preempt a workload running on an engine before deciding to reset
                                                                        ## the hardware engine and terminating the associated context.
    ]

###############################################################################
## @brief PCI address
class xet_pci_address_t(Structure):
    _fields_ = [
        ("domain", c_ulong),                                            ## [out] BDF domain
        ("bus", c_ulong),                                               ## [out] BDF bus
        ("device", c_ulong),                                            ## [out] BDF device
        ("function", c_ulong)                                           ## [out] BDF function
    ]

###############################################################################
## @brief PCI speed
class xet_pci_speed_t(Structure):
    _fields_ = [
        ("gen", c_ulong),                                               ## [out] The link generation
        ("width", c_ulong),                                             ## [out] The number of lanes
        ("maxBandwidth", c_ulong),                                      ## [out] The maximum bandwidth in bytes/sec
        ("maxPacketSize", c_ulong)                                      ## [out] Maximum packet size in bytes.
    ]

###############################################################################
## @brief Static PCI properties
class xet_pci_properties_t(Structure):
    _fields_ = [
        ("address", xet_pci_address_t),                                 ## [out] The BDF address
        ("numBars", c_ulong),                                           ## [out] The number of configured bars
        ("maxSpeed", xet_pci_speed_t)                                   ## [out] Fastest port configuration supported by the device.
    ]

###############################################################################
## @brief Dynamic PCI state
class xet_pci_state_t(Structure):
    _fields_ = [
        ("speed", xet_pci_speed_t)                                      ## [out] The current port configure speed
    ]

###############################################################################
## @brief PCI bar types
class xet_pci_bar_type_v(IntEnum):
    CONFIG = 0                                      ## PCI configuration space
    MMIO = auto()                                   ## MMIO registers
    VRAM = auto()                                   ## VRAM aperture
    ROM = auto()                                    ## ROM aperture
    VGA_IO = auto()                                 ## Legacy VGA IO ports
    VGA_MEM = auto()                                ## Legacy VGA memory
    INDIRECT_IO = auto()                            ## Indirect IO port access
    INDIRECT_MEM = auto()                           ## Indirect memory access
    OTHER = auto()                                  ## Other type of PCI bar

class xet_pci_bar_type_t(c_int):
    def __str__(self):
        return str(xet_pci_bar_type_v(value))


###############################################################################
## @brief Properties of a pci bar
class xet_pci_bar_properties_t(Structure):
    _fields_ = [
        ("type", xet_pci_bar_type_t),                                   ## [out] The type of bar
        ("base", c_ulonglong),                                          ## [out] Base address of the bar.
        ("size", c_ulonglong)                                           ## [out] Size of the bar.
    ]

###############################################################################
## @brief PCI throughput
## 
## @details
##     - Percent throughput is calculated by taking two snapshots (s1, s2) and
##       using the equation: %bw = 10^6 * ((s2.rxCounter - s1.rxCounter) +
##       (s2.txCounter - s1.txCounter)) / (s2.maxBandwidth * (s2.timestamp -
##       s1.timestamp))
class xet_pci_throughput_t(Structure):
    _fields_ = [
        ("timestamp", c_ulonglong),                                     ## [out] Monotonic timestamp counter in microseconds when the measurement
                                                                        ## was made.
                                                                        ## No assumption should be made about the absolute value of the timestamp.
                                                                        ## It should only be used to calculate delta time between two snapshots
                                                                        ## of the same structure.
                                                                        ## Never take the delta of this timestamp with the timestamp from a
                                                                        ## different structure.
        ("rxCounter", c_ulonglong),                                     ## [out] Monotonic counter for the number of bytes received
        ("txCounter", c_ulonglong),                                     ## [out] Monotonic counter for the number of bytes transmitted (including
                                                                        ## replays)
        ("maxBandwidth", c_ulong)                                       ## [out] The maximum bandwidth in bytes/sec under the current
                                                                        ## configuration
    ]

###############################################################################
## @brief PCI stats counters
## 
## @details
##     - Percent replays is calculated by taking two snapshots (s1, s2) and
##       using the equation: %replay = 10^6 * (s2.replayCounter -
##       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
class xet_pci_stats_t(Structure):
    _fields_ = [
        ("timestamp", c_ulonglong),                                     ## [out] Monotonic timestamp counter in microseconds when the measurement
                                                                        ## was made.
                                                                        ## No assumption should be made about the absolute value of the timestamp.
                                                                        ## It should only be used to calculate delta time between two snapshots
                                                                        ## of the same structure.
                                                                        ## Never take the delta of this timestamp with the timestamp from a
                                                                        ## different structure.
        ("replayCounter", c_ulonglong),                                 ## [out] Monotonic counter for the number of replay packets
        ("packetCounter", c_ulonglong)                                  ## [out] Monotonic counter for the number of packets
    ]

###############################################################################
## @brief Properties related to device power settings
class xet_power_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", xe_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", xe_bool_t),                                      ## [out] Software can change the power limits.
        ("maxLimit", c_ulong)                                           ## [out] The maximum power limit in milliwatts that can be requested.
    ]

###############################################################################
## @brief Energy counter snapshot
## 
## @details
##     - Average power is calculated by taking two snapshots (s1, s2) and using
##       the equation: PowerWatts = (s2.energy - s1.energy) / (s2.timestamp -
##       s1.timestamp)
class xet_power_energy_counter_t(Structure):
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
## @brief Energy threshold
## 
## @details
##     - Energy threshold value, when this value is crossed, pcu will signal an
##       interrupt.
class xet_power_energy_threshold_t(Structure):
    _fields_ = [
        ("energy", c_ulong)                                             ## [in,out] The energy threshold in joules.
    ]

###############################################################################
## @brief Sustained power limits
## 
## @details
##     - The power controller (Punit) will throttle the operating frequency if
##       the power averaged over a window (typically seconds) exceeds this
##       limit.
class xet_power_sustained_limit_t(Structure):
    _fields_ = [
        ("enabled", xe_bool_t),                                         ## [in,out] indicates if the limit is enabled (true) or ignored (false)
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
class xet_power_burst_limit_t(Structure):
    _fields_ = [
        ("enabled", xe_bool_t),                                         ## [in,out] indicates if the limit is enabled (true) or ignored (false)
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
class xet_power_peak_limit_t(Structure):
    _fields_ = [
        ("power", c_ulong)                                              ## [in,out] power limit in milliwatts
    ]

###############################################################################
## @brief Overcloking modes
class xet_oc_mode_v(IntEnum):
    INTERPOLATIVE = 0                               ## Interpolative Mode.
    OVERRIDE = 1                                    ## Override Mode.

class xet_oc_mode_t(c_int):
    def __str__(self):
        return str(xet_oc_mode_v(value))


###############################################################################
## @brief Overclocking error type
class xet_oc_error_type_v(IntEnum):
    OVERCLOCKING_LOCKED = 225                       ## The overclocking is locked. Service is read-only.
    OVERCLOCKING_DDOMAIN_SERVICE_NOT_SUPPORTED = auto() ## The specified domain does not support the requested service.
    OVERCLOCKING_RATIO_EXCEEDS_MAX = auto()         ## The ratio exceeds maximum overclocking limits.
    OVERCLOCKING_VOLTAGE_EXCEEDS_MAX = auto()       ## Requested voltage exceeds input regulators max supported voltage.
    OVERCLOCKING_NOT_SUPPORTED = auto()             ## No overclocking capability on the Hardware.
    $OVERCLOCKING_INVALID_VR_ADDRESS = auto()       ## The VR Address provided is illegal.
    $OVERCLOCKING_INVALID_ICCMAX = auto()           ## ICCMAX value given is invalid (more than 10 bits) or too low.
    OVERCLOCKING_VOLTAGE_OVERRIDE_DISABLED = auto() ## Voltage manipulation attempted when it is disabled.
    OVERCLOCKING_INVALID_COMMAND = auto()           ## Data setting invalid for the command.

class xet_oc_error_type_t(c_int):
    def __str__(self):
        return str(xet_oc_error_type_v(value))


###############################################################################
## @brief Overclocking VR Topolgy
## 
## @details
##     - Provides all the information related to the VR.
class xet_oc_vr_topology(Structure):
    _fields_ = [
        ("VccInAuxExists", xe_bool_t),                                  ## [out] VCCIN_AUX Exists (asserted if separate VR)
        ("VccStgPgExists", xe_bool_t),                                  ## [out] VCCSTG_PG Exists
        ("VccStPgExists", xe_bool_t),                                   ## [out] VCCST_PG Exists
        ("VccSfrOcPgExists", xe_bool_t),                                ## [out] VCCSFR_OC_PG Exists
        ("VccInAuxLp", c_ushort),                                       ## [out] VCCIN_Aux_LP Level (0: 1.8v, 1: 1.65v)
        ("VccInSvidAddress", c_ushort),                                 ## [out] VCCIN SVID Address
        ("VccInVrType", c_ushort),                                      ## [out] VCCIN VR Type (asserted if SVID)
        ("SvidNotPresent", c_ushort),                                   ## [out] SVID not present
        ("PsysDisabled", c_ushort)                                      ## [out] PSYS Disabled
    ]

###############################################################################
## @brief Overclocking properties
## 
## @details
##     - Provides all the overclocking capabilities and properties supported by
##       the device in the current domain.
class xet_oc_capabilities_t(Structure):
    _fields_ = [
        ("MaxOcRatioLimit", c_ushort),                                  ## [out] Max overclocking ratio limit
        ("P0Ratio", c_ushort),                                          ## [out] Fused P0 ratio.
        ("P0Voltage", c_ushort),                                        ## [out] Fused P0 voltage.
        ("RatioOcSupported", xe_bool_t),                                ## [out] Ratio overclocking supported
        ("VoltageOverrideSupported", xe_bool_t),                        ## [out] Voltage overrides supported
        ("VoltageOffsetSupported", xe_bool_t),                          ## [out] Voltage offset is supported
        ("HighVoltModeCapable", xe_bool_t),                             ## [out] Capable of high voltage mode
        ("HighVoltModeEnabled", xe_bool_t),                             ## [out] High voltage mode is enabled
        ("OcVrTopology", xet_oc_vr_topology)                            ## [out] Hold all the Vr Topology properties.
    ]

###############################################################################
## @brief Overclocking settings override
## 
## @details
##     - Provide the current settings to be read or changed.
class xet_oc_settings_override_t(Structure):
    _fields_ = [
        ("MaxOcRatio", c_ushort),                                       ## [in,out] Max overclocking ratio
        ("TargetVoltage", c_ushort),                                    ## [in,out] Target Voltage. Units: divide by 2^10 for decimal voltage.
        ("TargetMode", c_ushort),                                       ## [in,out] Overclock Mode: 0 - Interpolative,  1 - Override.
        ("VoltageOffset", c_ushort),                                    ## [in,out] Voltage offset +/-999mV (minimum end voltage cannot be lower
                                                                        ## than 250mV).
        ("ICCMax", c_ulong),                                            ## [in,out] Maximum desired current.
        ("TjMax", c_ulong)                                              ## [in,out] Maximum temperature in °C.
    ]

###############################################################################
## @brief Fan Point.
## 
## @details
##     - Temperature is given in °C and fan speed is given as a percentage
##       value
class xet_oc_fan_point_t(Structure):
    _fields_ = [
        ("TemperatureDegreesCelsius", c_ubyte),                         ## [in] Temperature for current point.
        ("FanSpeedPercent", c_ubyte)                                    ## [in] Percentage value, where 0% means stop the fan and 100% means run
                                                                        ## the fan at maximum speed.
    ]

###############################################################################
## @brief Fan control settings.
## 
## @details
##     - Provide the means to control the fan speed.
class xet_oc_fan_control_t(Structure):
    _fields_ = [
        ("FanPointsNumber", c_ulong),                                   ## [in] Number of fan points.
        ("pFanPoints", POINTER(xet_oc_fan_poc_int_t))                   ## [in] Array with FanPointsNumber of points.
    ]

###############################################################################
## @brief Frequency domains
class xet_freq_domain_v(IntEnum):
    GPU = 0                                         ## Frequency of the GPU.
    MEMORY = auto()                                 ## Frequency of the local memory.

class xet_freq_domain_t(c_int):
    def __str__(self):
        return str(xet_freq_domain_v(value))


###############################################################################
## @brief Frequency properties
## 
## @details
##     - Provides the set of frequencies as a list and as a range/step.
##     - It is generally recommended that applications choose frequencies from
##       the list. However applications can also construct the list themselves
##       using the range/steps provided.
class xet_freq_properties_t(Structure):
    _fields_ = [
        ("type", xet_freq_domain_t),                                    ## [out] The type of frequency domain (GPU, memory, ...)
        ("onSubdevice", xe_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", xe_bool_t),                                      ## [out] Indicates if software can control the frequency of this domain
        ("canOverclock", xe_bool_t),                                    ## [out] Indicates if software can overclock this frequency domain
        ("min", c_double),                                              ## [out] The minimum clock frequency in units of MHz
        ("max", c_double),                                              ## [out] The maximum clock frequency in units of MHz
        ("step", c_double),                                             ## [out] The step clock frequency in units of MHz
        ("num", c_ulong),                                               ## [out] The number of clocks in the array pClocks
        ("pClocks", POINTER(c_double))                                  ## [out] Array of clock frequencies in units of MHz ordered from smallest
                                                                        ## to largest.
    ]

###############################################################################
## @brief Frequency range between which the hardware can operate.
class xet_freq_range_t(Structure):
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
class xet_freq_throttle_reasons_v(IntEnum):
    NONE = 0                                        ## frequency not throttled
    AVE_PWR_CAP = XE_BIT( 0 )                       ## frequency throttled due to average power excursion (PL1)
    BURST_PWR_CAP = XE_BIT( 1 )                     ## frequency throttled due to burst power excursion (PL2)
    CURRENT_LIMIT = XE_BIT( 2 )                     ## frequency throttled due to current excursion (PL4)
    THERMAL_LIMIT = XE_BIT( 3 )                     ## frequency throttled due to thermal excursion (T > TjMax)
    PSU_ALERT = XE_BIT( 4 )                         ## frequency throttled due to power supply assertion
    SW_RANGE = XE_BIT( 5 )                          ## frequency throttled due to software supplied frequency range
    HW_RANGE = XE_BIT( 6 )                          ## frequency throttled due to a sub block that has a lower frequency
                                                    ## range when it receives clocks

class xet_freq_throttle_reasons_t(c_int):
    def __str__(self):
        return str(xet_freq_throttle_reasons_v(value))


###############################################################################
## @brief Frequency state
class xet_freq_state_t(Structure):
    _fields_ = [
        ("request", c_double),                                          ## [out] The current frequency request in MHz.
        ("tdp", c_double),                                              ## [out] The maximum frequency in MHz supported under the current TDP
                                                                        ## conditions
        ("efficient", c_double),                                        ## [out] The efficient minimum frequency in MHz
        ("actual", c_double),                                           ## [out] The resolved frequency in MHz
        ("throttleReasons", c_ulong)                                    ## [out] The reasons that the frequency is being limited by the hardware
                                                                        ## (Bitfield of (1<<::xet_freq_throttle_reasons_t)).
    ]

###############################################################################
## @brief Frequency throttle time snapshot
## 
## @details
##     - Percent time throttled is calculated by taking two snapshots (s1, s2)
##       and using the equation: %throttled = (s2.throttleTime -
##       s1.throttleTime) / (s2.timestamp - s1.timestamp)
class xet_freq_throttle_time_t(Structure):
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
## @brief Accelerator engine groups
class xet_engine_group_v(IntEnum):
    ALL = 0                                         ## Access information about all engines combined.
    COMPUTE = auto()                                ## Access information about compute engines.
    MEDIA = auto()                                  ## Access information about media engines.

class xet_engine_group_t(c_int):
    def __str__(self):
        return str(xet_engine_group_v(value))


###############################################################################
## @brief Engine group properties
class xet_engine_properties_t(Structure):
    _fields_ = [
        ("type", xet_engine_group_t),                                   ## [out] The engine group
        ("onSubdevice", xe_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
    ]

###############################################################################
## @brief Engine activity counters
## 
## @details
##     - Percent utilization is calculated by taking two snapshots (s1, s2) and
##       using the equation: %util = (s2.activeTime - s1.activeTime) /
##       (s2.timestamp - s1.timestamp)
class xet_engine_stats_t(Structure):
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
class xet_standby_type_v(IntEnum):
    GLOBAL = 0                                      ## Control the overall standby policy of the device/sub-device

class xet_standby_type_t(c_int):
    def __str__(self):
        return str(xet_standby_type_v(value))


###############################################################################
## @brief Standby hardware component properties
class xet_standby_properties_t(Structure):
    _fields_ = [
        ("type", xet_standby_type_t),                                   ## [out] Which standby hardware component this controls
        ("onSubdevice", xe_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
    ]

###############################################################################
## @brief Standby promotion modes
class xet_standby_promo_mode_v(IntEnum):
    DEFAULT = 0                                     ## Best compromise between performance and energy savings.
    NEVER = auto()                                  ## The device/component will never shutdown. This can improve performance
                                                    ## but uses more energy.

class xet_standby_promo_mode_t(c_int):
    def __str__(self):
        return str(xet_standby_promo_mode_v(value))


###############################################################################
## @brief Firmware properties
class xet_firmware_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", xe_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", xe_bool_t),                                      ## [out] Indicates if software can flash the firmware
        ("name", c_int8_t * XET_STRING_PROPERTY_SIZE),                  ## [out] NULL terminated string value
        ("version", c_int8_t * XET_STRING_PROPERTY_SIZE)                ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Memory module types
class xet_mem_type_v(IntEnum):
    HBM = 0                                         ## HBM memory
    DDR = auto()                                    ## DDR memory
    SRAM = auto()                                   ## SRAM memory
    L1 = auto()                                     ## L1 cache
    L3 = auto()                                     ## L3 cache
    GRF = auto()                                    ## Execution unit register file
    SLM = auto()                                    ## Execution unit shared local memory

class xet_mem_type_t(c_int):
    def __str__(self):
        return str(xet_mem_type_v(value))


###############################################################################
## @brief Memory properties
class xet_mem_properties_t(Structure):
    _fields_ = [
        ("type", xet_mem_type_t),                                       ## [out] The memory type
        ("onSubdevice", xe_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("size", c_ulonglong)                                           ## [out] Physical memory size in bytes
    ]

###############################################################################
## @brief Memory bandwidth
## 
## @details
##     - Percent bandwidth is calculated by taking two snapshots (s1, s2) and
##       using the equation: %bw = 10^6 * ((s2.readCounter - s1.readCounter) +
##       (s2.writeCounter - s1.writeCounter)) / (s2.maxBandwidth *
##       (s2.timestamp - s1.timestamp))
class xet_mem_bandwidth_t(Structure):
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
## @brief Memory allocation
## 
## @details
##     - Percent allocation is given by 100 * allocated / total.
##     - Percent free is given by 100 * (total - allocated) / total.
class xet_mem_alloc_t(Structure):
    _fields_ = [
        ("allocated", c_ulonglong),                                     ## [out] The total allocated bytes
        ("total", c_ulonglong)                                          ## [out] The total physical memory in bytes
    ]

###############################################################################
## @brief Connectivity switch properties
class xet_link_switch_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", xe_bool_t),                                     ## [out] True if the switch is located on a sub-device; false means that
                                                                        ## the switch is on the device of the calling SMI handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
    ]

###############################################################################
## @brief Connectivity switch state
class xet_link_switch_state_t(Structure):
    _fields_ = [
        ("enabled", xe_bool_t)                                          ## [out] Indicates if the switch is enabled/disabled
    ]

###############################################################################
## @brief Connectivity port speed
class xet_link_port_speed_t(Structure):
    _fields_ = [
        ("bitRate", c_ulong),                                           ## [out] Bits/sec that the link is operating at
        ("width", c_ulong),                                             ## [out] The number of lanes
        ("maxBandwidth", c_ulong)                                       ## [out] The maximum bandwidth in bytes/sec
    ]

###############################################################################
## @brief Connectivity port properties
class xet_link_port_properties_t(Structure):
    _fields_ = [
        ("portNum", c_ulong),                                           ## [out] The port number on the switch
        ("maxSpeed", xet_link_port_speed_t)                             ## [out] Maximum bandwidth supported by the port
    ]

###############################################################################
## @brief Connectivity port state
class xet_link_port_state_t(Structure):
    _fields_ = [
        ("isConnected", xe_bool_t),                                     ## [out] Indicates if the port is connected to a remote Switch
        ("rxSpeed", xet_link_port_speed_t),                             ## [out] Current maximum receive speed
        ("txSpeed", xet_link_port_speed_t)                              ## [out] Current maximum transmit speed
    ]

###############################################################################
## @brief Connectivity port throughput
## 
## @details
##     - Percent throughput is calculated by taking two snapshots (s1, s2) and
##       using the equation:
##     -     %rx_bandwidth = 10^6 * (s2.rxCounter - s1.rxCounter) /
##       (s2.rxMaxBandwidth * (s2.timestamp - s1.timestamp))
##     -     %tx_bandwidth = 10^6 * (s2.txCounter - s1.txCounter) /
##       (s2.txMaxBandwidth * (s2.timestamp - s1.timestamp))
class xet_link_port_throughput_t(Structure):
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
        ("rxMaxBandwidth", c_ulong),                                    ## [out] The current maximum bandwidth in bytes/sec for receiving packats
        ("txMaxBandwidth", c_ulong)                                     ## [out] The current maximum bandwidth in bytes/sec for transmitting
                                                                        ## packets
    ]

###############################################################################
## @brief Connectivity port stats counters
## 
## @details
##     - Percent replays is calculated by taking two snapshots (s1, s2) and
##       using the equation: %replay = 10^6 * (s2.replayCounter -
##       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
class xet_link_port_stats_t(Structure):
    _fields_ = [
        ("timestamp", c_ulonglong),                                     ## [out] Monotonic timestamp counter in microseconds when the measurement
                                                                        ## was made.
                                                                        ## No assumption should be made about the absolute value of the timestamp.
                                                                        ## It should only be used to calculate delta time between two snapshots
                                                                        ## of the same structure.
                                                                        ## Never take the delta of this timestamp with the timestamp from a
                                                                        ## different structure.
        ("replayCounter", c_ulonglong),                                 ## [out] Monotonic counter for the number of replay packets
        ("packetCounter", c_ulonglong)                                  ## [out] Monotonic counter for the number of packets
    ]

###############################################################################
## @brief Temperature sensors
class xet_temp_sensors_v(IntEnum):
    GLOBAL = 0                                      ## The maximum temperature across all device sensors
    GPU = auto()                                    ## The maximum temperature across all sensors in the GPU
    MEMORY = auto()                                 ## The maximum temperature across all sensors in the local memory

class xet_temp_sensors_t(c_int):
    def __str__(self):
        return str(xet_temp_sensors_v(value))


###############################################################################
## @brief Temperature sensor properties
class xet_temp_properties_t(Structure):
    _fields_ = [
        ("type", xet_temp_sensors_t),                                   ## [out] Which part of the device the temperature sensor measures
        ("onSubdevice", xe_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
    ]

###############################################################################
## @brief PSU voltage status
class xet_psu_voltage_status_v(IntEnum):
    NORMAL = 0                                      ## No unusual voltages have been detected
    OVER = auto()                                   ## Over-voltage has occurred
    UNDER = auto()                                  ## Under-voltage has occurred

class xet_psu_voltage_status_t(c_int):
    def __str__(self):
        return str(xet_psu_voltage_status_v(value))


###############################################################################
## @brief Static properties of the power supply
class xet_psu_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", xe_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", xe_bool_t),                                      ## [out] Indicates if software can control the PSU
        ("haveFan", xe_bool_t),                                         ## [out] True if the power supply has a fan
        ("ampLimit", c_ulong)                                           ## [out] The maximum electrical current in amperes that can be drawn
    ]

###############################################################################
## @brief Dynamic state of the power supply
class xet_psu_state_t(Structure):
    _fields_ = [
        ("voltStatus", xet_psu_voltage_status_t),                       ## [out] The current PSU voltage status
        ("fanFailed", xe_bool_t),                                       ## [out] Indicates if the fan has failed
        ("temperature", c_ulong),                                       ## [out] Read the current heatsink temperature in degrees celcius
        ("current", c_ulong)                                            ## [out] The amps being drawn in amperes
    ]

###############################################################################
## @brief Fan resource speed mode
class xet_fan_speed_mode_v(IntEnum):
    DEFAULT = 0                                     ## The fan speed is operating using the hardware default settings
    FIXED = auto()                                  ## The fan speed is currently set to a fixed value
    TABLE = auto()                                  ## The fan speed is currently controlled dynamically by hardware based on
                                                    ## a temp/speed table

class xet_fan_speed_mode_t(c_int):
    def __str__(self):
        return str(xet_fan_speed_mode_v(value))


###############################################################################
## @brief Fan speed units
class xet_fan_speed_units_v(IntEnum):
    RPM = 0                                         ## The fan speed is in units of revolutions per minute (rpm)
    PERCENT = auto()                                ## The fan speed is a percentage of the maximum speed of the fan

class xet_fan_speed_units_t(c_int):
    def __str__(self):
        return str(xet_fan_speed_units_v(value))


###############################################################################
## @brief Fan temperature/speed pair
class xet_fan_temp_speed_t(Structure):
    _fields_ = [
        ("temperature", c_ulong),                                       ## [in,out] Temperature in degrees celcius
        ("speed", c_ulong),                                             ## [in,out] The speed of the fan
        ("units", xet_fan_speed_units_t)                                ## [in,out] The units of the member speed
    ]

###############################################################################
## @brief Maximum number of fan temperature/speed pairs in the fan speed table.
XET_FAN_TEMP_SPEED_PAIR_COUNT = 32

###############################################################################
## @brief Fan properties
class xet_fan_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", xe_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", xe_bool_t),                                      ## [out] Indicates if software can control the fan speed
        ("maxSpeed", c_ulong),                                          ## [out] The maximum RPM of the fan
        ("maxPoints", c_ulong)                                          ## [out] The maximum number of points in the fan temp/speed table
    ]

###############################################################################
## @brief Fan configuration
class xet_fan_config_t(Structure):
    _fields_ = [
        ("mode", xet_fan_speed_mode_t),                                 ## [in,out] The fan speed mode (fixed, temp-speed table)
        ("speed", c_ulong),                                             ## [in,out] The fixed fan speed setting
        ("speedUnits", xet_fan_speed_units_t),                          ## [in,out] The units of the fixed fan speed setting
        ("numPoints", c_ulong),                                         ## [in,out] The number of valid points in the fan speed table
        ("table", xet_fan_temp_speed_t * XET_FAN_TEMP_SPEED_PAIR_COUNT) ## [in,out] Array of temperature/fan speed pairs
    ]

###############################################################################
## @brief Fan state
class xet_fan_state_t(Structure):
    _fields_ = [
        ("mode", xet_fan_speed_mode_t),                                 ## [out] The fan speed mode (default, fixed, temp-speed table)
        ("speedUnits", xet_fan_speed_units_t),                          ## [out] The units of the fan speed
        ("speed", c_ulong)                                              ## [out] The current fan speed
    ]

###############################################################################
## @brief LED properties
class xet_led_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", xe_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", xe_bool_t),                                      ## [out] Indicates if software can control the LED
        ("haveRGB", xe_bool_t)                                          ## [out] Indicates if the LED is RGB capable
    ]

###############################################################################
## @brief LED state
class xet_led_state_t(Structure):
    _fields_ = [
        ("isOn", xe_bool_t),                                            ## [in,out] Indicates if the LED is on or off
        ("red", c_ubyte),                                               ## [in,out][range(0, 255)] The LED red value
        ("green", c_ubyte),                                             ## [in,out][range(0, 255)] The LED green value
        ("blue", c_ubyte)                                               ## [in,out][range(0, 255)] The LED blue value
    ]

###############################################################################
## @brief RAS error type
class xet_ras_error_type_v(IntEnum):
    CORRECTABLE = 0                                 ## Errors were corrected by hardware
    UNCORRECTABLE = auto()                          ## Error were not corrected

class xet_ras_error_type_t(c_int):
    def __str__(self):
        return str(xet_ras_error_type_v(value))


###############################################################################
## @brief RAS properties
class xet_ras_properties_t(Structure):
    _fields_ = [
        ("type", xet_ras_error_type_t),                                 ## [out] The type of RAS error
        ("onSubdevice", xe_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("supported", xe_bool_t),                                       ## [out] True if RAS is supported on this device
        ("enabled", xe_bool_t)                                          ## [out] True if RAS is enabled on this device
    ]

###############################################################################
## @brief RAS error details
class xet_ras_details_t(Structure):
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
        ("numMemoryErrors", c_ulonglong),                               ## [out] The number of errors that have occurred in the local memory
        ("numPciErrors", c_ulonglong),                                  ## [out] The number of errors that have occurred in the PCI link
        ("numSwitchErrors", c_ulonglong),                               ## [out] The number of errors that have occurred in the high-speed
                                                                        ## connectivity links
        ("numDisplayErrors", c_ulonglong)                               ## [out] The number of errors that have occurred in the display
    ]

###############################################################################
## @brief Event types
class xet_sysman_event_type_v(IntEnum):
    FREQ_THROTTLED = 0                              ## The frequency is being throttled
    ENERGY_THRESHOLD_CROSSED = auto()               ## Interrupt from the PCU when the energy threshold is crossed.
    RAS_ERRORS = auto()                             ## ECC/RAS errors
    NUM = auto()                                    ## The number of event types

class xet_sysman_event_type_t(c_int):
    def __str__(self):
        return str(xet_sysman_event_type_v(value))


###############################################################################
## @brief Event properties
class xet_event_properties_t(Structure):
    _fields_ = [
        ("supportedEvents", xe_bool_t * XET_SYSMAN_EVENT_TYPE_NUM)      ## [out] Set to true for the events that are supported
    ]

###############################################################################
## @brief Request structure used to register/unregister events
class xet_event_request_t(Structure):
    _fields_ = [
        ("event", xet_sysman_event_type_t),                             ## [in] The event type to register.
        ("threshold", c_ulong)                                          ## [in] The application only receives a notification when the total count
                                                                        ## exceeds this value. Set to zero to receive a notification for every
                                                                        ## new event.
    ]

###############################################################################
## @brief Wait infinitely for events to arrive.
XET_EVENT_WAIT_INFINITE = 0xFFFFFFFF

###############################################################################
## @brief Diagnostic test suite type
class xet_diag_type_v(IntEnum):
    SCAN = 0                                        ## Run SCAN diagnostics
    ARRAY = auto()                                  ## Run Array diagnostics

class xet_diag_type_t(c_int):
    def __str__(self):
        return str(xet_diag_type_v(value))


###############################################################################
## @brief Diagnostic results
class xet_diag_result_v(IntEnum):
    NO_ERRORS = 0                                   ## Diagnostic completed without finding errors to repair
    ABORT = auto()                                  ## Diagnostic had problems running tests
    FAIL_CANT_REPAIR = auto()                       ## Diagnostic had problems setting up repairs
    REBOOT_FOR_REPAIR = auto()                      ## Diagnostics found errors, setup for repair and reboot is required to
                                                    ## complete the process

class xet_diag_result_t(c_int):
    def __str__(self):
        return str(xet_diag_result_v(value))


###############################################################################
## @brief Diagnostic test index to use for the very first test.
XET_DIAG_FIRST_TEST_INDEX = 0x0

###############################################################################
## @brief Diagnostic test index to use for the very last test.
XET_DIAG_LAST_TEST_INDEX = 0xFFFFFFFF

###############################################################################
## @brief Diagnostic test
class xet_diag_test_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [out] Index of the test
        ("name", POINTER(c_char))                                       ## [out] Name of the test
    ]

###############################################################################
## @brief Diagnostics test suite properties
class xet_diag_properties_t(Structure):
    _fields_ = [
        ("type", xet_diag_type_t),                                      ## [out] The type of diagnostics test suite
        ("onSubdevice", xe_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("name", POINTER(c_char)),                                      ## [out] Name of the diagnostics test suite
        ("numTests", c_ulong),                                          ## [out] The number of tests in the test suite
        ("pTests", POINTER(xet_diag_test_t))                            ## [out] Array of tests (size ::xet_diag_properties_t.numTests), sorted
                                                                        ## by increasing value of ::xet_diag_test_t.index
    ]

###############################################################################
## @brief Alias the existing callbacks definition for 'core' callbacks
class xet_core_callbacks_t(xe_callbacks_t):
    pass

###############################################################################
## @brief Alias the existing callbacks definition for 'experimental' callbacks
class xet_experimental_callbacks_t(xex_callbacks_t):
    pass

###############################################################################
## @brief API version of ::xet_tracer_desc_t
class xet_tracer_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xet_tracer_desc_version_t(c_int):
    def __str__(self):
        return str(xet_tracer_desc_version_v(value))


###############################################################################
## @brief Tracer descriptor
class xet_tracer_desc_t(Structure):
    _fields_ = [
        ("version", xet_tracer_desc_version_t),                         ## [in] ::XET_TRACER_DESC_VERSION_CURRENT
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
## @brief Function-pointer for xetInit
if __use_win_types:
    _xetInit_t = WINFUNCTYPE( xe_result_t, xe_init_flag_t )
else:
    _xetInit_t = CFUNCTYPE( xe_result_t, xe_init_flag_t )


###############################################################################
## @brief Table of Global functions pointers
class _xet_global_dditable_t(Structure):
    _fields_ = [
        ("pfnInit", c_void_p)                                           ## _xetInit_t
    ]

###############################################################################
## @brief Function-pointer for xetDeviceActivateMetricGroups
if __use_win_types:
    _xetDeviceActivateMetricGroups_t = WINFUNCTYPE( xe_result_t, xet_device_handle_t, c_ulong, POINTER(xet_metric_group_handle_t) )
else:
    _xetDeviceActivateMetricGroups_t = CFUNCTYPE( xe_result_t, xet_device_handle_t, c_ulong, POINTER(xet_metric_group_handle_t) )


###############################################################################
## @brief Table of Device functions pointers
class _xet_device_dditable_t(Structure):
    _fields_ = [
        ("pfnActivateMetricGroups", c_void_p)                           ## _xetDeviceActivateMetricGroups_t
    ]

###############################################################################
## @brief Function-pointer for xetCommandListAppendMetricTracerMarker
if __use_win_types:
    _xetCommandListAppendMetricTracerMarker_t = WINFUNCTYPE( xe_result_t, xet_command_list_handle_t, xet_metric_tracer_handle_t, c_ulong )
else:
    _xetCommandListAppendMetricTracerMarker_t = CFUNCTYPE( xe_result_t, xet_command_list_handle_t, xet_metric_tracer_handle_t, c_ulong )

###############################################################################
## @brief Function-pointer for xetCommandListAppendMetricQueryBegin
if __use_win_types:
    _xetCommandListAppendMetricQueryBegin_t = WINFUNCTYPE( xe_result_t, xet_command_list_handle_t, xet_metric_query_handle_t )
else:
    _xetCommandListAppendMetricQueryBegin_t = CFUNCTYPE( xe_result_t, xet_command_list_handle_t, xet_metric_query_handle_t )

###############################################################################
## @brief Function-pointer for xetCommandListAppendMetricQueryEnd
if __use_win_types:
    _xetCommandListAppendMetricQueryEnd_t = WINFUNCTYPE( xe_result_t, xet_command_list_handle_t, xet_metric_query_handle_t, xe_event_handle_t )
else:
    _xetCommandListAppendMetricQueryEnd_t = CFUNCTYPE( xe_result_t, xet_command_list_handle_t, xet_metric_query_handle_t, xe_event_handle_t )

###############################################################################
## @brief Function-pointer for xetCommandListAppendMetricMemoryBarrier
if __use_win_types:
    _xetCommandListAppendMetricMemoryBarrier_t = WINFUNCTYPE( xe_result_t, xet_command_list_handle_t )
else:
    _xetCommandListAppendMetricMemoryBarrier_t = CFUNCTYPE( xe_result_t, xet_command_list_handle_t )


###############################################################################
## @brief Table of CommandList functions pointers
class _xet_command_list_dditable_t(Structure):
    _fields_ = [
        ("pfnAppendMetricTracerMarker", c_void_p),                      ## _xetCommandListAppendMetricTracerMarker_t
        ("pfnAppendMetricQueryBegin", c_void_p),                        ## _xetCommandListAppendMetricQueryBegin_t
        ("pfnAppendMetricQueryEnd", c_void_p),                          ## _xetCommandListAppendMetricQueryEnd_t
        ("pfnAppendMetricMemoryBarrier", c_void_p)                      ## _xetCommandListAppendMetricMemoryBarrier_t
    ]

###############################################################################
## @brief Function-pointer for xetModuleGetDebugInfo
if __use_win_types:
    _xetModuleGetDebugInfo_t = WINFUNCTYPE( xe_result_t, xet_module_handle_t, xet_module_debug_info_format_t, POINTER(c_size_t), POINTER(c_ubyte) )
else:
    _xetModuleGetDebugInfo_t = CFUNCTYPE( xe_result_t, xet_module_handle_t, xet_module_debug_info_format_t, POINTER(c_size_t), POINTER(c_ubyte) )

###############################################################################
## @brief Function-pointer for xetModuleGetFunctionNames
if __use_win_types:
    _xetModuleGetFunctionNames_t = WINFUNCTYPE( xe_result_t, xet_module_handle_t, POINTER(c_ulong), POINTER(c_char*) )
else:
    _xetModuleGetFunctionNames_t = CFUNCTYPE( xe_result_t, xet_module_handle_t, POINTER(c_ulong), POINTER(c_char*) )


###############################################################################
## @brief Table of Module functions pointers
class _xet_module_dditable_t(Structure):
    _fields_ = [
        ("pfnGetDebugInfo", c_void_p),                                  ## _xetModuleGetDebugInfo_t
        ("pfnGetFunctionNames", c_void_p)                               ## _xetModuleGetFunctionNames_t
    ]

###############################################################################
## @brief Function-pointer for xetFunctionGetProfileInfo
if __use_win_types:
    _xetFunctionGetProfileInfo_t = WINFUNCTYPE( xe_result_t, xet_function_handle_t, POINTER(xet_profile_info_t) )
else:
    _xetFunctionGetProfileInfo_t = CFUNCTYPE( xe_result_t, xet_function_handle_t, POINTER(xet_profile_info_t) )


###############################################################################
## @brief Table of Function functions pointers
class _xet_function_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProfileInfo", c_void_p)                                 ## _xetFunctionGetProfileInfo_t
    ]

###############################################################################
## @brief Function-pointer for xetMetricGroupGet
if __use_win_types:
    _xetMetricGroupGet_t = WINFUNCTYPE( xe_result_t, xet_device_handle_t, POINTER(c_ulong), POINTER(xet_metric_group_handle_t) )
else:
    _xetMetricGroupGet_t = CFUNCTYPE( xe_result_t, xet_device_handle_t, POINTER(c_ulong), POINTER(xet_metric_group_handle_t) )

###############################################################################
## @brief Function-pointer for xetMetricGroupGetProperties
if __use_win_types:
    _xetMetricGroupGetProperties_t = WINFUNCTYPE( xe_result_t, xet_metric_group_handle_t, POINTER(xet_metric_group_properties_t) )
else:
    _xetMetricGroupGetProperties_t = CFUNCTYPE( xe_result_t, xet_metric_group_handle_t, POINTER(xet_metric_group_properties_t) )

###############################################################################
## @brief Function-pointer for xetMetricGroupCalculateMetricValues
if __use_win_types:
    _xetMetricGroupCalculateMetricValues_t = WINFUNCTYPE( xe_result_t, xet_metric_group_handle_t, c_size_t, POINTER(c_ubyte), POINTER(c_ulong), POINTER(xet_typed_value_t) )
else:
    _xetMetricGroupCalculateMetricValues_t = CFUNCTYPE( xe_result_t, xet_metric_group_handle_t, c_size_t, POINTER(c_ubyte), POINTER(c_ulong), POINTER(xet_typed_value_t) )


###############################################################################
## @brief Table of MetricGroup functions pointers
class _xet_metric_group_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _xetMetricGroupGet_t
        ("pfnGetProperties", c_void_p),                                 ## _xetMetricGroupGetProperties_t
        ("pfnCalculateMetricValues", c_void_p)                          ## _xetMetricGroupCalculateMetricValues_t
    ]

###############################################################################
## @brief Function-pointer for xetMetricGet
if __use_win_types:
    _xetMetricGet_t = WINFUNCTYPE( xe_result_t, xet_metric_group_handle_t, POINTER(c_ulong), POINTER(xet_metric_handle_t) )
else:
    _xetMetricGet_t = CFUNCTYPE( xe_result_t, xet_metric_group_handle_t, POINTER(c_ulong), POINTER(xet_metric_handle_t) )

###############################################################################
## @brief Function-pointer for xetMetricGetProperties
if __use_win_types:
    _xetMetricGetProperties_t = WINFUNCTYPE( xe_result_t, xet_metric_handle_t, POINTER(xet_metric_properties_t) )
else:
    _xetMetricGetProperties_t = CFUNCTYPE( xe_result_t, xet_metric_handle_t, POINTER(xet_metric_properties_t) )


###############################################################################
## @brief Table of Metric functions pointers
class _xet_metric_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _xetMetricGet_t
        ("pfnGetProperties", c_void_p)                                  ## _xetMetricGetProperties_t
    ]

###############################################################################
## @brief Function-pointer for xetMetricTracerOpen
if __use_win_types:
    _xetMetricTracerOpen_t = WINFUNCTYPE( xe_result_t, xet_device_handle_t, xet_metric_group_handle_t, POINTER(xet_metric_tracer_desc_t), xe_event_handle_t, POINTER(xet_metric_tracer_handle_t) )
else:
    _xetMetricTracerOpen_t = CFUNCTYPE( xe_result_t, xet_device_handle_t, xet_metric_group_handle_t, POINTER(xet_metric_tracer_desc_t), xe_event_handle_t, POINTER(xet_metric_tracer_handle_t) )

###############################################################################
## @brief Function-pointer for xetMetricTracerClose
if __use_win_types:
    _xetMetricTracerClose_t = WINFUNCTYPE( xe_result_t, xet_metric_tracer_handle_t )
else:
    _xetMetricTracerClose_t = CFUNCTYPE( xe_result_t, xet_metric_tracer_handle_t )

###############################################################################
## @brief Function-pointer for xetMetricTracerReadData
if __use_win_types:
    _xetMetricTracerReadData_t = WINFUNCTYPE( xe_result_t, xet_metric_tracer_handle_t, c_ulong, POINTER(c_size_t), POINTER(c_ubyte) )
else:
    _xetMetricTracerReadData_t = CFUNCTYPE( xe_result_t, xet_metric_tracer_handle_t, c_ulong, POINTER(c_size_t), POINTER(c_ubyte) )


###############################################################################
## @brief Table of MetricTracer functions pointers
class _xet_metric_tracer_dditable_t(Structure):
    _fields_ = [
        ("pfnOpen", c_void_p),                                          ## _xetMetricTracerOpen_t
        ("pfnClose", c_void_p),                                         ## _xetMetricTracerClose_t
        ("pfnReadData", c_void_p)                                       ## _xetMetricTracerReadData_t
    ]

###############################################################################
## @brief Function-pointer for xetMetricQueryPoolCreate
if __use_win_types:
    _xetMetricQueryPoolCreate_t = WINFUNCTYPE( xe_result_t, xet_device_handle_t, xet_metric_group_handle_t, POINTER(xet_metric_query_pool_desc_t), POINTER(xet_metric_query_pool_handle_t) )
else:
    _xetMetricQueryPoolCreate_t = CFUNCTYPE( xe_result_t, xet_device_handle_t, xet_metric_group_handle_t, POINTER(xet_metric_query_pool_desc_t), POINTER(xet_metric_query_pool_handle_t) )

###############################################################################
## @brief Function-pointer for xetMetricQueryPoolDestroy
if __use_win_types:
    _xetMetricQueryPoolDestroy_t = WINFUNCTYPE( xe_result_t, xet_metric_query_pool_handle_t )
else:
    _xetMetricQueryPoolDestroy_t = CFUNCTYPE( xe_result_t, xet_metric_query_pool_handle_t )


###############################################################################
## @brief Table of MetricQueryPool functions pointers
class _xet_metric_query_pool_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xetMetricQueryPoolCreate_t
        ("pfnDestroy", c_void_p)                                        ## _xetMetricQueryPoolDestroy_t
    ]

###############################################################################
## @brief Function-pointer for xetMetricQueryCreate
if __use_win_types:
    _xetMetricQueryCreate_t = WINFUNCTYPE( xe_result_t, xet_metric_query_pool_handle_t, c_ulong, POINTER(xet_metric_query_handle_t) )
else:
    _xetMetricQueryCreate_t = CFUNCTYPE( xe_result_t, xet_metric_query_pool_handle_t, c_ulong, POINTER(xet_metric_query_handle_t) )

###############################################################################
## @brief Function-pointer for xetMetricQueryDestroy
if __use_win_types:
    _xetMetricQueryDestroy_t = WINFUNCTYPE( xe_result_t, xet_metric_query_handle_t )
else:
    _xetMetricQueryDestroy_t = CFUNCTYPE( xe_result_t, xet_metric_query_handle_t )

###############################################################################
## @brief Function-pointer for xetMetricQueryReset
if __use_win_types:
    _xetMetricQueryReset_t = WINFUNCTYPE( xe_result_t, xet_metric_query_handle_t )
else:
    _xetMetricQueryReset_t = CFUNCTYPE( xe_result_t, xet_metric_query_handle_t )

###############################################################################
## @brief Function-pointer for xetMetricQueryGetData
if __use_win_types:
    _xetMetricQueryGetData_t = WINFUNCTYPE( xe_result_t, xet_metric_query_handle_t, POINTER(c_size_t), POINTER(c_ubyte) )
else:
    _xetMetricQueryGetData_t = CFUNCTYPE( xe_result_t, xet_metric_query_handle_t, POINTER(c_size_t), POINTER(c_ubyte) )


###############################################################################
## @brief Table of MetricQuery functions pointers
class _xet_metric_query_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xetMetricQueryCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xetMetricQueryDestroy_t
        ("pfnReset", c_void_p),                                         ## _xetMetricQueryReset_t
        ("pfnGetData", c_void_p)                                        ## _xetMetricQueryGetData_t
    ]

###############################################################################
## @brief Function-pointer for xetTracerCreate
if __use_win_types:
    _xetTracerCreate_t = WINFUNCTYPE( xe_result_t, xet_device_handle_t, POINTER(xet_tracer_desc_t), POINTER(xet_tracer_handle_t) )
else:
    _xetTracerCreate_t = CFUNCTYPE( xe_result_t, xet_device_handle_t, POINTER(xet_tracer_desc_t), POINTER(xet_tracer_handle_t) )

###############################################################################
## @brief Function-pointer for xetTracerDestroy
if __use_win_types:
    _xetTracerDestroy_t = WINFUNCTYPE( xe_result_t, xet_tracer_handle_t )
else:
    _xetTracerDestroy_t = CFUNCTYPE( xe_result_t, xet_tracer_handle_t )

###############################################################################
## @brief Function-pointer for xetTracerSetPrologues
if __use_win_types:
    _xetTracerSetPrologues_t = WINFUNCTYPE( xe_result_t, xet_tracer_handle_t, POINTER(xet_core_callbacks_t), POINTER(xet_experimental_callbacks_t) )
else:
    _xetTracerSetPrologues_t = CFUNCTYPE( xe_result_t, xet_tracer_handle_t, POINTER(xet_core_callbacks_t), POINTER(xet_experimental_callbacks_t) )

###############################################################################
## @brief Function-pointer for xetTracerSetEpilogues
if __use_win_types:
    _xetTracerSetEpilogues_t = WINFUNCTYPE( xe_result_t, xet_tracer_handle_t, POINTER(xet_core_callbacks_t), POINTER(xet_experimental_callbacks_t) )
else:
    _xetTracerSetEpilogues_t = CFUNCTYPE( xe_result_t, xet_tracer_handle_t, POINTER(xet_core_callbacks_t), POINTER(xet_experimental_callbacks_t) )

###############################################################################
## @brief Function-pointer for xetTracerSetEnabled
if __use_win_types:
    _xetTracerSetEnabled_t = WINFUNCTYPE( xe_result_t, xet_tracer_handle_t, xe_bool_t )
else:
    _xetTracerSetEnabled_t = CFUNCTYPE( xe_result_t, xet_tracer_handle_t, xe_bool_t )


###############################################################################
## @brief Table of Tracer functions pointers
class _xet_tracer_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xetTracerCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xetTracerDestroy_t
        ("pfnSetPrologues", c_void_p),                                  ## _xetTracerSetPrologues_t
        ("pfnSetEpilogues", c_void_p),                                  ## _xetTracerSetEpilogues_t
        ("pfnSetEnabled", c_void_p)                                     ## _xetTracerSetEnabled_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanGet
if __use_win_types:
    _xetSysmanGet_t = WINFUNCTYPE( xe_result_t, xet_device_handle_t, xet_sysman_version_t, POINTER(xet_sysman_handle_t) )
else:
    _xetSysmanGet_t = CFUNCTYPE( xe_result_t, xet_device_handle_t, xet_sysman_version_t, POINTER(xet_sysman_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanDeviceGetProperties
if __use_win_types:
    _xetSysmanDeviceGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_sysman_properties_t) )
else:
    _xetSysmanDeviceGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_sysman_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSchedulerGetCurrentMode
if __use_win_types:
    _xetSysmanSchedulerGetCurrentMode_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_sched_mode_t) )
else:
    _xetSysmanSchedulerGetCurrentMode_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_sched_mode_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSchedulerGetTimeoutModeProperties
if __use_win_types:
    _xetSysmanSchedulerGetTimeoutModeProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, POINTER(xet_sched_timeout_properties_t) )
else:
    _xetSysmanSchedulerGetTimeoutModeProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, POINTER(xet_sched_timeout_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSchedulerGetTimesliceModeProperties
if __use_win_types:
    _xetSysmanSchedulerGetTimesliceModeProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, POINTER(xet_sched_timeslice_properties_t) )
else:
    _xetSysmanSchedulerGetTimesliceModeProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, POINTER(xet_sched_timeslice_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSchedulerSetTimeoutMode
if __use_win_types:
    _xetSysmanSchedulerSetTimeoutMode_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_sched_timeout_properties_t), POINTER(xe_bool_t) )
else:
    _xetSysmanSchedulerSetTimeoutMode_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_sched_timeout_properties_t), POINTER(xe_bool_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSchedulerSetTimesliceMode
if __use_win_types:
    _xetSysmanSchedulerSetTimesliceMode_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_sched_timeslice_properties_t), POINTER(xe_bool_t) )
else:
    _xetSysmanSchedulerSetTimesliceMode_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_sched_timeslice_properties_t), POINTER(xe_bool_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSchedulerSetExclusiveMode
if __use_win_types:
    _xetSysmanSchedulerSetExclusiveMode_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xe_bool_t) )
else:
    _xetSysmanSchedulerSetExclusiveMode_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xe_bool_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSchedulerSetSingleCmdQueueMode
if __use_win_types:
    _xetSysmanSchedulerSetSingleCmdQueueMode_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xe_bool_t) )
else:
    _xetSysmanSchedulerSetSingleCmdQueueMode_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xe_bool_t) )

###############################################################################
## @brief Function-pointer for xetSysmanDeviceReset
if __use_win_types:
    _xetSysmanDeviceReset_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t )
else:
    _xetSysmanDeviceReset_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t )

###############################################################################
## @brief Function-pointer for xetSysmanDeviceWasRepaired
if __use_win_types:
    _xetSysmanDeviceWasRepaired_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xe_bool_t) )
else:
    _xetSysmanDeviceWasRepaired_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xe_bool_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPciGetProperties
if __use_win_types:
    _xetSysmanPciGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_pci_properties_t) )
else:
    _xetSysmanPciGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_pci_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPciGetState
if __use_win_types:
    _xetSysmanPciGetState_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_pci_state_t) )
else:
    _xetSysmanPciGetState_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_pci_state_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPciGetBarProperties
if __use_win_types:
    _xetSysmanPciGetBarProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pci_bar_properties_t) )
else:
    _xetSysmanPciGetBarProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pci_bar_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPciGetThroughput
if __use_win_types:
    _xetSysmanPciGetThroughput_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_pci_throughput_t) )
else:
    _xetSysmanPciGetThroughput_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_pci_throughput_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPciGetStats
if __use_win_types:
    _xetSysmanPciGetStats_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_pci_stats_t) )
else:
    _xetSysmanPciGetStats_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_pci_stats_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPowerGet
if __use_win_types:
    _xetSysmanPowerGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_pwr_handle_t) )
else:
    _xetSysmanPowerGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_pwr_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencyGet
if __use_win_types:
    _xetSysmanFrequencyGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_freq_handle_t) )
else:
    _xetSysmanFrequencyGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_freq_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanEngineGet
if __use_win_types:
    _xetSysmanEngineGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_engine_handle_t) )
else:
    _xetSysmanEngineGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_engine_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanStandbyGet
if __use_win_types:
    _xetSysmanStandbyGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_standby_handle_t) )
else:
    _xetSysmanStandbyGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_standby_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFirmwareGet
if __use_win_types:
    _xetSysmanFirmwareGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_firmware_handle_t) )
else:
    _xetSysmanFirmwareGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_firmware_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanMemoryGet
if __use_win_types:
    _xetSysmanMemoryGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_mem_handle_t) )
else:
    _xetSysmanMemoryGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_mem_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanLinkSwitchGet
if __use_win_types:
    _xetSysmanLinkSwitchGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_link_switch_handle_t) )
else:
    _xetSysmanLinkSwitchGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_link_switch_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanTemperatureGet
if __use_win_types:
    _xetSysmanTemperatureGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_temp_handle_t) )
else:
    _xetSysmanTemperatureGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_temp_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPsuGet
if __use_win_types:
    _xetSysmanPsuGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_psu_handle_t) )
else:
    _xetSysmanPsuGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_psu_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFanGet
if __use_win_types:
    _xetSysmanFanGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_fan_handle_t) )
else:
    _xetSysmanFanGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_fan_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanLedGet
if __use_win_types:
    _xetSysmanLedGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_led_handle_t) )
else:
    _xetSysmanLedGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_led_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanRasGet
if __use_win_types:
    _xetSysmanRasGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_ras_handle_t) )
else:
    _xetSysmanRasGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_ras_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanEventsGetProperties
if __use_win_types:
    _xetSysmanEventsGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_event_properties_t) )
else:
    _xetSysmanEventsGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_event_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanEventsRegister
if __use_win_types:
    _xetSysmanEventsRegister_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_event_request_t) )
else:
    _xetSysmanEventsRegister_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_event_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanEventsUnregister
if __use_win_types:
    _xetSysmanEventsUnregister_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_event_request_t) )
else:
    _xetSysmanEventsUnregister_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_event_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanEventsListen
if __use_win_types:
    _xetSysmanEventsListen_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, c_ulong, POINTER(c_ulong) )
else:
    _xetSysmanEventsListen_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, c_ulong, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanDiagnosticsGet
if __use_win_types:
    _xetSysmanDiagnosticsGet_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_diag_handle_t) )
else:
    _xetSysmanDiagnosticsGet_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(c_ulong), POINTER(xet_sysman_diag_handle_t) )


###############################################################################
## @brief Table of Sysman functions pointers
class _xet_sysman_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _xetSysmanGet_t
        ("pfnDeviceGetProperties", c_void_p),                           ## _xetSysmanDeviceGetProperties_t
        ("pfnSchedulerGetCurrentMode", c_void_p),                       ## _xetSysmanSchedulerGetCurrentMode_t
        ("pfnSchedulerGetTimeoutModeProperties", c_void_p),             ## _xetSysmanSchedulerGetTimeoutModeProperties_t
        ("pfnSchedulerGetTimesliceModeProperties", c_void_p),           ## _xetSysmanSchedulerGetTimesliceModeProperties_t
        ("pfnSchedulerSetTimeoutMode", c_void_p),                       ## _xetSysmanSchedulerSetTimeoutMode_t
        ("pfnSchedulerSetTimesliceMode", c_void_p),                     ## _xetSysmanSchedulerSetTimesliceMode_t
        ("pfnSchedulerSetExclusiveMode", c_void_p),                     ## _xetSysmanSchedulerSetExclusiveMode_t
        ("pfnSchedulerSetSingleCmdQueueMode", c_void_p),                ## _xetSysmanSchedulerSetSingleCmdQueueMode_t
        ("pfnDeviceReset", c_void_p),                                   ## _xetSysmanDeviceReset_t
        ("pfnDeviceWasRepaired", c_void_p),                             ## _xetSysmanDeviceWasRepaired_t
        ("pfnPciGetProperties", c_void_p),                              ## _xetSysmanPciGetProperties_t
        ("pfnPciGetState", c_void_p),                                   ## _xetSysmanPciGetState_t
        ("pfnPciGetBarProperties", c_void_p),                           ## _xetSysmanPciGetBarProperties_t
        ("pfnPciGetThroughput", c_void_p),                              ## _xetSysmanPciGetThroughput_t
        ("pfnPciGetStats", c_void_p),                                   ## _xetSysmanPciGetStats_t
        ("pfnPowerGet", c_void_p),                                      ## _xetSysmanPowerGet_t
        ("pfnFrequencyGet", c_void_p),                                  ## _xetSysmanFrequencyGet_t
        ("pfnEngineGet", c_void_p),                                     ## _xetSysmanEngineGet_t
        ("pfnStandbyGet", c_void_p),                                    ## _xetSysmanStandbyGet_t
        ("pfnFirmwareGet", c_void_p),                                   ## _xetSysmanFirmwareGet_t
        ("pfnMemoryGet", c_void_p),                                     ## _xetSysmanMemoryGet_t
        ("pfnLinkSwitchGet", c_void_p),                                 ## _xetSysmanLinkSwitchGet_t
        ("pfnTemperatureGet", c_void_p),                                ## _xetSysmanTemperatureGet_t
        ("pfnPsuGet", c_void_p),                                        ## _xetSysmanPsuGet_t
        ("pfnFanGet", c_void_p),                                        ## _xetSysmanFanGet_t
        ("pfnLedGet", c_void_p),                                        ## _xetSysmanLedGet_t
        ("pfnRasGet", c_void_p),                                        ## _xetSysmanRasGet_t
        ("pfnEventsGetProperties", c_void_p),                           ## _xetSysmanEventsGetProperties_t
        ("pfnEventsRegister", c_void_p),                                ## _xetSysmanEventsRegister_t
        ("pfnEventsUnregister", c_void_p),                              ## _xetSysmanEventsUnregister_t
        ("pfnEventsListen", c_void_p),                                  ## _xetSysmanEventsListen_t
        ("pfnDiagnosticsGet", c_void_p)                                 ## _xetSysmanDiagnosticsGet_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanPowerGetProperties
if __use_win_types:
    _xetSysmanPowerGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_properties_t) )
else:
    _xetSysmanPowerGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPowerGetEnergyCounter
if __use_win_types:
    _xetSysmanPowerGetEnergyCounter_t = WINFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_energy_counter_t) )
else:
    _xetSysmanPowerGetEnergyCounter_t = CFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_energy_counter_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPowerGetEnergyThreshold
if __use_win_types:
    _xetSysmanPowerGetEnergyThreshold_t = WINFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_energy_threshold_t) )
else:
    _xetSysmanPowerGetEnergyThreshold_t = CFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_energy_threshold_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPowerSetEnergyThreshold
if __use_win_types:
    _xetSysmanPowerSetEnergyThreshold_t = WINFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_energy_threshold_t) )
else:
    _xetSysmanPowerSetEnergyThreshold_t = CFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_energy_threshold_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPowerGetLimits
if __use_win_types:
    _xetSysmanPowerGetLimits_t = WINFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_sustained_limit_t), POINTER(xet_power_burst_limit_t), POINTER(xet_power_peak_limit_t) )
else:
    _xetSysmanPowerGetLimits_t = CFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_sustained_limit_t), POINTER(xet_power_burst_limit_t), POINTER(xet_power_peak_limit_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPowerSetLimits
if __use_win_types:
    _xetSysmanPowerSetLimits_t = WINFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_sustained_limit_t), POINTER(xet_power_burst_limit_t), POINTER(xet_power_peak_limit_t) )
else:
    _xetSysmanPowerSetLimits_t = CFUNCTYPE( xe_result_t, xet_sysman_pwr_handle_t, POINTER(xet_power_sustained_limit_t), POINTER(xet_power_burst_limit_t), POINTER(xet_power_peak_limit_t) )


###############################################################################
## @brief Table of SysmanPower functions pointers
class _xet_sysman_power_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanPowerGetProperties_t
        ("pfnGetEnergyCounter", c_void_p),                              ## _xetSysmanPowerGetEnergyCounter_t
        ("pfnGetEnergyThreshold", c_void_p),                            ## _xetSysmanPowerGetEnergyThreshold_t
        ("pfnSetEnergyThreshold", c_void_p),                            ## _xetSysmanPowerSetEnergyThreshold_t
        ("pfnGetLimits", c_void_p),                                     ## _xetSysmanPowerGetLimits_t
        ("pfnSetLimits", c_void_p)                                      ## _xetSysmanPowerSetLimits_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanFrequencySetFanSpeed
if __use_win_types:
    _xetSysmanFrequencySetFanSpeed_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_oc_fan_control_t) )
else:
    _xetSysmanFrequencySetFanSpeed_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_oc_fan_control_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencyGetOcCapabilities
if __use_win_types:
    _xetSysmanFrequencyGetOcCapabilities_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_oc_capabilities_t) )
else:
    _xetSysmanFrequencyGetOcCapabilities_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_oc_capabilities_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencyGetOcVrTopology
if __use_win_types:
    _xetSysmanFrequencyGetOcVrTopology_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_oc_vr_topology) )
else:
    _xetSysmanFrequencyGetOcVrTopology_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_oc_vr_topology) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencyGetOcOverrideProperties
if __use_win_types:
    _xetSysmanFrequencyGetOcOverrideProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_oc_settings_override_t) )
else:
    _xetSysmanFrequencyGetOcOverrideProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_oc_settings_override_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencyGetOcIccMax
if __use_win_types:
    _xetSysmanFrequencyGetOcIccMax_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(c_ulong) )
else:
    _xetSysmanFrequencyGetOcIccMax_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencyGetOcTjMax
if __use_win_types:
    _xetSysmanFrequencyGetOcTjMax_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(c_ulong) )
else:
    _xetSysmanFrequencyGetOcTjMax_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencySetOcOverrideProperties
if __use_win_types:
    _xetSysmanFrequencySetOcOverrideProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_oc_settings_override_t) )
else:
    _xetSysmanFrequencySetOcOverrideProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_oc_settings_override_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencySetOcIccMax
if __use_win_types:
    _xetSysmanFrequencySetOcIccMax_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(c_ulong) )
else:
    _xetSysmanFrequencySetOcIccMax_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencySetOcTjMax
if __use_win_types:
    _xetSysmanFrequencySetOcTjMax_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(c_ulong) )
else:
    _xetSysmanFrequencySetOcTjMax_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencyGetProperties
if __use_win_types:
    _xetSysmanFrequencyGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_freq_properties_t) )
else:
    _xetSysmanFrequencyGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_freq_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencyGetRange
if __use_win_types:
    _xetSysmanFrequencyGetRange_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_freq_range_t) )
else:
    _xetSysmanFrequencyGetRange_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_freq_range_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencySetRange
if __use_win_types:
    _xetSysmanFrequencySetRange_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_freq_range_t) )
else:
    _xetSysmanFrequencySetRange_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_freq_range_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencyGetState
if __use_win_types:
    _xetSysmanFrequencyGetState_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_freq_state_t) )
else:
    _xetSysmanFrequencyGetState_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_freq_state_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFrequencyGetThrottleTime
if __use_win_types:
    _xetSysmanFrequencyGetThrottleTime_t = WINFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_freq_throttle_time_t) )
else:
    _xetSysmanFrequencyGetThrottleTime_t = CFUNCTYPE( xe_result_t, xet_sysman_freq_handle_t, POINTER(xet_freq_throttle_time_t) )


###############################################################################
## @brief Table of SysmanFrequency functions pointers
class _xet_sysman_frequency_dditable_t(Structure):
    _fields_ = [
        ("pfnSetFanSpeed", c_void_p),                                   ## _xetSysmanFrequencySetFanSpeed_t
        ("pfnGetOcCapabilities", c_void_p),                             ## _xetSysmanFrequencyGetOcCapabilities_t
        ("pfnGetOcVrTopology", c_void_p),                               ## _xetSysmanFrequencyGetOcVrTopology_t
        ("pfnGetOcOverrideProperties", c_void_p),                       ## _xetSysmanFrequencyGetOcOverrideProperties_t
        ("pfnGetOcIccMax", c_void_p),                                   ## _xetSysmanFrequencyGetOcIccMax_t
        ("pfnGetOcTjMax", c_void_p),                                    ## _xetSysmanFrequencyGetOcTjMax_t
        ("pfnSetOcOverrideProperties", c_void_p),                       ## _xetSysmanFrequencySetOcOverrideProperties_t
        ("pfnSetOcIccMax", c_void_p),                                   ## _xetSysmanFrequencySetOcIccMax_t
        ("pfnSetOcTjMax", c_void_p),                                    ## _xetSysmanFrequencySetOcTjMax_t
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanFrequencyGetProperties_t
        ("pfnGetRange", c_void_p),                                      ## _xetSysmanFrequencyGetRange_t
        ("pfnSetRange", c_void_p),                                      ## _xetSysmanFrequencySetRange_t
        ("pfnGetState", c_void_p),                                      ## _xetSysmanFrequencyGetState_t
        ("pfnGetThrottleTime", c_void_p)                                ## _xetSysmanFrequencyGetThrottleTime_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanEngineGetProperties
if __use_win_types:
    _xetSysmanEngineGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_engine_handle_t, POINTER(xet_engine_properties_t) )
else:
    _xetSysmanEngineGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_engine_handle_t, POINTER(xet_engine_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanEngineGetActivity
if __use_win_types:
    _xetSysmanEngineGetActivity_t = WINFUNCTYPE( xe_result_t, xet_sysman_engine_handle_t, POINTER(xet_engine_stats_t) )
else:
    _xetSysmanEngineGetActivity_t = CFUNCTYPE( xe_result_t, xet_sysman_engine_handle_t, POINTER(xet_engine_stats_t) )


###############################################################################
## @brief Table of SysmanEngine functions pointers
class _xet_sysman_engine_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanEngineGetProperties_t
        ("pfnGetActivity", c_void_p)                                    ## _xetSysmanEngineGetActivity_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanStandbyGetProperties
if __use_win_types:
    _xetSysmanStandbyGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_standby_handle_t, POINTER(xet_standby_properties_t) )
else:
    _xetSysmanStandbyGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_standby_handle_t, POINTER(xet_standby_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanStandbyGetMode
if __use_win_types:
    _xetSysmanStandbyGetMode_t = WINFUNCTYPE( xe_result_t, xet_sysman_standby_handle_t, POINTER(xet_standby_promo_mode_t) )
else:
    _xetSysmanStandbyGetMode_t = CFUNCTYPE( xe_result_t, xet_sysman_standby_handle_t, POINTER(xet_standby_promo_mode_t) )

###############################################################################
## @brief Function-pointer for xetSysmanStandbySetMode
if __use_win_types:
    _xetSysmanStandbySetMode_t = WINFUNCTYPE( xe_result_t, xet_sysman_standby_handle_t, xet_standby_promo_mode_t )
else:
    _xetSysmanStandbySetMode_t = CFUNCTYPE( xe_result_t, xet_sysman_standby_handle_t, xet_standby_promo_mode_t )


###############################################################################
## @brief Table of SysmanStandby functions pointers
class _xet_sysman_standby_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanStandbyGetProperties_t
        ("pfnGetMode", c_void_p),                                       ## _xetSysmanStandbyGetMode_t
        ("pfnSetMode", c_void_p)                                        ## _xetSysmanStandbySetMode_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanFirmwareGetProperties
if __use_win_types:
    _xetSysmanFirmwareGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_firmware_handle_t, POINTER(xet_firmware_properties_t) )
else:
    _xetSysmanFirmwareGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_firmware_handle_t, POINTER(xet_firmware_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFirmwareGetChecksum
if __use_win_types:
    _xetSysmanFirmwareGetChecksum_t = WINFUNCTYPE( xe_result_t, xet_sysman_firmware_handle_t, POINTER(c_ulong) )
else:
    _xetSysmanFirmwareGetChecksum_t = CFUNCTYPE( xe_result_t, xet_sysman_firmware_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanFirmwareFlash
if __use_win_types:
    _xetSysmanFirmwareFlash_t = WINFUNCTYPE( xe_result_t, xet_sysman_firmware_handle_t, c_void_p, c_ulong )
else:
    _xetSysmanFirmwareFlash_t = CFUNCTYPE( xe_result_t, xet_sysman_firmware_handle_t, c_void_p, c_ulong )


###############################################################################
## @brief Table of SysmanFirmware functions pointers
class _xet_sysman_firmware_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanFirmwareGetProperties_t
        ("pfnGetChecksum", c_void_p),                                   ## _xetSysmanFirmwareGetChecksum_t
        ("pfnFlash", c_void_p)                                          ## _xetSysmanFirmwareFlash_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanMemoryGetProperties
if __use_win_types:
    _xetSysmanMemoryGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_mem_handle_t, POINTER(xet_mem_properties_t) )
else:
    _xetSysmanMemoryGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_mem_handle_t, POINTER(xet_mem_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanMemoryGetBandwidth
if __use_win_types:
    _xetSysmanMemoryGetBandwidth_t = WINFUNCTYPE( xe_result_t, xet_sysman_mem_handle_t, POINTER(xet_mem_bandwidth_t) )
else:
    _xetSysmanMemoryGetBandwidth_t = CFUNCTYPE( xe_result_t, xet_sysman_mem_handle_t, POINTER(xet_mem_bandwidth_t) )

###############################################################################
## @brief Function-pointer for xetSysmanMemoryGetAllocated
if __use_win_types:
    _xetSysmanMemoryGetAllocated_t = WINFUNCTYPE( xe_result_t, xet_sysman_mem_handle_t, POINTER(xet_mem_alloc_t) )
else:
    _xetSysmanMemoryGetAllocated_t = CFUNCTYPE( xe_result_t, xet_sysman_mem_handle_t, POINTER(xet_mem_alloc_t) )


###############################################################################
## @brief Table of SysmanMemory functions pointers
class _xet_sysman_memory_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanMemoryGetProperties_t
        ("pfnGetBandwidth", c_void_p),                                  ## _xetSysmanMemoryGetBandwidth_t
        ("pfnGetAllocated", c_void_p)                                   ## _xetSysmanMemoryGetAllocated_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanLinkSwitchGetProperties
if __use_win_types:
    _xetSysmanLinkSwitchGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_link_switch_handle_t, POINTER(xet_link_switch_properties_t) )
else:
    _xetSysmanLinkSwitchGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_link_switch_handle_t, POINTER(xet_link_switch_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanLinkSwitchGetState
if __use_win_types:
    _xetSysmanLinkSwitchGetState_t = WINFUNCTYPE( xe_result_t, xet_sysman_link_switch_handle_t, POINTER(xet_link_switch_state_t) )
else:
    _xetSysmanLinkSwitchGetState_t = CFUNCTYPE( xe_result_t, xet_sysman_link_switch_handle_t, POINTER(xet_link_switch_state_t) )

###############################################################################
## @brief Function-pointer for xetSysmanLinkSwitchSetState
if __use_win_types:
    _xetSysmanLinkSwitchSetState_t = WINFUNCTYPE( xe_result_t, xet_sysman_link_switch_handle_t, xe_bool_t )
else:
    _xetSysmanLinkSwitchSetState_t = CFUNCTYPE( xe_result_t, xet_sysman_link_switch_handle_t, xe_bool_t )

###############################################################################
## @brief Function-pointer for xetSysmanLinkSwitchGetPorts
if __use_win_types:
    _xetSysmanLinkSwitchGetPorts_t = WINFUNCTYPE( xe_result_t, xet_sysman_link_switch_handle_t, POINTER(c_ulong), POINTER(xet_sysman_link_port_handle_t) )
else:
    _xetSysmanLinkSwitchGetPorts_t = CFUNCTYPE( xe_result_t, xet_sysman_link_switch_handle_t, POINTER(c_ulong), POINTER(xet_sysman_link_port_handle_t) )


###############################################################################
## @brief Table of SysmanLinkSwitch functions pointers
class _xet_sysman_link_switch_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanLinkSwitchGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _xetSysmanLinkSwitchGetState_t
        ("pfnSetState", c_void_p),                                      ## _xetSysmanLinkSwitchSetState_t
        ("pfnGetPorts", c_void_p)                                       ## _xetSysmanLinkSwitchGetPorts_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanLinkPortGetProperties
if __use_win_types:
    _xetSysmanLinkPortGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_link_port_handle_t, POINTER(xet_link_port_properties_t) )
else:
    _xetSysmanLinkPortGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_link_port_handle_t, POINTER(xet_link_port_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanLinkPortGetState
if __use_win_types:
    _xetSysmanLinkPortGetState_t = WINFUNCTYPE( xe_result_t, xet_sysman_link_port_handle_t, POINTER(xet_link_port_state_t) )
else:
    _xetSysmanLinkPortGetState_t = CFUNCTYPE( xe_result_t, xet_sysman_link_port_handle_t, POINTER(xet_link_port_state_t) )

###############################################################################
## @brief Function-pointer for xetSysmanLinkPortGetThroughput
if __use_win_types:
    _xetSysmanLinkPortGetThroughput_t = WINFUNCTYPE( xe_result_t, xet_sysman_link_port_handle_t, POINTER(xet_link_port_throughput_t) )
else:
    _xetSysmanLinkPortGetThroughput_t = CFUNCTYPE( xe_result_t, xet_sysman_link_port_handle_t, POINTER(xet_link_port_throughput_t) )

###############################################################################
## @brief Function-pointer for xetSysmanLinkPortGetStats
if __use_win_types:
    _xetSysmanLinkPortGetStats_t = WINFUNCTYPE( xe_result_t, xet_sysman_link_port_handle_t, POINTER(xet_link_port_stats_t) )
else:
    _xetSysmanLinkPortGetStats_t = CFUNCTYPE( xe_result_t, xet_sysman_link_port_handle_t, POINTER(xet_link_port_stats_t) )

###############################################################################
## @brief Function-pointer for xetSysmanLinkPortIsConnected
if __use_win_types:
    _xetSysmanLinkPortIsConnected_t = WINFUNCTYPE( xe_result_t, xet_sysman_link_port_handle_t, xet_sysman_link_port_handle_t, POINTER(xe_bool_t) )
else:
    _xetSysmanLinkPortIsConnected_t = CFUNCTYPE( xe_result_t, xet_sysman_link_port_handle_t, xet_sysman_link_port_handle_t, POINTER(xe_bool_t) )


###############################################################################
## @brief Table of SysmanLinkPort functions pointers
class _xet_sysman_link_port_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanLinkPortGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _xetSysmanLinkPortGetState_t
        ("pfnGetThroughput", c_void_p),                                 ## _xetSysmanLinkPortGetThroughput_t
        ("pfnGetStats", c_void_p),                                      ## _xetSysmanLinkPortGetStats_t
        ("pfnIsConnected", c_void_p)                                    ## _xetSysmanLinkPortIsConnected_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanTemperatureGetProperties
if __use_win_types:
    _xetSysmanTemperatureGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_temp_handle_t, POINTER(xet_temp_properties_t) )
else:
    _xetSysmanTemperatureGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_temp_handle_t, POINTER(xet_temp_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanTemperatureRead
if __use_win_types:
    _xetSysmanTemperatureRead_t = WINFUNCTYPE( xe_result_t, xet_sysman_temp_handle_t, POINTER(c_ulong) )
else:
    _xetSysmanTemperatureRead_t = CFUNCTYPE( xe_result_t, xet_sysman_temp_handle_t, POINTER(c_ulong) )


###############################################################################
## @brief Table of SysmanTemperature functions pointers
class _xet_sysman_temperature_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanTemperatureGetProperties_t
        ("pfnRead", c_void_p)                                           ## _xetSysmanTemperatureRead_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanPsuGetProperties
if __use_win_types:
    _xetSysmanPsuGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_psu_handle_t, POINTER(xet_psu_properties_t) )
else:
    _xetSysmanPsuGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_psu_handle_t, POINTER(xet_psu_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanPsuGetState
if __use_win_types:
    _xetSysmanPsuGetState_t = WINFUNCTYPE( xe_result_t, xet_sysman_psu_handle_t, POINTER(xet_psu_state_t) )
else:
    _xetSysmanPsuGetState_t = CFUNCTYPE( xe_result_t, xet_sysman_psu_handle_t, POINTER(xet_psu_state_t) )


###############################################################################
## @brief Table of SysmanPsu functions pointers
class _xet_sysman_psu_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanPsuGetProperties_t
        ("pfnGetState", c_void_p)                                       ## _xetSysmanPsuGetState_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanFanGetProperties
if __use_win_types:
    _xetSysmanFanGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_fan_handle_t, POINTER(xet_fan_properties_t) )
else:
    _xetSysmanFanGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_fan_handle_t, POINTER(xet_fan_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFanGetConfig
if __use_win_types:
    _xetSysmanFanGetConfig_t = WINFUNCTYPE( xe_result_t, xet_sysman_fan_handle_t, POINTER(xet_fan_config_t) )
else:
    _xetSysmanFanGetConfig_t = CFUNCTYPE( xe_result_t, xet_sysman_fan_handle_t, POINTER(xet_fan_config_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFanSetConfig
if __use_win_types:
    _xetSysmanFanSetConfig_t = WINFUNCTYPE( xe_result_t, xet_sysman_fan_handle_t, POINTER(xet_fan_config_t) )
else:
    _xetSysmanFanSetConfig_t = CFUNCTYPE( xe_result_t, xet_sysman_fan_handle_t, POINTER(xet_fan_config_t) )

###############################################################################
## @brief Function-pointer for xetSysmanFanGetState
if __use_win_types:
    _xetSysmanFanGetState_t = WINFUNCTYPE( xe_result_t, xet_sysman_fan_handle_t, xet_fan_speed_units_t, POINTER(xet_fan_state_t) )
else:
    _xetSysmanFanGetState_t = CFUNCTYPE( xe_result_t, xet_sysman_fan_handle_t, xet_fan_speed_units_t, POINTER(xet_fan_state_t) )


###############################################################################
## @brief Table of SysmanFan functions pointers
class _xet_sysman_fan_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanFanGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _xetSysmanFanGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _xetSysmanFanSetConfig_t
        ("pfnGetState", c_void_p)                                       ## _xetSysmanFanGetState_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanLedGetProperties
if __use_win_types:
    _xetSysmanLedGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_led_handle_t, POINTER(xet_led_properties_t) )
else:
    _xetSysmanLedGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_led_handle_t, POINTER(xet_led_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanLedGetState
if __use_win_types:
    _xetSysmanLedGetState_t = WINFUNCTYPE( xe_result_t, xet_sysman_led_handle_t, POINTER(xet_led_state_t) )
else:
    _xetSysmanLedGetState_t = CFUNCTYPE( xe_result_t, xet_sysman_led_handle_t, POINTER(xet_led_state_t) )

###############################################################################
## @brief Function-pointer for xetSysmanLedSetState
if __use_win_types:
    _xetSysmanLedSetState_t = WINFUNCTYPE( xe_result_t, xet_sysman_led_handle_t, POINTER(xet_led_state_t) )
else:
    _xetSysmanLedSetState_t = CFUNCTYPE( xe_result_t, xet_sysman_led_handle_t, POINTER(xet_led_state_t) )


###############################################################################
## @brief Table of SysmanLed functions pointers
class _xet_sysman_led_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanLedGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _xetSysmanLedGetState_t
        ("pfnSetState", c_void_p)                                       ## _xetSysmanLedSetState_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanRasGetProperties
if __use_win_types:
    _xetSysmanRasGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_ras_handle_t, POINTER(xet_ras_properties_t) )
else:
    _xetSysmanRasGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_ras_handle_t, POINTER(xet_ras_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanRasGetErrors
if __use_win_types:
    _xetSysmanRasGetErrors_t = WINFUNCTYPE( xe_result_t, xet_sysman_ras_handle_t, xe_bool_t, POINTER(c_ulonglong), POINTER(xet_ras_details_t) )
else:
    _xetSysmanRasGetErrors_t = CFUNCTYPE( xe_result_t, xet_sysman_ras_handle_t, xe_bool_t, POINTER(c_ulonglong), POINTER(xet_ras_details_t) )


###############################################################################
## @brief Table of SysmanRas functions pointers
class _xet_sysman_ras_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanRasGetProperties_t
        ("pfnGetErrors", c_void_p)                                      ## _xetSysmanRasGetErrors_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanDiagnosticsGetProperties
if __use_win_types:
    _xetSysmanDiagnosticsGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_diag_handle_t, POINTER(xet_diag_properties_t) )
else:
    _xetSysmanDiagnosticsGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_diag_handle_t, POINTER(xet_diag_properties_t) )

###############################################################################
## @brief Function-pointer for xetSysmanDiagnosticsRunTests
if __use_win_types:
    _xetSysmanDiagnosticsRunTests_t = WINFUNCTYPE( xe_result_t, xet_sysman_diag_handle_t, c_ulong, c_ulong, POINTER(xet_diag_result_t) )
else:
    _xetSysmanDiagnosticsRunTests_t = CFUNCTYPE( xe_result_t, xet_sysman_diag_handle_t, c_ulong, c_ulong, POINTER(xet_diag_result_t) )


###############################################################################
## @brief Table of SysmanDiagnostics functions pointers
class _xet_sysman_diagnostics_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanDiagnosticsGetProperties_t
        ("pfnRunTests", c_void_p)                                       ## _xetSysmanDiagnosticsRunTests_t
    ]

###############################################################################
class _xet_dditable_t(Structure):
    _fields_ = [
        ("Global", _xet_global_dditable_t),
        ("Device", _xet_device_dditable_t),
        ("CommandList", _xet_command_list_dditable_t),
        ("Module", _xet_module_dditable_t),
        ("Function", _xet_function_dditable_t),
        ("MetricGroup", _xet_metric_group_dditable_t),
        ("Metric", _xet_metric_dditable_t),
        ("MetricTracer", _xet_metric_tracer_dditable_t),
        ("MetricQueryPool", _xet_metric_query_pool_dditable_t),
        ("MetricQuery", _xet_metric_query_dditable_t),
        ("Tracer", _xet_tracer_dditable_t),
        ("Sysman", _xet_sysman_dditable_t),
        ("SysmanPower", _xet_sysman_power_dditable_t),
        ("SysmanFrequency", _xet_sysman_frequency_dditable_t),
        ("SysmanEngine", _xet_sysman_engine_dditable_t),
        ("SysmanStandby", _xet_sysman_standby_dditable_t),
        ("SysmanFirmware", _xet_sysman_firmware_dditable_t),
        ("SysmanMemory", _xet_sysman_memory_dditable_t),
        ("SysmanLinkSwitch", _xet_sysman_link_switch_dditable_t),
        ("SysmanLinkPort", _xet_sysman_link_port_dditable_t),
        ("SysmanTemperature", _xet_sysman_temperature_dditable_t),
        ("SysmanPsu", _xet_sysman_psu_dditable_t),
        ("SysmanFan", _xet_sysman_fan_dditable_t),
        ("SysmanLed", _xet_sysman_led_dditable_t),
        ("SysmanRas", _xet_sysman_ras_dditable_t),
        ("SysmanDiagnostics", _xet_sysman_diagnostics_dditable_t)
    ]

###############################################################################
## @brief xet device-driver interfaces
class XET_DDI:
    def __init__(self, version : xe_api_version_t):
        # load the xe_loader library
        if "Windows" == platform.uname()[0]:
            self.__dll = WinDLL("xe_loader.dll")
        else:
            self.__dll = CDLL("xe_loader.so")

        # fill the ddi tables
        self.__dditable = _xet_dditable_t()

        # call driver to get function pointers
        _Global = _xet_global_dditable_t()
        r = xe_result_v(self.__dll.xetGetGlobalProcAddrTable(version, byref(_Global)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Global = _Global

        # attach function interface to function address
        self.xetInit = _xetInit_t(self.__dditable.Global.pfnInit)

        # call driver to get function pointers
        _Device = _xet_device_dditable_t()
        r = xe_result_v(self.__dll.xetGetDeviceProcAddrTable(version, byref(_Device)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Device = _Device

        # attach function interface to function address
        self.xetDeviceActivateMetricGroups = _xetDeviceActivateMetricGroups_t(self.__dditable.Device.pfnActivateMetricGroups)

        # call driver to get function pointers
        _CommandList = _xet_command_list_dditable_t()
        r = xe_result_v(self.__dll.xetGetCommandListProcAddrTable(version, byref(_CommandList)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.CommandList = _CommandList

        # attach function interface to function address
        self.xetCommandListAppendMetricTracerMarker = _xetCommandListAppendMetricTracerMarker_t(self.__dditable.CommandList.pfnAppendMetricTracerMarker)
        self.xetCommandListAppendMetricQueryBegin = _xetCommandListAppendMetricQueryBegin_t(self.__dditable.CommandList.pfnAppendMetricQueryBegin)
        self.xetCommandListAppendMetricQueryEnd = _xetCommandListAppendMetricQueryEnd_t(self.__dditable.CommandList.pfnAppendMetricQueryEnd)
        self.xetCommandListAppendMetricMemoryBarrier = _xetCommandListAppendMetricMemoryBarrier_t(self.__dditable.CommandList.pfnAppendMetricMemoryBarrier)

        # call driver to get function pointers
        _Module = _xet_module_dditable_t()
        r = xe_result_v(self.__dll.xetGetModuleProcAddrTable(version, byref(_Module)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Module = _Module

        # attach function interface to function address
        self.xetModuleGetDebugInfo = _xetModuleGetDebugInfo_t(self.__dditable.Module.pfnGetDebugInfo)
        self.xetModuleGetFunctionNames = _xetModuleGetFunctionNames_t(self.__dditable.Module.pfnGetFunctionNames)

        # call driver to get function pointers
        _Function = _xet_function_dditable_t()
        r = xe_result_v(self.__dll.xetGetFunctionProcAddrTable(version, byref(_Function)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Function = _Function

        # attach function interface to function address
        self.xetFunctionGetProfileInfo = _xetFunctionGetProfileInfo_t(self.__dditable.Function.pfnGetProfileInfo)

        # call driver to get function pointers
        _MetricGroup = _xet_metric_group_dditable_t()
        r = xe_result_v(self.__dll.xetGetMetricGroupProcAddrTable(version, byref(_MetricGroup)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.MetricGroup = _MetricGroup

        # attach function interface to function address
        self.xetMetricGroupGet = _xetMetricGroupGet_t(self.__dditable.MetricGroup.pfnGet)
        self.xetMetricGroupGetProperties = _xetMetricGroupGetProperties_t(self.__dditable.MetricGroup.pfnGetProperties)
        self.xetMetricGroupCalculateMetricValues = _xetMetricGroupCalculateMetricValues_t(self.__dditable.MetricGroup.pfnCalculateMetricValues)

        # call driver to get function pointers
        _Metric = _xet_metric_dditable_t()
        r = xe_result_v(self.__dll.xetGetMetricProcAddrTable(version, byref(_Metric)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Metric = _Metric

        # attach function interface to function address
        self.xetMetricGet = _xetMetricGet_t(self.__dditable.Metric.pfnGet)
        self.xetMetricGetProperties = _xetMetricGetProperties_t(self.__dditable.Metric.pfnGetProperties)

        # call driver to get function pointers
        _MetricTracer = _xet_metric_tracer_dditable_t()
        r = xe_result_v(self.__dll.xetGetMetricTracerProcAddrTable(version, byref(_MetricTracer)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.MetricTracer = _MetricTracer

        # attach function interface to function address
        self.xetMetricTracerOpen = _xetMetricTracerOpen_t(self.__dditable.MetricTracer.pfnOpen)
        self.xetMetricTracerClose = _xetMetricTracerClose_t(self.__dditable.MetricTracer.pfnClose)
        self.xetMetricTracerReadData = _xetMetricTracerReadData_t(self.__dditable.MetricTracer.pfnReadData)

        # call driver to get function pointers
        _MetricQueryPool = _xet_metric_query_pool_dditable_t()
        r = xe_result_v(self.__dll.xetGetMetricQueryPoolProcAddrTable(version, byref(_MetricQueryPool)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.MetricQueryPool = _MetricQueryPool

        # attach function interface to function address
        self.xetMetricQueryPoolCreate = _xetMetricQueryPoolCreate_t(self.__dditable.MetricQueryPool.pfnCreate)
        self.xetMetricQueryPoolDestroy = _xetMetricQueryPoolDestroy_t(self.__dditable.MetricQueryPool.pfnDestroy)

        # call driver to get function pointers
        _MetricQuery = _xet_metric_query_dditable_t()
        r = xe_result_v(self.__dll.xetGetMetricQueryProcAddrTable(version, byref(_MetricQuery)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.MetricQuery = _MetricQuery

        # attach function interface to function address
        self.xetMetricQueryCreate = _xetMetricQueryCreate_t(self.__dditable.MetricQuery.pfnCreate)
        self.xetMetricQueryDestroy = _xetMetricQueryDestroy_t(self.__dditable.MetricQuery.pfnDestroy)
        self.xetMetricQueryReset = _xetMetricQueryReset_t(self.__dditable.MetricQuery.pfnReset)
        self.xetMetricQueryGetData = _xetMetricQueryGetData_t(self.__dditable.MetricQuery.pfnGetData)

        # call driver to get function pointers
        _Tracer = _xet_tracer_dditable_t()
        r = xe_result_v(self.__dll.xetGetTracerProcAddrTable(version, byref(_Tracer)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Tracer = _Tracer

        # attach function interface to function address
        self.xetTracerCreate = _xetTracerCreate_t(self.__dditable.Tracer.pfnCreate)
        self.xetTracerDestroy = _xetTracerDestroy_t(self.__dditable.Tracer.pfnDestroy)
        self.xetTracerSetPrologues = _xetTracerSetPrologues_t(self.__dditable.Tracer.pfnSetPrologues)
        self.xetTracerSetEpilogues = _xetTracerSetEpilogues_t(self.__dditable.Tracer.pfnSetEpilogues)
        self.xetTracerSetEnabled = _xetTracerSetEnabled_t(self.__dditable.Tracer.pfnSetEnabled)

        # call driver to get function pointers
        _Sysman = _xet_sysman_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanProcAddrTable(version, byref(_Sysman)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Sysman = _Sysman

        # attach function interface to function address
        self.xetSysmanGet = _xetSysmanGet_t(self.__dditable.Sysman.pfnGet)
        self.xetSysmanDeviceGetProperties = _xetSysmanDeviceGetProperties_t(self.__dditable.Sysman.pfnDeviceGetProperties)
        self.xetSysmanSchedulerGetCurrentMode = _xetSysmanSchedulerGetCurrentMode_t(self.__dditable.Sysman.pfnSchedulerGetCurrentMode)
        self.xetSysmanSchedulerGetTimeoutModeProperties = _xetSysmanSchedulerGetTimeoutModeProperties_t(self.__dditable.Sysman.pfnSchedulerGetTimeoutModeProperties)
        self.xetSysmanSchedulerGetTimesliceModeProperties = _xetSysmanSchedulerGetTimesliceModeProperties_t(self.__dditable.Sysman.pfnSchedulerGetTimesliceModeProperties)
        self.xetSysmanSchedulerSetTimeoutMode = _xetSysmanSchedulerSetTimeoutMode_t(self.__dditable.Sysman.pfnSchedulerSetTimeoutMode)
        self.xetSysmanSchedulerSetTimesliceMode = _xetSysmanSchedulerSetTimesliceMode_t(self.__dditable.Sysman.pfnSchedulerSetTimesliceMode)
        self.xetSysmanSchedulerSetExclusiveMode = _xetSysmanSchedulerSetExclusiveMode_t(self.__dditable.Sysman.pfnSchedulerSetExclusiveMode)
        self.xetSysmanSchedulerSetSingleCmdQueueMode = _xetSysmanSchedulerSetSingleCmdQueueMode_t(self.__dditable.Sysman.pfnSchedulerSetSingleCmdQueueMode)
        self.xetSysmanDeviceReset = _xetSysmanDeviceReset_t(self.__dditable.Sysman.pfnDeviceReset)
        self.xetSysmanDeviceWasRepaired = _xetSysmanDeviceWasRepaired_t(self.__dditable.Sysman.pfnDeviceWasRepaired)
        self.xetSysmanPciGetProperties = _xetSysmanPciGetProperties_t(self.__dditable.Sysman.pfnPciGetProperties)
        self.xetSysmanPciGetState = _xetSysmanPciGetState_t(self.__dditable.Sysman.pfnPciGetState)
        self.xetSysmanPciGetBarProperties = _xetSysmanPciGetBarProperties_t(self.__dditable.Sysman.pfnPciGetBarProperties)
        self.xetSysmanPciGetThroughput = _xetSysmanPciGetThroughput_t(self.__dditable.Sysman.pfnPciGetThroughput)
        self.xetSysmanPciGetStats = _xetSysmanPciGetStats_t(self.__dditable.Sysman.pfnPciGetStats)
        self.xetSysmanPowerGet = _xetSysmanPowerGet_t(self.__dditable.Sysman.pfnPowerGet)
        self.xetSysmanFrequencyGet = _xetSysmanFrequencyGet_t(self.__dditable.Sysman.pfnFrequencyGet)
        self.xetSysmanEngineGet = _xetSysmanEngineGet_t(self.__dditable.Sysman.pfnEngineGet)
        self.xetSysmanStandbyGet = _xetSysmanStandbyGet_t(self.__dditable.Sysman.pfnStandbyGet)
        self.xetSysmanFirmwareGet = _xetSysmanFirmwareGet_t(self.__dditable.Sysman.pfnFirmwareGet)
        self.xetSysmanMemoryGet = _xetSysmanMemoryGet_t(self.__dditable.Sysman.pfnMemoryGet)
        self.xetSysmanLinkSwitchGet = _xetSysmanLinkSwitchGet_t(self.__dditable.Sysman.pfnLinkSwitchGet)
        self.xetSysmanTemperatureGet = _xetSysmanTemperatureGet_t(self.__dditable.Sysman.pfnTemperatureGet)
        self.xetSysmanPsuGet = _xetSysmanPsuGet_t(self.__dditable.Sysman.pfnPsuGet)
        self.xetSysmanFanGet = _xetSysmanFanGet_t(self.__dditable.Sysman.pfnFanGet)
        self.xetSysmanLedGet = _xetSysmanLedGet_t(self.__dditable.Sysman.pfnLedGet)
        self.xetSysmanRasGet = _xetSysmanRasGet_t(self.__dditable.Sysman.pfnRasGet)
        self.xetSysmanEventsGetProperties = _xetSysmanEventsGetProperties_t(self.__dditable.Sysman.pfnEventsGetProperties)
        self.xetSysmanEventsRegister = _xetSysmanEventsRegister_t(self.__dditable.Sysman.pfnEventsRegister)
        self.xetSysmanEventsUnregister = _xetSysmanEventsUnregister_t(self.__dditable.Sysman.pfnEventsUnregister)
        self.xetSysmanEventsListen = _xetSysmanEventsListen_t(self.__dditable.Sysman.pfnEventsListen)
        self.xetSysmanDiagnosticsGet = _xetSysmanDiagnosticsGet_t(self.__dditable.Sysman.pfnDiagnosticsGet)

        # call driver to get function pointers
        _SysmanPower = _xet_sysman_power_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanPowerProcAddrTable(version, byref(_SysmanPower)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanPower = _SysmanPower

        # attach function interface to function address
        self.xetSysmanPowerGetProperties = _xetSysmanPowerGetProperties_t(self.__dditable.SysmanPower.pfnGetProperties)
        self.xetSysmanPowerGetEnergyCounter = _xetSysmanPowerGetEnergyCounter_t(self.__dditable.SysmanPower.pfnGetEnergyCounter)
        self.xetSysmanPowerGetEnergyThreshold = _xetSysmanPowerGetEnergyThreshold_t(self.__dditable.SysmanPower.pfnGetEnergyThreshold)
        self.xetSysmanPowerSetEnergyThreshold = _xetSysmanPowerSetEnergyThreshold_t(self.__dditable.SysmanPower.pfnSetEnergyThreshold)
        self.xetSysmanPowerGetLimits = _xetSysmanPowerGetLimits_t(self.__dditable.SysmanPower.pfnGetLimits)
        self.xetSysmanPowerSetLimits = _xetSysmanPowerSetLimits_t(self.__dditable.SysmanPower.pfnSetLimits)

        # call driver to get function pointers
        _SysmanFrequency = _xet_sysman_frequency_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanFrequencyProcAddrTable(version, byref(_SysmanFrequency)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFrequency = _SysmanFrequency

        # attach function interface to function address
        self.xetSysmanFrequencySetFanSpeed = _xetSysmanFrequencySetFanSpeed_t(self.__dditable.SysmanFrequency.pfnSetFanSpeed)
        self.xetSysmanFrequencyGetOcCapabilities = _xetSysmanFrequencyGetOcCapabilities_t(self.__dditable.SysmanFrequency.pfnGetOcCapabilities)
        self.xetSysmanFrequencyGetOcVrTopology = _xetSysmanFrequencyGetOcVrTopology_t(self.__dditable.SysmanFrequency.pfnGetOcVrTopology)
        self.xetSysmanFrequencyGetOcOverrideProperties = _xetSysmanFrequencyGetOcOverrideProperties_t(self.__dditable.SysmanFrequency.pfnGetOcOverrideProperties)
        self.xetSysmanFrequencyGetOcIccMax = _xetSysmanFrequencyGetOcIccMax_t(self.__dditable.SysmanFrequency.pfnGetOcIccMax)
        self.xetSysmanFrequencyGetOcTjMax = _xetSysmanFrequencyGetOcTjMax_t(self.__dditable.SysmanFrequency.pfnGetOcTjMax)
        self.xetSysmanFrequencySetOcOverrideProperties = _xetSysmanFrequencySetOcOverrideProperties_t(self.__dditable.SysmanFrequency.pfnSetOcOverrideProperties)
        self.xetSysmanFrequencySetOcIccMax = _xetSysmanFrequencySetOcIccMax_t(self.__dditable.SysmanFrequency.pfnSetOcIccMax)
        self.xetSysmanFrequencySetOcTjMax = _xetSysmanFrequencySetOcTjMax_t(self.__dditable.SysmanFrequency.pfnSetOcTjMax)
        self.xetSysmanFrequencyGetProperties = _xetSysmanFrequencyGetProperties_t(self.__dditable.SysmanFrequency.pfnGetProperties)
        self.xetSysmanFrequencyGetRange = _xetSysmanFrequencyGetRange_t(self.__dditable.SysmanFrequency.pfnGetRange)
        self.xetSysmanFrequencySetRange = _xetSysmanFrequencySetRange_t(self.__dditable.SysmanFrequency.pfnSetRange)
        self.xetSysmanFrequencyGetState = _xetSysmanFrequencyGetState_t(self.__dditable.SysmanFrequency.pfnGetState)
        self.xetSysmanFrequencyGetThrottleTime = _xetSysmanFrequencyGetThrottleTime_t(self.__dditable.SysmanFrequency.pfnGetThrottleTime)

        # call driver to get function pointers
        _SysmanEngine = _xet_sysman_engine_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanEngineProcAddrTable(version, byref(_SysmanEngine)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanEngine = _SysmanEngine

        # attach function interface to function address
        self.xetSysmanEngineGetProperties = _xetSysmanEngineGetProperties_t(self.__dditable.SysmanEngine.pfnGetProperties)
        self.xetSysmanEngineGetActivity = _xetSysmanEngineGetActivity_t(self.__dditable.SysmanEngine.pfnGetActivity)

        # call driver to get function pointers
        _SysmanStandby = _xet_sysman_standby_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanStandbyProcAddrTable(version, byref(_SysmanStandby)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanStandby = _SysmanStandby

        # attach function interface to function address
        self.xetSysmanStandbyGetProperties = _xetSysmanStandbyGetProperties_t(self.__dditable.SysmanStandby.pfnGetProperties)
        self.xetSysmanStandbyGetMode = _xetSysmanStandbyGetMode_t(self.__dditable.SysmanStandby.pfnGetMode)
        self.xetSysmanStandbySetMode = _xetSysmanStandbySetMode_t(self.__dditable.SysmanStandby.pfnSetMode)

        # call driver to get function pointers
        _SysmanFirmware = _xet_sysman_firmware_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanFirmwareProcAddrTable(version, byref(_SysmanFirmware)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFirmware = _SysmanFirmware

        # attach function interface to function address
        self.xetSysmanFirmwareGetProperties = _xetSysmanFirmwareGetProperties_t(self.__dditable.SysmanFirmware.pfnGetProperties)
        self.xetSysmanFirmwareGetChecksum = _xetSysmanFirmwareGetChecksum_t(self.__dditable.SysmanFirmware.pfnGetChecksum)
        self.xetSysmanFirmwareFlash = _xetSysmanFirmwareFlash_t(self.__dditable.SysmanFirmware.pfnFlash)

        # call driver to get function pointers
        _SysmanMemory = _xet_sysman_memory_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanMemoryProcAddrTable(version, byref(_SysmanMemory)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanMemory = _SysmanMemory

        # attach function interface to function address
        self.xetSysmanMemoryGetProperties = _xetSysmanMemoryGetProperties_t(self.__dditable.SysmanMemory.pfnGetProperties)
        self.xetSysmanMemoryGetBandwidth = _xetSysmanMemoryGetBandwidth_t(self.__dditable.SysmanMemory.pfnGetBandwidth)
        self.xetSysmanMemoryGetAllocated = _xetSysmanMemoryGetAllocated_t(self.__dditable.SysmanMemory.pfnGetAllocated)

        # call driver to get function pointers
        _SysmanLinkSwitch = _xet_sysman_link_switch_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanLinkSwitchProcAddrTable(version, byref(_SysmanLinkSwitch)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanLinkSwitch = _SysmanLinkSwitch

        # attach function interface to function address
        self.xetSysmanLinkSwitchGetProperties = _xetSysmanLinkSwitchGetProperties_t(self.__dditable.SysmanLinkSwitch.pfnGetProperties)
        self.xetSysmanLinkSwitchGetState = _xetSysmanLinkSwitchGetState_t(self.__dditable.SysmanLinkSwitch.pfnGetState)
        self.xetSysmanLinkSwitchSetState = _xetSysmanLinkSwitchSetState_t(self.__dditable.SysmanLinkSwitch.pfnSetState)
        self.xetSysmanLinkSwitchGetPorts = _xetSysmanLinkSwitchGetPorts_t(self.__dditable.SysmanLinkSwitch.pfnGetPorts)

        # call driver to get function pointers
        _SysmanLinkPort = _xet_sysman_link_port_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanLinkPortProcAddrTable(version, byref(_SysmanLinkPort)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanLinkPort = _SysmanLinkPort

        # attach function interface to function address
        self.xetSysmanLinkPortGetProperties = _xetSysmanLinkPortGetProperties_t(self.__dditable.SysmanLinkPort.pfnGetProperties)
        self.xetSysmanLinkPortGetState = _xetSysmanLinkPortGetState_t(self.__dditable.SysmanLinkPort.pfnGetState)
        self.xetSysmanLinkPortGetThroughput = _xetSysmanLinkPortGetThroughput_t(self.__dditable.SysmanLinkPort.pfnGetThroughput)
        self.xetSysmanLinkPortGetStats = _xetSysmanLinkPortGetStats_t(self.__dditable.SysmanLinkPort.pfnGetStats)
        self.xetSysmanLinkPortIsConnected = _xetSysmanLinkPortIsConnected_t(self.__dditable.SysmanLinkPort.pfnIsConnected)

        # call driver to get function pointers
        _SysmanTemperature = _xet_sysman_temperature_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanTemperatureProcAddrTable(version, byref(_SysmanTemperature)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanTemperature = _SysmanTemperature

        # attach function interface to function address
        self.xetSysmanTemperatureGetProperties = _xetSysmanTemperatureGetProperties_t(self.__dditable.SysmanTemperature.pfnGetProperties)
        self.xetSysmanTemperatureRead = _xetSysmanTemperatureRead_t(self.__dditable.SysmanTemperature.pfnRead)

        # call driver to get function pointers
        _SysmanPsu = _xet_sysman_psu_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanPsuProcAddrTable(version, byref(_SysmanPsu)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanPsu = _SysmanPsu

        # attach function interface to function address
        self.xetSysmanPsuGetProperties = _xetSysmanPsuGetProperties_t(self.__dditable.SysmanPsu.pfnGetProperties)
        self.xetSysmanPsuGetState = _xetSysmanPsuGetState_t(self.__dditable.SysmanPsu.pfnGetState)

        # call driver to get function pointers
        _SysmanFan = _xet_sysman_fan_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanFanProcAddrTable(version, byref(_SysmanFan)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFan = _SysmanFan

        # attach function interface to function address
        self.xetSysmanFanGetProperties = _xetSysmanFanGetProperties_t(self.__dditable.SysmanFan.pfnGetProperties)
        self.xetSysmanFanGetConfig = _xetSysmanFanGetConfig_t(self.__dditable.SysmanFan.pfnGetConfig)
        self.xetSysmanFanSetConfig = _xetSysmanFanSetConfig_t(self.__dditable.SysmanFan.pfnSetConfig)
        self.xetSysmanFanGetState = _xetSysmanFanGetState_t(self.__dditable.SysmanFan.pfnGetState)

        # call driver to get function pointers
        _SysmanLed = _xet_sysman_led_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanLedProcAddrTable(version, byref(_SysmanLed)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanLed = _SysmanLed

        # attach function interface to function address
        self.xetSysmanLedGetProperties = _xetSysmanLedGetProperties_t(self.__dditable.SysmanLed.pfnGetProperties)
        self.xetSysmanLedGetState = _xetSysmanLedGetState_t(self.__dditable.SysmanLed.pfnGetState)
        self.xetSysmanLedSetState = _xetSysmanLedSetState_t(self.__dditable.SysmanLed.pfnSetState)

        # call driver to get function pointers
        _SysmanRas = _xet_sysman_ras_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanRasProcAddrTable(version, byref(_SysmanRas)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanRas = _SysmanRas

        # attach function interface to function address
        self.xetSysmanRasGetProperties = _xetSysmanRasGetProperties_t(self.__dditable.SysmanRas.pfnGetProperties)
        self.xetSysmanRasGetErrors = _xetSysmanRasGetErrors_t(self.__dditable.SysmanRas.pfnGetErrors)

        # call driver to get function pointers
        _SysmanDiagnostics = _xet_sysman_diagnostics_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanDiagnosticsProcAddrTable(version, byref(_SysmanDiagnostics)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanDiagnostics = _SysmanDiagnostics

        # attach function interface to function address
        self.xetSysmanDiagnosticsGetProperties = _xetSysmanDiagnosticsGetProperties_t(self.__dditable.SysmanDiagnostics.pfnGetProperties)
        self.xetSysmanDiagnosticsRunTests = _xetSysmanDiagnosticsRunTests_t(self.__dditable.SysmanDiagnostics.pfnRunTests)

        # success!
