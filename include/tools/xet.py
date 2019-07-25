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
## @brief SMI initialization flags (bitfield)
class xet_sysman_init_flags_v(IntEnum):
    NONE = 0                                        ## Default initialization
    WRITE = XE_BIT( 0 )                             ## Request write/control access to resources

class xet_sysman_init_flags_t(c_int):
    def __str__(self):
        return str(xet_sysman_init_flags_v(value))


###############################################################################
## @brief Resource types
class xet_resource_type_v(IntEnum):
    PSU = 0                                         ## PSU resource
    TEMP = auto()                                   ## Temperature sensor resource
    FAN = auto()                                    ## Fan resource
    LED = auto()                                    ## LED resource
    FIRMWARE = auto()                               ## Firmware resource
    PWR = auto()                                    ## Power domain resource
    FREQ = auto()                                   ## Frequency domain resource
    PWRWELL = auto()                                ## Power-well resource
    ACCEL = auto()                                  ## Accelerator asset resource
    MEM = auto()                                    ## Memory resource
    LINK = auto()                                   ## Link resource
    MAX_TYPES = auto()                              ## The number of resource types
    ANY = -1                                        ## Any resource filter

class xet_resource_type_t(c_int):
    def __str__(self):
        return str(xet_resource_type_v(value))


###############################################################################
## @brief Resource ID
class xet_resource_id_t(Structure):
    _fields_ = [
        ("type", xet_resource_type_t),                                  ## [in,out] Resource type
        ("index", c_ulong)                                              ## [in,out] Resource index (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::xet_resource_type_t]-1)
    ]

###############################################################################
## @brief Any resource
XET_RESOURCE_ID_ANY = { XET_RESOURCE_TYPE_ANY, 0x0 }

###############################################################################
## @brief Accelerator assets
class xet_accel_asset_v(IntEnum):
    PCIE_CONTROLLER = 0                             ## PCIe controller
    IDI_MEM_CONTROLLER = auto()                     ## IDI memory controller
    HBM_MEM_CONTROLLER = auto()                     ## HBM memory controller
    L3_CACHE = auto()                               ## L3 cache
    BLITTER = auto()                                ## Blitter
    VIDEO_DECODER = auto()                          ## Video decoder
    VIDEO_ENCODER = auto()                          ## Video encoder
    VIDEO_PROCESSING = auto()                       ## Video processing
    _3D_FF = auto()                                 ## 3D fixed-function hardware
    _3D_RENDER = auto()                             ## 3D programmable shader units
    COMPUTE = auto()                                ## Compute units
    SYSTOLIC = auto()                               ## Systolic array
    RAYTRACING = auto()                             ## Raytracing hardware
    LOCAL_MEM = auto()                              ## Local memory
    LINK = auto()                                   ## High speed link
    MAX_TYPES = auto()                              ## The number of accelerator asset types

class xet_accel_asset_t(c_int):
    def __str__(self):
        return str(xet_accel_asset_v(value))


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
    PCI = XE_BIT( 7 )                               ## Error occurred in the PCIe controller
    PCI_ROUTING = XE_BIT( 8 )                       ## Error occurred routing PCIe traffic to/from sub-devices
    SGUNIT = XE_BIT( 9 )                            ## Errors occurred handling transactions between PCI config space, MMIO
                                                    ## registers, local memory and sub-devices
    GSC = XE_BIT( 10 )                              ## Security errors occurred
    DISPLAY = XE_BIT( 11 )                          ## Errors occurred in the display
    SOC = XE_BIT( 12 )                              ## Errors occurred in other parts of the device
    GPU_HANG = XE_BIT( 13 )                         ## Driver detected that the GPU hardware was non-responsive
    GPU_WARM_RESET = XE_BIT( 14 )                   ## Driver performed a GPU warm reset
    ALL = ~0                                        ## Select all error locations

class xet_ras_error_loc_t(c_int):
    def __str__(self):
        return str(xet_ras_error_loc_v(value))


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
        ("resourceId", xet_resource_id_t),                              ## [in] Filter based on resource ID. Set to ::XET_RESOURCE_ID_ANY to get
                                                                        ## errors from anywhere in the device
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
XET_RAS_FILTER_ALL_COUNTERS = { XET_RESOURCE_ID_ANY, (uint32_t)XET_RAS_ERROR_TYPE_ALL, (uint32_t)XET_RAS_ERROR_LOC_ALL, 0 }

###############################################################################
## @brief Filter to get all RAS error counters that have errors
XET_RAS_FILTER_ALL_ERRORS = { XET_RESOURCE_ID_ANY, (uint32_t)XET_RAS_ERROR_TYPE_ALL, (uint32_t)XET_RAS_ERROR_LOC_ALL, 1 }

###############################################################################
## @brief RAS error
class xet_ras_error_t(Structure):
    _fields_ = [
        ("type", c_ulong),                                              ## [out] Bitfield describing type of error, constructed from one or more
                                                                        ## of ::xet_ras_error_type_t
        ("loc", c_ulong),                                               ## [out] Bitfield describing structural location of the error,
                                                                        ## constructed from one of ::xet_ras_error_loc_t
        ("dataType", xet_ras_data_type_t),                              ## [out] How to interpret the data
        ("data", c_ulonglong),                                          ## [out] The value of the error - interpretation depends on dataType
        ("resourceId", xet_resource_id_t)                               ## [out] Resource where the error was generated. If the error doesn't
                                                                        ## come from a specific resource, this will be ::XET_RESOURCE_ID_ANY
    ]

###############################################################################
## @brief Generic SMI information about a device
class xet_sysman_info_t(Structure):
    _fields_ = [
        ("numAssets", c_ulong * XET_ACCEL_ASSET_MAX_TYPES),             ## [out] The number of each accelerator asset in the device.
        ("numRas", c_ulong),                                            ## [out] The total number of RAS elements available for querying in this
                                                                        ## device.
        ("rasTypes", c_ulong),                                          ## [out] Bitfield of the type of RAS elements (::xet_ras_error_type_t)
                                                                        ## available for querying in this device.
        ("rasLocations", c_ulong),                                      ## [out] Bitfield of the structure location of RAS elements
                                                                        ## (::xet_ras_error_loc_t) available for querying in this device.
        ("numResourcesByType", c_ulong * XET_RESOURCE_TYPE_MAX_TYPES)   ## [out] The number of resources of each type in this device.
    ]

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
## @brief Device resource properties
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
class xet_device_properties_v(IntEnum):
    DEVICE_PROP_SERIAL_NUMBER = 0                   ## (ro static) The serial number of the device (data:
                                                    ## ::xet_device_prop_serial_number_t)
    DEVICE_PROP_BOARD_NUMBER = auto()               ## (ro static) The board number of the device (data:
                                                    ## ::xet_device_prop_board_number_t)
    DEVICE_PROP_BRAND = auto()                      ## (ro static) The brand name of the device (data:
                                                    ## ::xet_device_prop_brand_t)
    DEVICE_PROP_MODEL = auto()                      ## (ro static) The model name of the device (data:
                                                    ## ::xet_device_prop_model_t)
    DEVICE_PROP_DEVICEID = auto()                   ## (ro static) The device ID of the device (data:
                                                    ## ::xet_device_prop_deviceid_t)
    DEVICE_PROP_VENDOR_NAME = auto()                ## (ro static) The vendor name of the device (data:
                                                    ## ::xet_device_prop_vendor_name_t)
    DEVICE_PROP_DRIVER_VERSION = auto()             ## (ro static) The driver version associated with the device (data:
                                                    ## ::xet_device_prop_driver_version_t)
    DEVICE_PROP_BARS = auto()                       ## (ro static) The bars configured for the device (data:
                                                    ## ::xet_device_prop_bars_t)
    DEVICE_PROP_RESET = auto()                      ## (wo dynamic) Reset the device (data: ::xet_device_prop_reset_t)

class xet_device_properties_t(c_int):
    def __str__(self):
        return str(xet_device_properties_v(value))


###############################################################################
## @brief Data for property ::XET_DEVICE_PROP_SERIAL_NUMBER
class xet_device_prop_serial_number_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_DEVICE_PROP_BOARD_NUMBER
class xet_device_prop_board_number_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_DEVICE_PROP_BRAND
class xet_device_prop_brand_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_DEVICE_PROP_MODEL
class xet_device_prop_model_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_DEVICE_PROP_DEVICEID
class xet_device_prop_deviceid_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_DEVICE_PROP_VENDOR_NAME
class xet_device_prop_vendor_name_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_DEVICE_PROP_DRIVER_VERSION
class xet_device_prop_driver_version_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for the property ::XET_DEVICE_PROP_BARS
class xet_device_prop_bars_t(Structure):
    _fields_ = [
        ("num", c_ulong),                                               ## [out] The number of bars
        ("pBars", POINTER(xet_pci_bar_info_t))                          ## [out][range(0, num-1)] Information about each bar.
    ]

