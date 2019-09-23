${"#"} Programming Guide (Sysman)
<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    t=tags['$t']
    T=t.upper()
%>

[DO NOT EDIT]: # "generated from /scripts/tools/SYSMAN.md"

The following documents the high-level programming models and guidelines.


${"##"} Table of Contents
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
        + [Scheduler operations](#glos)
        + [PCI properties](#glop)
    + [Operations on power domains](#pwr)
	+ [Operations on frequency domains](#frq)
	+ [Operations on engine groups](#eng)
	+ [Operations on standby domains](#sby)
	+ [Operations on firmware](#fmw)
	+ [Querying memory modules](#mem)
	+ [Operations on connectivity switches and ports](#con)
	+ [Querying temperature](#tmp)
	+ [Operations on power supplies](#psu)
	+ [Operations on fans](#fan)
	+ [Operations on LEDs](#led)
	+ [Querying RAS errors](#ras)
	+ [Performing diagnostics](#dag)
    + [Events](#evd)


${"#"} <a name="in">Introduction</a>
Sysman is the System Resource Management Interface (SMI) used to monitor and control the power and performance of accelerator devices.

${"#"} <a name="ho">High-level overview</a>

${"##"} <a name="ini">Initialization</a>
An application wishing to manage power and performance for devices first needs to use the Level0 Core API to enumerate through available accelerator
devices in the system and select those of interest.

For each selected device handle, applications use the function ::${t}SysmanGet() to get an **SMI handle** to manage system resources of the device.

![Object hierarchy](../images/tools_sysman_object_hierarchy.png?raw=true) 

There is a unique handle for each device. Multiple threads can use the handle. If concurrent accesses are made to the same device property through
the handle, the last request wins.

The code example below shows how to enumerate the GPU devices in the system and create SMI handles for them:

```c
int gNumDevices = 0;    // Global

int ListDevices(xe_device_group_handle_t hDeviceGroup); // Forward declaration

int main( int argc, char *argv[] )
{
    int ret = -1;
    if ( (xeInit(XE_INIT_FLAG_NONE) != XE_RESULT_SUCCESS) ||
         (xetInit(XE_INIT_FLAG_NONE) != XE_RESULT_SUCCESS) )
    {
        fprintf(stderr, "Can't initialize the API.\n");
        ret = 1;
    }
    else
    {
        // Discover all the device groups and devices
        uint32_t groupCount = 0;
        xeDeviceGroupGet(&groupCount, nullptr);
        xe_device_group_handle_t* allDeviceGroups = (xe_device_group_handle_t*)
            malloc(groupCount * sizeof(xe_device_group_handle_t));
        xeDeviceGroupGet(&groupCount, allDeviceGroups);
        // Find the first GPU device group
        xe_device_group_handle_t hDeviceGroup = nullptr;
        for(uint32_t i = 0; i < groupCount; ++i)
        {
            xe_device_properties_t device_properties;
            xeDeviceGroupGetDeviceProperties(allDeviceGroups[i], &device_properties);
            if(XE_DEVICE_TYPE_GPU == device_properties.type)
            {
                if ((ret = ListDevices(allDeviceGroups[i])) != 0)
                {
                    break;
                }
            }
        }

        free(allDeviceGroups);
    }

    if (gNumDevices == 0)
    {
        fprintf(stdout, "No managed devices found.\n");
    }

    return ret;
}

int ListDevices(xe_device_group_handle_t hDeviceGroup)
{
    int ret = 0;
    uint32_t deviceCount = 0;
    if (xeDeviceGet(hDeviceGroup, &deviceCount, nullptr) == XE_RESULT_SUCCESS)
    {
        if (deviceCount)
        {
            xe_device_handle_t* allDevices = (xe_device_handle_t*)
                malloc(deviceCount * sizeof(xe_device_handle_t));
            xeDeviceGet(hDeviceGroup, &deviceCount, allDevices);

            for (uint32_t i = 0; i < deviceCount; ++i)
            {
                xet_sysman_handle_t hSysmanDevice;
                xe_result_t res = xetSysmanGet(allDevices[i], XET_SYSMAN_VERSION_CURRENT, &hSysmanDevice);
                if (res == XE_RESULT_SUCCESS)
                {
                    gNumDevices++;

                    fprintf(stdout, "Device %d\n", gNumDevices);

                    ShowDeviceInfo(hSysmanDevice);
                }
                else
                {
                    fprintf(stderr, "ERROR: Can't initialize system resource management for this device.\n");
                    ret++;
                }
            }

            free(allDevices);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Couldn't get list of devices in a device group.\n");
        ret = 1;
    }

    return ret;
}
```

${"##"} <a name="gdm">Global device management</a>
The following operations are provided to access overall device information and control aspects of the entire device:

- Get device UUID, deviceID, number of sub-devices
- Get Brand/model/vendor name
- Get/set scheduler mode and properties
- Reset device
- Query if the device has been repaired
- PCI information:
    - Get configured bars
    - Get maximum supported bandwidth
    - Query current speed (GEN/no. lanes)
    - Query current throughput
    - Query packet retry counters

The full list of available functions is described [below](#glo).

${"##"} <a name="dcm">Device component management</a>
Aside from management of the global properties of a device, there are many device components that can be managed to change the performance and/or power
configuration of the device. Similar components are broken into **classes** and each class has a set of operations that can be performed on them.

For example, devices typically have one or more frequency domains. The SMI API exposes a class for frequency and an enumeration of all frequency domains
that can be managed.

The table below summarizes the classes that provide device queries and an example list of components that would be enumerated for a device with two
sub-devices. The table shows the operations (queries) that will be provided for all components in each class.

| Class                 | Components    | Operations |
| :---                  | :---          | :---        |
| [Power](#pwr)         | Package: power<br />Sub-device 0: Total power<br />Sub-device 1: Total power | Get energy consumption |
| [Frequency](#frq)     | Sub-device 0: GPU frequency<br />Sub-device 0: HBM frequency<br />Sub-device 1: GPU frequency<br />Sub-device 1: HBM frequency | List available frequencies<br />Set frequency range<br />Get frequencies<br />Get throttle reasons<br />Get throttle time |
| [Engines](#eng)       | Sub-device 0: All engines<br />Sub-device 0: Compute engines<br />Sub-device 0: Media engines<br />Sub-device 1: All engines<br />Sub-device 1: Compute engines<br />Sub-device 1: Media engines | Get busy time |
| [Firmware](#fmw)      | Sub-device 0: Enumerates each firmware<br />Sub-device 1: Enumerates each firmware | Get firmware  name and version<br />Verify firmware checksum |
| [Mermory](#mem)       | Sub-device 0: HBM memory<br />Sub-device 1: HBM memory | Get maximum supported bandwidth<br />Get current allocation size<br />Get current bandwidth |
| [Link Switch](#con)   | Sub-device 0: One connectivity switch<br />Sub-device 1: One connectivity switch | Get state (enabled/disabled) | 
| [Port Switch](#con)   | Sub-device 0: Enumerates each port in a connectivity switch<br />Sub-device 1: Enumerates each port in a connectivity switch | Get max supported bandwidth per port<br />Get per-port state (connected, remote device/port, max supported bandwidth)<br />Get per-port current bandwidth<br />Get per-port stats (replay counters) | 
| [Temperature](#tmp)   | Package: temperature<br />Sub-device 0: GPU temperature<br />Sub-device 0: HBM temperature<br />Sub-device 1: GPU temperature<br />Sub-device 1: HBM temperature | Get current temperature sensor reading |
| [RAS](#ras)           | Sub-device 0: One set of RAS error counters<br />Sub-device 1: One set of RAS error counters | Read RAS total correctable and uncorrectable error counter.<br />Read breakdown of errors by category:<br />- no. resets<br />- no. programming errors<br />- no. driver errors<br />- no. compute errors<br />- no. cache errors<br />- no. memory errors<br />- no. PCI errors<br />- no. switch errors<br />- no. display errors<br />- no. non-compute errors | 
| [Diagnostics](#dag)   | Package: SCAN test suite<br />Package: ARRAY test suite | Get list of all diagnostics tests in the test suite | 

The table below summarizes the classes that provide device controls and an example list of components that would be enumerated for a device with two
sub-devices. The table shows the operations (controls) that will be provided for all components in each class.

| Class                 | Components    | Operations |
| :---                  | :---          | :---        |
| [Power](#pwr)         | Package: power | Set sustained power limit<br />Set burst power limit<br />Set peak power limit |
| [Frequency](#frq)     | Sub-device 0: GPU frequency<br />Sub-device 0: HBM frequency<br />Sub-device 1: GPU frequency<br />Sub-device 1: HBM frequency | Set frequency range |
| [Standby](#sby)       | Sub-device 0: Control entire sub-device<br />Sub-device 1: Control entire sub-device | Disable opportunistic standby |
| [Firmware](#fmw)      | Sub-device 0: Enumerates each firmware<br />Sub-device 1: Enumerates each firmware | Flash new firmware |
| [Link Switch](#con)   | Sub-device 0: One connectivity switch<br />Sub-device 1: One connectivity switch | Enable/disable the connectivity switch | 
| [Diagnostics](#con)   | SCAN test suite<br />ARRAY test suite | Run all or a subset of diagnostic tests in the test suite | 

${"##"} <a name="dce">Device component enumeration</a>
The SMI API provides functions to enumerate all components in a class that can be managed.

For example, there is a frequency class which is used to control the frequency of different parts of the device. On most devices, the enumerator
will provide two handles, one to control the GPU frequency and one to enumerate the HBM frequency. This is illustrated in the figure below:

![Frequency flow](../images/tools_sysman_freq_flow.png?raw=true) 

In the C API, each class is associated with a unique handle type (e.g. ::${t}_sysman_freq_handle_t refers to a frequency component).
In the C++ API, each class is a C++ class (e.g. An instance of the class ::${t}::SysmanFrequency refers to a frequency component).

The example code below shows how to use the SMI API to enumerate all GPU frequency components and fix each to a specific frequency:

```c
void FixGpuFrequency(xet_sysman_handle_t hSysmanDevice, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((xetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == XE_RESULT_SUCCESS) && numFreqDomains)
    {
        xet_sysman_freq_handle_t* pFreqHandles = (xet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(xet_sysman_freq_handle_t));
        if (xetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == XE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                xet_freq_properties_t props;
                if (xetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == XE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == XET_FREQ_DOMAIN_GPU)
                    {
                        if (props.canControl)
                        {
                            xet_freq_range_t range;
                            range.min = FreqMHz;
                            range.max = FreqMHz;
                            if (xetSysmanFrequencySetRange(pFreqHandles[index], &range) != XE_RESULT_SUCCESS)
                            {
                                fprintf(stderr, "ERROR: Problem setting the frequency range for domain with index %u.\n", index);
                            }
                        }
                        else
                        {
                            fprintf(stderr, "ERROR: Can't control GPU frequency domain with index %u.\n", index);
                        }
                    }
                }
            }
        }
        free(pFreqHandles);
    }
}
```

${"##"} <a name="sdm">Sub-device management</a>
An SMI handle cannot be created for a sub-device - ::${t}SysmanGet() will return error ::${X}_RESULT_ERROR_UNSUPPORTED if a device handle for a 
sub-device is passed to this function. Instead, the enumerator for device components will return a list of components that are located in each
sub-device. Properties for each component will indicate in which sub-device it is located. If software wishing to manage components in only one
sub-device should filter the enumerated components using the sub-device ID (see ::${x}_device_properties_t.subdeviceId).

The figure below shows the frequency components that will be enumerated on a device with two sub-devices where each sub-device has a GPU and
HBM frequency control:

![Frequency flow](../images/tools_sysman_freq_subdevices.png?raw=true) 

The code below shows how to fix the GPU frequency on a specific sub-device (notice the additional sub-device check):

```c
void FixSubdeviceGpuFrequency(xet_sysman_handle_t hSysmanDevice, uint32_t subdeviceId, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((xetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == XE_RESULT_SUCCESS) && numFreqDomains)
    {
        xet_sysman_freq_handle_t* pFreqHandles = (xet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(xet_sysman_freq_handle_t));
        if (xetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == XE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                xet_freq_properties_t props;
                if (xetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == XE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == XET_FREQ_DOMAIN_GPU)
                    {
                        // Only control the GPU frequency domain for a specific sub-device
                        if (props.onSubdevice && (props.subdeviceId == subdeviceId))
                        {
                            if (props.canControl)
                            {
                                xet_freq_range_t range;
                                range.min = FreqMHz;
                                range.max = FreqMHz;
                                if (xetSysmanFrequencySetRange(pFreqHandles[index], &range) != XE_RESULT_SUCCESS)
                                {
                                    fprintf(stderr, "ERROR: Problem setting the frequency range for domain with index %u.\n", index);
                                }
                            }
                            else
                            {
                                fprintf(stderr, "ERROR: Can't control GPU frequency domain with index %u.\n", index);
                            }
                        }
                    }
                }
            }
        }
        free(pFreqHandles);
    }
}
```

${"##"} <a name="evt">Events</a>
Events are a way to determine if changes have occurred on a device e.g. new RAS errors without poll the SMI API. An application registers the events
that it wishes to receive notification about and then it listens for notifications. The application can choose to block when listening - this will put
the calling application thread to sleep until new notifications are received.

The API enables registering for events from multiple devices and listening for any events coming from any devices by using one function call.

One notifications have occurred, the application can use the query SMI interface functions to get more details.

The following events are provided:

- Any RAS errors have occurred

The full list of available functions for handling events is described [below](#evd).


${"#"} <a name="id">Interface details</a>

${"##"} <a name="glo">Global operations</a>

${"###"} <a name="glod">Device properties</a>
The following operations permit getting properties about the entire device:

| Function                                                   | Description |
| :---                                                       | :---        |
| ::${t}SysmanDeviceGetProperties()                          | Get static device properties -  device UUID, sub-device ID, device brand/model/vendor strings |
| ::${t}SysmanDeviceWasRepaired()                            | Performs a warm reset of the device which includes unloading the driver. |

The example below shows how to display general information about a device:

```c
void ShowDeviceInfo(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_properties_t devProps;
    xe_bool_t repaired;
    if (xetSysmanDeviceGetProperties(hSysmanDevice, &devProps) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    UUID:           %s\n", devProps.core.uuid.id);
        fprintf(stdout, "    #subdevices:    %u\n", devProps.numSubdevices);
        fprintf(stdout, "    brand:          %s\n", devProps.brandName);
        fprintf(stdout, "    model:          %s\n", devProps.modelName);
        fprintf(stdout, "    driver timeout: disabled\n");
    }
    if (xetSysmanDeviceWasRepaired(hSysmanDevice, &repaired) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Was repaired:   %s\n", repaired ? "yes" : "no");
    }
}
```

${"###"} <a name="glos">Scheduler operations</a>
On some devices, it is possible to change the way the scheduler executes workloads. To find out if this is supported, execute the function
::${t}SysmanSchedulerGetCurrentMode() and check that it does not return an error.

The available scheduler operating modes are given by the enum ::${t}_sched_mode_t:

| Scheduler mode                     | Description |
| :---                               | :---        |
| ::${T}_SCHED_MODE_TIMEOUT          | This mode is optimized for multiple applications or contexts submitting work to the hardware. When higher priority work arrives, the scheduler attempts to pause the current executing work within some timeout interval, then submits the other work.<br />It is possible to configure (::${t}_sched_timeout_properties_t) the watchdog timeout which controls the maximum time the scheduler will wait for a workload to complete a batch of work or yield to other applications before it is terminated.<br />If the watchdog timeout is set to ::${T}_SCHED_WATCHDOG_DISABLE, the scheduler enforces no fairness. This means that if there is other work to execute, the scheduler will try to submit it but will not terminate an executing process that does not complete quickly. |
| ::${T}_SCHED_MODE_TIMESLICE        | This mode is optimized to provide fair sharing of hardware execution time between multiple contexts submitting work to the hardware concurrently.<br />It is possible to configure (::${t}_sched_timeslice_properties_t) the timeslice interval and the amount of time the scheduler will wait for work to yield to another application before it is terminated. |
| ::${T}_SCHED_MODE_EXCLUSIVE        | This mode is optimized for single application/context use-cases. It permits a context to run indefinitely on the hardware without being preempted or terminated. All pending work for other contexts must wait until the running context completes with no further submitted work. |
| ::${T}_SCHED_MODE_SINGLE_CMDQUEUE  | This mode is optimized for application debug. It ensures that only one command queue can execute work on the hardware at a given time. Work is permitted to run as long as needed without enforcing any scheduler fairness policies. |

The following functions are available for changing the behavior of the scheduler:

| Function                                             | Description |
| :---                                                 | :---        |
| ::${t}SysmanSchedulerGetCurrentMode()                | Get the current scheduler mode (timeout, timeslice, exclusive, single command queue) |
| ::${t}SysmanSchedulerGetTimeoutModeProperties()      | Get the settings for the timeout scheduler mode |
| ::${t}SysmanSchedulerGetTimesliceModeProperties()    | Get the settings for the timeslice scheduler mode |
| ::${t}SysmanSchedulerSetTimeoutMode                  | Change to timeout scheduler mode and/or change properties |
| ::${t}SysmanSchedulerSetTimesliceMode                | Change to timeslice scheduler mode and/or change properties |
| ::${t}SysmanSchedulerSetExclusiveMode                | Change to exclusive scheduler mode and/or change properties |
| ::${t}SysmanSchedulerSetSingleCmdQueueMode           | Change to single command queue scheduler mode and/or change properties |

The example below shows how to stop the scheduler enforcing fairness while permitting other work to attempt to run:

```c
void DisableSchedulerWatchdog(xet_sysman_handle_t hSysmanDevice)
{
    xe_result_t res;
    xet_sched_mode_t currentMode;
    res = xetSysmanSchedulerGetCurrentMode(hSysmanDevice, &currentMode);
    if (res == XE_RESULT_SUCCESS)
    {
        xe_bool_t requireReboot;
        xet_sched_timeout_properties_t props;
        props.watchdogTimeout = XET_SCHED_WATCHDOG_DISABLE;
        res = xetSysmanSchedulerSetTimeoutMode(hSysmanDevice, &props, &requireReboot);
        if (res == XE_RESULT_SUCCESS)
        {
            if (requireReboot)
            {
                fprintf(stderr, "WARNING: Reboot required to complete desired configuration.\n");
            }
            else
            {
                fprintf(stdout, "Schedule mode changed successfully.\n");
            }
        }
        else if(res == XE_RESULT_ERROR_UNSUPPORTED)
        {
            fprintf(stderr, "ERROR: The timeout scheduler mode is not supported on this device.\n");
        }
        else if(res == XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS)
        {
            fprintf(stderr, "ERROR: Don't have permissions to change the scheduler mode.\n");
        }
        else
        {
            fprintf(stderr, "ERROR: Problem calling the API to change the scheduler mode.\n");
        }
    }
    else if(res == XE_RESULT_ERROR_UNSUPPORTED)
    {
        fprintf(stderr, "ERROR: Scheduler modes are not supported on this device.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem calling the API.\n");
    }
}
```

${"###"} <a name="glop">PCI properties</a>
The following functions permit getting data about the PCI endpoint for the device:

| Function                                                   | Description |
| :---                                                       | :---        |
| ::${t}SysmanPciGetProperties()                             | Get static properties for the PCI port - BDF address, number of bars, maximum supported speed |
| ::${t}SysmanPciGetState()                                  | Get current PCI port speed (number of lanes, generation) |
| ::${t}SysmanPciGetBarProperties()                          | Get information about each configured PCI bar |
| ::${t}SysmanPciGetThroughput()                             | Get current PCI throughput |
| ::${t}SysmanPciGetStats()                                  | Get PCI statistics - total packets, number of packet replays |

The example below shows how to output the PCI BDF address:

```c
void ShowPciInfo(xet_sysman_handle_t hSysmanDevice)
{
    xet_pci_properties_t pciProps;
    if (xetSysmanPciGetProperties(hSysmanDevice, &pciProps) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    PCI address:        %04u:%02u:%02u.%u\n", pciProps.address.domain, pciProps.address.bus, pciProps.address.device, pciProps.address.function);
    }
}
```

${"##"} <a name="pwr">Operations on power domains</a>
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
| Burst     | 2ms           | Punit tracks the 2ms weighted moving average of power. When this exceeds a programmable threshold, the Punit starts throttling frequencies/voltages. The threshold is referred to as PL2 - Power Limit 2 - or burst power. |
| Sustained | 28sec         | Punit tracks the 28sec weighted moving average of power. When this exceeds a programmable threshold, the Punit throttles frequencies/voltages. The threshold is referred to as PL1 - Power Limit 1 - or sustained power.   |

Peak power limit is generally greater than the burst power limit which is generally greater than the sustained power limit. The default factory values
are tuned assuming the device is operating at normal temperatures running significant workloads:

- The peak power limit is tuned to avoid tripping the PSU over-current signal for all but the most intensive compute workloads. Most workloads should
be able to run at maximum frequencies without hitting this condition.
- The burst power limit permits most workloads to run at maximum frequencies for short periods.
- The sustained power limit will be triggered if high frequencies are requested for lengthy periods (28sec) and the frequencies will be throttled
if the high requests and utilization of the device continue.

The following functions are provided to manage the power of the device:

| Function                            | Description |
| :---                                | :---        |
| ::${t}SysmanPowerGet()              | Enumerate the power domains. |
| ::${t}SysmanPowerGetProperties()    | Get the maximum power limit that can be specified when changing the power limits of a specific power domain. |
| ::${t}SysmanPowerGetEnergyCounter() | Read the energy consumption of the specific domain. |
| ::${t}SysmanPowerGetLimits()        | Get the sustained/burst/peak power limits for the specific power domain. |
| ::${t}SysmanPowerSetLimits()        | Set the sustained/burst/peak power limits for the specific power domain. |

The example below shows how to output information about each power domain on a device:

```c
// Forward declaration
void ShowPowerLimits(xet_sysman_pwr_handle_t hPower);

void ShowPowerDomains(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numPowerDomains;
    if (xetSysmanPowerGet(hSysmanDevice, &numPowerDomains, NULL) == XE_RESULT_SUCCESS)
    {
        xet_sysman_pwr_handle_t* phPower =
            (xet_sysman_pwr_handle_t*)malloc(numPowerDomains * sizeof(xet_sysman_pwr_handle_t));
        if (xetSysmanPowerGet(hSysmanDevice, &numPowerDomains, phPower) == XE_RESULT_SUCCESS)
        {
            for (uint32_t pwrIndex = 0; pwrIndex < numPowerDomains; pwrIndex++)
            {
                xet_power_properties_t props;
                if (xetSysmanPowerGetProperties(phPower[pwrIndex], &props) == XE_RESULT_SUCCESS)
                {
                    if (props.onSubdevice)
                    {
                        fprintf(stdout, "Sub-device %u power:\n", props.subdeviceId);
                        fprintf(stdout, "    Can control: %s\n", props.canControl ? "yes" : "no");
                        ShowPowerLimits(phPower[pwrIndex]);
                    }
                    else
                    {
                        fprintf(stdout, "Total package power:\n");
                        fprintf(stdout, "    Can control: %s\n", props.canControl ? "yes" : "no");
                        ShowPowerLimits(phPower[pwrIndex]);
                    }
                }
            }
        }
        free(phPower);
    }
}

void ShowPowerLimits(xet_sysman_pwr_handle_t hPower)
{
    xet_power_sustained_limit_t sustainedLimits;
    xet_power_burst_limit_t burstLimits;
    xet_power_peak_limit_t peakLimits;
    if (xetSysmanPowerGetLimits(hPower, &sustainedLimits, &burstLimits, &peakLimits) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Power limits\n");
        if (sustainedLimits.enabled)
        {
            fprintf(stdout, "        Sustained: %.3f W %.3f sec\n",
                ((double)sustainedLimits.power) / 1000, ((double)sustainedLimits.interval) / 1000);
        }
        else
        {
            fprintf(stdout, "        Sustained: Disabled\n");
        }
        if (burstLimits.enabled)
        {
            fprintf(stdout, "        Burst:     %.3f\n", ((double)burstLimits.power) / 1000);
        }
        else
        {
            fprintf(stdout, "        Burst:     Disabled\n");
        }
        fprintf(stdout, "        Burst:     %.3f\n", ((double)peakLimits.power) / 1000);
    }
}
```

The next example shows how to output the average power. It assumes that the function is called regularly (say every 100ms).

```c
void ShowAveragePower(xet_sysman_handle_t hSysmanDevice, xet_power_energy_counter_t* pPrevEnergyCounter)
{
    xet_power_energy_counter_t newEnergyCounter;
    if (xetSysmanPowerGetEnergyCounter(hSysmanDevice, &newEnergyCounter) == XE_RESULT_SUCCESS)
    {
        uint64_t deltaTime = newEnergyCounter.timestamp - pPrevEnergyCounter->timestamp;
        if (deltaTime)
        {
            fprintf(stdout, "    Average power: %.3f W\n",
                ((double)(newEnergyCounter.energy - pPrevEnergyCounter->energy)) / ((double)deltaTime));
            *pPrevEnergyCounter = newEnergyCounter;
        }
    }
}
```

${"##"} <a name="frq">Operations on frequency domains</a>
The hardware manages frequencies to achieve a balance between best performance and power consumption. Most devices have one or more frequency domains.

The following functions are provided to manage the frequency domains on the device:

| Function                               | Description |
| :---                                   | :---        |
| ::${t}SysmanFrequencyGet()             | Enumerate all the frequency domains on the device and sub-devices. |
| ::${t}SysmanFrequencyGetProperties()   | Find out the part of the device (one of ::${t}_freq_domain_t) that is controlled by a frequency domain. |
| ::${t}SysmanFrequencyGetRange()        | Get the current min/max frequency between which the hardware can operate for a frequency domain. |
| ::${t}SysmanFrequencySetRange()        | Set the min/max frequency between which the hardware can operate for a frequency domain. |
| ::${t}SysmanFrequencyGetState()        | Get the current frequency request, actual frequency, TDP frequency and throttle reasons for a frequency domain. |
| ::${t}SysmanFrequencyGetThrottleTime() | Gets the amount of time a frequency domain has been throttled. |

It is only permitted to set the frequency range if the device property ::${t}_freq_properties_t.canControl is true for the specific frequency
domain.

By setting the min/max frequency range to the same value, software is effectively disabling the hardware controlled frequency and getting a fixed stable
frequency providing the Punit does not need to throttle due to excess power/heat. 

Based on the power/thermal conditions, the frequency requested by software or the hardware may not be respected. This situation can be determined
using the function ::${t}SysmanFrequencyGetState() which will indicate the current frequency request, the actual (resolved) frequency and other
frequency information that depends on the current conditions. If the actual frequency is below the requested frequency,
::${t}_freq_state_t.throttleReasons will provide the reasons why the frequency is being limited by the Punit.


${"##"} <a name="eng">Operations on engine groups</a>
It is possible to monitor the activity of one or engines combined into an **engine group**. A device can have multiple engine groups and the possible
types are defined in ::${t}_engine_group_t. The current engine groups supported are global activity across all engines, activity across all compute
accelerators and activity across all media accelerators.

By taking two snapshots of the activity counters, it is possible to calculate the average utilization of different parts of the device.

The following functions are provided:

| Function                               | Description |
| :---                                   | :---        |
| ::${t}SysmanEngineGet()                | Enumerate the engine groups that can be queried. |
| ::${t}SysmanEngineGetProperties()      | Get the properties of an engine group. This will return the type of engine group (one of ::${t}_engine_group_t) and on which sub-device the group is making measurements. |
| ::${t}SysmanEngineGetActivity()        | Returns the activity counters for an engine group. |


${"##"} <a name="sby">Operations on standby domains</a>
When a device is idle, it will enter a low-power state. Since exit from low-power states have associated latency, it can hurt performance. The
hardware attempts to stike a balance between saving power when there are large idle times between workloads submissions to the device and
keeping the device awake when idle because it has determined that new workload submissions are imminent.

A device can consist of one or more standby domains - the list of domains is given by ::${t}_standby_type_t.

The following functions can be used to control how the hardware promotes to standby states:

| Function                               | Description |
| :---                                   | :---        |
| ::${t}SysmanStandbyGet()               | Enumerate the standby domains. |
| ::${t}SysmanStandbyGetProperties()     | Get the properties of a standby domain. This will return the parts of the device that are affected by this domain (one of ::${t}_engine_group_t) and on which sub-device the domain is located. |
| ::${t}SysmanStandbyGetMode()           | Get the current promotion mode (one of ::${t}_standby_promo_mode_t) for a standby domain.|
| ::${t}SysmanStandbySetMode()           | Set the promotion mode (one of ::${t}_standby_promo_mode_t) for a standby domain. |


${"##"} <a name="fmw">Operations on firmwares</a>
The following functions are provided to manage firmwares on the device:

| Function                               | Description |
| :---                                   | :---        |
| ::${t}SysmanFirmwareGet()              | Enumerate all firmwares that can be managed on the device. |
| ::${t}SysmanFirmwareGetProperties()    | Find out the name and version of a firmware. |
| ::${t}SysmanFirmwareGetChecksum()      | Get the checksum for an installed firmware. |
| ::${t}SysmanFirmwareFlash()            | Flash a new firmware image. |

${"##"} <a name="mem">Querying memory modules</a>
The following functions provide access to information about the local memory modules on the device:

| Function                               | Description |
| :---                                   | :---        |
| ::${t}SysmanMemoryGet()                | Enumerate the memory modules. |
| ::${t}SysmanMemoryGetProperties()      | Find out the type of memory and maximum physical memory of a module. |
| ::${t}SysmanMemoryGetBandwidth()       | Returns memory bandwidth counters for a module. |
| ::${t}SysmanMemoryGetAllocated()       | Returns the currently allocated memory size for a module. |


${"##"} <a name="con">Operations on connectivity switches and ports</a>
A device is able to access memory and resources on a remote device using a high-speed data fabric rather than using the PCI bus. This is achieved through
a connectivity switch. If ::${t}SysmanLinkSwitchGet() returns one or more switches, high-speed connectivity to other devices is possible.

The following functions can be used to manage the switch:

| Function                               | Description |
| :---                                   | :---        |
| ::${t}SysmanLinkSwitchGet()            | Enumerate connectivity switches on the device. |
| ::${t}SysmanLinkSwitchGetProperties()  | Get static properties about the switch. |
| ::${t}SysmanLinkSwitchGetState()       | Get the current state of the switch (enabled/disabled). |
| ::${t}SysmanLinkSwitchSetState()       | Enables/disabled the switch. |
| ::${t}SysmanLinkSwitchGetPorts()       | Enumerate the ports on the switch. |

Each switch has one or more ports, each of which can be configured with a point-to-point connection to another port on another device's switch. A handle for
each port on the switch is obtained using the function ::${t}SysmanLinkSwitchGetPorts().

The following functions can be used to manage each connectivity port:

| ::${t}SysmanLinkPortGetProperties()    | Get the properties of a port on the switch - maximum supported bandwidth. |
| ::${t}SysmanLinkPortGetState()         | Get the current state of a port on the switch - connected, remote switch device/index/port, current maximum bandwidth. |
| ::${t}SysmanLinkPortGetThroughput()    | Get the throughput counters of a port on the switch. |
| ::${t}SysmanLinkPortGetStats()         | Gets telemetry counters of a port on the switch - number of replays. |

For devices with sub-devices, the switch is usually located in the sub-device. Given a device handle, ::${t}SysmanLinkSwitchGet() will
include the switches on each sub-device. In this case, ::${t}_link_switch_properties_t.onSubdevice will be set to true and
::${t}_link_switch_properties_t.subdeviceId will give the subdevice ID where that switch is located.

The example below shows how to get the state of all switches in the device and sub-devices:

```c
void ShowSwitchInfo(xet_sysman_link_switch_handle_t hSwitch)
{
    xet_link_switch_properties_t swprops;
    if (xetSysmanLinkSwitchGetProperties(hSwitch, &swprops) == XE_RESULT_SUCCESS)
    {
        xet_link_switch_state_t swstate;
        if (xetSysmanLinkSwitchGetState(hSwitch, &swstate) == XE_RESULT_SUCCESS)
        {
            if (swprops.onSubdevice)
            {
                fprintf(stdout, "        On sub-device: %u\n", swprops.subdeviceId);
            }
            fprintf(stdout, "        State:         %s\n", swstate.enabled ? "Enabled" : "Disabled");
            if (swstate.enabled)
            {
                uint32_t numPorts;
                if (xetSysmanLinkSwitchGetPorts(hSwitch, &numPorts, NULL) == XE_RESULT_SUCCESS)
                {
                    xet_sysman_link_port_handle_t* phPorts =
                        (xet_sysman_link_port_handle_t*)malloc(numPorts * sizeof(xet_sysman_link_port_handle_t));
                    if (xetSysmanLinkSwitchGetPorts(hSwitch, &numPorts, phPorts) == XE_RESULT_SUCCESS)
                    {
                        fprintf(stdout, "        Ports:\n");
                        for (uint32_t portIndex = 0; portIndex < numPorts; portIndex++)
                        {
                            xet_link_port_state_t portstate;
                            if (xetSysmanLinkPortGetState(phPorts[portIndex], &portstate)
                                == XE_RESULT_SUCCESS)
                            {
                                fprintf(stdout, "            %u: ", portIndex);
                                if (portstate.isConnected)
                                {
                                    fprintf(stdout,
                                        "connected, max rx/tx bandwidth: %u/%u bytes/sec\n",
                                        portstate.rxSpeed.maxBandwidth, portstate.txSpeed.maxBandwidth);
                                }
                                else
                                {
                                    fprintf(stdout, "not connected\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void ShowSwitches(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numSwitches;
    if ((xetSysmanLinkSwitchGet(hSysmanDevice, &numSwitches, NULL) == XE_RESULT_SUCCESS) && numSwitches)
    {
        xet_sysman_link_switch_handle_t* phSwitches =
            (xet_sysman_link_switch_handle_t*)malloc(numSwitches * sizeof(xet_sysman_link_switch_handle_t));
        if (xetSysmanLinkSwitchGet(hSysmanDevice, &numSwitches, phSwitches) == XE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numSwitches; index++)
            {
                fprintf(stdout, "    Switch %u:\n", index);
                ShowSwitchInfo(phSwitches[index]);
            }
        }
    }
}
```

${"##"} <a name="tmp">Querying temperature</a>
A device has multiple temperature sensors embedded at different locations. The following function can be used to read their current value:

| Function                               | Description |
| :---                                   | :---        |
| ::${t}SysmanTemperatureGet()           | Enumerate the temperature sensors on the device. |
| ::${t}SysmanTemperatureGetProperties() | Get static properties for a temperature sensor. In particular, this will indicate which parts of the device the sensor measures (one of ::${t}_temp_sensors_t). |
| ::${t}SysmanTemperatureRead()          | Read the temperature of a sensor. |


${"##"} <a name="psu">Operations on power supplies</a>
The following functions can be used to access information about each power-supply on a device:

| Function                               | Description |
| :---                                   | :---        |
| ::${t}SysmanPsuGet()                   | Enumerate the power supplies on the device that can be managed. |
| ::${t}SysmanPsuGetProperties()         | Get static details about the power supply. |
| ::${t}SysmanPsuGetState()              | Get information about the health (temperature, current, fan) of the power supply. |


${"##"} <a name="fan">Operations on fans</a>
If ::${t}SysmanFanGet() returns one or more fan handles, it is possible to manage their speed. The hardware can be instructed to run the fan at a fixed
speed (or 0 for silent operations) or to provide a table of temperature-speed points in which case the hardware will dynamically change the fan
speed based on the current temperature of the chip. This configuration information is described in the structure ::${t}_fan_config_t. When specifying
speed, one can provide the value in revolutions per minute (::${T}_FAN_SPEED_UNITS_RPM) or as a percentage of the maximum RPM
(::${T}_FAN_SPEED_UNITS_PERCENT).

The following functions are available:

| Function                               | Description |
| :---                                   | :---        |
| ::${t}SysmanFanGet()                   | Enumerate the fans on the device. |
| ::${t}SysmanFanGetProperties()         | Get the maximum RPM of the fan and the maximum number of points that can be specified in the temperature-speed table for a fan. |
| ::${t}SysmanFanGetConfig()             | Get the current configuration (speed) of a fan. |
| ::${t}SysmanFanSetConfig()             | Change the configuration (speed) of a fan. |
| ::${t}SysmanFanGetState()              | Get the current speed of a fan. |

The example below shows how to output the fan speed of all fans:

```c
void ShowFans(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numFans;
    if (xetSysmanFanGet(hSysmanDevice, &numFans, NULL) == XE_RESULT_SUCCESS)
    {
        xet_sysman_fan_handle_t* phFans =
            (xet_sysman_fan_handle_t*)malloc(numFans * sizeof(xet_sysman_fan_handle_t));
        if (xetSysmanFanGet(hSysmanDevice, &numFans, phFans) == XE_RESULT_SUCCESS)
        {
            fprintf(stdout, "    Fans\n");
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                xet_fan_state_t state;
                if (xetSysmanFanGetState(phFans[fanIndex], XET_FAN_SPEED_UNITS_RPM, &state)
                    == XE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "        Fan %u: %u RPM\n", fanIndex, state.speed);
                }
            }
        }
        free(phFans);
    }
}
```

The next example shows how to set the fan speed for all fans to a fixed value in RPM, but only if control is permitted:

```c
void SetFanSpeed(xet_sysman_handle_t hSysmanDevice, uint32_t SpeedRpm)
{
    uint32_t numFans;
    if (xetSysmanFanGet(hSysmanDevice, &numFans, NULL) == XE_RESULT_SUCCESS)
    {
        xet_sysman_fan_handle_t* phFans =
            (xet_sysman_fan_handle_t*)malloc(numFans * sizeof(xet_sysman_fan_handle_t));
        if (xetSysmanFanGet(hSysmanDevice, &numFans, phFans) == XE_RESULT_SUCCESS)
        {
            xet_fan_config_t config;
            config.mode = XET_FAN_SPEED_MODE_FIXED;
            config.speed = SpeedRpm;
            config.speedUnits = XET_FAN_SPEED_UNITS_RPM;
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                xet_fan_properties_t fanprops;
                if (xetSysmanFanGetProperties(phFans[fanIndex], &fanprops) == XE_RESULT_SUCCESS)
                {
                    if (fanprops.canControl)
                    {
                        xetSysmanFanSetConfig(phFans[fanIndex], &config);
                    }
                    else
                    {
                        fprintf(stderr, "ERROR: Can't control fan %u.\n", fanIndex);
                    }
                }
            }
        }
        free(phFans);
    }
}
```

${"##"} <a name="led">Operations on LEDs</a>
If ::${t}SysmanLedGet() returns one or more LED handles, it is possible to manage LEDs on the device. This includes turning them off/on and where
the capability exists, changing their color in realtime.

The following functions are available:

| Function                               | Description |
| :---                                   | :---        |
| ::${t}SysmanLedGet()                   | Enumerate the LEDs on the device that can be managed. |
| ::${t}SysmanLedGetProperties()         | Find out if a LED supports color changes. |
| ::${t}SysmanLedGetState()              | Find out if a LED is currently off/on and the color where the capability is available. |
| ::${t}SysmanLedSetState()              | Turn a LED off/on and set the color where the capability is available. |


${"##"} <a name="ras">Querying RAS errors</a>
RAS stands for Reliability, Availability and Serviceability. It is a feature of certain devices that attempts to correct random bit errors and
provide redundancy where permanent damage has occurred.

If a device supports RAS, it maintains counters for hardware and software errors. There are two types of errors and they are defined in
::${t}_ras_error_type_t:

| Error Type                          | Description |
| :---                                | :---        |
| ::${T}_RAS_ERROR_TYPE_UNCORRECTABLE | Hardware errors occurred which most likely resulted in loss of data or even a device hang. If an error results in device lockup, a warm boot is required before those errors will be reported. |
| ::${T}_RAS_ERROR_TYPE_CORRECTABLE   | These are errors that were corrected by the hardware and did not cause data corruption. |

Software can use the function ::${t}SysmanRasGetProperties() to find out if the device supports RAS and if it is enabled. This will also indicate
if the device had hardware repairs applied in the past. This information is returned in the structure ::${t}_ras_properties_t.

The function ::${t}SysmanRasGet() enumerates the available sets of RAS errors. If no handles are returned, the device does not support RAS.
A device without sub-devices will return one handle if RAS is supported. A device with sub-devices will return a handle for each sub-device.

To determine if errors have occurred, software uses the function ::${t}SysmanRasGetErrors(). This will return the total number of errors of a given type
(correctable/uncorrectable) that have occurred.

When calling ::${t}SysmanRasGetErrors(), software can request that the error counters be cleared. When this is done, all counters of the specified
type (correctable/uncorrectable) will be set to zero and any subsequent calls to this function will only show new errors that have occurred.
If software intends to clear errors, it should be the only application doing so and it should store the counters in an appropriate database
for historical analysis.

When calling ::${t}SysmanRasGetErrors(), an optional pointer to a structure of type ::${t}_ras_details_t can be supplied. This will give a
breakdown of the main device components where the errors occurred. The categories are defined in the structure ::${t}_ras_details_t:

| Error category                            | Description |
| :---                                      | :---        |
| ::${t}_ras_details_t.numResets            | The number of device resets that have taken place. |
| ::${t}_ras_details_t.numProgrammingErrors | The number of hardware exceptions generated by the way workloads have programmed the hardware. |
| ::${t}_ras_details_t.numDriverErrors      | The number of low level driver communication errors have occurred. |
| ::${t}_ras_details_t.numComputeErrors     | The number of errors that have occurred in the compute accelerator hardware. |
| ::${t}_ras_details_t.numNonComputeErrors  | The number of errors that have occurred in the fixed-function accelerator hardware. |
| ::${t}_ras_details_t.numCacheErrors       | The number of errors that have occurred in caches (L1/L3/register file/shared local memory/sampler). |
| ::${t}_ras_details_t.numMemoryErrors      | The number of errors that have occurred in the local memory. |
| ::${t}_ras_details_t.numPciErrors:        | The number of errors that have occurred in the PCI link. |
| ::${t}_ras_details_t.numSwitchErrors      | The number of errors that have occurred in the high-speed connectivity links. |
| ::${t}_ras_details_t.numDisplayErrors     | The number of errors that have occurred in the display. |

The code below shows how to determine if RAS is supported and the current state of RAS errors:

```c
void PrintRasDetails(xet_ras_details_t* pDetails)
{
    fprintf(stdout, "        Number new resets:                %llu\n", pDetails->numResets);
    fprintf(stdout, "        Number new programming errors:    %llu\n", pDetails->numProgrammingErrors);
    fprintf(stdout, "        Number new driver errors:         %llu\n", pDetails->numDriverErrors);
    fprintf(stdout, "        Number new compute errors:        %llu\n", pDetails->numComputeErrors);
    fprintf(stdout, "        Number new non-compute errors:    %llu\n", pDetails->numNonComputeErrors);
    fprintf(stdout, "        Number new cache errors:          %llu\n", pDetails->numCacheErrors);
    fprintf(stdout, "        Number new memory errors:         %llu\n", pDetails->numMemoryErrors);
    fprintf(stdout, "        Number new PCI errors:            %llu\n", pDetails->numPciErrors);
    fprintf(stdout, "        Number new switch errors:         %llu\n", pDetails->numSwitchErrors);
    fprintf(stdout, "        Number new display errors:        %llu\n", pDetails->numDisplayErrors);
}

void ShowRasErrors(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numRasErrorSets;
    if ((xetSysmanRasGet(hSysmanDevice, &numRasErrorSets, NULL) == XE_RESULT_SUCCESS) && numRasErrorSets)
    {
        xet_sysman_ras_handle_t* phRasErrorSets =
            (xet_sysman_ras_handle_t*)malloc(numRasErrorSets * sizeof(xet_sysman_ras_handle_t));
        if (xetSysmanRasGet(hSysmanDevice, &numRasErrorSets, phRasErrorSets) == XE_RESULT_SUCCESS)
        {
            for (uint32_t rasIndex = 0; rasIndex < numRasErrorSets; rasIndex++)
            {
                xet_ras_properties_t props;
                if (xetSysmanRasGetProperties(phRasErrorSets[rasIndex], &props) == XE_RESULT_SUCCESS)
                {
                    const char* pErrorType;
                    switch (props.type)
                    {
                    case XET_RAS_ERROR_TYPE_CORRECTABLE:
                        pErrorType = "Correctable";
                        break;
                    case XET_RAS_ERROR_TYPE_UNCORRECTABLE:
                        pErrorType = "Uncorrectable";
                        break;
                    default:
                        pErrorType = "Unknown";
                        break;
                    }
                    fprintf(stdout, "RAS %s errors\n", pErrorType);
                    if (props.onSubdevice)
                    {
                        fprintf(stdout, "    On sub-device: %u\n", props.subdeviceId);
                    }
                    fprintf(stdout, "    RAS supported: %s\n", props.supported ? "yes" : "no");
                    fprintf(stdout, "    RAS enabled: %s\n", props.enabled ? "yes" : "no");
                    if (props.supported && props.enabled)
                    {
                        uint64_t newErrors;
                        xet_ras_details_t errorDetails;
                        if (xetSysmanRasGetErrors(phRasErrorSets[rasIndex], 1, &newErrors, &errorDetails)
                            == XE_RESULT_SUCCESS)
                        {
                            fprintf(stdout, "    Number new errors: %llu\n", newErrors);
                            if (newErrors)
                            {
                                PrintRasDetails(&errorDetails);
                            }
                        }
                    }
                }
            }
        }
        free(phRasErrorSets);
    }
}
```


${"##"} <a name="dag">Performing diagnostics</a>
Diagnostics is the process of taking a device offline and requesting that the hardware run self-checks and repairs. This is achieved using the function
::${t}SysmanDiagnosticsRunTests(). On return from the function, software can use the diagnostics return code (::${t}_diag_result_t) to determine the new
course of action:

1. ::${T}_DIAG_RESULT_NO_ERRORS - No errors found and workloads can resume submission to the hardware.
2. ::${T}_DIAG_RESULT_ABORT - Hardware had problems running diagnostic tests.
3. ::${T}_DIAG_RESULT_FAIL_CANT_REPAIR - Hardware had problems setting up repair. Card should be removed from the system.
4. ::${T}_DIAG_RESULT_REBOOT_FOR_REPAIR - Hardware has prepared for repair and requires a reboot after which time workloads can resume submission.

The function ::${t}SysmanDeviceWasRepaired() can be used to determine if the device has been repaired.

There are multiple diagnostic test suites that can be run and these are defined in the enumerator ::${t}_diag_type_t. The function
::${t}SysmanDiagnosticsGet() will enumerate each available test suite and the function ::${t}SysmanDiagnosticsGetProperties() can be used to determine
the type and name of each test suite (::${t}_diag_properties_t.type and ::${t}_diag_properties_t.type).

Each test suite contains one or more diagnostic tests. On some systems, it is possible to run only a subset of the tests. Use the function
::${t}SysmanDiagnosticsGetProperties() and check that ::${t}_diag_properties_t.numTests is non-zero to determine if this feature is available. If it is,
::${t}_diag_properties_t.pTests provides the list of tests that can be run - the index and name of each test. The example code below shows how to 
all test suites and the tests in each if this is known:

```c
void ListDiagnosticTests(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numTestSuites;
    if ((xetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, NULL) == XE_RESULT_SUCCESS) && numTestSuites)
    {
        xet_sysman_diag_handle_t* phTestSuites =
            (xet_sysman_diag_handle_t*)malloc(numTestSuites * sizeof(xet_sysman_diag_handle_t));
        if (xetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, phTestSuites) == XE_RESULT_SUCCESS)
        {
            for (uint32_t suiteIndex = 0; suiteIndex < numTestSuites; suiteIndex++)
            {
                xet_diag_properties_t suiteProps;
                if (xetSysmanDiagnosticsGetProperties(phTestSuites[suiteIndex], &suiteProps) == XE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "Diagnostic test suite %s:\n", suiteProps.name);
                    if (suiteProps.numTests)
                    {
                        for (uint32_t i = 0; i < suiteProps.numTests; i++)
                        {
                            const xet_diag_test_t* pTest = &suiteProps.pTests[i];
                            fprintf(stdout, "    Test %u: %s\n", pTest->index, pTest->name);
                        }
                    }
                    else
                    {
                        fprintf(stdout, "    Cannot run subset of tests.\n");
                    }
                }
            }
        }
        free(phTestSuites);
    }
}
```

When running diagnostics for a test suite using ::${t}SysmanDiagnosticsRunTests(), it is possible to specify the start and index of tests in the suite.
Setting to ::${T}_DIAG_FIRST_TEST_INDEX and ::${T}_DIAG_LAST_TEST_INDEX will run all tests in the suite. If it is possible to run a subset of tests,
specify the index of the start test and the end test - all tests that have an index in this range will be run.


${"##"} <a name="evd">Events</a>
Events are a way to determine if changes have occurred on a device e.g. new RAS errors. An application registers the events that it wishes to receive
notification about and then it queries to receive notifications. The query can request a blocking wait - this will put the calling application thread
to sleep until new notifications are received.

The list of all events is provided by the enumerator ::${t}_sysman_event_type_t. Before registering to receive an event from this list, the application
should first check if it is supported for a specific class of devices (devices with the same device ID). This is achieved using the function
::${t}SysmanEventsGetProperties() and looking at the array ::${t}_event_properties_t.supportedEvents[::${t}_sysman_event_type_t] for each event.

For events supported on a given device, the application uses the function ::${t}SysmanEventsRegister() to register to receive notifications.
It can stop notifications at any time using the function ::${t}SysmanEventsUnregister().

Finally, the application uses the function ::${t}SysmanEventsListen() to get a list of new notifications that have occurred since the last time it checked.

The application can choose to block for events by setting timeout to ::${T}_EVENT_WAIT_INFINITE or it can set to zero if it wishes to get the current
status without blocking.

The event notifications are returned as a bitfield of event types. It is up to the application to then enumerate the corresponding device properties
to determine where the events occurred if that is required.

When calling ::${t}SysmanEventsListen(), the application can request that the status be cleared. The driver will return the current status and clear
it internally. The next call to the function will return no notifications until new events occur. If the application does not request that event list
be cleared, subsequent calls to this function will show the same notifications and any new notifications.

The first argument of ::${t}SysmanEventsListen() specifies the SMI handle for the device on which event notifications wish to be received. However, this
can be set to NULL in order to query event notifications across all devices for which the application has created SMI handles. When querying across
multiple devices, it is suggested not to request event status clearing. In this way, the application can know when any event has occurred and can then
make individual requests to each device, this time requesting that the event status be cleared.
