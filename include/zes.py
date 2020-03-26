"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

 @file zes.py

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
## @brief Handle for accessing System Resource Management features of a device
class zes_sysman_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device scheduler queue
class zes_sysman_sched_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device performance factors
class zes_sysman_perf_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device power domain
class zes_sysman_pwr_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device frequency domain
class zes_sysman_freq_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device engine group
class zes_sysman_engine_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device standby control
class zes_sysman_standby_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device firmware
class zes_sysman_firmware_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device memory module
class zes_sysman_mem_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman fabric port
class zes_sysman_fabric_port_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device temperature sensor
class zes_sysman_temp_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device power supply
class zes_sysman_psu_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device fan
class zes_sysman_fan_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device LED
class zes_sysman_led_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device RAS error set
class zes_sysman_ras_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device diagnostics test suite
class zes_sysman_diag_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle for a Sysman device event
class zes_sysman_event_handle_t(c_void_p):
    pass

###############################################################################
## @brief API version of Sysman
class zes_sysman_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 0, 91 )              ## version 0.91

class zes_sysman_version_t(c_int):
    def __str__(self):
        return str(zes_sysman_version_v(value))


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
class zes_sysman_state_t(Structure):
    _fields_ = [
        ("reset", c_ulong),                                             ## [out] Indicates if the device needs to be reset and for what reasons
                                                                        ## (bitfield of ::zes_reset_reasons_t)
        ("repaired", zes_repair_status_t)                               ## [out] Indicates if the device has been repaired
    ]

###############################################################################
## @brief Device properties
class zes_sysman_properties_t(Structure):
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
## @brief Properties related to device power settings
class zes_power_properties_t(Structure):
    _fields_ = [
        ("onSubdevice", ze_bool_t),                                     ## [out] True if this resource is located on a sub-device; false means
                                                                        ## that the resource is on the device of the calling Sysman handle
        ("subdeviceId", c_ulong),                                       ## [out] If onSubdevice is true, this gives the ID of the sub-device
        ("canControl", ze_bool_t),                                      ## [out] Software can change the power limits of this domain assuming the
                                                                        ## user has permissions.
        ("isEnergyThresholdSupported", ze_bool_t),                      ## [out] Indicates if this power domain supports the energy threshold
                                                                        ## event (::ZES_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED).
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
##       functions such as ::zesSysmanFrequencyOcSetConfig() are supported).
##     - The min/max hardware frequencies are specified for non-overclock
##       configurations. For overclock configurations, use
##       ::zesSysmanFrequencyOcGetConfig() to determine the maximum frequency
##       that can be requested.
##     - If step is non-zero, the available frequencies are (min, min + step,
##       min + 2xstep, ..., max). Otherwise, call
##       ::zesSysmanFrequencyGetAvailableClocks() to get the list of
##       frequencies that can be requested.
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
                                                                        ## ::ZES_SYSMAN_EVENT_TYPE_FREQ_THROTTLED
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
                                                    ## subsequently re-enabled using ::zesSysmanFabricPortSetConfig().

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
                                                                        ## ::ZES_SYSMAN_EVENT_TYPE_TEMP_CRITICAL is supported
        ("isThreshold1Supported", ze_bool_t),                           ## [out] Indicates if the temperature threshold 1 event
                                                                        ## ::ZES_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 is supported
        ("isThreshold2Supported", ze_bool_t)                            ## [out] Indicates if the temperature threshold 2 event
                                                                        ## ::ZES_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 is supported
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
        ("enableCritical", ze_bool_t),                                  ## [in,out] Indicates if event ::ZES_SYSMAN_EVENT_TYPE_TEMP_CRITICAL
                                                                        ## should be triggered by the driver.
        ("threshold1", zes_temp_threshold_t),                           ## [in,out] Configuration controlling if and when event
                                                                        ## ::ZES_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 should be triggered by the
                                                                        ## driver.
        ("threshold2", zes_temp_threshold_t),                           ## [in,out] Configuration controlling if and when event
                                                                        ## ::ZES_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 should be triggered by the
                                                                        ## driver.
        ("processId", c_ulong)                                          ## [out] Host processId that set this configuration (ignored when setting
                                                                        ## the configuration).
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
##        (::ZES_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS,
##        ::ZES_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS)
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
## @brief Event types
class zes_sysman_event_type_v(IntEnum):
    NONE = 0                                        ## Specifies no events
    DEVICE_RESET = ZE_BIT( 0 )                      ## Event is triggered when the driver is going to reset the device
    DEVICE_SLEEP_STATE_ENTER = ZE_BIT( 1 )          ## Event is triggered when the driver is about to put the device into a
                                                    ## deep sleep state
    DEVICE_SLEEP_STATE_EXIT = ZE_BIT( 2 )           ## Event is triggered when the driver is waking the device up from a deep
                                                    ## sleep state
    FREQ_THROTTLED = ZE_BIT( 3 )                    ## Event is triggered when the frequency starts being throttled
    ENERGY_THRESHOLD_CROSSED = ZE_BIT( 4 )          ## Event is triggered when the energy consumption threshold is reached
                                                    ## (use ::zesSysmanPowerSetEnergyThreshold() to configure).
    TEMP_CRITICAL = ZE_BIT( 5 )                     ## Event is triggered when the critical temperature is reached (use
                                                    ## ::zesSysmanTemperatureSetConfig() to configure - disabled by default).
    TEMP_THRESHOLD1 = ZE_BIT( 6 )                   ## Event is triggered when the temperature crosses threshold 1 (use
                                                    ## ::zesSysmanTemperatureSetConfig() to configure - disabled by default).
    TEMP_THRESHOLD2 = ZE_BIT( 7 )                   ## Event is triggered when the temperature crosses threshold 2 (use
                                                    ## ::zesSysmanTemperatureSetConfig() to configure - disabled by default).
    MEM_HEALTH = ZE_BIT( 8 )                        ## Event is triggered when the health of device memory changes.
    FABRIC_PORT_HEALTH = ZE_BIT( 9 )                ## Event is triggered when the health of fabric ports change.
    PCI_LINK_HEALTH = ZE_BIT( 10 )                  ## Event is triggered when the health of the PCI link changes.
    RAS_CORRECTABLE_ERRORS = ZE_BIT( 11 )           ## Event is triggered when accelerator RAS correctable errors cross
                                                    ## thresholds (use ::zesSysmanRasSetConfig() to configure - disabled by
                                                    ## default).
    RAS_UNCORRECTABLE_ERRORS = ZE_BIT( 12 )         ## Event is triggered when accelerator RAS uncorrectable errors cross
                                                    ## thresholds (use ::zesSysmanRasSetConfig() to configure - disabled by
                                                    ## default).
    DEVICE_RESET_REQUIRED = ZE_BIT( 14 )            ## Event is triggered when the device needs to be reset (use
                                                    ## ::ZESysmanDeviceGetState() to determine the reasons for the reset).
    ALL = 0x0FFF                                    ## Specifies all events

class zes_sysman_event_type_t(c_int):
    def __str__(self):
        return str(zes_sysman_event_type_v(value))


###############################################################################
## @brief Event configuration for a device
class zes_event_config_t(Structure):
    _fields_ = [
        ("registered", c_ulong)                                         ## [in,out] List of registered events (Bitfield of events
                                                                        ## ::zes_sysman_event_type_t). ::ZES_SYSMAN_EVENT_TYPE_NONE indicates
                                                                        ## there are no registered events. ::ZES_SYSMAN_EVENT_TYPE_ALL indicates
                                                                        ## that all events are registered.
    ]

###############################################################################
## @brief Don't wait - just check if there are any new events
ZES_EVENT_WAIT_NONE = 0x0

###############################################################################
## @brief Wait infinitely for events to arrive.
ZES_EVENT_WAIT_INFINITE = 0xFFFFFFFF

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
                                                                        ## run separately (use the function ::ZESysmanDiagnosticsGetTests() to
                                                                        ## get the list of these tests)
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
## @brief Function-pointer for zesSysmanGet
if __use_win_types:
    _zesSysmanGet_t = WINFUNCTYPE( ze_result_t, zes_device_handle_t, zes_sysman_version_t, POINTER(zes_sysman_handle_t) )
else:
    _zesSysmanGet_t = CFUNCTYPE( ze_result_t, zes_device_handle_t, zes_sysman_version_t, POINTER(zes_sysman_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanDeviceGetProperties
if __use_win_types:
    _zesSysmanDeviceGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_sysman_properties_t) )
else:
    _zesSysmanDeviceGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_sysman_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanDeviceGetState
if __use_win_types:
    _zesSysmanDeviceGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_sysman_state_t) )
