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
## @brief Handle of device group object
class xet_device_group_handle_t(c_void_p):
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
## @brief Handle of power object
class xet_power_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of a frequency domain on a device
class xet_freq_domain_handle_t(c_void_p):
    pass

###############################################################################
## @brief Maximum metric group name string size
XET_MAX_METRIC_GROUP_NAME = 256

###############################################################################
## @brief Maximum metric group description string size
XET_MAX_METRIC_GROUP_DESCRIPTION = 256

###############################################################################
## @brief Metric group sampling type
class xet_metric_group_sampling_type_t(c_int):
    pass

class xet_metric_group_sampling_type_v(IntEnum):
    EVENT_BASED = XE_BIT(0)                         ## Event based sampling
    TIME_BASED = XE_BIT(1)                          ## Time based sampling

###############################################################################
## @brief API version of ::xet_metric_group_properties_t
class xet_metric_group_properties_version_t(c_int):
    pass

class xet_metric_group_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

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
class xet_metric_type_t(c_int):
    pass

class xet_metric_type_v(IntEnum):
    DURATION = auto()                               ## Metric type: duration
    EVENT = auto()                                  ## Metric type: event
    EVENT_WITH_RANGE = auto()                       ## Metric type: event with range
    THROUGHPUT = auto()                             ## Metric type: throughput
    TIMESTAMP = auto()                              ## Metric type: timestamp
    FLAG = auto()                                   ## Metric type: flag
    RATIO = auto()                                  ## Metric type: ratio
    RAW = auto()                                    ## Metric type: raw

###############################################################################
## @brief Supported value types
class xet_value_type_t(c_int):
    pass

class xet_value_type_v(IntEnum):
    UINT32 = auto()                                 ## 32-bit unsigned-integer
    UINT64 = auto()                                 ## 64-bit unsigned-integer
    FLOAT32 = auto()                                ## 32-bit floating-point
    FLOAT64 = auto()                                ## 64-bit floating-point
    BOOL8 = auto()                                  ## 8-bit boolean

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
class xet_metric_properties_version_t(c_int):
    pass

class xet_metric_properties_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

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
class xet_metric_tracer_desc_version_t(c_int):
    pass

class xet_metric_tracer_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

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
class xet_metric_query_pool_desc_version_t(c_int):
    pass

class xet_metric_query_pool_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

###############################################################################
## @brief Metric query pool types
class xet_metric_query_pool_flag_t(c_int):
    pass

class xet_metric_query_pool_flag_v(IntEnum):
    PERFORMANCE = auto()                            ## Performance metric query pool.
    SKIP_EXECUTION = auto()                         ## Skips workload execution between begin/end calls.

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
class xet_module_debug_info_format_t(c_int):
    pass

class xet_module_debug_info_format_v(IntEnum):
    ELF_DWARF = auto()                              ## Format is ELF/DWARF

###############################################################################
## @brief API version of ::xet_profile_info_t
class xet_profile_info_version_t(c_int):
    pass

class xet_profile_info_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

###############################################################################
## @brief Supportted profile features
class xet_profile_flag_t(c_int):
    pass

class xet_profile_flag_v(IntEnum):
    REGISTER_REALLOCATION = XE_BIT(0)               ## request the compiler attempt to minimize register usage as much as
                                                    ## possible to allow for instrumentation
    FREE_REGISTER_INFO = XE_BIT(1)                  ## request the compiler generate free register info

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
class xet_profile_token_type_t(c_int):
    pass

class xet_profile_token_type_v(IntEnum):
    FREE_REGISTER = auto()                          ## GRF info

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
## @brief Power initialization flags (bitfield)
class xet_power_init_flags_t(c_int):
    pass

class xet_power_init_flags_v(IntEnum):
    NONE = 0                                        ## default initialization
    WRITE = XE_BIT( 0 )                             ## request access to power controls

###############################################################################
## @brief GPU domains
class xet_gpu_domain_t(c_int):
    pass

class xet_gpu_domain_v(IntEnum):
    BASE = XE_BIT( 0 )                              ## base die
    VIDEO_DECODE = XE_BIT( 1 )                      ## video decode engines
    VIDEO_ENCODE = XE_BIT( 2 )                      ## video encode engines
    VIDEO_PROCESSING = XE_BIT( 3 )                  ## video processing engines
    _3D_FIXED_FUNCTION = XE_BIT( 4 )                ## 3D fixed-function
    _3D_RENDER = XE_BIT( 5 )                        ## 3D programmable engines
    COMPUTE = XE_BIT( 6 )                           ## compute engines
    SYSTOLIC_ARRAY = XE_BIT( 7 )                    ## systolic array engines
    RAYTRACING = XE_BIT( 8 )                        ## raytracing engines
    LOCAL_MEMORY = XE_BIT( 9 )                      ## local memory
    BASE_CHIPLET_LINK = XE_BIT( 10 )                ## link between base die and chiplet

