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
## @brief Handle for a SMI device power domain
class zet_sysman_pwr_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device frequency domain
class zet_sysman_freq_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device engine group
class zet_sysman_engine_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device standby control
class zet_sysman_standby_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device firmware
class zet_sysman_firmware_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device memory module
class zet_sysman_mem_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device connectivity switch
class zet_sysman_link_switch_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device connectivity port
class zet_sysman_link_port_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device temperature sensor
class zet_sysman_temp_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device power supply
class zet_sysman_psu_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device fan
class zet_sysman_fan_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device LED
class zet_sysman_led_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device RAS error set
class zet_sysman_ras_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a SMI device diagnostics test suite
class zet_sysman_diag_handle_t(c_void_p):
    pass

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
## @brief API version of SMI
class zet_sysman_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 1, 0 )               ## version 1.0

class zet_sysman_version_t(c_int):
    def __str__(self):
        return str(zet_sysman_version_v(value))


###############################################################################
## @brief Maximum number of characters in string properties.
ZET_STRING_PROPERTY_SIZE = 32

###############################################################################
## @brief Device Type
class zet_device_type_v(IntEnum):
    INTEGRATED = 0                                  ## The device is an integrated GPU
    DISCRETE = auto()                               ## The device is a discrete GPU

class zet_device_type_t(c_int):
    def __str__(self):
        return str(zet_device_type_v(value))