else:
    _zesSysmanDeviceGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_sysman_state_t) )

###############################################################################
## @brief Function-pointer for zesSysmanDeviceReset
if __use_win_types:
    _zesSysmanDeviceReset_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, ze_bool_t )
else:
    _zesSysmanDeviceReset_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, ze_bool_t )

###############################################################################
## @brief Function-pointer for zesSysmanSchedulerGet
if __use_win_types:
    _zesSysmanSchedulerGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_sched_handle_t) )
else:
    _zesSysmanSchedulerGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_sched_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPerformanceFactorGet
if __use_win_types:
    _zesSysmanPerformanceFactorGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_perf_handle_t) )
else:
    _zesSysmanPerformanceFactorGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_perf_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanProcessesGetState
if __use_win_types:
    _zesSysmanProcessesGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_process_state_t) )
else:
    _zesSysmanProcessesGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_process_state_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPciGetProperties
if __use_win_types:
    _zesSysmanPciGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_pci_properties_t) )
else:
    _zesSysmanPciGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_pci_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPciGetState
if __use_win_types:
    _zesSysmanPciGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_pci_state_t) )
else:
    _zesSysmanPciGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_pci_state_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPciGetBars
if __use_win_types:
    _zesSysmanPciGetBars_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_pci_bar_properties_t) )
else:
    _zesSysmanPciGetBars_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_pci_bar_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPciGetStats
if __use_win_types:
    _zesSysmanPciGetStats_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_pci_stats_t) )
else:
    _zesSysmanPciGetStats_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_pci_stats_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPowerGet
if __use_win_types:
    _zesSysmanPowerGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_pwr_handle_t) )
else:
    _zesSysmanPowerGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_pwr_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyGet
if __use_win_types:
    _zesSysmanFrequencyGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_freq_handle_t) )
else:
    _zesSysmanFrequencyGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_freq_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanEngineGet
if __use_win_types:
    _zesSysmanEngineGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_engine_handle_t) )
else:
    _zesSysmanEngineGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_engine_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanStandbyGet
if __use_win_types:
    _zesSysmanStandbyGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_standby_handle_t) )
else:
    _zesSysmanStandbyGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_standby_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFirmwareGet
if __use_win_types:
    _zesSysmanFirmwareGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_firmware_handle_t) )
else:
    _zesSysmanFirmwareGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_firmware_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanMemoryGet
if __use_win_types:
    _zesSysmanMemoryGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_mem_handle_t) )
else:
    _zesSysmanMemoryGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_mem_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFabricPortGet
if __use_win_types:
    _zesSysmanFabricPortGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_fabric_port_handle_t) )
else:
    _zesSysmanFabricPortGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_fabric_port_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanTemperatureGet
if __use_win_types:
    _zesSysmanTemperatureGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_temp_handle_t) )
else:
    _zesSysmanTemperatureGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_temp_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPsuGet
if __use_win_types:
    _zesSysmanPsuGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_psu_handle_t) )
else:
    _zesSysmanPsuGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_psu_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFanGet
if __use_win_types:
    _zesSysmanFanGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_fan_handle_t) )
else:
    _zesSysmanFanGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_fan_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanLedGet
if __use_win_types:
    _zesSysmanLedGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_led_handle_t) )
else:
    _zesSysmanLedGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_led_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanRasGet
if __use_win_types:
    _zesSysmanRasGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_ras_handle_t) )
else:
    _zesSysmanRasGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_ras_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanEventGet
if __use_win_types:
    _zesSysmanEventGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_sysman_event_handle_t) )
else:
    _zesSysmanEventGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(zes_sysman_event_handle_t) )

###############################################################################
## @brief Function-pointer for zesSysmanDiagnosticsGet
if __use_win_types:
    _zesSysmanDiagnosticsGet_t = WINFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_diag_handle_t) )
else:
    _zesSysmanDiagnosticsGet_t = CFUNCTYPE( ze_result_t, zes_sysman_handle_t, POINTER(c_ulong), POINTER(zes_sysman_diag_handle_t) )


###############################################################################
## @brief Table of Sysman functions pointers
class _zes_sysman_dditable_t(Structure):
    _fields_ = [
        ("pfnGet", c_void_p),                                           ## _zesSysmanGet_t
        ("pfnDeviceGetProperties", c_void_p),                           ## _zesSysmanDeviceGetProperties_t
        ("pfnDeviceGetState", c_void_p),                                ## _zesSysmanDeviceGetState_t
        ("pfnDeviceReset", c_void_p),                                   ## _zesSysmanDeviceReset_t
        ("pfnSchedulerGet", c_void_p),                                  ## _zesSysmanSchedulerGet_t
        ("pfnPerformanceFactorGet", c_void_p),                          ## _zesSysmanPerformanceFactorGet_t
        ("pfnProcessesGetState", c_void_p),                             ## _zesSysmanProcessesGetState_t
        ("pfnPciGetProperties", c_void_p),                              ## _zesSysmanPciGetProperties_t
        ("pfnPciGetState", c_void_p),                                   ## _zesSysmanPciGetState_t
        ("pfnPciGetBars", c_void_p),                                    ## _zesSysmanPciGetBars_t
        ("pfnPciGetStats", c_void_p),                                   ## _zesSysmanPciGetStats_t
        ("pfnPowerGet", c_void_p),                                      ## _zesSysmanPowerGet_t
        ("pfnFrequencyGet", c_void_p),                                  ## _zesSysmanFrequencyGet_t
        ("pfnEngineGet", c_void_p),                                     ## _zesSysmanEngineGet_t
        ("pfnStandbyGet", c_void_p),                                    ## _zesSysmanStandbyGet_t
        ("pfnFirmwareGet", c_void_p),                                   ## _zesSysmanFirmwareGet_t
        ("pfnMemoryGet", c_void_p),                                     ## _zesSysmanMemoryGet_t
        ("pfnFabricPortGet", c_void_p),                                 ## _zesSysmanFabricPortGet_t
        ("pfnTemperatureGet", c_void_p),                                ## _zesSysmanTemperatureGet_t
        ("pfnPsuGet", c_void_p),                                        ## _zesSysmanPsuGet_t
        ("pfnFanGet", c_void_p),                                        ## _zesSysmanFanGet_t
        ("pfnLedGet", c_void_p),                                        ## _zesSysmanLedGet_t
        ("pfnRasGet", c_void_p),                                        ## _zesSysmanRasGet_t
        ("pfnEventGet", c_void_p),                                      ## _zesSysmanEventGet_t
        ("pfnDiagnosticsGet", c_void_p)                                 ## _zesSysmanDiagnosticsGet_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanSchedulerGetProperties
if __use_win_types:
    _zesSysmanSchedulerGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(zes_sched_properties_t) )
else:
    _zesSysmanSchedulerGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(zes_sched_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanSchedulerGetCurrentMode
if __use_win_types:
    _zesSysmanSchedulerGetCurrentMode_t = WINFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(zes_sched_mode_t) )
else:
    _zesSysmanSchedulerGetCurrentMode_t = CFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(zes_sched_mode_t) )

###############################################################################
## @brief Function-pointer for zesSysmanSchedulerGetTimeoutModeProperties
if __use_win_types:
    _zesSysmanSchedulerGetTimeoutModeProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, ze_bool_t, POINTER(zes_sched_timeout_properties_t) )
