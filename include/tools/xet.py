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
## @brief Invalid System Resource Management handle
XET_INVALID_SYSMAN_HANDLE = NULL

###############################################################################
## @brief Handle for a Sysman resource container
class xet_res_container_handle_t(c_void_p):
    pass

###############################################################################
## @brief Invalid Sysman resource container handle
XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE = NULL

###############################################################################
## @brief Handle for a Sysman resource
class xet_resource_handle_t(c_void_p):
    pass

###############################################################################
## @brief Invalid Sysman resource handle
XET_INVALID_SYSMAN_RESOURCE_HANDLE = NULL

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
## @brief SMI initialization flags (bitfield)
class xet_sysman_init_flags_v(IntEnum):
    NONE = 0                                        ## default initialization
    WRITE = XE_BIT( 0 )                             ## request write/control access to resources

class xet_sysman_init_flags_t(c_int):
    def __str__(self):
        return str(xet_sysman_init_flags_v(value))


###############################################################################
## @brief Resource container types
class xet_res_container_type_v(IntEnum):
    UNIT = 0                                        ## Unit resource container
    BOARD = auto()                                  ## Board resource container
    DEVICE = auto()                                 ## Device resource container
    SUBDEVICE = auto()                              ## Sub-device resource container
    MAX_TYPES = auto()                              ## The number of resource container types

class xet_res_container_type_t(c_int):
    def __str__(self):
        return str(xet_res_container_type_v(value))


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
    MEMORY = auto()                                 ## Memory resource
    LINK = auto()                                   ## Link resource
    MAX_TYPES = auto()                              ## The number of resource types

class xet_resource_type_t(c_int):
    def __str__(self):
        return str(xet_resource_type_v(value))


###############################################################################
## @brief Accelerator assets
class xet_accel_asset_v(IntEnum):
    PCIE_CONTROLLER = 0                             ## PCIe controller
    IDI_MEM_CONTROLLER = auto()                     ## IDI memory controller
    HBM_MEM_CONTROLLER = auto()                     ## HBM memory controller
    L3_CACHE = auto()                               ## L3 cache
    BLILTTER = auto()                               ## Blitter
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
## @brief Resource container universal unique id (UUID)
class xet_res_container_uuid_t(Structure):
    _fields_ = [
        ("id", c_ubyte * XE_MAX_UUID_SIZE)                              ## [out] resource container universal unique id
    ]

###############################################################################
## @brief Generic information about a resource container
class xet_res_container_info_t(Structure):
    _fields_ = [
        ("uuid", xet_res_container_uuid_t),                             ## [out] UUID for the resource container
        ("type", xet_res_container_type_t),                             ## [out] Type of resource container
        ("haveParent", xe_bool_t),                                      ## [out] Indicates if this resource container has a parent container
        ("numChildren", c_ulong),                                       ## [out] The number of child resource containers
        ("numPeers", c_ulong),                                          ## [out] The number of resource containers connected with peer-to-peer
                                                                        ## links
        ("numResourcesByType", c_ulong * XET_RESOURCE_TYPE_MAX_TYPES)   ## [out] The number of resources of each type attached to this resource
                                                                        ## container (not in the child resource containers)
    ]

###############################################################################
## @brief Resource universal unique id (UUID)
class xet_resource_uuid_t(Structure):
    _fields_ = [
        ("id", c_ubyte * XE_MAX_UUID_SIZE)                              ## [out] resource universal unique id
    ]

###############################################################################
## @brief Generic information about a resource
class xet_resource_info_t(Structure):
    _fields_ = [
        ("uuid", xet_resource_uuid_t),                                  ## [out] UUID for the resource
        ("type", xet_resource_type_t),                                  ## [out] Type of resource
        ("resContainerUuid", xet_res_container_uuid_t)                  ## [out] UUID for the resource container where this resouce is located
    ]

###############################################################################
## @brief Maximum number of characters in string properties.
XET_STRING_PROPERTY_SIZE = 32

###############################################################################
## @brief Board resource container properties
class xet_board_properties_v(IntEnum):
    BOARD_PROP_SERIAL_NUMBER = 0                    ## (ro static) The serial number of a board container
    BOARD_PROP_BOARD_NUMBER = auto()                ## (ro static) The board number of a board container

class xet_board_properties_t(c_int):
    def __str__(self):
        return str(xet_board_properties_v(value))