###############################################################################
## @brief API version of ::xet_power_average_limit_t
class xet_power_average_limit_version_t(c_int):
    pass

class xet_power_average_limit_version_v(IntEnum):
    AVERAGE_POWER_LIMIT_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 )   ## version 1.0

###############################################################################
## @brief Average power limit
## 
## @details
##     - The power controller (Punit) will throttle the operating frequency of
##       the device if the power averaged over a window (typically seconds)
##       exceeds a limit known as PL1.
class xet_power_average_limit_t(Structure):
    _fields_ = [
        ("version", xet_power_average_limit_version_t),                 ## [in] ::XET_AVERAGE_POWER_LIMIT_VERSION_CURRENT
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
## @brief All power limits
class xet_power_limits_t(Structure):
    _fields_ = [
        ("averagePowerLimit", xet_power_average_limit_t),               ## [in,out] average power limit information
        ("burstPowerLimit", xet_power_burst_limit_t),                   ## [in,out] burst power limit information
        ("peakPowerLimit", xet_power_peak_limit_t)                      ## [in,out] peak power limit information
    ]

###############################################################################
## @brief Turbo (dynamic hardware frequency management) modes
class xet_turbo_mode_t(c_int):
    pass

class xet_turbo_mode_v(IntEnum):
    DISABLED = 0                                    ## DVFS is currently disabled - frequency is fixed
    DEFAULT = auto()                                ## hardware default DVFS (typically EFFICIENT)
    MIN_PERFORMANCE = auto()                        ## min efficient frequency unless specific applications require otherwise
    EFFICIENT_PERFORMANCE = auto()                  ## balanced power and performance
    AGGRESSIVE_PERFORMANCE = auto()                 ## aggressively favor performance over power
    MAX_PERFORMANCE = auto()                        ## fixed max frequency unless limited by thermals/power

###############################################################################
## @brief Clock types
class xet_clock_type_t(c_int):
    pass

class xet_clock_type_v(IntEnum):
    FIXED = 0                                       ## fixed crystal clock
    PLL = auto()                                    ## phase-locked-loop (PLL) frequency range
    DIVIDER = auto()                                ## frequency is linked to another domain by a divider

###############################################################################
## @brief Frequency throttle reasons
class xet_freq_throttle_reasons_t(c_int):
    pass

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

###############################################################################
## @brief Properties of a frequency domain
## 
## @details
##     - A frequency domain contains one or more GPU functional blocks - see
##       ::xet_gpu_domain_t
##     - There is more than one type of clock - check clockType
##     - For clock type ::XET_CLOCK_TYPE_FIXED, minClock and maxClock will be
##       the same and numClockPoints will be 1.
##     - For clock type ::XET_CLOCK_TYPE_PLL, numClockPoints is given for
##       informational purposes. Do not assume the frequency step between
##       min/max clocks is (max - min) / (numClockPoints - 1). Instead, use the
##       function ::xetFreqDomainGetSupportedClocks to get the list of all
##       supported clocks between min/max.
##     - For clock type ::XET_CLOCK_TYPE_DIVIDER, the frequency of the domain
##       is given by multiplying the divider by the frequency of the source
##       domain. The possible divider values can be obtained using the function
##       ::xetFreqDomainGetSupportedClockDividers. For this clock type,
##       minClock/maxClock specifies the total range of frequencies whereas the
##       actual range depends on the current divider value.
class xet_freq_domain_properties_t(Structure):
    _fields_ = [
        ("gpuDomains", c_ulong),                                        ## [in] bitfield of xex_gpu_domain_t
        ("clockType", xet_clock_type_t),                                ## [in] clock type
        ("minClock", c_ulong),                                          ## [in] minimum frequency of the domain
        ("maxClock", c_ulong),                                          ## [in] maximum frequency of the domain
        ("numClockPoints", c_ulong),                                    ## [in] number of discrete clock points between and including min/max
        ("numClockDividers", c_ulong)                                   ## [in] for clock type ::XET_CLOCK_TYPE_DIVIDER, this gives the number of
                                                                        ## dividers available
    ]

###############################################################################
## @brief Frequency divider configuration
## 
## @details
##     - The frequency of a domain of type ::XET_CLOCK_TYPE_DIVIDER is obtained
##       by the formula:
##     - freq = source domain freq * numerator / denominator
class xet_clock_divider_t(Structure):
    _fields_ = [
        ("numerator", c_ushort),                                        ## [in,out] numerator of the ratio
        ("denominator", c_ushort)                                       ## [in,out] denominator of the ratio
    ]

###############################################################################
## @brief Fan capabilities
class xet_fan_capabilities_t(c_int):
    pass

class xet_fan_capabilities_v(IntEnum):
    GET_SPEED_PERCENTAGE = XE_BIT( 0 )              ## can query fan speed as a percentage
    SET_SPEED_PERCENTAGE = XE_BIT( 1 )              ## can set fan speed as a percentage
    GET_SPEED_RPM = XE_BIT( 2 )                     ## can query fan speed as rpm
    SET_SPEED_RPM = XE_BIT( 3 )                     ## can set fan speed as rpm
    HAVE_TEMPERATURE_SPEED_TABLE = XE_BIT( 4 )      ## can set temperature/fan speed table

###############################################################################
## @brief Fan speed modes
class xet_fan_speed_mode_t(c_int):
    pass

class xet_fan_speed_mode_v(IntEnum):
    AUTO = 0                                        ## fan speed is dynamically controlled based on temperature
    FIXED = auto()                                  ## fan speed is fixed

###############################################################################
## @brief Fan properties
class xet_fan_properties_t(Structure):
    _fields_ = [
        ("fanCapabilities", c_ulong),                                   ## [in] bitfield of ::xet_fan_capabilities_t
        ("maxRpm", c_ulong),                                            ## [in] maximum RPM of the fan. Will be 0 if maximum is not known.
        ("maxTemperatureSpeedPoints", c_ulong)                          ## [in] the maximum number of temperature/fan-speed points that can be
                                                                        ## programmed
    ]

###############################################################################
## @brief Temperature/fan-speed point
class xet_fan_point_t(Structure):
    _fields_ = [
        ("fanSpeedInRpm", xe_bool_t),                                   ## [in,out] false means fanSpeed is in percentage, true means fanSpeed is
                                                                        ## in RPM
        ("temperatureDegreesCentigrate", c_ushort),                     ## [in,out] temperature in degrees centigrate
        ("fanSpeed", c_ushort)                                          ## [in,out] the fan speed as a percentage (or RPM if fanSpeedInRpm is
                                                                        ## true)
    ]

###############################################################################
## @brief Fan speed info
class xet_fan_speed_info_t(Structure):
    _fields_ = [
        ("fanSpeedInRpm", xe_bool_t),                                   ## [in,out] false means fanSpeed is in percentage, true means fanSpeed is
                                                                        ## in RPM
        ("fanSpeedMode", xet_fan_speed_mode_t),                         ## [in,out] whether the fan speed is fixed or being controlled
                                                                        ## dynamically
        ("fanSpeed", c_ushort)                                          ## [in,out] the fan speed as a percentage (or RPM if fanSpeedInRpm is
                                                                        ## true)
    ]

###############################################################################
## @brief Temperature sensor properties
## 
## @details
##     - Temperature sensor index 0 is special - it is a virtual sensor that
##       gives the max across all sensors. The member **location** equals
##       0xFFFFFFFF in this case.
##     - Most systems apply the temperature threshold globally. In this case,
##       member **canChangeThreshold** will only be true for sensor index 0.
class xet_temperature_properties_t(Structure):
    _fields_ = [
        ("location", c_ulong),                                          ## [in] bitfield of ::xet_gpu_domain_t whose temperature is measured by
                                                                        ## this sensor
        ("maxTemperature", c_ushort),                                   ## [in] the temperature limit in celsius beyond which the power control
                                                                        ## unit (Punit) will throttle the frequency
        ("shutdownTemperature", c_ushort),                              ## [in] the temperature limit in celsius beyond which the power control
                                                                        ## unit (Punit) will shutdown the device
        ("canChangeThreshold", xe_bool_t)                               ## [in] true indicates that this a different threshold can be set
    ]

###############################################################################
## @brief Activity counter properties
## 
## @details
##     - Activity counter 0 is a normalized accumulation of activity across all
##       blocks. The member **blocks** equals 0xFFFFFFFF in this case.
class xet_activity_properties_t(Structure):
    _fields_ = [
        ("blocks", c_ulong)                                             ## [in] bitfield of ::xet_gpu_domain_t whose activity is included in this
                                                                        ## counter
    ]

###############################################################################
## @brief Activity counter data
## 
## @details
##     - Activity counter 0 is a normalized accumulation of activity across all
##       blocks.
##     - Samples these counters between two points and calculate utilization by
##       dividing delta(activityCounter) / delta(timeCounter).
##     - Powered down time is given by timeCounter - activityCounter -
##       idleCounter.
class xet_activity_counters_t(Structure):
    _fields_ = [
        ("activityCounter", c_ulonglong),                               ## [out] Monotonically increasing counter of activity in microseconds
        ("idleCounter", c_ulonglong),                                   ## [out] Monotonically increasing counter of time blocks are powered on
                                                                        ## but idle in microseconds
        ("timeCounter", c_ulonglong)                                    ## [out] Monotonically increasing counter of time in microseconds
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
class xet_tracer_desc_version_t(c_int):
    pass

class xet_tracer_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

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
    _xetMetricGroupGet_t = WINFUNCTYPE( xe_result_t, xet_device_group_handle_t, POINTER(c_ulong), POINTER(xet_metric_group_handle_t) )
else:
    _xetMetricGroupGet_t = CFUNCTYPE( xe_result_t, xet_device_group_handle_t, POINTER(c_ulong), POINTER(xet_metric_group_handle_t) )

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
    _xetTracerCreate_t = WINFUNCTYPE( xe_result_t, xet_device_group_handle_t, POINTER(xet_tracer_desc_t), POINTER(xet_tracer_handle_t) )
else:
    _xetTracerCreate_t = CFUNCTYPE( xe_result_t, xet_device_group_handle_t, POINTER(xet_tracer_desc_t), POINTER(xet_tracer_handle_t) )

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
## @brief Function-pointer for xetPowerCreate
if __use_win_types:
    _xetPowerCreate_t = WINFUNCTYPE( xe_result_t, xet_device_handle_t, c_ulong, POINTER(xet_power_handle_t) )
else:
    _xetPowerCreate_t = CFUNCTYPE( xe_result_t, xet_device_handle_t, c_ulong, POINTER(xet_power_handle_t) )

###############################################################################
## @brief Function-pointer for xetPowerDestroy
if __use_win_types:
    _xetPowerDestroy_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t )
else:
    _xetPowerDestroy_t = CFUNCTYPE( xe_result_t, xet_power_handle_t )

###############################################################################
## @brief Function-pointer for xetPowerGetAveragePowerLimit
if __use_win_types:
    _xetPowerGetAveragePowerLimit_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_average_limit_t) )