else:
    _zesSysmanSchedulerGetTimeoutModeProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, ze_bool_t, POINTER(zes_sched_timeout_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanSchedulerGetTimesliceModeProperties
if __use_win_types:
    _zesSysmanSchedulerGetTimesliceModeProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, ze_bool_t, POINTER(zes_sched_timeslice_properties_t) )
else:
    _zesSysmanSchedulerGetTimesliceModeProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, ze_bool_t, POINTER(zes_sched_timeslice_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanSchedulerSetTimeoutMode
if __use_win_types:
    _zesSysmanSchedulerSetTimeoutMode_t = WINFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(zes_sched_timeout_properties_t), POINTER(ze_bool_t) )
else:
    _zesSysmanSchedulerSetTimeoutMode_t = CFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(zes_sched_timeout_properties_t), POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zesSysmanSchedulerSetTimesliceMode
if __use_win_types:
    _zesSysmanSchedulerSetTimesliceMode_t = WINFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(zes_sched_timeslice_properties_t), POINTER(ze_bool_t) )
else:
    _zesSysmanSchedulerSetTimesliceMode_t = CFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(zes_sched_timeslice_properties_t), POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zesSysmanSchedulerSetExclusiveMode
if __use_win_types:
    _zesSysmanSchedulerSetExclusiveMode_t = WINFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(ze_bool_t) )
else:
    _zesSysmanSchedulerSetExclusiveMode_t = CFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zesSysmanSchedulerSetComputeUnitDebugMode
if __use_win_types:
    _zesSysmanSchedulerSetComputeUnitDebugMode_t = WINFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(ze_bool_t) )
else:
    _zesSysmanSchedulerSetComputeUnitDebugMode_t = CFUNCTYPE( ze_result_t, zes_sysman_sched_handle_t, POINTER(ze_bool_t) )


###############################################################################
## @brief Table of SysmanScheduler functions pointers
class _zes_sysman_scheduler_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanSchedulerGetProperties_t
        ("pfnGetCurrentMode", c_void_p),                                ## _zesSysmanSchedulerGetCurrentMode_t
        ("pfnGetTimeoutModeProperties", c_void_p),                      ## _zesSysmanSchedulerGetTimeoutModeProperties_t
        ("pfnGetTimesliceModeProperties", c_void_p),                    ## _zesSysmanSchedulerGetTimesliceModeProperties_t
        ("pfnSetTimeoutMode", c_void_p),                                ## _zesSysmanSchedulerSetTimeoutMode_t
        ("pfnSetTimesliceMode", c_void_p),                              ## _zesSysmanSchedulerSetTimesliceMode_t
        ("pfnSetExclusiveMode", c_void_p),                              ## _zesSysmanSchedulerSetExclusiveMode_t
        ("pfnSetComputeUnitDebugMode", c_void_p)                        ## _zesSysmanSchedulerSetComputeUnitDebugMode_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanPerformanceFactorGetProperties
if __use_win_types:
    _zesSysmanPerformanceFactorGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_perf_handle_t, POINTER(zes_perf_properties_t) )
else:
    _zesSysmanPerformanceFactorGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_perf_handle_t, POINTER(zes_perf_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPerformanceFactorGetConfig
if __use_win_types:
    _zesSysmanPerformanceFactorGetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_perf_handle_t, POINTER(c_double) )
else:
    _zesSysmanPerformanceFactorGetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_perf_handle_t, POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zesSysmanPerformanceFactorSetConfig
if __use_win_types:
    _zesSysmanPerformanceFactorSetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_perf_handle_t, c_double )
else:
    _zesSysmanPerformanceFactorSetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_perf_handle_t, c_double )


###############################################################################
## @brief Table of SysmanPerformanceFactor functions pointers
class _zes_sysman_performance_factor_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanPerformanceFactorGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zesSysmanPerformanceFactorGetConfig_t
        ("pfnSetConfig", c_void_p)                                      ## _zesSysmanPerformanceFactorSetConfig_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanPowerGetProperties
if __use_win_types:
    _zesSysmanPowerGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, POINTER(zes_power_properties_t) )
else:
    _zesSysmanPowerGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, POINTER(zes_power_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPowerGetEnergyCounter
if __use_win_types:
    _zesSysmanPowerGetEnergyCounter_t = WINFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, POINTER(zes_power_energy_counter_t) )
else:
    _zesSysmanPowerGetEnergyCounter_t = CFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, POINTER(zes_power_energy_counter_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPowerGetLimits
if __use_win_types:
    _zesSysmanPowerGetLimits_t = WINFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, POINTER(zes_power_sustained_limit_t), POINTER(zes_power_burst_limit_t), POINTER(zes_power_peak_limit_t) )
else:
    _zesSysmanPowerGetLimits_t = CFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, POINTER(zes_power_sustained_limit_t), POINTER(zes_power_burst_limit_t), POINTER(zes_power_peak_limit_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPowerSetLimits
if __use_win_types:
    _zesSysmanPowerSetLimits_t = WINFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, POINTER(zes_power_sustained_limit_t), POINTER(zes_power_burst_limit_t), POINTER(zes_power_peak_limit_t) )
else:
    _zesSysmanPowerSetLimits_t = CFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, POINTER(zes_power_sustained_limit_t), POINTER(zes_power_burst_limit_t), POINTER(zes_power_peak_limit_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPowerGetEnergyThreshold
if __use_win_types:
    _zesSysmanPowerGetEnergyThreshold_t = WINFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, POINTER(zes_energy_threshold_t) )
else:
    _zesSysmanPowerGetEnergyThreshold_t = CFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, POINTER(zes_energy_threshold_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPowerSetEnergyThreshold
if __use_win_types:
    _zesSysmanPowerSetEnergyThreshold_t = WINFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, c_double )
else:
    _zesSysmanPowerSetEnergyThreshold_t = CFUNCTYPE( ze_result_t, zes_sysman_pwr_handle_t, c_double )


###############################################################################
## @brief Table of SysmanPower functions pointers
class _zes_sysman_power_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanPowerGetProperties_t
        ("pfnGetEnergyCounter", c_void_p),                              ## _zesSysmanPowerGetEnergyCounter_t
        ("pfnGetLimits", c_void_p),                                     ## _zesSysmanPowerGetLimits_t
        ("pfnSetLimits", c_void_p),                                     ## _zesSysmanPowerSetLimits_t
        ("pfnGetEnergyThreshold", c_void_p),                            ## _zesSysmanPowerGetEnergyThreshold_t
        ("pfnSetEnergyThreshold", c_void_p)                             ## _zesSysmanPowerSetEnergyThreshold_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyGetProperties
if __use_win_types:
    _zesSysmanFrequencyGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_freq_properties_t) )
else:
    _zesSysmanFrequencyGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_freq_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyGetAvailableClocks
if __use_win_types:
    _zesSysmanFrequencyGetAvailableClocks_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(c_ulong), POINTER(c_double) )
else:
    _zesSysmanFrequencyGetAvailableClocks_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(c_ulong), POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyGetRange
if __use_win_types:
    _zesSysmanFrequencyGetRange_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_freq_range_t) )
else:
    _zesSysmanFrequencyGetRange_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_freq_range_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencySetRange
if __use_win_types:
    _zesSysmanFrequencySetRange_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_freq_range_t) )
else:
    _zesSysmanFrequencySetRange_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_freq_range_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyGetState
if __use_win_types:
    _zesSysmanFrequencyGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_freq_state_t) )
else:
    _zesSysmanFrequencyGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_freq_state_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyGetThrottleTime
if __use_win_types:
    _zesSysmanFrequencyGetThrottleTime_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_freq_throttle_time_t) )
else:
    _zesSysmanFrequencyGetThrottleTime_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_freq_throttle_time_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyOcGetCapabilities
if __use_win_types:
    _zesSysmanFrequencyOcGetCapabilities_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_oc_capabilities_t) )
else:
    _zesSysmanFrequencyOcGetCapabilities_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_oc_capabilities_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyOcGetConfig
if __use_win_types:
    _zesSysmanFrequencyOcGetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_oc_config_t) )
