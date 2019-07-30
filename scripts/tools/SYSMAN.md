${"#"} Programming Guide (Sysman)
<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    t=tags['$t']
    T=t.upper()
%>
[DO NOT EDIT]: # (generated from /scripts/tools/SYSMAN.md)

The following documents the high-level programming models and guidelines.


${"##"} Table of Contents
* [Introduction](#in)
* [Sysman handle](#hd)
* [Properties](#pr)
    + [Property identifier](#pri)
    + [Property data](#prd)
    + [Property types](#prt)
    + [Property availability](#pra)
    + [Property accuracy](#pry)
    + [Property access](#prw)
* [Accelerator assets](#ac)
* [Inventory](#iv)
* [Resources](#re)
    + [PSU resources](#reu)
    + [Temperature sensor resources](#ret)
    + [Fan resources](#ren)
    + [LED resources](#rel)
    + [Firmware resources](#rei)
    + [Frequency domain resources](#ref)
    + [Power domain resources](#rep)
    + [Power-well domain resources](#rew)
    + [Accelerator asset resources](#rea)
    + [Memory resources](#rem)
    + [Link resources](#rek)
* [Reliability, availability and serviceability (RAS)](#ra)
* [Events](#ev)
* [Diagnostics](#di)
* [Reset](#rt)
* [Sub-devices] (#sd)
* [Product reference](#pd)
    + [PVC](#pdp)
        + [PVC - PSU resources](#pdpu)
        + [PVC - Temperature sensor resources](#pdpt)
        + [PVC - Fan resources](#pdpn)
        + [PVC - LED resources](#pdpl)
        + [PVC - Firmware resources](#pdpi)
        + [PVC - Frequency domain resources](#pdpf)
        + [PVC - Power domain resources](#pdpp)
        + [PVC - Power-well domain resources](#pdpw)
        + [PVC - Accelerator asset resources](#pdpa)
        + [PVC - Memory resources](#pdpm)
        + [PVC - Link resources](#pdpk)
        + [PVC - Reliability, availability and serviceability (RAS)](#pdps)


${"#"} <a name="in">Introduction</a>
Sysman is the System Resource Management Interface (SMI) used to monitor and control the power and performance of accelerator devices.

${"#"} <a name="hd">Sysman handle</a>
An application wishing to manage power and performance for devices first needs to use the Level0 Core API to enumerate through available accelerator devices in the system and
select those of interest.

For each selected device handle, applications use the function ::${t}SysmanGet to get an SMI handle to manage system resources of the device.

![Object hierarchy](../images/tools_sysman_object_hierarchy.png?raw=true) 

There is a unique handle for each device. Multiple threads can use the handle. If concurrent accesses are made to the same device property through the handle, the last request wins.

${"#"} <a name="re">Resources</a>
A device is broken into resources. For example, the GPU frequency of a device is a resource. Resources are broken into groups, defined by the enumerator
$::{t}_resource_type_t. The groups are summarized in the table below:

| Resource group         | C API key | Resource Type |Description                                                                                                       |
| :--:                   | :--:      | :--:                          | :--:                                                                                             |
| **Inventory**          | dev       | ::${T}_RESOURCE_TYPE_DEV      | Properties provide device and driver inventory information.                                      |
| **Power domain**       | pwr       | ::${T}_RESOURCE_TYPE_PWR      | Properties permit monitoring of power consumption and setting operating power limits.            |
| **Frequency domain**   | freq      | ::${T}_RESOURCE_TYPE_FREQ     | Properties permit monitoring of frequency and setting frequency limits.                          |
| **Utilization**        | util      | ::${T}_RESOURCE_TYPE_UTIL     | Properties permit monitoring of activity of different component                                  |
| **Memory**             | mem       | ::${T}_RESOURCE_TYPE_MEM      | Properties permit monitoring of memory utilization.                                              |
| **Link**               | link      | ::${T}_RESOURCE_TYPE_LINK     | Properties permit monitoring utilization of PCIe and peer-to-peer links.                         |
| **Temperature**        | temp      | ::${T}_RESOURCE_TYPE_TEMP     | Properties permit monitoring temperatures.                                                       |
| **Standby**            | stby      | ::${T}_RESOURCE_TYPE_STBY     | Properties permit setting standby behavior of different components of the device.                |
| **Firmware**           | fw        | ::${T}_RESOURCE_TYPE_FW       | Properties provide firmware version and uploading new images.                                    |
| **PSU**                | psu       | ::${T}_RESOURCE_TYPE_PSU      | Properties provide status information about power supplies.                                      |
| **Fan**                | fan       | ::${T}_RESOURCE_TYPE_FAN      | Properties permit monitoring and controlling fans.                                               |
| **LED**                | led       | ::${T}_RESOURCE_TYPE_LED      | Properties permit changing the behavior of LEDs.                                                 |

Each resource in the system is identified uniquely by one of the values in the enumerator ::${t}_resid_t. Some of these resources are expected to be available on all devices
and are listed in the table below:

| Resource ID                 | Description                                                |
| :--:                        | :--:                                                       |
| ::${T}_RESID_DEV_INVENTORY  | Provides access to device inventory information            |
| ::${T}_RESID_PWR_PACKAGE    | Provides access to total device power telemetry and limits |
| ::${T}_RESID_FREQ_GPU       | Provides access to GPU frequency                           |
| ::${T}_RESID_FREQ_LOCAL_MEM | Provides access to local memory frequency                  |
| ::${T}_RESID_UTIL_GPU       | Provides access to GPU utilization counters                |
| ::${T}_RESID_MEM_LOCAL      | Provides access to local memory utilization counters       |
| ::${T}_RESID_LINK_PCIE      | Provides access to PCIe bandwidth counters                 |
| ::${T}_RESID_TEMP_PACKAGE   | Provides access to device temperature                      |

It's possible to get a list of all available resources using the function ::${t}SysmanGetResources(), as shown in the example below:

```c
void ShowAllResources(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numResources;
    if (xetSysmanGetResources(hSysmanDevice, XET_RESOURCE_TYPE_ANY, &numResources, NULL) == XE_RESULT_SUCCESS)
    {
        if (numResources)
        {
            xet_resid_info_t* pInfo = (xet_resid_info_t*)malloc(numResources * sizeof(xet_resid_info_t));
            if (xetSysmanGetResources(hSysmanDevice, XET_RESOURCE_TYPE_ANY, &numResources, pInfo) == XE_RESULT_SUCCESS)
            {
                for (uint32_t i = 0; i < numResources; i++)
                {
                    fprintf(stdout, "Resource %d: %s = %s\n", pInfo->id, pInfo->pName, pInfo->pDesc);
                }
            }
            free(pInfo);
        }
    }
}
```

It is also possible to get a list of all resources of a given type. The example below shows how to get a list of all fans associated with a device:

```c
void ShowFans(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numFans;
    if (xetSysmanGetResources(hSysmanDevice, XET_RESOURCE_TYPE_FAN, &numFans, NULL) == XE_RESULT_SUCCESS)
    {
        if (numFans)
        {
            xet_resid_info_t* pInfo = (xet_resid_info_t*)malloc(numFans * sizeof(xet_resid_info_t));
            if (xetSysmanGetResources(hSysmanDevice, XET_RESOURCE_TYPE_FAN, &numFans, pInfo) == XE_RESULT_SUCCESS)
            {
                for (uint32_t i = 0; i < numFans; i++)
                {
                    fprintf(stdout, "    Fan %s\n", pInfo->pName);
                }
            }
            free(pInfo);
        }
    }
}
```

Finally, it is possible to provide a list of resources and get information about their availability on a device using the function ::${t}SysmanGetResourceInfo().
The example below shows how to check whether specific resources are supported:

```c
void CheckResources(xet_sysman_handle_t hSysmanDevice)
{
    xet_resid_info_t resources [] =
    {
        { XET_RESID_UTIL_GPU },
        { XET_RESID_UTIL_COMPUTE },
        { XET_RESID_UTIL_MEDIA },
        { XET_RESID_UTIL_VIDEO_DECODE },
        { XET_RESID_UTIL_VIDEO_ENCODE }
    };
    uint32_t count = sizeof(resources) / sizeof(resources[0]);
    if (xetSysmanGetResourceInfo(hSysmanDevice, count, resources) == XE_RESULT_SUCCESS)
    {
        for (uint32_t i = 0; i < count; i++)
        {
            fprintf(stdout, "Resource %d: %s = %s\n", resources[i].id, resources[i].pName, resources[i].available ? "supported" : "not supported");
        }
    }
}
```


${"#"} <a name="pr">Properties</a>
For every resource type, there are a set of **properties** that can be accessed. These correspond to either telemetry or controls that modify the behavior of the resource.

In the following sections, we will discuss where to get the list of properties, the type of properties, how to determine which are available, how to determine if
an application has permissions to modify properties, how often properties can be accessed and how to read and write property values.

${"##"} <a name="pri">Property identifier</a>
All properties are defined in the enumeration ::${t}_resprop_t. As an example, consider the property used to read the current fan speed in RPM: ::${T}_RESPROP_FAN_SPEED_RPM.
Note that resource type C API key (fan) is contained in the name of the property identifier following RESPROP. This provides an easy visual way to determine which resource
type the property can be used with.

${"##"} <a name="prd">Property data</a>
For every property, there is a corresponding property data structure that can be used to get the current value or set a new value. The name of the property structure
is given by the writing the property identifier in lowercase and adding "_t" to the end. For example, the property ::${T}_RESPROP_FAN_SPEED_RPM has a corresponding
data structure ::${t}_resprop_fan_speed_rpm_t.

${"##"} <a name="prt">Property types</a>
There are four types of properties:

- **ro static** - Properties that are configured when the device boots and not intended to change until the device is shutdown. The value of these properties cannot be changed
by software.
- **ro dynamic** - Properties whose values change dynamically as the device runs. These properties are read-only and can only be monitored.
- **rw dynamic** - Runtime controls - Properties that can be controlled at runtime and modify the behavior of a device. The value of these properties can be changed by software
and read in order to get the last value that was set.
- **wo dynamic** - Runtime triggers - Properties that can be controlled at runtime and modify the behavior of a device. The value of these properties can be changed by software
but cannot be read back to get the last value - these are properties that trigger some behavior but don't have a backing value.

${"##"} <a name="pra">Property availability</a>
Determining if properties are supported and accessible is achieved by calling the API function ::{t}SysmanGetPropertyInfo(). The function is called with an array that indicates
the property identifiers of interest. On return, the array is populated with the API support (one of ::${t}_prop_support_t) and the access permissions (::${t}_prop_access_t)
for each property. API support indicates if the property is supported by the current version of the API, the device class and the device. It is possible that the API supports
a property but not for a particular device class or device. Access permissions are specific to a device and so should be checked for every device.

The example below shows how an application can determine if it can set a fixed fan speed on a specific device:

```c
bool HaveFanControl(xet_sysman_handle_t hSysmanDevice)
{
    bool ret = false;
    xet_resprop_info_t info;
    info.property = XET_RESPROP_FAN_FIXED_SPEED;
    if (xetSysmanGetPropertyInfo(hSysmanDevice, 1, &info) == XE_RESULT_SUCCESS)
    {
        if ((info.support & XET_PROP_SUPPORT_DEVICE) &&
            (info.access & XET_PROP_ACCESS_WRITE_PERMISSIONS))
        {
            ret = true;
        }
    }
    return ret;
}
```

${"##"} <a name="pry">Property accuracy</a>
All readable dynamic properties have a minimum sample-rate that is related to the time interval between updates of the underlying telemetry. If the property returns the
instantaneous value at the time of reading, we say that the sample interval is 0. If the property will have an updated value every 1 millisecond, we say that the
sample interval is 1 millisecond. This means that software should not expect an accuracy of this property if sampled faster than 1 millisecond.

Similarly, writable dynamic properties have a minimum update-rate that is related to the time it takes for the hardware to accept the new value. Software can update
the property faster than this rate, but it is unlikely that the new value will take effect immediately. If hardware changes immediately when a new property value is
written, we say that the update interval is 0. If the property will only react to a new value after 1 millisecond, we say that the update interval is 1 millisecond.

Software can determine the minimum sample and update intervals for each property by using the function ::{t}SysmanGetPropertyInfo(). The example below shows how
to determine these intervals for frequency control and monitoring the resolved frequency:

```c
void GetFreqIntervals(xet_sysman_handle_t hSysmanDevice)
{
    xet_resprop_info_t info[] =
    {
        { XET_RESPROP_FREQ_RANGE },
        { XET_RESPROP_FREQ_RESOLVED_FREQ },
    };
    if (xetSysmanGetPropertyInfo(hSysmanDevice, sizeof(info) / sizeof(info[0]), info) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "Frequency update interval: %u microseconds\n", info[0].minSetInterval);
        fprintf(stdout, "Frequency sample interval: %u microseconds\n", info[1].minGetInterval);
    }
}
```

${"##"} <a name="prw">Property access</a>
To read/write a property, use the functions ::${t}SysmanGetProperties() and ::${t}SysmanSetProperties() respectively.

Software passes in an array of ::${t}_resprop_request_t entries. Each entry specifies the resource identifier and the property identifier to be read/written. In the case
of writing data, the entry also stores the new values.

If all accesses complete successfully, the function will return ::${X}_RESULT_SUCCESS. If some of the accesses fail, the function will return ::${X}_RESULT_ERROR_UNKNOWN
in which case software should check the ::${t}_resprop_request_t.status of each entry to determine the resource/properties that had problems.

The code below shows how to read the fan speed and handle errors:

```c
void ShowFanInfo(xet_sysman_handle_t hSysmanDevice, xet_resid_t FanId)
{
    struct FanData
    {
        ${t}_resprop_fan_speed_rpm_t        speedRpm;
        ${t}_resprop_fan_speed_percent_t    speedPercent;
    };

    FanData data;
    ${t}_resprop_request_t requests[] = 
    {
        { FanId, ${T}_RESPROP_FAN_SPEED_RPM,       &data.speedRpm,       sizeof(data.speedRpm) },
        { FanId, ${T}_RESPROP_FAN_SPEED_PERCENT,   &data.speedPercent,   sizeof(data.speedPercent) },
    };

    ${x}_result_t res = ${t}SysmanGetProperties(hSysmanDevice, sizeof(requests) / sizeof(requests[0]), requests);

    if ((res == ${X}_RESULT_SUCCESS) || (res == ${X}_RESULT_ERROR_UNKNOWN))
    {
        if (requests[0].status == ${X}_RESULT_SUCCESS)
        {
            fprintf(stdout, "        Fan %u: speed = %u rpm\n", FanId, data.speedRpm.speed);
        }
        else
        {
            fprintf(stderr, "        Fan %u: error reading ${T}_RESPROP_FAN_SPEED_RPM\n", FanId);
        }
        if (requests[1].status == ${X}_RESULT_SUCCESS)
        {
            fprintf(stdout, "        Fan %u: speed = %u %%\n", FanId, data.speedPercent.speed);
        }
        else
        {
            fprintf(stderr, "        Fan %u: error reading ${T}_RESPROP_FAN_SPEED_PERCENT\n", FanId);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Can't request data.\n");
    }
}
```


${"#"} <a name="re">Resources</a>

${"##"} <a name="red">Device resource</a>
The device resource type (::${T}_RESOURCE_TYPE_DEV) has one resource ID (::${T}_RESID_DEV_INVENTORY) can be used to obtain inventory information:

- Serial number
- Board number
- Device ID
- Vendor ID
- Driver version
- PCI bars

${"##"} <a name="reu">PSU resources resources</a>
These resources provide information about power supply units attached to the device.

- Read maximum amp limit
- Monitor voltage status
- Monitor fan failure
- Monitor heatsink temperature
- Monitor current amps


${"##"} <a name="ret">Temperature sensor resources</a>
These resources provides access to temperature sensors on the device:

- Monitor temperature sensor value


${"##"} <a name="ren">Fan resources</a>
These resources provides access to fans on the device:

- Read maximum speed
- Monitor fan speed
- Set fixed fan speed
- Set fan speed table (table of temperature-speed points)

Fan speeds can be given in units of RPM (revolutions per minute) or percentage of maximum RPM.

Software can either request fixed fan speed, including turning the fan off, or depending on hardware capabilities, as a fan speed table. This is a table of temperature/speed
points. When programmed, the hardware will dynamically choose the fan speed based on the maximum temperature measured on the chip. Software should use the function
::${t}SysmanGetPropertyInfo() with the property ::${T}_RESPROP_FAN_SPEED_TABLE to determine if the hardware supports this mode.


${"##"} <a name="rel">LED resources</a>
These resources provide access to LEDs on the device:

- Turn LED on/off
- Change LED color

Not all LEDs support color control. Software should use the function ::${t}SysmanGetPropertyInfo() with the property ::${T}_RESPROP_LED_RGB_CAP to determine if the LED
supports programming the R/G/B color values.


${"##"} <a name="rei">Firmware resources</a>
These resources provide access to firmwares on the device.

- Read firmware name
- Read firmware version
- Verify firmware image
- Flash firmware image

Not all firmwares can be flashed through this API. Software should use the function ::${t}SysmanGetPropertyInfo() with the property ::${T}_RESPROP_FW_FLASH
to determine if write access is permitted.


${"##"} <a name="ref">Frequency domain resources</a>
These resources provide access to device frequencies:

- Get available frequencies
- Monitor frequency
- Monitor frequency throttle stats and reasons
- Set frequency range (min/max)


${"##"} <a name="rep">Power domain resources</a>
These resources provide access to device power limits:

- Monitor power
- Set power limits (sustained, burst, peak)

The PSU (Power Supply Unit) provides power to a device. The amount of power drawn by a device is a function of the voltage and frequency, both of which are controlled
by the Punit, a micro-controller on the device. If the voltage and frequency are two high, two conditions can occur:

1. Over-current - This is where the current drawn by the device exceeds the maximum current that the PSU can supply. The PSU asserts a signal when this occurs,
and it is processed by the Punit.
2. Over-temperature - The device is generating too much heat that cannot be dissipated fast enough. The Punit monitors temperatures and reacts when the sensors show
the maximum temperature exceeds the threshold TjMax (typically 100 degrees celcius).

When either of these conditions occurs, the Punit throttles the frequencies/voltages of the device down to their minimum values, severely impacting performance.
The Punit avoids such severe throttling by measuring the actual power being consumed by the system and slowly throttling the frequencies down when power exceeds some limits.
Three limits are monitored by the Punit:

| Limit     | Window        | Description                                                                                                                                                                                                                |
| :--:      | :--:          | :--:                                                                                                                                                                                                                       |
| Peak      | Instantaneous | Punit tracks the instantaneous power. When this exceeds a programmable threshold, the Punit will aggressively throttle frequencies/voltages. The threshold is referred to as PL4 - Power Limit 4 - or peak power.          |
| Burst     | 2ms           | Punit tracks the 2ms weighted moving average of power. When this exceeds a programmable threshold, the Punit starts throttling frequencies/voltages. The threshold is referred to as PL2 - Power Limit 2 - or burst power. |
| Sustained | 28sec         | Punit tracks the 28sec weighted moving average of power. When this exceeds a programmable threshold, the Punit throttles frequencies/voltages. The threshold is referred to as PL1 - Power Limit 1 - or sustained power.   |

Peak power limit is generally greater than the burst power limit which is generally greater than the sustained power limit. The default factory values are tuned assuming
the device is operating at normal temperatures running significant workloads:

- The peak power limit is tuned to avoid tripping the PSU over-current signal for all but the most intensive compute workloads. Most workloads should be able to run at maximum
frequencies without hitting this condition.
- The burst power limit permits most workloads to run at maximum frequencies for short periods.
- The sustained power limit will be triggered if high frequencies are requested for lengthy periods (28sec) and the frequencies will be throttled if the high requests and
utilization of the device continues.

The factory defaults tend to be conservative and attempt to provide best behavior for a variety of workloads. Devices that will be running specialized workloads can
benefit from raising these limits. This is the purpose of the power domain resource.

Frequency throttling is the term given to the situation where the Punit needs to resolve the software frequency requests to lower values in order to bring power
and/or thermals under control. The reasons for throttling can be obtained using the function ::${t}SysmanGetProperties() with the property ::${T}_RESPROP_FREQ_THROTTLE_REASONS.
This will return a bitfield of reasons taken from the enumerator ::${t}_freq_throttle_reasons_t.


${"##"} <a name="rew">Standby resources</a>
These resources provide access to standby settings:

- Set standby promotion mode

Power-well domains are parts of a device that can be powered off when there is no activity. While this saves power, it can also come with a performance cost given the
latency exiting from a power-gated (sleep) state. Generally the hardware effectively manages this trade-off, however properties of power-well domain resources enable
software to influence how easy it is for the hardware to promote the hardware to sleep states when idle.

As with frequency and power domains, power-well domains come with a list of enclosed accelerator assets. An asset can be found in only one power-well domain. When the
power-well domain enters a sleep state, all accelerator assets in that domain are no longer connected to power.

${"##"} <a name="rea">Utilization resources</a>
These resources provide access to activity statistics for a device:

- Monitor utilization

An accelerator asset resource enables monitoring the activity of one or more accelerator assets. Activity is defined as the wall time that assets are executing
workloads.

Software can query the accelerator assets that are included in the activity counters. The same accelerator asset resources will be available for all devices with
the device ID. In general, the accelerator asset resource with index 0 will provide the global activity of the entire devices. However this should not be assumed
and software should always enumerate through all these resources and choose the ones that cover the relevant accelerator assets.

The code example below shows how software can determine the indices, if any, of resources that measure only the activity of media accelerators:


${"##"} <a name="rem">Memory resources</a>
Memory resources provide access to memory statistics:

- Monitor memory bandwidth
- Monitor memory utilization


${"##"} <a name="rek">Link resources</a>
Link resources provide access to link statistics:

- Read available link speeds
- Monitor link bandwidth
- Set link speed range

Software can determine if it is possible to change the link speed (number of lanes, frequency) by calling the function ::${t}SysmanGetPropertyInfo()
and passing in the property ::${T}_RESPROP_LINK_SPEED_RANGE. If the resulting value of ::${t}_resprop_info_t.access indicates write access, then it is
possible to change the speed of the link.


${"#"} <a name="ra">Reliability, availability and serviceability (RAS)</a>
Devices may expose RAS telemetry. Rather than call out every type of unique metric, we define the set of orthogonal properties that can be combined to describe any metric.
This consists of error types ::${t}_ras_error_type_t (e.g. fatal and non-fatal) and error structural locations ::${t}_ras_error_loc_t (e.g. L3 cache).

An example of a RAS metric would be HBM correctable single-bit errors:

- Type: ::${T}_RAS_ERROR_TYPE_NON_FATAL | ::${T}_RAS_ERROR_TYPE_CORRECTABLE | ::${T}_RAS_ERROR_TYPE_SINGLE_BIT
- Location: ::${T}_RAS_ERROR_LOC_MAIN_MEM

The reason for making these properties bitfields is so that when querying errors, it is possible to filter the list of metrics based on any combination. For example, the
following filter will show all RAS telemetry for errors that were corrected anywhere in the device:

- Type: ::${T}_RAS_ERROR_TYPE_CORRECTABLE
- Location: ::${T}_RAS_ERROR_LOC_ALL

The API defines a RAS error filter ::${t}_ras_filter_t with the following memebers:

| Member                  | Description                                                                                                                  |
| :--:                    | :--:                                                                                                                         |
| Resource ID             | Only show errors related to a particular resource, otherwise all resources if this member is set to ::${T}_RESOURCE_TYPE_ANY |
| RAS error type          | Bitfield of one or more of ::${t}_ras_error_type_t                                                                           |
| RAS structural location | Bitfield of one or more of ::${t}_ras_error_loc_t                                                                            |
| Threshold               | Only show errors if they have occurred more than the specified amount of times                                               |

Macros define two generic filters:

- ::${T}_RAS_FILTER_ALL_COUNTERS - Show all error counters independent of whether errors have occurred
- ::${T}_RAS_FILTER_ALL_ERRORS - Show only error counters where at least one error has occurred

The function ::${t}SysmanGetRasErrors() is used to get the current status of error metrics. When calling this function, an array of elements ::${t}_ras_error_t
is provided where the error counter data will be returned. If the provided size of the array is too small to match the errors matching the filter, an error
will be returned and the required size if provided. The function ::${t}SysmanGetRasConfig() can be used to find the total number of errors counters that are available
(::${t}_ras_config_t.numRas) and hence the total array size that should be passed into the ::${t}SysmanGetRasErrors() function.

Note that for each error, the interpretation of the data depends on the provided error type in ::${t}_ras_error_t.dataType. Some errors may be counters
(::${T}_RAS_DATA_TYPE_COUNTER) while other errors may only indicate that errors have occurred (::${T}_RAS_DATA_TYPE_OCCURRED).

When calling ::${t}SysmanGetRasErrors(), it is possible to request that the error data (counter or occurrence) be cleared. This means that if the filter threshold is set
to 1 or more, the next call to ::${t}SysmanGetRasErrors() will only show new errors that have occurred since the last call. The counters are cleared per
application. This means that if there are multiple threads calling this function and requesting clearing of the counters, only one thread will see the new errors.

The code below shows how to get a list of all available error counters. This is something that an application could do during initialization:

```c
void ShowRasCounters(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numRas;
    xet_ras_filter_t filter = XET_RAS_FILTER_ALL_COUNTERS;
    if (xetSysmanGetRasErrors(hSysmanDevice, &filter, false, &numRas, NULL) == XE_RESULT_SUCCESS)
    {
        xet_ras_error_t* pCounters = (xet_ras_error_t*)malloc(numRas * sizeof(xet_ras_error_t));

        if (xetSysmanGetRasErrors(hSysmanDevice, &filter, false, &numRas, pCounters) == XE_RESULT_SUCCESS)
        {
            for (uint32_t i = 0; i < numRas; i++)
            {
                fprintf(stdout, "RAS error %s: value=%llu\n",
                    pCounters[i].pName, pCounters[i].data);
            }
        }
    }
}
```

The function ::${t}SysmanGetRasConfig() returns structure ::${t}_ras_config_t. This gives the total number of RAS errors available on the device
(::${t}_ras_config_t.numRas). It also gives a quick snapshot of all RAS error types (::${t}_ras_config_t.rasTypes) and all RAS error structural locations
(::${t}_ras_config_t.rasLocations) - these are not an enumeration all error counters (use ::${t}SysmanGetRasErrors() for that) but
a merging of all possible types (::${t}_ras_error_type_t) and locations (::${t}_ras_error_loc_t) so that software can quickly determine what might
be supported. The structure also indicates all structural locations where RAS counters are enabled (::${t}_ras_config_t.enabled).

If ::${t}_ras_config_t.rasLocations is not zero, it indicates the structural locations where RAS is supported. The function ::${t}SysmanRasSetup() can be used to
enable/disable RAS at any of those structural locations. On return, the function indicates the structual locations where RAS is enabled. The code below
shows how to determine if RAS is enabled for the local memory:

```c
void LocalMemoryRasConfig(xet_sysman_handle_t hSysmanDevice)
{
    xet_ras_config_t config;
    if (xetSysmanGetRasConfig(hSysmanDevice, &config) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "Local memory:\n");
        if (config.numRas)
        {
            fprintf(stdout, "    RAS support: yes\n");
            fprintf(stdout, "    RAS enabled: %s\n", (config.enabled & XET_RAS_ERROR_LOC_MAIN_MEM) ? "yes" : "no");
        }
        else
        {
            fprintf(stdout, "    RAS support: no\n");
        }
    }
}
```


${"#"} <a name="ev">Events</a>
Events are a way to determine is changes have occurred on a device e.g. new RAS errors. An application registers the events that it wishes to receive notification
about and then it queries to receive notifications. The query can request a blocking wait - this will put the calling application thread to sleep until new notifications
are received.

The list of all events is provided by the enumerator ::${t}_sysman_event_type_t. Before registering to receive an event from this list, the application should first
check if it is supported for a specific class of devices (devices with the same device ID). This is achieved using the function ::${t}SysmanSupportedEvents().

For events supported on a given device, the application uses the function ::${t}SysmanRegisterEvents() to register to receive notifications. It can stop notifications
at any time using the function ::${t}SysmanUnregisterEvents().

Finally, the application uses the function ::${t}SysmanGetEvents() to get a list of new notifications that have occurred since the last time it checked.

The application can choose to block for events by setting timeout to ::${T}_EVENT_WAIT_INFINITE or it can set to zero if it wishes to get the current status without
blocking.

The event notifications are returned as a bitfield of event types. It is up to the application to then enumerate the corresponding device properties to determine
where the events occurred if that is required.

When calling ::${t}SysmanGetEvents(), the application can request that the status be cleared. The driver will return the current status and clear it internally.
The next call to the function will return no notifications until new events occur. If the application does not request that event list be cleared, subsequent calls
to this function will show the same notifications and any new notifications.

The first argument of ::${t}SysmanGetEvents() specifies the SMI handle for the device on which event notifications wish to be received. However, this can be set to
NULL in order to query event notifications across all devices for which the application has created SMI handles. When querying across multiple devices, it is suggested
not to request event status clearing. In this way, the application can no when any event has occurred and can then make individual requests to each device, this time
requesting that the event status be cleared.


${"#"} <a name="di">Diagnostics</a>
Diagnostics is the process of taking a device offline and requesting that the hardware run self-checks and repairs. This is achieved using the function
::${t}SysmanRunDiagnosticTests(). On return from the function, software can use the diagnostics return code (::${t}_diag_result_t) to determine the new course of action:

1. ::${T}_DIAG_RESULT_NO_ERRORS - No errors found and workloads can resume submission to the hardware.
2. ::${T}_DIAG_RESULT_ABORT - Hardware had problems running diagnostic tests.
3. ::${T}_DIAG_RESULT_FAIL_CANT_REPAIR - Hardware had problems setting up repair. Card should be removed from the system.
4. ::${T}_DIAG_RESULT_REBOOT_FOR_REPAIR - Hardware has prepared for repair and requires a reboot after which time workloads can resume submission.

There are multiple types of diagnostic tests that can be run and these are defined in the enumeration ::${t}_diag_type_t.

When running diagnostics, the start and end tests need to be specified. To run all tests, set the start to ::${T}_DIAG_FIRST_TEST_INDEX and the end to
::${T}_DIAG_LAST_TEST_INDEX. However, it is possible to enumerate all possible tests using the function ::${t}SysmanGetDiagnosticTests(). This will return
a list of tests in the structure ::${t}_diag_test_list_t - from this software can get the name of each test and the corresponding index value that can be
used to specify start/end points when calling the function ::${t}SysmanRunDiagnosticTests(). If the driver doesn't return any tests (::${t}_diag_test_list_t.count = 0)
then it is not possible on that platform to run a subset of the diagnostic tests and ::${T}_DIAG_FIRST_TEST_INDEX and ::${T}_DIAG_LAST_TEST_INDEX should be
used instead for the start/stop indices respectively.


${"#"} <a name="rt">Reset</a>
A device can be reset (PCI device reset) can be achieved using the function ::${t}SysmanDeviceReset().


${"#"} <a name="sd">Sub-devices</a>
Multi-tile devices consists of sub-devices that are arranged under a logical device. At this stage, no resources are supported for managing resources on sub-devices and
an attempt to call ::${t}SysmanGet() with a device handle for a sub-device will receive an error ::${X}_RESULT_ERROR_UNSUPPORTED. Resources managed at the device level
will impact the configuration of sub-devices.