else:
    _xetPowerGetAveragePowerLimit_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_average_limit_t) )

###############################################################################
## @brief Function-pointer for xetPowerGetBurstPowerLimit
if __use_win_types:
    _xetPowerGetBurstPowerLimit_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_burst_limit_t) )
else:
    _xetPowerGetBurstPowerLimit_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_burst_limit_t) )

###############################################################################
## @brief Function-pointer for xetPowerGetPeakPowerLimit
if __use_win_types:
    _xetPowerGetPeakPowerLimit_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_peak_limit_t) )
else:
    _xetPowerGetPeakPowerLimit_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_peak_limit_t) )

###############################################################################
## @brief Function-pointer for xetPowerGetAllPowerLimits
if __use_win_types:
    _xetPowerGetAllPowerLimits_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_limits_t) )
else:
    _xetPowerGetAllPowerLimits_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_limits_t) )

###############################################################################
## @brief Function-pointer for xetPowerGetDefaultPowerLimits
if __use_win_types:
    _xetPowerGetDefaultPowerLimits_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_limits_t) )
else:
    _xetPowerGetDefaultPowerLimits_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_limits_t) )

###############################################################################
## @brief Function-pointer for xetPowerSetAveragePowerLimit
if __use_win_types:
    _xetPowerSetAveragePowerLimit_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_average_limit_t) )