###############################################################################
## @brief Device properties
class zet_sysman_properties_t(Structure):
    _fields_ = [
        ("core", ze_device_properties_t),                               ## [out] Core device properties
        ("numSubdevices", c_ulong),                                     ## [out] Number of sub-devices
        ("deviceType", zet_device_type_t),                              ## [out] Device type
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
        ("maxBandwidth", c_ulong),                                      ## [out] The maximum bandwidth in bytes/sec
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
## @brief Dynamic PCI state
class zet_pci_state_t(Structure):
    _fields_ = [
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
## @brief PCI throughput
## 
## @details
##     - Percent throughput is calculated by taking two snapshots (s1, s2) and
##       using the equation: %bw = 10^6 * ((s2.rxCounter - s1.rxCounter) +
##       (s2.txCounter - s1.txCounter)) / (s2.maxBandwidth * (s2.timestamp -
##       s1.timestamp))
class zet_pci_throughput_t(Structure):
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
        ("packetCounter", c_ulonglong)                                  ## [out] Monotonic counter for the number of packets
    ]

###############################################################################
## @brief Properties related to device power settings
class zet_power_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Software can change the power limits.
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
## @brief Energy threshold
## 
## @details
##     - Energy threshold value, when this value is crossed, pcu will signal an
##       interrupt.
class zet_power_energy_threshold_t(Structure):
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
## @brief Overclocking modes
class zet_oc_mode_v(IntEnum):
    OVERCLOCKING_INTERPOLATIVE_MODE = 0             ## Interpolative Mode.
    OVERCLOCKING_OVERRIDE_MODE = 1                  ## Override Mode.

class zet_oc_mode_t(c_int):
    def __str__(self):
        return str(zet_oc_mode_v(value))


###############################################################################
## @brief Over clocking error type
class zet_oc_error_type_v(IntEnum):
    OVERCLOCKING_LOCKED = 225                       ## The overclocking is locked. Service is read-only.
    OVERCLOCKING_DDOMAIN_SERVICE_NOT_SUPPORTED = auto() ## The specified domain does not support the requested service.
    OVERCLOCKING_RATIO_EXCEEDS_MAX = auto()         ## The ratio exceeds maximum overclocking limits.
    OVERCLOCKING_VOLTAGE_EXCEEDS_MAX = auto()       ## Requested voltage exceeds input regulators max supported voltage.
    OVERCLOCKING_NOT_SUPPORTED = auto()             ## No overclocking capability on the Hardware.
    OVERCLOCKING_INVALID_VR_ADDRESS = auto()        ## The VR Address provided is illegal.
    OOVERCLOCKING_INVALID_ICCMAX = auto()           ## ICCMAX value given is invalid (more than 10 bits) or too low.
    OVERCLOCKING_VOLTAGE_OVERRIDE_DISABLED = auto() ## Voltage manipulation attempted when it is disabled.
    OVERCLOCKING_INVALID_COMMAND = auto()           ## Data setting invalid for the command.

class zet_oc_error_type_t(c_int):
    def __str__(self):
        return str(zet_oc_error_type_v(value))


###############################################################################
## @brief Overclocking properties
## 
## @details
##     - Provides all the overclocking capabilities and properties supported by
##       the device in the current domain.
class zet_oc_capabilities_t(Structure):
    _fields_ = [
        ("MaxOcFrequencyLimit", c_double),                              ## [out] Max overclocking frequency limit in Mhz.
        ("MaxFactoryDefaultFrequency", c_double),                       ## [out] Maximum factory default frequency in Mhz.
        ("MaxFactoryDefaultVoltage", c_double),                         ## [out] Maximum factory default voltage in Votls.
        ("TjMaxSupported", ze_bool_t),                                  ## [out] is the TjMax supported on this domain.
        ("IccMaxSupported", ze_bool_t),                                 ## [out] is the Icc supported on this domain.
        ("FrequencyOcSupported", ze_bool_t),                            ## [out] Frequency overclocking supported
        ("VoltageOverrideSupported", ze_bool_t),                        ## [out] Voltage overrides supported
        ("VoltageOffsetSupported", ze_bool_t),                          ## [out] Voltage offset is supported
        ("HighVoltModeCapable", ze_bool_t),                             ## [out] Capable of high voltage mode
        ("HighVoltModeEnabled", ze_bool_t)                              ## [out] High voltage mode is enabled
    ]

###############################################################################
## @brief Overclocking configuration
## 
## @details
##     - Provide the current settings to be read or changed.
class zet_oc_configuration_t(Structure):
    _fields_ = [
        ("OcFrequency", c_double),                                      ## [in,out] Overclocking Frequency
        ("TargetVoltage", c_double),                                    ## [in,out] Target voltage in Volts
        ("TargetMode", zet_oc_mode_t),                                  ## [in,out] Overclock Mode ::zet_oc_mode_t.
        ("VoltageOffset", c_double)                                     ## [in,out] Voltage offset in Volts.
    ]

###############################################################################
## @brief Maximum desired current.
## 
## @details
##     - For overclock-able parts this holds the maximum desired current if the
##       domains supports it.
class zet_oc_icc_max_t(Structure):
    _fields_ = [
        ("IccMax", c_double)                                            ## [in,out] Maximum desired current in Amperes
    ]

###############################################################################
## @brief Temperature Junction Maximum.
## 
## @details
##     - For overclock-able parts this holds the maximum temperature limit at
##       which the part will throttle if the domains supports it.
class zet_oc_tj_max_t(Structure):
    _fields_ = [
        ("TjMax", c_double)                                             ## [in,out] Maximum desired current in degrees celcius.
    ]

###############################################################################
## @brief Frequency domains
class zet_freq_domain_v(IntEnum):
    GPU = 0                                         ## Frequency of the GPU.
    MEMORY = auto()                                 ## Frequency of the local memory.

class zet_freq_domain_t(c_int):
    def __str__(self):
        return str(zet_freq_domain_v(value))


###############################################################################
## @brief Frequency properties
## 
## @details
##     - Provides the set of frequencies as a list and as a range/step.
##     - It is generally recommended that applications choose frequencies from
##       the list. However applications can also construct the list themselves
##       using the range/steps provided.
class zet_freq_properties_t(Structure):
    _fields_ = [
        ("type", zet_freq_domain_t),                                    ## [out] The type of frequency domain (GPU, memory, ...)
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can control the frequency of this domain
        ("canOverclock", ze_bool_t),                                    ## [out] Indicates if software can overclock this frequency domain
        ("min", c_double),                                              ## [out] The minimum clock frequency in units of MHz
        ("max", c_double),                                              ## [out] The maximum clock frequency in units of MHz
        ("step", c_double),                                             ## [out] The step clock frequency in units of MHz
        ("num", c_ulong),                                               ## [out] The number of clocks in the array pClocks
        ("pClocks", POINTER(c_double))                                  ## [out] Array of clock frequencies in units of MHz ordered from smallest
                                                                        ## to largest.
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
                                                                        ## (Bitfield of (1<<::zet_freq_throttle_reasons_t)).
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
## @brief Accelerator engine groups
class zet_engine_group_v(IntEnum):
    ALL = 0                                         ## Access information about all engines combined.
    COMPUTE = auto()                                ## Access information about compute engines.
    MEDIA = auto()                                  ## Access information about media engines.

class zet_engine_group_t(c_int):
    def __str__(self):
        return str(zet_engine_group_v(value))


###############################################################################
## @brief Engine group properties
class zet_engine_properties_t(Structure):
    _fields_ = [
        ("type", zet_engine_group_t),                                   ## [out] The engine group
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
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
                                                                        ## that the resource is on the device of the calling SMI handle
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
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can flash the firmware
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
## @brief Memory properties
class zet_mem_properties_t(Structure):
    _fields_ = [
        ("type", zet_mem_type_t),                                       ## [out] The memory type
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
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
## @brief Memory allocation
## 
## @details
##     - Percent allocation is given by 100 * allocated / total.
##     - Percent free is given by 100 * (total - allocated) / total.
class zet_mem_alloc_t(Structure):
    _fields_ = [
        ("allocated", c_ulonglong),                                     ## [out] The total allocated bytes
        ("total", c_ulonglong)                                          ## [out] The total physical memory in bytes
    ]

###############################################################################
## @brief Connectivity switch properties
class zet_link_switch_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the switch is located on a sub-device; false means that
                                                                        ## the switch is on the device of the calling SMI handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
    ]

###############################################################################
## @brief Connectivity switch state
class zet_link_switch_state_t(Structure):
    _fields_ = [
        ("enabled", ze_bool_t)                                          ## [out] Indicates if the switch is enabled/disabled
    ]

###############################################################################
## @brief Connectivity port speed
class zet_link_port_speed_t(Structure):
    _fields_ = [
        ("bitRate", c_ulong),                                           ## [out] Bits/sec that the link is operating at
        ("width", c_ulong),                                             ## [out] The number of lanes
        ("maxBandwidth", c_ulong)                                       ## [out] The maximum bandwidth in bytes/sec
    ]

###############################################################################
## @brief Connectivity port properties
class zet_link_port_properties_t(Structure):
    _fields_ = [
        ("portNum", c_ulong),                                           ## [out] The port number on the switch
        ("maxSpeed", zet_link_port_speed_t)                             ## [out] Maximum bandwidth supported by the port
    ]

###############################################################################
## @brief Connectivity port state
class zet_link_port_state_t(Structure):
    _fields_ = [
        ("isConnected", ze_bool_t),                                     ## [out] Indicates if the port is connected to a remote Switch
        ("rxSpeed", zet_link_port_speed_t),                             ## [out] Current maximum receive speed
        ("txSpeed", zet_link_port_speed_t)                              ## [out] Current maximum transmit speed
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
class zet_link_port_throughput_t(Structure):
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
class zet_link_port_stats_t(Structure):
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
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
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
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can control the PSU
        ("haveFan", ze_bool_t),                                         ## [out] True if the power supply has a fan
        ("ampLimit", c_ulong)                                           ## [out] The maximum electrical current in amperes that can be drawn
    ]

###############################################################################
## @brief Dynamic state of the power supply
class zet_psu_state_t(Structure):
    _fields_ = [
        ("voltStatus", zet_psu_voltage_status_t),                       ## [out] The current PSU voltage status
        ("fanFailed", ze_bool_t),                                       ## [out] Indicates if the fan has failed
        ("temperature", c_ulong),                                       ## [out] Read the current heatsink temperature in degrees celcius
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
        ("temperature", c_ulong),                                       ## [in,out] Temperature in degrees celcius
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
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can control the fan speed
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
## @brief Fan state
class zet_fan_state_t(Structure):
    _fields_ = [
        ("mode", zet_fan_speed_mode_t),                                 ## [out] The fan speed mode (default, fixed, temp-speed table)
        ("speedUnits", zet_fan_speed_units_t),                          ## [out] The units of the fan speed
        ("speed", c_ulong)                                              ## [out] The current fan speed
    ]

###############################################################################
## @brief LED properties
class zet_led_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can control the LED
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
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("supported", ze_bool_t),                                       ## [out] True if RAS is supported on this device
        ("enabled", ze_bool_t)                                          ## [out] True if RAS is enabled on this device
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
        ("numMemoryErrors", c_ulonglong),                               ## [out] The number of errors that have occurred in the local memory
        ("numPciErrors", c_ulonglong),                                  ## [out] The number of errors that have occurred in the PCI link
        ("numSwitchErrors", c_ulonglong),                               ## [out] The number of errors that have occurred in the high-speed
                                                                        ## connectivity links
        ("numDisplayErrors", c_ulonglong)                               ## [out] The number of errors that have occurred in the display
    ]

###############################################################################
## @brief Event types
class zet_sysman_event_type_v(IntEnum):
    FREQ_THROTTLED = 0                              ## The frequency is being throttled
    ENERGY_THRESHOLD_CROSSED = auto()               ## Interrupt from the PCU when the energy threshold is crossed.
    MAX_TEMPERATURE = auto()                        ## Interrupt from the PCU when the energy Max temperature is reached.
    RAS_ERRORS = auto()                             ## ECC/RAS errors
    NUM = auto()                                    ## The number of event types

class zet_sysman_event_type_t(c_int):
    def __str__(self):
        return str(zet_sysman_event_type_v(value))


###############################################################################
## @brief Event properties
class zet_event_properties_t(Structure):
    _fields_ = [
        ("supportedEvents", ze_bool_t * ZET_SYSMAN_EVENT_TYPE_NUM)      ## [out] Set to true for the events that are supported
    ]

###############################################################################
## @brief Request structure used to register/unregister events
class zet_event_request_t(Structure):
    _fields_ = [
        ("event", zet_sysman_event_type_t),                             ## [in] The event type to register.
        ("threshold", c_ulong)                                          ## [in] The application only receives a notification when the total count
                                                                        ## exceeds this value. Set to zero to receive a notification for every
                                                                        ## new event.
    ]

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
        ("name", POINTER(c_char))                                       ## [out] Name of the test
    ]

###############################################################################
## @brief Diagnostics test suite properties
class zet_diag_properties_t(Structure):
    _fields_ = [
        ("type", zet_diag_type_t),                                      ## [out] The type of diagnostics test suite
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling SMI handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("name", POINTER(c_char)),                                      ## [out] Name of the diagnostics test suite
        ("numTests", c_ulong),                                          ## [out] The number of tests in the test suite
        ("pTests", POINTER(zet_diag_test_t))                            ## [out] Array of tests (size ::zet_diag_properties_t.numTests), sorted
                                                                        ## by increasing value of ::zet_diag_test_t.index
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
    _zetTracerCreate_t = WINFUNCTYPE( ze_result_t, zet_device_handle_t, POINTER(zet_tracer_desc_t), POINTER(zet_tracer_handle_t) )
else:
    _zetTracerCreate_t = CFUNCTYPE( ze_result_t, zet_device_handle_t, POINTER(zet_tracer_desc_t), POINTER(zet_tracer_handle_t) )

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
## @brief Function-pointer for zetSysmanDeviceReset
if __use_win_types:
    _zetSysmanDeviceReset_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t )
else:
    _zetSysmanDeviceReset_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t )

###############################################################################
## @brief Function-pointer for zetSysmanDeviceWasRepaired
if __use_win_types:
    _zetSysmanDeviceWasRepaired_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(ze_bool_t) )