###############################################################################
## @brief Data for property ::XET_BOARD_PROP_SERIAL_NUMBER
class xet_board_prop_serial_number_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Data for property ::XET_BOARD_PROP_BOARD_NUMBER
class xet_board_prop_board_number_t(Structure):
    _fields_ = [
        ("str", c_int8_t * XET_STRING_PROPERTY_SIZE)                    ## [out] NULL terminated string value
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
## @brief Data for a PCI bar
class xet_pci_bar_info_t(Structure):
    _fields_ = [
        ("type", xet_pci_bar_type_t),                                   ## [out] The type of bar
        ("base", c_ulonglong),                                          ## [out] Base address of the bar.
        ("size", c_ulonglong)                                           ## [out] Size of the bar.
    ]

###############################################################################
## @brief Hardware error types
class xet_hw_error_type_v(IntEnum):
    HW_ERROR_MESSAGING = 0                          ## Error while sending messages between sub-devices
    HW_ERROR_SGUNIT = auto()                        ## Error handling transactions between PCI config space, MMIO registers,
                                                    ## local memory and sub-devices
    HW_ERROR_GSC = auto()                           ## Authentication errors
    HW_ERROR_DISPLAY = auto()                       ## Display sub-system single-bit correctable errors
    HW_ERROR_GPU_EU_GRF = auto()                    ## Execution unit (EU) register file single-bit correctable errors
    HW_ERROR_GPU_EU_INSTCACHE = auto()              ## Execution unit (EU) instruction cache single-bit correctable errors
    HW_ERROR_GPU_SLM = auto()                       ## Execution unit (EU) shared local memory single-bit correctable errors
    HW_ERROR_GPU_SAMPLER = auto()                   ## Sampler single-bit correctable errors
    HW_ERROR_GPU_GUC = auto()                       ## Micro-controller SRAM single-bit correctable errors
    HW_ERROR_GPU_L3 = auto()                        ## L3 single-bit correctable errors
    HW_ERROR_GPU_ALL = auto()                       ## Total count of GPU errors
    HW_ERROR_PCI = auto()                           ## PCIe correctable or non-fatal errors
    HW_ERROR_PCI_ROUTING = auto()                   ## Errors routing PCIe traffic to/from sub-devices
    HW_ERROR_SOC = auto()                           ## Errors in other parts of the device
    HW_ERROR_COUNT = auto()                         ## Maximum number of hardware error types

class xet_hw_error_type_t(c_int):
    def __str__(self):
        return str(xet_hw_error_type_v(value))


###############################################################################
## @brief Device resource container properties
class xet_device_properties_v(IntEnum):
    DEVICE_PROP_BRAND = 0                           ## (ro static) The brand name of the device
    DEVICE_PROP_MODEL = auto()                      ## (ro static) The model name of the device
    DEVICE_PROP_DEVICEID = auto()                   ## (ro static) The device ID of the device
    DEVICE_PROP_VENDOR_NAME = auto()                ## (ro static) The vendor name of the device
    DEVICE_PROP_ACCEL_ASSETS = auto()               ## (ro static) The accelerator assets available in the device
    DEVICE_PROP_DRIVER_VERSION = auto()             ## (ro static) The driver version associated with the device
    DEVICE_PROP_BARS = auto()                       ## (ro static) The bars configured for the device
    DEVICE_PROP_ERROR_STATS = auto()                ## (ro dynamic) Error stats for the device
    DEVICE_PROP_COLD_SHUTDOWN = auto()              ## (wo dynamic) Cold shudown the device
    DEVICE_PROP_COLD_RESET = auto()                 ## (wo dynamic) Cold reset the device

class xet_device_properties_t(c_int):
    def __str__(self):
        return str(xet_device_properties_v(value))


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
## @brief Data about one type of accelerator asset
class xet_device_prop_accel_asset_t(Structure):
    _fields_ = [
        ("type", xet_accel_asset_t),                                    ## [out] The type of asset
        ("numBlocks", c_ulong),                                         ## [out] The number of blocks of this asset type
        ("numEngines", c_ulong)                                         ## [out] The number of submission engines for this type of asset
    ]

###############################################################################
## @brief Data for the property ::XET_DEVICE_PROP_ACCEL_ASSETS
class xet_device_prop_accel_assets_t(Structure):
    _fields_ = [
        ("assetBitfield", c_ulonglong),                                 ## [out] A bitfield of assets available in the resource container
        ("assetInfo", xet_device_prop_accel_asset_t * XET_ACCEL_ASSET_MAX_TYPES)## [out] Information about each asset.
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
## @brief Data for the property ::XET_DEVICE_PROP_ERROR_STATS
class xet_device_prop_error_stats_t(Structure):
    _fields_ = [
        ("TotalNonFatalError", c_ulong),                                ## [out] The total number of non-fatal hardware errors that have occurred
                                                                        ## since the driver booted
        ("errors", c_ulong * XET_HW_ERROR_COUNT),                       ## [out] Error counters for each type (::xet_hw_error_type_t) of hardware
                                                                        ## error.
        ("NumResets", c_ulong),                                         ## [out] The total number of hardware resets that have been performed
                                                                        ## since the driver booted
        ("NumHangs", c_ulong),                                          ## [out] The total number of hardware hangs that have occurred since the
                                                                        ## driver booted
        ("NumColdResets", c_ulong)                                      ## [out] The total number of cold resets that have been performanced
                                                                        ## since the driver booted
    ]

###############################################################################
## @brief Data for the property ::XET_DEVICE_PROP_COLD_SHUTDOWN
class xet_device_prop_driver_cold_shutdown_t(xe_bool_t):
    pass

###############################################################################
## @brief Data for the property ::XET_DEVICE_PROP_COLD_RESET
class xet_device_prop_driver_cold_reset_t(xe_bool_t):
    pass

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
class xet_psu_properties_v(IntEnum):
    PSU_PROP_AMP_LIMIT = 0                          ## (ro static) The maximum electrical current in Amperes that can be
                                                    ## drawn
    PSU_PROP_VOLTAGE_STATUS = auto()                ## (ro dynamic) Indicates if under or over voltage has occurred (one of
                                                    ## ::xet_psu_voltage_status_t)
    PSU_PROP_FAN_FAILURE = auto()                   ## (ro dynamic) Indicates if the fan has failed
    PSU_PROP_TEMPERATURE = auto()                   ## (ro dynamic) Read the current heatsink temperature in degrees celcius
    PSU_PROP_AMPS = auto()                          ## (ro dynamic) Read the amps being drawn in Amperes

class xet_psu_properties_t(c_int):
    def __str__(self):
        return str(xet_psu_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_PSU_PROP_AMP_LIMIT
class xet_psu_prop_amp_limit_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_PSU_PROP_VOLTAGE_STATUS
class xet_psu_prop_voltage_status_t(Structure):
    _fields_ = [
        ("status", xet_psu_voltage_status_t)                            ## [out] The current PSU voltage status)
    ]

###############################################################################
## @brief Data for the property ::XET_PSU_PROP_FAN_FAILURE
class xet_psu_prop_fan_failure_t(xe_bool_t):
    pass

###############################################################################
## @brief Data for the property ::XET_PSU_PROP_TEMPERATURE
class xet_psu_prop_temperature_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_PSU_PROP_AMPS
class xet_psu_prop_amps_t(c_ulong):
    pass

###############################################################################
## @brief Temperature sensor resource properties
class xet_temp_properties_v(IntEnum):
    TEMP_PROP_TEMPERATURE = 0                       ## (ro dynamic) The current temperature of the sensor in degrees celcius

class xet_temp_properties_t(c_int):
    def __str__(self):
        return str(xet_temp_properties_v(value))


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
class xet_fan_properties_v(IntEnum):
    FAN_PROP_MAX_RPM = 0                            ## (ro static) The maximum RPM of the fan
    FAN_PROP_MAX_TABLE_SIZE = auto()                ## (ro static) The maximum number of points in the fan temp/speed table
    FAN_PROP_SPEED_RPM = auto()                     ## (ro dynamic) The current fan speed in units of revolutions per minute
                                                    ## (rpm)
    FAN_PROP_SPEED_PERCENT = auto()                 ## (ro dynamic) The current fan speed as a percentage of the maximum
                                                    ## speed of that fan
    FAN_PROP_MODE = auto()                          ## (ro dynamic) The current fan speed mode (one of
                                                    ## ::xet_fan_speed_mode_t)
    FAN_PROP_FIXED_SPEED = auto()                   ## (rw dynamic) Read/write the fixed speed setting for the fan
    FAN_PROP_SPEED_TABLE = auto()                   ## (rw dynamic) Read/write the fan speed table

class xet_fan_properties_t(c_int):
    def __str__(self):
        return str(xet_fan_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_FAN_PROP_MAX_RPM
class xet_fan_prop_max_rpm_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_FAN_PROP_MAX_TABLE_SIZE
class xet_fan_prop_max_table_size_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_FAN_PROP_SPEED_RPM
class xet_fan_prop_speed_rpm_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_FAN_PROP_SPEED_PERCENT
class xet_fan_prop_speed_percent_t(c_ulong):
    pass

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
## @brief LED resource properties
class xet_led_properties_v(IntEnum):
    LED_PROP_RGB_CAP = 0                            ## (ro static) Indicates if the LED is RGB capable
    LED_PROP_STATE = auto()                         ## (rw dynaic) The LED state (on/off and color)

class xet_led_properties_t(c_int):
    def __str__(self):
        return str(xet_led_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_LED_PROP_RGB_CAP
class xet_led_prop_rgb_cap_t(xe_bool_t):
    pass

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
## @brief Firmware resource properties
class xet_firmware_properties_v(IntEnum):
    FIRMWARE_PROP_NAME = 0                          ## (ro static) Name encoded in the loaded firmware image
    FIRMWARE_PROP_VERSION = auto()                  ## (ro static) The version of the loaded firmware image
    FIRMWARE_PROP_CHECK = auto()                    ## (ro dynamic) Verify the checksum of the loaded firmware image
    FIRMWARE_PROP_FLASH = auto()                    ## (wo dynamically) Flash a new firmware image

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
## @brief Power domain resource properties
class xet_pwr_properties_v(IntEnum):
    PWR_PROP_ACCEL_ASSETS = 0                       ## (ro static) List of accelerator assets that contribute to this power
                                                    ## domain
    PWR_PROP_MAX_LIMIT = auto()                     ## (ro static) The maximum power limit that can be requested
    PWR_PROP_ENERGY_COUNTER = auto()                ## (ro dynamic) The value of the monotonic energy counter
    PWR_PROP_SUSTAINED_LIMIT = auto()               ## (rw dynamic) The sustained power limit
    PWR_PROP_BURST_LIMIT = auto()                   ## (rw dynamic) The burst power limit
    PWR_PROP_PEAK_LIMIT = auto()                    ## (rw dynamic) The peak power limit

class xet_pwr_properties_t(c_int):
    def __str__(self):
        return str(xet_pwr_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_PWR_PROP_ACCEL_ASSETS.
## 
## @details
##     - Bitfield of (1<<::xet_accel_asset_t)
class xet_pwr_prop_accel_assets_t(c_ulonglong):
    pass

###############################################################################
## @brief Data for the property ::XET_PWR_PROP_MAX_LIMIT
## 
## @details
##     - Units are in millwatts
class xet_pwr_prop_max_limit_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_PWR_PROP_ENERGY_COUNTER
## 
## @details
##     - Units are in millijoules
class xet_pwr_prop_energy_counter_t(c_ulonglong):
    pass

###############################################################################
## @brief API version of ::xet_pwr_prop_sustained_limit_t
class xet_pwr_sustained_limit_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xet_pwr_sustained_limit_version_t(c_int):
    def __str__(self):
        return str(xet_pwr_sustained_limit_version_v(value))


###############################################################################
## @brief Data for the property ::XET_PWR_PROP_SUSTAINED_LIMIT
## 
## @details
##     - The power controller (Punit) will throttle the operating frequency if
##       the power averaged over a window (typically seconds) exceeds this
##       limit.
class xet_pwr_prop_sustained_limit_t(Structure):
    _fields_ = [
        ("version", xet_pwr_sustained_limit_version_t),                 ## [in] ::XET_PWR_SUSTAINED_LIMIT_VERSION_CURRENT
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
## @brief Frequency domain types
class xet_freq_domain_type_v(IntEnum):
    INDEPENDENT = 0                                 ## The frequency of this domain can be managed independently of other
                                                    ## domains
    DEPENDENT = auto()                              ## The frequency of this domain is dependent on another domain through a
                                                    ## clock divider

class xet_freq_domain_type_t(c_int):
    def __str__(self):
        return str(xet_freq_domain_type_v(value))


###############################################################################
## @brief DVFS mode
class xet_dvfs_mode_v(IntEnum):
    MIN = 0                                         ## Fixed minimum frequency will be requested unless specific applications
                                                    ## request otherwise.
    EFFICIENT = auto()                              ## Dynamic frequency management that prefers power saving over
                                                    ## performance.
    STABLE = auto()                                 ## Fixed frequency that should not be throttled under normal operating
                                                    ## conditions.
    DEFAULT = auto()                                ## Dynamic frequency management that balances power and performance.
    AGGRESSIVE = auto()                             ## Dynamic frequency management that trades more power for better
                                                    ## performance.
    MAX = auto()                                    ## Fixed maximum frequency.

class xet_dvfs_mode_t(c_int):
    def __str__(self):
        return str(xet_dvfs_mode_v(value))


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
##     - The frequency of a domain of type ::XET_FREQ_DOMAIN_TYPE_DEPENDENT is
##       obtained by the formula:
##     - freq = source domain freq * numerator / denominator
class xet_freq_divider_t(Structure):
    _fields_ = [
        ("numerator", c_ushort),                                        ## [in,out] numerator of the ratio
        ("denominator", c_ushort)                                       ## [in,out] denominator of the ratio
    ]

###############################################################################
## @brief Frequency domain resource properties
class xet_freq_properties_v(IntEnum):
    FREQ_PROP_ACCEL_ASSETS = 0                      ## (ro static) List of accelerator assets that are connected to this
                                                    ## power domain
    FREQ_PROP_DOMAIN_TYPE = auto()                  ## (ro static) The type of frequency domain (one of
                                                    ## ::xet_freq_domain_type_t)
    FREQ_PROP_AVAIL_CLOCKS = auto()                 ## (ro static) Available frequency clocks that this domain can run at.
    FREQ_PROP_AVAIL_DIVIDERS = auto()               ## (ro static) Available dividers that this domain can run with.
    FREQ_PROP_SRC_FREQ = auto()                     ## (ro static) Get the UUID of the source frequency domain resource if
                                                    ## the type is dependent.
    FREQ_PROP_DVFS_MODE = auto()                    ## (rw dynamic) The operating mode of dynamic frequency management for
                                                    ## this domain (one of ::xet_dvfs_mode_t).
    FREQ_PROP_FREQ_RANGE = auto()                   ## (rw dynamic) The frequencies between which dynamic frequency
                                                    ## management operates.
    FREQ_PROP_FREQ_TDP = auto()                     ## (ro dynamic) The maximum frequency supported under the current TDP
                                                    ## conditions
    FREQ_PROP_FREQ_EFFICIENT = auto()               ## (ro dynamic) The efficient minimum frequency
    FREQ_PROP_FREQ_REQUEST = auto()                 ## (ro dynamic) The current frequency request.
    FREQ_PROP_FREQ_RESOLVED = auto()                ## (ro dynamic) The resolved frequency.
    FREQ_PROP_FREQ_DIVIDER = auto()                 ## (rw dynamic) The current frequency divider for dependent frequency
                                                    ## domains.
    FREQ_PROP_THROTTLE_REASONS = auto()             ## (ro dynamic) The reasons that the frequency is being limited by the
                                                    ## PCU.
    FREQ_PROP_THROTTLE_TIME = auto()                ## (ro dynamic) The total time that the frequency has been limited by the
                                                    ## PCU.

class xet_freq_properties_t(c_int):
    def __str__(self):
        return str(xet_freq_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_ACCEL_ASSETS
## 
## @details
##     - Bitfield of (1<<::xet_accel_asset_t)
class xet_freq_prop_accel_assets_t(c_ulonglong):
    pass

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
##     - The list is ordered from the smallest frequency to the largest
##       frequency.
class xet_freq_prop_avail_clocks_t(Structure):
    _fields_ = [
        ("num", c_ulong),                                               ## [out] The number of clocks
        ("pClocks", POINTER(c_ulong))                                   ## [out] Array of clock frequencies in MHz ordered from smallest to
                                                                        ## largest.
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
## @brief Data for the property ::XET_FREQ_PROP_SRC_FREQ
class xet_freq_prop_src_freq_t(Structure):
    _fields_ = [
        ("uuid", xet_resource_uuid_t)                                   ## [out] The resource UUID of the source frequency domain
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_DVFS_MODE
class xet_freq_prop_dvfs_mode_t(Structure):
    _fields_ = [
        ("mode", xet_dvfs_mode_t)                                       ## [in,out] The DVFS operating mode
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_RANGE
class xet_freq_prop_freq_range_t(Structure):
    _fields_ = [
        ("min", c_ulong),                                               ## [in,out] Minimum frequency in MHz
        ("max", c_ushort)                                               ## [in,out] Maximum frequency in MHz
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_TDP
## 
## @details
##     - In units of MHz
class xet_freq_prop_freq_tdp_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_EFFICIENT
## 
## @details
##     - In units of MHz
class xet_freq_prop_freq_efficient_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_REQUEST
## 
## @details
##     - In units of MHz
class xet_freq_prop_freq_request_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_RESOLVED
## 
## @details
##     - In units of MHz
class xet_freq_prop_freq_resolved_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_FREQ_DIVIDER
class xet_freq_prop_freq_divider_t(Structure):
    _fields_ = [
        ("divider", xet_freq_divider_t)                                 ## [in,out] The frequency divider
    ]

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_THROTTLE_REASONS
## 
## @details
##     - Bitfield of ::xet_freq_throttle_reasons_t
class xet_freq_prop_throttle_reasons_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_FREQ_PROP_THROTTLE_TIME
## 
## @details
##     - In units of microseconds
class xet_freq_prop_throttle_time_t(c_ulong):
    pass

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
class xet_pwrwell_properties_v(IntEnum):
    PWRWELL_PROP_ACCEL_ASSETS = 0                   ## (ro static) List of accelerator assets that are connected to this
                                                    ## power-well domain
    PWRWELL_PROP_PROMO_CAP = auto()                 ## (ro static) Find out if the power-well domain has a programmable
                                                    ## promotion setting
    PWRWELL_PROP_PROMO_MODE = auto()                ## (rw dynamic) The current promotion mode
    PWRWELL_PROP_SLEEP_COUNTER = auto()             ## (ro dynamic) The monotonic counter for the amount of time the
                                                    ## power-well is off
    PWRWELL_PROP_IDLE_COUNTER = auto()              ## (ro dynamic) The monotonic counter for the amount of time the
                                                    ## power-well is on but not executing any accelerator workloads
    PWRWELL_PROP_ACTIVE_COUNTER = auto()            ## (ro dynamic) The monotonic counter for the amount of time the
                                                    ## power-well is on and executing accelerator workloads
    PWRWELL_PROP_WAKE_COUNTER = auto()              ## (ro dynamic) The monotonic counter for the number of times that the
                                                    ## power-well has transitioned from a sleep state to a powered on state
    PWRWELL_PROP_EXEC_COUNTER = auto()              ## (ro dynamic) The monotonic counter for the number of times that the
                                                    ## power-well has transitioned from a sleep or idle state to an active
                                                    ## state

class xet_pwrwell_properties_t(c_int):
    def __str__(self):
        return str(xet_pwrwell_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_ACCEL_ASSETS
## 
## @details
##     - Bitfield of (1<<::xet_accel_asset_t)
class xet_pwrwell_prop_accel_assets_t(c_ulonglong):
    pass

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_PROMO_CAP
class xet_pwrwell_prop_promo_cap_t(xe_bool_t):
    pass

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_PROMO_MODE
class xet_pwrwell_prop_promo_mode_t(Structure):
    _fields_ = [
        ("mode", xet_pwrwell_promo_mode_t)                              ## [in,out] Current promotion mode
    ]

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_SLEEP_COUNTER
## 
## @details
##     - Monotonic counter in units of seconds.
class xet_pwrwell_prop_sleep_counter_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_IDLE_COUNTER
## 
## @details
##     - Monotonic counter in units of seconds.
class xet_pwrwell_prop_idle_counter_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_ACTIVE_COUNTER
## 
## @details
##     - Monotonic counter in units of seconds.
class xet_pwrwell_prop_active_counter_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_WAKE_COUNTER
## 
## @details
##     - Monotonic counter.
class xet_pwrwell_prop_wake_counter_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_PWRWELL_PROP_EXEC_COUNTER
## 
## @details
##     - Monotonic counter.
class xet_pwrwell_prop_exec_counter_t(c_ulong):
    pass

###############################################################################
## @brief Accelerator asset resource properties
class xet_accel_properties_v(IntEnum):
    ACCEL_PROP_ACCEL_ASSETS = 0                     ## (ro static) List of accelerator assets that contribute to counters in
                                                    ## this resource
    ACCEL_PROP_ACTIVE_COUNTER = auto()              ## (ro dynamic) The total wall time accelerator assets in this resource
                                                    ## are active.
    ACCEL_PROP_IDLE_COUNTER = auto()                ## (ro dynamic) The total wall time no accelerator assets in this
                                                    ## resource are active

class xet_accel_properties_t(c_int):
    def __str__(self):
        return str(xet_accel_properties_v(value))


###############################################################################
## @brief Data for the property ::XET_ACCEL_PROP_ACCEL_ASSETS
## 
## @details
##     - Bitfield of (1<<::xet_accel_asset_t)
class xet_accel_prop_accel_assets_t(c_ulonglong):
    pass

###############################################################################
## @brief Data for the property ::XET_ACCEL_PROP_ACTIVE_COUNTER
## 
## @details
##     - Monotonic counter in units of seconds.
class xet_accel_prop_active_counter_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_ACCEL_PROP_IDLE_COUNTER
## 
## @details
##     - Monotonic counter in units of seconds.
class xet_accel_prop_idle_counter_t(c_ulong):
    pass

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
class xet_mem_properties_v(IntEnum):
    MEM_PROP_TYPE = 0                               ## (ro static) The type of memory covered by this resource (one of
                                                    ## ::xet_mem_type_t)
    MEM_PROP_ECC_CAP = auto()                       ## (ro static) Indicates if this memory resource supports ECC/RAS
                                                    ## features
    MEM_PROP_BAD_LIST = auto()                      ## (ro static) Get the list of pages that have been permanently marked
                                                    ## bad
    MEM_PROP_UTILIZATION = auto()                   ## (ro dynamic) Get current allocated/unallocated size
    MEM_PROP_BANDWIDTH = auto()                     ## (ro dynamic) Get current read/write bandwidth counters and maximum
                                                    ## bandwidth
    MEM_PROP_ECC_ENABLED = auto()                   ## (rw dynamic) Determine if ECC is enabled/disabled or change this
                                                    ## setting
    MEM_PROP_ECC_COUNTERS = auto()                  ## (ro dynamic) ECC error counters
    MEM_PROP_ECC_CLEAR = auto()                     ## (wo dynamic) Clear ECC error counters
    MEM_PROP_ECC_POISON = auto()                    ## (wo dynamic) Poison the memory resource

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
## @brief Data for the property ::XET_MEM_PROP_ECC_CAP
class xet_mem_prop_ecc_cap_t(xe_bool_t):
    pass

###############################################################################
## @brief Data for the property ::XET_MEM_PROP_BAD_LIST
class xet_mem_prop_bad_list_t(Structure):
    _fields_ = [
        ("pCount", POINTER(c_ulong)),                                   ## [in,out] The number of elements in pList
                                                                        ## If pCount is zero, then the driver will update the value with the
                                                                        ## number of elements needed to store the bad list.
                                                                        ## If pCount is less than that required to store the bad list, the driver
                                                                        ## will update the value with the required number of elements and return
                                                                        ## an error.
                                                                        ## If pCount is larger than that required to store the bad list, the
                                                                        ## driver will update the value with the number of elements actually returned.
        ("pList", POINTER(xet_mem_retire_info_t))                       ## [in] Pointer to storage for information about each bad page.
    ]

###############################################################################
## @brief Data for the property ::XET_MEM_PROP_UTILIZATION
class xet_mem_prop_utilization_t(Structure):
    _fields_ = [
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
## @brief Data for the property ::XET_MEM_PROP_ECC_COUNTERS
class xet_mem_prop_ecc_counters_t(Structure):
    _fields_ = [
        ("parityErrors", c_ulong),                                      ## [out] Total parity errors that have occurred
        ("correctableErrors", c_ulong),                                 ## [out] Total correctable errors that have occurred
        ("uncorrectableErrors", c_ulong),                               ## [out] Total uncorrectable errors that have occurred
        ("retiredPages", c_ulong),                                      ## [out] Total number of pages that have been retired
        ("badPages", c_ulong)                                           ## [out] Total number of pages that have been permanently marked as bad
    ]

###############################################################################
## @brief Data for the property ::XET_MEM_PROP_ECC_CLEAR
class xet_mem_prop_ecc_clear_t(xe_bool_t):
    pass

###############################################################################
## @brief Data for the property ::XET_MEM_PROP_ECC_POISON
class xet_mem_prop_ecc_poison_t(xe_bool_t):
    pass

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
class xet_link_properties_v(IntEnum):
    LINK_PROP_TYPE = 0                              ## (ro static) The type of link (one of ::xet_link_type_t)
    LINK_PROP_BUS_ADDRESS = auto()                  ## (ro static) The bus address of the link
    LINK_PROP_PWR_CAP = auto()                      ## (ro static) Indicates if the link frequency can adjust to control
                                                    ## power
    LINK_PROP_AVAIL_SPEEDS = auto()                 ## (ro static) Available link speeds
    LINK_PROP_MAX_PACKET_SIZE = auto()              ## (ro static) Available link speeds
    LINK_PROP_BANDWIDTH = auto()                    ## (ro dynamic) Available link speeds
    LINK_PROP_REPLAY_COUNTER = auto()               ## (ro dynamic) Total number of packet replays that have occurred
    LINK_PROP_SPEED = auto()                        ## (ro dynamic) Current link speed
    LINK_PROP_SPEED_RANGE = auto()                  ## (wo dynamic) Set the min/max speeds between which the link can operate

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
class xet_link_prop_pwr_cap_t(xe_bool_t):
    pass

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
class xet_link_prop_max_packet_size_t(c_ulong):
    pass

###############################################################################
## @brief Data for the property ::XET_LINK_PROP_BANDWIDTH
class xet_link_prop_bandwidth_t(Structure):
    _fields_ = [
        ("recvCounter", c_ulong),                                       ## [out] Total bytes received across the link
        ("sendCounter", c_ulong),                                       ## [out] Total bytes sent across the link
        ("maxBandwidth", c_ulong)                                       ## [out] Maximum bytes/sec that can be transfered acros the link
    ]

###############################################################################
## @brief Data for the property ::XET_LINK_PROP_REPLAY_COUNTER
class xet_link_prop_replay_counter_t(c_ulong):
    pass

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
## @brief Event types
class xet_sysman_event_type_v(IntEnum):
    FREQ_THROTTLED = 0                              ## The frequency is being throttled
    FREQ_POLICY_CHANGED = auto()                    ## Another API client has modified frequency domain properties
    GPU_ERRORS = auto()                             ## GPU hardware errors have occurred
    RESET = auto()                                  ## Device reset has occurred
    HANG = auto()                                   ## Device hang has occurred
    MEM_ERRORS = auto()                             ## ECC correctable errors have occurred in a memory resource
    LINK_ERRORS = auto()                            ## Link replays have occured in a link resource
    COUNT = auto()                                  ## The number of event types

class xet_sysman_event_type_t(c_int):
    def __str__(self):
        return str(xet_sysman_event_type_v(value))


###############################################################################
## @brief Event data
class xet_sysman_event_data_t(Structure):
    _fields_ = [
        ("uuid", xet_res_container_uuid_t),                             ## [out] The UUID of the resource container that generated the event
        ("events", c_ulong)                                             ## [out] Bitfield of events (1<<::xet_sysman_event_type_t) that have been
                                                                        ## triggered.
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
## @brief Function-pointer for xetSysmanCreate
if __use_win_types:
    _xetSysmanCreate_t = WINFUNCTYPE( xe_result_t, xet_device_group_handle_t, c_ulong, POINTER(xet_sysman_handle_t) )
else:
    _xetSysmanCreate_t = CFUNCTYPE( xe_result_t, xet_device_group_handle_t, c_ulong, POINTER(xet_sysman_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanDestroy
if __use_win_types:
    _xetSysmanDestroy_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t )
else:
    _xetSysmanDestroy_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t )

###############################################################################
## @brief Function-pointer for xetSysmanGetResourceContainers
if __use_win_types:
    _xetSysmanGetResourceContainers_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_res_container_type_t, POINTER(c_ulong), POINTER(xet_res_container_handle_t) )
else:
    _xetSysmanGetResourceContainers_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_res_container_type_t, POINTER(c_ulong), POINTER(xet_res_container_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetDeviceResourceContainer
if __use_win_types:
    _xetSysmanGetDeviceResourceContainer_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_device_handle_t, POINTER(xet_res_container_handle_t) )
else:
    _xetSysmanGetDeviceResourceContainer_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_device_handle_t, POINTER(xet_res_container_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanGetResourceContainerByUuid
if __use_win_types:
    _xetSysmanGetResourceContainerByUuid_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_res_container_uuid_t), POINTER(xet_res_container_handle_t) )
else:
    _xetSysmanGetResourceContainerByUuid_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, POINTER(xet_res_container_uuid_t), POINTER(xet_res_container_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanRegisterEvents
if __use_win_types:
    _xetSysmanRegisterEvents_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_res_container_handle_t, c_ulong )
else:
    _xetSysmanRegisterEvents_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_res_container_handle_t, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanUnregisterEvents
if __use_win_types:
    _xetSysmanUnregisterEvents_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_res_container_handle_t, c_ulong )
else:
    _xetSysmanUnregisterEvents_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xet_res_container_handle_t, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanListenEvents
if __use_win_types:
    _xetSysmanListenEvents_t = WINFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, POINTER(c_ulong), POINTER(xet_sysman_event_data_t) )
else:
    _xetSysmanListenEvents_t = CFUNCTYPE( xe_result_t, xet_sysman_handle_t, xe_bool_t, POINTER(c_ulong), POINTER(xet_sysman_event_data_t) )


###############################################################################
## @brief Table of Sysman functions pointers
class _xet_sysman_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xetSysmanCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xetSysmanDestroy_t
        ("pfnGetResourceContainers", c_void_p),                         ## _xetSysmanGetResourceContainers_t
        ("pfnGetDeviceResourceContainer", c_void_p),                    ## _xetSysmanGetDeviceResourceContainer_t
        ("pfnGetResourceContainerByUuid", c_void_p),                    ## _xetSysmanGetResourceContainerByUuid_t
        ("pfnRegisterEvents", c_void_p),                                ## _xetSysmanRegisterEvents_t
        ("pfnUnregisterEvents", c_void_p),                              ## _xetSysmanUnregisterEvents_t
        ("pfnListenEvents", c_void_p)                                   ## _xetSysmanListenEvents_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanResContainerGetInfo
if __use_win_types:
    _xetSysmanResContainerGetInfo_t = WINFUNCTYPE( xe_result_t, xet_res_container_handle_t, POINTER(xet_res_container_info_t) )
else:
    _xetSysmanResContainerGetInfo_t = CFUNCTYPE( xe_result_t, xet_res_container_handle_t, POINTER(xet_res_container_info_t) )

###############################################################################
## @brief Function-pointer for xetSysmanResContainerGetParent
if __use_win_types:
    _xetSysmanResContainerGetParent_t = WINFUNCTYPE( xe_result_t, xet_res_container_handle_t, POINTER(xet_res_container_handle_t) )
else:
    _xetSysmanResContainerGetParent_t = CFUNCTYPE( xe_result_t, xet_res_container_handle_t, POINTER(xet_res_container_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanResContainerGetChildren
if __use_win_types:
    _xetSysmanResContainerGetChildren_t = WINFUNCTYPE( xe_result_t, xet_res_container_handle_t, POINTER(c_ulong), POINTER(xet_res_container_handle_t) )
else:
    _xetSysmanResContainerGetChildren_t = CFUNCTYPE( xe_result_t, xet_res_container_handle_t, POINTER(c_ulong), POINTER(xet_res_container_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanResContainerGetPeers
if __use_win_types:
    _xetSysmanResContainerGetPeers_t = WINFUNCTYPE( xe_result_t, xet_res_container_handle_t, POINTER(c_ulong), POINTER(xet_res_container_handle_t) )
else:
    _xetSysmanResContainerGetPeers_t = CFUNCTYPE( xe_result_t, xet_res_container_handle_t, POINTER(c_ulong), POINTER(xet_res_container_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanResContainerGetAccelAssetName
if __use_win_types:
    _xetSysmanResContainerGetAccelAssetName_t = WINFUNCTYPE( xe_result_t, xet_res_container_handle_t, xet_accel_asset_t, POINTER(c_char*) )
else:
    _xetSysmanResContainerGetAccelAssetName_t = CFUNCTYPE( xe_result_t, xet_res_container_handle_t, xet_accel_asset_t, POINTER(c_char*) )

###############################################################################
## @brief Function-pointer for xetSysmanResContainerGetResources
if __use_win_types:
    _xetSysmanResContainerGetResources_t = WINFUNCTYPE( xe_result_t, xet_res_container_handle_t, xet_resource_type_t, POINTER(c_ulong), POINTER(xet_resource_handle_t) )
else:
    _xetSysmanResContainerGetResources_t = CFUNCTYPE( xe_result_t, xet_res_container_handle_t, xet_resource_type_t, POINTER(c_ulong), POINTER(xet_resource_handle_t) )

###############################################################################
## @brief Function-pointer for xetSysmanResContainerGetBoardProperties
if __use_win_types:
    _xetSysmanResContainerGetBoardProperties_t = WINFUNCTYPE( xe_result_t, xet_res_container_handle_t, c_ulong, POINTER(xet_board_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResContainerGetBoardProperties_t = CFUNCTYPE( xe_result_t, xet_res_container_handle_t, c_ulong, POINTER(xet_board_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResContainerGetDeviceProperties
if __use_win_types:
    _xetSysmanResContainerGetDeviceProperties_t = WINFUNCTYPE( xe_result_t, xet_res_container_handle_t, c_ulong, POINTER(xet_device_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResContainerGetDeviceProperties_t = CFUNCTYPE( xe_result_t, xet_res_container_handle_t, c_ulong, POINTER(xet_device_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResContainerSetDeviceProperties
if __use_win_types:
    _xetSysmanResContainerSetDeviceProperties_t = WINFUNCTYPE( xe_result_t, xet_res_container_handle_t, c_ulong, POINTER(xet_device_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResContainerSetDeviceProperties_t = CFUNCTYPE( xe_result_t, xet_res_container_handle_t, c_ulong, POINTER(xet_device_properties_t), c_void_p, c_ulong )


###############################################################################
## @brief Table of SysmanResContainer functions pointers
class _xet_sysman_res_container_dditable_t(Structure):
    _fields_ = [
        ("pfnGetInfo", c_void_p),                                       ## _xetSysmanResContainerGetInfo_t
        ("pfnGetParent", c_void_p),                                     ## _xetSysmanResContainerGetParent_t
        ("pfnGetChildren", c_void_p),                                   ## _xetSysmanResContainerGetChildren_t
        ("pfnGetPeers", c_void_p),                                      ## _xetSysmanResContainerGetPeers_t
        ("pfnGetAccelAssetName", c_void_p),                             ## _xetSysmanResContainerGetAccelAssetName_t
        ("pfnGetResources", c_void_p),                                  ## _xetSysmanResContainerGetResources_t
        ("pfnGetBoardProperties", c_void_p),                            ## _xetSysmanResContainerGetBoardProperties_t
        ("pfnGetDeviceProperties", c_void_p),                           ## _xetSysmanResContainerGetDeviceProperties_t
        ("pfnSetDeviceProperties", c_void_p)                            ## _xetSysmanResContainerSetDeviceProperties_t
    ]

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetInfo
if __use_win_types:
    _xetSysmanResourceGetInfo_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, POINTER(xet_resource_info_t) )
else:
    _xetSysmanResourceGetInfo_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, POINTER(xet_resource_info_t) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetPsuProperties
if __use_win_types:
    _xetSysmanResourceGetPsuProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_psu_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetPsuProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_psu_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetPsuProperties
if __use_win_types:
    _xetSysmanResourceSetPsuProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_psu_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetPsuProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_psu_properties_t), c_void_p, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetTempProperties
if __use_win_types:
    _xetSysmanResourceGetTempProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_temp_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetTempProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_temp_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetTempProperties
if __use_win_types:
    _xetSysmanResourceSetTempProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_temp_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetTempProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_temp_properties_t), c_void_p, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetFanProperties
if __use_win_types:
    _xetSysmanResourceGetFanProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_fan_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetFanProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_fan_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetFanProperties
if __use_win_types:
    _xetSysmanResourceSetFanProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_fan_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetFanProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_fan_properties_t), c_void_p, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetLedProperties
if __use_win_types:
    _xetSysmanResourceGetLedProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_led_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetLedProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_led_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetLedProperties
if __use_win_types:
    _xetSysmanResourceSetLedProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_led_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetLedProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_led_properties_t), c_void_p, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetFirmwareProperties
if __use_win_types:
    _xetSysmanResourceGetFirmwareProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_firmware_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetFirmwareProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_firmware_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetFirmwareProperties
if __use_win_types:
    _xetSysmanResourceSetFirmwareProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_firmware_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetFirmwareProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_firmware_properties_t), c_void_p, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetPwrProperties
if __use_win_types:
    _xetSysmanResourceGetPwrProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_pwr_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetPwrProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_pwr_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetPwrProperties
if __use_win_types:
    _xetSysmanResourceSetPwrProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_pwr_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetPwrProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_pwr_properties_t), c_void_p, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetFreqProperties
if __use_win_types:
    _xetSysmanResourceGetFreqProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_freq_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetFreqProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_freq_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetFreqProperties
if __use_win_types:
    _xetSysmanResourceSetFreqProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_freq_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetFreqProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_freq_properties_t), c_void_p, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetPwrWellProperties
if __use_win_types:
    _xetSysmanResourceGetPwrWellProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_pwrwell_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetPwrWellProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_pwrwell_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetPwrWellProperties
if __use_win_types:
    _xetSysmanResourceSetPwrWellProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_pwrwell_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetPwrWellProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_pwrwell_properties_t), c_void_p, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetAccelProperties
if __use_win_types:
    _xetSysmanResourceGetAccelProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_accel_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetAccelProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_accel_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetAccelProperties
if __use_win_types:
    _xetSysmanResourceSetAccelProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_accel_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetAccelProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_accel_properties_t), c_void_p, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetMemProperties
if __use_win_types:
    _xetSysmanResourceGetMemProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_mem_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetMemProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_mem_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetMemProperties
if __use_win_types:
    _xetSysmanResourceSetMemProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_mem_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetMemProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_mem_properties_t), c_void_p, c_ulong )

###############################################################################
## @brief Function-pointer for xetSysmanResourceGetLinkProperties
if __use_win_types:
    _xetSysmanResourceGetLinkProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_link_properties_t), c_void_p, POINTER(c_ulong) )
else:
    _xetSysmanResourceGetLinkProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_link_properties_t), c_void_p, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for xetSysmanResourceSetLinkProperties
if __use_win_types:
    _xetSysmanResourceSetLinkProperties_t = WINFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_link_properties_t), c_void_p, c_ulong )
else:
    _xetSysmanResourceSetLinkProperties_t = CFUNCTYPE( xe_result_t, xet_resource_handle_t, c_ulong, POINTER(xet_link_properties_t), c_void_p, c_ulong )


###############################################################################
## @brief Table of SysmanResource functions pointers
class _xet_sysman_resource_dditable_t(Structure):
    _fields_ = [
        ("pfnGetInfo", c_void_p),                                       ## _xetSysmanResourceGetInfo_t
        ("pfnGetPsuProperties", c_void_p),                              ## _xetSysmanResourceGetPsuProperties_t
        ("pfnSetPsuProperties", c_void_p),                              ## _xetSysmanResourceSetPsuProperties_t
        ("pfnGetTempProperties", c_void_p),                             ## _xetSysmanResourceGetTempProperties_t
        ("pfnSetTempProperties", c_void_p),                             ## _xetSysmanResourceSetTempProperties_t
        ("pfnGetFanProperties", c_void_p),                              ## _xetSysmanResourceGetFanProperties_t
        ("pfnSetFanProperties", c_void_p),                              ## _xetSysmanResourceSetFanProperties_t
        ("pfnGetLedProperties", c_void_p),                              ## _xetSysmanResourceGetLedProperties_t
        ("pfnSetLedProperties", c_void_p),                              ## _xetSysmanResourceSetLedProperties_t
        ("pfnGetFirmwareProperties", c_void_p),                         ## _xetSysmanResourceGetFirmwareProperties_t
        ("pfnSetFirmwareProperties", c_void_p),                         ## _xetSysmanResourceSetFirmwareProperties_t
        ("pfnGetPwrProperties", c_void_p),                              ## _xetSysmanResourceGetPwrProperties_t
        ("pfnSetPwrProperties", c_void_p),                              ## _xetSysmanResourceSetPwrProperties_t
        ("pfnGetFreqProperties", c_void_p),                             ## _xetSysmanResourceGetFreqProperties_t
        ("pfnSetFreqProperties", c_void_p),                             ## _xetSysmanResourceSetFreqProperties_t
        ("pfnGetPwrWellProperties", c_void_p),                          ## _xetSysmanResourceGetPwrWellProperties_t
        ("pfnSetPwrWellProperties", c_void_p),                          ## _xetSysmanResourceSetPwrWellProperties_t
        ("pfnGetAccelProperties", c_void_p),                            ## _xetSysmanResourceGetAccelProperties_t
        ("pfnSetAccelProperties", c_void_p),                            ## _xetSysmanResourceSetAccelProperties_t
        ("pfnGetMemProperties", c_void_p),                              ## _xetSysmanResourceGetMemProperties_t
        ("pfnSetMemProperties", c_void_p),                              ## _xetSysmanResourceSetMemProperties_t
        ("pfnGetLinkProperties", c_void_p),                             ## _xetSysmanResourceGetLinkProperties_t
        ("pfnSetLinkProperties", c_void_p)                              ## _xetSysmanResourceSetLinkProperties_t
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
        ("SysmanResContainer", _xet_sysman_res_container_dditable_t),
        ("SysmanResource", _xet_sysman_resource_dditable_t)
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
        self.xetSysmanGetResourceContainers = _xetSysmanGetResourceContainers_t(self.__dditable.Sysman.pfnGetResourceContainers)
        self.xetSysmanGetDeviceResourceContainer = _xetSysmanGetDeviceResourceContainer_t(self.__dditable.Sysman.pfnGetDeviceResourceContainer)
        self.xetSysmanGetResourceContainerByUuid = _xetSysmanGetResourceContainerByUuid_t(self.__dditable.Sysman.pfnGetResourceContainerByUuid)
        self.xetSysmanRegisterEvents = _xetSysmanRegisterEvents_t(self.__dditable.Sysman.pfnRegisterEvents)
        self.xetSysmanUnregisterEvents = _xetSysmanUnregisterEvents_t(self.__dditable.Sysman.pfnUnregisterEvents)
        self.xetSysmanListenEvents = _xetSysmanListenEvents_t(self.__dditable.Sysman.pfnListenEvents)

        # call driver to get function pointers
        _SysmanResContainer = _xet_sysman_res_container_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanResContainerProcAddrTable(version, byref(_SysmanResContainer)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanResContainer = _SysmanResContainer

        # attach function interface to function address
        self.xetSysmanResContainerGetInfo = _xetSysmanResContainerGetInfo_t(self.__dditable.SysmanResContainer.pfnGetInfo)
        self.xetSysmanResContainerGetParent = _xetSysmanResContainerGetParent_t(self.__dditable.SysmanResContainer.pfnGetParent)
        self.xetSysmanResContainerGetChildren = _xetSysmanResContainerGetChildren_t(self.__dditable.SysmanResContainer.pfnGetChildren)
        self.xetSysmanResContainerGetPeers = _xetSysmanResContainerGetPeers_t(self.__dditable.SysmanResContainer.pfnGetPeers)
        self.xetSysmanResContainerGetAccelAssetName = _xetSysmanResContainerGetAccelAssetName_t(self.__dditable.SysmanResContainer.pfnGetAccelAssetName)
        self.xetSysmanResContainerGetResources = _xetSysmanResContainerGetResources_t(self.__dditable.SysmanResContainer.pfnGetResources)
        self.xetSysmanResContainerGetBoardProperties = _xetSysmanResContainerGetBoardProperties_t(self.__dditable.SysmanResContainer.pfnGetBoardProperties)
        self.xetSysmanResContainerGetDeviceProperties = _xetSysmanResContainerGetDeviceProperties_t(self.__dditable.SysmanResContainer.pfnGetDeviceProperties)
        self.xetSysmanResContainerSetDeviceProperties = _xetSysmanResContainerSetDeviceProperties_t(self.__dditable.SysmanResContainer.pfnSetDeviceProperties)

        # call driver to get function pointers
        _SysmanResource = _xet_sysman_resource_dditable_t()
        r = xe_result_v(self.__dll.xetGetSysmanResourceProcAddrTable(version, byref(_SysmanResource)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanResource = _SysmanResource

        # attach function interface to function address
        self.xetSysmanResourceGetInfo = _xetSysmanResourceGetInfo_t(self.__dditable.SysmanResource.pfnGetInfo)
        self.xetSysmanResourceGetPsuProperties = _xetSysmanResourceGetPsuProperties_t(self.__dditable.SysmanResource.pfnGetPsuProperties)
        self.xetSysmanResourceSetPsuProperties = _xetSysmanResourceSetPsuProperties_t(self.__dditable.SysmanResource.pfnSetPsuProperties)
        self.xetSysmanResourceGetTempProperties = _xetSysmanResourceGetTempProperties_t(self.__dditable.SysmanResource.pfnGetTempProperties)
        self.xetSysmanResourceSetTempProperties = _xetSysmanResourceSetTempProperties_t(self.__dditable.SysmanResource.pfnSetTempProperties)
        self.xetSysmanResourceGetFanProperties = _xetSysmanResourceGetFanProperties_t(self.__dditable.SysmanResource.pfnGetFanProperties)
        self.xetSysmanResourceSetFanProperties = _xetSysmanResourceSetFanProperties_t(self.__dditable.SysmanResource.pfnSetFanProperties)
        self.xetSysmanResourceGetLedProperties = _xetSysmanResourceGetLedProperties_t(self.__dditable.SysmanResource.pfnGetLedProperties)
        self.xetSysmanResourceSetLedProperties = _xetSysmanResourceSetLedProperties_t(self.__dditable.SysmanResource.pfnSetLedProperties)
        self.xetSysmanResourceGetFirmwareProperties = _xetSysmanResourceGetFirmwareProperties_t(self.__dditable.SysmanResource.pfnGetFirmwareProperties)
        self.xetSysmanResourceSetFirmwareProperties = _xetSysmanResourceSetFirmwareProperties_t(self.__dditable.SysmanResource.pfnSetFirmwareProperties)
        self.xetSysmanResourceGetPwrProperties = _xetSysmanResourceGetPwrProperties_t(self.__dditable.SysmanResource.pfnGetPwrProperties)
        self.xetSysmanResourceSetPwrProperties = _xetSysmanResourceSetPwrProperties_t(self.__dditable.SysmanResource.pfnSetPwrProperties)
        self.xetSysmanResourceGetFreqProperties = _xetSysmanResourceGetFreqProperties_t(self.__dditable.SysmanResource.pfnGetFreqProperties)
        self.xetSysmanResourceSetFreqProperties = _xetSysmanResourceSetFreqProperties_t(self.__dditable.SysmanResource.pfnSetFreqProperties)
        self.xetSysmanResourceGetPwrWellProperties = _xetSysmanResourceGetPwrWellProperties_t(self.__dditable.SysmanResource.pfnGetPwrWellProperties)
        self.xetSysmanResourceSetPwrWellProperties = _xetSysmanResourceSetPwrWellProperties_t(self.__dditable.SysmanResource.pfnSetPwrWellProperties)
        self.xetSysmanResourceGetAccelProperties = _xetSysmanResourceGetAccelProperties_t(self.__dditable.SysmanResource.pfnGetAccelProperties)
        self.xetSysmanResourceSetAccelProperties = _xetSysmanResourceSetAccelProperties_t(self.__dditable.SysmanResource.pfnSetAccelProperties)
        self.xetSysmanResourceGetMemProperties = _xetSysmanResourceGetMemProperties_t(self.__dditable.SysmanResource.pfnGetMemProperties)
        self.xetSysmanResourceSetMemProperties = _xetSysmanResourceSetMemProperties_t(self.__dditable.SysmanResource.pfnSetMemProperties)
        self.xetSysmanResourceGetLinkProperties = _xetSysmanResourceGetLinkProperties_t(self.__dditable.SysmanResource.pfnGetLinkProperties)
        self.xetSysmanResourceSetLinkProperties = _xetSysmanResourceSetLinkProperties_t(self.__dditable.SysmanResource.pfnSetLinkProperties)

        # success!
