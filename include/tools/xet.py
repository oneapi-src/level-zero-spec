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
## @brief Handle for accessing System Resource Management features
class xet_sysman_handle_t(c_void_p):
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
## @brief Resource types
class xet_resource_type_v(IntEnum):
    DEV = 0x0                                       ## Inventory resource
    PWR = 0x1                                       ## Power domain resource
    FREQ = 0x2                                      ## Frequency domain resource
    UTIL = 0x3                                      ## Resource used to monitor GPU utilization
    MEM = 0x4                                       ## Memory resource
    LINK = 0x5                                      ## Link resource
    TEMP = 0x6                                      ## Temperature sensor resource
    STBY = 0x7                                      ## Resource used to control standby mode
    FW = 0x8                                        ## Firmware resource
    PSU = 0x9                                       ## PSU resource
    FAN = 0xA                                       ## Fan resource
    LED = 0xB                                       ## LED resource
    ANY = -1                                        ## Any resource filter

class xet_resource_type_t(c_int):
    def __str__(self):
        return str(xet_resource_type_v(value))


###############################################################################
## @brief Resource ID
## 
## @details
##     - Every resource in the system has a unique identify.
##     - Resource IDs will always have the same value between versions of the
##       API.
##     - Never assume that resources of the same type have numerically
##       sequential values.
##     - The resource ID has the resource type (::xet_resource_type_t) in the
##       upper 16 bits.
class xet_resid_v(IntEnum):
    DEV_INVENTORY = 0                               ## General device inventory
    PWR_TOTAL = 0x10000                             ## Device total power
    FREQ_GPU = 0x20000                              ## GPU frequency
    FREQ_LOCAL_MEM = 0x20001                        ## Local memory frequency
    UTIL_GPU = 0x30000                              ## Utilization of the entire GPU
    UTIL_COMPUTE = 0x30001                          ## Utilization of the compute/3D units
    UTIL_MEDIA = 0x30002                            ## Utilization of the media units
    UTIL_VIDEO_DECODE = 0x30003                     ## Utilization of the video decode units
    UTIL_VIDEO_ENCODE = 0x30004                     ## Utilization of the video encode units
    MEM_LOCAL = 0x40000                             ## Local GPU memory
    LINK_PCIE = 0x50000                             ## PCIe link
    LINK_CD_PORT1 = 0x50001                         ## High speed companion die switch port 1
    LINK_CD_PORT2 = 0x50002                         ## High speed companion die switch port 2
    LINK_CD_PORT3 = 0x50003                         ## High speed companion die switch port 3
    LINK_CD_PORT4 = 0x50004                         ## High speed companion die switch port 4
    LINK_CD_PORT5 = 0x50005                         ## High speed companion die switch port 5
    LINK_CD_PORT6 = 0x50006                         ## High speed companion die switch port 6
    LINK_CD_PORT7 = 0x50007                         ## High speed companion die switch port 7
    LINK_CD_PORT8 = 0x50008                         ## High speed companion die switch port 8
    LINK_CD_PORT9 = 0x50009                         ## High speed companion die switch port 9
    LINK_CD_PORT10 = 0x5000A                        ## High speed companion die switch port 10
    LINK_CD_PORT11 = 0x5000B                        ## High speed companion die switch port 11
    LINK_CD_PORT12 = 0x5000C                        ## High speed companion die switch port 12
    LINK_CD_PORT13 = 0x5000D                        ## High speed companion die switch port 13
    LINK_CD_PORT14 = 0x5000E                        ## High speed companion die switch port 14
    LINK_CD_PORT15 = 0x5000F                        ## High speed companion die switch port 15
    LINK_CD_PORT16 = 0x50010                        ## High speed companion die switch port 16
    TEMP_MAX = 0x60000                              ## The maximum temperature reported by the sensors in the device
    TEMP_GPU = 0x60001                              ## The maximum temperature reported by the sensors in the GPU component
                                                    ## of the device
    TEMP_LOCAL_MEM = 0x60002                        ## The maximum temperature reported by the sensors in the local memory of
                                                    ## device
    STBY_GLOBAL = 0x70000                           ## Control sleep promotion of the common parts of the device
    STBY_COMPUTE = 0x70001                          ## Control sleep promotion of the compute components of the GPU
    STBY_MEDIA = 0x70002                            ## Control sleep promotion of the media components of the GPU
    FW_1 = 0x80001                                  ## Firmware 1
    FW_2 = 0x80002                                  ## Firmware 2
    FW_3 = 0x80003                                  ## Firmware 3
    FW_4 = 0x80004                                  ## Firmware 4
    FW_5 = 0x80005                                  ## Firmware 5
    FW_6 = 0x80006                                  ## Firmware 6
    FW_7 = 0x80007                                  ## Firmware 7
    FW_8 = 0x80008                                  ## Firmware 8
    FW_9 = 0x80009                                  ## Firmware 9
    FW_10 = 0x8000A                                 ## Firmware 10
    FW_11 = 0x8000B                                 ## Firmware 11
    FW_12 = 0x8000C                                 ## Firmware 12
    FW_13 = 0x8000D                                 ## Firmware 13
    FW_14 = 0x8000E                                 ## Firmware 14
    FW_15 = 0x8000F                                 ## Firmware 15
    FW_16 = 0x80010                                 ## Firmware 16
    FW_17 = 0x80011                                 ## Firmware 17
    FW_18 = 0x80012                                 ## Firmware 18
    FW_19 = 0x80013                                 ## Firmware 19
    FW_20 = 0x80014                                 ## Firmware 20
    PSU_MAIN = 0x90000                              ## Primary power supply
    PSU_AUX = 0x90001                               ## Auxilary power supply
    PSU_1 = 0x90002                                 ## Power supply 1
    PSU_2 = 0x90003                                 ## Power supply 2
    FAN_MAIN = 0xA0000                              ## The main fan
    FAN_1 = 0xA0001                                 ## Fan 1
    FAN_2 = 0xA0002                                 ## Fan 2
    FAN_3 = 0xA0003                                 ## Fan 3
    LED_MAIN = 0xB0000                              ## The main LED
    LED_1 = 0xB0001                                 ## LED 1
    LED_2 = 0xB0002                                 ## LED 1
    LED_3 = 0xB0003                                 ## LED 1
    ANY = -1                                        ## Any resource ID

class xet_resid_t(c_int):
    def __str__(self):
        return str(xet_resid_v(value))