else:
    _zesSysmanFrequencyOcGetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_oc_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyOcSetConfig
if __use_win_types:
    _zesSysmanFrequencyOcSetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_oc_config_t), POINTER(ze_bool_t) )
else:
    _zesSysmanFrequencyOcSetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(zes_oc_config_t), POINTER(ze_bool_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyOcGetIccMax
if __use_win_types:
    _zesSysmanFrequencyOcGetIccMax_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(c_double) )
else:
    _zesSysmanFrequencyOcGetIccMax_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyOcSetIccMax
if __use_win_types:
    _zesSysmanFrequencyOcSetIccMax_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, c_double )
else:
    _zesSysmanFrequencyOcSetIccMax_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, c_double )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyOcGetTjMax
if __use_win_types:
    _zesSysmanFrequencyOcGetTjMax_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(c_double) )
else:
    _zesSysmanFrequencyOcGetTjMax_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, POINTER(c_double) )

###############################################################################
## @brief Function-pointer for zesSysmanFrequencyOcSetTjMax
if __use_win_types:
    _zesSysmanFrequencyOcSetTjMax_t = WINFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, c_double )
else:
    _zesSysmanFrequencyOcSetTjMax_t = CFUNCTYPE( ze_result_t, zes_sysman_freq_handle_t, c_double )


###############################################################################
## @brief Table of SysmanFrequency functions pointers
class _zes_sysman_frequency_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanFrequencyGetProperties_t
        ("pfnGetAvailableClocks", c_void_p),                            ## _zesSysmanFrequencyGetAvailableClocks_t
        ("pfnGetRange", c_void_p),                                      ## _zesSysmanFrequencyGetRange_t
        ("pfnSetRange", c_void_p),                                      ## _zesSysmanFrequencySetRange_t
        ("pfnGetState", c_void_p),                                      ## _zesSysmanFrequencyGetState_t
        ("pfnGetThrottleTime", c_void_p),                               ## _zesSysmanFrequencyGetThrottleTime_t
        ("pfnOcGetCapabilities", c_void_p),                             ## _zesSysmanFrequencyOcGetCapabilities_t
        ("pfnOcGetConfig", c_void_p),                                   ## _zesSysmanFrequencyOcGetConfig_t
        ("pfnOcSetConfig", c_void_p),                                   ## _zesSysmanFrequencyOcSetConfig_t
        ("pfnOcGetIccMax", c_void_p),                                   ## _zesSysmanFrequencyOcGetIccMax_t
        ("pfnOcSetIccMax", c_void_p),                                   ## _zesSysmanFrequencyOcSetIccMax_t
        ("pfnOcGetTjMax", c_void_p),                                    ## _zesSysmanFrequencyOcGetTjMax_t
        ("pfnOcSetTjMax", c_void_p)                                     ## _zesSysmanFrequencyOcSetTjMax_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanEngineGetProperties
if __use_win_types:
    _zesSysmanEngineGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_engine_handle_t, POINTER(zes_engine_properties_t) )
else:
    _zesSysmanEngineGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_engine_handle_t, POINTER(zes_engine_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanEngineGetActivity
if __use_win_types:
    _zesSysmanEngineGetActivity_t = WINFUNCTYPE( ze_result_t, zes_sysman_engine_handle_t, POINTER(zes_engine_stats_t) )
else:
    _zesSysmanEngineGetActivity_t = CFUNCTYPE( ze_result_t, zes_sysman_engine_handle_t, POINTER(zes_engine_stats_t) )


###############################################################################
## @brief Table of SysmanEngine functions pointers
class _zes_sysman_engine_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanEngineGetProperties_t
        ("pfnGetActivity", c_void_p)                                    ## _zesSysmanEngineGetActivity_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanStandbyGetProperties
if __use_win_types:
    _zesSysmanStandbyGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_standby_handle_t, POINTER(zes_standby_properties_t) )
else:
    _zesSysmanStandbyGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_standby_handle_t, POINTER(zes_standby_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanStandbyGetMode
if __use_win_types:
    _zesSysmanStandbyGetMode_t = WINFUNCTYPE( ze_result_t, zes_sysman_standby_handle_t, POINTER(zes_standby_promo_mode_t) )
else:
    _zesSysmanStandbyGetMode_t = CFUNCTYPE( ze_result_t, zes_sysman_standby_handle_t, POINTER(zes_standby_promo_mode_t) )

###############################################################################
## @brief Function-pointer for zesSysmanStandbySetMode
if __use_win_types:
    _zesSysmanStandbySetMode_t = WINFUNCTYPE( ze_result_t, zes_sysman_standby_handle_t, zes_standby_promo_mode_t )
else:
    _zesSysmanStandbySetMode_t = CFUNCTYPE( ze_result_t, zes_sysman_standby_handle_t, zes_standby_promo_mode_t )


###############################################################################
## @brief Table of SysmanStandby functions pointers
class _zes_sysman_standby_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanStandbyGetProperties_t
        ("pfnGetMode", c_void_p),                                       ## _zesSysmanStandbyGetMode_t
        ("pfnSetMode", c_void_p)                                        ## _zesSysmanStandbySetMode_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanFirmwareGetProperties
if __use_win_types:
    _zesSysmanFirmwareGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_firmware_handle_t, POINTER(zes_firmware_properties_t) )
else:
    _zesSysmanFirmwareGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_firmware_handle_t, POINTER(zes_firmware_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFirmwareGetChecksum
if __use_win_types:
    _zesSysmanFirmwareGetChecksum_t = WINFUNCTYPE( ze_result_t, zes_sysman_firmware_handle_t, POINTER(c_ulong) )
else:
    _zesSysmanFirmwareGetChecksum_t = CFUNCTYPE( ze_result_t, zes_sysman_firmware_handle_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for zesSysmanFirmwareFlash
if __use_win_types:
    _zesSysmanFirmwareFlash_t = WINFUNCTYPE( ze_result_t, zes_sysman_firmware_handle_t, c_void_p, c_ulong )
else:
    _zesSysmanFirmwareFlash_t = CFUNCTYPE( ze_result_t, zes_sysman_firmware_handle_t, c_void_p, c_ulong )


###############################################################################
## @brief Table of SysmanFirmware functions pointers
class _zes_sysman_firmware_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanFirmwareGetProperties_t
        ("pfnGetChecksum", c_void_p),                                   ## _zesSysmanFirmwareGetChecksum_t
        ("pfnFlash", c_void_p)                                          ## _zesSysmanFirmwareFlash_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanMemoryGetProperties
if __use_win_types:
    _zesSysmanMemoryGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_mem_handle_t, POINTER(zes_mem_properties_t) )
else:
    _zesSysmanMemoryGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_mem_handle_t, POINTER(zes_mem_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanMemoryGetState
if __use_win_types:
    _zesSysmanMemoryGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_mem_handle_t, POINTER(zes_mem_state_t) )
else:
    _zesSysmanMemoryGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_mem_handle_t, POINTER(zes_mem_state_t) )

###############################################################################
## @brief Function-pointer for zesSysmanMemoryGetBandwidth
if __use_win_types:
    _zesSysmanMemoryGetBandwidth_t = WINFUNCTYPE( ze_result_t, zes_sysman_mem_handle_t, POINTER(zes_mem_bandwidth_t) )
else:
    _zesSysmanMemoryGetBandwidth_t = CFUNCTYPE( ze_result_t, zes_sysman_mem_handle_t, POINTER(zes_mem_bandwidth_t) )


###############################################################################
## @brief Table of SysmanMemory functions pointers
class _zes_sysman_memory_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanMemoryGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _zesSysmanMemoryGetState_t
        ("pfnGetBandwidth", c_void_p)                                   ## _zesSysmanMemoryGetBandwidth_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanFabricPortGetProperties
if __use_win_types:
    _zesSysmanFabricPortGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, POINTER(zes_fabric_port_properties_t) )
else:
    _zesSysmanFabricPortGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, POINTER(zes_fabric_port_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFabricPortGetLinkType
if __use_win_types:
    _zesSysmanFabricPortGetLinkType_t = WINFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, ze_bool_t, POINTER(zes_fabric_link_type_t) )
