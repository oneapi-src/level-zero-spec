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
        + [Scheduler operations](#glos)
        + [PCI properties](#glop)
    + [Operations on power domains](#pwr)
	+ [Operations on frequency domains](#frq)
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


# <a name="in">Introduction</a>
Sysman is the System Resource Management Interface (SMI) used to monitor and control the power and performance of accelerator devices.

# <a name="ho">High-level overview</a>

## <a name="ini">Initialization</a>
An application wishing to manage power and performance for devices first needs to use the Level0 Core API to enumerate through available accelerator
devices in the system and select those of interest.

For each selected device handle, applications use the function ::zetSysmanGet() to get an **SMI handle** to manage system resources of the device.

![Object hierarchy](../images/tools_sysman_object_hierarchy.png?raw=true) 

There is a unique handle for each device. Multiple threads can use the handle. If concurrent accesses are made to the same device property through
the handle, the last request wins.

The code example below shows how to enumerate the GPU devices in the system and create SMI handles for them:

```c
int gNumDevices = 0;    // Global
int ListDevice(ze_device_handle_t hDevice); // Forward declaration
void ShowDeviceInfo(zet_sysman_handle_t hSysmanDevice); // Forward declaration

int main( int argc, char *argv[] )
{
    int ret = -1;
    if ( (zeInit(ZE_INIT_FLAG_NONE) != ZE_RESULT_SUCCESS) ||
         (zetInit(ZE_INIT_FLAG_NONE) != ZE_RESULT_SUCCESS) )
    {
        fprintf(stderr, "Can't initialize the API.\n");
        ret = 1;
    }
    else
    {
        // Discover all the device groups and devices
        uint32_t driversCount = 0;
        zeDriverGet(&driversCount, nullptr);
        ze_driver_handle_t* allDrivers = (ze_driver_handle_t*)
            malloc(driversCount * sizeof(ze_driver_handle_t));
        zeDriverGet(&driversCount, allDrivers);

        // Find the first GPU device group
        ze_driver_handle_t hDriver = nullptr;
        for(uint32_t i = 0; i < driversCount; ++i)
        {
            uint32_t deviceCount = 0;
            zeDeviceGet(allDrivers[i], &deviceCount, nullptr);

            ze_device_handle_t* allDevices = (ze_device_handle_t*)
                malloc(deviceCount * sizeof(ze_device_handle_t));
            zeDeviceGet(allDrivers[i], &deviceCount, allDevices);

            for(uint32_t d = 0; d < deviceCount; ++i)
            {
                ze_device_properties_t device_properties;
                zeDeviceGetProperties(allDevices[d], &device_properties);
                if(ZE_DEVICE_TYPE_GPU == device_properties.type)
                {
                    if ((ret = ListDevice(allDevices[d])) != 0)
                    {
                        break;
                    }
                }
            }

            free(allDevices);
        }

        free(allDrivers);
    }

    if (gNumDevices == 0)
    {
        fprintf(stdout, "No managed devices found.\n");
    }

    return ret;
}

int ListDevice(ze_device_handle_t hDevice)
{
    int ret = 0;

    zet_sysman_handle_t hSysmanDevice;
    ze_result_t res = zetSysmanGet(hDevice, ZET_SYSMAN_VERSION_CURRENT, &hSysmanDevice);
    if (res == ZE_RESULT_SUCCESS)
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

    return ret;
}

void ShowDeviceInfo(zet_sysman_handle_t hSysmanDevice)
{
    zet_sysman_properties_t devProps;
    ze_bool_t repaired;
    if (zetSysmanDeviceGetProperties(hSysmanDevice, &devProps) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    UUID:           %s\n", devProps.core.uuid.id);
        fprintf(stdout, "    #subdevices:    %u\n", devProps.numSubdevices);
        fprintf(stdout, "    brand:          %s\n", devProps.brandName);
        fprintf(stdout, "    model:          %s\n", devProps.modelName);
        fprintf(stdout, "    driver timeout: disabled\n");
    }
    if (zetSysmanDeviceWasRepaired(hSysmanDevice, &repaired) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Was repaired:   %s\n", repaired ? "yes" : "no");
    }
}
```

## <a name="gdm">Global device management</a>
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

## <a name="dcm">Device component management</a>
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
| [Fabric port](#con)   | Sub-device 0: Enumerates each port<br />Sub-device 1: Enumerates each port | Get port configuration (UP/DOWN)<br />Get physical link details<br />Get port health (green/yellow/red/black)<br />Get remote port UUID<br />Get port max rx/tx speed<br />Get port current rx/tx bandwidth | 
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
| [Fabric port](#con)   | Sub-device 0: Control each port<br />Sub-device 1: Control each port | Configure port UP/DOWN<br />Turn beaconing ON/OFF | 
| [Diagnostics](#con)   | SCAN test suite<br />ARRAY test suite | Run all or a subset of diagnostic tests in the test suite | 

## <a name="dce">Device component enumeration</a>
The SMI API provides functions to enumerate all components in a class that can be managed.

For example, there is a frequency class which is used to control the frequency of different parts of the device. On most devices, the enumerator
will provide two handles, one to control the GPU frequency and one to enumerate the HBM frequency. This is illustrated in the figure below:

![Frequency flow](../images/tools_sysman_freq_flow.png?raw=true) 

In the C API, each class is associated with a unique handle type (e.g. ::zet_sysman_freq_handle_t refers to a frequency component).
In the C++ API, each class is a C++ class (e.g. An instance of the class ::zet::SysmanFrequency refers to a frequency component).

The example code below shows how to use the SMI API to enumerate all GPU frequency components and fix each to a specific frequency:

```c
void FixGpuFrequency(zet_sysman_handle_t hSysmanDevice, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zet_sysman_freq_handle_t* pFreqHandles = (zet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(zet_sysman_freq_handle_t));
        if (zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zet_freq_properties_t props;
                if (zetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == ZET_FREQ_DOMAIN_GPU)
                    {
                        if (props.canControl)
                        {
                            zet_freq_range_t range;
                            range.min = FreqMHz;
                            range.max = FreqMHz;
                            if (zetSysmanFrequencySetRange(pFreqHandles[index], &range) != ZE_RESULT_SUCCESS)
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

## <a name="sdm">Sub-device management</a>
An SMI handle cannot be created for a sub-device - ::zetSysmanGet() will return error ::ZE_RESULT_ERROR_UNSUPPORTED if a device handle for a 
sub-device is passed to this function. Instead, the enumerator for device components will return a list of components that are located in each
sub-device. Properties for each component will indicate in which sub-device it is located. If software wishing to manage components in only one
sub-device should filter the enumerated components using the sub-device ID (see ::ze_device_properties_t.subdeviceId).

The figure below shows the frequency components that will be enumerated on a device with two sub-devices where each sub-device has a GPU and
HBM frequency control:

![Frequency flow](../images/tools_sysman_freq_subdevices.png?raw=true) 

The code below shows how to fix the GPU frequency on a specific sub-device (notice the additional sub-device check):

```c
void FixSubdeviceGpuFrequency(zet_sysman_handle_t hSysmanDevice, uint32_t subdeviceId, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zet_sysman_freq_handle_t* pFreqHandles = (zet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(zet_sysman_freq_handle_t));
        if (zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zet_freq_properties_t props;
                if (zetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == ZET_FREQ_DOMAIN_GPU)
                    {
                        // Only control the GPU frequency domain for a specific sub-device
                        if (props.onSubdevice && (props.subdeviceId == subdeviceId))
                        {
                            if (props.canControl)
                            {
                                zet_freq_range_t range;
                                range.min = FreqMHz;
                                range.max = FreqMHz;
                                if (zetSysmanFrequencySetRange(pFreqHandles[index], &range) != ZE_RESULT_SUCCESS)
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

## <a name="evt">Events</a>
Events are a way to determine if changes have occurred on a device e.g. new RAS errors without poll the SMI API. An application registers the events
that it wishes to receive notification about and then it listens for notifications. The application can choose to block when listening - this will put
the calling application thread to sleep until new notifications are received.

The API enables registering for events from multiple devices and listening for any events coming from any devices by using one function call.

One notifications have occurred, the application can use the query SMI interface functions to get more details.

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
| ::zetSysmanDeviceWasRepaired()                            | Determine if the device has undergone repairs, either through the running of diagnostics or by manufacturing. |

The example below shows how to display general information about a device:

```c
void ShowDeviceInfo(zet_sysman_handle_t hSysmanDevice)
{
    zet_sysman_properties_t devProps;
    ze_bool_t repaired;
    if (zetSysmanDeviceGetProperties(hSysmanDevice, &devProps) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    UUID:           %s\n", devProps.core.uuid.id);
        fprintf(stdout, "    #subdevices:    %u\n", devProps.numSubdevices);
        fprintf(stdout, "    brand:          %s\n", devProps.brandName);
        fprintf(stdout, "    model:          %s\n", devProps.modelName);
        fprintf(stdout, "    driver timeout: disabled\n");
    }
    if (zetSysmanDeviceWasRepaired(hSysmanDevice, &repaired) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Was repaired:   %s\n", repaired ? "yes" : "no");
    }
}
```

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
| ::zetSysmanSchedulerSetTimeoutMode                  | Change to timeout scheduler mode and/or change properties |
| ::zetSysmanSchedulerSetTimesliceMode                | Change to timeslice scheduler mode and/or change properties |
| ::zetSysmanSchedulerSetExclusiveMode                | Change to exclusive scheduler mode and/or change properties |
| ::zetSysmanSchedulerSetComputeUnitDebugMode         | Change to compute unit debug scheduler mode and/or change properties |

The example below shows how to stop the scheduler enforcing fairness while permitting other work to attempt to run:

```c
void DisableSchedulerWatchdog(zet_sysman_handle_t hSysmanDevice)
{
    ze_result_t res;
    zet_sched_mode_t currentMode;
    res = zetSysmanSchedulerGetCurrentMode(hSysmanDevice, &currentMode);
    if (res == ZE_RESULT_SUCCESS)
    {
        ze_bool_t requireReboot;
        zet_sched_timeout_properties_t props;
        props.watchdogTimeout = ZET_SCHED_WATCHDOG_DISABLE;
        res = zetSysmanSchedulerSetTimeoutMode(hSysmanDevice, &props, &requireReboot);
        if (res == ZE_RESULT_SUCCESS)
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
        else if(res == ZE_RESULT_ERROR_UNSUPPORTED)
        {
            fprintf(stderr, "ERROR: The timeout scheduler mode is not supported on this device.\n");
        }
        else if(res == ZE_RESULT_ERROR_INSUFFICENT_PERMISSIONS)
        {
            fprintf(stderr, "ERROR: Don't have permissions to change the scheduler mode.\n");
        }
        else
        {
            fprintf(stderr, "ERROR: Problem calling the API to change the scheduler mode.\n");
        }
    }
    else if(res == ZE_RESULT_ERROR_UNSUPPORTED)
    {
        fprintf(stderr, "ERROR: Scheduler modes are not supported on this device.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem calling the API.\n");
    }
}
```

### <a name="glop">PCI properties</a>
The following functions permit getting data about the PCI endpoint for the device:

| Function                                                   | Description |
| :---                                                       | :---        |
| ::zetSysmanPciGetProperties()                             | Get static properties for the PCI port - BDF address, number of bars, maximum supported speed |
| ::zetSysmanPciGetState()                                  | Get current PCI port speed (number of lanes, generation) |
| ::zetSysmanPciGetBarProperties()                          | Get information about each configured PCI bar |
| ::zetSysmanPciGetStats()                                  | Get PCI statistics - throughput, total packets, number of packet replays |

The example below shows how to output the PCI BDF address:

```c
void ShowPciInfo(zet_sysman_handle_t hSysmanDevice)
{
    zet_pci_properties_t pciProps;
    if (zetSysmanPciGetProperties(hSysmanDevice, &pciProps) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    PCI address:        %04u:%02u:%02u.%u\n", pciProps.address.domain, pciProps.address.bus, pciProps.address.device, pciProps.address.function);
    }
}
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

The following functions are provided to manage the power of the device:

| Function                            | Description |
| :---                                | :---        |
| ::zetSysmanPowerGet()              | Enumerate the power domains. |
| ::zetSysmanPowerGetProperties()    | Get the maximum power limit that can be specified when changing the power limits of a specific power domain. |
| ::zetSysmanPowerGetEnergyCounter() | Read the energy consumption of the specific domain. |
| ::zetSysmanPowerGetLimits()        | Get the sustained/burst/peak power limits for the specific power domain. |
| ::zetSysmanPowerSetLimits()        | Set the sustained/burst/peak power limits for the specific power domain. |

The example below shows how to output information about each power domain on a device:

```c
// Forward declaration
void ShowPowerLimits(zet_sysman_pwr_handle_t hPower);

void ShowPowerDomains(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numPowerDomains;
    if (zetSysmanPowerGet(hSysmanDevice, &numPowerDomains, NULL) == ZE_RESULT_SUCCESS)
    {
        zet_sysman_pwr_handle_t* phPower =
            (zet_sysman_pwr_handle_t*)malloc(numPowerDomains * sizeof(zet_sysman_pwr_handle_t));
        if (zetSysmanPowerGet(hSysmanDevice, &numPowerDomains, phPower) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t pwrIndex = 0; pwrIndex < numPowerDomains; pwrIndex++)
            {
                zet_power_properties_t props;
                if (zetSysmanPowerGetProperties(phPower[pwrIndex], &props) == ZE_RESULT_SUCCESS)
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

void ShowPowerLimits(zet_sysman_pwr_handle_t hPower)
{
    zet_power_sustained_limit_t sustainedLimits;
    zet_power_burst_limit_t burstLimits;
    zet_power_peak_limit_t peakLimits;
    if (zetSysmanPowerGetLimits(hPower, &sustainedLimits, &burstLimits, &peakLimits) == ZE_RESULT_SUCCESS)
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
void ShowAveragePower(zet_sysman_pwr_handle_t hPower, zet_power_energy_counter_t* pPrevEnergyCounter)
{
    zet_power_energy_counter_t newEnergyCounter;
    if (zetSysmanPowerGetEnergyCounter(hPower, &newEnergyCounter) == ZE_RESULT_SUCCESS)
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

## <a name="frq">Operations on frequency domains</a>
The hardware manages frequencies to achieve a balance between best performance and power consumption. Most devices have one or more frequency domains.

The following functions are provided to manage the frequency domains on the device:

| Function                                  | Description |
| :---                                      | :---        |
| ::zetSysmanFrequencyGet()                | Enumerate all the frequency domains on the device and sub-devices. |
| ::zetSysmanFrequencyGetProperties()      | Find out which domain ::zet_domain_t is controlled by this frequency and min/max hardware frequencies.  |
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


## <a name="eng">Operations on engine groups</a>
It is possible to monitor the activity of one or engines combined into an **engine group**. A device can have multiple engine groups and the possible
types are defined in ::zet_engine_group_t. The current engine groups supported are global activity across all engines, activity across all compute
accelerators and activity across all media accelerators.

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

The API permits measuring the receive and transmit bandwidth flowing through each port. It also provides the maximum receive and transmit
speed (frequency/number of lanes) of each port and the current speeds which can be lower if operating in a degraded state. Note that a
port's receive and transmit speeds are not necessarily the same.

Since ports are contained inside a switch, the measured bandwidth at a port can be higher than the actual bandwidth generated by
the accelerators directly connected by two ports. As such, bandwidth metrics at each port are more relevant for determining points of
congestion in the fabric and less relevant for measuring the total bandwidth passing between two accelerators.

The following functions can be used to manage Fabric ports:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanFabricPortGet()            | Enumerate all fabric ports on the device. |
| ::zetSysmanFabricPortGetProperties()  | Get static properties about the switch (model, UUID, max receive/transmit speed). |
| ::zetSysmanFabricPortGetLinkType()    | Get details about the physical link connected to the port. |
| ::zetSysmanFabricPortGetConfig()      | Determine if the port is configured UP and if beaconing is on or off. |
| ::zetSysmanFabricPortSetConfig()      | Configure the port UP or DOWN and turn beaconing on or off. |
| ::zetSysmanFabricPortGetState()       | Determine the health of the port connection, reasons for link degradation or connection issues and the current receive/transmit speed. |
| ::zetSysmanFabricPortGetThroughput()  | Get port receive/transmit counters along with current receive/transmit port speed. |

For devices with sub-devices, the fabric ports are usually located in the sub-device. Given a device handle, ::zetSysmanFabricPortGet() will
include the ports on each sub-device. In this case, ::zet_fabric_port_properties_t.onSubdevice will be set to true and
::zet_fabric_port_properties_t.subdeviceId will give the subdevice ID where that port is located.

The example below shows how to get the state of all fabric ports in the device and sub-devices:

```c
void ShowFabricPortInfo(zet_sysman_fabric_port_handle_t hPort)
{
    zet_fabric_port_properties_t props;
    if (zetSysmanFabricPortGetProperties(hPort, &props) == ZE_RESULT_SUCCESS)
    {
        zet_fabric_port_state_t state;
        if (zetSysmanFabricPortGetState(hPort, &state) == ZE_RESULT_SUCCESS)
        {
            zet_fabric_link_type_t link;
            if (zetSysmanFabricPortGetLinkType(hPort, false, &link) == ZE_RESULT_SUCCESS)
            {
                zet_fabric_port_config_t config;
                if (zetSysmanFabricPortGetConfig(hPort, &config) == ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout,
                        "        Model:                 %s\n", props.model);
                    if (props.onSubdevice)
                    {
                        fprintf(stdout,
                            "        On sub-device:         %u\n", props.subdeviceId);
                    }
                    if (config.enabled)
                    {
                        const char* status;
                        fprintf(stdout,
                            "        Config:                UP\n");
                        switch (state.status)
                        {
                        case ZET_FABRIC_PORT_STATUS_GREEN:
                            status = "GREEN - The port is up and operating as expected";
                            break;
                        case ZET_FABRIC_PORT_STATUS_YELLOW:
                            status = "YELLOW - The port is up but has quality and/or bandwidth degradation";
                            break;
                        case ZET_FABRIC_PORT_STATUS_RED:
                            status = "RED - Port connection instabilities";
                            break;
                        case ZET_FABRIC_PORT_STATUS_BLACK:
                            status = "BLACK - The port is configured down";
                            break;
                        default:
                            status = "UNKNOWN";
                            break;
                        }
                        fprintf(stdout,
                            "        Status:                %s\n", status);
                        fprintf(stdout,
                            "        Link type:             %s\n", link.desc);
                        fprintf(stdout,
                            "        Max speed (rx/tx):     %llu/%llu bytes/sec\n",
                            (long long unsigned int)props.maxRxSpeed.maxBandwidth,
                            (long long unsigned int)props.maxTxSpeed.maxBandwidth);
                        fprintf(stdout,
                            "        Current speed (rx/tx): %llu/%llu bytes/sec\n",
                            (long long unsigned int)state.rxSpeed.maxBandwidth,
                            (long long unsigned int)state.txSpeed.maxBandwidth);
                    }
                    else
                    {
                        fprintf(stdout,
                            "        Config:                DOWN\n");
                    }
                }
            }
        }
    }
}

void ShowFabricPorts(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numPorts;
    if ((zetSysmanFabricPortGet(hSysmanDevice, &numPorts, NULL) == ZE_RESULT_SUCCESS) && numPorts)
    {
        zet_sysman_fabric_port_handle_t* phPorts =
            (zet_sysman_fabric_port_handle_t*)malloc(numPorts * sizeof(zet_sysman_fabric_port_handle_t));
        if (zetSysmanFabricPortGet(hSysmanDevice, &numPorts, phPorts) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numPorts; index++)
            {
                fprintf(stdout, "    Port %u:\n", index);
                ShowFabricPortInfo(phPorts[index]);
            }
        }
        free(phPorts);
    }
}
```

## <a name="tmp">Querying temperature</a>
A device has multiple temperature sensors embedded at different locations. The following function can be used to read their current value:

| Function                               | Description |
| :---                                   | :---        |
| ::zetSysmanTemperatureGet()           | Enumerate the temperature sensors on the device. |
| ::zetSysmanTemperatureGetProperties() | Get static properties for a temperature sensor. In particular, this will indicate which parts of the device the sensor measures (one of ::zet_temp_sensors_t). |
| ::zetSysmanTemperatureRead()          | Read the temperature of a sensor. |


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

The example below shows how to output the fan speed of all fans:

```c
void ShowFans(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numFans;
    if (zetSysmanFanGet(hSysmanDevice, &numFans, NULL) == ZE_RESULT_SUCCESS)
    {
        zet_sysman_fan_handle_t* phFans =
            (zet_sysman_fan_handle_t*)malloc(numFans * sizeof(zet_sysman_fan_handle_t));
        if (zetSysmanFanGet(hSysmanDevice, &numFans, phFans) == ZE_RESULT_SUCCESS)
        {
            fprintf(stdout, "    Fans\n");
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                zet_fan_state_t state;
                if (zetSysmanFanGetState(phFans[fanIndex], ZET_FAN_SPEED_UNITS_RPM, &state)
                    == ZE_RESULT_SUCCESS)
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
void SetFanSpeed(zet_sysman_handle_t hSysmanDevice, uint32_t SpeedRpm)
{
    uint32_t numFans;
    if (zetSysmanFanGet(hSysmanDevice, &numFans, NULL) == ZE_RESULT_SUCCESS)
    {
        zet_sysman_fan_handle_t* phFans =
            (zet_sysman_fan_handle_t*)malloc(numFans * sizeof(zet_sysman_fan_handle_t));
        if (zetSysmanFanGet(hSysmanDevice, &numFans, phFans) == ZE_RESULT_SUCCESS)
        {
            zet_fan_config_t config;
            config.mode = ZET_FAN_SPEED_MODE_FIXED;
            config.speed = SpeedRpm;
            config.speedUnits = ZET_FAN_SPEED_UNITS_RPM;
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                zet_fan_properties_t fanprops;
                if (zetSysmanFanGetProperties(phFans[fanIndex], &fanprops) == ZE_RESULT_SUCCESS)
                {
                    if (fanprops.canControl)
                    {
                        zetSysmanFanSetConfig(phFans[fanIndex], &config);
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
RAS stands for Reliability, Availability and Serviceability. It is a feature of certain devices that attempts to correct random bit errors and
provide redundancy where permanent damage has occurred.

If a device supports RAS, it maintains counters for hardware and software errors. There are two types of errors and they are defined in
::zet_ras_error_type_t:

| Error Type                          | Description |
| :---                                | :---        |
| ::ZET_RAS_ERROR_TYPE_UNCORRECTABLE | Hardware errors occurred which most likely resulted in loss of data or even a device hang. If an error results in device lockup, a warm boot is required before those errors will be reported. |
| ::ZET_RAS_ERROR_TYPE_CORRECTABLE   | These are errors that were corrected by the hardware and did not cause data corruption. |

Software can use the function ::zetSysmanRasGetProperties() to find out if the device supports RAS and if it is enabled. This information is returned in the structure ::zet_ras_properties_t.

The function ::zetSysmanRasGet() enumerates the available sets of RAS errors. If no handles are returned, the device does not support RAS.
A device without sub-devices will return one handle if RAS is supported. A device with sub-devices will return a handle for each sub-device.

To determine if errors have occurred, software uses the function ::zetSysmanRasGetErrors(). This will return the total number of errors of a given type
(correctable/uncorrectable) that have occurred.

When calling ::zetSysmanRasGetErrors(), software can request that the error counters be cleared. When this is done, all counters of the specified
type (correctable/uncorrectable) will be set to zero and any subsequent calls to this function will only show new errors that have occurred.
If software intends to clear errors, it should be the only application doing so and it should store the counters in an appropriate database
for historical analysis.

When calling ::zetSysmanRasGetErrors(), an optional pointer to a structure of type ::zet_ras_details_t can be supplied. This will give a
breakdown of the main device components where the errors occurred. The categories are defined in the structure ::zet_ras_details_t. The meaning
of each category depends on the error type (correctable, uncorrectable).

| Error category                            |  ::ZET_RAS_ERROR_TYPE_CORRECTABLE | ::ZET_RAS_ERROR_TYPE_UNCORRECTABLE | 
| :---                                      | :---        | :---        |
| ::zet_ras_details_t.numResets            | Always zero. | Number of device resets that have taken place. |
| ::zet_ras_details_t.numProgrammingErrors | Always zero. | Number of hardware exceptions generated by the way workloads have programmed the hardware. |
| ::zet_ras_details_t.numDriverErrors      | Always zero. | Number of low level driver communication errors have occurred. |
| ::zet_ras_details_t.numComputeErrors     | Number of errors that have occurred in the accelerator hardware that were corrected. | Number of errors that have occurred in the accelerator hardware that were not corrected. These would have caused the hardware to hang and the driver to reset. |
| ::zet_ras_details_t.numNonComputeErrors  | Number of errors occurring in fixed-function accelerator hardware that were corrected. | Number of errors occurring in the fixed-function accelerator hardware there could not be corrected. Typically these will result in a PCI bus reset and driver reset. |
| ::zet_ras_details_t.numCacheErrors       | Number of ECC correctable errors that have occurred in the on-chip caches (L1/L3/register file/shared local memory). | Number of ECC uncorrectable errors that have occurred in the on-chip caches (L1/L3/register file/shared local memory). These would have caused the hardware to hang and the driver to reset. |
| ::zet_ras_details_t.numMemoryErrors      | Number of times the device memory has transitioned from a healthy state to a degraded state. Degraded state occurs when the number of correctable errors cross a threshold. | Number of times the device memory has transitioned from a healthy/degraded state to a critical/replace state. |
| ::zet_ras_details_t.numPciErrors:        | controllerNumber of PCI packet replays that have occurred. | Number of PCI bus resets. |
| ::zet_ras_details_t.numFabricErrors      | Number of times one or more ports have transitioned from a green status to a yellow status. This indicates that links are experiencing quality degradation. | Number of times one or more ports have transitioned from a green/yellow status to a red status. This indicates that links are experiencing connectivity statibility issues. |
| ::zet_ras_details_t.numDisplayErrors     | Number of ECC correctable errors that have occurred in the display. | Number of ECC uncorrectable errors that have occurred in the display. |

The code below shows how to determine if RAS is supported and the current state of RAS errors:

```c
void PrintRasDetails(zet_ras_details_t* pDetails)
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

void ShowRasErrors(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numRasErrorSets;
    if ((zetSysmanRasGet(hSysmanDevice, &numRasErrorSets, NULL) == ZE_RESULT_SUCCESS) && numRasErrorSets)
    {
        zet_sysman_ras_handle_t* phRasErrorSets =
            (zet_sysman_ras_handle_t*)malloc(numRasErrorSets * sizeof(zet_sysman_ras_handle_t));
        if (zetSysmanRasGet(hSysmanDevice, &numRasErrorSets, phRasErrorSets) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t rasIndex = 0; rasIndex < numRasErrorSets; rasIndex++)
            {
                zet_ras_properties_t props;
                if (zetSysmanRasGetProperties(phRasErrorSets[rasIndex], &props) == ZE_RESULT_SUCCESS)
                {
                    const char* pErrorType;
                    switch (props.type)
                    {
                    case ZET_RAS_ERROR_TYPE_CORRECTABLE:
                        pErrorType = "Correctable";
                        break;
                    case ZET_RAS_ERROR_TYPE_UNCORRECTABLE:
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
                        zet_ras_details_t errorDetails;
                        if (zetSysmanRasGetErrors(phRasErrorSets[rasIndex], 1, &newErrors, &errorDetails)
                            == ZE_RESULT_SUCCESS)
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


## <a name="dag">Performing diagnostics</a>
Diagnostics is the process of taking a device offline and requesting that the hardware run self-checks and repairs. This is achieved using the function
::zetSysmanDiagnosticsRunTests(). On return from the function, software can use the diagnostics return code (::zet_diag_result_t) to determine the new
course of action:

1. ::ZET_DIAG_RESULT_NO_ERRORS - No errors found and workloads can resume submission to the hardware.
2. ::ZET_DIAG_RESULT_ABORT - Hardware had problems running diagnostic tests.
3. ::ZET_DIAG_RESULT_FAIL_CANT_REPAIR - Hardware had problems setting up repair. Card should be removed from the system.
4. ::ZET_DIAG_RESULT_REBOOT_FOR_REPAIR - Hardware has prepared for repair and requires a reboot after which time workloads can resume submission.

The function ::zetSysmanDeviceWasRepaired() can be used to determine if the device has been repaired.

There are multiple diagnostic test suites that can be run and these are defined in the enumerator ::zet_diag_type_t. The function
::zetSysmanDiagnosticsGet() will enumerate each available test suite and the function ::zetSysmanDiagnosticsGetProperties() can be used to determine
the type and name of each test suite (::zet_diag_properties_t.type and ::zet_diag_properties_t.type).

Each test suite contains one or more diagnostic tests. On some systems, it is possible to run only a subset of the tests. Use the function
::zetSysmanDiagnosticsGetProperties() and check that ::zet_diag_properties_t.numTests is non-zero to determine if this feature is available. If it is,
::zet_diag_properties_t.pTests provides the list of tests that can be run - the index and name of each test. The example code below shows how to 
all test suites and the tests in each if this is known:

```c
void ListDiagnosticTests(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numTestSuites;
    if ((zetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, NULL) == ZE_RESULT_SUCCESS) && numTestSuites)
    {
        zet_sysman_diag_handle_t* phTestSuites =
            (zet_sysman_diag_handle_t*)malloc(numTestSuites * sizeof(zet_sysman_diag_handle_t));
        if (zetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, phTestSuites) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t suiteIndex = 0; suiteIndex < numTestSuites; suiteIndex++)
            {
                zet_diag_properties_t suiteProps;
                if (zetSysmanDiagnosticsGetProperties(phTestSuites[suiteIndex], &suiteProps) == ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "Diagnostic test suite %s:\n", suiteProps.name);
                    if (suiteProps.numTests)
                    {
                        for (uint32_t i = 0; i < suiteProps.numTests; i++)
                        {
                            const zet_diag_test_t* pTest = &suiteProps.pTests[i];
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

When running diagnostics for a test suite using ::zetSysmanDiagnosticsRunTests(), it is possible to specify the start and index of tests in the suite.
Setting to ::ZET_DIAG_FIRST_TEST_INDEX and ::ZET_DIAG_LAST_TEST_INDEX will run all tests in the suite. If it is possible to run a subset of tests,
specify the index of the start test and the end test - all tests that have an index in this range will be run.


## <a name="evd">Events</a>
Events are a way to determine if changes have occurred on a device e.g. new RAS errors. An application registers the events that it wishes to receive
notification about and then it queries to receive notifications. The query can request a blocking wait - this will put the calling application thread
to sleep until new notifications are received.

The list of all events is provided by the enumerator ::zet_sysman_event_type_t. Before registering to receive an event from this list, the application
should first check if it is supported for a specific class of devices (devices with the same device ID). This is achieved using the function
::zetSysmanEventsGetProperties() and looking at the array ::zet_event_properties_t.supportedEvents[::zet_sysman_event_type_t] for each event.

For events supported on a given device, the application uses the function ::zetSysmanEventsRegister() to register to receive notifications.
It can stop notifications at any time using the function ::zetSysmanEventsUnregister().

Finally, the application uses the function ::zetSysmanEventsListen() to get a list of new notifications that have occurred since the last time it checked.

The application can choose to block for events by setting timeout to ::ZET_EVENT_WAIT_INFINITE or it can set to zero if it wishes to get the current
status without blocking.

The event notifications are returned as a bitfield of event types. It is up to the application to then enumerate the corresponding device properties
to determine where the events occurred if that is required.

When calling ::zetSysmanEventsListen(), the application can request that the status be cleared. The driver will return the current status and clear
it internally. The next call to the function will return no notifications until new events occur. If the application does not request that event list
be cleared, subsequent calls to this function will show the same notifications and any new notifications.

The first argument of ::zetSysmanEventsListen() specifies the SMI handle for the device on which event notifications wish to be received. However, this
can be set to NULL in order to query event notifications across all devices for which the application has created SMI handles. When querying across
multiple devices, it is suggested not to request event status clearing. In this way, the application can know when any event has occurred and can then
make individual requests to each device, this time requesting that the event status be cleared.

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
| ::zetSysmanFirmwareFlash()           | Firmware flashing must be handled with care. |
| ::zetSysmanFabricPortSetConfig()     | Putting fabric ports offline can distrupt workloads, causing uncorrectable errors. |
| ::zetSysmanDiagnosticsRunTests()     | Diagnostics take a device offline. |


## <a name="sev">Virtualization</a>
In virtualization environments, only the host is permitted to access any features of the API. Attempts to use the API in virtual machines will
fail.