###############################################################################
## @brief Data for the property ::XET_DEVICE_PROP_RESET
class xet_device_prop_reset_t(Structure):
    _fields_ = [
        ("doReset", xe_bool_t)                                          ## [in] Set to true to perform a reset of the device
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
## @brief Request structure to determine device properties that are
##        supported/accessible
class xet_device_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_device_properties_t),                          ## [in] The property
        ("support", c_ubyte),                                           ## [out] API support for the property - one of ::xet_prop_support_t
        ("access", c_ubyte),                                            ## [out] The access permissions for the property - one of
                                                                        ## ::xet_prop_access_t
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a device property
class xet_device_property_request_t(Structure):
    _fields_ = [
        ("property", xet_device_properties_t),                          ## [in] The property being requested (one of ::xet_device_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
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
## @brief PSU resource properties
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
class xet_psu_properties_v(IntEnum):
    PSU_PROP_AMP_LIMIT = 0                          ## (ro static) The maximum electrical current in amperes that can be
                                                    ## drawn (data: ::xet_psu_prop_amp_limit_t)
    PSU_PROP_VOLTAGE_STATUS = auto()                ## (ro dynamic) Indicates if under or over voltage has occurred (data:
                                                    ## ::xet_psu_prop_voltage_status_t)
    PSU_PROP_FAN_FAILURE = auto()                   ## (ro dynamic) Indicates if the fan has failed (data:
                                                    ## ::xet_psu_prop_fan_failure_t)
    PSU_PROP_TEMPERATURE = auto()                   ## (ro dynamic) The current heatsink temperature in degrees celcius
                                                    ## (data: ::xet_psu_prop_temperature_t)
    PSU_PROP_AMPS = auto()                          ## (ro dynamic) The current amps being drawn in amperes (data:
                                                    ## ::xet_psu_prop_amps_t)

class xet_psu_properties_t(c_int):
    def __str__(self):
        return str(xet_psu_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_PSU_PROP_AMP_LIMIT
class xet_psu_prop_amp_limit_t(Structure):
    _fields_ = [
        ("limit", c_ulong)                                              ## [out] The maximum electrical current in amperes that can be drawn
    ]

###############################################################################
## @brief Data for the property ::XET_PSU_PROP_VOLTAGE_STATUS
class xet_psu_prop_voltage_status_t(Structure):
    _fields_ = [
        ("status", xet_psu_voltage_status_t)                            ## [out] The current PSU voltage status)
    ]

###############################################################################
## @brief Data for the property ::XET_PSU_PROP_FAN_FAILURE
class xet_psu_prop_fan_failure_t(Structure):
    _fields_ = [
        ("status", xe_bool_t)                                           ## [out] Indicates if the fan has failed
    ]

###############################################################################
## @brief Data for the property ::XET_PSU_PROP_TEMPERATURE
class xet_psu_prop_temperature_t(Structure):
    _fields_ = [
        ("temperature", c_ulong)                                        ## [out] Read the current heatsink temperature in degrees celcius
    ]

###############################################################################
## @brief Data for the property ::XET_PSU_PROP_AMPS
class xet_psu_prop_amps_t(Structure):
    _fields_ = [
        ("current", c_ulong)                                            ## [out] The amps being drawn in amperes
    ]

###############################################################################
## @brief Request structure to determine PSU resource properties that are
##        supported/accessible
class xet_psu_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_psu_properties_t),                             ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a PSU resource property
class xet_psu_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the PSU resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_PSU]-1)
        ("property", xet_psu_properties_t),                             ## [in] The property being requested (one of ::xet_psu_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
    ]

###############################################################################
## @brief Temperature sensor resource properties
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
class xet_temp_properties_v(IntEnum):
    TEMP_PROP_TEMPERATURE = 0                       ## (ro dynamic) The current temperature of the sensor in degrees celcius
                                                    ## (data: ::xet_temp_prop_temperature_t)

class xet_temp_properties_t(c_int):
    def __str__(self):
        return str(xet_temp_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_TEMP_PROP_TEMPERATURE
class xet_temp_prop_temperature_t(Structure):
    _fields_ = [
        ("temperature", c_ulong)                                        ## [out] The current temperature of the sensor in degrees celcius
    ]

###############################################################################
## @brief Request structure to determine temperature sensor properties that are
##        supported/accessible
class xet_temp_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_temp_properties_t),                            ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a temperature sensor resource property
class xet_temp_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the temperature sensor resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_TEMP]-1)
        ("property", xet_temp_properties_t),                            ## [in] The property being requested (one of ::xet_temp_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
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
## @brief Fan resource properties
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
class xet_fan_properties_v(IntEnum):
    FAN_PROP_MAX_RPM = 0                            ## (ro static) The maximum RPM of the fan (data:
                                                    ## ::xet_fan_prop_max_rpm_t)
    FAN_PROP_MAX_TABLE_SIZE = auto()                ## (ro static) The maximum number of points in the fan temp/speed table
                                                    ## (data: ::xet_fan_prop_max_table_size_t)
    FAN_PROP_SPEED_RPM = auto()                     ## (ro dynamic) The current fan speed in units of revolutions per minute
                                                    ## (rpm) (data: ::xet_fan_prop_speed_rpm_t)
    FAN_PROP_SPEED_PERCENT = auto()                 ## (ro dynamic) The current fan speed as a percentage of the maximum
                                                    ## speed of that fan (data: ::xet_fan_prop_speed_percent_t)
    FAN_PROP_MODE = auto()                          ## (ro dynamic) The current fan speed mode (one of
                                                    ## ::xet_fan_speed_mode_t) (data: ::xet_fan_prop_mode_t)
    FAN_PROP_FIXED_SPEED = auto()                   ## (rw dynamic) Read/write the fixed speed setting for the fan (data:
                                                    ## ::xet_fan_prop_fixed_speed_t)
    FAN_PROP_SPEED_TABLE = auto()                   ## (rw dynamic) Read/write the fan speed table (data:
                                                    ## ::xet_fan_prop_speed_table_t)

class xet_fan_properties_t(c_int):
    def __str__(self):
        return str(xet_fan_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_FAN_PROP_MAX_RPM
class xet_fan_prop_max_rpm_t(Structure):
    _fields_ = [
        ("maxSpeed", c_ulong)                                           ## [out] The maximum RPM of the fan
    ]

###############################################################################
## @brief Data for the property ::XET_FAN_PROP_MAX_TABLE_SIZE
class xet_fan_prop_max_table_size_t(Structure):
    _fields_ = [
        ("maxPoints", c_ulong)                                          ## [out] The maximum number of points in the fan temp/speed table
    ]

###############################################################################
## @brief Data for the property ::XET_FAN_PROP_SPEED_RPM
class xet_fan_prop_speed_rpm_t(Structure):
    _fields_ = [
        ("speed", c_ulong)                                              ## [out] The current fan speed in units of revolutions per minute (rpm)
    ]

###############################################################################
## @brief Data for the property ::XET_FAN_PROP_SPEED_PERCENT
class xet_fan_prop_speed_percent_t(Structure):
    _fields_ = [
        ("speed", c_ulong)                                              ## [out] The current fan speed as a percentage of the maximum speed of
                                                                        ## that fan
    ]

###############################################################################
## @brief Data for the property ::XET_FAN_PROP_MODE
class xet_fan_prop_mode_t(Structure):
    _fields_ = [
        ("mode", xet_fan_speed_mode_t)                                  ## [in,out] The current fan speed mode (one of ::xet_fan_speed_mode_t)
    ]

###############################################################################
## @brief Data for the property ::XET_FAN_PROP_FIXED_SPEED
class xet_fan_prop_fixed_speed_t(Structure):
    _fields_ = [
        ("speed", c_ulong),                                             ## [in,out] The speed of the fan
        ("units", xet_fan_speed_units_t)                                ## [in,out] The units of the member speed
    ]

###############################################################################
## @brief Data for the property ::XET_FAN_PROP_SPEED_TABLE
class xet_fan_prop_speed_table_t(Structure):
    _fields_ = [
        ("pCount", POINTER(c_ulong)),                                   ## [in,out] The number of temp/speed pairs.
                                                                        ## When reading the current fan speed table, this will be set to the
                                                                        ## number of points returned.
                                                                        ## When setting the fan speed table, this specifies the number of valid
                                                                        ## points in the table.
        ("points", xet_fan_temp_speed_t * XET_FAN_TEMP_SPEED_PAIR_COUNT)## [in,out][range(0, *pCount)] Array of temperature/fan speed pairs
    ]

###############################################################################
## @brief Request structure to determine fan resource properties that are
##        supported/accessible
class xet_fan_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_fan_properties_t),                             ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a fan resource property
class xet_fan_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the fan resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_FAN]-1)
        ("property", xet_fan_properties_t),                             ## [in] The property being requested (one of ::xet_fan_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
    ]

###############################################################################
## @brief LED resource properties
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
class xet_led_properties_v(IntEnum):
    LED_PROP_RGB_CAP = 0                            ## (ro static) Indicates if the LED is RGB capable (data:
                                                    ## ::xet_led_prop_rgb_cap_t)
    LED_PROP_STATE = auto()                         ## (rw dynaic) The LED state - on/off and color (data:
                                                    ## ::xet_led_prop_state_t)