else:
    _xetPowerSetAveragePowerLimit_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_average_limit_t) )

###############################################################################
## @brief Function-pointer for xetPowerSetBurstPowerLimit
if __use_win_types:
    _xetPowerSetBurstPowerLimit_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_burst_limit_t) )
else:
    _xetPowerSetBurstPowerLimit_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_burst_limit_t) )

###############################################################################
## @brief Function-pointer for xetPowerSetPeakPowerLimit
if __use_win_types:
    _xetPowerSetPeakPowerLimit_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_peak_limit_t) )
else:
    _xetPowerSetPeakPowerLimit_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_peak_limit_t) )

###############################################################################
## @brief Function-pointer for xetPowerSetPowerLimits
if __use_win_types:
    _xetPowerSetPowerLimits_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_limits_t) )
else:
    _xetPowerSetPowerLimits_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_power_limits_t) )

###############################################################################
## @brief Function-pointer for xetPowerGetEnergyCounter
if __use_win_types:
    _xetPowerGetEnergyCounter_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(c_ulonglong) )
else:
    _xetPowerGetEnergyCounter_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(c_ulonglong) )

###############################################################################
## @brief Function-pointer for xetPowerGetTurboMode
if __use_win_types:
    _xetPowerGetTurboMode_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_turbo_mode_t) )