###############################################################################
## @brief Resource properties
## 
## @details
##     - For every property, there is a corresponding structure used to hold
##       the property data. The type of the data structure is derived from the
##       property enumerator, converted to lower-case with '_t' appended.
##     - Properties can be either read-only (ro), write-only (wo) or read-write
##       (rw).
##     - Properties can be either static or dynamic. Static properties are set
##       during initialization and will not change during the lifetime of the
##       application. Dynamic properties can change at any time and should be
##       reread.
class xet_resprop_v(IntEnum):
    DEV_SERIAL_NUMBER = 0x00000                     ## (ro static) The serial number of the device (data:
                                                    ## ::xet_resprop_dev_serial_number_t)
    DEV_BOARD_NUMBER = 0x00001                      ## (ro static) The board number of the device (data:
                                                    ## ::xet_resprop_dev_board_number_t)
    DEV_BRAND = 0x00002                             ## (ro static) The brand name of the device (data:
                                                    ## ::xet_resprop_dev_brand_t)
    DEV_MODEL = 0x00003                             ## (ro static) The model name of the device (data:
                                                    ## ::xet_resprop_dev_model_t)
    DEV_DEVICEID = 0x00004                          ## (ro static) The device ID of the device (data:
                                                    ## ::xet_resprop_dev_deviceid_t)
    DEV_VENDOR_NAME = 0x00005                       ## (ro static) The vendor name of the device (data:
                                                    ## ::xet_resprop_dev_vendor_name_t)
    DEV_DRIVER_VERSION = 0x00006                    ## (ro static) The driver version associated with the device (data:
                                                    ## ::xet_resprop_dev_driver_version_t)
    DEV_BARS = 0x00007                              ## (ro static) The bars configured for the device (data:
                                                    ## ::xet_resprop_dev_bars_t)
    PWR_MAX_LIMIT = 0x10000                         ## (ro static) The maximum power limit that can be requested (data:
                                                    ## ::xet_resprop_pwr_max_limit_t)
    PWR_ENERGY_COUNTER = 0x10001                    ## (ro dynamic) The value of the monotonic energy counter (data:
                                                    ## ::xet_resprop_pwr_energy_counter_t)
    PWR_SUSTAINED_LIMIT = 0x10002                   ## (rw dynamic) The sustained power limit (data:
                                                    ## ::xet_resprop_pwr_sustained_limit_t)
    PWR_BURST_LIMIT = 0x10003                       ## (rw dynamic) The burst power limit (data:
                                                    ## ::xet_resprop_pwr_burst_limit_t)
    PWR_PEAK_LIMIT = 0x10004                        ## (rw dynamic) The peak power limit (data:
                                                    ## ::xet_resprop_pwr_peak_limit_t)
    FREQ_AVAIL_CLOCKS = 0x20000                     ## (ro static) Available frequency clocks that this domain can run at
                                                    ## (data: ::xet_resprop_freq_avail_clocks_t)
    FREQ_RANGE = 0x20001                            ## (rw dynamic) The current frequency range (data:
                                                    ## ::xet_resprop_freq_range_t)
    FREQ_REQUESTED_FREQ = 0x20002                   ## (ro dynamic) The current frequency request (data:
                                                    ## ::xet_resprop_freq_requested_freq_t)
    FREQ_TDP_FREQ = 0x20003                         ## (ro dynamic) The maximum frequency supported under the current TDP
                                                    ## conditions (data: ::xet_resprop_freq_tdp_freq_t)
    FREQ_EFFICIENT_FREQ = 0x20004                   ## (ro dynamic) The efficient minimum frequency (data:
                                                    ## ::xet_resprop_freq_efficient_freq_t)
    FREQ_RESOLVED_FREQ = 0x20005                    ## (ro dynamic) The resolved frequency (data:
                                                    ## ::xet_resprop_freq_resolved_freq_t)
    FREQ_THROTTLE_REASONS = 0x20006                 ## (ro dynamic) The reasons that the frequency is being limited by the
                                                    ## PCU (data: ::xet_resprop_freq_throttle_reasons_t)
    FREQ_THROTTLE_TIME = 0x20007                    ## (ro dynamic) The total time that the frequency has been limited by the
                                                    ## PCU (data: ::xet_resprop_freq_throttle_time_t)
    UTIL_COUNTERS = 0x30000                         ## (ro dynamic) The total wall time this resource is active (data:
                                                    ## ::xet_resprop_util_counters_t)
    MEM_TYPE = 0x40000                              ## (ro static) The type of memory covered by this resource (data:
                                                    ## ::xet_resprop_mem_type_t)
    MEM_UTILIZATION = 0x40001                       ## (ro dynamic) Get current allocated/unallocated size (data:
                                                    ## ::xet_resprop_mem_utilization_t)
    MEM_BANDWIDTH = 0x40002                         ## (ro dynamic) Get current read/write bandwidth counters and maximum
                                                    ## bandwidth (data: ::xet_resprop_mem_bandwidth_t)
    LINK_TYPE = 0x50000                             ## (ro static) The type of link (data: ::xet_resprop_link_type_t)
    LINK_BUS_ADDRESS = 0x50001                      ## (ro static) The bus address of the link (data:
                                                    ## ::xet_resprop_link_bus_address_t)
    LINK_PEER_DEVICE = 0x50002                      ## (ro static) For links of type ::XET_LINK_TYPE_CD_PORT, this gives the
                                                    ## UUID of the peer device (data: ::xet_resprop_link_peer_device_t)
    LINK_AVAIL_SPEEDS = 0x50003                     ## (ro static) Available link speeds (data:
                                                    ## ::xet_resprop_link_avail_speeds_t)
    LINK_MAX_PACKET_SIZE = 0x50004                  ## (ro static) Maximum packet size (data:
                                                    ## ::xet_resprop_link_max_packet_size_t)
    LINK_STATE = 0x50005                            ## (rw dynamic) Link state (enabled/disabled) (data:
                                                    ## ::xet_resprop_link_state_t)
    LINK_BANDWIDTH = 0x50006                        ## (ro dynamic) Monotonic bandwidth counters (data:
                                                    ## ::xet_resprop_link_bandwidth_t)
    LINK_SPEED = 0x50007                            ## (ro dynamic) Current link speed (data: ::xet_resprop_link_speed_t)
    LINK_SPEED_RANGE = 0x50008                      ## (wo dynamic) Set the min/max speeds between which the link can operate
                                                    ## (data: ::xet_resprop_link_speed_range_t)
    TEMP_TEMPERATURE = 0x60000                      ## (ro dynamic) The current temperature of the sensor in degrees celcius
                                                    ## (data: ::xet_resprop_temp_temperature_t)
    STBY_PROMO_MODE = 0x70000                       ## (rw dynamic) The current promotion mode (data:
                                                    ## ::xet_resprop_stby_promo_mode_t)
    FW_NAME = 0x80000                               ## (ro static) Name encoded in the loaded firmware image (data:
                                                    ## ::xet_resprop_fw_name_t)
    FW_VERSION = 0x80001                            ## (ro static) The version of the loaded firmware image (data:
                                                    ## ::xet_resprop_fw_version_t)
    FW_CHECK = 0x80002                              ## (ro dynamic) Verify the checksum of the loaded firmware image (data:
                                                    ## ::xet_resprop_fw_check_t)
    FW_FLASH = 0x80003                              ## (wo dynamically) Flash a new firmware image (data:
                                                    ## ::xet_resprop_fw_flash_t)
    PSU_AMP_LIMIT = 0x90000                         ## (ro static) The maximum electrical current in amperes that can be
                                                    ## drawn (data: ::xet_resprop_psu_amp_limit_t)
    PSU_VOLTAGE_STATUS = 0x90001                    ## (ro dynamic) Indicates if under or over voltage has occurred (data:
                                                    ## ::xet_resprop_psu_voltage_status_t)
    PSU_FAN_FAILURE = 0x90002                       ## (ro dynamic) Indicates if the fan has failed (data:
                                                    ## ::xet_resprop_psu_fan_failure_t)
    PSU_TEMPERATURE = 0x90003                       ## (ro dynamic) The current heatsink temperature in degrees celcius
                                                    ## (data: ::xet_resprop_psu_temperature_t)
    PSU_AMPS = 0x90004                              ## (ro dynamic) The current amps being drawn in amperes (data:
                                                    ## ::xet_resprop_psu_amps_t)
    FAN_MAX_RPM = 0xA0000                           ## (ro static) The maximum RPM of the fan (data:
                                                    ## ::xet_resprop_fan_max_rpm_t)
    FAN_MAX_TABLE_SIZE = 0xA0001                    ## (ro static) The maximum number of points in the fan temp/speed table
                                                    ## (data: ::xet_resprop_fan_max_table_size_t)
    FAN_SPEED_RPM = 0xA0002                         ## (ro dynamic) The current fan speed in units of revolutions per minute
                                                    ## (rpm) (data: ::xet_resprop_fan_speed_rpm_t)
    FAN_SPEED_PERCENT = 0xA0003                     ## (ro dynamic) The current fan speed as a percentage of the maximum
                                                    ## speed of that fan (data: ::xet_resprop_fan_speed_percent_t)
    FAN_MODE = 0xA0004                              ## (ro dynamic) The current fan speed mode (one of
                                                    ## ::xet_fan_speed_mode_t) (data: ::xet_resprop_fan_mode_t)
    FAN_FIXED_SPEED = 0xA0005                       ## (rw dynamic) Read/write the fixed speed setting for the fan (data:
                                                    ## ::xet_resprop_fan_fixed_speed_t)
    FAN_SPEED_TABLE = 0xA0006                       ## (rw dynamic) Read/write the fan speed table (data:
                                                    ## ::xet_resprop_fan_speed_table_t)
    LED_RGB_CAP = 0xB0000                           ## (ro static) Indicates if the LED is RGB capable (data:
                                                    ## ::xet_resprop_led_rgb_cap_t)
    LED_STATE = 0xB0001                             ## (rw dynaic) The LED state - on/off and color (data:
                                                    ## ::xet_resprop_led_state_t)