else:
    _zetSysmanDeviceWasRepaired_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(ze_bool_t) )

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
## @brief Function-pointer for zetSysmanPciGetThroughput
if __use_win_types:
    _zetSysmanPciGetThroughput_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_pci_throughput_t) )
else:
    _zetSysmanPciGetThroughput_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_pci_throughput_t) )

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
## @brief Function-pointer for zetSysmanLinkSwitchGet
if __use_win_types:
    _zetSysmanLinkSwitchGet_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_link_switch_handle_t) )
else:
    _zetSysmanLinkSwitchGet_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(c_ulong), POINTER(zet_sysman_link_switch_handle_t) )

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
## @brief Function-pointer for zetSysmanEventsGetProperties
if __use_win_types:
    _zetSysmanEventsGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_event_properties_t) )
else:
    _zetSysmanEventsGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, POINTER(zet_event_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanEventsRegister
if __use_win_types:
    _zetSysmanEventsRegister_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, c_ulong, POINTER(zet_event_request_t) )
else:
    _zetSysmanEventsRegister_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, c_ulong, POINTER(zet_event_request_t) )

###############################################################################
## @brief Function-pointer for zetSysmanEventsUnregister
if __use_win_types:
    _zetSysmanEventsUnregister_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, c_ulong, POINTER(zet_event_request_t) )
else:
    _zetSysmanEventsUnregister_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, c_ulong, POINTER(zet_event_request_t) )

###############################################################################
## @brief Function-pointer for zetSysmanEventsListen
if __use_win_types:
    _zetSysmanEventsListen_t = WINFUNCTYPE( ze_result_t, zet_sysman_handle_t, ze_bool_t, c_ulong, POINTER(c_ulong) )
