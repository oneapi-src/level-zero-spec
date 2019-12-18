# Programming Guide (Sysman)


[DO NOT EDIT]: # "generated from /scripts/tools/SYSMAN.md"

The following documents the high-level programming models and guidelines.


## Table of Contents
* [Introduction](#in)
* [High-level overview](#ho)
    + [Initialization](#ini)
    + [Global device management](#gdm)
    + [Device component management](#dcm)
    + [Device component enumeration](#dce)
    + [Sub-device management](#sdm)
    + [Events](#evt)
* [Interface details](#id)
    + [Global operations](#glo)
        + [Device properties](#glod)
        + [Host processes](#gloz)
        + [Scheduler operations](#glos)
        + [Performance profiles](#glox)
        + [Device reset](#glor)
        + [PCI link operations](#glop)
    + [Operations on power domains](#pwr)
	+ [Operations on frequency domains](#frq)
        + [Frequency/Voltage over-clocking](#fro)
	+ [Operations on engine groups](#eng)
	+ [Operations on standby domains](#sby)
	+ [Operations on firmware](#fmw)
	+ [Querying memory modules](#mem)
	+ [Operations on fabric ports](#con)
	+ [Querying temperature](#tmp)
	+ [Operations on power supplies](#psu)
	+ [Operations on fans](#fan)
	+ [Operations on LEDs](#led)
	+ [Querying RAS errors](#ras)
	+ [Performing diagnostics](#dag)
    + [Events](#evd)
* [Security](#se)
    + [Linux](#sel)
    + [Windows](#sew)
    + [Privileged telemetry](#set)
    + [Privileged controls](#sec)
    + [Virtualization](#sev)
    + [Function summary](#sef)


# <a name="in">Introduction</a>
Sysman is the System Resource Management library used to monitor and control the power and performance of accelerator devices.

# <a name="ho">High-level overview</a>

## <a name="ini">Initialization</a>
An application wishing to manage power and performance for devices first needs to use the Level0 Core API to enumerate through available accelerator
devices in the system and select those of interest.

For each selected device handle, applications use the function ::zetSysmanGet() to get an **Sysman handle** to manage system resources of the device.

![Object hierarchy](../images/tools_sysman_object_hierarchy.png?raw=true) 

There is a unique handle for each device. Multiple threads can use the handle. If concurrent accesses are made to the same device property through
the handle, the last request wins.

The pseudo code below shows how to enumerate the GPU devices in the system and create Sysman handles for them:

```c
function main( ... )
    if ( (zeInit(ZE_INIT_FLAG_NONE) != ZE_RESULT_SUCCESS) or
         (zetInit(ZE_INIT_FLAG_NONE) != ZE_RESULT_SUCCESS) )
        output("Can't initialize the API")
    else
        # Discover all the drivers
        uint32_t driversCount = 0
        zeDriverGet(&driversCount, nullptr)
        ze_driver_handle_t* allDrivers =
            allocate(driversCount * sizeof(ze_driver_handle_t))
        zeDriverGet(&driversCount, allDrivers)

        ze_driver_handle_t hDriver = nullptr
        for(i = 0 .. driversCount-1)
            # Discover devices in a driver
            uint32_t deviceCount = 0
            zeDeviceGet(allDrivers[i], &deviceCount, nullptr)

            ze_device_handle_t* allDevices = 
                allocate_memory(deviceCount * sizeof(ze_device_handle_t))
            zeDeviceGet(allDrivers[i], &deviceCount, allDevices)

            for(devIndex = 0 .. deviceCount-1)
                ze_device_properties_t device_properties
                zeDeviceGetProperties(allDevices[devIndex], &device_properties)
                if(ZE_DEVICE_TYPE_GPU != device_properties.type)
				    next
				# Create Sysman handle
				zet_sysman_handle_t hSysmanDevice
				ze_result_t res = zetSysmanGet(hDevice, ZET_SYSMAN_VERSION_CURRENT, &hSysmanDevice)
				if (res == ZE_RESULT_SUCCESS)
					# Start using hSysmanDevice to manage the device
				else
					output("ERROR: Can't initialize system resource management for this device")

    free_memory(...)

```

## <a name="gdm">Global device management</a>
The following operations are provided to access overall device information and control aspects of the entire device:

- Get device UUID, deviceID, number of sub-devices
- Get Brand/model/vendor name
- Query the information about processes using this device
- Get/set scheduler mode and properties
- Get/set performance profiles
- Reset device
- Query if the device has been repaired
- PCI information:
    - Get configured bars
    - Get maximum supported bandwidth
    - Query current speed (GEN/no. lanes)
	- Query current health
    - Query current throughput
    - Query packet retry counters

The full list of available functions is described [below](#glo).

## <a name="dcm">Device component management</a>
Aside from management of the global properties of a device, there are many device components that can be managed to change the performance and/or power
configuration of the device. Similar components are broken into **classes** and each class has a set of operations that can be performed on them.

For example, devices typically have one or more frequency domains. The Sysman API exposes a class for frequency and an enumeration of all frequency domains
that can be managed.

The table below summarizes the classes that provide device queries and an example list of components that would be enumerated for a device with two
sub-devices. The table shows the operations (queries) that will be provided for all components in each class.

| Class                 | Components    | Operations |
| :---                  | :---          | :---        |
| [Power](#pwr)         | Package: power<br />Sub-device 0: Total power<br />Sub-device 1: Total power | Get energy consumption |
| [Frequency](#frq)     | Sub-device 0: GPU frequency<br />Sub-device 0: Memory frequency<br />Sub-device 1: GPU frequency<br />Sub-device 1: Memory frequency | List available frequencies<br />Set frequency range<br />Get frequencies<br />Get throttle reasons<br />Get throttle time |
| [Engines](#eng)       | Sub-device 0: All engines<br />Sub-device 0: Compute engines<br />Sub-device 0: Media engines<br />Sub-device 1: All engines<br />Sub-device 1: Compute engines<br />Sub-device 1: Media engines | Get busy time |
| [Firmware](#fmw)      | Sub-device 0: Enumerates each firmware<br />Sub-device 1: Enumerates each firmware | Get firmware  name and version<br />Verify firmware checksum |
| [Memory](#mem)        | Sub-device 0: Memory module<br />Sub-device 1: Memory module | Get maximum supported bandwidth<br />Get current allocation size<br />Get current bandwidth |
| [Fabric port](#con)   | Sub-device 0: Enumerates each port<br />Sub-device 1: Enumerates each port | Get port configuration (UP/DOWN)<br />Get physical link details<br />Get port health (green/yellow/red/black)<br />Get remote port UUID<br />Get port max rx/tx speed<br />Get port current rx/tx bandwidth | 
| [Temperature](#tmp)   | Package: temperature<br />Sub-device 0: GPU temperature<br />Sub-device 0: Memory temperature<br />Sub-device 1: GPU temperature<br />Sub-device 1: Memory temperature | Get current temperature sensor reading |
| [PSU](#psu)           | Package: Power supplies | Get details about the power supply<br />Query current state (temperature,current,fan) |
| [Fan](#fan)           | Package: Fans | Get details (max fan speed)<br />Get config (fixed fan speed, temperature-speed table)<br />Query current fan speed |
| [LED](#led)           | Package: LEDs | Get details (supports RGB configuration)<br />Query current state (on,color) |
| [RAS](#ras)           | Sub-device 0: Set of uncorrectable accelerator RAS errors, set of correctable accelerator RAS errors<br />Sub-device 1: Set of uncorrectable accelerator RAS errors, set of correctable accelerator RAS errors | Read accelerator RAS total correctable and uncorrectable error counters.<br />Read breakdown of errors by category:<br />- no. resets<br />- no. programming errors<br />- no. driver errors<br />- no. compute errors<br />- no. cache errors<br />- no. display errors<br />- no. non-compute errors | 
| [Diagnostics](#dag)   | Package: SCAN test suite<br />Package: ARRAY test suite | Get list of all diagnostics tests in the test suite | 

The table below summarizes the classes that provide device controls and an example list of components that would be enumerated for a device with two
sub-devices. The table shows the operations (controls) that will be provided for all components in each class.

| Class                 | Components    | Operations |
| :---                  | :---          | :---        |
| [Power](#pwr)         | Package: power | Set sustained power limit<br />Set burst power limit<br />Set peak power limit |
| [Frequency](#frq)     | Sub-device 0: GPU frequency<br />Sub-device 0: Memory frequency<br />Sub-device 1: GPU frequency<br />Sub-device 1: Memory frequency | Set frequency range |
| [Standby](#sby)       | Sub-device 0: Control entire sub-device<br />Sub-device 1: Control entire sub-device | Disable opportunistic standby |
| [Firmware](#fmw)      | Sub-device 0: Enumerates each firmware<br />Sub-device 1: Enumerates each firmware | Flash new firmware |
| [Fabric port](#con)   | Sub-device 0: Control each port<br />Sub-device 1: Control each port | Configure port UP/DOWN<br />Turn beaconing ON/OFF | 
| [Fan](#fan)           | Package: Fans | Set config (fixed speed, temperature-speed table) |
| [LED](#led)           | Package: LEDs | Turn LED on/off and set color where applicable |
| [Diagnostics](#con)   | SCAN test suite<br />ARRAY test suite | Run all or a subset of diagnostic tests in the test suite | 

## <a name="dce">Device component enumeration</a>
The Sysman API provides functions to enumerate all components in a class that can be managed.

For example, there is a frequency class which is used to control the frequency of different parts of the device. On most devices, the enumerator
will provide two handles, one to control the GPU frequency and one to enumerate the device memory frequency. This is illustrated in the figure below:

![Frequency flow](../images/tools_sysman_freq_flow.png?raw=true) 

In the C API, each class is associated with a unique handle type (e.g. ::zet_sysman_freq_handle_t refers to a frequency component).
In the C++ API, each class is a C++ class (e.g. An instance of the class ::zet::SysmanFrequency refers to a frequency component).

The pseudo code below shows how to use the Sysman API to enumerate all GPU frequency components and fix each to a specific frequency if this is supported:

```c
function FixGpuFrequency(zet_sysman_handle_t hSysmanDevice, double FreqMHz)
    uint32_t numFreqDomains
    if ((zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS))
        zet_sysman_freq_handle_t* pFreqHandles =
		    allocate_memory(numFreqDomains * sizeof(zet_sysman_freq_handle_t))
        if (zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
            for (index = 0 .. numFreqDomains-1)
                zet_freq_properties_t props
                if (zetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                    # Only change the frequency of the domain if:
					# 1. The domain controls a GPU accelerator
					# 2. The domain frequency can be changed
                    if (props.type == ZET_FREQ_DOMAIN_GPU
					    and props.canControl)
						    # Fix the frequency
						    zet_freq_range_t range
						    range.min = FreqMHz
						    range.max = FreqMHz
						    zetSysmanFrequencySetRange(pFreqHandles[index], &range)
	free_memory(...)
```

## <a name="sdm">Sub-device management</a>
A Sysman handle cannot be created for a sub-device - ::zetSysmanGet() will return error ::ZE_RESULT_ERROR_UNSUPPORTED if a device handle for a 
sub-device is passed to this function. Instead, the enumerator for device components will return a list of components that are located in each
sub-device. Properties for each component will indicate in which sub-device it is located. If software wishing to manage components in only one
sub-device should filter the enumerated components using the sub-device ID (see ::ze_device_properties_t.subdeviceId).

The figure below shows the frequency components that will be enumerated on a device with two sub-devices where each sub-device has a GPU and
device memory frequency control:

![Frequency flow](../images/tools_sysman_freq_subdevices.png?raw=true) 

The pseudo code below shows how to fix the GPU frequency on a specific sub-device (notice the additional sub-device check):

```c
function FixSubdeviceGpuFrequency(zet_sysman_handle_t hSysmanDevice, uint32_t subdeviceId, double FreqMHz)
    uint32_t numFreqDomains
    if ((zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS))
        zet_sysman_freq_handle_t* pFreqHandles =
		    allocate_memory(numFreqDomains * sizeof(zet_sysman_freq_handle_t))
        if (zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
            for (index = 0 .. numFreqDomains-1)
                zet_freq_properties_t props
                if (zetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                    # Only change the frequency of the domain if:
					# 1. The domain controls a GPU accelerator
					# 2. The domain frequency can be changed
					# 3. The domain is located in the specified sub-device
                    if (props.type == ZET_FREQ_DOMAIN_GPU
					    and props.canControl
						and props.subdeviceId == subdeviceId)
						    # Fix the frequency
						    zet_freq_range_t range
						    range.min = FreqMHz
						    range.max = FreqMHz
						    zetSysmanFrequencySetRange(pFreqHandles[index], &range)
	free_memory(...)
```

## <a name="evt">Events</a>
Events are a way to determine if changes have occurred on a device e.g. new RAS errors without polling the Sysman API. An application registers the events
that it wishes to receive notification about and then it listens for notifications. The application can choose to block when listening - this will put
the calling application thread to sleep until new notifications are received.

The API enables registering for events from multiple devices and listening for any events coming from any devices by using one function call.

Once notifications have occurred, the application can use the query Sysman interface functions to get more details.

The following events are provided:

- Any RAS errors have occurred

The full list of available functions for handling events is described [below](#evd).


# <a name="id">Interface details</a>

## <a name="glo">Global operations</a>

### <a name="glod">Device properties</a>
The following operations permit getting properties about the entire device:

| Function                                                   | Description |
| :---                                                       | :---        |
| ::zetSysmanDeviceGetProperties()                          | Get static device properties -  device UUID, sub-device ID, device brand/model/vendor strings |
| ::zetSysmanDeviceGetRepairStatus()                        | Determine if the device has undergone repairs, either through the running of diagnostics or by manufacturing. |

The pseudo code below shows how to display general information about a device:

```c
function ShowDeviceInfo(zet_sysman_handle_t hSysmanDevice)
	zet_sysman_properties_t devProps
    zet_repair_status_t repaired
	if (zetSysmanDeviceGetProperties(hSysmanDevice, &devProps) == ZE_RESULT_SUCCESS)
		output("    UUID:           %s", devProps.core.uuid.id)
		output("    #subdevices:    %u", devProps.numSubdevices)
		output("    brand:          %s", devProps.brandName)
		output("    model:          %s", devProps.modelName)
    if (zetSysmanDeviceRepairStatus(hSysmanDevice, &repaired) == ZE_RESULT_SUCCESS)
        output("    Was repaired:   %s", (repaired == ZET_REPAIR_STATUS_PERFORMED) ? "yes" : "no")
```

### <a name="gloz">Host processes</a>
The following functions provide information about host processes that are using the device:

| Function                                                   | Description |
| :---                                                       | :---        |
| ::zetSysmanProcessesGetState()                            | Get information about all processes that are using this device -  process ID, device memory allocation size, accelerators being used. |

Using the process ID, an application can determine the owner and the path to the executable - this information is not returned by the API.


### <a name="glos">Scheduler operations</a>
On some devices, it is possible to change the way the scheduler executes workloads. To find out if this is supported, execute the function
::zetSysmanSchedulerGetCurrentMode() and check that it does not return an error.

The available scheduler operating modes are given by the enum ::zet_sched_mode_t:

| Scheduler mode                       | Description |
| :---                                 | :---        |
| ::ZET_SCHED_MODE_TIMEOUT            | This mode is optimized for multiple applications or contexts submitting work to the hardware. When higher priority work arrives, the scheduler attempts to pause the current executing work within some timeout interval, then submits the other work.<br />It is possible to configure (::zet_sched_timeout_properties_t) the watchdog timeout which controls the maximum time the scheduler will wait for a workload to complete a batch of work or yield to other applications before it is terminated.<br />If the watchdog timeout is set to ::ZET_SCHED_WATCHDOG_DISABLE, the scheduler enforces no fairness. This means that if there is other work to execute, the scheduler will try to submit it but will not terminate an executing process that does not complete quickly. |
| ::ZET_SCHED_MODE_TIMESLICE          | This mode is optimized to provide fair sharing of hardware execution time between multiple contexts submitting work to the hardware concurrently.<br />It is possible to configure (::zet_sched_timeslice_properties_t) the timeslice interval and the amount of time the scheduler will wait for work to yield to another application before it is terminated. |
| ::ZET_SCHED_MODE_EXCLUSIVE          | This mode is optimized for single application/context use-cases. It permits a context to run indefinitely on the hardware without being preempted or terminated. All pending work for other contexts must wait until the running context completes with no further submitted work. |
| ::ZET_SCHED_MODE_COMPUTE_UNIT_DEBUG | This mode is optimized for application debug. It ensures that only one command queue can execute work on the hardware at a given time. Work is permitted to run as long as needed without enforcing any scheduler fairness policies. |

The following functions are available for changing the behavior of the scheduler:

| Function                                             | Description |
| :---                                                 | :---        |
| ::zetSysmanSchedulerGetCurrentMode()                | Get the current scheduler mode (timeout, timeslice, exclusive, single command queue) |
| ::zetSysmanSchedulerGetTimeoutModeProperties()      | Get the settings for the timeout scheduler mode |
| ::zetSysmanSchedulerGetTimesliceModeProperties()    | Get the settings for the timeslice scheduler mode |
| ::zetSysmanSchedulerSetTimeoutMode()                | Change to timeout scheduler mode and/or change properties |
| ::zetSysmanSchedulerSetTimesliceMode()              | Change to timeslice scheduler mode and/or change properties |
| ::zetSysmanSchedulerSetExclusiveMode()              | Change to exclusive scheduler mode and/or change properties |
| ::zetSysmanSchedulerSetComputeUnitDebugMode()       | Change to compute unit debug scheduler mode and/or change properties |

The pseudo code below shows how to stop the scheduler enforcing fairness while permitting other work to attempt to run:

```c
function DisableSchedulerWatchdog(zet_sysman_handle_t hSysmanDevice)
    ze_result_t res
    zet_sched_mode_t currentMode
    res = zetSysmanSchedulerGetCurrentMode(hSysmanDevice, &currentMode)
    if (res == ZE_RESULT_SUCCESS)
        ze_bool_t requireReboot
        zet_sched_timeout_properties_t props
        props.watchdogTimeout = ZET_SCHED_WATCHDOG_DISABLE
        res = zetSysmanSchedulerSetTimeoutMode(hSysmanDevice, &props, &requireReboot)
        if (res == ZE_RESULT_SUCCESS)
            if (requireReboot)
                output("WARNING: Reboot required to complete desired configuration.")
            else
                output("Schedule mode changed successfully.")
        else if(res == ZE_RESULT_ERROR_UNSUPPORTED)
            output("ERROR: The timeout scheduler mode is not supported on this device.")
        else if(res == ZE_RESULT_ERROR_INSUFFICENT_PERMISSIONS)
            output("ERROR: Don't have permissions to change the scheduler mode.")
        else
            output("ERROR: Problem calling the API to change the scheduler mode.")
    else if(res == ZE_RESULT_ERROR_UNSUPPORTED)
        output("ERROR: Scheduler modes are not supported on this device.")
    else
        output("ERROR: Problem calling the API.")
```

### <a name="glox">Performance profiles</a>
Some devices can be configured to optimize resource allocations/availability/frequencies for specific types of workloads. These are known as
_performance profiles_. The full list of profiles is described in the table below. Not all devices support these profiles - use the function
::zetSysmanPerformanceProfileGetSupported() to get the list avaiable on a given device. In general, the balanced profile (default) is
optimal for most workloads, however there are outlier workloads where the hardware is not able to detect the optimal configuration and can
benefit from one of these profiles being manually loaded.

| Performance profile                  | Description |
| :---                                 | :---        |
| ::ZET_PERF_PROFILE_BALANCED         | The hardware is configured to strike a balance between compute and memory resources. This is the default profile when the device boots/resets. |
| ::ZET_PERF_PROFILE_COMPUTE_BOUNDED  | The hardware is configured to prioritize performance of the compute units. |
| ::ZET_PERF_PROFILE_MEMORY_BOUNDED   | The hardware is configured to prioritize memory throughput. |


The following functions are available to change the performance profile of a device:

| Function                                             | Description |
| :---                                                 | :---        |
| ::zetSysmanPerformanceProfileGetSupported()         | Get a list of supported performance profiles that can be loaded for this device |
| ::zetSysmanPerformanceProfileGet()      			   | Get current pre-configured performance profile being used by the hardware |
| ::zetSysmanPerformanceProfileSet()    			   | Load a pre-configured performance profile |


### <a name="glor">Device reset</a>
The device can be reset using the following function:

| Function                                                   | Description |
| :---                                                       | :---        |
| ::zetSysmanDeviceReset()                                  | Requests that the driver reset the device. If the hardware is hung, this will perform an PCI bus reset. |


### <a name="glop">PCI link operations</a>
The following functions permit getting data about the PCI endpoint for the device:

| Function                                                   | Description |
| :---                                                       | :---        |
| ::zetSysmanPciGetProperties()                             | Get static properties for the PCI port - BDF address, number of bars, maximum supported speed |
| ::zetSysmanPciGetState()                                  | Get current PCI port speed (number of lanes, generation) and health. |
| ::zetSysmanPciGetBarProperties()                          | Get information about each configured PCI bar |
| ::zetSysmanPciGetStats()                                  | Get PCI statistics - throughput, total packets, number of packet replays |

::zetSysmanPciGetState() returns a structure that contains the current health of the PCI link which can be one of the following

| PCI link health                        | Description |
| :---                                   | :---        |
| ::ZET_PCI_LINK_STATUS_GREEN           | The PCI link is operating as expected. |
| ::ZET_PCI_LINK_STATUS_YELLOW          | The PCI link has quality issues and/or bandwidth degradation. |
| ::ZET_PCI_LINK_STATUS_RED             | The PCI link is unstable and preventing workloads making forward progress. |

If the PCI link is in a yellow state, the API provides additional information about the types of quality degradation that are being observed.
If the PCI link is in a red state, the API provides additional information about the causes of the instability.

When the PCI link health state changes, the event ::ZET_SYSMAN_EVENT_TYPE_PCI_LINK_HEALTH is triggered.

The pseudo code below shows how to output the PCI BDF address:

```c
function ShowPciInfo(zet_sysman_handle_t hSysmanDevice)
    zet_pci_properties_t pciProps;
    if (zetSysmanPciGetProperties(hSysmanDevice, &pciProps) == ZE_RESULT_SUCCESS)
        output("    PCI address:        %04u:%02u:%02u.%u",
		    pciProps.address.domain,
			pciProps.address.bus,
			pciProps.address.device,
			pciProps.address.function);
```

## <a name="pwr">Operations on power domains</a>
The PSU (Power Supply Unit) provides power to a device. The amount of power drawn by a device is a function of the voltage and frequency,
both of which are controlled by the Punit, a micro-controller on the device. If the voltage and frequency are too high, two conditions can occur:

1. Over-current - This is where the current drawn by the device exceeds the maximum current that the PSU can supply. The PSU asserts a signal when
this occurs, and it is processed by the Punit.
2. Over-temperature - The device is generating too much heat that cannot be dissipated fast enough. The Punit monitors temperatures and reacts when
the sensors show the maximum temperature exceeds the threshold TjMax (typically 100 degrees celcius).

When either of these conditions occurs, the Punit throttles the frequencies/voltages of the device down to their minimum values, severely impacting
performance. The Punit avoids such severe throttling by measuring the actual power being consumed by the system and slowly throttling the frequencies
down when power exceeds some limits. Three limits are monitored by the Punit:

| Limit     | Window        | Description                                                                                                                                                                                                                |
| :---      | :---          | :---                                                                                                                                                                                                                       |
| Peak      | Instantaneous | Punit tracks the instantaneous power. When this exceeds a programmable threshold, the Punit will aggressively throttle frequencies/voltages. The threshold is referred to as PL4 - Power Limit 4 - or peak power.          |
| Burst     | 2ms           | Punit tracks the 2ms moving average of power. When this exceeds a programmable threshold, the Punit starts throttling frequencies/voltages. The threshold is referred to as PL2 - Power Limit 2 - or burst power. |
| Sustained | 28sec         | Punit tracks the 28sec moving average of power. When this exceeds a programmable threshold, the Punit throttles frequencies/voltages. The threshold is referred to as PL1 - Power Limit 1 - or sustained power.   |

Peak power limit is generally greater than the burst power limit which is generally greater than the sustained power limit. The default factory values
are tuned assuming the device is operating at normal temperatures running significant workloads:

- The peak power limit is tuned to avoid tripping the PSU over-current signal for all but the most intensive compute workloads. Most workloads should
be able to run at maximum frequencies without hitting this condition.
- The burst power limit permits most workloads to run at maximum frequencies for short periods.
- The sustained power limit will be triggered if high frequencies are requested for lengthy periods (configurable, default is 28sec) and the frequencies will be throttled
if the high requests and utilization of the device continue.

Some power domains support requesting the event ::ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED be generated when the energy consumption exceeds
some value. This can be a useful technique to suspend an application until the GPU becomes busy. The technique involves calling
::zetSysmanPowerSetEnergyThreshold() with some delta energy threshold, registering to receive the event using the function
::zetSysmanEventSetConfig() and then calling ::zetSysmanEventListen() to block until the event is triggered. When the energy consumed by the
power domain from the time the call is made exceeds the specified delta, the event is triggered and the application is woken up.

The following functions are provided to manage the power of the device:

| Function                              | Description |
| :---                                  | :---        |
| ::zetSysmanPowerGet()                | Enumerate the power domains. |
| ::zetSysmanPowerGetProperties()      | Get the maximum power limit that can be specified when changing the power limits of a specific power domain. |
| ::zetSysmanPowerGetEnergyCounter()   | Read the energy consumption of the specific domain. |
| ::zetSysmanPowerGetLimits()          | Get the sustained/burst/peak power limits for the specific power domain. |
| ::zetSysmanPowerSetLimits()          | Set the sustained/burst/peak power limits for the specific power domain. |
| ::zetSysmanPowerGetEnergyThreshold() | Get the current energy threshold. |
| ::zetSysmanPowerSetEnergyThreshold() | Set the energy threshold. Event ::ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED will be generated when the energy consumed since calling this functions exceeds the specified threshold. |

The pseudo code below shows how to output information about each power domain on a device:

```c
function ShowPowerDomains(zet_sysman_handle_t hSysmanDevice)
    uint32_t numPowerDomains
    if (zetSysmanPowerGet(hSysmanDevice, &numPowerDomains, NULL) == ZE_RESULT_SUCCESS)
        zet_sysman_pwr_handle_t* phPower =
            allocate_memory(numPowerDomains * sizeof(zet_sysman_pwr_handle_t))
        if (zetSysmanPowerGet(hSysmanDevice, &numPowerDomains, phPower) == ZE_RESULT_SUCCESS)
            for (pwrIndex = 0 .. numPowerDomains-1)
                zet_power_properties_t props
                if (zetSysmanPowerGetProperties(phPower[pwrIndex], &props) == ZE_RESULT_SUCCESS)
                    if (props.onSubdevice)
                        output("Sub-device %u power:\n", props.subdeviceId)
                        output("    Can control: %s", props.canControl ? "yes" : "no")
                        call_function ShowPowerLimits(phPower[pwrIndex])
                    else
                        output("Total package power:\n")
                        output("    Can control: %s", props.canControl ? "yes" : "no")
                        call_function ShowPowerLimits(phPower[pwrIndex])
    free_memory(...)
}

function ShowPowerLimits(zet_sysman_pwr_handle_t hPower)
    zet_power_sustained_limit_t sustainedLimits
    zet_power_burst_limit_t burstLimits
    zet_power_peak_limit_t peakLimits
    if (zetSysmanPowerGetLimits(hPower, &sustainedLimits, &burstLimits, &peakLimits) == ZE_RESULT_SUCCESS)
        output("    Power limits\n")
        if (sustainedLimits.enabled)
            output("        Sustained: %.3f W %.3f sec",
                sustainedLimits.power / 1000,
				sustainedLimits.interval / 1000)
        else
            output("        Sustained: Disabled")
        if (burstLimits.enabled)
            output("        Burst:     %.3f", burstLimits.power / 1000)
        else
            output("        Burst:     Disabled")
        output("        Burst:     %.3f", peakLimits.power / 1000)
```

The pseudo code shows how to output the average power. It assumes that the function is called regularly (say every 100ms).

```c
function ShowAveragePower(zet_sysman_pwr_handle_t hPower, zet_power_energy_counter_t* pPrevEnergyCounter)
    zet_power_energy_counter_t newEnergyCounter;
    if (zetSysmanPowerGetEnergyCounter(hPower, &newEnergyCounter) == ZE_RESULT_SUCCESS)
        uint64_t deltaTime = newEnergyCounter.timestamp - pPrevEnergyCounter->timestamp;
        if (deltaTime)
            output("    Average power: %.3f W",
                (newEnergyCounter.energy - pPrevEnergyCounter->energy) / deltaTime);
            *pPrevEnergyCounter = newEnergyCounter;
```

## <a name="frq">Operations on frequency domains</a>
The hardware manages frequencies to achieve a balance between best performance and power consumption. Most devices have one or more frequency domains.

The following functions are provided to manage the frequency domains on the device:

| Function                                  | Description |
| :---                                      | :---        |
| ::zetSysmanFrequencyGet()                | Enumerate all the frequency domains on the device and sub-devices. |
| ::zetSysmanFrequencyGetProperties()      | Find out which domain ::zet_freq_domain_t is controlled by this frequency and min/max hardware frequencies.  |
| ::zetSysmanFrequencyGetAvailableClocks() | Get an array of all available frequencies that can be requested on this domain. |
| ::zetSysmanFrequencyGetRange()           | Get the current min/max frequency between which the hardware can operate for a frequency domain. |
| ::zetSysmanFrequencySetRange()           | Set the min/max frequency between which the hardware can operate for a frequency domain. |
| ::zetSysmanFrequencyGetState()           | Get the current frequency request, actual frequency, TDP frequency and throttle reasons for a frequency domain. |
| ::zetSysmanFrequencyGetThrottleTime()    | Gets the amount of time a frequency domain has been throttled. |

It is only permitted to set the frequency range if the device property ::zet_freq_properties_t.canControl is true for the specific frequency
domain.

By setting the min/max frequency range to the same value, software is effectively disabling the hardware controlled frequency and getting a fixed stable
frequency providing the Punit does not need to throttle due to excess power/heat. 

Based on the power/thermal conditions, the frequency requested by software or the hardware may not be respected. This situation can be determined
using the function ::zetSysmanFrequencyGetState() which will indicate the current frequency request, the actual (resolved) frequency and other
frequency information that depends on the current conditions. If the actual frequency is below the requested frequency,
::zet_freq_state_t.throttleReasons will provide the reasons why the frequency is being limited by the Punit.

When a frequency domain starts being throttled, the event ::ZET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED is triggered if this is supported (check
::zet_freq_properties_t.isThrottleEventSupported).

### <a name="fro">Frequency/Voltage overclocking</a>
Overclocking involves modifying the voltage-frequency (V-F) curve to either achieve better performance by permitting the hardware to reach higher frequencies
or better efficiency by lowering the voltage for the same frequency.

By default, the hardware imposes a factory-fused maximum frequency and a voltage-frequency curve. The voltage-frequency curve specifies how much
voltage is needed to safely reach a given frequency without hitting overcurrent conditions. If the hardware detects overcurrent (IccMax), it will
severely throttle frequencies in order to protect itself. Also, if the hardware detects that any part of the chip exceeds a maximum temperature
limit (TjMax) it will also severely throttle frequencies.

To improve maximum performance, the following modifications can be made:

- Increase the maximum frequency.
- Increase the voltage to ensure stability at the higher frequency.
- Increase the maximum current (IccMax).
- Increase the maximum temperature (TjMax).

All these changes come with the risk of damage to the device. Any attempt at overclocking voids the product warranty.

To improve efficiency for a given workload that is not excercising the full circuitry of the device, the following modifications can be made:

- Decrease the voltage

Frequency/voltage overclocking is accomplished by calling ::zetSysmanFrequencyOcSetConfig() with a new overclock configuration ::zet_oc_config_t.
There are two modes that control the way voltage is handled when overclocking the frequency:

| Voltage overclock mode                    | Description |
| :---                                      | :---        |
| ::ZET_OC_MODE_OVERRIDE                   | In this mode, a fixed user-supplied voltage (::zet_oc_config_t.voltageTarget + ::zet_oc_config_t.voltageOffset) is applied at all times, independent of the frequency request. This is not efficient but can improve stability by avoiding power-supply voltage changes as the frequency changes. |
| ::ZET_OC_MODE_INTERPOLATIVE              | In this mode, a new point is added to the interpolated V-F curve with a user-supplied overclock voltage and frequency (::zet_oc_config_t.frequency, ::zet_oc_config_t.voltageTarget). The user can also specify a voltage offset (::zet_oc_config_t.voltageOffset) that is applied to all points on the interpolated V-F curve, including the new overclock point. This mode is much more efficient than the override mode since lower voltages are used for lower frequencies, but at the expense of small latencies introduced each time the frequency is changed. |

The figure below shows a fictitious factory default V-F curve (dark blue) for frequency requests between 100MHz and 1100MHz.
The other curves show how different overclock modes and parameters change the way the hardware drives the voltage. Note that
in all modes, the voltage used to drive the overclock frequency (in this example 1300MHz) is the sum of the voltage target
and the voltage offset.

![Overclock V-F curve](../images/tools_sysman_oc.png?raw=true) 

The following functions are provided to handle overclocking:

| Function                                  | Description |
| :---                                      | :---        |
| ::zetSysmanFrequencyOcGetCapabilities()  | Determine the overclock capabilities of the device. |
| ::zetSysmanFrequencyOcGetConfig()        | Get the overclock configuration in effect. |
| ::zetSysmanFrequencyOcSetConfig()        | Set a new overclock configuration. |
| ::zetSysmanFrequencyOcGetIccMax()        | Get the maximum current limit in effect. |
| ::zetSysmanFrequencyOcSetIccMax()        | Set a new maximum current limit. |
| ::zetSysmanFrequencyOcGetTjMax()         | Get the maximum temperature limit in effect. |
| ::zetSysmanFrequencyOcSetTjMax()         | Set a new maximum temperature limit. |

Overclocking can be turned off by calling ::zetSysmanFrequencyOcSetConfig() with mode ::ZET_OC_MODE_OFF and by calling
::zetSysmanFrequencyOcGetIccMax() and ::zetSysmanFrequencyOcSetTjMax() with values of 0.0.

## <a name="eng">Operations on engine groups</a>
It is possible to monitor the activity of one or engines combined into an **engine group**. A device can have multiple engine groups and the possible
types are defined in ::zet_engine_group_t. The current engine groups supported are global activity across all engines, activity across all compute
accelerators, activity across all media accelerators and activity across all copy engines.

By taking two snapshots of the activity counters, it is possible to calculate the average utilization of different parts of the device.

The following functions are provided:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanEngineGet()                | Enumerate the engine groups that can be queried. |
| ::zetSysmanEngineGetProperties()      | Get the properties of an engine group. This will return the type of engine group (one of ::zet_engine_group_t) and on which sub-device the group is making measurements. |
| ::zetSysmanEngineGetActivity()        | Returns the activity counters for an engine group. |


## <a name="sby">Operations on standby domains</a>
When a device is idle, it will enter a low-power state. Since exit from low-power states have associated latency, it can hurt performance. The
hardware attempts to stike a balance between saving power when there are large idle times between workloads submissions to the device and
keeping the device awake when idle because it has determined that new workload submissions are imminent.

A device can consist of one or more standby domains - the list of domains is given by ::zet_standby_type_t.

The following functions can be used to control how the hardware promotes to standby states:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanStandbyGet()               | Enumerate the standby domains. |
| ::zetSysmanStandbyGetProperties()     | Get the properties of a standby domain. This will return the parts of the device that are affected by this domain (one of ::zet_engine_group_t) and on which sub-device the domain is located. |
| ::zetSysmanStandbyGetMode()           | Get the current promotion mode (one of ::zet_standby_promo_mode_t) for a standby domain.|
| ::zetSysmanStandbySetMode()           | Set the promotion mode (one of ::zet_standby_promo_mode_t) for a standby domain. |


## <a name="fmw">Operations on firmwares</a>
The following functions are provided to manage firmwares on the device:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanFirmwareGet()              | Enumerate all firmwares that can be managed on the device. |
| ::zetSysmanFirmwareGetProperties()    | Find out the name and version of a firmware. |
| ::zetSysmanFirmwareGetChecksum()      | Get the checksum for an installed firmware. |
| ::zetSysmanFirmwareFlash()            | Flash a new firmware image. |

## <a name="mem">Querying memory modules</a>
The API provides an enumeration of all device memory modules. For each memory module, the current and maximum bandwidth can be queried.
The API also provides a health metric which can take one of the following values (::zet_mem_health_t):

| Memory health                         | Description |
| :---                                  | :---        |
| ::ZET_MEM_HEALTH_OK                  | All memory channels are healthy. |
| ::ZET_MEM_HEALTH_DEGRADED            | Excessive correctable errors have been detected on one or more channels. Device should be reset. |
| ::ZET_MEM_HEALTH_CRITICAL            | Operating with reduced memory to cover banks with too many uncorrectable errors. |
| ::ZET_MEM_HEALTH_REPLACE             | Device should be replaced due to excessive uncorrectable errors. |

When the health state of a memory module changes, the event ::ZET_SYSMAN_EVENT_TYPE_MEM_HEALTH is triggered.

The following functions provide access to information about the device memory modules:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanMemoryGet()                | Enumerate the memory modules. |
| ::zetSysmanMemoryGetProperties()      | Find out the type of memory and maximum physical memory of a module. |
| ::zetSysmanMemoryGetBandwidth()       | Returns memory bandwidth counters for a module. |
| ::zetSysmanMemoryGetState()           | Returns the currently health and allocated memory size for a module. |


## <a name="con">Operations on Fabric ports</a>
**Fabric** is the term given to describe high-speed interconnections between accelerator devices, primarily used to provide low latency fast
access to remote device memory. Devices have one or more **fabric ports** that transmit and receive data over physical links. Links connect
fabric ports, thus permitting data to travel between devices. Routing rules determine the flow of traffic through the fabric.

The figure below shows four devices, each with two fabric ports. Each port has a link that connects it to a port on another device.
In this example, the devices are connected in a ring. Device A and D can access each other's memory through either device B or device C
depending on how the fabric routing rules are configured. If the connection between device B and D goes down, the routing rules can be
modified such that device B and D can still access each other's memory by going through two hops in the fabric (device A and C).

![Fabric ports](../images/tools_sysman_fabric.png?raw=true)

The API permits enumerating all the ports available on a device. Each port has a universal unique identifier (UUID). If the port is connected
to another port, the API will provide the remote port's UUID. By enumerating all ports on all devices that are connected to the fabric,
an application can build a topology map of connectivity.

For each port, the API permits querying its configuration (UP/DOWN) and its health which can take one of the following values:

| Fabric port health                     | Description |
| :---                                   | :---        |
| ::ZET_FABRIC_PORT_STATUS_GREEN        | The port is up and operating as expected. |
| ::ZET_FABRIC_PORT_STATUS_YELLOW       | The port is up but has quality and/or bandwidth degradation. |
| ::ZET_FABRIC_PORT_STATUS_RED          | Port connection instabilities are preventing workloads making forward progress. |
| ::ZET_FABRIC_PORT_STATUS_BLACK        | The port is configured down. |

If the port is in a yellow state, the API provides additional information about the types of quality degradation that are being observed.
If the port is in a red state, the API provides additional information about the causes of the instability.

When a port's health state changes, the event ::ZET_SYSMAN_EVENT_TYPE_FABRIC_PORT_HEALTH is triggered.

The API permits measuring the receive and transmit bandwidth flowing through each port. It also provides the maximum receive and transmit
speed (frequency/number of lanes) of each port and the current speeds which can be lower if operating in a degraded state. Note that a
port's receive and transmit speeds are not necessarily the same.

Since ports can pass data directly through to another port, the measured bandwidth at a port can be higher than the actual bandwidth generated by
the accelerators directly connected by two ports. As such, bandwidth metrics at each port are more relevant for determining points of
congestion in the fabric and less relevant for measuring the total bandwidth passing between two accelerators.

The following functions can be used to manage Fabric ports:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanFabricPortGet()            | Enumerate all fabric ports on the device. |
| ::zetSysmanFabricPortGetProperties()  | Get static properties about the port (model, UUID, max receive/transmit speed). |
| ::zetSysmanFabricPortGetLinkType()    | Get details about the physical link connected to the port. |
| ::zetSysmanFabricPortGetConfig()      | Determine if the port is configured UP and if beaconing is on or off. |
| ::zetSysmanFabricPortSetConfig()      | Configure the port UP or DOWN and turn beaconing on or off. |
| ::zetSysmanFabricPortGetState()       | Determine the health of the port connection, reasons for link degradation or connection issues and the current receive/transmit speed. |
| ::zetSysmanFabricPortGetThroughput()  | Get port receive/transmit counters along with current receive/transmit port speed. |

For devices with sub-devices, the fabric ports are usually located in the sub-device. Given a device handle, ::zetSysmanFabricPortGet() will
include the ports on each sub-device. In this case, ::zet_fabric_port_properties_t.onSubdevice will be set to true and
::zet_fabric_port_properties_t.subdeviceId will give the subdevice ID where that port is located.

The pseudo-code below shows how to get the state of all fabric ports in the device and sub-devices:

```c
void ShowFabricPorts(zet_sysman_handle_t hSysmanDevice)
    uint32_t numPorts
    if ((zetSysmanFabricPortGet(hSysmanDevice, &numPorts, NULL) == ZE_RESULT_SUCCESS))
        zet_sysman_fabric_port_handle_t* phPorts =
            allocate_memory(numPorts * sizeof(zet_sysman_fabric_port_handle_t))
        if (zetSysmanFabricPortGet(hSysmanDevice, &numPorts, phPorts) == ZE_RESULT_SUCCESS)
            for (index = 0 .. numPorts-1)
			    # Show information about a particular port
                output("    Port %u:\n", index)
                call_function ShowFabricPortInfo(phPorts[index])
	free_memory(...)

function ShowFabricPortInfo(zet_sysman_fabric_port_handle_t hPort)
    zet_fabric_port_properties_t props
    if (zetSysmanFabricPortGetProperties(hPort, &props) == ZE_RESULT_SUCCESS)
        zet_fabric_port_state_t state
        if (zetSysmanFabricPortGetState(hPort, &state) == ZE_RESULT_SUCCESS)
            zet_fabric_link_type_t link
            if (zetSysmanFabricPortGetLinkType(hPort, false, &link) == ZE_RESULT_SUCCESS)
                zet_fabric_port_config_t config
                if (zetSysmanFabricPortGetConfig(hPort, &config) == ZE_RESULT_SUCCESS)
                    output("        Model:                 %s", props.model)
                    if (props.onSubdevice)
                        output("        On sub-device:         %u", props.subdeviceId)
                    if (config.enabled)
                    {
                        var status
                        output("        Config:                UP")
                        switch (state.status)
							case ZET_FABRIC_PORT_STATUS_GREEN:
								status = "GREEN - The port is up and operating as expected"
							case ZET_FABRIC_PORT_STATUS_YELLOW:
								status = "YELLOW - The port is up but has quality and/or bandwidth degradation"
							case ZET_FABRIC_PORT_STATUS_RED:
								status = "RED - Port connection instabilities"
							case ZET_FABRIC_PORT_STATUS_BLACK:
								status = "BLACK - The port is configured down"
							default:
								status = "UNKNOWN"
                        output("        Status:                %s", status)
                        output("        Link type:             %s", link.desc)
                        output(
                            "        Max speed (rx/tx):     %llu/%llu bytes/sec",
                            props.maxRxSpeed.maxBandwidth,
                            props.maxTxSpeed.maxBandwidth)
                        output(
                            "        Current speed (rx/tx): %llu/%llu bytes/sec",
                            state.rxSpeed.maxBandwidth,
                            state.txSpeed.maxBandwidth)
                    else
                        output("        Config:                DOWN")
```

## <a name="tmp">Querying temperature</a>
A device has multiple temperature sensors embedded at different locations. The following locations are supported:

| Temperature sensor location                | Description |
| :---                                       | :---        |
| ::ZET_TEMP_SENSORS_GLOBAL                 | Returns the maximum measured across all sensors in the device. |
| ::ZET_TEMP_SENSORS_GPU                    | Returns the maximum measured across all sensors in the GPU accelerator. |
| ::ZET_TEMP_SENSORS_MEMORY                 | Returns the maximum measured across all sensors in the device memory. |

For some sensors, it is possible to request that events be triggered when temperatures cross thresholds. This is accomplished using the
function ::zetSysmanTemperatureGetConfig() and ::zetSysmanTemperatureSetConfig(). Support for specific events is accomplished by calling
::zetSysmanTemperatureGetProperties(). In general, temperature events are only supported on the temperature sensor of type
::ZET_TEMP_SENSORS_GLOBAL. The list below describes the list of temperature events:

| Event                                      | Check support                                    | Description |
| :---                                       | :---                                             | :--- |
| ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL     | ::zet_temp_properties_t.isCriticalTempSupported | The event is triggered when the temperature crosses into the critical zone where severe frequency throttling will be taking place. |
| ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1   | ::zet_temp_properties_t.isThreshold1Supported   | The event is triggered when the temperature crosses the custom threshold 1. Flags can be set to limit the trigger to when crossing from high to low or low to high. |
| ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2   | ::zet_temp_properties_t.isThreshold2Supported   | The event is triggered when the temperature crosses the custom threshold 2. Flags can be set to limit the trigger to when crossing from high to low or low to high. |

The following function can be used to manage temperature sensors:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanTemperatureGet()           | Enumerate the temperature sensors on the device. |
| ::zetSysmanTemperatureGetProperties() | Get static properties for a temperature sensor. In particular, this will indicate which parts of the device the sensor measures (one of ::zet_temp_sensors_t). |
| ::zetSysmanTemperatureGetConfig()     | Get information about the current temperature thresholds - enabled/threshold/processID. |
| ::zetSysmanTemperatureSetConfig()     | Set new temperature thresholds. Events will be triggered when the temperature crosses these thresholds. |
| ::zetSysmanTemperatureGetState()      | Read the temperature of a sensor. |


## <a name="psu">Operations on power supplies</a>
The following functions can be used to access information about each power-supply on a device:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanPsuGet()                   | Enumerate the power supplies on the device that can be managed. |
| ::zetSysmanPsuGetProperties()         | Get static details about the power supply. |
| ::zetSysmanPsuGetState()              | Get information about the health (temperature, current, fan) of the power supply. |


## <a name="fan">Operations on fans</a>
If ::zetSysmanFanGet() returns one or more fan handles, it is possible to manage their speed. The hardware can be instructed to run the fan at a fixed
speed (or 0 for silent operations) or to provide a table of temperature-speed points in which case the hardware will dynamically change the fan
speed based on the current temperature of the chip. This configuration information is described in the structure ::zet_fan_config_t. When specifying
speed, one can provide the value in revolutions per minute (::ZET_FAN_SPEED_UNITS_RPM) or as a percentage of the maximum RPM
(::ZET_FAN_SPEED_UNITS_PERCENT).

The following functions are available:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanFanGet()                   | Enumerate the fans on the device. |
| ::zetSysmanFanGetProperties()         | Get the maximum RPM of the fan and the maximum number of points that can be specified in the temperature-speed table for a fan. |
| ::zetSysmanFanGetConfig()             | Get the current configuration (speed) of a fan. |
| ::zetSysmanFanSetConfig()             | Change the configuration (speed) of a fan. |
| ::zetSysmanFanGetState()              | Get the current speed of a fan. |

The pseudo code below shows how to output the fan speed of all fans:

```c
function ShowFans(zet_sysman_handle_t hSysmanDevice)
    uint32_t numFans
    if (zetSysmanFanGet(hSysmanDevice, &numFans, NULL) == ZE_RESULT_SUCCESS)
        zet_sysman_fan_handle_t* phFans =
            allocate_memory(numFans * sizeof(zet_sysman_fan_handle_t))
        if (zetSysmanFanGet(hSysmanDevice, &numFans, phFans) == ZE_RESULT_SUCCESS)
            output("    Fans")
            for (fanIndex = 0 .. numFans-1)
                uint32_t speed
                if (zetSysmanFanGetState(phFans[fanIndex], ZET_FAN_SPEED_UNITS_RPM, &speed)
				    == ZE_RESULT_SUCCESS)
                        output("        Fan %u: %u RPM", fanIndex, speed)
	free_memory(...)
}
```

The next example shows how to set the fan speed for all fans to a fixed value in RPM, but only if control is permitted:

```c
function SetFanSpeed(zet_sysman_handle_t hSysmanDevice, uint32_t SpeedRpm)
{
    uint32_t numFans
    if (zetSysmanFanGet(hSysmanDevice, &numFans, NULL) == ZE_RESULT_SUCCESS)
        zet_sysman_fan_handle_t* phFans =
            allocate_memory(numFans * sizeof(zet_sysman_fan_handle_t))
        if (zetSysmanFanGet(hSysmanDevice, &numFans, phFans) == ZE_RESULT_SUCCESS)
            zet_fan_config_t config
            config.mode = ZET_FAN_SPEED_MODE_FIXED
            config.speed = SpeedRpm
            config.speedUnits = ZET_FAN_SPEED_UNITS_RPM
            for (fanIndex = 0 .. numFans-1)
                zet_fan_properties_t fanprops
                if (zetSysmanFanGetProperties(phFans[fanIndex], &fanprops) == ZE_RESULT_SUCCESS)
                    if (fanprops.canControl)
                        zetSysmanFanSetConfig(phFans[fanIndex], &config)
                    else
                        output("ERROR: Can't control fan %u.\n", fanIndex)
	free_memory(...)
}
```

## <a name="led">Operations on LEDs</a>
If ::zetSysmanLedGet() returns one or more LED handles, it is possible to manage LEDs on the device. This includes turning them off/on and where
the capability exists, changing their color in realtime.

The following functions are available:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanLedGet()                   | Enumerate the LEDs on the device that can be managed. |
| ::zetSysmanLedGetProperties()         | Find out if a LED supports color changes. |
| ::zetSysmanLedGetState()              | Find out if a LED is currently off/on and the color where the capability is available. |
| ::zetSysmanLedSetState()              | Turn a LED off/on and set the color where the capability is available. |


## <a name="ras">Querying RAS errors</a>
RAS stands for Reliability, Availability and Serviceability. It is a feature of certain devices accelerators that attempts to correct
random bit errors and provide redundancy where permanent damage has occurred.

If a device accelerator supports RAS, it maintains counters for hardware and software errors. There are two types of errors and they are defined in
::zet_ras_error_type_t:

| Error Type                          | Description |
| :---                                | :---        |
| ::ZET_RAS_ERROR_TYPE_UNCORRECTABLE | Hardware errors occurred which most likely resulted in loss of data or even a device hang. If an error results in device lockup, a warm boot is required before those errors will be reported. |
| ::ZET_RAS_ERROR_TYPE_CORRECTABLE   | These are errors that were corrected by the hardware and did not cause data corruption. |

Note that these are errors related to the accelerator device and do not include similar RAS behavior of components such as device memory,
high-speed fabric and the PCI link to the host - errors related to these components are provided via separate health metrics (see
::zetSysmanMemoryGetState(), ::zetSysmanFabricPortGetState() and ::zetSysmanPciGetState()).

A RAS error set is a collection of all RAS errors of a given type (correctable/uncorrectable) located either in a sub-device or a device.
The function ::zetSysmanRasGet() enumerates the available RAS error sets, providing a handle for each. If no handles are returned,
no RAS errors are available/enabled on the device.

A device without sub-devices will typically return two RAS error handles if the device supports RAS - one for correctable handles and one for
uncorrectable handles. In addition, a device with sub-devices will return additional handles for each sub-device. The function
::zetSysmanRasGetProperties() can be used to determine the type RAS errors (correctable/uncorrectable) represented by the handle and the
sub-device location.

To determine if errors have occurred, software uses the function ::zetSysmanRasGetState(). This will return the total number of errors of a given type
(correctable/uncorrectable) that have occurred.

When calling ::zetSysmanRasGetState(), software can request that the error counters be cleared. When this is done, all counters of the specified
type (correctable/uncorrectable) will be set to zero and any subsequent calls to this function will only show new errors that have occurred.
If software intends to clear errors, it should be the only application doing so and it should store the counters in an appropriate database
for historical analysis.

When calling ::zetSysmanRasGetState(), an optional pointer to a structure of type ::zet_ras_details_t can be supplied. This will give a
breakdown of the main device components where the errors occurred. The categories are defined in the structure ::zet_ras_details_t. The meaning
of each category depends on the error type (correctable, uncorrectable).

| Error category                            |  ::ZET_RAS_ERROR_TYPE_CORRECTABLE | ::ZET_RAS_ERROR_TYPE_UNCORRECTABLE | 
| :---                                      | :---        | :---        |
| ::zet_ras_details_t.numResets            | Always zero. | Number of device resets that have taken place. |
| ::zet_ras_details_t.numProgrammingErrors | Always zero. | Number of hardware exceptions generated by the way workloads have programmed the hardware. |
| ::zet_ras_details_t.numDriverErrors      | Always zero. | Number of low level driver communication errors have occurred. |
| ::zet_ras_details_t.numComputeErrors     | Number of errors that have occurred in the accelerator hardware that were corrected. | Number of errors that have occurred in the accelerator hardware that were not corrected. These would have caused the hardware to hang and the driver to reset. |
| ::zet_ras_details_t.numNonComputeErrors  | Number of errors occurring in fixed-function accelerator hardware that were corrected. | Number of errors occurring in the fixed-function accelerator hardware there could not be corrected. Typically these will result in a PCI bus reset and driver reset. |
| ::zet_ras_details_t.numCacheErrors       | Number of ECC correctable errors that have occurred in the on-chip caches (caches/register file/shared local memory). | Number of ECC uncorrectable errors that have occurred in the on-chip caches (caches/register file/shared local memory). These would have caused the hardware to hang and the driver to reset. |
| ::zet_ras_details_t.numDisplayErrors     | Number of ECC correctable errors that have occurred in the display. | Number of ECC uncorrectable errors that have occurred in the display. |

Each RAS error type can trigger events when the error counters exceed thresholds. The events are listed in the table below. Software can use the
functions ::zetSysmanRasGetConfig() and ::zetSysmanRasSetConfig() to get and set the thresholds for each error type. The default is for all
thresholds to be 0 which means that no events are generated. Thresholds can be set on the total RAS error counter or on each of the detailed
error counters.

| RAS error Type                      | Event |
| :---                                | :---        |
| ::ZET_RAS_ERROR_TYPE_UNCORRECTABLE | ::ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS |
| ::ZET_RAS_ERROR_TYPE_CORRECTABLE   | ::ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS |

The table below summaries all the RAS management functions:

| Function                              | Description |
| :---                                  | :---        |
| ::zetSysmanRasGet()                  | Get handles to the available RAS error sets. |
| ::zetSysmanRasGetProperties()        | Get properties about a RAS error set - type of RAS errors and sub-device location. |
| ::zetSysmanRasGetConfig()            | Get the current list of thresholds for each counter in the RAS error set. RAS error events will be generated when the thresholds are exceeded. |
| ::zetSysmanRasSetConfig()            | Set current list of thresholds for each counter in the RAS error set. RAS error events will be generated when the thresholds are exceeded. |
| ::zetSysmanRasGetState()             | Get the current state of the RAS error counters for a given RAS error set. The counters can also be optionally cleared. |

The pseudo code below shows how to determine the RAS error sets on a device and show the current state of RAS errors:

```c
void ShowRasErrors(zet_sysman_handle_t hSysmanDevice)
    uint32_t numRasErrorSets
    zet_sysman_ras_handle_t* phRasErrorSets
    if (zetSysmanRasGet(hSysmanDevice, &numRasErrorSets, NULL) != ZE_RESULT_SUCCESS)
        return
    if (numRasErrorSets == 0)
        output("No RAS error sets available/enabled on this device.")
        return
	phRasErrorSets =
		allocate_memory(numRasErrorSets * sizeof(zet_sysman_ras_handle_t))
	if (zetSysmanRasGet(hSysmanDevice, &numRasErrorSets, phRasErrorSets) == ZE_RESULT_SUCCESS)
		for (rasIndex = 0 .. numRasErrorSets)
			uint64_t newErrors
			zet_ras_details_t errorDetails
			zet_ras_properties_t props
			if (zetSysmanRasGetProperties(phRasErrorSets[rasIndex], &props) == ZE_RESULT_SUCCESS)
				var pErrorType
				switch (props.type)
					case ZET_RAS_ERROR_TYPE_CORRECTABLE:
						pErrorType = "Correctable"
					case ZET_RAS_ERROR_TYPE_UNCORRECTABLE:
						pErrorType = "Uncorrectable"
					default:
						pErrorType = "Unknown"
				output("RAS %s errors", pErrorType)
				if (props.onSubdevice)
					output("    On sub-device: %u", props.subdeviceId)
				if (zetSysmanRasGetState(phRasErrorSets[rasIndex], 1, &newErrors, &errorDetails)
					== ZE_RESULT_SUCCESS)
						output("    Number new errors: %llu", newErrors)
						if (newErrors)
							call_function OutputRasDetails(&errorDetails)
	free_memory(...)

function OutputRasDetails(zet_ras_details_t* pDetails)
    output("        Number new resets:                %llu", pDetails->numResets)
    output("        Number new programming errors:    %llu", pDetails->numProgrammingErrors)
    output("        Number new driver errors:         %llu", pDetails->numDriverErrors)
    output("        Number new compute errors:        %llu", pDetails->numComputeErrors)
    output("        Number new non-compute errors:    %llu", pDetails->numNonComputeErrors)
    output("        Number new cache errors:          %llu", pDetails->numCacheErrors)
    output("        Number new memory errors:         %llu", pDetails->numMemoryErrors)
    output("        Number new PCI errors:            %llu", pDetails->numPciErrors)
    output("        Number new fabric errors:         %llu", pDetails->numFabricErrors)
    output("        Number new display errors:        %llu", pDetails->numDisplayErrors)
```


## <a name="dag">Performing diagnostics</a>
Diagnostics is the process of taking a device offline and requesting that the hardware run self-checks and repairs. This is achieved using the function
::zetSysmanDiagnosticsRunTests(). On return from the function, software can use the diagnostics return code (::zet_diag_result_t) to determine the new
course of action:

1. ::ZET_DIAG_RESULT_NO_ERRORS - No errors found and workloads can resume submission to the hardware.
2. ::ZET_DIAG_RESULT_ABORT - Hardware had problems running diagnostic tests.
3. ::ZET_DIAG_RESULT_FAIL_CANT_REPAIR - Hardware had problems setting up repair. Card should be removed from the system.
4. ::ZET_DIAG_RESULT_REBOOT_FOR_REPAIR - Hardware has prepared for repair and requires a reboot after which time workloads can resume submission.

The function ::zetSysmanDeviceGetRepairStatus() can be used to determine if the device has been repaired.

There are multiple diagnostic test suites that can be run and these are defined in the enumerator ::zet_diag_type_t. The function
::zetSysmanDiagnosticsGet() will enumerate each available test suite and the function ::zetSysmanDiagnosticsGetProperties() can be used to determine
the type and name of each test suite (::zet_diag_properties_t.type and ::zet_diag_properties_t.type).

Each test suite contains one or more diagnostic tests. On some systems, it is possible to run only a subset of the tests. Use the function
::zetSysmanDiagnosticsGetProperties() and check that ::zet_diag_properties_t.haveTests is true to determine if this feature is available. If it is,
the function ::zetSysmanDiagnosticsGetTests() can be called to get the list of individual tests that can be run.

When running diagnostics for a test suite using ::zetSysmanDiagnosticsRunTests(), it is possible to specify the start and index of tests in the suite.
Setting to ::ZET_DIAG_FIRST_TEST_INDEX and ::ZET_DIAG_LAST_TEST_INDEX will run all tests in the suite. If it is possible to run a subset of tests,
specify the index of the start test and the end test - all tests that have an index in this range will be run.

The table below summaries all the diagnostic management functions:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanDiagnosticsGet()           | Get handles to the available diagnostic test suites that can be run. |
| ::zetSysmanDiagnosticsGetProperties() | Get information about a test suite - type, name, location and if individual tests can be run. |
| ::zetSysmanDiagnosticsGetTests()      | Get list of individual diagnostic tests that can be run. |
| ::zetSysmanDiagnosticsRunTests()      | Run either all or individual diagnostic tests. |

The pseudo code below shows how to discover all test suites and the tests in each:

```c
function ListDiagnosticTests(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numTestSuites
    if ((zetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, NULL) == ZE_RESULT_SUCCESS))
        zet_sysman_diag_handle_t* phTestSuites =
            allocate_memory(numTestSuites * sizeof(zet_sysman_diag_handle_t))
        if (zetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, phTestSuites) == ZE_RESULT_SUCCESS)
            for (suiteIndex = 0 .. numTestSuites-1)
                uint32_t numTests = 0
                zet_diag_test_t* pTests
                zet_diag_properties_t suiteProps
                if (zetSysmanDiagnosticsGetProperties(phTestSuites[suiteIndex], &suiteProps) != ZE_RESULT_SUCCESS)
                    next_loop(suiteIndex)
                output("Diagnostic test suite %s:", suiteProps.name)
                if (!suiteProps.haveTests)
                    output("    There are no individual tests that can be selected.")
                    next_loop(suiteIndex)
                if (zetSysmanDiagnosticsGetTests(phTestSuites[suiteIndex], &numTests, NULL) != ZE_RESULT_SUCCESS)
                    output("    Problem getting list of individual tests.")
                    next_loop(suiteIndex)
                pTests = allocate_memory(numTests * sizeof(zet_diag_test_t*))
                if (zetSysmanDiagnosticsGetTests(phTestSuites[suiteIndex], &numTests, pTests) != ZE_RESULT_SUCCESS)
                    output("    Problem getting list of individual tests.")
                    next_loop(suiteIndex)
                for (i = 0 .. numTests-1)
                    output("    Test %u: %s", pTests[i].index, pTests[i].name)
	free_memory(...)
```

## <a name="evd">Events</a>
Events are a way to determine if changes have occurred on a device e.g. new RAS errors. An application registers the events that it wishes to receive
notification about and then it queries to receive notifications. The query can request a blocking wait - this will put the calling application thread
to sleep until new notifications are received.

For every device on which the application wants to receive events, it should perform the following actions:

1. Use ::zetSysmanEventGet() to get an event handler from the Sysman handle for the device.
2. Use ::zetSysmanEventSetConfig() to indicate which events it wants to listen to.
3. For each event, call the appropriate function to set conditions that will trigger the event.

Finally, the application calls ::zetSysmanEventListen() with a list of event handles that it wishes to listen for events on. A wait timeout is used
to request non-blocking operations (timeout = ::ZET_EVENT_WAIT_NONE) or blocking operations (timeout = ::ZET_EVENT_WAIT_INFINITE) or to return
after a specified amount of time even if no events have been received.

Once events have occurred, the application can call ::zetSysmanEventGetState() to determine the list of events that have been received
for each event handle. If events have been received, the application can use the function relevant to the event to determine the actual state.

The list of events is given in the table below. For each event, the corresponding configuration and state functions are shown. Where a
configuration function is not shown, the event is generated automatically; where a configuration function is shown, it must be called to
enable the event and/or provide threshold conditions.

| Event                                             | Trigger                                               | Configuration function                | State function                    |
| :---                                              | :---                                                  | :---                                  | :---                              |
| ::ZET_SYSMAN_EVENT_TYPE_DEVICE_RESET             | Device is about to be reset by the driver             |                                       |                                   |
| ::ZET_SYSMAN_EVENT_TYPE_DEVICE_SLEEP_STATE_ENTER | Device is about to enter a deep sleep state           |                                       |                                   |
| ::ZET_SYSMAN_EVENT_TYPE_DEVICE_SLEEP_STATE_EXIT  | Device is exiting a deep sleep state                  |                                       |                                   |
| ::ZET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED           | Frequency starts being throttled                      |                                       | ::zetSysmanFrequencyGetState()   |
| ::ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED | Energy consumption threshold is reached               | ::zetSysmanPowerSetEnergyThreshold() |                                   |
| ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL            | Critical temperature is reached                       | ::zetSysmanTemperatureSetConfig()    | ::zetSysmanTemperatureGetState() |
| ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1          | Temperature crosses threshold 1                       | ::zetSysmanTemperatureSetConfig()    | ::zetSysmanTemperatureGetState() |
| ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2          | Temperature crosses threshold 2                       | ::zetSysmanTemperatureSetConfig()    | ::zetSysmanTemperatureGetState() |
| ::ZET_SYSMAN_EVENT_TYPE_MEM_HEALTH               | Health of device memory changes                       |                                       | ::zetSysmanMemoryGetState()      |
| ::ZET_SYSMAN_EVENT_TYPE_FABRIC_PORT_HEALTH       | Health of fabric ports change                         |                                       | ::zetSysmanFabricPortGetState()  |
| ::ZET_SYSMAN_EVENT_TYPE_PCI_LINK_HEALTH          | Health of the PCI link to the host                    |                                       | ::zetSysmanPciGetState()         |
| ::ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS   | Accerlator RAS correctable errors cross thresholds    | ::zetSysmanRasSetConfig()            | ::zetSysmanRasGetState()         |
| ::ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS | Accelerator RAS uncorrectable errors cross thresholds | ::zetSysmanRasSetConfig()            | ::zetSysmanRasGetState()         |

The call to ::zetSysmanEventListen() requires the driver handle. The list of event handles must only be for devices that have been enumerated
from that driver, otherwise and error will be returned. If the application is managing devices from multiple drivers, it will need to call this
function separately for each driver.

The table below summaries all the event management functions:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanEventGet()                 | Get the event handle for a specific Sysman device. |
| ::zetSysmanEventGetConfig()           | Get the current list of events for a given event handle that have been registered. |
| ::zetSysmanEventSetConfig()           | Set the events that should be registered on a given event handle. |
| ::zetSysmanEventGetState()            | Get the list of events that have been received for a given event handle. |
| ::zetSysmanEventListen()              | Wait for events to arrive for a given list of event handles. |

The pseudo code below shows how to configure all temperature sensors to trigger an event when the temperature exceeds a specified threshold
or when the critical temperature is reached.

```c
function WaitForExcessTemperatureEvent(zet_driver_handle_t hDriver, double tempLimit)
{
	# This will contain the number of event handles (devices) that we will listen for events from
    var numEventHandles = 0

    # Get list of all devices under this driver
    uint32_t deviceCount = 0
    zeDeviceGet(hDriver, &deviceCount, nullptr)
	# Allocate memory for all device handles
    ze_device_handle_t* phDevices =
		allocate_memory(deviceCount * sizeof(ze_device_handle_t))
	# Allocate memory for the event handle for each device
    zet_sysman_event_handle_t* phEvents =
	    allocate_memory(deviceCount * sizeof(zet_sysman_event_handle_t))
	# Allocate memory for the event handles that we will actually listen to
    zet_sysman_event_handle_t* phListenEvents =
	    allocate_memory(deviceCount * sizeof(zet_sysman_event_handle_t))
	# Allocate memory so that we can map an event handle in phListenEvent to the device handle
    uint32_t* pListenDeviceIndex = allocate_memory(deviceCount * sizeof(uint32_t))

	# Get all device handles
    zeDeviceGet(hDriver, &deviceCount, phDevices)
    for(devIndex = 0 .. deviceCount-1)
		# Get Sysman handle for the device
        zet_sysman_handle_t hSysmanDevice
        if (zetSysmanGet(phDevices[devIndex], ZET_SYSMAN_VERSION_CURRENT, &hSysmanDevice)
		    != ZE_RESULT_SUCCESS)
                next_loop(devIndex)

		# Get event handle for this device
        if (zetSysmanEventGet(hSysmanDevice, &phEvents[devIndex]) != ZE_RESULT_SUCCESS)
            next_loop(devIndex)

		# Get handles to all temperature sensors
        uint32_t numTempSensors = 0
        if (zetSysmanTemperatureGet(hSysmanDevice, &numTempSensors, NULL) != ZE_RESULT_SUCCESS)
            next_loop(devIndex)
        zet_sysman_temp_handle_t* allTempSensors
            allocate_memory(deviceCount * sizeof(zet_sysman_temp_handle_t))
        if (zetSysmanTemperatureGet(hSysmanDevice, &numTempSensors, allTempSensors) == ZE_RESULT_SUCCESS)
            # Configure each temperature sensor to trigger a critical event and a threshold1 event
			var numConfiguredTempSensors = 0
            for (tempIndex = 0 .. numTempSensors-1)
                if (zetSysmanTemperatureGetConfig(allTempSensors[tempIndex], &config) != ZE_RESULT_SUCCESS)
                    next_loop(tempIndex)
				zet_temp_config_t config
                config.enableCritical = true
                config.threshold1.enableHighToLow = false
                config.threshold1.enableLowToHigh = true
                config.threshold1.threshold = tempLimit
                config.threshold2.enableHighToLow = false
                config.threshold2.enableLowToHigh = false
                if (zetSysmanTemperatureSetConfig(allTempSensors[tempIndex], &config) == ZE_RESULT_SUCCESS)
                    numConfiguredTempSensors++

		# If we configured any sensors to generate events, we can now register to receive on this device
        if (numConfiguredTempSensors)
            zet_event_config_t eventConfig
            eventConfig.registered =
			    ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL | ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1
            if (zetSysmanEventSetConfig(phEvents[devIndex], &eventConfig) == ZE_RESULT_SUCCESS)
                phListenEvents[numEventHandles] = phEvents[devIndex]
                pListenDeviceIndex[numEventHandles] = devIndex
                numEventHandles++

    # If we registered to receive events on any devices, start listening now
    if (numEventHandles)
        # Block until we receive events
        uint32_t events
        if (zetSysmanEventListen(hDriver, ZET_EVENT_WAIT_INFINITE, deviceCount, phListenEvents, &events)
		    == ZE_RESULT_SUCCESS)
                for (evtIndex .. numEventHandles)
                    if (zetSysmanEventGetState(phListenEvents[evtIndex], true, &events)
					    != ZE_RESULT_SUCCESS)
                            next_loop(evtIndex)
                    if (events & ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL)
                        output("Device %u: Went above the critical temperature.",
						    pListenDeviceIndex[evtIndex])
                    else if (events & ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1)
                        output("Device %u: Went above the temperature threshold %f.",
						    pListenDeviceIndex[evtIndex], tempLimit)

	free_memory(...)
```

# <a name="se">Security</a>

## <a name="sel">Linux</a>
The default security provided by the accelerator driver is to permit querying and controlling of system resources to the UNIX user **root**, querying
only for users that are members of the UNIX group **root** and no access to any other user. Some queries are permitted from any user (e.g requesting
current frequency, checking standby state).

It is the responsibility of the Linux distribution or the systems administrator to relax or tighten these permissions. This is typically done
by adding udev daemon rules. For example, many distributions of Linux have the following rule:

```c
root	video	/dev/dri/card0
``` 

This will permit all users in the UNIX group **video** to query information about system resources. In order to open up control access to users
of the video group, udev rules need to be added for each relevant control. For example, to permit someone in the video group to disable standby,
the following udev daemon rule would be needed:

```c
chmod g+w /sys/class/drm/card0/rc6_enable
```

The full list of sysfs files used by the API are described in the table below. For each file, the list of affected API functions is given.

| sysfs file                            | Description | Functions  |
| :---                                  | :---      | :---        |
| /sys/class/drm/card0/rc6_enable       | Used to enable/disable standby. | ::zetSysmanStandbyGet()<br/>::zetSysmanStandbyGetProperties()<br />::zetSysmanStandbyGetMode()<br />::zetSysmanStandbySetMode()<br />|
| TBD | In development | TBD |


## <a name="sew">Windows</a>
At this time, Level0 Sysman does not support Windows.


## <a name="set">Privileged telemetry</a>
Certain telemetry makes a system vulnerable to side-channel attacks. By default, these will only be available to the administrator user on the
system. It is up to the administrator to relax those requirements, as described in the preceeding sections. This is the case for the following API
calls:

| Function                              | Description |
| :---                                  | :---        |
| ::zetSysmanPciGetStats()             | Access to total PCI thoughtput and number of packets can reveal useful information about the workload |
| ::zetSysmanMemoryGetBandwidth()      | Access to realtime device local memory bandwidth can reveal useful information about the workload |
| ::zetSysmanFabricPortGetThroughput() | Access to realtime fabric data bandwidth can reveal useful information about the workload |


## <a name="sec">Privileged controls</a>
Certain controls can be used in denial-of-service attacks. By default, these will only be available to the administrator user on the
system. It is up to the administrator to relax those requirements, as described in the preceeding sections. This is the case for the following API
calls:

| Function                              | Description |
| :---                                  | :---        |
| ::zetSysmanDeviceReset()             | Device resets cause loss of data for running workloads. |
| ::zetSysmanFirmwareGet()             | All firmware operations must be handled with care. |
| ::zetSysmanFirmwareGetProperties()   | All firmware operations must be handled with care. |
| ::zetSysmanFirmwareGetChecksum()     | All firmware operations must be handled with care. |
| ::zetSysmanFirmwareFlash()           | All firmware operations must be handled with care. |
| ::zetSysmanFabricPortSetConfig()     | Putting fabric ports offline can distrupt workloads, causing uncorrectable errors. |
| ::zetSysmanDiagnosticsRunTests()     | Diagnostics take a device offline. |


## <a name="sev">Virtualization</a>
In virtualization environments, only the host is permitted to access any features of the API. Attempts to use the API in virtual machines will
fail.


## <a name="sef">Function summary</a>
The table below summarizes the default permissions for each API function:

| Function                                              | Administrator access | Group access         | Other access         | Virtual machine      |
| :---                                                  | :---                 | :---                 | :---                 | :---                 |
| ::zetSysmanDeviceGetProperties()                     | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanDeviceGetRepairStatus()                   | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanSchedulerGetCurrentMode()                 | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanSchedulerGetTimeoutModeProperties()       | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanSchedulerGetTimesliceModeProperties()     | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanSchedulerSetTimeoutMode()                 | read-write           | read-write           | read-only            | no-access            |
| ::zetSysmanSchedulerSetTimesliceMode()               | read-write           | read-write           | read-only            | no-access            |
| ::zetSysmanSchedulerSetExclusiveMode()               | read-write           | read-write           | read-only            | no-access            |
| ::zetSysmanSchedulerSetComputeUnitDebugMode()        | read-write           | read-write           | read-only            | no-access            |
| ::zetSysmanDeviceReset()                             | read-write           | no-access            | no-access            | no-access            |
| ::zetSysmanPciGetProperties()                        | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanPciGetState()                             | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanPciGetBarProperties()                     | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanPciGetStats()                             | read-only            | no-access            | no-access            | no-access            |
| ::zetSysmanPowerGet()                                | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanPowerGetProperties()                      | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanPowerGetEnergyCounter()                   | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanPowerGetEnergyThreshold()                 | read-only            | read-only            | no-access            | no-access            |
| ::zetSysmanPowerSetEnergyThreshold()                 | read-write           | read-write           | no-access            | no-access            |
| ::zetSysmanPowerGetLimits()                          | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanPowerSetLimits()                          | read-write           | read-write           | read-only            | no-access            |
| ::zetSysmanFrequencyGet()                            | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFrequencyGetProperties()                  | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFrequencyGetAvailableClocks()             | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFrequencyGetRange()                       | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFrequencySetRange()                       | read-write           | read-write           | read-only            | no-access            |
| ::zetSysmanFrequencyGetState()                       | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFrequencyGetThrottleTime()                | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFrequencyOcGetCapabilities()              | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFrequencyOcGetConfig()                    | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFrequencyOcSetConfig()                    | read-write           | no-access            | no-access            | no-access            |
| ::zetSysmanFrequencyOcGetIccMax()                    | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFrequencyOcSetIccMax()                    | read-write           | no-access            | no-access            | no-access            |
| ::zetSysmanFrequencyOcGetTjMax()                     | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFrequencyOcSetTjMax()                     | read-write           | no-access            | no-access            | no-access            |
| ::zetSysmanEngineGet()                               | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanEngineGetProperties()                     | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanEngineGetActivity()                       | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanStandbyGet()                              | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanStandbyGetProperties()                    | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanStandbyGetMode()                          | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanStandbySetMode()                          | read-write           | read-write           | read-only            | no-access            |
| ::zetSysmanFirmwareGet()                             | read-only            | no-access            | no-access            | no-access            |
| ::zetSysmanFirmwareGetProperties()                   | read-only            | no-access            | no-access            | no-access            |
| ::zetSysmanFirmwareGetChecksum()                     | read-only            | no-access            | no-access            | no-access            |
| ::zetSysmanFirmwareFlash()                           | read-write           | no-access            | no-access            | no-access            |
| ::zetSysmanMemoryGet()                               | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanMemoryGetProperties()                     | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanMemoryGetBandwidth()                      | read-only            | no-access            | no-access            | no-access            |
| ::zetSysmanMemoryGetState()                          | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFabricPortGet()                           | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFabricPortGetProperties()                 | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFabricPortGetLinkType()                   | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFabricPortGetConfig()                     | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFabricPortSetConfig()                     | read-write           | no-access            | no-access            | no-access            |
| ::zetSysmanFabricPortGetState()                      | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFabricPortGetThroughput()                 | read-only            | no-access            | no-access            | no-access            |
| ::zetSysmanTemperatureGet()                          | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanTemperatureGetProperties()                | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanTemperatureGetConfig()                    | read-only            | read-only            | no-access            | no-access            |
| ::zetSysmanTemperatureSetConfig()                    | read-write           | read-write           | no-access            | no-access            |
| ::zetSysmanTemperatureGetState()                     | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanPsuGet()                                  | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanPsuGetProperties()                        | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanPsuGetState()                             | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFanGet()                                  | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFanGetProperties()                        | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFanGetConfig()                            | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanFanSetConfig()                            | read-write           | read-write           | read-only            | no-access            |
| ::zetSysmanFanGetState()                             | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanLedGet()                                  | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanLedGetProperties()                        | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanLedGetState()                             | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanLedSetState()                             | read-write           | read-write           | read-only            | no-access            |
| ::zetSysmanRasGet()                                  | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanRasGetProperties()                        | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanRasGetConfig()                            | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanRasSetConfig()                            | read-write           | read-write           | no-access            | no-access            |
| ::zetSysmanRasGetState()                             | read-write           | read-write           | read-only            | no-access            |
| ::zetSysmanEventGet                                  | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanEventGetConfig()                          | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanEventSetConfig()                          | read-write           | read-write           | read-write           | no-access            |
| ::zetSysmanEventGetState()                           | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanEventListen()                             | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanDiagnosticsGet()                          | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanDiagnosticsGetProperties()                | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanDiagnosticsGetTests()                     | read-only            | read-only            | read-only            | no-access            |
| ::zetSysmanDiagnosticsRunTests()                     | read-write           | no-access            | no-access            | no-access            |