else:
    _xetPowerGetTurboMode_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(xet_turbo_mode_t) )

###############################################################################
## @brief Function-pointer for xetPowerSetTurboMode
if __use_win_types:
    _xetPowerSetTurboMode_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, xet_turbo_mode_t )
else:
    _xetPowerSetTurboMode_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, xet_turbo_mode_t )

###############################################################################
## @brief Function-pointer for xetPowerFanCount
if __use_win_types:
    _xetPowerFanCount_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(c_ulong) )
else:
    _xetPowerFanCount_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetPowerFanGetProperties
if __use_win_types:
    _xetPowerFanGetProperties_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, POINTER(xet_fan_properties_t) )
else:
    _xetPowerFanGetProperties_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, POINTER(xet_fan_properties_t) )

###############################################################################
## @brief Function-pointer for xetPowerFanGetSpeedTable
if __use_win_types:
    _xetPowerFanGetSpeedTable_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, xe_bool_t, POINTER(c_ulong), POINTER(xet_fan_poc_int_t) )
else:
    _xetPowerFanGetSpeedTable_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, xe_bool_t, POINTER(c_ulong), POINTER(xet_fan_poc_int_t) )

###############################################################################
## @brief Function-pointer for xetPowerFanSetSpeedTable
if __use_win_types:
    _xetPowerFanSetSpeedTable_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ulong, POINTER(xet_fan_poc_int_t) )
else:
    _xetPowerFanSetSpeedTable_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ulong, POINTER(xet_fan_poc_int_t) )

###############################################################################
## @brief Function-pointer for xetPowerFanGetSpeed
if __use_win_types:
    _xetPowerFanGetSpeed_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ulong, xe_bool_t, POINTER(xet_fan_speed_info_t) )
else:
    _xetPowerFanGetSpeed_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ulong, xe_bool_t, POINTER(xet_fan_speed_info_t) )

###############################################################################
## @brief Function-pointer for xetPowerFanSetSpeed
if __use_win_types:
    _xetPowerFanSetSpeed_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ulong, POINTER(xet_fan_speed_info_t) )
else:
    _xetPowerFanSetSpeed_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ulong, POINTER(xet_fan_speed_info_t) )

###############################################################################
## @brief Function-pointer for xetPowerTemperatureSensorCount
if __use_win_types:
    _xetPowerTemperatureSensorCount_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(c_ulong) )
else:
    _xetPowerTemperatureSensorCount_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetPowerGetTemperatureProperties
if __use_win_types:
    _xetPowerGetTemperatureProperties_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, POINTER(xet_temperature_properties_t) )
else:
    _xetPowerGetTemperatureProperties_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, POINTER(xet_temperature_properties_t) )

###############################################################################
## @brief Function-pointer for xetPowerGetTemperature
if __use_win_types:
    _xetPowerGetTemperature_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ulong, POINTER(c_ushort) )
else:
    _xetPowerGetTemperature_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ulong, POINTER(c_ushort) )

###############################################################################
## @brief Function-pointer for xetPowerSetTemperatureThreshold
if __use_win_types:
    _xetPowerSetTemperatureThreshold_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ushort )
else:
    _xetPowerSetTemperatureThreshold_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ushort )

###############################################################################
## @brief Function-pointer for xetPowerActivityCount
if __use_win_types:
    _xetPowerActivityCount_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(c_ulong) )
else:
    _xetPowerActivityCount_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetPowerGetActivityProperties
if __use_win_types:
    _xetPowerGetActivityProperties_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, POINTER(xet_activity_properties_t) )
else:
    _xetPowerGetActivityProperties_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, POINTER(xet_activity_properties_t) )

###############################################################################
## @brief Function-pointer for xetPowerGetActivityCounters
if __use_win_types:
    _xetPowerGetActivityCounters_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ulong, POINTER(xet_activity_counters_t) )