class xet_resprop_t(c_int):
    def __str__(self):
        return str(xet_resprop_v(value))


###############################################################################
## @brief Maximum number of characters in string properties.
XET_STRING_PROPERTY_SIZE = 32

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
## @brief Data for a PCI bar
class xet_pci_bar_info_t(Structure):
    _fields_ = [
        ("type", xet_pci_bar_type_t),                                   ## [out] The type of bar
        ("base", c_ulonglong),                                          ## [out] Base address of the bar.
        ("size", c_ulonglong)                                           ## [out] Size of the bar.
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_DEV_SERIAL_NUMBER
class xet_resprop_dev_serial_number_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_DEV_BOARD_NUMBER
class xet_resprop_dev_board_number_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_DEV_BRAND
class xet_resprop_dev_brand_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_DEV_MODEL
class xet_resprop_dev_model_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_DEV_DEVICEID
class xet_resprop_dev_deviceid_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_DEV_VENDOR_NAME
class xet_resprop_dev_vendor_name_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_DEV_DRIVER_VERSION
class xet_resprop_dev_driver_version_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_DEV_BARS
class xet_resprop_dev_bars_t(Structure):
    _fields_ = [
        ("num", c_ulong),                                               ## [out] The number of bars
        ("pBars", POINTER(xet_pci_bar_info_t))                          ## [out][range(0, num-1)] Information about each bar.
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_PWR_MAX_LIMIT
class xet_resprop_pwr_max_limit_t(Structure):
    _fields_ = [
        ("limit", c_ulong)                                              ## [out] The maximum power limit in milliwatts that can be requested.
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_PWR_ENERGY_COUNTER
class xet_resprop_pwr_energy_counter_t(Structure):
    _fields_ = [
        ("energy", c_ulonglong)                                         ## [out] The value of the monotonic energy counter in millijoules.
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_PWR_SUSTAINED_LIMIT
## 
## @details
##     - The power controller (Punit) will throttle the operating frequency if
##       the power averaged over a window (typically seconds) exceeds this
##       limit.
class xet_resprop_pwr_sustained_limit_t(Structure):
    _fields_ = [
        ("enabled", xe_bool_t),                                         ## [in,out] indicates if the limit is enabled (true) or ignored (false)
        ("power", c_ulong),                                             ## [in,out] power limit in milliwatts
        ("interval", c_ulong)                                           ## [in,out] power averaging window (Tau) in milliseconds
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_PWR_BURST_LIMIT
## 
## @details
##     - The power controller (Punit) will throttle the operating frequency of
##       the device if the power averaged over a few milliseconds exceeds a
##       limit known as PL2. Typically PL2 > PL1 so that it permits the
##       frequency to burst higher for short periods than would be otherwise
##       permitted by PL1.
class xet_resprop_pwr_burst_limit_t(Structure):
    _fields_ = [
        ("enabled", xe_bool_t),                                         ## [in,out] indicates if the limit is enabled (true) or ignored (false)
        ("power", c_ulong)                                              ## [in,out] power limit in milliwatts
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_PWR_PEAK_LIMIT
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
class xet_resprop_pwr_peak_limit_t(Structure):
    _fields_ = [
        ("power", c_ulong)                                              ## [in,out] power limit in milliwatts
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
## @brief Data for the property ::XET_RESPROP_FREQ_AVAIL_CLOCKS
## 
## @details
##     - Provides the set of frequencies as a list and as a range/step.
##     - It is generally recommended that applications choose frequencies from
##       the list. However applications can also construct the list themselves
##       using the range/steps provided.
class xet_resprop_freq_avail_clocks_t(Structure):
    _fields_ = [
        ("min", c_double),                                              ## [out] The minimum clock frequency in units of MHz
        ("max", c_double),                                              ## [out] The maximum clock frequency in units of MHz
        ("step", c_double),                                             ## [out] The step clock frequency in units of MHz
        ("num", c_ulong),                                               ## [out] The number of clocks
        ("pClocks", POINTER(c_double))                                  ## [out] Array of clock frequencies in units of MHz ordered from smallest
                                                                        ## to largest.
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FREQ_RANGE
class xet_resprop_freq_range_t(Structure):
    _fields_ = [
        ("min", c_double),                                              ## [in,out] The min frequency in MHz below which hardware frequency
                                                                        ## management will not request frequencies. Setting to 0 will return the
                                                                        ## hardware default value.
        ("max", c_double)                                               ## [in,out] The max frequency in MHz above which hardware frequency
                                                                        ## management will not request frequencies. Setting to 0 will return the
                                                                        ## hardware default value.
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FREQ_REQUESTED_FREQ
class xet_resprop_freq_requested_freq_t(Structure):
    _fields_ = [
        ("freqRequest", c_double)                                       ## [out] The current frequency request in MHz.
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FREQ_TDP_FREQ
class xet_resprop_freq_tdp_freq_t(Structure):
    _fields_ = [
        ("freqTdp", c_double)                                           ## [out] The maximum frequency in MHz supported under the current TDP
                                                                        ## conditions
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FREQ_EFFICIENT_FREQ
class xet_resprop_freq_efficient_freq_t(Structure):
    _fields_ = [
        ("freqEfficient", c_double)                                     ## [out] The efficient minimum frequency in MHz
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FREQ_RESOLVED_FREQ
class xet_resprop_freq_resolved_freq_t(Structure):
    _fields_ = [
        ("freqResolved", c_double)                                      ## [out] The resolved frequency in MHz
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FREQ_THROTTLE_REASONS
class xet_resprop_freq_throttle_reasons_t(Structure):
    _fields_ = [
        ("throttleReasons", c_ulong)                                    ## [out] The reasons that the frequency is being limited by the PCU
                                                                        ## (Bitfield of (1<<::xet_freq_throttle_reasons_t)).
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FREQ_THROTTLE_TIME
class xet_resprop_freq_throttle_time_t(Structure):
    _fields_ = [
        ("throttleTime", c_ulong)                                       ## [out] The total time in microseconds that the frequency has been
                                                                        ## limited by the PCU.
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_UTIL_COUNTERS
## 
## @details
##     - Percentage utilization is given by the equation: 100 *
##       delta(activeCounter) / ( delta(activeCounter) + delta(idleCounter) ).
class xet_resprop_util_counters_t(Structure):
    _fields_ = [
        ("activeCounter", c_ulong),                                     ## [out] Monotonic counter for total wall time in microseconds that this
                                                                        ## resource is actively running workloads.
        ("idleCounter", c_ulong)                                        ## [out] Monotonic counter for total wall time in microseconds that this
                                                                        ## resource is not actively running any workloads.
    ]

###############################################################################
## @brief Memory resource types
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
## @brief Data for the property ::XET_RESPROP_MEM_TYPE
class xet_resprop_mem_type_t(Structure):
    _fields_ = [
        ("type", xet_mem_type_t)                                        ## [out] The memory type
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_MEM_UTILIZATION
## 
## @details
##     - The total physical memory is the sum of all others (stolen + bad +
##       allocated + unallocated).
##     - Percent software memory utilization given by 100 * allocated /
##       (allocated + unallocated).
##     - Percent bad memory given by 100 * bad / total
class xet_resprop_mem_utilization_t(Structure):
    _fields_ = [
        ("total", c_ulonglong),                                         ## [out] The total physical memory in bytes
        ("stolen", c_ulonglong),                                        ## [out] The total stolen memory in bytes
        ("bad", c_ulonglong),                                           ## [out] The total bad memory in bytes
        ("allocated", c_ulonglong),                                     ## [out] The total allocated bytes
        ("unallocated", c_ulonglong)                                    ## [out] The total unallocated bytes
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_MEM_BANDWIDTH
class xet_resprop_mem_bandwidth_t(Structure):
    _fields_ = [
        ("readCounter", c_ulong),                                       ## [out] Total bytes read from memory
        ("writeCounter", c_ulong),                                      ## [out] Total bytes written to memory
        ("maxBandwidth", c_ulong)                                       ## [out] Current maximum bandwidth in units of bytes/sec
    ]

###############################################################################
## @brief Link resource types
class xet_link_type_v(IntEnum):
    PCI = 0                                         ## PCI connection
    CD_PORT = auto()                                ## Companion die physical port

class xet_link_type_t(c_int):
    def __str__(self):
        return str(xet_link_type_v(value))


###############################################################################
## @brief Link speed element
class xet_link_speed_t(Structure):
    _fields_ = [
        ("numLanes", c_ulong),                                          ## [out] The number of lanes used by the link
        ("speed", c_ulong),                                             ## [out] The frequency of the link in units of MHz
        ("bandwidth", c_ulong)                                          ## [out] The maximum bandwidth in units of bytes/sec
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_LINK_TYPE
class xet_resprop_link_type_t(Structure):
    _fields_ = [
        ("type", xet_link_type_t)                                       ## [out] The type of link
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_LINK_BUS_ADDRESS
class xet_resprop_link_bus_address_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_LINK_PEER_DEVICE
class xet_resprop_link_peer_device_t(Structure):
    _fields_ = [
        ("uuid", xe_device_uuid_t)                                      ## [out] UUID of the peer device connected to through this link
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_LINK_AVAIL_SPEEDS
## 
## @details
##     - The list is ordered from the smallest ratio to the largest ratio.
class xet_resprop_link_avail_speeds_t(Structure):
    _fields_ = [
        ("num", c_ulong),                                               ## [out] The number of elements in pList
        ("pList", POINTER(xet_link_speed_t))                            ## [out][range(0, num-1)] Pointer to an array of link speeds
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_LINK_STATE
class xet_resprop_link_state_t(Structure):
    _fields_ = [
        ("enable", xe_bool_t)                                           ## [out] Indicates if the link is disabled/endabled.
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_LINK_MAX_PACKET_SIZE
class xet_resprop_link_max_packet_size_t(Structure):
    _fields_ = [
        ("maxPacketSize", c_ulong)                                      ## [out] Maximum packet size in bytes.
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_LINK_BANDWIDTH
class xet_resprop_link_bandwidth_t(Structure):
    _fields_ = [
        ("recvCounter", c_ulong),                                       ## [out] Total bytes received across the link
        ("sendCounter", c_ulong),                                       ## [out] Total bytes sent across the link
        ("maxBandwidth", c_ulong)                                       ## [out] Maximum bytes/sec that can be transfered acros the link
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_LINK_SPEED
class xet_resprop_link_speed_t(Structure):
    _fields_ = [
        ("pSpeed", POINTER(xet_link_speed_t))                           ## [out] Pointer to the current speed configuration
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_LINK_SPEED_RANGE
class xet_resprop_link_speed_range_t(Structure):
    _fields_ = [
        ("pMinSpeed", POINTER(xet_link_speed_t)),                       ## [out] Pointer to the min speed configuration (one of those in the
                                                                        ## array returned by property ::XET_RESPROP_LINK_AVAIL_SPEEDS)
        ("pMaxSpeed", POINTER(xet_link_speed_t))                        ## [out] Pointer to the max speed configuration (one of those in the
                                                                        ## array returned by property ::XET_RESPROP_LINK_AVAIL_SPEEDS)
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_TEMP_TEMPERATURE
class xet_resprop_temp_temperature_t(Structure):
    _fields_ = [
        ("temperature", c_ulong)                                        ## [out] The current temperature of the sensor in degrees celcius
    ]

###############################################################################
## @brief Standby promotion modes
class xet_stby_promo_mode_v(IntEnum):
    IMMEDIATE = 0                                   ## The device/component will shutdown immediately when all contained
                                                    ## units are idle. This improves energy savings at the expense of
                                                    ## performance.
    DEFAULT = auto()                                ## Best compromise between performance and energy savings.
    NEVER = auto()                                  ## The device/component will never shutdown. This can improve performance
                                                    ## but uses more energy.

class xet_stby_promo_mode_t(c_int):
    def __str__(self):
        return str(xet_stby_promo_mode_v(value))


###############################################################################
## @brief Data for the property ::XET_RESPROP_STBY_PROMO_MODE
class xet_resprop_stby_promo_mode_t(Structure):
    _fields_ = [
        ("mode", xet_stby_promo_mode_t)                                 ## [in,out] Current promotion mode
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_FW_NAME
class xet_resprop_fw_name_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_RESPROP_FW_VERSION
class xet_resprop_fw_version_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FW_CHECK
class xet_resprop_fw_check_t(Structure):
    _fields_ = [
        ("checksum", c_ulong)                                           ## [out] The calculated checksum of the loaded firmware image
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FW_FLASH
class xet_resprop_fw_flash_t(Structure):
    _fields_ = [
        ("pImage", c_void_p),                                           ## [in] Pointer to the image to be flashed
        ("size", c_ulong)                                               ## [in] Size in bytes of the image pointed to by pImage
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
## @brief Data for the property ::XET_RESPROP_PSU_AMP_LIMIT
class xet_resprop_psu_amp_limit_t(Structure):
    _fields_ = [
        ("limit", c_ulong)                                              ## [out] The maximum electrical current in amperes that can be drawn
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_PSU_VOLTAGE_STATUS
class xet_resprop_psu_voltage_status_t(Structure):
    _fields_ = [
        ("status", xet_psu_voltage_status_t)                            ## [out] The current PSU voltage status)
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_PSU_FAN_FAILURE
class xet_resprop_psu_fan_failure_t(Structure):
    _fields_ = [
        ("status", xe_bool_t)                                           ## [out] Indicates if the fan has failed
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_PSU_TEMPERATURE
class xet_resprop_psu_temperature_t(Structure):
    _fields_ = [
        ("temperature", c_ulong)                                        ## [out] Read the current heatsink temperature in degrees celcius
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_PSU_AMPS
class xet_resprop_psu_amps_t(Structure):
    _fields_ = [
        ("current", c_ulong)                                            ## [out] The amps being drawn in amperes
    ]

###############################################################################
## @brief Fan resource speed mode
class xet_fan_speed_mode_v(IntEnum):
    FIXED = 0                                       ## The fan speed is currently set to a fixed value
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
## @brief Data for the property ::XET_RESPROP_FAN_MAX_RPM
class xet_resprop_fan_max_rpm_t(Structure):
    _fields_ = [
        ("maxSpeed", c_ulong)                                           ## [out] The maximum RPM of the fan
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FAN_MAX_TABLE_SIZE
class xet_resprop_fan_max_table_size_t(Structure):
    _fields_ = [
        ("maxPoints", c_ulong)                                          ## [out] The maximum number of points in the fan temp/speed table
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FAN_SPEED_RPM
class xet_resprop_fan_speed_rpm_t(Structure):
    _fields_ = [
        ("speed", c_ulong)                                              ## [out] The current fan speed in units of revolutions per minute (rpm)
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FAN_SPEED_PERCENT
class xet_resprop_fan_speed_percent_t(Structure):
    _fields_ = [
        ("speed", c_ulong)                                              ## [out] The current fan speed as a percentage of the maximum speed of
                                                                        ## that fan
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FAN_MODE
class xet_resprop_fan_mode_t(Structure):
    _fields_ = [
        ("mode", xet_fan_speed_mode_t)                                  ## [in,out] The current fan speed mode (one of ::xet_fan_speed_mode_t)
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FAN_FIXED_SPEED
class xet_resprop_fan_fixed_speed_t(Structure):
    _fields_ = [
        ("speed", c_ulong),                                             ## [in,out] The speed of the fan
        ("units", xet_fan_speed_units_t)                                ## [in,out] The units of the member speed
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_FAN_SPEED_TABLE
class xet_resprop_fan_speed_table_t(Structure):
    _fields_ = [
        ("pCount", POINTER(c_ulong)),                                   ## [in,out] The number of temp/speed pairs.
                                                                        ## When reading the current fan speed table, this will be set to the
                                                                        ## number of points returned.
                                                                        ## When setting the fan speed table, this specifies the number of valid
                                                                        ## points in the table.
        ("points", xet_fan_temp_speed_t * XET_FAN_TEMP_SPEED_PAIR_COUNT)## [in,out][range(0, *pCount)] Array of temperature/fan speed pairs
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_LED_RGB_CAP
class xet_resprop_led_rgb_cap_t(Structure):
    _fields_ = [
        ("haveRGB", xe_bool_t)                                          ## [out] Indicates if the LED is RGB capable
    ]

###############################################################################
## @brief Data for the property ::XET_RESPROP_LED_STATE
class xet_resprop_led_state_t(Structure):
    _fields_ = [
        ("isOn", xe_bool_t),                                            ## [in,out] Indicates if the LED is on or off
        ("red", c_ubyte),                                               ## [in,out][range(0, 255)] The LED red value
        ("green", c_ubyte),                                             ## [in,out][range(0, 255)] The LED green value
        ("blue", c_ubyte)                                               ## [in,out][range(0, 255)] The LED blue value
    ]

###############################################################################
## @brief Property support
class xet_prop_support_v(IntEnum):
    NONE = 0                                        ## The property is not supported by this version of the API
    API = XE_BIT( 0 )                               ## The property is supported by the the API
    DEVICE_CLASS = XE_BIT( 1 )                      ## The property is supported for the class of device
    DEVICE = XE_BIT( 2 )                            ## The property is supported for the device

class xet_prop_support_t(c_int):
    def __str__(self):
        return str(xet_prop_support_v(value))


###############################################################################
## @brief Property access permissions
class xet_prop_access_v(IntEnum):
    NO_PERMISSIONS = 0                              ## The application does not have read-write access to the property
    READ_PERMISSIONS = XE_BIT( 0 )                  ## The application has only read access to the property
    WRITE_PERMISSIONS = XE_BIT( 1 )                 ## The application has write access to the property

class xet_prop_access_t(c_int):
    def __str__(self):
        return str(xet_prop_access_v(value))


###############################################################################
## @brief Structure containing information about a resource
class xet_resid_info_t(Structure):
    _fields_ = [
        ("id", xet_resid_t),                                            ## [in] The ID of the resource
        ("type", xet_resource_type_t),                                  ## [in] The type of resource
        ("pName", POINTER(c_char)),                                     ## [out] The name of the resource
        ("pDesc", POINTER(c_char)),                                     ## [out] Human readable description of this resouce
        ("available", xe_bool_t),                                       ## [out] Set to TRUE if the resource with this ID is available on the
                                                                        ## device, otherwise set to FALSE
        ("propsOnSubdevices", xe_bool_t)                                ## [out] Set to TRUE if this resource will change properties on
                                                                        ## sub-devices or is merging telemetry from sub-devices
    ]

###############################################################################
## @brief Request structure to get resource property info
class xet_resprop_info_t(Structure):
    _fields_ = [
        ("property", xet_resprop_t),                                    ## [in] The property
        ("resourceType", xet_resource_type_t),                          ## [out] The type of resource this property is used with
        ("pName", POINTER(c_char)),                                     ## [out] Resource property name
        ("pDesc", POINTER(c_char)),                                     ## [out] Human readable description of this property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minGetInterval", c_ulong),                                    ## [out] The minimum interval in microseconds between reads to this
                                                                        ## property
        ("minSetInterval", c_ulong)                                     ## [out] The minimum interval in microseconds between writes to this
                                                                        ## property
    ]

###############################################################################
## @brief Request structure used to query a resource property value
class xet_resprop_request_t(Structure):
    _fields_ = [
        ("resource", xet_resid_t),                                      ## [in] The resource ID
        ("property", xet_resprop_t),                                    ## [in] The property being requested
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong),                                              ## [in] The size of the data structure pointed to by pData.
        ("status", xe_result_t)                                         ## [out] Indicates if the request was successful or not.
                                                                        ## ::XE_RESULT_SUCCESS - Data was successful read or updated.
                                                                        ## ::XE_RESULT_ERROR_DEVICE_ACCESS - Problem reading or writing device data.
                                                                        ## ::XE_RESULT_ERROR_INVALID_ARGUMENT - Resource ID or property ID are
                                                                        ## invalid or size does not match required storage for property data.
                                                                        ## ::XE_RESULT_ERROR_UNSUPPORTED - Resource ID and/or property ID not
                                                                        ## supported on this device.
                                                                        ## ::XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS - Insufficient permission to
                                                                        ## access this property.
    ]

###############################################################################
## @brief RAS error type
class xet_ras_error_type_v(IntEnum):
    NONE = 0                                        ## No error type
    FATAL = XE_BIT( 0 )                             ## Error was fatal
    NON_FATAL = XE_BIT( 1 )                         ## Error was not fatal
    CORRECTABLE = XE_BIT( 2 )                       ## Error was corrected
    UNCORRECTABLE = XE_BIT( 3 )                     ## Error was not corrected
    PARITY = XE_BIT( 4 )                            ## Parity error occurred
    SINGLE_BIT = XE_BIT( 5 )                        ## Single bit error occurred
    DOUBLE_BIT = XE_BIT( 6 )                        ## Single bit error occurred
    REPLAY = XE_BIT( 7 )                            ## Replay occurred
    RESET = XE_BIT( 8 )                             ## Resets occurred
    ALL = ~0                                        ## Select all error types

class xet_ras_error_type_t(c_int):
    def __str__(self):
        return str(xet_ras_error_type_v(value))


###############################################################################
## @brief RAS error structural location
class xet_ras_error_loc_v(IntEnum):
    NONE = 0                                        ## No location
    MAIN_MEM = XE_BIT( 0 )                          ## Error occurred in main onboard memory
    L3_CACHE = XE_BIT( 1 )                          ## Error occurred in L3 cache
    SAMPLER_SRAM = XE_BIT( 2 )                      ## Error occurred in sampler SRAM
    GUC_SRAM = XE_BIT( 3 )                          ## Error occurred in microcontroller SRAM
    INST_CACHE = XE_BIT( 4 )                        ## Error occurred in the compute unit instruction cache
    GRF = XE_BIT( 5 )                               ## Error occurred in the compute unit register file
    SLM = XE_BIT( 6 )                               ## Error occurred in the compute unit shared local memory
    MESSAGING = XE_BIT( 7 )                         ## Errors occurred handling transactions between PCI config space, MMIO
                                                    ## registers, local memory and sub-devices
    SECURITY = XE_BIT( 8 )                          ## Security errors occurred
    DISPLAY = XE_BIT( 9 )                           ## Errors occurred in the display
    SOC = XE_BIT( 10 )                              ## Errors occurred in other parts of the device
    GPU_HANG = XE_BIT( 11 )                         ## Driver detected that the GPU hardware was non-responsive
    PCI = XE_BIT( 12 )                              ## Error occurred in the PCIe controller
    PCI_ROUTING = XE_BIT( 13 )                      ## Error occurred routing PCIe traffic to/from sub-devices
    P2P_LINK = XE_BIT( 14 )                         ## Errors detected with peer-to-peer connection
    ALL = ~0                                        ## Select all error locations

class xet_ras_error_loc_t(c_int):
    def __str__(self):
        return str(xet_ras_error_loc_v(value))


###############################################################################
## @brief RAS configuration
class xet_ras_config_t(Structure):
    _fields_ = [
        ("numRas", c_ulong),                                            ## [in] Total number of RAS counters available on this device
        ("rasTypes", c_ulong),                                          ## [in] All RAS types supported on this device (bitfield of
                                                                        ## ::xet_ras_error_type_t)
        ("rasLocations", c_ulong),                                      ## [in] All structural locations where RAS is supported on this device
                                                                        ## (bitfield of ::xet_ras_error_loc_t)
        ("enabled", c_ulong)                                            ## [in] All structural locations where RAS is currently enabled on this
                                                                        ## device (bitfield of ::xet_ras_error_loc_t)
    ]

###############################################################################
## @brief RAS data type
class xet_ras_data_type_v(IntEnum):
    NONE = 0                                        ## Errors not supported
    OCCURRED = auto()                               ## Indicates if an error occurred
    COUNTER = auto()                                ## Provides a counter for the number of errors that have occurred

class xet_ras_data_type_t(c_int):
    def __str__(self):
        return str(xet_ras_data_type_v(value))


###############################################################################
## @brief Filter RAS errors
class xet_ras_filter_t(Structure):
    _fields_ = [
        ("resourceId", xet_resid_t),                                    ## [in] Filter based on resource ID. Set to ::XET_RESID_ANY to get errors
                                                                        ## from anywhere in the device
        ("type", c_ulong),                                              ## [in] Bitfield of error types to filter - one or more of
                                                                        ## ::xet_ras_error_type_t. Set to ::XET_RAS_ERROR_TYPE_ALL to have all
                                                                        ## error types returned.
        ("location", c_ulong),                                          ## [in] Bitfield of error locations to filter - one or more of
                                                                        ## ::xet_ras_error_loc_t. Set to ::XET_RAS_ERROR_LOC_ALL to have all
                                                                        ## error locations returned.
        ("threshold", c_ulong)                                          ## [in] Only return error elements that have occurred at least this
                                                                        ## number of times.
                                                                        ## If set to 0, will get a list of all possible RAS elements, even those
                                                                        ## that have not had errors.
                                                                        ## For error elements of type ::XET_RAS_DATA_TYPE_OCCURRED, there is no
                                                                        ## underlying counter, so they will always be returned independent of the
                                                                        ## threshold setting.
    ]

###############################################################################
## @brief Filter to get all RAS error counters
XET_RAS_FILTER_ALL_COUNTERS = { XET_RESID_ANY, (uint32_t)XET_RAS_ERROR_TYPE_ALL, (uint32_t)XET_RAS_ERROR_LOC_ALL, 0 }

###############################################################################
## @brief Filter to get all RAS error counters that have errors
XET_RAS_FILTER_ALL_ERRORS = { XET_RESID_ANY, (uint32_t)XET_RAS_ERROR_TYPE_ALL, (uint32_t)XET_RAS_ERROR_LOC_ALL, 1 }

###############################################################################
## @brief RAS error
class xet_ras_error_t(Structure):
    _fields_ = [
        ("pName", POINTER(c_char)),                                     ## [out] Name of this error
        ("pDesc", POINTER(c_char)),                                     ## [out] Human readable description of this error
        ("type", c_ulong),                                              ## [out] Bitfield describing type of error, constructed from one or more
                                                                        ## of ::xet_ras_error_type_t
        ("loc", c_ulong),                                               ## [out] Bitfield describing structural location of the error,
                                                                        ## constructed from one of ::xet_ras_error_loc_t
        ("dataType", xet_ras_data_type_t),                              ## [out] How to interpret the data
        ("data", c_ulonglong),                                          ## [out] The value of the error - interpretation depends on dataType
        ("accumulated", c_ulonglong),                                   ## [out] The accumulated value of the error (never cleared until device
                                                                        ## driver is reloaded)
        ("resourceId", xet_resid_t)                                     ## [out] Resource where the error was generated. If the error doesn't
                                                                        ## come from a specific resource, this will be ::XET_RESID_ANY
    ]

###############################################################################
## @brief Event types
class xet_sysman_event_type_v(IntEnum):
    FREQ_THROTTLED = 0                              ## The frequency is being throttled
    RAS_ERRORS = auto()                             ## ECC/RAS errors
    COUNT = auto()                                  ## The number of event types

class xet_sysman_event_type_t(c_int):
    def __str__(self):
        return str(xet_sysman_event_type_v(value))


###############################################################################
## @brief Request structure to determine events that are supported
class xet_event_support_t(Structure):
    _fields_ = [
        ("event", xet_sysman_event_type_t),                             ## [in] The event
        ("supported", xe_bool_t)                                        ## [out] Set to true/false to know if the event is supported
    ]

###############################################################################
## @brief Request structure used to register/unregister events
class xet_event_request_t(Structure):
    _fields_ = [
        ("event", xet_sysman_event_type_t),                             ## [in] The event type to register.
        ("resourceId", xet_resid_t),                                    ## [in] Only events being generated by the specified resource. If
                                                                        ## ::XET_RESID_ANY, then applies to all events from all resources in the
                                                                        ## device.
        ("threshold", c_ulong)                                          ## [in] The application only receives a notification when the total count
                                                                        ## exceeds this value. Set to zero to receive a notification for every
                                                                        ## new event.
    ]

###############################################################################
## @brief Wait infinitely for events to arrive.
XET_EVENT_WAIT_INFINITE = 0xFFFFFFFF

###############################################################################
## @brief Diagnostic type
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
## @brief List of all diagnostic tests of a given type ::xet_diag_type_t
class xet_diag_test_list_t(Structure):
    _fields_ = [
        ("type", xet_diag_type_t),                                      ## [out] The type of tests
        ("count", c_ulong),                                             ## [out] The number of tests in the array pTests
        ("pTests", POINTER(xet_diag_test_t))                            ## [out] Array of tests, sorted by increasing value of
                                                                        ## ::xet_diag_test_t.index
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
## @brief Function-pointer for xetSysmanGet
if __use_win_types:
    _xetSysmanGet_t = WINFUNCTYPE( xe_result_t, xet_device_handle_t, xet_sysman_version_t, POINTER(xet_sysman_handle_t) )
else:
    _xetSysmanGet_t = CFUNCTYPE( xe_result_t, xet_device_handle_t, xet_sysman_version_t, POINTER(xet_sysman_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetResourceInfo
if __use_win_types:
    _xetSysmanGetResourceInfo_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_resid_info_t) )
else:
    _xetSysmanGetResourceInfo_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_resid_info_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetResources
if __use_win_types:
    _xetSysmanGetResources_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_resource_type_t, POINTER(c_ulong), POINTER(xet_resid_info_t) )
else:
    _xetSysmanGetResources_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_resource_type_t, POINTER(c_ulong), POINTER(xet_resid_info_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetPropertyInfo
if __use_win_types:
    _xetSysmanGetPropertyInfo_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_resprop_info_t) )
else:
    _xetSysmanGetPropertyInfo_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_resprop_info_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetProperties
if __use_win_types:
    _xetSysmanGetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_resprop_request_t) )
else:
    _xetSysmanGetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_resprop_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetProperties
if __use_win_types:
    _xetSysmanSetProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_resprop_request_t) )
else:
    _xetSysmanSetProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_resprop_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetRasConfig
if __use_win_types:
    _xetSysmanGetRasConfig_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_ras_config_t) )
else:
    _xetSysmanGetRasConfig_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_ras_config_t) )

###############################################################################
## @brief Function-pointer for xetSysmanRasSetup
if __use_win_types:
    _xetSysmanRasSetup_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, c_ulong, POINTER(c_ulong) )
else:
    _xetSysmanRasSetup_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, c_ulong, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanGetRasErrors
if __use_win_types:
    _xetSysmanGetRasErrors_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_ras_filter_t), xe_bool_t, POINTER(c_ulong), POINTER(xet_ras_error_t) )
else:
    _xetSysmanGetRasErrors_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_ras_filter_t), xe_bool_t, POINTER(c_ulong), POINTER(xet_ras_error_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSupportedEvents
if __use_win_types:
    _xetSysmanSupportedEvents_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_event_support_t) )
else:
    _xetSysmanSupportedEvents_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_event_support_t) )

###############################################################################
## @brief Function-pointer for xetSysmanRegisterEvents
if __use_win_types:
    _xetSysmanRegisterEvents_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_event_request_t) )
else:
    _xetSysmanRegisterEvents_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_event_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanUnregisterEvents
if __use_win_types:
    _xetSysmanUnregisterEvents_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_event_request_t) )
else:
    _xetSysmanUnregisterEvents_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_event_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetEvents
if __use_win_types:
    _xetSysmanGetEvents_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, c_ulong, POINTER(c_ulong) )
else:
    _xetSysmanGetEvents_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, c_ulong, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanGetDiagnosticTests
if __use_win_types:
    _xetSysmanGetDiagnosticTests_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_diag_type_t, POINTER(xet_diag_test_list_t*) )
else:
    _xetSysmanGetDiagnosticTests_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_diag_type_t, POINTER(xet_diag_test_list_t*) )

###############################################################################
## @brief Function-pointer for xetSysmanRunDiagnosticTests
if __use_win_types:
    _xetSysmanRunDiagnosticTests_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_diag_type_t, c_ulong, c_ulong, POINTER(xet_diag_result_t) )
else:
    _xetSysmanRunDiagnosticTests_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_diag_type_t, c_ulong, c_ulong, POINTER(xet_diag_result_t) )

###############################################################################
## @brief Function-pointer for xetSysmanDeviceReset
if __use_win_types:
    _xetSysmanDeviceReset_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t )
else:
    _xetSysmanDeviceReset_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t )


###############################################################################
## @brief Table of Sysman functions pointers
class _xet_sysman_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _xetSysmanGet_t
        ("pfnGetResourceInfo", c_void_p),                               ## _xetSysmanGetResourceInfo_t
        ("pfnGetResources", c_void_p),                                  ## _xetSysmanGetResources_t
        ("pfnGetPropertyInfo", c_void_p),                               ## _xetSysmanGetPropertyInfo_t
        ("pfnGetProperties", c_void_p),                                 ## _xetSysmanGetProperties_t
        ("pfnSetProperties", c_void_p),                                 ## _xetSysmanSetProperties_t
        ("pfnGetRasConfig", c_void_p),                                  ## _xetSysmanGetRasConfig_t
        ("pfnRasSetup", c_void_p),                                      ## _xetSysmanRasSetup_t
        ("pfnGetRasErrors", c_void_p),                                  ## _xetSysmanGetRasErrors_t
        ("pfnSupportedEvents", c_void_p),                               ## _xetSysmanSupportedEvents_t
        ("pfnRegisterEvents", c_void_p),                                ## _xetSysmanRegisterEvents_t
        ("pfnUnregisterEvents", c_void_p),                              ## _xetSysmanUnregisterEvents_t
        ("pfnGetEvents", c_void_p),                                     ## _xetSysmanGetEvents_t
        ("pfnGetDiagnosticTests", c_void_p),                            ## _xetSysmanGetDiagnosticTests_t
        ("pfnRunDiagnosticTests", c_void_p),                            ## _xetSysmanRunDiagnosticTests_t
        ("pfnDeviceReset", c_void_p)                                    ## _xetSysmanDeviceReset_t
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
        ("Sysman", _xet_sysman_dditable_t)
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
        self.xetSysmanGetResourceInfo = _xetSysmanGetResourceInfo_t(self.__dditable.Sysman.pfnGetResourceInfo)
        self.xetSysmanGetResources = _xetSysmanGetResources_t(self.__dditable.Sysman.pfnGetResources)
        self.xetSysmanGetPropertyInfo = _xetSysmanGetPropertyInfo_t(self.__dditable.Sysman.pfnGetPropertyInfo)
        self.xetSysmanGetProperties = _xetSysmanGetProperties_t(self.__dditable.Sysman.pfnGetProperties)
        self.xetSysmanSetProperties = _xetSysmanSetProperties_t(self.__dditable.Sysman.pfnSetProperties)
        self.xetSysmanGetRasConfig = _xetSysmanGetRasConfig_t(self.__dditable.Sysman.pfnGetRasConfig)
        self.xetSysmanRasSetup = _xetSysmanRasSetup_t(self.__dditable.Sysman.pfnRasSetup)
        self.xetSysmanGetRasErrors = _xetSysmanGetRasErrors_t(self.__dditable.Sysman.pfnGetRasErrors)
        self.xetSysmanSupportedEvents = _xetSysmanSupportedEvents_t(self.__dditable.Sysman.pfnSupportedEvents)
        self.xetSysmanRegisterEvents = _xetSysmanRegisterEvents_t(self.__dditable.Sysman.pfnRegisterEvents)
        self.xetSysmanUnregisterEvents = _xetSysmanUnregisterEvents_t(self.__dditable.Sysman.pfnUnregisterEvents)
        self.xetSysmanGetEvents = _xetSysmanGetEvents_t(self.__dditable.Sysman.pfnGetEvents)
        self.xetSysmanGetDiagnosticTests = _xetSysmanGetDiagnosticTests_t(self.__dditable.Sysman.pfnGetDiagnosticTests)
        self.xetSysmanRunDiagnosticTests = _xetSysmanRunDiagnosticTests_t(self.__dditable.Sysman.pfnRunDiagnosticTests)
        self.xetSysmanDeviceReset = _xetSysmanDeviceReset_t(self.__dditable.Sysman.pfnDeviceReset)

        # success!