else:
    _zesSysmanFabricPortGetLinkType_t = CFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, ze_bool_t, POINTER(zes_fabric_link_type_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFabricPortGetConfig
if __use_win_types:
    _zesSysmanFabricPortGetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, POINTER(zes_fabric_port_config_t) )
else:
    _zesSysmanFabricPortGetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, POINTER(zes_fabric_port_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFabricPortSetConfig
if __use_win_types:
    _zesSysmanFabricPortSetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, POINTER(zes_fabric_port_config_t) )
else:
    _zesSysmanFabricPortSetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, POINTER(zes_fabric_port_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFabricPortGetState
if __use_win_types:
    _zesSysmanFabricPortGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, POINTER(zes_fabric_port_state_t) )
else:
    _zesSysmanFabricPortGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, POINTER(zes_fabric_port_state_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFabricPortGetThroughput
if __use_win_types:
    _zesSysmanFabricPortGetThroughput_t = WINFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, POINTER(zes_fabric_port_throughput_t) )
else:
    _zesSysmanFabricPortGetThroughput_t = CFUNCTYPE( ze_result_t, zes_sysman_fabric_port_handle_t, POINTER(zes_fabric_port_throughput_t) )


###############################################################################
## @brief Table of SysmanFabricPort functions pointers
class _zes_sysman_fabric_port_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanFabricPortGetProperties_t
        ("pfnGetLinkType", c_void_p),                                   ## _zesSysmanFabricPortGetLinkType_t
        ("pfnGetConfig", c_void_p),                                     ## _zesSysmanFabricPortGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zesSysmanFabricPortSetConfig_t
        ("pfnGetState", c_void_p),                                      ## _zesSysmanFabricPortGetState_t
        ("pfnGetThroughput", c_void_p)                                  ## _zesSysmanFabricPortGetThroughput_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanTemperatureGetProperties
if __use_win_types:
    _zesSysmanTemperatureGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_temp_handle_t, POINTER(zes_temp_properties_t) )
else:
    _zesSysmanTemperatureGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_temp_handle_t, POINTER(zes_temp_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanTemperatureGetConfig
if __use_win_types:
    _zesSysmanTemperatureGetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_temp_handle_t, POINTER(zes_temp_config_t) )
else:
    _zesSysmanTemperatureGetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_temp_handle_t, POINTER(zes_temp_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanTemperatureSetConfig
if __use_win_types:
    _zesSysmanTemperatureSetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_temp_handle_t, POINTER(zes_temp_config_t) )
else:
    _zesSysmanTemperatureSetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_temp_handle_t, POINTER(zes_temp_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanTemperatureGetState
if __use_win_types:
    _zesSysmanTemperatureGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_temp_handle_t, POINTER(c_double) )
else:
    _zesSysmanTemperatureGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_temp_handle_t, POINTER(c_double) )


###############################################################################
## @brief Table of SysmanTemperature functions pointers
class _zes_sysman_temperature_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanTemperatureGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zesSysmanTemperatureGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zesSysmanTemperatureSetConfig_t
        ("pfnGetState", c_void_p)                                       ## _zesSysmanTemperatureGetState_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanPsuGetProperties
if __use_win_types:
    _zesSysmanPsuGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_psu_handle_t, POINTER(zes_psu_properties_t) )
else:
    _zesSysmanPsuGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_psu_handle_t, POINTER(zes_psu_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanPsuGetState
if __use_win_types:
    _zesSysmanPsuGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_psu_handle_t, POINTER(zes_psu_state_t) )
else:
    _zesSysmanPsuGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_psu_handle_t, POINTER(zes_psu_state_t) )


###############################################################################
## @brief Table of SysmanPsu functions pointers
class _zes_sysman_psu_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanPsuGetProperties_t
        ("pfnGetState", c_void_p)                                       ## _zesSysmanPsuGetState_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanFanGetProperties
if __use_win_types:
    _zesSysmanFanGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_fan_handle_t, POINTER(zes_fan_properties_t) )
else:
    _zesSysmanFanGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_fan_handle_t, POINTER(zes_fan_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFanGetConfig
if __use_win_types:
    _zesSysmanFanGetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_fan_handle_t, POINTER(zes_fan_config_t) )
else:
    _zesSysmanFanGetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_fan_handle_t, POINTER(zes_fan_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFanSetConfig
if __use_win_types:
    _zesSysmanFanSetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_fan_handle_t, POINTER(zes_fan_config_t) )
else:
    _zesSysmanFanSetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_fan_handle_t, POINTER(zes_fan_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanFanGetState
if __use_win_types:
    _zesSysmanFanGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_fan_handle_t, zes_fan_speed_units_t, POINTER(c_ulong) )
else:
    _zesSysmanFanGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_fan_handle_t, zes_fan_speed_units_t, POINTER(c_ulong) )


###############################################################################
## @brief Table of SysmanFan functions pointers
class _zes_sysman_fan_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanFanGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zesSysmanFanGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zesSysmanFanSetConfig_t
        ("pfnGetState", c_void_p)                                       ## _zesSysmanFanGetState_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanLedGetProperties
if __use_win_types:
    _zesSysmanLedGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_led_handle_t, POINTER(zes_led_properties_t) )
else:
    _zesSysmanLedGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_led_handle_t, POINTER(zes_led_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanLedGetState
if __use_win_types:
    _zesSysmanLedGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_led_handle_t, POINTER(zes_led_state_t) )
else:
    _zesSysmanLedGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_led_handle_t, POINTER(zes_led_state_t) )

###############################################################################
## @brief Function-pointer for zesSysmanLedSetState
if __use_win_types:
    _zesSysmanLedSetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_led_handle_t, POINTER(zes_led_state_t) )
else:
    _zesSysmanLedSetState_t = CFUNCTYPE( ze_result_t, zes_sysman_led_handle_t, POINTER(zes_led_state_t) )


###############################################################################
## @brief Table of SysmanLed functions pointers
class _zes_sysman_led_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanLedGetProperties_t
        ("pfnGetState", c_void_p),                                      ## _zesSysmanLedGetState_t
        ("pfnSetState", c_void_p)                                       ## _zesSysmanLedSetState_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanRasGetProperties
if __use_win_types:
    _zesSysmanRasGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_ras_handle_t, POINTER(zes_ras_properties_t) )
else:
    _zesSysmanRasGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_ras_handle_t, POINTER(zes_ras_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanRasGetConfig
if __use_win_types:
    _zesSysmanRasGetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_ras_handle_t, POINTER(zes_ras_config_t) )
else:
    _zesSysmanRasGetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_ras_handle_t, POINTER(zes_ras_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanRasSetConfig
if __use_win_types:
    _zesSysmanRasSetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_ras_handle_t, POINTER(zes_ras_config_t) )
else:
    _zesSysmanRasSetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_ras_handle_t, POINTER(zes_ras_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanRasGetState
if __use_win_types:
    _zesSysmanRasGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_ras_handle_t, ze_bool_t, POINTER(c_ulonglong), POINTER(zes_ras_details_t) )
else:
    _zesSysmanRasGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_ras_handle_t, ze_bool_t, POINTER(c_ulonglong), POINTER(zes_ras_details_t) )


###############################################################################
## @brief Table of SysmanRas functions pointers
class _zes_sysman_ras_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanRasGetProperties_t
        ("pfnGetConfig", c_void_p),                                     ## _zesSysmanRasGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zesSysmanRasSetConfig_t
        ("pfnGetState", c_void_p)                                       ## _zesSysmanRasGetState_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanDiagnosticsGetProperties
if __use_win_types:
    _zesSysmanDiagnosticsGetProperties_t = WINFUNCTYPE( ze_result_t, zes_sysman_diag_handle_t, POINTER(zes_diag_properties_t) )
else:
    _zesSysmanDiagnosticsGetProperties_t = CFUNCTYPE( ze_result_t, zes_sysman_diag_handle_t, POINTER(zes_diag_properties_t) )