class xet_led_properties_t(c_int):
    def __str__(self):
        return str(xet_led_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_LED_PROP_RGB_CAP
class xet_led_prop_rgb_cap_t(Structure):
    _fields_ = [
        ("haveRGB", xe_bool_t)                                          ## [out] Indicates if the LED is RGB capable
    ]

###############################################################################
## @brief Data for the property ::XET_LED_PROP_STATE
class xet_led_prop_state_t(Structure):
    _fields_ = [
        ("isOn", xe_bool_t),                                            ## [in,out] Indicates if the LED is on or off
        ("red", c_ubyte),                                               ## [in,out][range(0, 255)] The LED red value
        ("green", c_ubyte),                                             ## [in,out][range(0, 255)] The LED green value
        ("blue", c_ubyte)                                               ## [in,out][range(0, 255)] The LED blue value
    ]

###############################################################################
## @brief Request structure to determine LED resource properties that are
##        supported/accessible
class xet_led_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_led_properties_t),                             ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a LED resource property
class xet_led_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the LED resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_LED]-1)
        ("property", xet_led_properties_t),                             ## [in] The property being requested (one of ::xet_led_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
    ]

###############################################################################
## @brief Firmware resource properties
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
class xet_firmware_properties_v(IntEnum):
    FIRMWARE_PROP_NAME = 0                          ## (ro static) Name encoded in the loaded firmware image (data:
                                                    ## ::xet_firmware_prop_name_t)
    FIRMWARE_PROP_VERSION = auto()                  ## (ro static) The version of the loaded firmware image (data:
                                                    ## ::xet_firmware_prop_version_t)
    FIRMWARE_PROP_CHECK = auto()                    ## (ro dynamic) Verify the checksum of the loaded firmware image (data:
                                                    ## ::xet_firmware_prop_check_t)
    FIRMWARE_PROP_FLASH = auto()                    ## (wo dynamically) Flash a new firmware image (data:
                                                    ## ::xet_firmware_prop_flash_t)

class xet_firmware_properties_t(c_int):
    def __str__(self):
        return str(xet_firmware_properties_v(value))


###############################################################################
## @brief Data for property ::XET_FIRMWARE_PROP_NAME
class xet_firmware_prop_name_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_FIRMWARE_PROP_VERSION
class xet_firmware_prop_version_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for the property ::XET_FIRMWARE_PROP_CHECK
class xet_firmware_prop_check_t(Structure):
    _fields_ = [
        ("checksum", c_ulong)                                           ## [out] The calculated checksum of the loaded firmware image
    ]

###############################################################################
## @brief Data for the property ::XET_FIRMWARE_PROP_FLASH
class xet_firmware_prop_flash_t(Structure):
    _fields_ = [
        ("pImage", c_void_p),                                           ## [in] Pointer to the image to be flashed
        ("size", c_ulong)                                               ## [in] Size in bytes of the image pointed to by pImage
    ]

###############################################################################
## @brief Request structure to determine firmware resource properties that are
##        supported/accessible
class xet_firmware_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_firmware_properties_t),                        ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a firmware resource property
class xet_firmware_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the firmware resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_FIRMWARE]-1)
        ("property", xet_firmware_properties_t),                        ## [in] The property being requested (one of
                                                                        ## ::xet_firmware_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
    ]

###############################################################################
## @brief Power domain resource properties
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
class xet_pwr_properties_v(IntEnum):
    PWR_PROP_ACCEL_ASSETS = 0                       ## (ro static) List of accelerator assets that contribute to this power
                                                    ## domain (data: ::xet_pwr_prop_accel_assets_t)
    PWR_PROP_MAX_LIMIT = auto()                     ## (ro static) The maximum power limit that can be requested (data:
                                                    ## ::xet_pwr_prop_max_limit_t)
    PWR_PROP_ENERGY_COUNTER = auto()                ## (ro dynamic) The value of the monotonic energy counter (data:
                                                    ## ::xet_pwr_prop_energy_counter_t)
    PWR_PROP_SUSTAINED_LIMIT = auto()               ## (rw dynamic) The sustained power limit (data:
                                                    ## ::xet_pwr_prop_sustained_limit_t)
    PWR_PROP_BURST_LIMIT = auto()                   ## (rw dynamic) The burst power limit (data:
                                                    ## ::xet_pwr_prop_burst_limit_t)
    PWR_PROP_PEAK_LIMIT = auto()                    ## (rw dynamic) The peak power limit (data: ::xet_pwr_prop_peak_limit_t)

class xet_pwr_properties_t(c_int):
    def __str__(self):
        return str(xet_pwr_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_PWR_PROP_ACCEL_ASSETS
class xet_pwr_prop_accel_assets_t(Structure):
    _fields_ = [
        ("assets", c_ulonglong)                                         ## [out] List of accelerator assets that contribute to this power domain
                                                                        ## (Bitfield of (1<<::xet_accel_asset_t)).
    ]

###############################################################################
## @brief Data for the property ::XET_PWR_PROP_MAX_LIMIT
class xet_pwr_prop_max_limit_t(Structure):
    _fields_ = [
        ("assets", c_ulong)                                             ## [out] The maximum power limit in milliwatts that can be requested.
    ]

###############################################################################
## @brief Data for the property ::XET_PWR_PROP_ENERGY_COUNTER
class xet_pwr_prop_energy_counter_t(Structure):
    _fields_ = [
        ("energy", c_ulonglong)                                         ## [out] The value of the monotonic energy counter in millijoules.
    ]

###############################################################################
## @brief Data for the property ::XET_PWR_PROP_SUSTAINED_LIMIT
## 
## @details
##     - The power controller (Punit) will throttle the operating frequency if
##       the power averaged over a window (typically seconds) exceeds this
##       limit.
class xet_pwr_prop_sustained_limit_t(Structure):
    _fields_ = [
        ("enabled", xe_bool_t),                                         ## [in,out] indicates if the limit is enabled (true) or ignored (false)
        ("power", c_ulong),                                             ## [in,out] power limit in milliwatts
        ("interval", c_ulong)                                           ## [in,out] power averaging window (Tau) in milliseconds
    ]

###############################################################################
## @brief Data for the property ::XET_PWR_PROP_BURST_LIMIT
## 
## @details
##     - The power controller (Punit) will throttle the operating frequency of
##       the device if the power averaged over a few milliseconds exceeds a
##       limit known as PL2. Typically PL2 > PL1 so that it permits the
##       frequency to burst higher for short periods than would be otherwise
##       permitted by PL1.
class xet_pwr_prop_burst_limit_t(Structure):
    _fields_ = [
        ("enabled", xe_bool_t),                                         ## [in,out] indicates if the limit is enabled (true) or ignored (false)
        ("power", c_ulong)                                              ## [in,out] power limit in milliwatts
    ]

###############################################################################
## @brief Data for the property ::XET_PWR_PROP_PEAK_LIMIT
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
class xet_pwr_prop_peak_limit_t(Structure):
    _fields_ = [
        ("power", c_ulong)                                              ## [in,out] power limit in milliwatts
    ]

###############################################################################
## @brief Request structure to determine power domain resource properties that
##        are supported/accessible
class xet_pwr_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_pwr_properties_t),                             ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a power domain resource property
class xet_pwr_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the power domain resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_PWR]-1)
        ("property", xet_pwr_properties_t),                             ## [in] The property being requested (one of ::xet_pwr_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
    ]

###############################################################################
## @brief Frequency domain types
class xet_freq_domain_type_v(IntEnum):
    PLL = 0                                         ## The frequency of this domain is controlled by a phased-locked loop
                                                    ## (PLL). It can generally accept a range of frequencies with a fixed
                                                    ## step.
    DIVIDER = auto()                                ## The frequency of this domain is dependent on another domain through a
                                                    ## clock divider. There is generally a limit set of divider ratios.
    MULTIPLIER = auto()                             ## The frequency of this domain is dependent on another domain through a
                                                    ## fractional multiplier.

class xet_freq_domain_type_t(c_int):
    def __str__(self):
        return str(xet_freq_domain_type_v(value))


###############################################################################
## @brief Frequency mode
class xet_freq_mode_v(IntEnum):
    DEFAULT = 0                                     ## The frequency of this domain is managed autonomously by the hardware.
    FIXED = auto()                                  ## The frequency of this domain has been fixed by SMI.

class xet_freq_mode_t(c_int):
    def __str__(self):
        return str(xet_freq_mode_v(value))


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
## @brief Frequency divider element
## 
## @details
##     - The frequency of a domain of type ::XET_FREQ_DOMAIN_TYPE_DIVIDER is
##       obtained by the formula:
##     - freq = source domain freq * numerator / denominator
class xet_freq_divider_t(Structure):
    _fields_ = [
        ("numerator", c_ushort),                                        ## [in,out] numerator of the ratio
        ("denominator", c_ushort)                                       ## [in,out] denominator of the ratio
    ]