else:
    _xetPowerGetActivityCounters_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, c_ulong, c_ulong, POINTER(xet_activity_counters_t) )


###############################################################################
## @brief Table of Power functions pointers
class _xet_power_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xetPowerCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xetPowerDestroy_t
        ("pfnGetAveragePowerLimit", c_void_p),                          ## _xetPowerGetAveragePowerLimit_t
        ("pfnGetBurstPowerLimit", c_void_p),                            ## _xetPowerGetBurstPowerLimit_t
        ("pfnGetPeakPowerLimit", c_void_p),                             ## _xetPowerGetPeakPowerLimit_t
        ("pfnGetAllPowerLimits", c_void_p),                             ## _xetPowerGetAllPowerLimits_t
        ("pfnGetDefaultPowerLimits", c_void_p),                         ## _xetPowerGetDefaultPowerLimits_t
        ("pfnSetAveragePowerLimit", c_void_p),                          ## _xetPowerSetAveragePowerLimit_t
        ("pfnSetBurstPowerLimit", c_void_p),                            ## _xetPowerSetBurstPowerLimit_t
        ("pfnSetPeakPowerLimit", c_void_p),                             ## _xetPowerSetPeakPowerLimit_t
        ("pfnSetPowerLimits", c_void_p),                                ## _xetPowerSetPowerLimits_t
        ("pfnGetEnergyCounter", c_void_p),                              ## _xetPowerGetEnergyCounter_t
        ("pfnGetTurboMode", c_void_p),                                  ## _xetPowerGetTurboMode_t
        ("pfnSetTurboMode", c_void_p),                                  ## _xetPowerSetTurboMode_t
        ("pfnFanCount", c_void_p),                                      ## _xetPowerFanCount_t
        ("pfnFanGetProperties", c_void_p),                              ## _xetPowerFanGetProperties_t
        ("pfnFanGetSpeedTable", c_void_p),                              ## _xetPowerFanGetSpeedTable_t
        ("pfnFanSetSpeedTable", c_void_p),                              ## _xetPowerFanSetSpeedTable_t
        ("pfnFanGetSpeed", c_void_p),                                   ## _xetPowerFanGetSpeed_t
        ("pfnFanSetSpeed", c_void_p),                                   ## _xetPowerFanSetSpeed_t
        ("pfnTemperatureSensorCount", c_void_p),                        ## _xetPowerTemperatureSensorCount_t
        ("pfnGetTemperatureProperties", c_void_p),                      ## _xetPowerGetTemperatureProperties_t
        ("pfnGetTemperature", c_void_p),                                ## _xetPowerGetTemperature_t
        ("pfnSetTemperatureThreshold", c_void_p),                       ## _xetPowerSetTemperatureThreshold_t
        ("pfnActivityCount", c_void_p),                                 ## _xetPowerActivityCount_t
        ("pfnGetActivityProperties", c_void_p),                         ## _xetPowerGetActivityProperties_t
        ("pfnGetActivityCounters", c_void_p)                            ## _xetPowerGetActivityCounters_t
    ]

###############################################################################
## @brief Function-pointer for xetFreqDomainGet
if __use_win_types:
    _xetFreqDomainGet_t = WINFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(c_ulong), POINTER(xet_freq_domain_handle_t) )
else:
    _xetFreqDomainGet_t = CFUNCTYPE( xe_result_t, xet_power_handle_t, POINTER(c_ulong), POINTER(xet_freq_domain_handle_t) )

###############################################################################
## @brief Function-pointer for xetFreqDomainGetProperties
if __use_win_types:
    _xetFreqDomainGetProperties_t = WINFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, POINTER(xet_freq_domain_properties_t) )
else:
    _xetFreqDomainGetProperties_t = CFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, POINTER(xet_freq_domain_properties_t) )

###############################################################################
## @brief Function-pointer for xetFreqDomainGetSourceFreqDomain
if __use_win_types:
    _xetFreqDomainGetSourceFreqDomain_t = WINFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, POINTER(xet_freq_domain_handle_t) )
else:
    _xetFreqDomainGetSourceFreqDomain_t = CFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, POINTER(xet_freq_domain_handle_t) )

###############################################################################
## @brief Function-pointer for xetFreqDomainGetSupportedClocks
if __use_win_types:
    _xetFreqDomainGetSupportedClocks_t = WINFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, c_ulong, POINTER(c_ulong) )