###############################################################################
## @brief Function-pointer for zesSysmanDiagnosticsGetTests
if __use_win_types:
    _zesSysmanDiagnosticsGetTests_t = WINFUNCTYPE( ze_result_t, zes_sysman_diag_handle_t, POINTER(c_ulong), POINTER(zes_diag_test_t) )
else:
    _zesSysmanDiagnosticsGetTests_t = CFUNCTYPE( ze_result_t, zes_sysman_diag_handle_t, POINTER(c_ulong), POINTER(zes_diag_test_t) )

###############################################################################
## @brief Function-pointer for zesSysmanDiagnosticsRunTests
if __use_win_types:
    _zesSysmanDiagnosticsRunTests_t = WINFUNCTYPE( ze_result_t, zes_sysman_diag_handle_t, c_ulong, c_ulong, POINTER(zes_diag_result_t) )
else:
    _zesSysmanDiagnosticsRunTests_t = CFUNCTYPE( ze_result_t, zes_sysman_diag_handle_t, c_ulong, c_ulong, POINTER(zes_diag_result_t) )


###############################################################################
## @brief Table of SysmanDiagnostics functions pointers
class _zes_sysman_diagnostics_dditable_t(Structure):
    _fields_ = [
        ("pfnGetProperties", c_void_p),                                 ## _zesSysmanDiagnosticsGetProperties_t
        ("pfnGetTests", c_void_p),                                      ## _zesSysmanDiagnosticsGetTests_t
        ("pfnRunTests", c_void_p)                                       ## _zesSysmanDiagnosticsRunTests_t
    ]

###############################################################################
## @brief Function-pointer for zesSysmanEventGetConfig
if __use_win_types:
    _zesSysmanEventGetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_event_handle_t, POINTER(zes_event_config_t) )