###############################################################################
## @brief Frequency multiplier
## 
## @details
##     - The frequency of a domain of type ::XET_FREQ_DOMAIN_TYPE_MULTIPLIER is
##       obtained by the formula:
##     - freq = source domain freq * multiplierFP8_8 / 2^8
class xet_freq_multiplier_t(Structure):
    _fields_ = [
        ("multiplierFP8_8", c_ushort)                                   ## [in,out] Multiplier in fixed-point U8.8 format
    ]

###############################################################################
## @brief Frequency domain resource properties
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
class xet_freq_properties_v(IntEnum):
    FREQ_PROP_ACCEL_ASSETS = 0                      ## (ro static) List of accelerator assets that are connected to this
                                                    ## power domain (data: ::xet_freq_prop_accel_assets_t)
    FREQ_PROP_POWER_DOMAIN = auto()                 ## (ro static) Resource ID of the power domain to which this frequency
                                                    ## domain is connected
    FREQ_PROP_DOMAIN_TYPE = auto()                  ## (ro static) The type of frequency domain (data:
                                                    ## ::xet_freq_prop_domain_type_t)
    FREQ_PROP_AVAIL_CLOCKS = auto()                 ## (ro static) Available frequency clocks that this domain can run at
                                                    ## (data: ::xet_freq_prop_avail_clocks_t)
    FREQ_PROP_AVAIL_DIVIDERS = auto()               ## (ro static) Available dividers that this domain can run with (data:
                                                    ## ::xet_freq_prop_avail_dividers_t)
    FREQ_PROP_AVAIL_MULTIPLIERS = auto()            ## (ro static) The range of multiplier values (data:
                                                    ## ::xet_freq_prop_avail_multipliers_t)
    FREQ_PROP_SRC_FREQ = auto()                     ## (ro static) Get the resource ID of the source frequency domain
                                                    ## resource if the type is dependent (data: ::xet_freq_prop_src_freq_t)
    FREQ_PROP_FREQ_REQUEST = auto()                 ## (rw dynamic) The current frequency request (data:
                                                    ## ::xet_freq_prop_freq_request_t)
    FREQ_PROP_FREQ_DIVIDER = auto()                 ## (rw dynamic) The current frequency divider for frequency domains of
                                                    ## type ::XET_FREQ_DOMAIN_TYPE_DIVIDER (data:
                                                    ## ::xet_freq_prop_freq_divider_t)
    FREQ_PROP_FREQ_MULTIPLIER = auto()              ## (rw dynamic) The current frequency multiplier for frequency domains of
                                                    ## type ::XET_FREQ_DOMAIN_TYPE_MULTIPLIER  (data:
                                                    ## ::xet_freq_prop_freq_divider_t)
    FREQ_PROP_FREQ_TDP = auto()                     ## (ro dynamic) The maximum frequency supported under the current TDP
                                                    ## conditions (data: ::xet_freq_prop_freq_tdp_t)
    FREQ_PROP_FREQ_EFFICIENT = auto()               ## (ro dynamic) The efficient minimum frequency (data:
                                                    ## ::xet_freq_prop_freq_efficient_t)
    FREQ_PROP_FREQ_RESOLVED = auto()                ## (ro dynamic) The resolved frequency (data:
                                                    ## ::xet_freq_prop_freq_resolved_t)
    FREQ_PROP_THROTTLE_REASONS = auto()             ## (ro dynamic) The reasons that the frequency is being limited by the
                                                    ## PCU (data: ::xet_freq_prop_throttle_reasons_t)
    FREQ_PROP_THROTTLE_TIME = auto()                ## (ro dynamic) The total time that the frequency has been limited by the
                                                    ## PCU (data: ::xet_freq_prop_throttle_time_t)

