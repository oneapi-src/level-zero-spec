"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

 @file zes.py
 @version v0.91-271

 """
import platform
from ctypes import *
from enum import *

###############################################################################
__version__ = "1.0"

###############################################################################
## @brief Handle to a driver instance
class zes_driver_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of device object
class zes_device_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device scheduler queue
class zes_sched_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device performance factors
class zes_perf_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device power domain
class zes_pwr_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device frequency domain
class zes_freq_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device engine group
class zes_engine_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device standby control
class zes_standby_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device firmware
class zes_firmware_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device memory module
class zes_mem_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman fabric port
class zes_fabric_port_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device temperature sensor
class zes_temp_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device power supply
class zes_psu_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device fan
class zes_fan_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device LED
class zes_led_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device RAS error set
class zes_ras_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device diagnostics test suite
class zes_diag_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device event
class zes_event_handle_t(c_void_p):
    pass

###############################################################################
## @brief API version of Sysman
class zes_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 0, 91 )              ## version 0.91

class zes_version_t(c_int):
    def __str__(self):
        return str(zes_version_v(value))


###############################################################################
## @brief Maximum number of characters in string properties.
ZES_STRING_PROPERTY_SIZE = 64

###############################################################################
## @brief Types of accelerator engines
class zes_engine_type_v(IntEnum):
    OTHER = 0                                       ## Undefined types of accelerators.
    COMPUTE = auto()                                ## Engines that process compute kernels.
    _3D = auto()                                    ## Engines that process 3D content
    MEDIA = auto()                                  ## Engines that process media workloads
    DMA = auto()                                    ## Engines that copy blocks of data

class zes_engine_type_t(c_int):
    def __str__(self):
        return str(zes_engine_type_v(value))


###############################################################################
## @brief Device repair status
class zes_repair_status_v(IntEnum):
    UNSUPPORTED = 0                                 ## The device does not support in-field repairs.
    NOT_PERFORMED = auto()                          ## The device has never been repaired.
    PERFORMED = auto()                              ## The device has been repaired.

class zes_repair_status_t(c_int):
    def __str__(self):
        return str(zes_repair_status_v(value))


###############################################################################
## @brief Device reset reasons
class zes_reset_reasons_v(IntEnum):
    NONE = 0                                        ## The device does not need to be reset
    WEDGED = ZE_BIT( 0 )                            ## The device needs to be reset because one or more parts of the hardware
                                                    ## is wedged
    REPAIR = ZE_BIT( 1 )                            ## The device needs to be reset in order to complete in-field repairs

class zes_reset_reasons_t(c_int):
    def __str__(self):
        return str(zes_reset_reasons_v(value))


###############################################################################
## @brief Device state
class zes_device_state_t(Structure):
    _fields_ = [
        ("reset", c_ulong),                                             ## [out] Indicates if the device needs to be reset and for what reasons
                                                                        ## (bitfield of ::zes_reset_reasons_t)
        ("repaired", zes_repair_status_t)                               ## [out] Indicates if the device has been repaired
    ]

###############################################################################
## @brief Device properties
class zes_device_properties_t(Structure):
    _fields_ = [
        ("core", ze_device_properties_t),                               ## [out] Core device properties
        ("numSubdevices", c_ulong),                                     ## [out] Number of sub-devices
        ("serialNumber", c_int8_t * ZES_STRING_PROPERTY_SIZE),          ## [out] Manufacturing serial number (NULL terminated string value)
        ("boardNumber", c_int8_t * ZES_STRING_PROPERTY_SIZE),           ## [out] Manufacturing board number (NULL terminated string value)
        ("brandName", c_int8_t * ZES_STRING_PROPERTY_SIZE),             ## [out] Brand name of the device (NULL terminated string value)
        ("modelName", c_int8_t * ZES_STRING_PROPERTY_SIZE),             ## [out] Model name of the device (NULL terminated string value)
        ("vendorName", c_int8_t * ZES_STRING_PROPERTY_SIZE),            ## [out] Vendor name of the device (NULL terminated string value)
        ("driverVersion", c_int8_t * ZES_STRING_PROPERTY_SIZE)          ## [out] Installed driver version (NULL terminated string value)
    ]

###############################################################################
## @brief Contains information about a process that has an open connection with
##        this device
## 
## @details
##     - The application can use the process ID to query the OS for the owner
##       and the path to the executable.
class zes_process_state_t(Structure):
    _fields_ = [
        ("processId", c_ulong),                                         ## [out] Host OS process ID.
        ("memSize", c_int64_t),                                         ## [out] Device memory size in bytes allocated by this process (may not
                                                                        ## necessarily be resident on the device at the time of reading).
        ("engines", c_ulonglong)                                        ## [out] Bitfield of accelerator engines being used by this process (or
                                                                        ## 1<<::zes_engine_type_t together).
    ]

###############################################################################
## @brief PCI address
class zes_pci_address_t(Structure):
    _fields_ = [
        ("domain", c_ulong),                                            ## [out] BDF domain
        ("bus", c_ulong),                                               ## [out] BDF bus
        ("device", c_ulong),                                            ## [out] BDF device
        ("function", c_ulong)                                           ## [out] BDF function
    ]

###############################################################################
## @brief PCI speed
class zes_pci_speed_t(Structure):
    _fields_ = [
        ("gen", c_ulong),                                               ## [out] The link generation
        ("width", c_ulong),                                             ## [out] The number of lanes
        ("maxBandwidth", c_ulonglong)                                   ## [out] The maximum bandwidth in bytes/sec
    ]

###############################################################################
## @brief Static PCI properties
class zes_pci_properties_t(Structure):
    _fields_ = [
        ("address", zes_pci_address_t),                                 ## [out] The BDF address
        ("maxSpeed", zes_pci_speed_t)                                   ## [out] Fastest port configuration supported by the device.
    ]

###############################################################################
## @brief PCI link status
class zes_pci_link_status_v(IntEnum):
    GREEN = 0                                       ## The link is up and operating as expected
    YELLOW = auto()                                 ## The link is up but has quality and/or bandwidth degradation
    RED = auto()                                    ## The link has stability issues and preventing workloads making forward
                                                    ## progress

class zes_pci_link_status_t(c_int):
    def __str__(self):
        return str(zes_pci_link_status_v(value))


###############################################################################
## @brief PCI link quality degradation reasons
class zes_pci_link_qual_issues_v(IntEnum):
    NONE = 0                                        ## There are no quality issues with the link at this time
    REPLAYS = ZE_BIT( 0 )                           ## An significant number of replays are occurring
    SPEED = ZE_BIT( 1 )                             ## There is a degradation in the maximum bandwidth of the link

class zes_pci_link_qual_issues_t(c_int):
    def __str__(self):
        return str(zes_pci_link_qual_issues_v(value))


###############################################################################
## @brief PCI link stability issues
class zes_pci_link_stab_issues_v(IntEnum):
    NONE = 0                                        ## There are no connection stability issues at this time
    RETRAINING = ZE_BIT( 0 )                        ## Link retraining has occurred to deal with quality issues

class zes_pci_link_stab_issues_t(c_int):
    def __str__(self):
        return str(zes_pci_link_stab_issues_v(value))


###############################################################################
## @brief Dynamic PCI state
class zes_pci_state_t(Structure):
    _fields_ = [
        ("status", zes_pci_link_status_t),                              ## [out] The current status of the port
        ("qualityIssues", zes_pci_link_qual_issues_t),                  ## [out] If status is ::ZES_PCI_LINK_STATUS_YELLOW, this gives a bitfield
                                                                        ## of quality issues that have been detected
        ("stabilityIssues", zes_pci_link_stab_issues_t),                ## [out] If status is ::ZES_PCI_LINK_STATUS_RED, this gives a bitfield of
                                                                        ## reasons for the connection instability
        ("speed", zes_pci_speed_t)                                      ## [out] The current port configure speed
    ]

###############################################################################
## @brief PCI bar types
class zes_pci_bar_type_v(IntEnum):
    MMIO = 0                                        ## MMIO registers
    ROM = auto()                                    ## ROM aperture
    MEM = auto()                                    ## Device memory

class zes_pci_bar_type_t(c_int):
    def __str__(self):
        return str(zes_pci_bar_type_v(value))


###############################################################################
## @brief Properties of a pci bar
class zes_pci_bar_properties_t(Structure):
    _fields_ = [
        ("type", zes_pci_bar_type_t),                                   ## [out] The type of bar
        ("index", c_ulong),                                             ## [out] The index of the bar
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
class zes_pci_stats_t(Structure):
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
        ("speed", zes_pci_speed_t)                                      ## [out] The current speed of the link
    ]

###############################################################################
## @brief Diagnostic test suite type
class zes_diag_type_v(IntEnum):
    SCAN = 0                                        ## Run SCAN diagnostics
    ARRAY = auto()                                  ## Run Array diagnostics

class zes_diag_type_t(c_int):
    def __str__(self):
        return str(zes_diag_type_v(value))


###############################################################################
## @brief Diagnostic results
class zes_diag_result_v(IntEnum):
    NO_ERRORS = 0                                   ## Diagnostic completed without finding errors to repair
    ABORT = auto()                                  ## Diagnostic had problems running tests
    FAIL_CANT_REPAIR = auto()                       ## Diagnostic had problems setting up repairs
    REBOOT_FOR_REPAIR = auto()                      ## Diagnostics found errors, setup for repair and reboot is required to
                                                    ## complete the process

class zes_diag_result_t(c_int):
    def __str__(self):
        return str(zes_diag_result_v(value))


###############################################################################
## @brief Diagnostic test index to use for the very first test.
ZES_DIAG_FIRST_TEST_INDEX = 0x0

###############################################################################
## @brief Diagnostic test index to use for the very last test.
ZES_DIAG_LAST_TEST_INDEX = 0xFFFFFFFF

###############################################################################
## @brief Diagnostic test
class zes_diag_test_t(Structure):
    _fields_ = [
        ("index", c_ulong),                                             ## [out] Index of the test
        ("name", c_char * ZES_STRING_PROPERTY_SIZE)                     ## [out] Name of the test
    ]

###############################################################################
## @brief Diagnostics test suite properties
class zes_diag_properties_t(Structure):
    _fields_ = [
        ("type", zes_diag_type_t),                                      ## [out] The type of diagnostics test suite
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("name", c_char * ZES_STRING_PROPERTY_SIZE),                    ## [out] Name of the diagnostics test suite
        ("haveTests", ze_bool_t)                                        ## [out] Indicates if this test suite has individual tests which can be
                                                                        ## run separately (use the function ::zesDiagnosticsGetTests() to get the
                                                                        ## list of these tests)
    ]

###############################################################################
## @brief Accelerator engine groups
class zes_engine_group_v(IntEnum):
    ALL = 0                                         ## Access information about all engines combined.
    COMPUTE_ALL = auto()                            ## Access information about all compute engines combined.
    MEDIA_ALL = auto()                              ## Access information about all media engines combined.
    COPY_ALL = auto()                               ## Access information about all copy (blitter) engines combined.

class zes_engine_group_t(c_int):
    def __str__(self):
        return str(zes_engine_group_v(value))


###############################################################################
## @brief Engine group properties
class zes_engine_properties_t(Structure):
    _fields_ = [
        ("type", zes_engine_group_t),                                   ## [out] The engine group
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
class zes_engine_stats_t(Structure):
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
## @brief Event types
class zes_event_type_v(IntEnum):
    NONE = 0                                        ## Specifies no events
    DEVICE_RESET = ZE_BIT( 0 )                      ## Event is triggered when the driver is going to reset the device
    DEVICE_SLEEP_STATE_ENTER = ZE_BIT( 1 )          ## Event is triggered when the driver is about to put the device into a
                                                    ## deep sleep state
    DEVICE_SLEEP_STATE_EXIT = ZE_BIT( 2 )           ## Event is triggered when the driver is waking the device up from a deep
                                                    ## sleep state
    FREQ_THROTTLED = ZE_BIT( 3 )                    ## Event is triggered when the frequency starts being throttled
    ENERGY_THRESHOLD_CROSSED = ZE_BIT( 4 )          ## Event is triggered when the energy consumption threshold is reached
                                                    ## (use ::zesPowerSetEnergyThreshold() to configure).
    TEMP_CRITICAL = ZE_BIT( 5 )                     ## Event is triggered when the critical temperature is reached (use
                                                    ## ::zesTemperatureSetConfig() to configure - disabled by default).
    TEMP_THRESHOLD1 = ZE_BIT( 6 )                   ## Event is triggered when the temperature crosses threshold 1 (use
                                                    ## ::zesTemperatureSetConfig() to configure - disabled by default).
    TEMP_THRESHOLD2 = ZE_BIT( 7 )                   ## Event is triggered when the temperature crosses threshold 2 (use
                                                    ## ::zesTemperatureSetConfig() to configure - disabled by default).
    MEM_HEALTH = ZE_BIT( 8 )                        ## Event is triggered when the health of device memory changes.
    FABRIC_PORT_HEALTH = ZE_BIT( 9 )                ## Event is triggered when the health of fabric ports change.
    PCI_LINK_HEALTH = ZE_BIT( 10 )                  ## Event is triggered when the health of the PCI link changes.
    RAS_CORRECTABLE_ERRORS = ZE_BIT( 11 )           ## Event is triggered when accelerator RAS correctable errors cross
                                                    ## thresholds (use ::zesRasSetConfig() to configure - disabled by
                                                    ## default).
    RAS_UNCORRECTABLE_ERRORS = ZE_BIT( 12 )         ## Event is triggered when accelerator RAS uncorrectable errors cross
                                                    ## thresholds (use ::zesRasSetConfig() to configure - disabled by
                                                    ## default).
    DEVICE_RESET_REQUIRED = ZE_BIT( 14 )            ## Event is triggered when the device needs to be reset (use
                                                    ## ::zesDeviceGetState() to determine the reasons for the reset).
    ALL = 0x0FFF                                    ## Specifies all events

class zes_event_type_t(c_int):
    def __str__(self):
        return str(zes_event_type_v(value))


###############################################################################
## @brief Event configuration for a device
class zes_event_config_t(Structure):
    _fields_ = [
        ("registered", c_ulong)                                         ## [in,out] List of registered events (Bitfield of events
                                                                        ## ::zes_event_type_t). ::ZES_EVENT_TYPE_NONE indicates there are no
                                                                        ## registered events. ::ZES_EVENT_TYPE_ALL indicates that all events are
                                                                        ## registered.
    ]

###############################################################################
## @brief Don't wait - just check if there are any new events
ZES_EVENT_WAIT_NONE = 0x0

###############################################################################
## @brief Wait infinitely for events to arrive.
ZES_EVENT_WAIT_INFINITE = 0xFFFFFFFF

###############################################################################
## @brief Maximum Fabric port model string size
ZES_MAX_FABRIC_PORT_MODEL_SIZE = 256

###############################################################################
## @brief Maximum size of the buffer that will return information about link
##        types
ZES_MAX_FABRIC_LINK_TYPE_SIZE = 256

###############################################################################
## @brief Fabric port status
class zes_fabric_port_status_v(IntEnum):
    GREEN = 0                                       ## The port is up and operating as expected
    YELLOW = auto()                                 ## The port is up but has quality and/or speed degradation
    RED = auto()                                    ## Port connection instabilities are preventing workloads making forward
                                                    ## progress
    BLACK = auto()                                  ## The port is configured down

class zes_fabric_port_status_t(c_int):
    def __str__(self):
        return str(zes_fabric_port_status_v(value))


###############################################################################
## @brief Fabric port quality degradation reasons
class zes_fabric_port_qual_issues_v(IntEnum):
    NONE = 0                                        ## There are no quality issues with the link at this time
    FABRIC_PORT_QUAL_LINK_ERRORS = ZE_BIT( 0 )      ## Excessive link errors are occurring
    SPEED = ZE_BIT( 1 )                             ## There is a degradation in the bitrate and/or width of the link

class zes_fabric_port_qual_issues_t(c_int):
    def __str__(self):
        return str(zes_fabric_port_qual_issues_v(value))


###############################################################################
## @brief Fabric port stability issues
class zes_fabric_port_stab_issues_v(IntEnum):
    NONE = 0                                        ## There are no connection stability issues at this time
    FAILED = ZE_BIT( 0 )                            ## A previously operating link has failed. Hardware will automatically
                                                    ## retrain this port. This state will persist until either the physical
                                                    ## connection is removed or the link trains successfully.
    TRAINING_TIMEOUT = ZE_BIT( 1 )                  ## A connection has not been established within an expected time.
                                                    ## Hardware will continue to attempt port training. This status will
                                                    ## persist until either the physical connection is removed or the link
                                                    ## successfully trains.
    FLAPPING = ZE_BIT( 2 )                          ## Port has excessively trained and then transitioned down for some
                                                    ## period of time. Driver will allow port to continue to train, but will
                                                    ## not enable the port for use until the port has been disabled and
                                                    ## subsequently re-enabled using ::zesFabricPortSetConfig().

class zes_fabric_port_stab_issues_t(c_int):
    def __str__(self):
        return str(zes_fabric_port_stab_issues_v(value))


###############################################################################
## @brief Unique identifier for a fabric port
## 
## @details
##     - This not a universal identifier. The identified is garanteed to be
##       unique for the current hardware configuration of the system. Changes
##       in the hardware may result in a different identifier for a given port.
##     - The main purpose of this identifier to build up an instantaneous
##       topology map of system connectivity. An application should enumerate
##       all fabric ports and match ::zes_fabric_port_state_t.remotePortId to
##       ::zes_fabric_port_properties_t.portId.
class zes_fabric_port_id_t(Structure):
    _fields_ = [
        ("fabricId", c_ulong),                                          ## [out] Unique identifier for the fabric end-point
        ("attachId", c_ulong),                                          ## [out] Unique identifier for the device attachment point
        ("portNumber", c_ubyte)                                         ## [out] The logical port number (this is typically marked somewhere on
                                                                        ## the physical device)
    ]

###############################################################################
## @brief Fabric port speed in one direction
class zes_fabric_port_speed_t(Structure):
    _fields_ = [
        ("bitRate", c_ulonglong),                                       ## [out] Bits/sec that the link is operating at
        ("width", c_ulong)                                              ## [out] The number of lanes
    ]

###############################################################################
## @brief Fabric port properties
class zes_fabric_port_properties_t(Structure):
    _fields_ = [
        ("model", c_int8_t * ZES_MAX_FABRIC_PORT_MODEL_SIZE),           ## [out] Description of port technology
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the port is located on a sub-device; false means that
                                                                        ## the port is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("portId", zes_fabric_port_id_t),                               ## [out] The unique port identifier
        ("maxRxSpeed", zes_fabric_port_speed_t),                        ## [out] Maximum speed supported by the receive side of the port
        ("maxTxSpeed", zes_fabric_port_speed_t)                         ## [out] Maximum speed supported by the transmit side of the port
    ]

###############################################################################
## @brief Provides information about the fabric link attached to a port
class zes_fabric_link_type_t(Structure):
    _fields_ = [
        ("desc", c_int8_t * ZES_MAX_FABRIC_LINK_TYPE_SIZE)              ## [out] This provides a static textural description of the physic
                                                                        ## attachment type
    ]

###############################################################################
## @brief Fabric port configuration
class zes_fabric_port_config_t(Structure):
    _fields_ = [
        ("enabled", ze_bool_t),                                         ## [in,out] Port is configured up/down
        ("beaconing", ze_bool_t)                                        ## [in,out] Beaconing is configured on/off
    ]

###############################################################################
## @brief Fabric port state
class zes_fabric_port_state_t(Structure):
    _fields_ = [
        ("status", zes_fabric_port_status_t),                           ## [out] The current status of the port
        ("qualityIssues", zes_fabric_port_qual_issues_t),               ## [out] If status is ::ZES_FABRIC_PORT_STATUS_YELLOW, this gives a
                                                                        ## bitfield of quality issues that have been detected
        ("stabilityIssues", zes_fabric_port_stab_issues_t),             ## [out] If status is ::ZES_FABRIC_PORT_STATUS_RED, this gives a bitfield
                                                                        ## of reasons for the connection instability
        ("remotePortId", zes_fabric_port_id_t),                         ## [out] The unique port identifier for the remote connection point
        ("rxSpeed", zes_fabric_port_speed_t),                           ## [out] Current maximum receive speed
        ("txSpeed", zes_fabric_port_speed_t)                            ## [out] Current maximum transmit speed
    ]

###############################################################################
## @brief Fabric port throughput.
class zes_fabric_port_throughput_t(Structure):
    _fields_ = [
        ("timestamp", c_ulonglong),                                     ## [out] Monotonic timestamp counter in microseconds when the measurement
                                                                        ## was made.
                                                                        ## No assumption should be made about the absolute value of the timestamp.
                                                                        ## It should only be used to calculate delta time between two snapshots
                                                                        ## of the same structure.
                                                                        ## Never take the delta of this timestamp with the timestamp from a
                                                                        ## different structure.
        ("rxCounter", c_ulonglong),                                     ## [out] Monotonic counter for the number of bytes received. This
                                                                        ## includes all protocol overhead, not only the GPU traffic.
        ("txCounter", c_ulonglong)                                      ## [out] Monotonic counter for the number of bytes transmitted. This
                                                                        ## includes all protocol overhead, not only the GPU traffic.
    ]

###############################################################################
## @brief Fan resource speed mode
class zes_fan_speed_mode_v(IntEnum):
    DEFAULT = 0                                     ## The fan speed is operating using the hardware default settings
    FIXED = auto()                                  ## The fan speed is currently set to a fixed value
    TABLE = auto()                                  ## The fan speed is currently controlled dynamically by hardware based on
                                                    ## a temp/speed table

class zes_fan_speed_mode_t(c_int):
    def __str__(self):
        return str(zes_fan_speed_mode_v(value))


###############################################################################
## @brief Fan speed units
class zes_fan_speed_units_v(IntEnum):
    RPM = 0                                         ## The fan speed is in units of revolutions per minute (rpm)
    PERCENT = auto()                                ## The fan speed is a percentage of the maximum speed of the fan

class zes_fan_speed_units_t(c_int):
    def __str__(self):
        return str(zes_fan_speed_units_v(value))


###############################################################################
## @brief Fan temperature/speed pair
class zes_fan_temp_speed_t(Structure):
    _fields_ = [
        ("temperature", c_ulong),                                       ## [in,out] Temperature in degrees Celsius.
        ("speed", c_ulong),                                             ## [in,out] The speed of the fan
        ("units", zes_fan_speed_units_t)                                ## [in,out] The units of the member speed
    ]

###############################################################################
## @brief Maximum number of fan temperature/speed pairs in the fan speed table.
ZES_FAN_TEMP_SPEED_PAIR_COUNT = 32

###############################################################################
## @brief Fan properties
class zes_fan_properties_t(Structure):
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
class zes_fan_config_t(Structure):
    _fields_ = [
        ("mode", zes_fan_speed_mode_t),                                 ## [in,out] The fan speed mode (fixed, temp-speed table)
        ("speed", c_ulong),                                             ## [in,out] The fixed fan speed setting
        ("speedUnits", zes_fan_speed_units_t),                          ## [in,out] The units of the fixed fan speed setting
        ("numPoints", c_ulong),                                         ## [in,out] The number of valid points in the fan speed table
        ("table", zes_fan_temp_speed_t * ZES_FAN_TEMP_SPEED_PAIR_COUNT) ## [in,out] Array of temperature/fan speed pairs
    ]

###############################################################################
## @brief Firmware properties
class zes_firmware_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can flash the firmware assuming the user
                                                                        ## has permissions
        ("name", c_int8_t * ZES_STRING_PROPERTY_SIZE),                  ## [out] NULL terminated string value
        ("version", c_int8_t * ZES_STRING_PROPERTY_SIZE)                ## [out] NULL terminated string value
    ]

###############################################################################
## @brief Frequency domains.
class zes_freq_domain_v(IntEnum):
    GPU = 0                                         ## GPU Core Domain.
    MEMORY = auto()                                 ## Local Memory Domain.

class zes_freq_domain_t(c_int):
    def __str__(self):
        return str(zes_freq_domain_v(value))


###############################################################################
## @brief Frequency properties
## 
## @details
##     - Indicates if this frequency domain can be overclocked (if true,
##       functions such as ::zesFrequencyOcSetConfig() are supported).
##     - The min/max hardware frequencies are specified for non-overclock
##       configurations. For overclock configurations, use
##       ::zesFrequencyOcGetConfig() to determine the maximum frequency that
##       can be requested.
##     - If step is non-zero, the available frequencies are (min, min + step,
##       min + 2xstep, ..., max). Otherwise, call
##       ::zesFrequencyGetAvailableClocks() to get the list of frequencies that
##       can be requested.
class zes_freq_properties_t(Structure):
    _fields_ = [
        ("type", zes_freq_domain_t),                                    ## [out] The hardware block that this frequency domain controls (GPU,
                                                                        ## memory, ...)
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Indicates if software can control the frequency of this domain
                                                                        ## assuming the user has permissions
        ("isThrottleEventSupported", ze_bool_t),                        ## [out] Indicates if software can register to receive event
                                                                        ## ::ZES_EVENT_TYPE_FREQ_THROTTLED
        ("min", c_double),                                              ## [out] The minimum hardware clock frequency in units of MHz
        ("max", c_double),                                              ## [out] The maximum non-overclock hardware clock frequency in units of
                                                                        ## MHz.
        ("step", c_double)                                              ## [out] The minimum step-size for clock frequencies in units of MHz. The
                                                                        ## hardware will clamp intermediate frequencies to lowest multiplier of
                                                                        ## this number.
    ]

###############################################################################
## @brief Frequency range between which the hardware can operate.
class zes_freq_range_t(Structure):
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
class zes_freq_throttle_reasons_v(IntEnum):
    NONE = 0                                        ## frequency not throttled
    AVE_PWR_CAP = ZE_BIT( 0 )                       ## frequency throttled due to average power excursion (PL1)
    BURST_PWR_CAP = ZE_BIT( 1 )                     ## frequency throttled due to burst power excursion (PL2)
    CURRENT_LIMIT = ZE_BIT( 2 )                     ## frequency throttled due to current excursion (PL4)
    THERMAL_LIMIT = ZE_BIT( 3 )                     ## frequency throttled due to thermal excursion (T > TjMax)
    PSU_ALERT = ZE_BIT( 4 )                         ## frequency throttled due to power supply assertion
    SW_RANGE = ZE_BIT( 5 )                          ## frequency throttled due to software supplied frequency range
    HW_RANGE = ZE_BIT( 6 )                          ## frequency throttled due to a sub block that has a lower frequency
                                                    ## range when it receives clocks

class zes_freq_throttle_reasons_t(c_int):
    def __str__(self):
        return str(zes_freq_throttle_reasons_v(value))


###############################################################################
## @brief Frequency state
class zes_freq_state_t(Structure):
    _fields_ = [
        ("request", c_double),                                          ## [out] The current frequency request in MHz.
        ("tdp", c_double),                                              ## [out] The maximum frequency in MHz supported under the current TDP
                                                                        ## conditions
        ("efficient", c_double),                                        ## [out] The efficient minimum frequency in MHz
        ("actual", c_double),                                           ## [out] The resolved frequency in MHz
        ("throttleReasons", c_ulong)                                    ## [out] The reasons that the frequency is being limited by the hardware
                                                                        ## (Bitfield of ::zes_freq_throttle_reasons_t).
    ]

###############################################################################
## @brief Frequency throttle time snapshot
## 
## @details
##     - Percent time throttled is calculated by taking two snapshots (s1, s2)
##       and using the equation: %throttled = (s2.throttleTime -
##       s1.throttleTime) / (s2.timestamp - s1.timestamp)
class zes_freq_throttle_time_t(Structure):
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
class zes_oc_mode_v(IntEnum):
    OFF = 0                                         ## Overclocking if off - hardware is running using factory default
                                                    ## voltages/frequencies.
    OVERRIDE = auto()                               ## Overclock override mode - In this mode, a fixed user-supplied voltage
                                                    ## is applied independent of the frequency request. The maximum permitted
                                                    ## frequency can also be increased.
    INTERPOLATIVE = auto()                          ## Overclock interpolative mode - In this mode, the voltage/frequency
                                                    ## curve can be extended with a new voltage/frequency point that will be
                                                    ## interpolated. The existing voltage/frequency points can also be offset
                                                    ## (up or down) by a fixed voltage.

class zes_oc_mode_t(c_int):
    def __str__(self):
        return str(zes_oc_mode_v(value))


###############################################################################
## @brief Overclocking properties
## 
## @details
##     - Provides all the overclocking capabilities and properties supported by
##       the device for the frequency domain.
class zes_oc_capabilities_t(Structure):
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
class zes_oc_config_t(Structure):
    _fields_ = [
        ("mode", zes_oc_mode_t),                                        ## [in,out] Overclock Mode ::zes_oc_mode_t.
        ("frequency", c_double),                                        ## [in,out] Overclocking Frequency in MHz. This cannot be greater than
                                                                        ## ::zes_oc_capabilities_t.maxOcFrequency.
        ("voltageTarget", c_double),                                    ## [in,out] Overclock voltage in Volts. This cannot be greater than
                                                                        ## ::zes_oc_capabilities_t.maxOcVoltage.
        ("voltageOffset", c_double)                                     ## [in,out] This voltage offset is applied to all points on the
                                                                        ## voltage/frequency curve, include the new overclock voltageTarget. It
                                                                        ## can be in the range (::zes_oc_capabilities_t.minOcVoltageOffset,
                                                                        ## ::zes_oc_capabilities_t.maxOcVoltageOffset).
    ]

###############################################################################
## @brief LED properties
class zes_led_properties_t(Structure):
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
class zes_led_state_t(Structure):
    _fields_ = [
        ("isOn", ze_bool_t),                                            ## [in,out] Indicates if the LED is on or off
        ("red", c_ubyte),                                               ## [in,out][range(0, 255)] The LED red value
        ("green", c_ubyte),                                             ## [in,out][range(0, 255)] The LED green value
        ("blue", c_ubyte)                                               ## [in,out][range(0, 255)] The LED blue value
    ]

###############################################################################
## @brief Memory module types
class zes_mem_type_v(IntEnum):
    HBM = 0                                         ## HBM memory
    DDR = auto()                                    ## DDR memory
    SRAM = auto()                                   ## SRAM memory
    L1 = auto()                                     ## L1 cache
    L3 = auto()                                     ## L3 cache
    GRF = auto()                                    ## Execution unit register file
    SLM = auto()                                    ## Execution unit shared local memory

class zes_mem_type_t(c_int):
    def __str__(self):
        return str(zes_mem_type_v(value))


###############################################################################
## @brief Memory health
class zes_mem_health_v(IntEnum):
    OK = 0                                          ## All memory channels are healthy
    DEGRADED = auto()                               ## Excessive correctable errors have been detected on one or more
                                                    ## channels. Device should be reset.
    CRITICAL = auto()                               ## Operating with reduced memory to cover banks with too many
                                                    ## uncorrectable errors.
    REPLACE = auto()                                ## Device should be replaced due to excessive uncorrectable errors.

class zes_mem_health_t(c_int):
    def __str__(self):
        return str(zes_mem_health_v(value))


###############################################################################
## @brief Memory properties
class zes_mem_properties_t(Structure):
    _fields_ = [
        ("type", zes_mem_type_t),                                       ## [out] The memory type
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
class zes_mem_state_t(Structure):
    _fields_ = [
        ("health", zes_mem_health_t),                                   ## [out] Indicates the health of the memory
        ("free", c_ulonglong),                                          ## [out] The free memory in bytes
        ("size", c_ulonglong)                                           ## [out] The total allocatable memory in bytes (can be less than
                                                                        ## ::zes_mem_properties_t.physicalSize)
    ]

###############################################################################
## @brief Memory bandwidth
## 
## @details
##     - Percent bandwidth is calculated by taking two snapshots (s1, s2) and
##       using the equation: %bw = 10^6 * ((s2.readCounter - s1.readCounter) +
##       (s2.writeCounter - s1.writeCounter)) / (s2.maxBandwidth *
##       (s2.timestamp - s1.timestamp))
class zes_mem_bandwidth_t(Structure):
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
## @brief Static information about a Performance Factor domain
class zes_perf_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this Performance Factor affects accelerators located on
                                                                        ## a sub-device
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("engines", c_ulonglong)                                        ## [out] Bitfield of accelerator engines that are affected by this
                                                                        ## Performance Factor (bitfield of 1<<::zes_engine_type_t).
    ]

###############################################################################
## @brief Properties related to device power settings
class zes_power_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Software can change the power limits of this domain assuming the
                                                                        ## user has permissions.
        ("isEnergyThresholdSupported", ze_bool_t),                      ## [out] Indicates if this power domain supports the energy threshold
                                                                        ## event (::ZES_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED).
        ("defaultLimit", c_ulong),                                      ## [out] The factory default TDP power limit of the part in milliwatts.
        ("minLimit", c_ulong),                                          ## [out] The minimum power limit in milliwatts that can be requested.
        ("maxLimit", c_ulong)                                           ## [out] The maximum power limit in milliwatts that can be requested.
    ]

###############################################################################
## @brief Energy counter snapshot
## 
## @details
##     - Average power is calculated by taking two snapshots (s1, s2) and using
##       the equation: PowerWatts = (s2.energy - s1.energy) / (s2.timestamp -
##       s1.timestamp)
class zes_power_energy_counter_t(Structure):
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
class zes_power_sustained_limit_t(Structure):
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
class zes_power_burst_limit_t(Structure):
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
class zes_power_peak_limit_t(Structure):
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
class zes_energy_threshold_t(Structure):
    _fields_ = [
        ("enable", ze_bool_t),                                          ## [in,out] Indicates if the energy threshold is enabled.
        ("threshold", c_double),                                        ## [in,out] The energy threshold in Joules. Will be 0.0 if no threshold
                                                                        ## has been set.
        ("processId", c_ulong)                                          ## [in,out] The host process ID that set the energy threshold. Will be
                                                                        ## 0xFFFFFFFF if no threshold has been set.
    ]

###############################################################################
## @brief PSU voltage status
class zes_psu_voltage_status_v(IntEnum):
    NORMAL = 0                                      ## No unusual voltages have been detected
    OVER = auto()                                   ## Over-voltage has occurred
    UNDER = auto()                                  ## Under-voltage has occurred

class zes_psu_voltage_status_t(c_int):
    def __str__(self):
        return str(zes_psu_voltage_status_v(value))


###############################################################################
## @brief Static properties of the power supply
class zes_psu_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("haveFan", ze_bool_t),                                         ## [out] True if the power supply has a fan
        ("ampLimit", c_ulong)                                           ## [out] The maximum electrical current in amperes that can be drawn
    ]

###############################################################################
## @brief Dynamic state of the power supply
class zes_psu_state_t(Structure):
    _fields_ = [
        ("voltStatus", zes_psu_voltage_status_t),                       ## [out] The current PSU voltage status
        ("fanFailed", ze_bool_t),                                       ## [out] Indicates if the fan has failed
        ("temperature", c_ulong),                                       ## [out] Read the current heatsink temperature in degrees Celsius.
        ("current", c_ulong)                                            ## [out] The amps being drawn in amperes
    ]

###############################################################################
## @brief RAS error type
class zes_ras_error_type_v(IntEnum):
    CORRECTABLE = 0                                 ## Errors were corrected by hardware
    UNCORRECTABLE = auto()                          ## Error were not corrected

class zes_ras_error_type_t(c_int):
    def __str__(self):
        return str(zes_ras_error_type_v(value))


###############################################################################
## @brief RAS properties
class zes_ras_properties_t(Structure):
    _fields_ = [
        ("type", zes_ras_error_type_t),                                 ## [out] The type of RAS error
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
    ]

###############################################################################
## @brief RAS error details
class zes_ras_details_t(Structure):
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
##        (::ZES_EVENT_TYPE_RAS_CORRECTABLE_ERRORS,
##        ::ZES_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS)
## 
## @details
##     - The driver maintains a total counter which is updated every time a
##       hardware block covered by the corresponding RAS error set notifies
##       that an error has occurred. When this total count goes above the
##       totalThreshold specified below, a RAS event is triggered.
##     - The driver also maintains a counter for each category of RAS error
##       (see ::zes_ras_details_t for a breakdown). Each time a hardware block
##       of that category notifies that an error has occurred, that
##       corresponding category counter is updated. When it goes above the
##       threshold specified in detailedThresholds, a RAS event is triggered.
class zes_ras_config_t(Structure):
    _fields_ = [
        ("totalThreshold", c_ulonglong),                                ## [in,out] If the total RAS errors exceeds this threshold, the event
                                                                        ## will be triggered. A value of 0ULL disables triggering the event based
                                                                        ## on the total counter.
        ("detailedThresholds", zes_ras_details_t),                      ## [in,out] If the RAS errors for each category exceed the threshold for
                                                                        ## that category, the event will be triggered. A value of 0ULL will
                                                                        ## disable an event being triggered for that category.
        ("processId", c_ulong)                                          ## [out] Host processId that set this configuration (ignored when setting
                                                                        ## the configuration).
    ]

###############################################################################
## @brief Scheduler mode
class zes_sched_mode_v(IntEnum):
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

class zes_sched_mode_t(c_int):
    def __str__(self):
        return str(zes_sched_mode_v(value))


###############################################################################
## @brief Properties related to scheduler component
class zes_sched_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Software can change the scheduler component configuration
                                                                        ## assuming the user has permissions.
        ("engines", c_ulonglong),                                       ## [out] Bitfield of accelerator engines that are controlled by this
                                                                        ## scheduler component (bitfield of 1<<::zes_engine_type_t).
        ("supportedModes", c_ulong)                                     ## [out] Bitfield of scheduler modes that can be configured for this
                                                                        ## scheduler component (bitfield of 1<<::zes_sched_mode_t).
    ]

###############################################################################
## @brief Disable forward progress guard timeout.
ZES_SCHED_WATCHDOG_DISABLE = (~(0ULL))

###############################################################################
## @brief Configuration for timeout scheduler mode (::ZES_SCHED_MODE_TIMEOUT)
class zes_sched_timeout_properties_t(Structure):
    _fields_ = [
        ("watchdogTimeout", c_ulonglong)                                ## [in,out] The maximum time in microseconds that the scheduler will wait
                                                                        ## for a batch of work submitted to a hardware engine to complete or to
                                                                        ## be preempted so as to run another context.
                                                                        ## If this time is exceeded, the hardware engine is reset and the context terminated.
                                                                        ## If set to ::ZES_SCHED_WATCHDOG_DISABLE, a running workload can run as
                                                                        ## long as it wants without being terminated, but preemption attempts to
                                                                        ## run other contexts are permitted but not enforced.
    ]

###############################################################################
## @brief Configuration for timeslice scheduler mode
##        (::ZES_SCHED_MODE_TIMESLICE)
class zes_sched_timeslice_properties_t(Structure):
    _fields_ = [
        ("interval", c_ulonglong),                                      ## [in,out] The average interval in microseconds that a submission for a
                                                                        ## context will run on a hardware engine before being preempted out to
                                                                        ## run a pending submission for another context.
        ("yieldTimeout", c_ulonglong)                                   ## [in,out] The maximum time in microseconds that the scheduler will wait
                                                                        ## to preempt a workload running on an engine before deciding to reset
                                                                        ## the hardware engine and terminating the associated context.
    ]

###############################################################################
## @brief Standby hardware components
class zes_standby_type_v(IntEnum):
    GLOBAL = 0                                      ## Control the overall standby policy of the device/sub-device

class zes_standby_type_t(c_int):
    def __str__(self):
        return str(zes_standby_type_v(value))


###############################################################################
## @brief Standby hardware component properties
class zes_standby_properties_t(Structure):
    _fields_ = [
        ("type", zes_standby_type_t),                                   ## [out] Which standby hardware component this controls
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong)                                        ## [out] If onSubdevice is true, this gives the ID of the sub-device
    ]

###############################################################################
## @brief Standby promotion modes
class zes_standby_promo_mode_v(IntEnum):
    DEFAULT = 0                                     ## Best compromise between performance and energy savings.
    NEVER = auto()                                  ## The device/component will never shutdown. This can improve performance
                                                    ## but uses more energy.

class zes_standby_promo_mode_t(c_int):
    def __str__(self):
        return str(zes_standby_promo_mode_v(value))


###############################################################################
## @brief Temperature sensors
class zes_temp_sensors_v(IntEnum):
    GLOBAL = 0                                      ## The maximum temperature across all device sensors
    GPU = auto()                                    ## The maximum temperature across all sensors in the GPU
    MEMORY = auto()                                 ## The maximum temperature across all sensors in the local memory

class zes_temp_sensors_t(c_int):
    def __str__(self):
        return str(zes_temp_sensors_v(value))


###############################################################################
## @brief Temperature sensor properties
class zes_temp_properties_t(Structure):
    _fields_ = [
        ("type", zes_temp_sensors_t),                                   ## [out] Which part of the device the temperature sensor measures
        ("onSubdevice", ze_bool_t),                                     ## [out] True if the resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("isCriticalTempSupported", ze_bool_t),                         ## [out] Indicates if the critical temperature event
                                                                        ## ::ZES_EVENT_TYPE_TEMP_CRITICAL is supported
        ("isThreshold1Supported", ze_bool_t),                           ## [out] Indicates if the temperature threshold 1 event
                                                                        ## ::ZES_EVENT_TYPE_TEMP_THRESHOLD1 is supported
        ("isThreshold2Supported", ze_bool_t)                            ## [out] Indicates if the temperature threshold 2 event
                                                                        ## ::ZES_EVENT_TYPE_TEMP_THRESHOLD2 is supported
    ]

###############################################################################
## @brief Temperature sensor threshold
class zes_temp_threshold_t(Structure):
    _fields_ = [
        ("enableLowToHigh", ze_bool_t),                                 ## [in,out] Trigger an event when the temperature crosses from below the
                                                                        ## threshold to above.
        ("enableHighToLow", ze_bool_t),                                 ## [in,out] Trigger an event when the temperature crosses from above the
                                                                        ## threshold to below.
        ("threshold", c_double)                                         ## [in,out] The threshold in degrees Celsius.
    ]

###############################################################################
## @brief Temperature configuration - which events should be triggered and the
##        trigger conditions.
class zes_temp_config_t(Structure):
    _fields_ = [
        ("enableCritical", ze_bool_t),                                  ## [in,out] Indicates if event ::ZES_EVENT_TYPE_TEMP_CRITICAL should be
                                                                        ## triggered by the driver.
        ("threshold1", zes_temp_threshold_t),                           ## [in,out] Configuration controlling if and when event
                                                                        ## ::ZES_EVENT_TYPE_TEMP_THRESHOLD1 should be triggered by the driver.
        ("threshold2", zes_temp_threshold_t),                           ## [in,out] Configuration controlling if and when event
                                                                        ## ::ZES_EVENT_TYPE_TEMP_THRESHOLD2 should be triggered by the driver.
        ("processId", c_ulong)                                          ## [out] Host processId that set this configuration (ignored when setting
                                                                        ## the configuration).
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
## @brief Function-pointer for zesDeviceGetProperties
if __use_win_types:
    _zesDeviceGetProperties_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_device_properties_t) )
else:
    _zesDeviceGetProperties_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_device_properties_t) )

###############################################################################
## @brief Function-pointer for zesDeviceGetState
if __use_win_types:
    _zesDeviceGetState_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_device_state_t) )
else:
    _zesDeviceGetState_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_device_state_t) )

###############################################################################
## @brief Function-pointer for zesDeviceReset
if __use_win_types:
    _zesDeviceReset_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, ze_bool_t )
else:
    _zesDeviceReset_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, ze_bool_t )

###############################################################################
## @brief Function-pointer for zesDeviceProcessesGetState
if __use_win_types:
    _zesDeviceProcessesGetState_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_process_state_t) )
else:
    _zesDeviceProcessesGetState_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_process_state_t) )

###############################################################################
## @brief Function-pointer for zesDevicePciGetProperties
if __use_win_types:
    _zesDevicePciGetProperties_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_pci_properties_t) )
else:
    _zesDevicePciGetProperties_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_pci_properties_t) )

###############################################################################
## @brief Function-pointer for zesDevicePciGetState
if __use_win_types:
    _zesDevicePciGetState_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_pci_state_t) )
else:
    _zesDevicePciGetState_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_pci_state_t) )

###############################################################################
## @brief Function-pointer for zesDevicePciGetBars
if __use_win_types:
    _zesDevicePciGetBars_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_pci_bar_properties_t) )
else:
    _zesDevicePciGetBars_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_pci_bar_properties_t) )

###############################################################################
## @brief Function-pointer for zesDevicePciGetStats
if __use_win_types:
    _zesDevicePciGetStats_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_pci_stats_t) )
else:
    _zesDevicePciGetStats_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_pci_stats_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumDiagnosticTestSuites
if __use_win_types:
    _zesDeviceEnumDiagnosticTestSuites_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_diag_handle_t) )
else:
    _zesDeviceEnumDiagnosticTestSuites_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_diag_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumEngineGroups
if __use_win_types:
    _zesDeviceEnumEngineGroups_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_engine_handle_t) )
else:
    _zesDeviceEnumEngineGroups_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_engine_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceCreateEvents
if __use_win_types:
    _zesDeviceCreateEvents_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_event_handle_t) )
else:
    _zesDeviceCreateEvents_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(zes_event_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumFabricPorts
if __use_win_types:
    _zesDeviceEnumFabricPorts_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_fabric_port_handle_t) )
else:
    _zesDeviceEnumFabricPorts_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_fabric_port_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumFans
if __use_win_types:
    _zesDeviceEnumFans_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_fan_handle_t) )
else:
    _zesDeviceEnumFans_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_fan_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumFirmwares
if __use_win_types:
    _zesDeviceEnumFirmwares_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_firmware_handle_t) )
else:
    _zesDeviceEnumFirmwares_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_firmware_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumFrequencyDomains
if __use_win_types:
    _zesDeviceEnumFrequencyDomains_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_freq_handle_t) )
else:
    _zesDeviceEnumFrequencyDomains_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_freq_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumLeds
if __use_win_types:
    _zesDeviceEnumLeds_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_led_handle_t) )
else:
    _zesDeviceEnumLeds_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_led_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumMemoryModules
if __use_win_types:
    _zesDeviceEnumMemoryModules_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_mem_handle_t) )
else:
    _zesDeviceEnumMemoryModules_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_mem_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumPerformanceFactorDomains
if __use_win_types:
    _zesDeviceEnumPerformanceFactorDomains_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_perf_handle_t) )
else:
    _zesDeviceEnumPerformanceFactorDomains_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_perf_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumPowerDomains
if __use_win_types:
    _zesDeviceEnumPowerDomains_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_pwr_handle_t) )
else:
    _zesDeviceEnumPowerDomains_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_pwr_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumPsus
if __use_win_types:
    _zesDeviceEnumPsus_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_psu_handle_t) )
else:
    _zesDeviceEnumPsus_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_psu_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumRasErrorSets
if __use_win_types:
    _zesDeviceEnumRasErrorSets_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_ras_handle_t) )
else:
    _zesDeviceEnumRasErrorSets_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_ras_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumSchedulers
if __use_win_types:
    _zesDeviceEnumSchedulers_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_sched_handle_t) )
else:
    _zesDeviceEnumSchedulers_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_sched_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumStandbyDomains
if __use_win_types:
    _zesDeviceEnumStandbyDomains_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_standby_handle_t) )
else:
    _zesDeviceEnumStandbyDomains_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_standby_handle_t) )

###############################################################################
## @brief Function-pointer for zesDeviceEnumTemperatureSensors
if __use_win_types:
    _zesDeviceEnumTemperatureSensors_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_temp_handle_t) )
else:
    _zesDeviceEnumTemperatureSensors_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, POINTER(c_ulong), POINTER(zes_temp_handle_t) )


###############################################################################
## @brief Table of Device functions pointers
class _zes_device_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesDeviceGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _zesDeviceGetState_t
        ("pfnReset", c_void_p),                                         ## _zesDeviceReset_t
        ("pfnProcessesGetState", c_void_p),                             ## _zesDeviceProcessesGetState_t
        ("pfnPciGetProperties", c_void_p),                              ## _zesDevicePciGetProperties_t
        ("pfnPciGetState", c_void_p),                                   ## _zesDevicePciGetState_t
        ("pfnPciGetBars", c_void_p),                                    ## _zesDevicePciGetBars_t
        ("pfnPciGetStats", c_void_p),                                   ## _zesDevicePciGetStats_t
        ("pfnEnumDiagnosticTestSuites", c_void_p),                      ## _zesDeviceEnumDiagnosticTestSuites_t
        ("pfnEnumEngineGroups", c_void_p),                              ## _zesDeviceEnumEngineGroups_t
        ("pfnCreateEvents", c_void_p),                                  ## _zesDeviceCreateEvents_t
        ("pfnEnumFabricPorts", c_void_p),                               ## _zesDeviceEnumFabricPorts_t
        ("pfnEnumFans", c_void_p),                                      ## _zesDeviceEnumFans_t
        ("pfnEnumFirmwares", c_void_p),                                 ## _zesDeviceEnumFirmwares_t
        ("pfnEnumFrequencyDomains", c_void_p),                          ## _zesDeviceEnumFrequencyDomains_t
        ("pfnEnumLeds", c_void_p),                                      ## _zesDeviceEnumLeds_t
        ("pfnEnumMemoryModules", c_void_p),                             ## _zesDeviceEnumMemoryModules_t
        ("pfnEnumPerformanceFactorDomains", c_void_p),                  ## _zesDeviceEnumPerformanceFactorDomains_t
        ("pfnEnumPowerDomains", c_void_p),                              ## _zesDeviceEnumPowerDomains_t
        ("pfnEnumPsus", c_void_p),                                      ## _zesDeviceEnumPsus_t
        ("pfnEnumRasErrorSets", c_void_p),                              ## _zesDeviceEnumRasErrorSets_t
        ("pfnEnumSchedulers", c_void_p),                                ## _zesDeviceEnumSchedulers_t
        ("pfnEnumStandbyDomains", c_void_p),                            ## _zesDeviceEnumStandbyDomains_t
        ("pfnEnumTemperatureSensors", c_void_p)                         ## _zesDeviceEnumTemperatureSensors_t
    ]

###############################################################################
## @brief Function-pointer for zesSchedulerGetProperties
if __use_win_types:
    _zesSchedulerGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(zes_sched_properties_t) )
else:
    _zesSchedulerGetProperties_t = CFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(zes_sched_properties_t) )

###############################################################################
## @brief Function-pointer for zesSchedulerGetCurrentMode
if __use_win_types:
    _zesSchedulerGetCurrentMode_t = WINFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(zes_sched_mode_t) )
else:
    _zesSchedulerGetCurrentMode_t = CFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(zes_sched_mode_t) )

###############################################################################
## @brief Function-pointer for zesSchedulerGetTimeoutModeProperties
if __use_win_types:
    _zesSchedulerGetTimeoutModeProperties_t = WINFUNCTYPE( ze_result_t, zes_sched_handle_t, ze_bool_t, POINTER(zes_sched_timeout_properties_t) )
else:
    _zesSchedulerGetTimeoutModeProperties_t = CFUNCTYPE( ze_result_t, zes_sched_handle_t, ze_bool_t, POINTER(zes_sched_timeout_properties_t) )

###############################################################################
## @brief Function-pointer for zesSchedulerGetTimesliceModeProperties
if __use_win_types:
    _zesSchedulerGetTimesliceModeProperties_t = WINFUNCTYPE( ze_result_t, zes_sched_handle_t, ze_bool_t, POINTER(zes_sched_timeslice_properties_t) )
else:
    _zesSchedulerGetTimesliceModeProperties_t = CFUNCTYPE( ze_result_t, zes_sched_handle_t, ze_bool_t, POINTER(zes_sched_timeslice_properties_t) )

###############################################################################
## @brief Function-pointer for zesSchedulerSetTimeoutMode
if __use_win_types:
    _zesSchedulerSetTimeoutMode_t = WINFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(zes_sched_timeout_properties_t), POINTER(ze_bool_t) )
else:
    _zesSchedulerSetTimeoutMode_t = CFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(zes_sched_timeout_properties_t), POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zesSchedulerSetTimesliceMode
if __use_win_types:
    _zesSchedulerSetTimesliceMode_t = WINFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(zes_sched_timeslice_properties_t), POINTER(ze_bool_t) )
else:
    _zesSchedulerSetTimesliceMode_t = CFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(zes_sched_timeslice_properties_t), POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zesSchedulerSetExclusiveMode
if __use_win_types:
    _zesSchedulerSetExclusiveMode_t = WINFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(ze_bool_t) )
else:
    _zesSchedulerSetExclusiveMode_t = CFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zesSchedulerSetComputeUnitDebugMode
if __use_win_types:
    _zesSchedulerSetComputeUnitDebugMode_t = WINFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(ze_bool_t) )
else:
    _zesSchedulerSetComputeUnitDebugMode_t = CFUNCTYPE( ze_result_t, zes_sched_handle_t, POINTER(ze_bool_t) )


###############################################################################
## @brief Table of Scheduler functions pointers
class _zes_scheduler_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSchedulerGetProperties_t
        ("pfnGetCurrentMode", c_void_p),                                ## _zesSchedulerGetCurrentMode_t
        ("pfnGetTimeoutModeProperties", c_void_p),                      ## _zesSchedulerGetTimeoutModeProperties_t
        ("pfnGetTimesliceModeProperties", c_void_p),                    ## _zesSchedulerGetTimesliceModeProperties_t
        ("pfnSetTimeoutMode", c_void_p),                                ## _zesSchedulerSetTimeoutMode_t
        ("pfnSetTimesliceMode", c_void_p),                              ## _zesSchedulerSetTimesliceMode_t
        ("pfnSetExclusiveMode", c_void_p),                              ## _zesSchedulerSetExclusiveMode_t
        ("pfnSetComputeUnitDebugMode", c_void_p)                        ## _zesSchedulerSetComputeUnitDebugMode_t
    ]

###############################################################################
## @brief Function-pointer for zesPerformanceFactorGetProperties
if __use_win_types:
    _zesPerformanceFactorGetProperties_t = WINFUNCTYPE( ze_result_t, zes_perf_handle_t, POINTER(zes_perf_properties_t) )
else:
    _zesPerformanceFactorGetProperties_t = CFUNCTYPE( ze_result_t, zes_perf_handle_t, POINTER(zes_perf_properties_t) )

###############################################################################
## @brief Function-pointer for zesPerformanceFactorGetConfig
if __use_win_types:
    _zesPerformanceFactorGetConfig_t = WINFUNCTYPE( ze_result_t, zes_perf_handle_t, POINTER(c_double) )
else:
    _zesPerformanceFactorGetConfig_t = CFUNCTYPE( ze_result_t, zes_perf_handle_t, POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zesPerformanceFactorSetConfig
if __use_win_types:
    _zesPerformanceFactorSetConfig_t = WINFUNCTYPE( ze_result_t, zes_perf_handle_t, c_double )
else:
    _zesPerformanceFactorSetConfig_t = CFUNCTYPE( ze_result_t, zes_perf_handle_t, c_double )


###############################################################################
## @brief Table of PerformanceFactor functions pointers
class _zes_performance_factor_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesPerformanceFactorGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zesPerformanceFactorGetConfig_t
        ("pfnSetConfig", c_void_p)                                      ## _zesPerformanceFactorSetConfig_t
    ]

###############################################################################
## @brief Function-pointer for zesPowerGetProperties
if __use_win_types:
    _zesPowerGetProperties_t = WINFUNCTYPE( ze_result_t, zes_pwr_handle_t, POINTER(zes_power_properties_t) )
else:
    _zesPowerGetProperties_t = CFUNCTYPE( ze_result_t, zes_pwr_handle_t, POINTER(zes_power_properties_t) )

###############################################################################
## @brief Function-pointer for zesPowerGetEnergyCounter
if __use_win_types:
    _zesPowerGetEnergyCounter_t = WINFUNCTYPE( ze_result_t, zes_pwr_handle_t, POINTER(zes_power_energy_counter_t) )
else:
    _zesPowerGetEnergyCounter_t = CFUNCTYPE( ze_result_t, zes_pwr_handle_t, POINTER(zes_power_energy_counter_t) )

###############################################################################
## @brief Function-pointer for zesPowerGetLimits
if __use_win_types:
    _zesPowerGetLimits_t = WINFUNCTYPE( ze_result_t, zes_pwr_handle_t, POINTER(zes_power_sustained_limit_t), POINTER(zes_power_burst_limit_t), POINTER(zes_power_peak_limit_t) )
else:
    _zesPowerGetLimits_t = CFUNCTYPE( ze_result_t, zes_pwr_handle_t, POINTER(zes_power_sustained_limit_t), POINTER(zes_power_burst_limit_t), POINTER(zes_power_peak_limit_t) )

###############################################################################
## @brief Function-pointer for zesPowerSetLimits
if __use_win_types:
    _zesPowerSetLimits_t = WINFUNCTYPE( ze_result_t, zes_pwr_handle_t, POINTER(zes_power_sustained_limit_t), POINTER(zes_power_burst_limit_t), POINTER(zes_power_peak_limit_t) )
else:
    _zesPowerSetLimits_t = CFUNCTYPE( ze_result_t, zes_pwr_handle_t, POINTER(zes_power_sustained_limit_t), POINTER(zes_power_burst_limit_t), POINTER(zes_power_peak_limit_t) )

###############################################################################
## @brief Function-pointer for zesPowerGetEnergyThreshold
if __use_win_types:
    _zesPowerGetEnergyThreshold_t = WINFUNCTYPE( ze_result_t, zes_pwr_handle_t, POINTER(zes_energy_threshold_t) )
else:
    _zesPowerGetEnergyThreshold_t = CFUNCTYPE( ze_result_t, zes_pwr_handle_t, POINTER(zes_energy_threshold_t) )

###############################################################################
## @brief Function-pointer for zesPowerSetEnergyThreshold
if __use_win_types:
    _zesPowerSetEnergyThreshold_t = WINFUNCTYPE( ze_result_t, zes_pwr_handle_t, c_double )
else:
    _zesPowerSetEnergyThreshold_t = CFUNCTYPE( ze_result_t, zes_pwr_handle_t, c_double )


###############################################################################
## @brief Table of Power functions pointers
class _zes_power_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesPowerGetProperties_t
        ("pfnGetEnergyCounter", c_void_p),                              ## _zesPowerGetEnergyCounter_t
        ("pfnGetLimits", c_void_p),                                     ## _zesPowerGetLimits_t
        ("pfnSetLimits", c_void_p),                                     ## _zesPowerSetLimits_t
        ("pfnGetEnergyThreshold", c_void_p),                            ## _zesPowerGetEnergyThreshold_t
        ("pfnSetEnergyThreshold", c_void_p)                             ## _zesPowerSetEnergyThreshold_t
    ]

###############################################################################
## @brief Function-pointer for zesFrequencyGetProperties
if __use_win_types:
    _zesFrequencyGetProperties_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_freq_properties_t) )
else:
    _zesFrequencyGetProperties_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_freq_properties_t) )

###############################################################################
## @brief Function-pointer for zesFrequencyGetAvailableClocks
if __use_win_types:
    _zesFrequencyGetAvailableClocks_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(c_ulong), POINTER(c_double) )
else:
    _zesFrequencyGetAvailableClocks_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(c_ulong), POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zesFrequencyGetRange
if __use_win_types:
    _zesFrequencyGetRange_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_freq_range_t) )
else:
    _zesFrequencyGetRange_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_freq_range_t) )

###############################################################################
## @brief Function-pointer for zesFrequencySetRange
if __use_win_types:
    _zesFrequencySetRange_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_freq_range_t) )
else:
    _zesFrequencySetRange_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_freq_range_t) )

###############################################################################
## @brief Function-pointer for zesFrequencyGetState
if __use_win_types:
    _zesFrequencyGetState_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_freq_state_t) )
else:
    _zesFrequencyGetState_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_freq_state_t) )

###############################################################################
## @brief Function-pointer for zesFrequencyGetThrottleTime
if __use_win_types:
    _zesFrequencyGetThrottleTime_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_freq_throttle_time_t) )
else:
    _zesFrequencyGetThrottleTime_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_freq_throttle_time_t) )

###############################################################################
## @brief Function-pointer for zesFrequencyOcGetCapabilities
if __use_win_types:
    _zesFrequencyOcGetCapabilities_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_oc_capabilities_t) )
else:
    _zesFrequencyOcGetCapabilities_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_oc_capabilities_t) )

###############################################################################
## @brief Function-pointer for zesFrequencyOcGetConfig
if __use_win_types:
    _zesFrequencyOcGetConfig_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_oc_config_t) )
else:
    _zesFrequencyOcGetConfig_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_oc_config_t) )

###############################################################################
## @brief Function-pointer for zesFrequencyOcSetConfig
if __use_win_types:
    _zesFrequencyOcSetConfig_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_oc_config_t), POINTER(ze_bool_t) )
else:
    _zesFrequencyOcSetConfig_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(zes_oc_config_t), POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zesFrequencyOcGetIccMax
if __use_win_types:
    _zesFrequencyOcGetIccMax_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(c_double) )
else:
    _zesFrequencyOcGetIccMax_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zesFrequencyOcSetIccMax
if __use_win_types:
    _zesFrequencyOcSetIccMax_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, c_double )
else:
    _zesFrequencyOcSetIccMax_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, c_double )

###############################################################################
## @brief Function-pointer for zesFrequencyOcGetTjMax
if __use_win_types:
    _zesFrequencyOcGetTjMax_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(c_double) )
else:
    _zesFrequencyOcGetTjMax_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zesFrequencyOcSetTjMax
if __use_win_types:
    _zesFrequencyOcSetTjMax_t = WINFUNCTYPE( ze_result_t, zes_freq_handle_t, c_double )
else:
    _zesFrequencyOcSetTjMax_t = CFUNCTYPE( ze_result_t, zes_freq_handle_t, c_double )


###############################################################################
## @brief Table of Frequency functions pointers
class _zes_frequency_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesFrequencyGetProperties_t
        ("pfnGetAvailableClocks", c_void_p),                            ## _zesFrequencyGetAvailableClocks_t
        ("pfnGetRange", c_void_p),                                      ## _zesFrequencyGetRange_t
        ("pfnSetRange", c_void_p),                                      ## _zesFrequencySetRange_t
        ("pfnGetState", c_void_p),                                      ## _zesFrequencyGetState_t
        ("pfnGetThrottleTime", c_void_p),                               ## _zesFrequencyGetThrottleTime_t
        ("pfnOcGetCapabilities", c_void_p),                             ## _zesFrequencyOcGetCapabilities_t
        ("pfnOcGetConfig", c_void_p),                                   ## _zesFrequencyOcGetConfig_t
        ("pfnOcSetConfig", c_void_p),                                   ## _zesFrequencyOcSetConfig_t
        ("pfnOcGetIccMax", c_void_p),                                   ## _zesFrequencyOcGetIccMax_t
        ("pfnOcSetIccMax", c_void_p),                                   ## _zesFrequencyOcSetIccMax_t
        ("pfnOcGetTjMax", c_void_p),                                    ## _zesFrequencyOcGetTjMax_t
        ("pfnOcSetTjMax", c_void_p)                                     ## _zesFrequencyOcSetTjMax_t
    ]

###############################################################################
## @brief Function-pointer for zesEngineGetProperties
if __use_win_types:
    _zesEngineGetProperties_t = WINFUNCTYPE( ze_result_t, zes_engine_handle_t, POINTER(zes_engine_properties_t) )
else:
    _zesEngineGetProperties_t = CFUNCTYPE( ze_result_t, zes_engine_handle_t, POINTER(zes_engine_properties_t) )

###############################################################################
## @brief Function-pointer for zesEngineGetActivity
if __use_win_types:
    _zesEngineGetActivity_t = WINFUNCTYPE( ze_result_t, zes_engine_handle_t, POINTER(zes_engine_stats_t) )
else:
    _zesEngineGetActivity_t = CFUNCTYPE( ze_result_t, zes_engine_handle_t, POINTER(zes_engine_stats_t) )


###############################################################################
## @brief Table of Engine functions pointers
class _zes_engine_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesEngineGetProperties_t
        ("pfnGetActivity", c_void_p)                                    ## _zesEngineGetActivity_t
    ]

###############################################################################
## @brief Function-pointer for zesStandbyGetProperties
if __use_win_types:
    _zesStandbyGetProperties_t = WINFUNCTYPE( ze_result_t, zes_standby_handle_t, POINTER(zes_standby_properties_t) )
else:
    _zesStandbyGetProperties_t = CFUNCTYPE( ze_result_t, zes_standby_handle_t, POINTER(zes_standby_properties_t) )

###############################################################################
## @brief Function-pointer for zesStandbyGetMode
if __use_win_types:
    _zesStandbyGetMode_t = WINFUNCTYPE( ze_result_t, zes_standby_handle_t, POINTER(zes_standby_promo_mode_t) )
else:
    _zesStandbyGetMode_t = CFUNCTYPE( ze_result_t, zes_standby_handle_t, POINTER(zes_standby_promo_mode_t) )

###############################################################################
## @brief Function-pointer for zesStandbySetMode
if __use_win_types:
    _zesStandbySetMode_t = WINFUNCTYPE( ze_result_t, zes_standby_handle_t, zes_standby_promo_mode_t )
else:
    _zesStandbySetMode_t = CFUNCTYPE( ze_result_t, zes_standby_handle_t, zes_standby_promo_mode_t )


###############################################################################
## @brief Table of Standby functions pointers
class _zes_standby_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesStandbyGetProperties_t
        ("pfnGetMode", c_void_p),                                       ## _zesStandbyGetMode_t
        ("pfnSetMode", c_void_p)                                        ## _zesStandbySetMode_t
    ]

###############################################################################
## @brief Function-pointer for zesFirmwareGetProperties
if __use_win_types:
    _zesFirmwareGetProperties_t = WINFUNCTYPE( ze_result_t, zes_firmware_handle_t, POINTER(zes_firmware_properties_t) )
else:
    _zesFirmwareGetProperties_t = CFUNCTYPE( ze_result_t, zes_firmware_handle_t, POINTER(zes_firmware_properties_t) )

###############################################################################
## @brief Function-pointer for zesFirmwareGetChecksum
if __use_win_types:
    _zesFirmwareGetChecksum_t = WINFUNCTYPE( ze_result_t, zes_firmware_handle_t, POINTER(c_ulong) )
else:
    _zesFirmwareGetChecksum_t = CFUNCTYPE( ze_result_t, zes_firmware_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for zesFirmwareFlash
if __use_win_types:
    _zesFirmwareFlash_t = WINFUNCTYPE( ze_result_t, zes_firmware_handle_t, c_void_p, c_ulong )
else:
    _zesFirmwareFlash_t = CFUNCTYPE( ze_result_t, zes_firmware_handle_t, c_void_p, c_ulong )


###############################################################################
## @brief Table of Firmware functions pointers
class _zes_firmware_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesFirmwareGetProperties_t
        ("pfnGetChecksum", c_void_p),                                   ## _zesFirmwareGetChecksum_t
        ("pfnFlash", c_void_p)                                          ## _zesFirmwareFlash_t
    ]

###############################################################################
## @brief Function-pointer for zesMemoryGetProperties
if __use_win_types:
    _zesMemoryGetProperties_t = WINFUNCTYPE( ze_result_t, zes_mem_handle_t, POINTER(zes_mem_properties_t) )
else:
    _zesMemoryGetProperties_t = CFUNCTYPE( ze_result_t, zes_mem_handle_t, POINTER(zes_mem_properties_t) )

###############################################################################
## @brief Function-pointer for zesMemoryGetState
if __use_win_types:
    _zesMemoryGetState_t = WINFUNCTYPE( ze_result_t, zes_mem_handle_t, POINTER(zes_mem_state_t) )
else:
    _zesMemoryGetState_t = CFUNCTYPE( ze_result_t, zes_mem_handle_t, POINTER(zes_mem_state_t) )

###############################################################################
## @brief Function-pointer for zesMemoryGetBandwidth
if __use_win_types:
    _zesMemoryGetBandwidth_t = WINFUNCTYPE( ze_result_t, zes_mem_handle_t, POINTER(zes_mem_bandwidth_t) )
else:
    _zesMemoryGetBandwidth_t = CFUNCTYPE( ze_result_t, zes_mem_handle_t, POINTER(zes_mem_bandwidth_t) )


###############################################################################
## @brief Table of Memory functions pointers
class _zes_memory_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesMemoryGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _zesMemoryGetState_t
        ("pfnGetBandwidth", c_void_p)                                   ## _zesMemoryGetBandwidth_t
    ]

###############################################################################
## @brief Function-pointer for zesFabricPortGetProperties
if __use_win_types:
    _zesFabricPortGetProperties_t = WINFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, POINTER(zes_fabric_port_properties_t) )
else:
    _zesFabricPortGetProperties_t = CFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, POINTER(zes_fabric_port_properties_t) )

###############################################################################
## @brief Function-pointer for zesFabricPortGetLinkType
if __use_win_types:
    _zesFabricPortGetLinkType_t = WINFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, ze_bool_t, POINTER(zes_fabric_link_type_t) )
else:
    _zesFabricPortGetLinkType_t = CFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, ze_bool_t, POINTER(zes_fabric_link_type_t) )

###############################################################################
## @brief Function-pointer for zesFabricPortGetConfig
if __use_win_types:
    _zesFabricPortGetConfig_t = WINFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, POINTER(zes_fabric_port_config_t) )
else:
    _zesFabricPortGetConfig_t = CFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, POINTER(zes_fabric_port_config_t) )

###############################################################################
## @brief Function-pointer for zesFabricPortSetConfig
if __use_win_types:
    _zesFabricPortSetConfig_t = WINFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, POINTER(zes_fabric_port_config_t) )
else:
    _zesFabricPortSetConfig_t = CFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, POINTER(zes_fabric_port_config_t) )

###############################################################################
## @brief Function-pointer for zesFabricPortGetState
if __use_win_types:
    _zesFabricPortGetState_t = WINFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, POINTER(zes_fabric_port_state_t) )
else:
    _zesFabricPortGetState_t = CFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, POINTER(zes_fabric_port_state_t) )

###############################################################################
## @brief Function-pointer for zesFabricPortGetThroughput
if __use_win_types:
    _zesFabricPortGetThroughput_t = WINFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, POINTER(zes_fabric_port_throughput_t) )
else:
    _zesFabricPortGetThroughput_t = CFUNCTYPE( ze_result_t, zes_fabric_port_handle_t, POINTER(zes_fabric_port_throughput_t) )


###############################################################################
## @brief Table of FabricPort functions pointers
class _zes_fabric_port_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesFabricPortGetProperties_t
        ("pfnGetLinkType", c_void_p),                                   ## _zesFabricPortGetLinkType_t
        ("pfnGetConfig", c_void_p),                                     ## _zesFabricPortGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zesFabricPortSetConfig_t
        ("pfnGetState", c_void_p),                                      ## _zesFabricPortGetState_t
        ("pfnGetThroughput", c_void_p)                                  ## _zesFabricPortGetThroughput_t
    ]

###############################################################################
## @brief Function-pointer for zesTemperatureGetProperties
if __use_win_types:
    _zesTemperatureGetProperties_t = WINFUNCTYPE( ze_result_t, zes_temp_handle_t, POINTER(zes_temp_properties_t) )
else:
    _zesTemperatureGetProperties_t = CFUNCTYPE( ze_result_t, zes_temp_handle_t, POINTER(zes_temp_properties_t) )

###############################################################################
## @brief Function-pointer for zesTemperatureGetConfig
if __use_win_types:
    _zesTemperatureGetConfig_t = WINFUNCTYPE( ze_result_t, zes_temp_handle_t, POINTER(zes_temp_config_t) )
else:
    _zesTemperatureGetConfig_t = CFUNCTYPE( ze_result_t, zes_temp_handle_t, POINTER(zes_temp_config_t) )

###############################################################################
## @brief Function-pointer for zesTemperatureSetConfig
if __use_win_types:
    _zesTemperatureSetConfig_t = WINFUNCTYPE( ze_result_t, zes_temp_handle_t, POINTER(zes_temp_config_t) )
else:
    _zesTemperatureSetConfig_t = CFUNCTYPE( ze_result_t, zes_temp_handle_t, POINTER(zes_temp_config_t) )

###############################################################################
## @brief Function-pointer for zesTemperatureGetState
if __use_win_types:
    _zesTemperatureGetState_t = WINFUNCTYPE( ze_result_t, zes_temp_handle_t, POINTER(c_double) )
else:
    _zesTemperatureGetState_t = CFUNCTYPE( ze_result_t, zes_temp_handle_t, POINTER(c_double) )


###############################################################################
## @brief Table of Temperature functions pointers
class _zes_temperature_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesTemperatureGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zesTemperatureGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zesTemperatureSetConfig_t
        ("pfnGetState", c_void_p)                                       ## _zesTemperatureGetState_t
    ]

###############################################################################
## @brief Function-pointer for zesPsuGetProperties
if __use_win_types:
    _zesPsuGetProperties_t = WINFUNCTYPE( ze_result_t, zes_psu_handle_t, POINTER(zes_psu_properties_t) )
else:
    _zesPsuGetProperties_t = CFUNCTYPE( ze_result_t, zes_psu_handle_t, POINTER(zes_psu_properties_t) )

###############################################################################
## @brief Function-pointer for zesPsuGetState
if __use_win_types:
    _zesPsuGetState_t = WINFUNCTYPE( ze_result_t, zes_psu_handle_t, POINTER(zes_psu_state_t) )
else:
    _zesPsuGetState_t = CFUNCTYPE( ze_result_t, zes_psu_handle_t, POINTER(zes_psu_state_t) )


###############################################################################
## @brief Table of Psu functions pointers
class _zes_psu_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesPsuGetProperties_t
        ("pfnGetState", c_void_p)                                       ## _zesPsuGetState_t
    ]

###############################################################################
## @brief Function-pointer for zesFanGetProperties
if __use_win_types:
    _zesFanGetProperties_t = WINFUNCTYPE( ze_result_t, zes_fan_handle_t, POINTER(zes_fan_properties_t) )
else:
    _zesFanGetProperties_t = CFUNCTYPE( ze_result_t, zes_fan_handle_t, POINTER(zes_fan_properties_t) )

###############################################################################
## @brief Function-pointer for zesFanGetConfig
if __use_win_types:
    _zesFanGetConfig_t = WINFUNCTYPE( ze_result_t, zes_fan_handle_t, POINTER(zes_fan_config_t) )
else:
    _zesFanGetConfig_t = CFUNCTYPE( ze_result_t, zes_fan_handle_t, POINTER(zes_fan_config_t) )

###############################################################################
## @brief Function-pointer for zesFanSetConfig
if __use_win_types:
    _zesFanSetConfig_t = WINFUNCTYPE( ze_result_t, zes_fan_handle_t, POINTER(zes_fan_config_t) )
else:
    _zesFanSetConfig_t = CFUNCTYPE( ze_result_t, zes_fan_handle_t, POINTER(zes_fan_config_t) )

###############################################################################
## @brief Function-pointer for zesFanGetState
if __use_win_types:
    _zesFanGetState_t = WINFUNCTYPE( ze_result_t, zes_fan_handle_t, zes_fan_speed_units_t, POINTER(c_ulong) )
else:
    _zesFanGetState_t = CFUNCTYPE( ze_result_t, zes_fan_handle_t, zes_fan_speed_units_t, POINTER(c_ulong) )


###############################################################################
## @brief Table of Fan functions pointers
class _zes_fan_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesFanGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zesFanGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zesFanSetConfig_t
        ("pfnGetState", c_void_p)                                       ## _zesFanGetState_t
    ]

###############################################################################
## @brief Function-pointer for zesLedGetProperties
if __use_win_types:
    _zesLedGetProperties_t = WINFUNCTYPE( ze_result_t, zes_led_handle_t, POINTER(zes_led_properties_t) )
else:
    _zesLedGetProperties_t = CFUNCTYPE( ze_result_t, zes_led_handle_t, POINTER(zes_led_properties_t) )

###############################################################################
## @brief Function-pointer for zesLedGetState
if __use_win_types:
    _zesLedGetState_t = WINFUNCTYPE( ze_result_t, zes_led_handle_t, POINTER(zes_led_state_t) )
else:
    _zesLedGetState_t = CFUNCTYPE( ze_result_t, zes_led_handle_t, POINTER(zes_led_state_t) )

###############################################################################
## @brief Function-pointer for zesLedSetState
if __use_win_types:
    _zesLedSetState_t = WINFUNCTYPE( ze_result_t, zes_led_handle_t, POINTER(zes_led_state_t) )
else:
    _zesLedSetState_t = CFUNCTYPE( ze_result_t, zes_led_handle_t, POINTER(zes_led_state_t) )


###############################################################################
## @brief Table of Led functions pointers
class _zes_led_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesLedGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _zesLedGetState_t
        ("pfnSetState", c_void_p)                                       ## _zesLedSetState_t
    ]

###############################################################################
## @brief Function-pointer for zesRasGetProperties
if __use_win_types:
    _zesRasGetProperties_t = WINFUNCTYPE( ze_result_t, zes_ras_handle_t, POINTER(zes_ras_properties_t) )
else:
    _zesRasGetProperties_t = CFUNCTYPE( ze_result_t, zes_ras_handle_t, POINTER(zes_ras_properties_t) )

###############################################################################
## @brief Function-pointer for zesRasGetConfig
if __use_win_types:
    _zesRasGetConfig_t = WINFUNCTYPE( ze_result_t, zes_ras_handle_t, POINTER(zes_ras_config_t) )
else:
    _zesRasGetConfig_t = CFUNCTYPE( ze_result_t, zes_ras_handle_t, POINTER(zes_ras_config_t) )

###############################################################################
## @brief Function-pointer for zesRasSetConfig
if __use_win_types:
    _zesRasSetConfig_t = WINFUNCTYPE( ze_result_t, zes_ras_handle_t, POINTER(zes_ras_config_t) )
else:
    _zesRasSetConfig_t = CFUNCTYPE( ze_result_t, zes_ras_handle_t, POINTER(zes_ras_config_t) )

###############################################################################
## @brief Function-pointer for zesRasGetState
if __use_win_types:
    _zesRasGetState_t = WINFUNCTYPE( ze_result_t, zes_ras_handle_t, ze_bool_t, POINTER(c_ulonglong), POINTER(zes_ras_details_t) )
else:
    _zesRasGetState_t = CFUNCTYPE( ze_result_t, zes_ras_handle_t, ze_bool_t, POINTER(c_ulonglong), POINTER(zes_ras_details_t) )


###############################################################################
## @brief Table of Ras functions pointers
class _zes_ras_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesRasGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zesRasGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zesRasSetConfig_t
        ("pfnGetState", c_void_p)                                       ## _zesRasGetState_t
    ]

###############################################################################
## @brief Function-pointer for zesDiagnosticsGetProperties
if __use_win_types:
    _zesDiagnosticsGetProperties_t = WINFUNCTYPE( ze_result_t, zes_diag_handle_t, POINTER(zes_diag_properties_t) )
else:
    _zesDiagnosticsGetProperties_t = CFUNCTYPE( ze_result_t, zes_diag_handle_t, POINTER(zes_diag_properties_t) )

###############################################################################
## @brief Function-pointer for zesDiagnosticsGetTests
if __use_win_types:
    _zesDiagnosticsGetTests_t = WINFUNCTYPE( ze_result_t, zes_diag_handle_t, POINTER(c_ulong), POINTER(zes_diag_test_t) )
else:
    _zesDiagnosticsGetTests_t = CFUNCTYPE( ze_result_t, zes_diag_handle_t, POINTER(c_ulong), POINTER(zes_diag_test_t) )

###############################################################################
## @brief Function-pointer for zesDiagnosticsRunTests
if __use_win_types:
    _zesDiagnosticsRunTests_t = WINFUNCTYPE( ze_result_t, zes_diag_handle_t, c_ulong, c_ulong, POINTER(zes_diag_result_t) )
else:
    _zesDiagnosticsRunTests_t = CFUNCTYPE( ze_result_t, zes_diag_handle_t, c_ulong, c_ulong, POINTER(zes_diag_result_t) )


###############################################################################
## @brief Table of Diagnostics functions pointers
class _zes_diagnostics_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesDiagnosticsGetProperties_t
        ("pfnGetTests", c_void_p),                                      ## _zesDiagnosticsGetTests_t
        ("pfnRunTests", c_void_p)                                       ## _zesDiagnosticsRunTests_t
    ]

###############################################################################
## @brief Function-pointer for zesEventGetConfig
if __use_win_types:
    _zesEventGetConfig_t = WINFUNCTYPE( ze_result_t, zes_event_handle_t, POINTER(zes_event_config_t) )
else:
    _zesEventGetConfig_t = CFUNCTYPE( ze_result_t, zes_event_handle_t, POINTER(zes_event_config_t) )

###############################################################################
## @brief Function-pointer for zesEventSetConfig
if __use_win_types:
    _zesEventSetConfig_t = WINFUNCTYPE( ze_result_t, zes_event_handle_t, POINTER(zes_event_config_t) )
else:
    _zesEventSetConfig_t = CFUNCTYPE( ze_result_t, zes_event_handle_t, POINTER(zes_event_config_t) )

###############################################################################
## @brief Function-pointer for zesEventGetState
if __use_win_types:
    _zesEventGetState_t = WINFUNCTYPE( ze_result_t, zes_event_handle_t, ze_bool_t, POINTER(c_ulong) )
else:
    _zesEventGetState_t = CFUNCTYPE( ze_result_t, zes_event_handle_t, ze_bool_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for zesEventListen
if __use_win_types:
    _zesEventListen_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, c_ulong, c_ulong, POINTER(zes_event_handle_t), POINTER(c_ulong) )
else:
    _zesEventListen_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, c_ulong, c_ulong, POINTER(zes_event_handle_t), POINTER(c_ulong) )


###############################################################################
## @brief Table of Event functions pointers
class _zes_event_dditable_t(Structure):
    _fields_ = [
        ("pfnGetConfig", c_void_p),                                     ## _zesEventGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zesEventSetConfig_t
        ("pfnGetState", c_void_p),                                      ## _zesEventGetState_t
        ("pfnListen", c_void_p)                                         ## _zesEventListen_t
    ]

###############################################################################
class _zes_dditable_t(Structure):
    _fields_ = [
        ("Device", _zes_device_dditable_t),
        ("Scheduler", _zes_scheduler_dditable_t),
        ("PerformanceFactor", _zes_performance_factor_dditable_t),
        ("Power", _zes_power_dditable_t),
        ("Frequency", _zes_frequency_dditable_t),
        ("Engine", _zes_engine_dditable_t),
        ("Standby", _zes_standby_dditable_t),
        ("Firmware", _zes_firmware_dditable_t),
        ("Memory", _zes_memory_dditable_t),
        ("FabricPort", _zes_fabric_port_dditable_t),
        ("Temperature", _zes_temperature_dditable_t),
        ("Psu", _zes_psu_dditable_t),
        ("Fan", _zes_fan_dditable_t),
        ("Led", _zes_led_dditable_t),
        ("Ras", _zes_ras_dditable_t),
        ("Diagnostics", _zes_diagnostics_dditable_t),
        ("Event", _zes_event_dditable_t)
    ]

###############################################################################
## @brief zes device-driver interfaces
class ZES_DDI:
    def __init__(self, version : ze_api_version_t):
        # load the xe_loader library
        if "Windows" == platform.uname()[0]:
            self.__dll = WinDLL("ze_loader.dll")
        else:
            self.__dll = CDLL("ze_loader.so")

        # fill the ddi tables
        self.__dditable = _zes_dditable_t()

        # call driver to get function pointers
        _Device = _zes_device_dditable_t()
        r = ze_result_v(self.__dll.zesGetDeviceProcAddrTable(version, byref(_Device)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Device = _Device

        # attach function interface to function address
        self.zesDeviceGetProperties = _zesDeviceGetProperties_t(self.__dditable.Device.pfnGetProperties)
        self.zesDeviceGetState = _zesDeviceGetState_t(self.__dditable.Device.pfnGetState)
        self.zesDeviceReset = _zesDeviceReset_t(self.__dditable.Device.pfnReset)
        self.zesDeviceProcessesGetState = _zesDeviceProcessesGetState_t(self.__dditable.Device.pfnProcessesGetState)
        self.zesDevicePciGetProperties = _zesDevicePciGetProperties_t(self.__dditable.Device.pfnPciGetProperties)
        self.zesDevicePciGetState = _zesDevicePciGetState_t(self.__dditable.Device.pfnPciGetState)
        self.zesDevicePciGetBars = _zesDevicePciGetBars_t(self.__dditable.Device.pfnPciGetBars)
        self.zesDevicePciGetStats = _zesDevicePciGetStats_t(self.__dditable.Device.pfnPciGetStats)
        self.zesDeviceEnumDiagnosticTestSuites = _zesDeviceEnumDiagnosticTestSuites_t(self.__dditable.Device.pfnEnumDiagnosticTestSuites)
        self.zesDeviceEnumEngineGroups = _zesDeviceEnumEngineGroups_t(self.__dditable.Device.pfnEnumEngineGroups)
        self.zesDeviceCreateEvents = _zesDeviceCreateEvents_t(self.__dditable.Device.pfnCreateEvents)
        self.zesDeviceEnumFabricPorts = _zesDeviceEnumFabricPorts_t(self.__dditable.Device.pfnEnumFabricPorts)
        self.zesDeviceEnumFans = _zesDeviceEnumFans_t(self.__dditable.Device.pfnEnumFans)
        self.zesDeviceEnumFirmwares = _zesDeviceEnumFirmwares_t(self.__dditable.Device.pfnEnumFirmwares)
        self.zesDeviceEnumFrequencyDomains = _zesDeviceEnumFrequencyDomains_t(self.__dditable.Device.pfnEnumFrequencyDomains)
        self.zesDeviceEnumLeds = _zesDeviceEnumLeds_t(self.__dditable.Device.pfnEnumLeds)
        self.zesDeviceEnumMemoryModules = _zesDeviceEnumMemoryModules_t(self.__dditable.Device.pfnEnumMemoryModules)
        self.zesDeviceEnumPerformanceFactorDomains = _zesDeviceEnumPerformanceFactorDomains_t(self.__dditable.Device.pfnEnumPerformanceFactorDomains)
        self.zesDeviceEnumPowerDomains = _zesDeviceEnumPowerDomains_t(self.__dditable.Device.pfnEnumPowerDomains)
        self.zesDeviceEnumPsus = _zesDeviceEnumPsus_t(self.__dditable.Device.pfnEnumPsus)
        self.zesDeviceEnumRasErrorSets = _zesDeviceEnumRasErrorSets_t(self.__dditable.Device.pfnEnumRasErrorSets)
        self.zesDeviceEnumSchedulers = _zesDeviceEnumSchedulers_t(self.__dditable.Device.pfnEnumSchedulers)
        self.zesDeviceEnumStandbyDomains = _zesDeviceEnumStandbyDomains_t(self.__dditable.Device.pfnEnumStandbyDomains)
        self.zesDeviceEnumTemperatureSensors = _zesDeviceEnumTemperatureSensors_t(self.__dditable.Device.pfnEnumTemperatureSensors)

        # call driver to get function pointers
        _Scheduler = _zes_scheduler_dditable_t()
        r = ze_result_v(self.__dll.zesGetSchedulerProcAddrTable(version, byref(_Scheduler)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Scheduler = _Scheduler

        # attach function interface to function address
        self.zesSchedulerGetProperties = _zesSchedulerGetProperties_t(self.__dditable.Scheduler.pfnGetProperties)
        self.zesSchedulerGetCurrentMode = _zesSchedulerGetCurrentMode_t(self.__dditable.Scheduler.pfnGetCurrentMode)
        self.zesSchedulerGetTimeoutModeProperties = _zesSchedulerGetTimeoutModeProperties_t(self.__dditable.Scheduler.pfnGetTimeoutModeProperties)
        self.zesSchedulerGetTimesliceModeProperties = _zesSchedulerGetTimesliceModeProperties_t(self.__dditable.Scheduler.pfnGetTimesliceModeProperties)
        self.zesSchedulerSetTimeoutMode = _zesSchedulerSetTimeoutMode_t(self.__dditable.Scheduler.pfnSetTimeoutMode)
        self.zesSchedulerSetTimesliceMode = _zesSchedulerSetTimesliceMode_t(self.__dditable.Scheduler.pfnSetTimesliceMode)
        self.zesSchedulerSetExclusiveMode = _zesSchedulerSetExclusiveMode_t(self.__dditable.Scheduler.pfnSetExclusiveMode)
        self.zesSchedulerSetComputeUnitDebugMode = _zesSchedulerSetComputeUnitDebugMode_t(self.__dditable.Scheduler.pfnSetComputeUnitDebugMode)

        # call driver to get function pointers
        _PerformanceFactor = _zes_performance_factor_dditable_t()
        r = ze_result_v(self.__dll.zesGetPerformanceFactorProcAddrTable(version, byref(_PerformanceFactor)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.PerformanceFactor = _PerformanceFactor

        # attach function interface to function address
        self.zesPerformanceFactorGetProperties = _zesPerformanceFactorGetProperties_t(self.__dditable.PerformanceFactor.pfnGetProperties)
        self.zesPerformanceFactorGetConfig = _zesPerformanceFactorGetConfig_t(self.__dditable.PerformanceFactor.pfnGetConfig)
        self.zesPerformanceFactorSetConfig = _zesPerformanceFactorSetConfig_t(self.__dditable.PerformanceFactor.pfnSetConfig)

        # call driver to get function pointers
        _Power = _zes_power_dditable_t()
        r = ze_result_v(self.__dll.zesGetPowerProcAddrTable(version, byref(_Power)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Power = _Power

        # attach function interface to function address
        self.zesPowerGetProperties = _zesPowerGetProperties_t(self.__dditable.Power.pfnGetProperties)
        self.zesPowerGetEnergyCounter = _zesPowerGetEnergyCounter_t(self.__dditable.Power.pfnGetEnergyCounter)
        self.zesPowerGetLimits = _zesPowerGetLimits_t(self.__dditable.Power.pfnGetLimits)
        self.zesPowerSetLimits = _zesPowerSetLimits_t(self.__dditable.Power.pfnSetLimits)
        self.zesPowerGetEnergyThreshold = _zesPowerGetEnergyThreshold_t(self.__dditable.Power.pfnGetEnergyThreshold)
        self.zesPowerSetEnergyThreshold = _zesPowerSetEnergyThreshold_t(self.__dditable.Power.pfnSetEnergyThreshold)

        # call driver to get function pointers
        _Frequency = _zes_frequency_dditable_t()
        r = ze_result_v(self.__dll.zesGetFrequencyProcAddrTable(version, byref(_Frequency)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Frequency = _Frequency

        # attach function interface to function address
        self.zesFrequencyGetProperties = _zesFrequencyGetProperties_t(self.__dditable.Frequency.pfnGetProperties)
        self.zesFrequencyGetAvailableClocks = _zesFrequencyGetAvailableClocks_t(self.__dditable.Frequency.pfnGetAvailableClocks)
        self.zesFrequencyGetRange = _zesFrequencyGetRange_t(self.__dditable.Frequency.pfnGetRange)
        self.zesFrequencySetRange = _zesFrequencySetRange_t(self.__dditable.Frequency.pfnSetRange)
        self.zesFrequencyGetState = _zesFrequencyGetState_t(self.__dditable.Frequency.pfnGetState)
        self.zesFrequencyGetThrottleTime = _zesFrequencyGetThrottleTime_t(self.__dditable.Frequency.pfnGetThrottleTime)
        self.zesFrequencyOcGetCapabilities = _zesFrequencyOcGetCapabilities_t(self.__dditable.Frequency.pfnOcGetCapabilities)
        self.zesFrequencyOcGetConfig = _zesFrequencyOcGetConfig_t(self.__dditable.Frequency.pfnOcGetConfig)
        self.zesFrequencyOcSetConfig = _zesFrequencyOcSetConfig_t(self.__dditable.Frequency.pfnOcSetConfig)
        self.zesFrequencyOcGetIccMax = _zesFrequencyOcGetIccMax_t(self.__dditable.Frequency.pfnOcGetIccMax)
        self.zesFrequencyOcSetIccMax = _zesFrequencyOcSetIccMax_t(self.__dditable.Frequency.pfnOcSetIccMax)
        self.zesFrequencyOcGetTjMax = _zesFrequencyOcGetTjMax_t(self.__dditable.Frequency.pfnOcGetTjMax)
        self.zesFrequencyOcSetTjMax = _zesFrequencyOcSetTjMax_t(self.__dditable.Frequency.pfnOcSetTjMax)

        # call driver to get function pointers
        _Engine = _zes_engine_dditable_t()
        r = ze_result_v(self.__dll.zesGetEngineProcAddrTable(version, byref(_Engine)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Engine = _Engine

        # attach function interface to function address
        self.zesEngineGetProperties = _zesEngineGetProperties_t(self.__dditable.Engine.pfnGetProperties)
        self.zesEngineGetActivity = _zesEngineGetActivity_t(self.__dditable.Engine.pfnGetActivity)

        # call driver to get function pointers
        _Standby = _zes_standby_dditable_t()
        r = ze_result_v(self.__dll.zesGetStandbyProcAddrTable(version, byref(_Standby)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Standby = _Standby

        # attach function interface to function address
        self.zesStandbyGetProperties = _zesStandbyGetProperties_t(self.__dditable.Standby.pfnGetProperties)
        self.zesStandbyGetMode = _zesStandbyGetMode_t(self.__dditable.Standby.pfnGetMode)
        self.zesStandbySetMode = _zesStandbySetMode_t(self.__dditable.Standby.pfnSetMode)

        # call driver to get function pointers
        _Firmware = _zes_firmware_dditable_t()
        r = ze_result_v(self.__dll.zesGetFirmwareProcAddrTable(version, byref(_Firmware)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Firmware = _Firmware

        # attach function interface to function address
        self.zesFirmwareGetProperties = _zesFirmwareGetProperties_t(self.__dditable.Firmware.pfnGetProperties)
        self.zesFirmwareGetChecksum = _zesFirmwareGetChecksum_t(self.__dditable.Firmware.pfnGetChecksum)
        self.zesFirmwareFlash = _zesFirmwareFlash_t(self.__dditable.Firmware.pfnFlash)

        # call driver to get function pointers
        _Memory = _zes_memory_dditable_t()
        r = ze_result_v(self.__dll.zesGetMemoryProcAddrTable(version, byref(_Memory)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Memory = _Memory

        # attach function interface to function address
        self.zesMemoryGetProperties = _zesMemoryGetProperties_t(self.__dditable.Memory.pfnGetProperties)
        self.zesMemoryGetState = _zesMemoryGetState_t(self.__dditable.Memory.pfnGetState)
        self.zesMemoryGetBandwidth = _zesMemoryGetBandwidth_t(self.__dditable.Memory.pfnGetBandwidth)

        # call driver to get function pointers
        _FabricPort = _zes_fabric_port_dditable_t()
        r = ze_result_v(self.__dll.zesGetFabricPortProcAddrTable(version, byref(_FabricPort)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.FabricPort = _FabricPort

        # attach function interface to function address
        self.zesFabricPortGetProperties = _zesFabricPortGetProperties_t(self.__dditable.FabricPort.pfnGetProperties)
        self.zesFabricPortGetLinkType = _zesFabricPortGetLinkType_t(self.__dditable.FabricPort.pfnGetLinkType)
        self.zesFabricPortGetConfig = _zesFabricPortGetConfig_t(self.__dditable.FabricPort.pfnGetConfig)
        self.zesFabricPortSetConfig = _zesFabricPortSetConfig_t(self.__dditable.FabricPort.pfnSetConfig)
        self.zesFabricPortGetState = _zesFabricPortGetState_t(self.__dditable.FabricPort.pfnGetState)
        self.zesFabricPortGetThroughput = _zesFabricPortGetThroughput_t(self.__dditable.FabricPort.pfnGetThroughput)

        # call driver to get function pointers
        _Temperature = _zes_temperature_dditable_t()
        r = ze_result_v(self.__dll.zesGetTemperatureProcAddrTable(version, byref(_Temperature)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Temperature = _Temperature

        # attach function interface to function address
        self.zesTemperatureGetProperties = _zesTemperatureGetProperties_t(self.__dditable.Temperature.pfnGetProperties)
        self.zesTemperatureGetConfig = _zesTemperatureGetConfig_t(self.__dditable.Temperature.pfnGetConfig)
        self.zesTemperatureSetConfig = _zesTemperatureSetConfig_t(self.__dditable.Temperature.pfnSetConfig)
        self.zesTemperatureGetState = _zesTemperatureGetState_t(self.__dditable.Temperature.pfnGetState)

        # call driver to get function pointers
        _Psu = _zes_psu_dditable_t()
        r = ze_result_v(self.__dll.zesGetPsuProcAddrTable(version, byref(_Psu)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Psu = _Psu

        # attach function interface to function address
        self.zesPsuGetProperties = _zesPsuGetProperties_t(self.__dditable.Psu.pfnGetProperties)
        self.zesPsuGetState = _zesPsuGetState_t(self.__dditable.Psu.pfnGetState)

        # call driver to get function pointers
        _Fan = _zes_fan_dditable_t()
        r = ze_result_v(self.__dll.zesGetFanProcAddrTable(version, byref(_Fan)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Fan = _Fan

        # attach function interface to function address
        self.zesFanGetProperties = _zesFanGetProperties_t(self.__dditable.Fan.pfnGetProperties)
        self.zesFanGetConfig = _zesFanGetConfig_t(self.__dditable.Fan.pfnGetConfig)
        self.zesFanSetConfig = _zesFanSetConfig_t(self.__dditable.Fan.pfnSetConfig)
        self.zesFanGetState = _zesFanGetState_t(self.__dditable.Fan.pfnGetState)

        # call driver to get function pointers
        _Led = _zes_led_dditable_t()
        r = ze_result_v(self.__dll.zesGetLedProcAddrTable(version, byref(_Led)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Led = _Led

        # attach function interface to function address
        self.zesLedGetProperties = _zesLedGetProperties_t(self.__dditable.Led.pfnGetProperties)
        self.zesLedGetState = _zesLedGetState_t(self.__dditable.Led.pfnGetState)
        self.zesLedSetState = _zesLedSetState_t(self.__dditable.Led.pfnSetState)

        # call driver to get function pointers
        _Ras = _zes_ras_dditable_t()
        r = ze_result_v(self.__dll.zesGetRasProcAddrTable(version, byref(_Ras)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Ras = _Ras

        # attach function interface to function address
        self.zesRasGetProperties = _zesRasGetProperties_t(self.__dditable.Ras.pfnGetProperties)
        self.zesRasGetConfig = _zesRasGetConfig_t(self.__dditable.Ras.pfnGetConfig)
        self.zesRasSetConfig = _zesRasSetConfig_t(self.__dditable.Ras.pfnSetConfig)
        self.zesRasGetState = _zesRasGetState_t(self.__dditable.Ras.pfnGetState)

        # call driver to get function pointers
        _Diagnostics = _zes_diagnostics_dditable_t()
        r = ze_result_v(self.__dll.zesGetDiagnosticsProcAddrTable(version, byref(_Diagnostics)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Diagnostics = _Diagnostics

        # attach function interface to function address
        self.zesDiagnosticsGetProperties = _zesDiagnosticsGetProperties_t(self.__dditable.Diagnostics.pfnGetProperties)
        self.zesDiagnosticsGetTests = _zesDiagnosticsGetTests_t(self.__dditable.Diagnostics.pfnGetTests)
        self.zesDiagnosticsRunTests = _zesDiagnosticsRunTests_t(self.__dditable.Diagnostics.pfnRunTests)

        # call driver to get function pointers
        _Event = _zes_event_dditable_t()
        r = ze_result_v(self.__dll.zesGetEventProcAddrTable(version, byref(_Event)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Event = _Event

        # attach function interface to function address
        self.zesEventGetConfig = _zesEventGetConfig_t(self.__dditable.Event.pfnGetConfig)
        self.zesEventSetConfig = _zesEventSetConfig_t(self.__dditable.Event.pfnSetConfig)
        self.zesEventGetState = _zesEventGetState_t(self.__dditable.Event.pfnGetState)
        self.zesEventListen = _zesEventListen_t(self.__dditable.Event.pfnListen)

        # success!