else:
    _xetFreqDomainGetSupportedClocks_t = CFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, c_ulong, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetFreqDomainGetSupportedClockDividers
if __use_win_types:
    _xetFreqDomainGetSupportedClockDividers_t = WINFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, c_ulong, POINTER(xet_clock_divider_t) )
else:
    _xetFreqDomainGetSupportedClockDividers_t = CFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, c_ulong, POINTER(xet_clock_divider_t) )

###############################################################################
## @brief Function-pointer for xetFreqDomainGetClockRange
if __use_win_types:
    _xetFreqDomainGetClockRange_t = WINFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, POINTER(c_ulong), POINTER(c_ulong) )
else:
    _xetFreqDomainGetClockRange_t = CFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, POINTER(c_ulong), POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetFreqDomainSetClockRange
if __use_win_types:
    _xetFreqDomainSetClockRange_t = WINFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, c_ulong, c_ulong )
else:
    _xetFreqDomainSetClockRange_t = CFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, c_ulong, c_ulong )

###############################################################################
## @brief Function-pointer for xetFreqDomainSetClockDivider
if __use_win_types:
    _xetFreqDomainSetClockDivider_t = WINFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, POINTER(xet_clock_divider_t) )
else:
    _xetFreqDomainSetClockDivider_t = CFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, POINTER(xet_clock_divider_t) )

###############################################################################
## @brief Function-pointer for xetFreqDomainGetCurrentFrequency
if __use_win_types:
    _xetFreqDomainGetCurrentFrequency_t = WINFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, POINTER(c_ulong), POINTER(c_ulong), POINTER(xet_freq_throttle_reasons_t) )
else:
    _xetFreqDomainGetCurrentFrequency_t = CFUNCTYPE( xe_result_t, xet_freq_domain_handle_t, POINTER(c_ulong), POINTER(c_ulong), POINTER(xet_freq_throttle_reasons_t) )