class xet_freq_properties_t(c_int):
    def __str__(self):
        return str(xet_freq_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_ACCEL_ASSETS
class xet_freq_prop_accel_assets_t(Structure):
    _fields_ = [
        ("assets", c_ulonglong)                                         ## [out] List of accelerator assets that are connected to this power
                                                                        ## domain (Bitfield of (1<<::xet_accel_asset_t)).
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_POWER_DOMAIN
class xet_freq_prop_power_domain_t(Structure):
    _fields_ = [
        ("resource", xet_resource_id_t)                                 ## [out] The resource ID of the power domain
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_DOMAIN_TYPE
class xet_freq_prop_domain_type_t(Structure):
    _fields_ = [
        ("type", xet_freq_domain_type_t)                                ## [out] The type of frequency domain
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_AVAIL_CLOCKS
## 
## @details
##     - Provides the set of frequencies as a list and as a range/step.
##     - It is generally recommended that applications choose frequencies from
##       the list. However applications can also construct the list themselves
##       using the range/steps provided.
class xet_freq_prop_avail_clocks_t(Structure):
    _fields_ = [
        ("minFP16_16", c_ulong),                                        ## [out] The minimum clock frequency in units of MHz (fixed point
                                                                        ## U16.16).
        ("maxFP16_16", c_ulong),                                        ## [out] The maximum clock frequency in units of MHz (fixed point
                                                                        ## U16.16).
        ("stepFP16_16", c_ulong),                                       ## [out] The step clock frequency in units of MHz (fixed point U16.16).
        ("num", c_ulong),                                               ## [out] The number of clocks
        ("pClocksFP16_16", POINTER(c_ulong))                            ## [out] Array of clock frequencies in units of MHz (fixed-point U16.16)
                                                                        ## ordered from smallest to largest.
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_AVAIL_DIVIDERS
## 
## @details
##     - The list is ordered from the smallest ratio to the largest ratio.
class xet_freq_prop_avail_dividers_t(Structure):
    _fields_ = [
        ("num", c_ulong),                                               ## [out] The number of dividers
        ("pDividers", POINTER(xet_freq_divider_t))                      ## [out] Array of numerator/denominator for each divider
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_AVAIL_MULTIPLIERS
## 
## @details
##     - The range of multiplier values.
class xet_freq_prop_avail_multipliers_t(Structure):
    _fields_ = [
        ("minFP8_8", c_ushort),                                         ## [out] The minimum multiplier value in fixed-point U8.8 format
        ("maxFP8_8", c_ushort),                                         ## [out] The maximum multiplier value in fixed-point U8.8 format
        ("minStepFP8_8", c_ushort)                                      ## [out] The smallest multiplier step size in fixed-point U8.8
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_SRC_FREQ
class xet_freq_prop_src_freq_t(Structure):
    _fields_ = [
        ("resourceId", xet_resource_id_t)                               ## [out] The resource ID of the source frequency domain
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_REQUEST
class xet_freq_prop_freq_request_t(Structure):
    _fields_ = [
        ("mode", xet_freq_mode_t),                                      ## [in,out] The frequency mode
        ("freqRequest", c_ulong)                                        ## [out] The current frequency request in MHz. If setting this property,
                                                                        ## the value will be used if mode is ::XET_FREQ_MODE_FIXED, otherwise the
                                                                        ## hardware will take back control.
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_DIVIDER
class xet_freq_prop_freq_divider_t(Structure):
    _fields_ = [
        ("mode", xet_freq_mode_t),                                      ## [in,out] The frequency mode
        ("divider", xet_freq_divider_t)                                 ## [in,out] The frequency divider. If setting this property, the value
                                                                        ## will be used if mode is ::XET_FREQ_MODE_FIXED, otherwise the hardware
                                                                        ## will take back control.
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_MULTIPLIER
class xet_freq_prop_freq_multiplier_t(Structure):
    _fields_ = [
        ("mode", xet_freq_mode_t),                                      ## [in,out] The frequency mode
        ("multiplier", xet_freq_multiplier_t)                           ## [in,out] The frequency multiplier. If setting this property, the value
                                                                        ## will be used if mode is ::XET_FREQ_MODE_FIXED, otherwise the hardware
                                                                        ## will take back control.
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_TDP
class xet_freq_prop_freq_tdp_t(Structure):
    _fields_ = [
        ("freqTdp", c_ulong)                                            ## [out] The maximum frequency in MHz supported under the current TDP
                                                                        ## conditions
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_EFFICIENT
class xet_freq_prop_freq_efficient_t(Structure):
    _fields_ = [
        ("freqEfficient", c_ulong)                                      ## [out] The efficient minimum frequency in MHz
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_RESOLVED
class xet_freq_prop_freq_resolved_t(Structure):
    _fields_ = [
        ("freqResolved", c_ulong)                                       ## [out] The resolved frequency in MHz
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_THROTTLE_REASONS
class xet_freq_prop_throttle_reasons_t(Structure):
    _fields_ = [
        ("throttleReasons", c_ulong)                                    ## [out] The reasons that the frequency is being limited by the PCU
                                                                        ## (Bitfield of (1<<::xet_freq_throttle_reasons_t)).
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_THROTTLE_TIME
class xet_freq_prop_throttle_time_t(Structure):
    _fields_ = [
        ("throttleTime", c_ulong)                                       ## [out] The total time in microseconds that the frequency has been
                                                                        ## limited by the PCU.
    ]

###############################################################################
## @brief Request structure to determine frequency domain resource properties
##        that are supported/accessible
class xet_freq_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_freq_properties_t),                            ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a frequency domain resource property
class xet_freq_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the frequency domain resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_FREQ]-1)
        ("property", xet_freq_properties_t),                            ## [in] The property being requested (one of ::xet_freq_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
    ]

###############################################################################
## @brief Power-well domain promotion modes
class xet_pwrwell_promo_mode_v(IntEnum):
    IMMEDIATE = 0                                   ## The power-well will shutdown immediately when all contained units are
                                                    ## idle.
    EFFICIENT = auto()                              ## Favor energy savings over performance. The power-well is more likely
                                                    ## to shutdown when all contained units are idle, even if this will cause
                                                    ## some performance degredation.
    DEFAULT = auto()                                ## Best compromise between performance and energy savings.
    PERFORMANCE = auto()                            ## Favor performance over energy savings. The power-well is more likely
                                                    ## to stay on when all contained units are idle since it has dedicated
                                                    ## that more work will be executing shortly.
    NEVER = auto()                                  ## The power-well will never shutdown. This can improve performance but
                                                    ## uses more energy.

class xet_pwrwell_promo_mode_t(c_int):
    def __str__(self):
        return str(xet_pwrwell_promo_mode_v(value))


###############################################################################
## @brief Power-well domain resource properties
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
class xet_pwrwell_properties_v(IntEnum):
    PWRWELL_PROP_ACCEL_ASSETS = 0                   ## (ro static) List of accelerator assets that are connected to this
                                                    ## power-well domain (data: ::xet_pwrwell_prop_accel_assets_t)
    PWRWELL_PROP_PROMO_CAP = auto()                 ## (ro static) Find out if the power-well domain has a programmable
                                                    ## promotion setting (data: ::xet_pwrwell_prop_promo_cap_t)
    PWRWELL_PROP_PROMO_MODE = auto()                ## (rw dynamic) The current promotion mode (data:
                                                    ## ::xet_pwrwell_prop_promo_mode_t)
    PWRWELL_PROP_UTILIZATION = auto()               ## (ro dynamic) Monotonic counters for the amount of time the power-well
                                                    ## is off/idle/active (data: ::xet_pwrwell_prop_utilization_t)
    PWRWELL_PROP_TRANSITIONS = auto()               ## (ro dynamic) The monotonic counter for the number of times that the
                                                    ## power-well has transitioned between off/idle/active states (data:
                                                    ## ::xet_pwrwell_prop_transitions_t)

class xet_pwrwell_properties_t(c_int):
    def __str__(self):
        return str(xet_pwrwell_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_ACCEL_ASSETS
class xet_pwrwell_prop_accel_assets_t(Structure):
    _fields_ = [
        ("assets", c_ulonglong)                                         ## [out] List of accelerator assets that are connected to this power-well
                                                                        ## domain (bitfield of (1<<::xet_accel_asset_t)).
    ]

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_PROMO_CAP
class xet_pwrwell_prop_promo_cap_t(Structure):
    _fields_ = [
        ("canChangePromoMode", xe_bool_t)                               ## [out] Indicates if the power-well domain has a programmable promotion
                                                                        ## setting.
    ]

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_PROMO_MODE
class xet_pwrwell_prop_promo_mode_t(Structure):
    _fields_ = [
        ("mode", xet_pwrwell_promo_mode_t)                              ## [in,out] Current promotion mode
    ]

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_UTILIZATION
class xet_pwrwell_prop_utilization_t(Structure):
    _fields_ = [
        ("sleepCounter", c_ulong),                                      ## [out] The monotonic counter for the amount of time in microseconds
                                                                        ## that the power-well is off.
        ("idleCounter", c_ulong),                                       ## [out] The monotonic counter for the amount of time in microseconds
                                                                        ## that the power-well is on but not executing any accelerator workloads.
        ("activeCounter", c_ulong)                                      ## [out] The monotonic counter for the amount of time the power-well is
                                                                        ## on and executing accelerator workloads.
    ]

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_TRANSITIONS
class xet_pwrwell_prop_transitions_t(Structure):
    _fields_ = [
        ("wakeCounter", c_ulong),                                       ## [out] The monotonic counter for the number of times that the
                                                                        ## power-well has transitioned from a sleep state to a powered on state.
        ("execCounter", c_ulong)                                        ## [out] The monotonic counter for the number of times that the
                                                                        ## power-well has transitioned from a sleep or idle state to an active
                                                                        ## state.
    ]

###############################################################################
## @brief Request structure to determine power-well domain resource properties
##        that are supported/accessible
class xet_pwrwell_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_pwrwell_properties_t),                         ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a power-well domain resource property
class xet_pwrwell_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the power-well domain resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_PWRWELL]-1)
        ("property", xet_pwrwell_properties_t),                         ## [in] The property being requested (one of ::xet_pwrwell_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
    ]

###############################################################################
## @brief Accelerator asset resource properties
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
class xet_accel_properties_v(IntEnum):
    ACCEL_PROP_ACCEL_ASSETS = 0                     ## (ro static) List of accelerator assets that contribute to counters in
                                                    ## this resource (data: ::xet_accel_prop_accel_assets_t)
    ACCEL_PROP_UTILIZATION = auto()                 ## (ro dynamic) The total wall time accelerator assets in this resource
                                                    ## are active (data: ::xet_accel_prop_utilization_t)

class xet_accel_properties_t(c_int):
    def __str__(self):
        return str(xet_accel_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_ACCEL_PROP_ACCEL_ASSETS
class xet_accel_prop_accel_assets_t(Structure):
    _fields_ = [
        ("assets", c_ulonglong)                                         ## [out] List of accelerator assets that contribute to counters in this
                                                                        ## resource (bitfield of (1<<::xet_accel_asset_t)).
    ]

###############################################################################
## @brief Data for the property ::XET_ACCEL_PROP_UTILIZATION
class xet_accel_prop_utilization_t(Structure):
    _fields_ = [
        ("activeCounter", c_ulong),                                     ## [out] Monotonic counter for total wall time in microseconds that
                                                                        ## accelerator assets in this resource are active.
        ("idleCounter", c_ulong)                                        ## [out] Monotonic counter for total wall time in microseconds that no
                                                                        ## accelerator assets in this resource are active.
    ]

###############################################################################
## @brief Request structure to determine accelerator resource properties that
##        are supported/accessible
class xet_accel_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_accel_properties_t),                           ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query an accelerator resource property
class xet_accel_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the accelerator resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_ACCEL]-1)
        ("property", xet_accel_properties_t),                           ## [in] The property being requested (one of ::xet_accel_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
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
## @brief Memory retire reasons
class xet_mem_retire_reason_v(IntEnum):
    MULTIPLE_SINGLE_BIT_ERRORS = 0                  ## Memory page has been retired due to multiple single bit ECC errors
    DOUBLE_BIT_ERRORS = auto()                      ## Memory page has been retired due to one or more double bit ECC errors

class xet_mem_retire_reason_t(c_int):
    def __str__(self):
        return str(xet_mem_retire_reason_v(value))


###############################################################################
## @brief Retired page info
class xet_mem_retire_info_t(Structure):
    _fields_ = [
        ("address", c_ulonglong),                                       ## [out] The address of the page
        ("reason", xet_mem_retire_reason_t)                             ## [out] The reason the page was retired
    ]

###############################################################################
## @brief Memory resource properties
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
class xet_mem_properties_v(IntEnum):
    MEM_PROP_TYPE = 0                               ## (ro static) The type of memory covered by this resource (data:
                                                    ## ::xet_mem_prop_type_t)
    MEM_PROP_UTILIZATION = auto()                   ## (ro dynamic) Get current allocated/unallocated size (data:
                                                    ## ::xet_mem_prop_utilization_t)
    MEM_PROP_BANDWIDTH = auto()                     ## (ro dynamic) Get current read/write bandwidth counters and maximum
                                                    ## bandwidth (data: ::xet_mem_prop_bandwidth_t)

class xet_mem_properties_t(c_int):
    def __str__(self):
        return str(xet_mem_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_MEM_PROP_TYPE
class xet_mem_prop_type_t(Structure):
    _fields_ = [
        ("type", xet_mem_type_t)                                        ## [out] The memory type
    ]

###############################################################################
## @brief Data for the property ::XET_MEM_PROP_UTILIZATION
## 
## @details
##     - The total physical memory is the sum of all others (stolen + bad +
##       allocated + unallocated).
##     - Percent software memory utilization given by 100 * allocated /
##       (allocated + unallocated).
##     - Percent bad memory given by 100 * bad / total
class xet_mem_prop_utilization_t(Structure):
    _fields_ = [
        ("total", c_ulonglong),                                         ## [out] The total physical memory in bytes
        ("stolen", c_ulonglong),                                        ## [out] The total stolen memory in bytes
        ("bad", c_ulonglong),                                           ## [out] The total bad memory in bytes
        ("allocated", c_ulonglong),                                     ## [out] The total allocated bytes
        ("unallocated", c_ulonglong)                                    ## [out] The total unallocated bytes
    ]

###############################################################################
## @brief Data for the property ::XET_MEM_PROP_BANDWIDTH
class xet_mem_prop_bandwidth_t(Structure):
    _fields_ = [
        ("readCounter", c_ulong),                                       ## [out] Total bytes read from memory
        ("writeCounter", c_ulong),                                      ## [out] Total bytes written to memory
        ("maxBandwidth", c_ulong)                                       ## [out] Current maximum bandwidth in units of bytes/sec
    ]

###############################################################################
## @brief Request structure to determine memory resource properties that are
##        supported/accessible
class xet_mem_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_mem_properties_t),                             ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a memory resource property
class xet_mem_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the memory resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_MEM]-1)
        ("property", xet_mem_properties_t),                             ## [in] The property being requested (one of ::xet_mem_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
    ]

###############################################################################
## @brief Link resource types
class xet_link_type_v(IntEnum):
    PCI = 0                                         ## PCI connection
    PEER_TO_PEER = auto()                           ## Peer-to-peer connection

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
## @brief Link resource properties
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
class xet_link_properties_v(IntEnum):
    LINK_PROP_TYPE = 0                              ## (ro static) The type of link (data: ::xet_link_prop_type_t)
    LINK_PROP_BUS_ADDRESS = auto()                  ## (ro static) The bus address of the link (data:
                                                    ## ::xet_link_prop_bus_address_t)
    LINK_PROP_PWR_CAP = auto()                      ## (ro static) Indicates if the link frequency can adjust to control
                                                    ## power (data: ::xet_link_prop_pwr_cap_t)
    LINK_PROP_AVAIL_SPEEDS = auto()                 ## (ro static) Available link speeds (data:
                                                    ## ::xet_link_prop_avail_speeds_t)
    LINK_PROP_MAX_PACKET_SIZE = auto()              ## (ro static) Maximum packet size (data:
                                                    ## ::xet_link_prop_max_packet_size_t)
    LINK_PROP_BANDWIDTH = auto()                    ## (ro dynamic) Monotonic bandwidth counters (data:
                                                    ## ::xet_link_prop_bandwidth_t)
    LINK_PROP_SPEED = auto()                        ## (ro dynamic) Current link speed (data: ::xet_link_prop_speed_t)
    LINK_PROP_SPEED_RANGE = auto()                  ## (wo dynamic) Set the min/max speeds between which the link can operate
                                                    ## (data: ::xet_link_prop_speed_range_t)

class xet_link_properties_t(c_int):
    def __str__(self):
        return str(xet_link_properties_v(value))


###############################################################################
## @brief Data for property ::XET_LINK_PROP_TYPE
class xet_link_prop_type_t(Structure):
    _fields_ = [
        ("type", xet_link_type_t)                                       ## [out] The type of link
    ]

###############################################################################
## @brief Data for property ::XET_LINK_PROP_BUS_ADDRESS
class xet_link_prop_bus_address_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for the property ::XET_LINK_PROP_PWR_CAP
class xet_link_prop_pwr_cap_t(Structure):
    _fields_ = [
        ("havePwrMgmt", xe_bool_t)                                      ## [out] Indicates if the link frequency can adjust to control power.
    ]

###############################################################################
## @brief Data for the property ::XET_LINK_PROP_AVAIL_SPEEDS
## 
## @details
##     - The list is ordered from the smallest ratio to the largest ratio.
class xet_link_prop_avail_speeds_t(Structure):
    _fields_ = [
        ("num", c_ulong),                                               ## [out] The number of elements in pList
        ("pList", POINTER(xet_link_speed_t))                            ## [out][range(0, num-1)] Pointer to an array of link speeds
    ]

###############################################################################
## @brief Data for the property ::XET_LINK_PROP_MAX_PACKET_SIZE
class xet_link_prop_max_packet_size_t(Structure):
    _fields_ = [
        ("maxPacketSize", c_ulong)                                      ## [out] Maximum packet size in bytes.
    ]

###############################################################################
## @brief Data for the property ::XET_LINK_PROP_BANDWIDTH
class xet_link_prop_bandwidth_t(Structure):
    _fields_ = [
        ("recvCounter", c_ulong),                                       ## [out] Total bytes received across the link
        ("sendCounter", c_ulong),                                       ## [out] Total bytes sent across the link
        ("maxBandwidth", c_ulong)                                       ## [out] Maximum bytes/sec that can be transfered acros the link
    ]

###############################################################################
## @brief Data for the property ::XET_LINK_PROP_SPEED
class xet_link_prop_speed_t(Structure):
    _fields_ = [
        ("pSpeed", POINTER(xet_link_speed_t))                           ## [out] Pointer to the current speed configuration
    ]

###############################################################################
## @brief Data for the property ::XET_LINK_PROP_SPEED_RANGE
class xet_link_prop_speed_range_t(Structure):
    _fields_ = [
        ("pMinSpeed", POINTER(xet_link_speed_t)),                       ## [out] Pointer to the min speed configuration (one of those in the
                                                                        ## array returned by property ::XET_LINK_PROP_AVAIL_SPEEDS)
        ("pMaxSpeed", POINTER(xet_link_speed_t))                        ## [out] Pointer to the max speed configuration (one of those in the
                                                                        ## array returned by property ::XET_LINK_PROP_AVAIL_SPEEDS)
    ]

###############################################################################
## @brief Request structure to determine link resource properties that are
##        supported/accessible
class xet_link_prop_capability_t(Structure):
    _fields_ = [
        ("property", xet_link_properties_t),                            ## [in] The property
        ("support", xet_prop_support_t),                                ## [out] API support for the property
        ("access", xet_prop_access_t),                                  ## [out] The access permissions for the property
        ("minSampleRate", c_ulong)                                      ## [out] The minimum rate in microseconds that this property can be
                                                                        ## polled
    ]

###############################################################################
## @brief Request structure used to query a link resource property
class xet_link_property_request_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [in] The index of the link resource (0 ...
                                                                        ## ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_LINK]-1)
        ("property", xet_link_properties_t),                            ## [in] The property being requested (one of ::xet_link_properties_t).
        ("pData", c_void_p),                                            ## [in] Pointer to the data for the property.
                                                                        ## Each property has a corresponding data structure. The type of the data
                                                                        ## structure is derived from the property enumerator, converted to
                                                                        ## lower-case with "_t" appended.
        ("size", c_ulong)                                               ## [in] The size of the data structure pointed to by pData.
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
        ("resourceId", xet_resource_id_t),                              ## [in] Only events being generated by the specified resource. If
                                                                        ## ::XET_RESOURCE_ID_ANY, then applies to all events from all resources
                                                                        ## in the device.
        ("threshold", c_ulong)                                          ## [in] The application only receives a notification when the total count
                                                                        ## exceeds this value. Set to zero to receive a notification for every
                                                                        ## new event.
    ]

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
    FAILED = auto()                                 ## Diagnostic had problems running tests or attempting to setup repairs
    REBOOT_FOR_REPAIR = auto()                      ## Diagnostics found errors, setup for repair and reboot is required to
                                                    ## complete the process

class xet_diag_result_t(c_int):
    def __str__(self):
        return str(xet_diag_result_v(value))


###############################################################################
## @brief Wait infinitely for events to arrive.
XET_EVENT_WAIT_INFINITE = 0xFFFFFFFF

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
## @brief Function-pointer for xetSysmanCreate
if __use_win_types:
    _xetSysmanCreate_t = WINFUNCTYPE( xe_result_t, xet_device_handle_t, xet_sysman_version_t, c_ulong, POINTER(xet_sysman_handle_t) )
else:
    _xetSysmanCreate_t = CFUNCTYPE( xe_result_t, xet_device_handle_t, xet_sysman_version_t, c_ulong, POINTER(xet_sysman_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanDestroy
if __use_win_types:
    _xetSysmanDestroy_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t )
else:
    _xetSysmanDestroy_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t )

###############################################################################
## @brief Function-pointer for xetSysmanGetAccelAssetName
if __use_win_types:
    _xetSysmanGetAccelAssetName_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_accel_asset_t, POINTER(c_char*) )
else:
    _xetSysmanGetAccelAssetName_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_accel_asset_t, POINTER(c_char*) )

###############################################################################
## @brief Function-pointer for xetSysmanGetInfo
if __use_win_types:
    _xetSysmanGetInfo_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_sysman_info_t) )