else:
    _zetSysmanEventsListen_t = CFUNCTYPE( ze_result_t, zet_sysman_handle_t, ze_bool_t, c_ulong, POINTER(c_ulong) )

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
        ("pfnSchedulerGetCurrentMode", c_void_p),                       ## _zetSysmanSchedulerGetCurrentMode_t
        ("pfnSchedulerGetTimeoutModeProperties", c_void_p),             ## _zetSysmanSchedulerGetTimeoutModeProperties_t
        ("pfnSchedulerGetTimesliceModeProperties", c_void_p),           ## _zetSysmanSchedulerGetTimesliceModeProperties_t
        ("pfnSchedulerSetTimeoutMode", c_void_p),                       ## _zetSysmanSchedulerSetTimeoutMode_t
        ("pfnSchedulerSetTimesliceMode", c_void_p),                     ## _zetSysmanSchedulerSetTimesliceMode_t
        ("pfnSchedulerSetExclusiveMode", c_void_p),                     ## _zetSysmanSchedulerSetExclusiveMode_t
        ("pfnSchedulerSetComputeUnitDebugMode", c_void_p),              ## _zetSysmanSchedulerSetComputeUnitDebugMode_t
        ("pfnDeviceReset", c_void_p),                                   ## _zetSysmanDeviceReset_t
        ("pfnDeviceWasRepaired", c_void_p),                             ## _zetSysmanDeviceWasRepaired_t
        ("pfnPciGetProperties", c_void_p),                              ## _zetSysmanPciGetProperties_t
        ("pfnPciGetState", c_void_p),                                   ## _zetSysmanPciGetState_t
        ("pfnPciGetBarProperties", c_void_p),                           ## _zetSysmanPciGetBarProperties_t
        ("pfnPciGetThroughput", c_void_p),                              ## _zetSysmanPciGetThroughput_t
        ("pfnPciGetStats", c_void_p),                                   ## _zetSysmanPciGetStats_t
        ("pfnPowerGet", c_void_p),                                      ## _zetSysmanPowerGet_t
        ("pfnFrequencyGet", c_void_p),                                  ## _zetSysmanFrequencyGet_t
        ("pfnEngineGet", c_void_p),                                     ## _zetSysmanEngineGet_t
        ("pfnStandbyGet", c_void_p),                                    ## _zetSysmanStandbyGet_t
        ("pfnFirmwareGet", c_void_p),                                   ## _zetSysmanFirmwareGet_t
        ("pfnMemoryGet", c_void_p),                                     ## _zetSysmanMemoryGet_t
        ("pfnLinkSwitchGet", c_void_p),                                 ## _zetSysmanLinkSwitchGet_t
        ("pfnTemperatureGet", c_void_p),                                ## _zetSysmanTemperatureGet_t
        ("pfnPsuGet", c_void_p),                                        ## _zetSysmanPsuGet_t
        ("pfnFanGet", c_void_p),                                        ## _zetSysmanFanGet_t
        ("pfnLedGet", c_void_p),                                        ## _zetSysmanLedGet_t
        ("pfnRasGet", c_void_p),                                        ## _zetSysmanRasGet_t
        ("pfnEventsGetProperties", c_void_p),                           ## _zetSysmanEventsGetProperties_t
        ("pfnEventsRegister", c_void_p),                                ## _zetSysmanEventsRegister_t
        ("pfnEventsUnregister", c_void_p),                              ## _zetSysmanEventsUnregister_t
        ("pfnEventsListen", c_void_p),                                  ## _zetSysmanEventsListen_t
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
## @brief Function-pointer for zetSysmanPowerGetEnergyThreshold
if __use_win_types:
    _zetSysmanPowerGetEnergyThreshold_t = WINFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_energy_threshold_t) )
else:
    _zetSysmanPowerGetEnergyThreshold_t = CFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_energy_threshold_t) )

###############################################################################
## @brief Function-pointer for zetSysmanPowerSetEnergyThreshold
if __use_win_types:
    _zetSysmanPowerSetEnergyThreshold_t = WINFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_energy_threshold_t) )
else:
    _zetSysmanPowerSetEnergyThreshold_t = CFUNCTYPE( ze_result_t, zet_sysman_pwr_handle_t, POINTER(zet_power_energy_threshold_t) )

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
## @brief Table of SysmanPower functions pointers
class _zet_sysman_power_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanPowerGetProperties_t
        ("pfnGetEnergyCounter", c_void_p),                              ## _zetSysmanPowerGetEnergyCounter_t
        ("pfnGetEnergyThreshold", c_void_p),                            ## _zetSysmanPowerGetEnergyThreshold_t
        ("pfnSetEnergyThreshold", c_void_p),                            ## _zetSysmanPowerSetEnergyThreshold_t
        ("pfnGetLimits", c_void_p),                                     ## _zetSysmanPowerGetLimits_t
        ("pfnSetLimits", c_void_p)                                      ## _zetSysmanPowerSetLimits_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetLastOcError
if __use_win_types:
    _zetSysmanFrequencyGetLastOcError_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_error_type_t) )
else:
    _zetSysmanFrequencyGetLastOcError_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_error_type_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetOcCapabilities
if __use_win_types:
    _zetSysmanFrequencyGetOcCapabilities_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_capabilities_t) )
else:
    _zetSysmanFrequencyGetOcCapabilities_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_capabilities_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetOcConfig
if __use_win_types:
    _zetSysmanFrequencyGetOcConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_configuration_t) )
else:
    _zetSysmanFrequencyGetOcConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_configuration_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencySetOcConfig
if __use_win_types:
    _zetSysmanFrequencySetOcConfig_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_configuration_t) )
else:
    _zetSysmanFrequencySetOcConfig_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_configuration_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetOcIccMax
if __use_win_types:
    _zetSysmanFrequencyGetOcIccMax_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_icc_max_t) )
else:
    _zetSysmanFrequencyGetOcIccMax_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_icc_max_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencySetOcIccMax
if __use_win_types:
    _zetSysmanFrequencySetOcIccMax_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_icc_max_t) )
else:
    _zetSysmanFrequencySetOcIccMax_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_icc_max_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetOcTjMax
if __use_win_types:
    _zetSysmanFrequencyGetOcTjMax_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_tj_max_t) )
else:
    _zetSysmanFrequencyGetOcTjMax_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_tj_max_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencySetOcTjMax
if __use_win_types:
    _zetSysmanFrequencySetOcTjMax_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_tj_max_t) )
else:
    _zetSysmanFrequencySetOcTjMax_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_oc_tj_max_t) )

###############################################################################
## @brief Function-pointer for zetSysmanFrequencyGetProperties
if __use_win_types:
    _zetSysmanFrequencyGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_properties_t) )
else:
    _zetSysmanFrequencyGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_freq_handle_t, POINTER(zet_freq_properties_t) )

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
## @brief Table of SysmanFrequency functions pointers
class _zet_sysman_frequency_dditable_t(Structure):
    _fields_ = [
        ("pfnGetLastOcError", c_void_p),                                ## _zetSysmanFrequencyGetLastOcError_t
        ("pfnGetOcCapabilities", c_void_p),                             ## _zetSysmanFrequencyGetOcCapabilities_t
        ("pfnGetOcConfig", c_void_p),                                   ## _zetSysmanFrequencyGetOcConfig_t
        ("pfnSetOcConfig", c_void_p),                                   ## _zetSysmanFrequencySetOcConfig_t
        ("pfnGetOcIccMax", c_void_p),                                   ## _zetSysmanFrequencyGetOcIccMax_t
        ("pfnSetOcIccMax", c_void_p),                                   ## _zetSysmanFrequencySetOcIccMax_t
        ("pfnGetOcTjMax", c_void_p),                                    ## _zetSysmanFrequencyGetOcTjMax_t
        ("pfnSetOcTjMax", c_void_p),                                    ## _zetSysmanFrequencySetOcTjMax_t
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanFrequencyGetProperties_t
        ("pfnGetRange", c_void_p),                                      ## _zetSysmanFrequencyGetRange_t
        ("pfnSetRange", c_void_p),                                      ## _zetSysmanFrequencySetRange_t
        ("pfnGetState", c_void_p),                                      ## _zetSysmanFrequencyGetState_t
        ("pfnGetThrottleTime", c_void_p)                                ## _zetSysmanFrequencyGetThrottleTime_t
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
## @brief Function-pointer for zetSysmanMemoryGetBandwidth
if __use_win_types:
    _zetSysmanMemoryGetBandwidth_t = WINFUNCTYPE( ze_result_t, zet_sysman_mem_handle_t, POINTER(zet_mem_bandwidth_t) )
else:
    _zetSysmanMemoryGetBandwidth_t = CFUNCTYPE( ze_result_t, zet_sysman_mem_handle_t, POINTER(zet_mem_bandwidth_t) )

###############################################################################
## @brief Function-pointer for zetSysmanMemoryGetAllocated
if __use_win_types:
    _zetSysmanMemoryGetAllocated_t = WINFUNCTYPE( ze_result_t, zet_sysman_mem_handle_t, POINTER(zet_mem_alloc_t) )
else:
    _zetSysmanMemoryGetAllocated_t = CFUNCTYPE( ze_result_t, zet_sysman_mem_handle_t, POINTER(zet_mem_alloc_t) )


###############################################################################
## @brief Table of SysmanMemory functions pointers
class _zet_sysman_memory_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanMemoryGetProperties_t
        ("pfnGetBandwidth", c_void_p),                                  ## _zetSysmanMemoryGetBandwidth_t
        ("pfnGetAllocated", c_void_p)                                   ## _zetSysmanMemoryGetAllocated_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanLinkSwitchGetProperties
if __use_win_types:
    _zetSysmanLinkSwitchGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_link_switch_handle_t, POINTER(zet_link_switch_properties_t) )
else:
    _zetSysmanLinkSwitchGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_link_switch_handle_t, POINTER(zet_link_switch_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanLinkSwitchGetState
if __use_win_types:
    _zetSysmanLinkSwitchGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_link_switch_handle_t, POINTER(zet_link_switch_state_t) )
else:
    _zetSysmanLinkSwitchGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_link_switch_handle_t, POINTER(zet_link_switch_state_t) )

###############################################################################
## @brief Function-pointer for zetSysmanLinkSwitchSetState
if __use_win_types:
    _zetSysmanLinkSwitchSetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_link_switch_handle_t, ze_bool_t )
else:
    _zetSysmanLinkSwitchSetState_t = CFUNCTYPE( ze_result_t, zet_sysman_link_switch_handle_t, ze_bool_t )

###############################################################################
## @brief Function-pointer for zetSysmanLinkSwitchGetPorts
if __use_win_types:
    _zetSysmanLinkSwitchGetPorts_t = WINFUNCTYPE( ze_result_t, zet_sysman_link_switch_handle_t, POINTER(c_ulong), POINTER(zet_sysman_link_port_handle_t) )
else:
    _zetSysmanLinkSwitchGetPorts_t = CFUNCTYPE( ze_result_t, zet_sysman_link_switch_handle_t, POINTER(c_ulong), POINTER(zet_sysman_link_port_handle_t) )


###############################################################################
## @brief Table of SysmanLinkSwitch functions pointers
class _zet_sysman_link_switch_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanLinkSwitchGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _zetSysmanLinkSwitchGetState_t
        ("pfnSetState", c_void_p),                                      ## _zetSysmanLinkSwitchSetState_t
        ("pfnGetPorts", c_void_p)                                       ## _zetSysmanLinkSwitchGetPorts_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanLinkPortGetProperties
if __use_win_types:
    _zetSysmanLinkPortGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_link_port_handle_t, POINTER(zet_link_port_properties_t) )
else:
    _zetSysmanLinkPortGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_link_port_handle_t, POINTER(zet_link_port_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanLinkPortGetState
if __use_win_types:
    _zetSysmanLinkPortGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_link_port_handle_t, POINTER(zet_link_port_state_t) )
else:
    _zetSysmanLinkPortGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_link_port_handle_t, POINTER(zet_link_port_state_t) )

###############################################################################
## @brief Function-pointer for zetSysmanLinkPortGetThroughput
if __use_win_types:
    _zetSysmanLinkPortGetThroughput_t = WINFUNCTYPE( ze_result_t, zet_sysman_link_port_handle_t, POINTER(zet_link_port_throughput_t) )
else:
    _zetSysmanLinkPortGetThroughput_t = CFUNCTYPE( ze_result_t, zet_sysman_link_port_handle_t, POINTER(zet_link_port_throughput_t) )

###############################################################################
## @brief Function-pointer for zetSysmanLinkPortGetStats
if __use_win_types:
    _zetSysmanLinkPortGetStats_t = WINFUNCTYPE( ze_result_t, zet_sysman_link_port_handle_t, POINTER(zet_link_port_stats_t) )
else:
    _zetSysmanLinkPortGetStats_t = CFUNCTYPE( ze_result_t, zet_sysman_link_port_handle_t, POINTER(zet_link_port_stats_t) )

###############################################################################
## @brief Function-pointer for zetSysmanLinkPortIsConnected
if __use_win_types:
    _zetSysmanLinkPortIsConnected_t = WINFUNCTYPE( ze_result_t, zet_sysman_link_port_handle_t, zet_sysman_link_port_handle_t, POINTER(ze_bool_t) )
else:
    _zetSysmanLinkPortIsConnected_t = CFUNCTYPE( ze_result_t, zet_sysman_link_port_handle_t, zet_sysman_link_port_handle_t, POINTER(ze_bool_t) )


###############################################################################
## @brief Table of SysmanLinkPort functions pointers
class _zet_sysman_link_port_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanLinkPortGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _zetSysmanLinkPortGetState_t
        ("pfnGetThroughput", c_void_p),                                 ## _zetSysmanLinkPortGetThroughput_t
        ("pfnGetStats", c_void_p),                                      ## _zetSysmanLinkPortGetStats_t
        ("pfnIsConnected", c_void_p)                                    ## _zetSysmanLinkPortIsConnected_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanTemperatureGetProperties
if __use_win_types:
    _zetSysmanTemperatureGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(zet_temp_properties_t) )
else:
    _zetSysmanTemperatureGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(zet_temp_properties_t) )

###############################################################################
## @brief Function-pointer for zetSysmanTemperatureRead
if __use_win_types:
    _zetSysmanTemperatureRead_t = WINFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(c_ulong) )
else:
    _zetSysmanTemperatureRead_t = CFUNCTYPE( ze_result_t, zet_sysman_temp_handle_t, POINTER(c_ulong) )


###############################################################################
## @brief Table of SysmanTemperature functions pointers
class _zet_sysman_temperature_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanTemperatureGetProperties_t
        ("pfnRead", c_void_p)                                           ## _zetSysmanTemperatureRead_t
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
    _zetSysmanFanGetState_t = WINFUNCTYPE( ze_result_t, zet_sysman_fan_handle_t, zet_fan_speed_units_t, POINTER(zet_fan_state_t) )
else:
    _zetSysmanFanGetState_t = CFUNCTYPE( ze_result_t, zet_sysman_fan_handle_t, zet_fan_speed_units_t, POINTER(zet_fan_state_t) )


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
## @brief Function-pointer for zetSysmanRasGetErrors
if __use_win_types:
    _zetSysmanRasGetErrors_t = WINFUNCTYPE( ze_result_t, zet_sysman_ras_handle_t, ze_bool_t, POINTER(c_ulonglong), POINTER(zet_ras_details_t) )
else:
    _zetSysmanRasGetErrors_t = CFUNCTYPE( ze_result_t, zet_sysman_ras_handle_t, ze_bool_t, POINTER(c_ulonglong), POINTER(zet_ras_details_t) )


###############################################################################
## @brief Table of SysmanRas functions pointers
class _zet_sysman_ras_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zetSysmanRasGetProperties_t
        ("pfnGetErrors", c_void_p)                                      ## _zetSysmanRasGetErrors_t
    ]

###############################################################################
## @brief Function-pointer for zetSysmanDiagnosticsGetProperties
if __use_win_types:
    _zetSysmanDiagnosticsGetProperties_t = WINFUNCTYPE( ze_result_t, zet_sysman_diag_handle_t, POINTER(zet_diag_properties_t) )