###############################################################################
## @brief Table of FreqDomain functions pointers
class _xet_freq_domain_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _xetFreqDomainGet_t
        ("pfnGetProperties", c_void_p),                                 ## _xetFreqDomainGetProperties_t
        ("pfnGetSourceFreqDomain", c_void_p),                           ## _xetFreqDomainGetSourceFreqDomain_t
        ("pfnGetSupportedClocks", c_void_p),                            ## _xetFreqDomainGetSupportedClocks_t
        ("pfnGetSupportedClockDividers", c_void_p),                     ## _xetFreqDomainGetSupportedClockDividers_t
        ("pfnGetClockRange", c_void_p),                                 ## _xetFreqDomainGetClockRange_t
        ("pfnSetClockRange", c_void_p),                                 ## _xetFreqDomainSetClockRange_t
        ("pfnSetClockDivider", c_void_p),                               ## _xetFreqDomainSetClockDivider_t
        ("pfnGetCurrentFrequency", c_void_p)                            ## _xetFreqDomainGetCurrentFrequency_t
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
        ("Power", _xet_power_dditable_t),
        ("FreqDomain", _xet_freq_domain_dditable_t)
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
        _Power = _xet_power_dditable_t()
        r = xe_result_v(self.__dll.xetGetPowerProcAddrTable(version, byref(_Power)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Power = _Power

        # attach function interface to function address
        self.xetPowerCreate = _xetPowerCreate_t(self.__dditable.Power.pfnCreate)
        self.xetPowerDestroy = _xetPowerDestroy_t(self.__dditable.Power.pfnDestroy)
        self.xetPowerGetAveragePowerLimit = _xetPowerGetAveragePowerLimit_t(self.__dditable.Power.pfnGetAveragePowerLimit)
        self.xetPowerGetBurstPowerLimit = _xetPowerGetBurstPowerLimit_t(self.__dditable.Power.pfnGetBurstPowerLimit)
        self.xetPowerGetPeakPowerLimit = _xetPowerGetPeakPowerLimit_t(self.__dditable.Power.pfnGetPeakPowerLimit)
        self.xetPowerGetAllPowerLimits = _xetPowerGetAllPowerLimits_t(self.__dditable.Power.pfnGetAllPowerLimits)
        self.xetPowerGetDefaultPowerLimits = _xetPowerGetDefaultPowerLimits_t(self.__dditable.Power.pfnGetDefaultPowerLimits)
        self.xetPowerSetAveragePowerLimit = _xetPowerSetAveragePowerLimit_t(self.__dditable.Power.pfnSetAveragePowerLimit)
        self.xetPowerSetBurstPowerLimit = _xetPowerSetBurstPowerLimit_t(self.__dditable.Power.pfnSetBurstPowerLimit)
        self.xetPowerSetPeakPowerLimit = _xetPowerSetPeakPowerLimit_t(self.__dditable.Power.pfnSetPeakPowerLimit)
        self.xetPowerSetPowerLimits = _xetPowerSetPowerLimits_t(self.__dditable.Power.pfnSetPowerLimits)
        self.xetPowerGetEnergyCounter = _xetPowerGetEnergyCounter_t(self.__dditable.Power.pfnGetEnergyCounter)
        self.xetPowerGetTurboMode = _xetPowerGetTurboMode_t(self.__dditable.Power.pfnGetTurboMode)
        self.xetPowerSetTurboMode = _xetPowerSetTurboMode_t(self.__dditable.Power.pfnSetTurboMode)
        self.xetPowerFanCount = _xetPowerFanCount_t(self.__dditable.Power.pfnFanCount)
        self.xetPowerFanGetProperties = _xetPowerFanGetProperties_t(self.__dditable.Power.pfnFanGetProperties)
        self.xetPowerFanGetSpeedTable = _xetPowerFanGetSpeedTable_t(self.__dditable.Power.pfnFanGetSpeedTable)
        self.xetPowerFanSetSpeedTable = _xetPowerFanSetSpeedTable_t(self.__dditable.Power.pfnFanSetSpeedTable)
        self.xetPowerFanGetSpeed = _xetPowerFanGetSpeed_t(self.__dditable.Power.pfnFanGetSpeed)
        self.xetPowerFanSetSpeed = _xetPowerFanSetSpeed_t(self.__dditable.Power.pfnFanSetSpeed)
        self.xetPowerTemperatureSensorCount = _xetPowerTemperatureSensorCount_t(self.__dditable.Power.pfnTemperatureSensorCount)
        self.xetPowerGetTemperatureProperties = _xetPowerGetTemperatureProperties_t(self.__dditable.Power.pfnGetTemperatureProperties)
        self.xetPowerGetTemperature = _xetPowerGetTemperature_t(self.__dditable.Power.pfnGetTemperature)
        self.xetPowerSetTemperatureThreshold = _xetPowerSetTemperatureThreshold_t(self.__dditable.Power.pfnSetTemperatureThreshold)
        self.xetPowerActivityCount = _xetPowerActivityCount_t(self.__dditable.Power.pfnActivityCount)
        self.xetPowerGetActivityProperties = _xetPowerGetActivityProperties_t(self.__dditable.Power.pfnGetActivityProperties)
        self.xetPowerGetActivityCounters = _xetPowerGetActivityCounters_t(self.__dditable.Power.pfnGetActivityCounters)

        # call driver to get function pointers
        _FreqDomain = _xet_freq_domain_dditable_t()
        r = xe_result_v(self.__dll.xetGetFreqDomainProcAddrTable(version, byref(_FreqDomain)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.FreqDomain = _FreqDomain

        # attach function interface to function address
        self.xetFreqDomainGet = _xetFreqDomainGet_t(self.__dditable.FreqDomain.pfnGet)
        self.xetFreqDomainGetProperties = _xetFreqDomainGetProperties_t(self.__dditable.FreqDomain.pfnGetProperties)
        self.xetFreqDomainGetSourceFreqDomain = _xetFreqDomainGetSourceFreqDomain_t(self.__dditable.FreqDomain.pfnGetSourceFreqDomain)
        self.xetFreqDomainGetSupportedClocks = _xetFreqDomainGetSupportedClocks_t(self.__dditable.FreqDomain.pfnGetSupportedClocks)
        self.xetFreqDomainGetSupportedClockDividers = _xetFreqDomainGetSupportedClockDividers_t(self.__dditable.FreqDomain.pfnGetSupportedClockDividers)
        self.xetFreqDomainGetClockRange = _xetFreqDomainGetClockRange_t(self.__dditable.FreqDomain.pfnGetClockRange)
        self.xetFreqDomainSetClockRange = _xetFreqDomainSetClockRange_t(self.__dditable.FreqDomain.pfnSetClockRange)
        self.xetFreqDomainSetClockDivider = _xetFreqDomainSetClockDivider_t(self.__dditable.FreqDomain.pfnSetClockDivider)
        self.xetFreqDomainGetCurrentFrequency = _xetFreqDomainGetCurrentFrequency_t(self.__dditable.FreqDomain.pfnGetCurrentFrequency)

        # success!