else:
    _xetSysmanGetInfo_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_sysman_info_t) )

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
## @brief Function-pointer for xetSysmanAvailableDeviceProperties
if __use_win_types:
    _xetSysmanAvailableDeviceProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_device_prop_capability_t) )
else:
    _xetSysmanAvailableDeviceProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_device_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetDeviceProperties
if __use_win_types:
    _xetSysmanGetDeviceProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_device_property_request_t) )
else:
    _xetSysmanGetDeviceProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_device_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetDeviceProperties
if __use_win_types:
    _xetSysmanSetDeviceProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_device_property_request_t) )
else:
    _xetSysmanSetDeviceProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_device_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailablePsuProperties
if __use_win_types:
    _xetSysmanAvailablePsuProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_psu_prop_capability_t) )
else:
    _xetSysmanAvailablePsuProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_psu_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetPsuProperties
if __use_win_types:
    _xetSysmanGetPsuProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_psu_property_request_t) )
else:
    _xetSysmanGetPsuProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_psu_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetPsuProperties
if __use_win_types:
    _xetSysmanSetPsuProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_psu_property_request_t) )
else:
    _xetSysmanSetPsuProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_psu_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailableTempProperties
if __use_win_types:
    _xetSysmanAvailableTempProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_temp_prop_capability_t) )