else:
    _zetSysmanDiagnosticsGetProperties_t = CFUNCTYPE( ze_result_t, zet_sysman_diag_handle_t, POINTER(zet_diag_properties_t) )

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
        ("pfnRunTests", c_void_p)                                       ## _zetSysmanDiagnosticsRunTests_t
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
        ("SysmanLinkSwitch", _zet_sysman_link_switch_dditable_t),
        ("SysmanLinkPort", _zet_sysman_link_port_dditable_t),
        ("SysmanTemperature", _zet_sysman_temperature_dditable_t),
        ("SysmanPsu", _zet_sysman_psu_dditable_t),
        ("SysmanFan", _zet_sysman_fan_dditable_t),
        ("SysmanLed", _zet_sysman_led_dditable_t),
        ("SysmanRas", _zet_sysman_ras_dditable_t),
        ("SysmanDiagnostics", _zet_sysman_diagnostics_dditable_t)
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
        self.zetSysmanSchedulerGetCurrentMode = _zetSysmanSchedulerGetCurrentMode_t(self.__dditable.Sysman.pfnSchedulerGetCurrentMode)
        self.zetSysmanSchedulerGetTimeoutModeProperties = _zetSysmanSchedulerGetTimeoutModeProperties_t(self.__dditable.Sysman.pfnSchedulerGetTimeoutModeProperties)
        self.zetSysmanSchedulerGetTimesliceModeProperties = _zetSysmanSchedulerGetTimesliceModeProperties_t(self.__dditable.Sysman.pfnSchedulerGetTimesliceModeProperties)
        self.zetSysmanSchedulerSetTimeoutMode = _zetSysmanSchedulerSetTimeoutMode_t(self.__dditable.Sysman.pfnSchedulerSetTimeoutMode)
        self.zetSysmanSchedulerSetTimesliceMode = _zetSysmanSchedulerSetTimesliceMode_t(self.__dditable.Sysman.pfnSchedulerSetTimesliceMode)
        self.zetSysmanSchedulerSetExclusiveMode = _zetSysmanSchedulerSetExclusiveMode_t(self.__dditable.Sysman.pfnSchedulerSetExclusiveMode)
        self.zetSysmanSchedulerSetComputeUnitDebugMode = _zetSysmanSchedulerSetComputeUnitDebugMode_t(self.__dditable.Sysman.pfnSchedulerSetComputeUnitDebugMode)
        self.zetSysmanDeviceReset = _zetSysmanDeviceReset_t(self.__dditable.Sysman.pfnDeviceReset)
        self.zetSysmanDeviceWasRepaired = _zetSysmanDeviceWasRepaired_t(self.__dditable.Sysman.pfnDeviceWasRepaired)
        self.zetSysmanPciGetProperties = _zetSysmanPciGetProperties_t(self.__dditable.Sysman.pfnPciGetProperties)
        self.zetSysmanPciGetState = _zetSysmanPciGetState_t(self.__dditable.Sysman.pfnPciGetState)
        self.zetSysmanPciGetBarProperties = _zetSysmanPciGetBarProperties_t(self.__dditable.Sysman.pfnPciGetBarProperties)
        self.zetSysmanPciGetThroughput = _zetSysmanPciGetThroughput_t(self.__dditable.Sysman.pfnPciGetThroughput)
        self.zetSysmanPciGetStats = _zetSysmanPciGetStats_t(self.__dditable.Sysman.pfnPciGetStats)
        self.zetSysmanPowerGet = _zetSysmanPowerGet_t(self.__dditable.Sysman.pfnPowerGet)
        self.zetSysmanFrequencyGet = _zetSysmanFrequencyGet_t(self.__dditable.Sysman.pfnFrequencyGet)
        self.zetSysmanEngineGet = _zetSysmanEngineGet_t(self.__dditable.Sysman.pfnEngineGet)
        self.zetSysmanStandbyGet = _zetSysmanStandbyGet_t(self.__dditable.Sysman.pfnStandbyGet)
        self.zetSysmanFirmwareGet = _zetSysmanFirmwareGet_t(self.__dditable.Sysman.pfnFirmwareGet)
        self.zetSysmanMemoryGet = _zetSysmanMemoryGet_t(self.__dditable.Sysman.pfnMemoryGet)
        self.zetSysmanLinkSwitchGet = _zetSysmanLinkSwitchGet_t(self.__dditable.Sysman.pfnLinkSwitchGet)
        self.zetSysmanTemperatureGet = _zetSysmanTemperatureGet_t(self.__dditable.Sysman.pfnTemperatureGet)
        self.zetSysmanPsuGet = _zetSysmanPsuGet_t(self.__dditable.Sysman.pfnPsuGet)
        self.zetSysmanFanGet = _zetSysmanFanGet_t(self.__dditable.Sysman.pfnFanGet)
        self.zetSysmanLedGet = _zetSysmanLedGet_t(self.__dditable.Sysman.pfnLedGet)
        self.zetSysmanRasGet = _zetSysmanRasGet_t(self.__dditable.Sysman.pfnRasGet)
        self.zetSysmanEventsGetProperties = _zetSysmanEventsGetProperties_t(self.__dditable.Sysman.pfnEventsGetProperties)
        self.zetSysmanEventsRegister = _zetSysmanEventsRegister_t(self.__dditable.Sysman.pfnEventsRegister)
        self.zetSysmanEventsUnregister = _zetSysmanEventsUnregister_t(self.__dditable.Sysman.pfnEventsUnregister)
        self.zetSysmanEventsListen = _zetSysmanEventsListen_t(self.__dditable.Sysman.pfnEventsListen)
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
        self.zetSysmanPowerGetEnergyThreshold = _zetSysmanPowerGetEnergyThreshold_t(self.__dditable.SysmanPower.pfnGetEnergyThreshold)
        self.zetSysmanPowerSetEnergyThreshold = _zetSysmanPowerSetEnergyThreshold_t(self.__dditable.SysmanPower.pfnSetEnergyThreshold)
        self.zetSysmanPowerGetLimits = _zetSysmanPowerGetLimits_t(self.__dditable.SysmanPower.pfnGetLimits)
        self.zetSysmanPowerSetLimits = _zetSysmanPowerSetLimits_t(self.__dditable.SysmanPower.pfnSetLimits)

        # call driver to get function pointers
        _SysmanFrequency = _zet_sysman_frequency_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanFrequencyProcAddrTable(version, byref(_SysmanFrequency)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFrequency = _SysmanFrequency

        # attach function interface to function address
        self.zetSysmanFrequencyGetLastOcError = _zetSysmanFrequencyGetLastOcError_t(self.__dditable.SysmanFrequency.pfnGetLastOcError)
        self.zetSysmanFrequencyGetOcCapabilities = _zetSysmanFrequencyGetOcCapabilities_t(self.__dditable.SysmanFrequency.pfnGetOcCapabilities)
        self.zetSysmanFrequencyGetOcConfig = _zetSysmanFrequencyGetOcConfig_t(self.__dditable.SysmanFrequency.pfnGetOcConfig)
        self.zetSysmanFrequencySetOcConfig = _zetSysmanFrequencySetOcConfig_t(self.__dditable.SysmanFrequency.pfnSetOcConfig)
        self.zetSysmanFrequencyGetOcIccMax = _zetSysmanFrequencyGetOcIccMax_t(self.__dditable.SysmanFrequency.pfnGetOcIccMax)
        self.zetSysmanFrequencySetOcIccMax = _zetSysmanFrequencySetOcIccMax_t(self.__dditable.SysmanFrequency.pfnSetOcIccMax)
        self.zetSysmanFrequencyGetOcTjMax = _zetSysmanFrequencyGetOcTjMax_t(self.__dditable.SysmanFrequency.pfnGetOcTjMax)
        self.zetSysmanFrequencySetOcTjMax = _zetSysmanFrequencySetOcTjMax_t(self.__dditable.SysmanFrequency.pfnSetOcTjMax)
        self.zetSysmanFrequencyGetProperties = _zetSysmanFrequencyGetProperties_t(self.__dditable.SysmanFrequency.pfnGetProperties)
        self.zetSysmanFrequencyGetRange = _zetSysmanFrequencyGetRange_t(self.__dditable.SysmanFrequency.pfnGetRange)
        self.zetSysmanFrequencySetRange = _zetSysmanFrequencySetRange_t(self.__dditable.SysmanFrequency.pfnSetRange)
        self.zetSysmanFrequencyGetState = _zetSysmanFrequencyGetState_t(self.__dditable.SysmanFrequency.pfnGetState)
        self.zetSysmanFrequencyGetThrottleTime = _zetSysmanFrequencyGetThrottleTime_t(self.__dditable.SysmanFrequency.pfnGetThrottleTime)

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
        self.zetSysmanMemoryGetBandwidth = _zetSysmanMemoryGetBandwidth_t(self.__dditable.SysmanMemory.pfnGetBandwidth)
        self.zetSysmanMemoryGetAllocated = _zetSysmanMemoryGetAllocated_t(self.__dditable.SysmanMemory.pfnGetAllocated)

        # call driver to get function pointers
        _SysmanLinkSwitch = _zet_sysman_link_switch_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanLinkSwitchProcAddrTable(version, byref(_SysmanLinkSwitch)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanLinkSwitch = _SysmanLinkSwitch

        # attach function interface to function address
        self.zetSysmanLinkSwitchGetProperties = _zetSysmanLinkSwitchGetProperties_t(self.__dditable.SysmanLinkSwitch.pfnGetProperties)
        self.zetSysmanLinkSwitchGetState = _zetSysmanLinkSwitchGetState_t(self.__dditable.SysmanLinkSwitch.pfnGetState)
        self.zetSysmanLinkSwitchSetState = _zetSysmanLinkSwitchSetState_t(self.__dditable.SysmanLinkSwitch.pfnSetState)
        self.zetSysmanLinkSwitchGetPorts = _zetSysmanLinkSwitchGetPorts_t(self.__dditable.SysmanLinkSwitch.pfnGetPorts)

        # call driver to get function pointers
        _SysmanLinkPort = _zet_sysman_link_port_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanLinkPortProcAddrTable(version, byref(_SysmanLinkPort)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanLinkPort = _SysmanLinkPort

        # attach function interface to function address
        self.zetSysmanLinkPortGetProperties = _zetSysmanLinkPortGetProperties_t(self.__dditable.SysmanLinkPort.pfnGetProperties)
        self.zetSysmanLinkPortGetState = _zetSysmanLinkPortGetState_t(self.__dditable.SysmanLinkPort.pfnGetState)
        self.zetSysmanLinkPortGetThroughput = _zetSysmanLinkPortGetThroughput_t(self.__dditable.SysmanLinkPort.pfnGetThroughput)
        self.zetSysmanLinkPortGetStats = _zetSysmanLinkPortGetStats_t(self.__dditable.SysmanLinkPort.pfnGetStats)
        self.zetSysmanLinkPortIsConnected = _zetSysmanLinkPortIsConnected_t(self.__dditable.SysmanLinkPort.pfnIsConnected)

        # call driver to get function pointers
        _SysmanTemperature = _zet_sysman_temperature_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanTemperatureProcAddrTable(version, byref(_SysmanTemperature)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanTemperature = _SysmanTemperature

        # attach function interface to function address
        self.zetSysmanTemperatureGetProperties = _zetSysmanTemperatureGetProperties_t(self.__dditable.SysmanTemperature.pfnGetProperties)
        self.zetSysmanTemperatureRead = _zetSysmanTemperatureRead_t(self.__dditable.SysmanTemperature.pfnRead)

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
        self.zetSysmanRasGetErrors = _zetSysmanRasGetErrors_t(self.__dditable.SysmanRas.pfnGetErrors)

        # call driver to get function pointers
        _SysmanDiagnostics = _zet_sysman_diagnostics_dditable_t()
        r = ze_result_v(self.__dll.zetGetSysmanDiagnosticsProcAddrTable(version, byref(_SysmanDiagnostics)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanDiagnostics = _SysmanDiagnostics

        # attach function interface to function address
        self.zetSysmanDiagnosticsGetProperties = _zetSysmanDiagnosticsGetProperties_t(self.__dditable.SysmanDiagnostics.pfnGetProperties)
        self.zetSysmanDiagnosticsRunTests = _zetSysmanDiagnosticsRunTests_t(self.__dditable.SysmanDiagnostics.pfnRunTests)

        # success!
