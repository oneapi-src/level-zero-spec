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
* [Sysman handle](#hd)
* [System Resource Management](#sm)
    + [General](#smg)
    + [Power](#smp)
	+ [Frequency](#smf)
	+ [Activity](#sma)
	+ [Memory](#smm)
	+ [PCI](#smp)
	+ [Switch](#sml)
	+ [Temperature](#smt)
	+ [Standby](#sms)
	+ [Firmware](#smw)
	+ [PSU](#smy)
	+ [Fan](#smn)
	+ [LED](#smd)
* [Reliability, availability and serviceability (RAS)](#ra)
* [Events](#ev)
* [Diagnostics](#di)
* [Sub-devices](#sd)

${"#"} <a name="in">Introduction</a>
Sysman is the System Resource Management Interface (SMI) used to monitor and control the power and performance of accelerator devices.

${"#"} <a name="hd">Sysman handle</a>
An application wishing to manage power and performance for devices first needs to use the Level0 Core API to enumerate through available accelerator devices in the system and
select those of interest.

For each selected device handle, applications use the function ::${t}SysmanGet to get an SMI handle to manage system resources of the device.

![Object hierarchy](../images/tools_sysman_object_hierarchy.png?raw=true) 

There is a unique handle for each device. Multiple threads can use the handle. If concurrent accesses are made to the same device property through the handle, the last request wins.

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

${"#"} <a name="sm">System Resource Management</a>
System resource management is broken down by device component type:

| Device component type                         | Description |
| :---                                | :---        |
| [General](#smg) | Access to general device configuration information, operating mode and reset. |
| [Power](#smp) | Access to power configuration of the device. |
| [Frequency](#smf) | Access to frequency configuration of various domains (GPU, local memory). |
| [Activity](#sma) | Access to accelerator activity counters. |
| [Memory](#smm) | Access to local memory bandwidth and allocation information. |
| [PCI](#smp) | Access to PCI statistics. |
| [Switch](#sml) | Access to high-speed peer-to-peer connection configuration and statistics. |
| [Temperature](#smt) | Access to temperature sensor readins. |
| [Standby](#sms) | Access to standby promotion configuration. |
| [Firmware](#smw) | Access to device firmwares. |
| [PSU](#smy) | Access to device power supply information. |
| [Fan](#smn) | Access to device fan controls and state. |
| [LED](#smd) | Access to device LED controls and state. |

For each component type, there are a set of functions that provide access and control of that component. Most components types have the same function
set of functions - read static properties of the component, read the current state of the component, get statistical data, make configuration changes.
The diagram below illustrated the typical flow used when working with frequency domains:

![Frequency flow](../images/tools_sysman_freq_flow.png?raw=true) 

Many component types have multiple components - for example, there are two frequency domains (GPU, MEMORY). When calling the functions for a component
type, the appropriate component identifier is provided as an argument to the function. The diagram above shows that there are two frequency domains
and so the function calls will receive either ::${T}_FREQ_DOMAIN_GPU or ::${T}_FREQ_DOMAIN_MEMORY.

Other component types can have an arbitrary number of components - for example the number of fans. The number is provided in the general device properties
for the SMI handle ::${t}_sysman_properties_t which is obtained by call the function ::${t}SysmanDeviceGetProperties(). For example, the number of
fans is given in ::${t}_sysman_properties_t.numFans. When calling the functions for fans, one specifies the fan index, a number between 0 and the
number of fans minus 1. This is illustrated in the diagram below:

![Fan flow](../images/tools_sysman_fan_flow.png?raw=true)

${"##"} <a name="smg">General</a>
The following functions are provided to manage general aspects of the device:

| Function                             | Device behavior | Sub-device behavior |
| :---                                 | :---        | :---        |
| ::${t}SysmanDeviceGetProperties()    | Returns static properties for the device. This includes the device serial number and the number of various components such as fans and which components can have their configuration changes. | Returns static properties for the sub-device only. Some information such as serial number are the same as the device. |
| ::${t}SysmanDeviceGetOperatingMode() | Find out what type of workload performance optimization is currently in effect (see note below). | Not supported. |
| ::${t}SysmanDeviceSetOperatingMode() | Change the workload optimization mode (see note below). | Not supported. |
| ::${t}SysmanDeviceReset()            | Performs a warm reset of the device which includes unloading the driver. | Not supported. |

By default, the device is optimized for multi-application operations. This will attempt to provide fair access to the accelerator resources
for simultaneous processes/virtual machines using the device. However, it is possible to modify the operating mode to optimize for different use-cases.
The possible optimizations are given by the enumerator ::${t}_operating_mode_t.

The example below shows how to output information about a device:

```c
void ShowDeviceInfo(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_properties_t props;
    xet_operating_mode_t mode;
    
    if (xetSysmanDeviceGetProperties(hSysmanDevice, &props) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    UUID:    %s\n", props.uuid.id);
        fprintf(stdout, "    brand:   %s\n", props.brandName);
        fprintf(stdout, "    model:   %s\n", props.modelName);
        fprintf(stdout, "    serial#: %s\n", props.serialNumber);
        fprintf(stdout, "    board#:  %s\n", props.boardNumber);
    }
    if (xetSysmanDeviceGetOperatingMode(hSysmanDevice, &mode) == XE_RESULT_SUCCESS)
    {
        switch (mode)
        {
        case XET_OPERATING_MODE_EXCLUSIVE_COMPUTE_PROCESS:
            fprintf(stdout, "    mode:    exclusive compute process\n");
            break;
        default:
            fprintf(stdout, "    mode:    multiply process\n");
            break;
        }
    }
}
```

${"##"} <a name="smp">Power</a>
The PSU (Power Supply Unit) provides power to a device. The amount of power drawn by a device is a function of the voltage and frequency,
both of which are controlled by the Punit, a micro-controller on the device. If the voltage and frequency are two high, two conditions can occur:

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
if the high requests and utilization of the device continues.

The following functions are provided to manage the power of the device:

| Function                            | Device behavior | Sub-device behavior |
| :---                                | :---        | :---        |
| ::${t}SysmanPowerGetProperties()    | Get the maximum power limit that can be specified when changing the power of the device. | Get the maximum power limit that can be specified when changing the power of the sub-device. |
| ::${t}SysmanPowerGetEnergyCounter() | Read the energy consumption of the whole device, including sub-devices. | Read the energy consumption of the sub-device only. |
| ::${t}SysmanPowerGetLimits()        | Get the sustained/burst/peak power limits for the whole device. | Get the sustained/burst/peak power limits for the sub-device only. |
| ::${t}SysmanPowerSetLimits()        | Set the sustained/burst/peak power limits for the whole device. | Set the sustained/burst/peak power limits for the sub-device only. This may not be supported - check ::${t}_power_properties_t.canControl. |

The example below shows how to output the power limits:

```c
void ShowPowerLimits(xet_sysman_handle_t hSysmanDevice)
{
    xet_power_sustained_limit_t sustainedLimits;
    xet_power_burst_limit_t burstLimits;
    xet_power_peak_limit_t peakLimits;
    if (xetSysmanPowerGetLimits(hSysmanDevice, &sustainedLimits, &burstLimits, &peakLimits) == XE_RESULT_SUCCESS)
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

${"##"} <a name="smf">Frequency</a>
The hardware manages frequencies to achieve a balance between best performance and power consumption.

A device has multiple frequency domains. Those that are visible to software are defined by the enumerator ::${t}_freq_domain_t. Each domain can
be managed individually using the following functions:

| Function                               | Device behavior | Sub-device behavior |
| :---                                   | :---        | :---        |
| ::${t}SysmanFrequencyGetProperties()   | Find out the available frequencies for the frequency domain (will be the same for each sub-device). | Same behavior as at the device level. |
| ::${t}SysmanFrequencyGetLimits()       | Will take the most restrictive min/max range across all sub-devices. | The current min/max frequency between which the frequency domain can operate. |
| ::${t}SysmanFrequencySetLimits()       | Set the min/max frequency for the frequency domain. If there are sub-devices, sets the same range across all of them. | Set the min/max frequency for the frequency domain on the sub-device only. |
| ::${t}SysmanFrequencyGetState()        | Get the current frequency request, actual frequency, TDP frequency and throttle reasons. If there are sub-devices, takes the average of the frequencies and merges the throttle reasons. | Get the current frequency request, actual frequency, TDP frequency and throttle reasons for the sub-device only. |
| ::${t}SysmanFrequencyGetThrottleTime() | Gets the amount of time the frequency domain has been throttled. If there are sub-devices, it will return the max across all of them. | Gets the amount of time the frequency domain in the sub-device has been throttled. |

It is only permitted to set the frequency limits if the device property ::${t}_freq_properties_t.canControl is true for the specific frequency
domain.

Setting the min/max frequency limits to the same value, software is effectively disabling the hardware controlled frequency and getting a fixed stable
frequency providing the Punit does not need to throttle due to excess power/heat. 

Based on the power/thermal conditions, the frequency requested by software or the hardware may not be respected. This situation can be determined
using the function ::${t}SysmanFrequencyGetState() which will indicate the current frequency request, the actual (resolved) frequency and other
frequency information that depends on the current conditions. If the actual frequency is below the requested frequency,
::${t}_freq_state_t.throttleReasons will provide the reasons why the frequency is being limited by the Punit.

The example below shows how to fix the frequency of a frequency domain, but only if control is permitted:

```c
void FixFrequency(xet_sysman_handle_t hSysmanDevice, xet_freq_domain_t Domain, double FreqMHz)
{
    xet_freq_properties_t props;
    if (xetSysmanFrequencyGetProperties(hSysmanDevice, Domain, &props) == XE_RESULT_SUCCESS)
    {
        if (props.canControl)
        {
            xet_freq_limits_t limits;
            limits.min = FreqMHz;
            limits.max = FreqMHz;
            if (xetSysmanFrequencySetLimits(hSysmanDevice, Domain, &limits) != XE_RESULT_SUCCESS)
            {
                fprintf(stderr, "ERROR: Problem setting the frequency limits.\n");
            }
        }
        else
        {
            fprintf(stderr, "ERROR: Can't control this frequency domain.\n");
        }
    }
}
```

${"##"} <a name="sma">Activity</a>
It is possible to monitor the activity of various accelerator assets on the device - the list if provided in the enumerator ::${t}_activity_type_t.
By taking two snapshots of the activity counters, it is possible to calculate the average utilization of different parts of the device. Currently
it is possible to get the utilization across all accelerator assets in the device or for only the compute assets and the media assets separately.

The following functions are provided:

| Function                               | Device behavior | Sub-device behavior |
| :---                                   | :---        | :---        |
| ::${t}SysmanActivityGetStats()         | Returns the activity counters for the specified ::${t}_activity_type_t. If there are sub-devices, this will return the average across all of them. | Returns the activity counters for the specified ::${t}_activity_type_t in the sub-device. |


${"##"} <a name="smm">Memory</a>
The following functions provide access to information about the local memory:

| Function                               | Device behavior | Sub-device behavior |
| :---                                   | :---        | :---        |
| ::${t}SysmanMemoryGetProperties()      | Find out the type of memory and maximum physical memory. If there are sub-devices, the type of memory will be the same and the maximum physical memory will be the sum of the physical memory size in each sub-device.  | Find out the type of memory and maximum physical memory in the sub-device. |
| ::${t}SysmanMemoryGetAllocated()       | Returns the currently allocated memory size. If there are sub-devices, it returns the total allocated memory for the memory in each sub-device. | Returns the currently allocated memory size for the memory in the sub-device. |
| ::${t}SysmanMemoryGetBandwidth()       | Returns memory bandwidth counters. If there are sub-devices, this will return the average across each sub-device memory. | Returns bandwidth counters for the memory in the sub-device. |

${"##"} <a name="smp">PCI</a>
The PCI bus is the primary means by which the CPU communicates with the device.

The following functions provide access to information about the PCI device:

| Function                               | Device behavior |
| :---                                   | :---        |
| ::${t}SysmanPciGetProperties()         | Get the PCI address, number of configured bars and the maximum supported speed. |
| ::${t}SysmanPciGetBarProperties()      | Get information about each configured bar. |
| ::${t}SysmanPciGetState()              | Get the current speed. |
| ::${t}SysmanPciGetThroughput()         | Get the current throughput counters |
| ::${t}SysmanPciGetStats()              | Get telemetry counters - replay counts. |

These functions will return the same information for a sub-device handle.

${"##"} <a name="sml">Switch</a>
A device is able access memory and resources on a remote device using a high-speed switch rather than using the PCI bus. If the device has such a
switch, the property ::${t}_sysman_properties_t.numSwitches will be non-zero.

The following functions can be used to manage the switch:

| Function                               | Device/sub-device behavior |
| :---                                   | :---        |
| ::${t}SysmanSwitchGetProperties()      | Get the GUID of the switch and the number of ports. |
| ::${t}SysmanSwitchGetState()           | Get the current state of the switch (enabled/disabled). |
| ::${t}SysmanSwitchSetState()           | Enables/disabled the switch. |
| ::${t}SysmanSwitchPortGetProperties()  | Get the properties of a port on the switch - maximum supported bandwidth. |
| ::${t}SysmanSwitchPortGetState()       | Get the current state of a port on the switch - connected, remote switch GUID, current maximum bandwidth. |
| ::${t}SysmanSwitchPortGetThroughput()  | Get the throughput counters of a port on the switch. |
| ::${t}SysmanSwitchPortGetStats()       | Gets telemetry counters of a port on the switch - number of replays. |

For devices with sub-devices, the switch is usually located in the sub-device. Given a device handle, ::${t}_sysman_properties_t.numSwitches will
include the switches on each sub-device. In this case, ::${t}_switch_properties_t.onSubdevice will be set to true and
::${t}_switch_properties_t.subdeviceUuid will give the device UUID of the sub-device where that switch is located. Give a sub-device handle,
::${t}_sysman_properties_t.numSwitches will only give the number of switches in the sub-device.

The example below shows how to get the state of all switches in the device and sub-devices:

```c
void ShowSwitchInfo(xet_sysman_handle_t hSysmanDevice, uint32_t SwitchIndex)
{
    xet_switch_properties_t swprops;
    if (xetSysmanSwitchGetProperties(hSysmanDevice, SwitchIndex, &swprops) == XE_RESULT_SUCCESS)
    {
        xet_switch_state_t swstate;
        if (xetSysmanSwitchGetState(hSysmanDevice, SwitchIndex, &swstate) == XE_RESULT_SUCCESS)
        {
            fprintf(stdout, "        GUID:          %s\n", swprops.address.guid);
            fprintf(stdout, "        #port:         %u\n", swprops.numPorts);
            if (swprops.onSubdevice)
            {
                fprintf(stdout, "        On sub-device: %s\n", swprops.subdeviceUuid.id);
            }
            fprintf(stdout, "        State:         %s\n", swstate.enabled ? "Enabled" : "Disabled");
            if (swstate.enabled)
            {
                fprintf(stdout, "        Ports:\n");
                for (uint32_t portIndex = 0; portIndex < swprops.numPorts; portIndex++)
                {
                    xet_switch_port_state_t portstate;
                    if (xetSysmanSwitchPortGetState(hSysmanDevice, SwitchIndex, portIndex, &portstate)
                        == XE_RESULT_SUCCESS)
                    {
                        if (portstate.connected)
                        {
                            fprintf(stdout,
                                "            %u: "
                                "connected to switch with GUID %s, max rx/tx bandwidth %u/%u bytes/sec\n",
                                portIndex, portstate.remote.guid,
                                portstate.rxSpeed.maxBandwidth, portstate.txSpeed.maxBandwidth);
                        }
                        else
                        {
                            fprintf(stdout, "            %u: not connected\n", portIndex);
                        }
                    }
                }
            }
        }
    }
}

void ShowSwitches(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_properties_t props;
    if (xetSysmanDeviceGetProperties(hSysmanDevice, &props) == XE_RESULT_SUCCESS)
    {
        if (props.numSwitches)
        {
            for (uint32_t switchIndex = 0; switchIndex < props.numSwitches; switchIndex++)
            {
                fprintf(stdout, "    Switch %u:\n", switchIndex);
                ShowSwitchInfo(hSysmanDevice, switchIndex);
            }
        }
    }
}
```

${"##"} <a name="smt">Temperature</a>
A device has multiple temperature sensors embedded at different locations. The following function can be used to read their current value:

| Function                               | Device behavior | Sub-device behavior |
| :---                                   | :---        | :---        |
| ::${t}SysmanTemperatureGet()           | Gets the temperature for a specified sensor. If there are sub-devices, it will take the max found on the same sensor in each sub-device. | Gets the temperature for a specified sensor in the sub-device. |

The supported temperature sensor locations are described by the enumerator ::${t}_temp_sensors_t.

${"##"} <a name="sms">Standby</a>
When a device is idle, it will enter a low-power state. Since exit from low-power states have associated latency, they can hurt performance. The
hardware attempts to stike a balance between between saving power when there are large idle times between workloads submissions to the device and
keeping the device awake when idle because it has determined that new workload submissions are imminent.

The following functions can be used to control how the hardware promotes to standby states:

| Function                               | Device behavior | Sub-device behavior |
| :---                                   | :---        | :---        |
| ::${t}SysmanStandbyGetMode()           | Get the current promotion mode for the device. If there are sub-devices, this will return the promotion mode across sub-devices that gives the best performance. | Get the current promotion mode for the sub-device. |
| ::${t}SysmanStandbySetMode()           | Set the promotion mode for the device. If there are sub-devices, this will set the same promotion mode across all sub-devices. | Set the promotion mode for the sub-device. |

The available promotion modes are described in the enumerator ::${t}_stby_promo_mode_t.

${"##"} <a name="smw">Firmware</a>
If ::${t}_sysman_properties_t.numFirmwares is non-zero, the following functions can be used to manage firmwares on the device:

| Function                               | Device behavior | Sub-device behavior |
| :---                                   | :---        | :---        |
| ::${t}SysmanFirmwareGetProperties()    | Find out the name and version of each installed firmware, including those in sub-devices. | Find out the name and version of each installed firmware in the sub-device. |
| ::${t}SysmanFirmwareGetChecksum()      | Get the checksum for an installed firmware, including those in sub-devices | Get the checksum for an installed firmware. |
| ::${t}SysmanFirmwareFlash()            | Flash a new firmware image, including for firmware on sub-devices | Flash a new firmware image on a sub-devices |

${"##"} <a name="smy">PSU</a>
If ::${t}_sysman_properties_t.numPsus is non-zero, the following functions can be used to access information about each power-supply:

| Function                               | Device behavior | Sub-device behavior |
| :---                                   | :---        | :---        |
| ::${t}SysmanPsuGetProperties()         | Get static details about the power supply. | No power supplies will be enumerated. |
| ::${t}SysmanPsuGetState()              | Get information about the health (temperature, current, fan) of the power supply. | No power supplies will be enumerated. |

${"##"} <a name="smn">Fan</a>
If ::${t}_sysman_properties_t.numFans is non-zero, it is possible to manage their speed. The hardware can be instructed to run the fan at a fixed
speed (or 0 for silent operations) or to provide a table of temperature-speed points in which case the hardware will dynamically change the fan
speed based on the current temperature of the chip. This configuration information is described in the structure ::${t}_fan_config_t. When specifying
speed, one can provide the value in revolutions per minute (::${T}_FAN_SPEED_UNITS_RPM) or as a percentage of the maximum RPM
(::${T}_FAN_SPEED_UNITS_PERCENT).

The following functions are available:

| Function                               | Device behavior | Sub-device behavior |
| :---                                   | :---        | :---        |
| ::${t}SysmanFanGetProperties()         | Get the maximum RPM of the fan and the maximum number of points that can be specified in the temperature-speed. | No fans will be enumerated. |
| ::${t}SysmanFanGetConfig()             | Get the current fan configuration. | No fans will be enumerated. |
| ::${t}SysmanFanSetConfig()             | Change the fan configuration. | No fans will be enumerated. |
| ::${t}SysmanFanGetState()              | Get the current speed of the fan. | No fans will be enumerated. |

The example below shows how to output the fan speed of all fans:

```c
void ShowFans(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_properties_t props;
    
    if (xetSysmanDeviceGetProperties(hSysmanDevice, &props) == XE_RESULT_SUCCESS)
    {
        if (props.numFans)
        {
            fprintf(stdout, "    Fans\n");
            for (uint32_t fanIndex = 0; fanIndex < props.numFans; fanIndex++)
            {
                xet_fan_state_t state;
                if (xetSysmanFanGetState(hSysmanDevice, fanIndex, XET_FAN_SPEED_UNITS_RPM, &state)
                    == XE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "        Fan %u: %u RPM\n", fanIndex, state.speed);
                }
            }
        }
    }
}
```

The next example shows how to set the fan speed for all fans to a fixed value in RPM, but only if control is permitted:

```c
void SetFanSpeed(xet_sysman_handle_t hSysmanDevice, uint32_t SpeedRpm)
{
    xet_sysman_properties_t props;
    if (xetSysmanDeviceGetProperties(hSysmanDevice, &props) == XE_RESULT_SUCCESS)
    {
        if (props.numFans)
        {
            xet_fan_config_t config;
            config.mode = XET_FAN_SPEED_MODE_FIXED;
            config.speed = SpeedRpm;
            config.speedUnits = XET_FAN_SPEED_UNITS_RPM;
            for (uint32_t fanIndex = 0; fanIndex < props.numFans; fanIndex++)
            {
                xet_fan_properties_t fanprops;
                if (xetSysmanFanGetProperties(hSysmanDevice, fanIndex, &fanprops) == XE_RESULT_SUCCESS)
                {
                    if (fanprops.canControl)
                    {
                        xetSysmanFanSetConfig(hSysmanDevice, fanIndex, &config);
                    }
                    else
                    {
                        fprintf(stderr, "ERROR: Can't control fan %u.\n", fanIndex);
                    }
                }
            }
        }
    }
}
```

${"##"} <a name="smd">LED</a>
If ::${t}_sysman_properties_t.numLeds is non-zero, it is possible to manage LEDs on the device. This includes turning them off/on and where
the capability exists, changing their color in realtime.

The following functions are available:

| Function                               | Device behavior | Sub-device behavior |
| :---                                   | :---        | :---        |
| ::${t}SysmanLedGetProperties()         | Find out if the LED supports color changes. | No LEDs will be enumerated. |
| ::${t}SysmanLedGetState()              | Find out if the LED is currently off/on and the color where the capability exists. | No LEDs will be enumerated. |
| ::${t}SysmanLedSetState()              | Turn the LED off/on and set the color where the capability exists. | No LEDs will be enumerated. |


${"#"} <a name="ra">Reliability, availability and serviceability (RAS)</a>
The device driver maintains counters for hardware and software errors related to the device. There are two types of errors and they are defined in
the enumerator ::${t}_ras_error_type_t:

| Error Type                          | Description |
| :---                                | :---        |
| ::${T}_RAS_ERROR_TYPE_UNCORRECTABLE | Hardware errors occurred which most likely resulted in loss of data or even a device hang. If an error results in device lockup, a warm boot is required before those errors will be reported. |
| ::${T}_RAS_ERROR_TYPE_CORRECTABLE   | These are errors that were corrected by the hardware and did not cause data corruption. |

Software can use the function ::${t}SysmanRasGetProperties() to find out if the device supports RAS and if it is enabled. This will also indicate
if the device had hardware repairs applied in the past. This information is returned in the structure ::${t}_ras_properties_t.

To determine if errors have occurred, software uses the function ::${t}SysmanRasGetErrors(). This will return the total number of errors of a given type
(correctable/uncorrectable) that have occurred.

When calling ::${t}SysmanRasGetErrors(), software can request that the error counters be cleared. When this is done, all counters of the specified
type (correctable/uncorrectable) will be set to zero and any subsequent calls to this function will only show new errors that have occurred.
If software intends to clear errors, it should be the only application doing so and it should store the counters in an appropriate database
for historical analysis.

When calling ::${t}SysmanRasGetErrors(), an optional pointer to a structure of type ::${t}_ras_details_t can be supplied. This will give a
breakdown of the main device components where the errors occurred.

The code below shows how to determine if RAS is supported and the current state of RAS errors:

```c
void PrintRasDetails(xet_ras_details_t* pDetails)
{
    fprintf(stdout, "    Number new resets:                %llu\n", pDetails->numResets);
    fprintf(stdout, "    Number new programming errors:    %llu\n", pDetails->numProgrammingErrors);
    fprintf(stdout, "    Number new driver errors:         %llu\n", pDetails->numDriverErrors);
    fprintf(stdout, "    Number new compute errors:        %llu\n", pDetails->numComputeErrors);
    fprintf(stdout, "    Number new non-compute errors:    %llu\n", pDetails->numNonComputeErrors);
    fprintf(stdout, "    Number new cache errors:          %llu\n", pDetails->numCacheErrors);
    fprintf(stdout, "    Number new memory errors:         %llu\n", pDetails->numMemoryErrors);
    fprintf(stdout, "    Number new link errors:           %llu\n", pDetails->numLinkErrors);
    fprintf(stdout, "    Number new display errors:        %llu\n", pDetails->numDisplayErrors);
}

void ShowRasErrors(xet_sysman_handle_t hSysmanDevice)
{
    xet_ras_properties_t props;
    if (xetSysmanRasGetProperties(hSysmanDevice, &props) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "RAS supported: %s\n", props.supported ? "yes" : "no");
        fprintf(stdout, "RAS enabled: %s\n", props.enabled ? "yes" : "no");
        fprintf(stdout, "RAS repaired: %s\n", props.repaired ? "yes" : "no");
        if (props.supported && props.enabled)
        {
            uint64_t newErrors;
            xet_ras_details_t errorDetails;
            if (xetSysmanRasGetErrors(hSysmanDevice, XET_RAS_ERROR_TYPE_UNCORRECTABLE, 1, &newErrors, &errorDetails) == XE_RESULT_SUCCESS)
            {
                fprintf(stdout, "RAS new uncorrectable errors: %llu\n", newErrors);
                if (newErrors)
                {
                    PrintRasDetails(&errorDetails);
                }
            }
            if (xetSysmanRasGetErrors(hSysmanDevice, XET_RAS_ERROR_TYPE_CORRECTABLE, 1, &newErrors, &errorDetails) == XE_RESULT_SUCCESS)
            {
                fprintf(stdout, "RAS new correctable errors: %llu\n", newErrors);
                if (newErrors)
                {
                    PrintRasDetails(&errorDetails);
                }
            }
        }
    }
}
```

For devices with sub-devices, the RAS error counters are collected per sub-device. The driver also maintains accumulated totals acrosss all sub-devices.
When ::${t}SysmanRasGetErrors() is called with a device-level SMI handle, the accumulated total errors across all sub-devices will be returned and
all accumulated totals and sub-device error counters are cleared if requested. When called with a sub-device SMI handle, only the errors relevant
to that sub-device are returned and cleared if requested.


${"#"} <a name="ev">Events</a>
Events are a way to determine is changes have occurred on a device e.g. new RAS errors. An application registers the events that it wishes to receive
notification about and then it queries to receive notifications. The query can request a blocking wait - this will put the calling application thread
to sleep until new notifications are received.

The list of all events is provided by the enumerator ::${t}_sysman_event_type_t. Before registering to receive an event from this list, the application
should first check if it is supported for a specific class of devices (devices with the same device ID). This is achieved using the function
::${t}SysmanDeviceGetProperties() and looking at the array ::${t}_sysman_properties_t.supportedEvents[::${t}_sysman_event_type_t] for each event.

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
multiple devices, it is suggested not to request event status clearing. In this way, the application can no when any event has occurred and can then
make individual requests to each device, this time requesting that the event status be cleared.

${"#"} <a name="di">Diagnostics</a>
Diagnostics is the process of taking a device offline and requesting that the hardware run self-checks and repairs. This is achieved using the function
::${t}SysmanDiagnosticsRunTests(). On return from the function, software can use the diagnostics return code (::${t}_diag_result_t) to determine the new
course of action:

1. ::${T}_DIAG_RESULT_NO_ERRORS - No errors found and workloads can resume submission to the hardware.
2. ::${T}_DIAG_RESULT_ABORT - Hardware had problems running diagnostic tests.
3. ::${T}_DIAG_RESULT_FAIL_CANT_REPAIR - Hardware had problems setting up repair. Card should be removed from the system.
4. ::${T}_DIAG_RESULT_REBOOT_FOR_REPAIR - Hardware has prepared for repair and requires a reboot after which time workloads can resume submission.

There are multiple types of diagnostic tests that can be run and these are defined in the enumeration ::${t}_diag_type_t.

When running diagnostics, the start and end tests need to be specified. To run all tests, set the start to ::${T}_DIAG_FIRST_TEST_INDEX and the end to
::${T}_DIAG_LAST_TEST_INDEX. However, it is possible to enumerate all possible tests using the function ::${t}SysmanDiagnosticsRunTests(). This will
return a list of tests in the structure ::${t}_diag_test_list_t - from this software can get the name of each test and the corresponding index value
that can be used to specify start/end points when calling the function ::${t}SysmanDiagnosticsRunTests(). If the driver doesn't return any tests
(::${t}_diag_test_list_t.count = 0) then it is not possible on that platform to run a subset of the diagnostic tests and ::${T}_DIAG_FIRST_TEST_INDEX
and ::${T}_DIAG_LAST_TEST_INDEX should be used instead for the start/stop indices respectively.

Diagnostics can only be performed at the device level. Using these functions with a sub-device SMI handle will return an unsupported error.

${"#"} <a name="sd">Sub-devices</a>
Multi-tile devices consist of sub-devices that are arranged under a logical device, otherwise known as **tiles**.

When ::${t}SysmanGet() is called with a device handle for a sub-device, the returned SMI handle can be used to manage resources only on that sub-device.

The behavior of the system resource management functions can change depending on whether they are operating on a SMI handle for a sub-devices or for
the overall device.

These differences are described in the table below:

| Component           | Device operations | Sub-device operations |
| :---                | :--- | :--- |
| [General](#smg)     | Get: Device level information<br />Set: Operating mode for all sub-devices | Get: Mostly same as device level information<br />Set: Changing operating mode not supported |
| [Power](#smp)       | Get: Power consumption of whole device, including sub-devices<br />Set: Maximum power limit of the whole device | Get: Power consumption of the sub-device<br />Set: Maximum power limit of the sub-device (if supported) |
| [Frequency](#smf)   | Get: Average frequency across sub-devices<br />Set: Set same frequency on all sub-devices | Get: Actual frequency of sub-device<br />Set: Set frequency of sub-device |
| [Activity](#sma)    | Get: Average activity across all sub-devices. | Get: Activity of sub-device. |
| [Memory](#smm)      | Get: Gives total memory allocation for all sub-devices; memory bandwidth is averaged across all sub-devices | Get: Memory bandwidth and allocation for memory located in the sub-device |
| [PCI](#smp)         | Get: PCI information at device level | Get: Same as device-level |
| [Switch](#sml)      | Get/Set: Can access all switches, including those in sub-devices | Get/Set: Can access on switches in the sub-device |
| [Temperature](#smt) | Get: Maximum temperature across all sensors of all sub-devices | Get: Maximum temperature of sensors on the sub-device |
| [Standby](#sms)     | Set: Changes standby mode for all sub-devices | Set: Change standby mode for the sub-device. |
| [Firmware](#smw)    | Get/Set: Can access all firmwares, including those in sub-devices | Get/Set: Can access firmwares in the sub-device |
| [PSU](#smy)         | Get/Set: Can access all power supplies | Get/Set: No PSUs will be enumerated |
| [Fan](#smn)         | Get/Set: Can access all fans | Get/Set: No fans will be enumerated |
| [LED](#smd)         | Get/Set: Can access all LEDs | Get/Set: No LEDs will be enumerated |

Everything can be accessed from the device-level. In some cases, software might want to limit settings to the sub-device level e.g. setting different
frequencies on each sub-device.

Note that RAS is available per sub-device. However, diagnostics can only be performed at the device level - providing an SMI handle for a sub-device
will return an error.