else:
    _xetSysmanAvailableTempProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_temp_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetTempProperties
if __use_win_types:
    _xetSysmanGetTempProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_temp_property_request_t) )
else:
    _xetSysmanGetTempProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_temp_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailableFanProperties
if __use_win_types:
    _xetSysmanAvailableFanProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_fan_prop_capability_t) )
else:
    _xetSysmanAvailableFanProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_fan_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetFanProperties
if __use_win_types:
    _xetSysmanGetFanProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_fan_property_request_t) )
else:
    _xetSysmanGetFanProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_fan_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetFanProperties
if __use_win_types:
    _xetSysmanSetFanProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_fan_property_request_t) )
else:
    _xetSysmanSetFanProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_fan_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailableLedProperties
if __use_win_types:
    _xetSysmanAvailableLedProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_led_prop_capability_t) )
else:
    _xetSysmanAvailableLedProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_led_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetLedProperties
if __use_win_types:
    _xetSysmanGetLedProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_led_property_request_t) )
else:
    _xetSysmanGetLedProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_led_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetLedProperties
if __use_win_types:
    _xetSysmanSetLedProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_led_property_request_t) )
else:
    _xetSysmanSetLedProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_led_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailableFirmwareProperties
if __use_win_types:
    _xetSysmanAvailableFirmwareProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_firmware_prop_capability_t) )
else:
    _xetSysmanAvailableFirmwareProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_firmware_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetFirmwareProperties
if __use_win_types:
    _xetSysmanGetFirmwareProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_firmware_property_request_t) )
else:
    _xetSysmanGetFirmwareProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_firmware_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetFirmwareProperties
if __use_win_types:
    _xetSysmanSetFirmwareProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_firmware_property_request_t) )
else:
    _xetSysmanSetFirmwareProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_firmware_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailablePwrProperties
if __use_win_types:
    _xetSysmanAvailablePwrProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwr_prop_capability_t) )
else:
    _xetSysmanAvailablePwrProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwr_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetPwrProperties
if __use_win_types:
    _xetSysmanGetPwrProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwr_property_request_t) )
else:
    _xetSysmanGetPwrProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwr_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetPwrProperties
if __use_win_types:
    _xetSysmanSetPwrProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwr_property_request_t) )
else:
    _xetSysmanSetPwrProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwr_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailableFreqProperties
if __use_win_types:
    _xetSysmanAvailableFreqProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_freq_prop_capability_t) )
else:
    _xetSysmanAvailableFreqProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_freq_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetFreqProperties
if __use_win_types:
    _xetSysmanGetFreqProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_freq_property_request_t) )
else:
    _xetSysmanGetFreqProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_freq_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetFreqProperties
if __use_win_types:
    _xetSysmanSetFreqProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_freq_property_request_t) )
else:
    _xetSysmanSetFreqProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_freq_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailablePwrwellProperties
if __use_win_types:
    _xetSysmanAvailablePwrwellProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwrwell_prop_capability_t) )
else:
    _xetSysmanAvailablePwrwellProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwrwell_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetPwrwellProperties
if __use_win_types:
    _xetSysmanGetPwrwellProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwrwell_property_request_t) )
else:
    _xetSysmanGetPwrwellProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwrwell_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetPwrwellProperties
if __use_win_types:
    _xetSysmanSetPwrwellProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwrwell_property_request_t) )
else:
    _xetSysmanSetPwrwellProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_pwrwell_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailableAccelProperties
if __use_win_types:
    _xetSysmanAvailableAccelProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_accel_prop_capability_t) )
else:
    _xetSysmanAvailableAccelProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_accel_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetAccelProperties
if __use_win_types:
    _xetSysmanGetAccelProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_accel_property_request_t) )
else:
    _xetSysmanGetAccelProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_accel_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailableMemProperties
if __use_win_types:
    _xetSysmanAvailableMemProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_mem_prop_capability_t) )
else:
    _xetSysmanAvailableMemProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_mem_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetMemProperties
if __use_win_types:
    _xetSysmanGetMemProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_mem_property_request_t) )
else:
    _xetSysmanGetMemProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_mem_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetMemProperties
if __use_win_types:
    _xetSysmanSetMemProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_mem_property_request_t) )
else:
    _xetSysmanSetMemProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_mem_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanAvailableLinkProperties
if __use_win_types:
    _xetSysmanAvailableLinkProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_link_prop_capability_t) )
else:
    _xetSysmanAvailableLinkProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_link_prop_capability_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetLinkProperties
if __use_win_types:
    _xetSysmanGetLinkProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_link_property_request_t) )
else:
    _xetSysmanGetLinkProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_link_property_request_t) )

###############################################################################
## @brief Function-pointer for xetSysmanSetLinkProperties
if __use_win_types:
    _xetSysmanSetLinkProperties_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_link_property_request_t) )
else:
    _xetSysmanSetLinkProperties_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, c_ulong, POINTER(xet_link_property_request_t) )

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
## @brief Function-pointer for xetSysmanRunDiagnostics
if __use_win_types:
    _xetSysmanRunDiagnostics_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_diag_type_t, POINTER(xet_diag_result_t) )
else:
    _xetSysmanRunDiagnostics_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_diag_type_t, POINTER(xet_diag_result_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetEvents
if __use_win_types:
    _xetSysmanGetEvents_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, c_ulong, POINTER(c_ulong) )
else:
    _xetSysmanGetEvents_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, c_ulong, POINTER(c_ulong) )