else:
    _zesSysmanEventGetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_event_handle_t, POINTER(zes_event_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanEventSetConfig
if __use_win_types:
    _zesSysmanEventSetConfig_t = WINFUNCTYPE( ze_result_t, zes_sysman_event_handle_t, POINTER(zes_event_config_t) )
else:
    _zesSysmanEventSetConfig_t = CFUNCTYPE( ze_result_t, zes_sysman_event_handle_t, POINTER(zes_event_config_t) )

###############################################################################
## @brief Function-pointer for zesSysmanEventGetState
if __use_win_types:
    _zesSysmanEventGetState_t = WINFUNCTYPE( ze_result_t, zes_sysman_event_handle_t, ze_bool_t, POINTER(c_ulong) )
else:
    _zesSysmanEventGetState_t = CFUNCTYPE( ze_result_t, zes_sysman_event_handle_t, ze_bool_t, POINTER(c_ulong) )

###############################################################################
## @brief Function-pointer for zesSysmanEventListen
if __use_win_types:
    _zesSysmanEventListen_t = WINFUNCTYPE( ze_result_t, ze_driver_handle_t, c_ulong, c_ulong, POINTER(zes_sysman_event_handle_t), POINTER(c_ulong) )
else:
    _zesSysmanEventListen_t = CFUNCTYPE( ze_result_t, ze_driver_handle_t, c_ulong, c_ulong, POINTER(zes_sysman_event_handle_t), POINTER(c_ulong) )


###############################################################################
## @brief Table of SysmanEvent functions pointers
class _zes_sysman_event_dditable_t(Structure):
    _fields_ = [
        ("pfnGetConfig", c_void_p),                                     ## _zesSysmanEventGetConfig_t
        ("pfnSetConfig", c_void_p),                                     ## _zesSysmanEventSetConfig_t
        ("pfnGetState", c_void_p),                                      ## _zesSysmanEventGetState_t
        ("pfnListen", c_void_p)                                         ## _zesSysmanEventListen_t
    ]

###############################################################################
class _zes_dditable_t(Structure):
    _fields_ = [
        ("Sysman", _zes_sysman_dditable_t),
        ("SysmanScheduler", _zes_sysman_scheduler_dditable_t),
        ("SysmanPerformanceFactor", _zes_sysman_performance_factor_dditable_t),
        ("SysmanPower", _zes_sysman_power_dditable_t),
        ("SysmanFrequency", _zes_sysman_frequency_dditable_t),
        ("SysmanEngine", _zes_sysman_engine_dditable_t),
        ("SysmanStandby", _zes_sysman_standby_dditable_t),
        ("SysmanFirmware", _zes_sysman_firmware_dditable_t),
        ("SysmanMemory", _zes_sysman_memory_dditable_t),
        ("SysmanFabricPort", _zes_sysman_fabric_port_dditable_t),
        ("SysmanTemperature", _zes_sysman_temperature_dditable_t),
        ("SysmanPsu", _zes_sysman_psu_dditable_t),
        ("SysmanFan", _zes_sysman_fan_dditable_t),
        ("SysmanLed", _zes_sysman_led_dditable_t),
        ("SysmanRas", _zes_sysman_ras_dditable_t),
        ("SysmanDiagnostics", _zes_sysman_diagnostics_dditable_t),
        ("SysmanEvent", _zes_sysman_event_dditable_t)
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
        _Sysman = _zes_sysman_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanProcAddrTable(version, byref(_Sysman)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Sysman = _Sysman

        # attach function interface to function address
        self.zesSysmanGet = _zesSysmanGet_t(self.__dditable.Sysman.pfnGet)
        self.zesSysmanDeviceGetProperties = _zesSysmanDeviceGetProperties_t(self.__dditable.Sysman.pfnDeviceGetProperties)
        self.zesSysmanDeviceGetState = _zesSysmanDeviceGetState_t(self.__dditable.Sysman.pfnDeviceGetState)
        self.zesSysmanDeviceReset = _zesSysmanDeviceReset_t(self.__dditable.Sysman.pfnDeviceReset)
        self.zesSysmanSchedulerGet = _zesSysmanSchedulerGet_t(self.__dditable.Sysman.pfnSchedulerGet)
        self.zesSysmanPerformanceFactorGet = _zesSysmanPerformanceFactorGet_t(self.__dditable.Sysman.pfnPerformanceFactorGet)
        self.zesSysmanProcessesGetState = _zesSysmanProcessesGetState_t(self.__dditable.Sysman.pfnProcessesGetState)
        self.zesSysmanPciGetProperties = _zesSysmanPciGetProperties_t(self.__dditable.Sysman.pfnPciGetProperties)
        self.zesSysmanPciGetState = _zesSysmanPciGetState_t(self.__dditable.Sysman.pfnPciGetState)
        self.zesSysmanPciGetBars = _zesSysmanPciGetBars_t(self.__dditable.Sysman.pfnPciGetBars)
        self.zesSysmanPciGetStats = _zesSysmanPciGetStats_t(self.__dditable.Sysman.pfnPciGetStats)
        self.zesSysmanPowerGet = _zesSysmanPowerGet_t(self.__dditable.Sysman.pfnPowerGet)
        self.zesSysmanFrequencyGet = _zesSysmanFrequencyGet_t(self.__dditable.Sysman.pfnFrequencyGet)
        self.zesSysmanEngineGet = _zesSysmanEngineGet_t(self.__dditable.Sysman.pfnEngineGet)
        self.zesSysmanStandbyGet = _zesSysmanStandbyGet_t(self.__dditable.Sysman.pfnStandbyGet)
        self.zesSysmanFirmwareGet = _zesSysmanFirmwareGet_t(self.__dditable.Sysman.pfnFirmwareGet)
        self.zesSysmanMemoryGet = _zesSysmanMemoryGet_t(self.__dditable.Sysman.pfnMemoryGet)
        self.zesSysmanFabricPortGet = _zesSysmanFabricPortGet_t(self.__dditable.Sysman.pfnFabricPortGet)
        self.zesSysmanTemperatureGet = _zesSysmanTemperatureGet_t(self.__dditable.Sysman.pfnTemperatureGet)
        self.zesSysmanPsuGet = _zesSysmanPsuGet_t(self.__dditable.Sysman.pfnPsuGet)
        self.zesSysmanFanGet = _zesSysmanFanGet_t(self.__dditable.Sysman.pfnFanGet)
        self.zesSysmanLedGet = _zesSysmanLedGet_t(self.__dditable.Sysman.pfnLedGet)
        self.zesSysmanRasGet = _zesSysmanRasGet_t(self.__dditable.Sysman.pfnRasGet)
        self.zesSysmanEventGet = _zesSysmanEventGet_t(self.__dditable.Sysman.pfnEventGet)
        self.zesSysmanDiagnosticsGet = _zesSysmanDiagnosticsGet_t(self.__dditable.Sysman.pfnDiagnosticsGet)

        # call driver to get function pointers
        _SysmanScheduler = _zes_sysman_scheduler_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanSchedulerProcAddrTable(version, byref(_SysmanScheduler)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanScheduler = _SysmanScheduler

        # attach function interface to function address
        self.zesSysmanSchedulerGetProperties = _zesSysmanSchedulerGetProperties_t(self.__dditable.SysmanScheduler.pfnGetProperties)
        self.zesSysmanSchedulerGetCurrentMode = _zesSysmanSchedulerGetCurrentMode_t(self.__dditable.SysmanScheduler.pfnGetCurrentMode)
        self.zesSysmanSchedulerGetTimeoutModeProperties = _zesSysmanSchedulerGetTimeoutModeProperties_t(self.__dditable.SysmanScheduler.pfnGetTimeoutModeProperties)
        self.zesSysmanSchedulerGetTimesliceModeProperties = _zesSysmanSchedulerGetTimesliceModeProperties_t(self.__dditable.SysmanScheduler.pfnGetTimesliceModeProperties)
        self.zesSysmanSchedulerSetTimeoutMode = _zesSysmanSchedulerSetTimeoutMode_t(self.__dditable.SysmanScheduler.pfnSetTimeoutMode)
        self.zesSysmanSchedulerSetTimesliceMode = _zesSysmanSchedulerSetTimesliceMode_t(self.__dditable.SysmanScheduler.pfnSetTimesliceMode)
        self.zesSysmanSchedulerSetExclusiveMode = _zesSysmanSchedulerSetExclusiveMode_t(self.__dditable.SysmanScheduler.pfnSetExclusiveMode)
        self.zesSysmanSchedulerSetComputeUnitDebugMode = _zesSysmanSchedulerSetComputeUnitDebugMode_t(self.__dditable.SysmanScheduler.pfnSetComputeUnitDebugMode)

        # call driver to get function pointers
        _SysmanPerformanceFactor = _zes_sysman_performance_factor_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanPerformanceFactorProcAddrTable(version, byref(_SysmanPerformanceFactor)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanPerformanceFactor = _SysmanPerformanceFactor

        # attach function interface to function address
        self.zesSysmanPerformanceFactorGetProperties = _zesSysmanPerformanceFactorGetProperties_t(self.__dditable.SysmanPerformanceFactor.pfnGetProperties)
        self.zesSysmanPerformanceFactorGetConfig = _zesSysmanPerformanceFactorGetConfig_t(self.__dditable.SysmanPerformanceFactor.pfnGetConfig)
        self.zesSysmanPerformanceFactorSetConfig = _zesSysmanPerformanceFactorSetConfig_t(self.__dditable.SysmanPerformanceFactor.pfnSetConfig)

        # call driver to get function pointers
        _SysmanPower = _zes_sysman_power_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanPowerProcAddrTable(version, byref(_SysmanPower)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanPower = _SysmanPower

        # attach function interface to function address
        self.zesSysmanPowerGetProperties = _zesSysmanPowerGetProperties_t(self.__dditable.SysmanPower.pfnGetProperties)
        self.zesSysmanPowerGetEnergyCounter = _zesSysmanPowerGetEnergyCounter_t(self.__dditable.SysmanPower.pfnGetEnergyCounter)
        self.zesSysmanPowerGetLimits = _zesSysmanPowerGetLimits_t(self.__dditable.SysmanPower.pfnGetLimits)
        self.zesSysmanPowerSetLimits = _zesSysmanPowerSetLimits_t(self.__dditable.SysmanPower.pfnSetLimits)
        self.zesSysmanPowerGetEnergyThreshold = _zesSysmanPowerGetEnergyThreshold_t(self.__dditable.SysmanPower.pfnGetEnergyThreshold)
        self.zesSysmanPowerSetEnergyThreshold = _zesSysmanPowerSetEnergyThreshold_t(self.__dditable.SysmanPower.pfnSetEnergyThreshold)

        # call driver to get function pointers
        _SysmanFrequency = _zes_sysman_frequency_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanFrequencyProcAddrTable(version, byref(_SysmanFrequency)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFrequency = _SysmanFrequency

        # attach function interface to function address
        self.zesSysmanFrequencyGetProperties = _zesSysmanFrequencyGetProperties_t(self.__dditable.SysmanFrequency.pfnGetProperties)
        self.zesSysmanFrequencyGetAvailableClocks = _zesSysmanFrequencyGetAvailableClocks_t(self.__dditable.SysmanFrequency.pfnGetAvailableClocks)
        self.zesSysmanFrequencyGetRange = _zesSysmanFrequencyGetRange_t(self.__dditable.SysmanFrequency.pfnGetRange)
        self.zesSysmanFrequencySetRange = _zesSysmanFrequencySetRange_t(self.__dditable.SysmanFrequency.pfnSetRange)
        self.zesSysmanFrequencyGetState = _zesSysmanFrequencyGetState_t(self.__dditable.SysmanFrequency.pfnGetState)
        self.zesSysmanFrequencyGetThrottleTime = _zesSysmanFrequencyGetThrottleTime_t(self.__dditable.SysmanFrequency.pfnGetThrottleTime)
        self.zesSysmanFrequencyOcGetCapabilities = _zesSysmanFrequencyOcGetCapabilities_t(self.__dditable.SysmanFrequency.pfnOcGetCapabilities)
        self.zesSysmanFrequencyOcGetConfig = _zesSysmanFrequencyOcGetConfig_t(self.__dditable.SysmanFrequency.pfnOcGetConfig)
        self.zesSysmanFrequencyOcSetConfig = _zesSysmanFrequencyOcSetConfig_t(self.__dditable.SysmanFrequency.pfnOcSetConfig)
        self.zesSysmanFrequencyOcGetIccMax = _zesSysmanFrequencyOcGetIccMax_t(self.__dditable.SysmanFrequency.pfnOcGetIccMax)
        self.zesSysmanFrequencyOcSetIccMax = _zesSysmanFrequencyOcSetIccMax_t(self.__dditable.SysmanFrequency.pfnOcSetIccMax)
        self.zesSysmanFrequencyOcGetTjMax = _zesSysmanFrequencyOcGetTjMax_t(self.__dditable.SysmanFrequency.pfnOcGetTjMax)
        self.zesSysmanFrequencyOcSetTjMax = _zesSysmanFrequencyOcSetTjMax_t(self.__dditable.SysmanFrequency.pfnOcSetTjMax)

        # call driver to get function pointers
        _SysmanEngine = _zes_sysman_engine_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanEngineProcAddrTable(version, byref(_SysmanEngine)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanEngine = _SysmanEngine

        # attach function interface to function address
        self.zesSysmanEngineGetProperties = _zesSysmanEngineGetProperties_t(self.__dditable.SysmanEngine.pfnGetProperties)
        self.zesSysmanEngineGetActivity = _zesSysmanEngineGetActivity_t(self.__dditable.SysmanEngine.pfnGetActivity)

        # call driver to get function pointers
        _SysmanStandby = _zes_sysman_standby_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanStandbyProcAddrTable(version, byref(_SysmanStandby)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanStandby = _SysmanStandby

        # attach function interface to function address
        self.zesSysmanStandbyGetProperties = _zesSysmanStandbyGetProperties_t(self.__dditable.SysmanStandby.pfnGetProperties)
        self.zesSysmanStandbyGetMode = _zesSysmanStandbyGetMode_t(self.__dditable.SysmanStandby.pfnGetMode)
        self.zesSysmanStandbySetMode = _zesSysmanStandbySetMode_t(self.__dditable.SysmanStandby.pfnSetMode)

        # call driver to get function pointers
        _SysmanFirmware = _zes_sysman_firmware_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanFirmwareProcAddrTable(version, byref(_SysmanFirmware)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFirmware = _SysmanFirmware

        # attach function interface to function address
        self.zesSysmanFirmwareGetProperties = _zesSysmanFirmwareGetProperties_t(self.__dditable.SysmanFirmware.pfnGetProperties)
        self.zesSysmanFirmwareGetChecksum = _zesSysmanFirmwareGetChecksum_t(self.__dditable.SysmanFirmware.pfnGetChecksum)
        self.zesSysmanFirmwareFlash = _zesSysmanFirmwareFlash_t(self.__dditable.SysmanFirmware.pfnFlash)

        # call driver to get function pointers
        _SysmanMemory = _zes_sysman_memory_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanMemoryProcAddrTable(version, byref(_SysmanMemory)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanMemory = _SysmanMemory

        # attach function interface to function address
        self.zesSysmanMemoryGetProperties = _zesSysmanMemoryGetProperties_t(self.__dditable.SysmanMemory.pfnGetProperties)
        self.zesSysmanMemoryGetState = _zesSysmanMemoryGetState_t(self.__dditable.SysmanMemory.pfnGetState)
        self.zesSysmanMemoryGetBandwidth = _zesSysmanMemoryGetBandwidth_t(self.__dditable.SysmanMemory.pfnGetBandwidth)

        # call driver to get function pointers
        _SysmanFabricPort = _zes_sysman_fabric_port_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanFabricPortProcAddrTable(version, byref(_SysmanFabricPort)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFabricPort = _SysmanFabricPort

        # attach function interface to function address
        self.zesSysmanFabricPortGetProperties = _zesSysmanFabricPortGetProperties_t(self.__dditable.SysmanFabricPort.pfnGetProperties)
        self.zesSysmanFabricPortGetLinkType = _zesSysmanFabricPortGetLinkType_t(self.__dditable.SysmanFabricPort.pfnGetLinkType)
        self.zesSysmanFabricPortGetConfig = _zesSysmanFabricPortGetConfig_t(self.__dditable.SysmanFabricPort.pfnGetConfig)
        self.zesSysmanFabricPortSetConfig = _zesSysmanFabricPortSetConfig_t(self.__dditable.SysmanFabricPort.pfnSetConfig)
        self.zesSysmanFabricPortGetState = _zesSysmanFabricPortGetState_t(self.__dditable.SysmanFabricPort.pfnGetState)
        self.zesSysmanFabricPortGetThroughput = _zesSysmanFabricPortGetThroughput_t(self.__dditable.SysmanFabricPort.pfnGetThroughput)

        # call driver to get function pointers
        _SysmanTemperature = _zes_sysman_temperature_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanTemperatureProcAddrTable(version, byref(_SysmanTemperature)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanTemperature = _SysmanTemperature

        # attach function interface to function address
        self.zesSysmanTemperatureGetProperties = _zesSysmanTemperatureGetProperties_t(self.__dditable.SysmanTemperature.pfnGetProperties)
        self.zesSysmanTemperatureGetConfig = _zesSysmanTemperatureGetConfig_t(self.__dditable.SysmanTemperature.pfnGetConfig)
        self.zesSysmanTemperatureSetConfig = _zesSysmanTemperatureSetConfig_t(self.__dditable.SysmanTemperature.pfnSetConfig)
        self.zesSysmanTemperatureGetState = _zesSysmanTemperatureGetState_t(self.__dditable.SysmanTemperature.pfnGetState)

        # call driver to get function pointers
        _SysmanPsu = _zes_sysman_psu_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanPsuProcAddrTable(version, byref(_SysmanPsu)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanPsu = _SysmanPsu

        # attach function interface to function address
        self.zesSysmanPsuGetProperties = _zesSysmanPsuGetProperties_t(self.__dditable.SysmanPsu.pfnGetProperties)
        self.zesSysmanPsuGetState = _zesSysmanPsuGetState_t(self.__dditable.SysmanPsu.pfnGetState)

        # call driver to get function pointers
        _SysmanFan = _zes_sysman_fan_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanFanProcAddrTable(version, byref(_SysmanFan)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanFan = _SysmanFan

        # attach function interface to function address
        self.zesSysmanFanGetProperties = _zesSysmanFanGetProperties_t(self.__dditable.SysmanFan.pfnGetProperties)
        self.zesSysmanFanGetConfig = _zesSysmanFanGetConfig_t(self.__dditable.SysmanFan.pfnGetConfig)
        self.zesSysmanFanSetConfig = _zesSysmanFanSetConfig_t(self.__dditable.SysmanFan.pfnSetConfig)
        self.zesSysmanFanGetState = _zesSysmanFanGetState_t(self.__dditable.SysmanFan.pfnGetState)

        # call driver to get function pointers
        _SysmanLed = _zes_sysman_led_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanLedProcAddrTable(version, byref(_SysmanLed)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanLed = _SysmanLed

        # attach function interface to function address
        self.zesSysmanLedGetProperties = _zesSysmanLedGetProperties_t(self.__dditable.SysmanLed.pfnGetProperties)
        self.zesSysmanLedGetState = _zesSysmanLedGetState_t(self.__dditable.SysmanLed.pfnGetState)
        self.zesSysmanLedSetState = _zesSysmanLedSetState_t(self.__dditable.SysmanLed.pfnSetState)

        # call driver to get function pointers
        _SysmanRas = _zes_sysman_ras_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanRasProcAddrTable(version, byref(_SysmanRas)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanRas = _SysmanRas

        # attach function interface to function address
        self.zesSysmanRasGetProperties = _zesSysmanRasGetProperties_t(self.__dditable.SysmanRas.pfnGetProperties)
        self.zesSysmanRasGetConfig = _zesSysmanRasGetConfig_t(self.__dditable.SysmanRas.pfnGetConfig)
        self.zesSysmanRasSetConfig = _zesSysmanRasSetConfig_t(self.__dditable.SysmanRas.pfnSetConfig)
        self.zesSysmanRasGetState = _zesSysmanRasGetState_t(self.__dditable.SysmanRas.pfnGetState)

        # call driver to get function pointers
        _SysmanDiagnostics = _zes_sysman_diagnostics_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanDiagnosticsProcAddrTable(version, byref(_SysmanDiagnostics)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanDiagnostics = _SysmanDiagnostics

        # attach function interface to function address
        self.zesSysmanDiagnosticsGetProperties = _zesSysmanDiagnosticsGetProperties_t(self.__dditable.SysmanDiagnostics.pfnGetProperties)
        self.zesSysmanDiagnosticsGetTests = _zesSysmanDiagnosticsGetTests_t(self.__dditable.SysmanDiagnostics.pfnGetTests)
        self.zesSysmanDiagnosticsRunTests = _zesSysmanDiagnosticsRunTests_t(self.__dditable.SysmanDiagnostics.pfnRunTests)

        # call driver to get function pointers
        _SysmanEvent = _zes_sysman_event_dditable_t()
        r = ze_result_v(self.__dll.zesGetSysmanEventProcAddrTable(version, byref(_SysmanEvent)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.SysmanEvent = _SysmanEvent

        # attach function interface to function address
        self.zesSysmanEventGetConfig = _zesSysmanEventGetConfig_t(self.__dditable.SysmanEvent.pfnGetConfig)
        self.zesSysmanEventSetConfig = _zesSysmanEventSetConfig_t(self.__dditable.SysmanEvent.pfnSetConfig)
        self.zesSysmanEventGetState = _zesSysmanEventGetState_t(self.__dditable.SysmanEvent.pfnGetState)
        self.zesSysmanEventListen = _zesSysmanEventListen_t(self.__dditable.SysmanEvent.pfnListen)

        # success!