###############################################################################
## @brief Table of Sysman functions pointers
class _xet_sysman_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xetSysmanCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xetSysmanDestroy_t
        ("pfnGetAccelAssetName", c_void_p),                             ## _xetSysmanGetAccelAssetName_t
        ("pfnGetInfo", c_void_p),                                       ## _xetSysmanGetInfo_t
        ("pfnRasSetup", c_void_p),                                      ## _xetSysmanRasSetup_t
        ("pfnGetRasErrors", c_void_p),                                  ## _xetSysmanGetRasErrors_t
        ("pfnAvailableDeviceProperties", c_void_p),                     ## _xetSysmanAvailableDeviceProperties_t
        ("pfnGetDeviceProperties", c_void_p),                           ## _xetSysmanGetDeviceProperties_t
        ("pfnSetDeviceProperties", c_void_p),                           ## _xetSysmanSetDeviceProperties_t
        ("pfnAvailablePsuProperties", c_void_p),                        ## _xetSysmanAvailablePsuProperties_t
        ("pfnGetPsuProperties", c_void_p),                              ## _xetSysmanGetPsuProperties_t
        ("pfnSetPsuProperties", c_void_p),                              ## _xetSysmanSetPsuProperties_t
        ("pfnAvailableTempProperties", c_void_p),                       ## _xetSysmanAvailableTempProperties_t
        ("pfnGetTempProperties", c_void_p),                             ## _xetSysmanGetTempProperties_t
        ("pfnAvailableFanProperties", c_void_p),                        ## _xetSysmanAvailableFanProperties_t
        ("pfnGetFanProperties", c_void_p),                              ## _xetSysmanGetFanProperties_t
        ("pfnSetFanProperties", c_void_p),                              ## _xetSysmanSetFanProperties_t
        ("pfnAvailableLedProperties", c_void_p),                        ## _xetSysmanAvailableLedProperties_t
        ("pfnGetLedProperties", c_void_p),                              ## _xetSysmanGetLedProperties_t
        ("pfnSetLedProperties", c_void_p),                              ## _xetSysmanSetLedProperties_t
        ("pfnAvailableFirmwareProperties", c_void_p),                   ## _xetSysmanAvailableFirmwareProperties_t
        ("pfnGetFirmwareProperties", c_void_p),                         ## _xetSysmanGetFirmwareProperties_t
        ("pfnSetFirmwareProperties", c_void_p),                         ## _xetSysmanSetFirmwareProperties_t
        ("pfnAvailablePwrProperties", c_void_p),                        ## _xetSysmanAvailablePwrProperties_t
        ("pfnGetPwrProperties", c_void_p),                              ## _xetSysmanGetPwrProperties_t
        ("pfnSetPwrProperties", c_void_p),                              ## _xetSysmanSetPwrProperties_t
        ("pfnAvailableFreqProperties", c_void_p),                       ## _xetSysmanAvailableFreqProperties_t
        ("pfnGetFreqProperties", c_void_p),                             ## _xetSysmanGetFreqProperties_t
        ("pfnSetFreqProperties", c_void_p),                             ## _xetSysmanSetFreqProperties_t
        ("pfnAvailablePwrwellProperties", c_void_p),                    ## _xetSysmanAvailablePwrwellProperties_t
        ("pfnGetPwrwellProperties", c_void_p),                          ## _xetSysmanGetPwrwellProperties_t
        ("pfnSetPwrwellProperties", c_void_p),                          ## _xetSysmanSetPwrwellProperties_t
        ("pfnAvailableAccelProperties", c_void_p),                      ## _xetSysmanAvailableAccelProperties_t
        ("pfnGetAccelProperties", c_void_p),                            ## _xetSysmanGetAccelProperties_t
        ("pfnAvailableMemProperties", c_void_p),                        ## _xetSysmanAvailableMemProperties_t
        ("pfnGetMemProperties", c_void_p),                              ## _xetSysmanGetMemProperties_t
        ("pfnSetMemProperties", c_void_p),                              ## _xetSysmanSetMemProperties_t
        ("pfnAvailableLinkProperties", c_void_p),                       ## _xetSysmanAvailableLinkProperties_t
        ("pfnGetLinkProperties", c_void_p),                             ## _xetSysmanGetLinkProperties_t
        ("pfnSetLinkProperties", c_void_p),                             ## _xetSysmanSetLinkProperties_t
        ("pfnSupportedEvents", c_void_p),                               ## _xetSysmanSupportedEvents_t
        ("pfnRegisterEvents", c_void_p),                                ## _xetSysmanRegisterEvents_t
        ("pfnUnregisterEvents", c_void_p),                              ## _xetSysmanUnregisterEvents_t
        ("pfnRunDiagnostics", c_void_p),                                ## _xetSysmanRunDiagnostics_t
        ("pfnGetEvents", c_void_p)                                      ## _xetSysmanGetEvents_t
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
        self.xetSysmanCreate = _xetSysmanCreate_t(self.__dditable.Sysman.pfnCreate)
        self.xetSysmanDestroy = _xetSysmanDestroy_t(self.__dditable.Sysman.pfnDestroy)
        self.xetSysmanGetAccelAssetName = _xetSysmanGetAccelAssetName_t(self.__dditable.Sysman.pfnGetAccelAssetName)
        self.xetSysmanGetInfo = _xetSysmanGetInfo_t(self.__dditable.Sysman.pfnGetInfo)
        self.xetSysmanRasSetup = _xetSysmanRasSetup_t(self.__dditable.Sysman.pfnRasSetup)
        self.xetSysmanGetRasErrors = _xetSysmanGetRasErrors_t(self.__dditable.Sysman.pfnGetRasErrors)
        self.xetSysmanAvailableDeviceProperties = _xetSysmanAvailableDeviceProperties_t(self.__dditable.Sysman.pfnAvailableDeviceProperties)
        self.xetSysmanGetDeviceProperties = _xetSysmanGetDeviceProperties_t(self.__dditable.Sysman.pfnGetDeviceProperties)
        self.xetSysmanSetDeviceProperties = _xetSysmanSetDeviceProperties_t(self.__dditable.Sysman.pfnSetDeviceProperties)
        self.xetSysmanAvailablePsuProperties = _xetSysmanAvailablePsuProperties_t(self.__dditable.Sysman.pfnAvailablePsuProperties)
        self.xetSysmanGetPsuProperties = _xetSysmanGetPsuProperties_t(self.__dditable.Sysman.pfnGetPsuProperties)
        self.xetSysmanSetPsuProperties = _xetSysmanSetPsuProperties_t(self.__dditable.Sysman.pfnSetPsuProperties)
        self.xetSysmanAvailableTempProperties = _xetSysmanAvailableTempProperties_t(self.__dditable.Sysman.pfnAvailableTempProperties)
        self.xetSysmanGetTempProperties = _xetSysmanGetTempProperties_t(self.__dditable.Sysman.pfnGetTempProperties)
        self.xetSysmanAvailableFanProperties = _xetSysmanAvailableFanProperties_t(self.__dditable.Sysman.pfnAvailableFanProperties)
        self.xetSysmanGetFanProperties = _xetSysmanGetFanProperties_t(self.__dditable.Sysman.pfnGetFanProperties)
        self.xetSysmanSetFanProperties = _xetSysmanSetFanProperties_t(self.__dditable.Sysman.pfnSetFanProperties)
        self.xetSysmanAvailableLedProperties = _xetSysmanAvailableLedProperties_t(self.__dditable.Sysman.pfnAvailableLedProperties)
        self.xetSysmanGetLedProperties = _xetSysmanGetLedProperties_t(self.__dditable.Sysman.pfnGetLedProperties)
        self.xetSysmanSetLedProperties = _xetSysmanSetLedProperties_t(self.__dditable.Sysman.pfnSetLedProperties)
        self.xetSysmanAvailableFirmwareProperties = _xetSysmanAvailableFirmwareProperties_t(self.__dditable.Sysman.pfnAvailableFirmwareProperties)
        self.xetSysmanGetFirmwareProperties = _xetSysmanGetFirmwareProperties_t(self.__dditable.Sysman.pfnGetFirmwareProperties)
        self.xetSysmanSetFirmwareProperties = _xetSysmanSetFirmwareProperties_t(self.__dditable.Sysman.pfnSetFirmwareProperties)
        self.xetSysmanAvailablePwrProperties = _xetSysmanAvailablePwrProperties_t(self.__dditable.Sysman.pfnAvailablePwrProperties)
        self.xetSysmanGetPwrProperties = _xetSysmanGetPwrProperties_t(self.__dditable.Sysman.pfnGetPwrProperties)
        self.xetSysmanSetPwrProperties = _xetSysmanSetPwrProperties_t(self.__dditable.Sysman.pfnSetPwrProperties)
        self.xetSysmanAvailableFreqProperties = _xetSysmanAvailableFreqProperties_t(self.__dditable.Sysman.pfnAvailableFreqProperties)
        self.xetSysmanGetFreqProperties = _xetSysmanGetFreqProperties_t(self.__dditable.Sysman.pfnGetFreqProperties)
        self.xetSysmanSetFreqProperties = _xetSysmanSetFreqProperties_t(self.__dditable.Sysman.pfnSetFreqProperties)
        self.xetSysmanAvailablePwrwellProperties = _xetSysmanAvailablePwrwellProperties_t(self.__dditable.Sysman.pfnAvailablePwrwellProperties)
        self.xetSysmanGetPwrwellProperties = _xetSysmanGetPwrwellProperties_t(self.__dditable.Sysman.pfnGetPwrwellProperties)
        self.xetSysmanSetPwrwellProperties = _xetSysmanSetPwrwellProperties_t(self.__dditable.Sysman.pfnSetPwrwellProperties)
        self.xetSysmanAvailableAccelProperties = _xetSysmanAvailableAccelProperties_t(self.__dditable.Sysman.pfnAvailableAccelProperties)
        self.xetSysmanGetAccelProperties = _xetSysmanGetAccelProperties_t(self.__dditable.Sysman.pfnGetAccelProperties)
        self.xetSysmanAvailableMemProperties = _xetSysmanAvailableMemProperties_t(self.__dditable.Sysman.pfnAvailableMemProperties)
        self.xetSysmanGetMemProperties = _xetSysmanGetMemProperties_t(self.__dditable.Sysman.pfnGetMemProperties)
        self.xetSysmanSetMemProperties = _xetSysmanSetMemProperties_t(self.__dditable.Sysman.pfnSetMemProperties)
        self.xetSysmanAvailableLinkProperties = _xetSysmanAvailableLinkProperties_t(self.__dditable.Sysman.pfnAvailableLinkProperties)
        self.xetSysmanGetLinkProperties = _xetSysmanGetLinkProperties_t(self.__dditable.Sysman.pfnGetLinkProperties)
        self.xetSysmanSetLinkProperties = _xetSysmanSetLinkProperties_t(self.__dditable.Sysman.pfnSetLinkProperties)
        self.xetSysmanSupportedEvents = _xetSysmanSupportedEvents_t(self.__dditable.Sysman.pfnSupportedEvents)
        self.xetSysmanRegisterEvents = _xetSysmanRegisterEvents_t(self.__dditable.Sysman.pfnRegisterEvents)
        self.xetSysmanUnregisterEvents = _xetSysmanUnregisterEvents_t(self.__dditable.Sysman.pfnUnregisterEvents)
        self.xetSysmanRunDiagnostics = _xetSysmanRunDiagnostics_t(self.__dditable.Sysman.pfnRunDiagnostics)
        self.xetSysmanGetEvents = _xetSysmanGetEvents_t(self.__dditable.Sysman.pfnGetEvents)

        # success!
