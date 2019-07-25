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
    + [Property groups and lists](#prg)
    + [Property types](#prt)
    + [Property availability](#pra)
    + [Property value access](#prw)
    + [Property accuracy](#pry)
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
        + [PVC - PVC - Reliability, availability and serviceability (RAS)](#pdps)


${"#"} <a name="in">Introduction</a>
Sysman is the System Resource Management Interface (SMI) used to monitor and control accelerator power and performance..

${"#"} <a name="hd">Sysman handle</a>
An application wishing to manage power and performance for devices first needs to use the Level0 Core API to enumerate through available accelerator devices in the system and
select those of interest.

For each selected device handle, applications use the XetSysman interface to create a Sysman handle for the device.

![Object hierarchy](../images/tools_sysman_object_hierarchy.png?raw=true) 

The application uses the function ::${t}SysmanCreate() to create a Sysman handle for a device. By default, the handle only permits monitoring of system resources,
but the application can request write access using the flag ::${T}_SYSMAN_INIT_FLAGS_WRITE so that it can also make system configuration changes through the handle.
At the time of creation, no check is made to determine if the application has the necessary access rights since this is a function of specific configuration knobs.
Instead the application can use other functions to determine what it has read access to and what it has write access to.

An application can create multiple handles to the same underlying device. For example, an application could create a handle with only read access to a devices power and
performance telemetry and have a separate handle that it uses for making system configuration changes, or it could opt to use the same handle for both.

Multithreaded accesses using the same Sysman handle are premitted and where possible, the accesses will be lock-free. The exception would be a simultaneous change to the same
configuration, whether through the same Sysman handle or through multiple Sysman handles to the same device - these requests will be serialized at the device layer.

When the first Sysman handle is created for a given device by an application, the driver creates memory resources for that device. Any subsequent Sysman handles update the
reference count on this underlying storage. Only once all Sysman handles for a given device are destroyed will the underlying memory be freed.

${"#"} <a name="pr">Properties</a>
Most telemetry and configuration controls are accessed through **properties**.

${"##"} <a name="prg">Property groups and lists</a>
Properties are broken into groups. For each group, there is an enumerator for all properties (property list)

| Property group         | C API key | Property list |Description                                                                                                      |
| :--:                   | :--:      | :--:                         | :--:                                                                                             |
| **Device**             | device    | ::${t}_device_properties_t   | Properties provide device and driver inventory information and the ability to reset.             |
| **PSU**                | psu       | ::${t}_psu_properties_t      | Properties provide status information about power supplies.                                      |
| **Temperature sensor** | temp      | ::${t}_temp_properties_t     | Properties permit monitoring temperature sensors.                                                |
| **Fan**                | fan       | ::${t}_fan_properties_t      | Properties permit monitoring and controlling fans.                                               |
| **LED**                | led       | ::${t}_led_properties_t      | Properties permit changing the behavior of LEDs.                                                 |
| **Firmware**           | firmware  | ::${t}_firmware_properties_t | Properties provide firmware version and uploading new images.                                    |
| **Power domain**       | pwr       | ::${t}_pwr_properties_t      | Properties permit monitoring of power consumption and setting operating power limits.            |
| **Frequency domain**   | freq      | ::${t}_freq_properties_t     | Properties permit monitoring of frequency and setting frequency limits.                          |
| **Power-well domain**  | pwrwell   | ::${t}_pwrwell_properties_t  | Properties permit monitoring the sleep states of the chip and changing the sleep state behavior. |
| **Accelerator asset**  | accel     | ::${t}_accel_properties_t    | Properties permit monitoring of activity of accelerator assets.                                  |
| **Memory**             | mem       | ::${t}_mem_properties_t      | Properties permit monitoring of memory utilization and errors.                                   |
| **Link**               | link      | ::${t}_link_properties_t     | Properties permit monitoring utilization and errors of peer-to-peer links.                       |

For each group, there are separate API functions that determine access capabilities for a property and to read/write property values.
Separation of the API in this way groups common functionality together.

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
Determining if properties are supported and accessible is achieved by calling the API function xetSysmanAvailableXxxProperties(), where **xxx** is replaced with the
C API key from the table above for the appropriate group (**Xxx** means that the first character in the key is capitalized, **XXX** means that all characters in the key are capitalized).

Each function xetSysmanAvailableXxxProperties() receives an array or requests. Each request specifies a property. On return from the function, each request will indicate the API support
(one of ::${t}_prop_support_t) and the access permissions (::${t}_prop_access_t). API support indicates if the property is supported by the current version of the API, the device class
and the device. It is possible that the API supports a property but not for a particular device class or device. Access permissions are specific to a device and so should be checked for
every device.

The table below gives the function and request structure needed to determine the availability for any property in each group:

| Property group         | Property availability func               | Property availability request struct | Properties enum type         |
| :--:                   | :--:                                     | :--:                                 | :--:                         |
| **Device**             | ::${t}SysmanAvailableDeviceProperties    | ::${t}_device_prop_capability_t      | ::${t}_device_properties_t   |
| **PSU**                | ::${t}SysmanAvailablePsuProperties       | ::${t}_psu_prop_capability_t         | ::${t}_psu_properties_t      |
| **Temperature sensor** | ::${t}SysmanAvailableTempProperties      | ::${t}_temp_prop_capability_t        | ::${t}_temp_properties_t     |
| **Fan**                | ::${t}SysmanAvailableFanProperties       | ::${t}_fan_prop_capability_t         | ::${t}_fan_properties_t      |
| **LED**                | ::${t}SysmanAvailableLedProperties       | ::${t}_led_prop_capability_t         | ::${t}_led_properties_t      |
| **Firmware**           | ::${t}SysmanAvailableFirmwareProperties  | ::${t}_firmware_prop_capability_t    | ::${t}_firmware_properties_t |
| **Power domain**       | ::${t}SysmanAvailablePwrProperties       | ::${t}_pwr_prop_capability_t         | ::${t}_pwr_properties_t      |
| **Frequency domain**   | ::${t}SysmanAvailableFreqProperties      | ::${t}_freq_prop_capability_t        | ::${t}_freq_properties_t     |
| **Power-well domain**  | ::${t}SysmanAvailablePwrwellProperties   | ::${t}_pwrwell_prop_capability_t     | ::${t}_pwrwell_properties_t  |
| **Accelerator asset**  | ::${t}SysmanAvailableAccelProperties     | ::${t}_accel_prop_capability_t       | ::${t}_accel_properties_t    |
| **Memory**             | ::${t}SysmanAvailableMemProperties       | ::${t}_mem_prop_capability_t         | ::${t}_mem_properties_t      |
| **Link**               | ::${t}SysmanAvailableLinkProperties      | ::${t}_link_prop_capability_t        | ::${t}_link_properties_t     |

The example below shows how an application can determine if it can set a fixed fan speed on a specific device:

```c
bool HaveFanControl(xet_sysman_handle_t hSysmanDevice)
{
    bool ret = false;
    ${t}_fan_prop_capability_t cap;
    cap.property = ${T}_FAN_PROP_FIXED_SPEED;
    if (${t}SysmanAvailableFanProperties(hSysmanDevice, 1, &cap) == ${X}_RESULT_SUCCESS)
    {
        if ((cap.support & ${T}_PROP_SUPPORT_DEVICE) &&
            (cap.access & ${T}_PROP_ACCESS_WRITE_PERMISSIONS))
        {
            ret = true;
        }
    }
    return ret;
}
```

${"##"} <a name="prw">Property access</a>
To read/write a property, a common code syntax is used for all properties. There is an enumerator for the property which gives it a unique ID within a property group, there is a property structure
to hold the associated value and there is a request structure used to make read/write requests.

The table below lists all property group enumerator types and corresponding request structures and get/set functions:

| Property group         | Property enum type           | Request struc                       | Get property func                  | Set property func                 |
| :--:                   | :--:                         | :--:                                | :--:                               | :--:                              |
| **Device**             | ::${t}_device_properties_t   |  ::${t}_device_property_request_t   | ::${t}SysmanGetDeviceProperties    | ::${t}SysmanSetDeviceProperties   |
| **PSU**                | ::${t}_psu_properties_t      |  ::${t}_psu_property_request_t      | ::${t}SysmanGetPsuProperties       | ::${t}SysmanSetPsuProperties      |
| **Temperature sensor** | ::${t}_temp_properties_t     |  ::${t}_temp_property_request_t     | ::${t}SysmanGetTempProperties      |                                   |
| **Fan**                | ::${t}_fan_properties_t      |  ::${t}_fan_property_request_t      | ::${t}SysmanGetFanProperties       | ::${t}SysmanSetFanProperties      |
| **LED**                | ::${t}_led_properties_t      |  ::${t}_led_property_request_t      | ::${t}SysmanGetLedProperties       | ::${t}SysmanSetLedProperties      |
| **Firmware**           | ::${t}_firmware_properties_t |  ::${t}_firmware_property_request_t | ::${t}SysmanGetFirmwareProperties  | ::${t}SysmanSetFirmwareProperties |
| **Power domain**       | ::${t}_pwr_properties_t      |  ::${t}_pwr_property_request_t      | ::${t}SysmanGetPwrProperties       | ::${t}SysmanSetPwrProperties      |
| **Frequency domain**   | ::${t}_freq_properties_t     |  ::${t}_freq_property_request_t     | ::${t}SysmanGetFreqProperties      | ::${t}SysmanSetFreqProperties     |
| **Power-well domain**  | ::${t}_pwrwell_properties_t  |  ::${t}_pwrwell_property_request_t  | ::${t}SysmanGetPwrwellProperties   | ::${t}SysmanSetPwrwellProperties  |
| **Accelerator asset**  | ::${t}_accel_properties_t    |   ::${t}_accel_property_request_t   | ::${t}SysmanGetAccelProperties     |                                   |
| **Memory**             | ::${t}_mem_properties_t      |  ::${t}_mem_property_request_t      | ::${t}SysmanGetMemProperties       | ::${t}SysmanSetMemProperties      |
| **Link**               | ::${t}_link_properties_t     |  ::${t}_link_property_request_t     | ::${t}SysmanGetLinkProperties      | ::${t}SysmanSetLinkProperties     |

The get/set functions accept an array of request structures. This enables querying multiple properties in the same group at once. It also enables querying properties across multiple
resources in the same group e.g. query the fan speed across all fans connected to a device.

As an example, consider the fan property that gives the speed in RPM:

| Description                | C-API                          |
| :--:                       | :--:                           |
| Property enumerator type   | ::${t}_fan_properties_t        |
| Property enumerator        | ::${T}_FAN_PROP_SPEED_RPM      |
| Property value structure   | ::${t}_fan_prop_speed_rpm_t    |
| Property request structure | ::${t}_fan_property_request_t  |
| Property get function      | ::${t}SysmanGetFanProperties() |
| Property set function      | ::${t}SysmanSetFanProperties() |

Notice how the property value structure is the same as the property enumerator but in low-caps with "_t" appended to the end. All properties follow this convention.

The code below shows how to read the fan speed:

```c
void ShowFanInfo(${t}_sysman_handle_t hSysmanDevice, uint32_t FanIndex)
{
    struct FanData
    {
        ${t}_fan_prop_speed_rpm_t        speedRpm;
        ${t}_fan_prop_speed_percent_t    speedPercent;
    };

    FanData data;
    ${t}_fan_property_request_t requests[] = 
    {
        { FanIndex, ${T}_FAN_PROP_SPEED_RPM,       &data.speedRpm,       sizeof(data.speedRpm) },
        { FanIndex, ${T}_FAN_PROP_SPEED_PERCENT,   &data.speedPercent,   sizeof(data.speedPercent) },
    };

    if (${t}SysmanGetFanProperties(hSysmanDevice, sizeof(requests) / sizeof(requests[0]), requests)
	    == ${X}_RESULT_SUCCESS)
    {
        fprintf(stdout,
                "        Fan %u: %u rpm (%u %%)\n",
                FanIndex, data.speedRpm.speed, data.speedPercent.speed);
    }
}
```

${"##"} <a name="pry">Property accuracy</a>
All readable dynamic properties have a minimum sample-rate that is related to the time interval between updates of the underlying telemetry. If the property returns the
instantaneous value at the time of reading, we say that the sample interval is 0. If the property will have an updated value every 1 millisecond, we say that the
sample interval is 1 millisecond. This means that software should not expect an accuracy of this property if sampled faster than 1 millisecond.

Software can determine the minimum sample interval for each property by using the appropriate availability function. The returned data gives the sample interval.
For example, if calling ::${t}SysmanAvailableFreqProperties() with the property ::${T}_FREQ_PROP_FREQ_REQUEST returns ::${t}_freq_prop_capability_t.minGetInterval = 1000,
this means that software should not expect to see new values for the current frequency for 1 millisecond after the last time it read the value.

Similarly, writable dynamic properties have a minimum update-rate that is related to the time it takes for the hardware to accept the new value. Software can update
the property faster than this rate, but it is unlikely that the new value will take effect immediately. If hardware changes immediately when a new property value is
written, we say that the update interval is 0. If the property will only react to a new value after 1 millisecond, we say that the update interval is 1 millisecond.

Software can determine the minimum update interval for each property by using the appropriate availability function. For example, if calling
::${t}SysmanAvailableFreqProperties() with the property ::${T}_FREQ_PROP_FREQ_REQUEST returns ::${t}_freq_prop_capability_t.minSetInterval = 1000,
this means that software should not expect a new frequency request to take effect until 1 millisecond has elapsed.

${"#"} <a name="ac">Accelerator assets</a>
Some resources apply to more than one part of a device, but not necessarily the entire device. For example, there may be two frequency domains. One controls the performance
of media accelerator assets and one controls the performance of compute accelerator assets. Rather than enumerate all possible combinations for all products, a more generic
solution is achieved by defining all accelerator assets and then for each resource, indicating the list of assets that are measured/affected by the resource. The list is
defined in the enumerator type ::${t}_accel_asset_t. 

A frequency domain resource is a good example of how this list is used. Each frequency domain resource has a property ::${T}_FREQ_PROP_ACCEL_ASSETS. The data structure for
the value of this property is given by ::${t}_freq_prop_accel_assets_t (lower-case everything and add "_t" to the end). It contains the member
::${t}_freq_prop_accel_assets_t.assets that is of type uint64_t. This is a bitfield which will have a bit for each accelerator asset whose performance will be impacted
by this frequency domain resource. All devices of the same class (same device ID) will have the same frequency resources with the same associated accelerator assets since
this is a property of the product hardware and not of specific devices.

It is possible to use ::${t}SysmanGetInfo() to determine the list of all accelerator assets available on the device along with the number
of such assets (::${t}_sysman_info_t.numAssets[]).

The example below shows how to output the list of assets on the device:

```c
void ShowAcceleratorAssets(${t}_sysman_handle_t hSysmanDevice)
{
    ${t}_sysman_info_t info;
    if (${t}SysmanGetInfo(hSysmanDevice, &info) == ${X}_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Assets:\n");
        for (int i = 0; i < ${T}_ACCEL_ASSET_MAX_TYPES; i++)
        {
            if (info.numAssets[i])
            {
                const char* pAssetName;
                ${t}SysmanGetAccelAssetName(hSysmanDevice, (${t}_accel_asset_t)i, &pAssetName);
                fprintf(stdout, "        %s: %u\n", pAssetName, info.numAssets[i]);
            }
        }
        fprintf(stdout, "\n");
    }
}
```

${"#"} <a name="re">Resources</a>
Except for the device property group, the other groups describe properties for one or more resources. For example, there can be multiple fans associated with a device and each
fan has the same property such as speed. Each fan is a resource with a zero-based index. Resources are grouped in the same way as property groups. These are defined in the
enumerator type ::{t}_resource_type_t.

A resource ID is defined as the combination of the resource type (::{t}_resource_type_t) and the index. The structure ::${t}_resource_id_t is used to specify a resource ID.
This uniquely specifies a resource in a device. It is expected that resource IDs are valid across all devices of the same class (same device ID). For example Fan0 will be the
same on all devices from the same product family.

For a given device, it is possible to determine the number of resources of each type using the API function ::${t}SysmanGetInfo(). This populates the structure
::${t}_sysman_info_t. The member ::${t}_sysman_info_t.numResourcesByType[] is an array which will give you the number of resources for each type.

The example below shows how to determine the number of fans associated with a device and then show the speed for each fan using the function ShowFanInfo() shown
in the previous example:

```c
void ShowNumFans(${t}_sysman_handle_t hSysmanDevice)
{
    ${t}_sysman_info_t info;
    if (${t}SysmanGetInfo(hSysmanDevice, &info) == ${X}_RESULT_SUCCESS)
    {
        fprintf(stdout,
                "Num fans: %u\n",
                info.numResourcesByType[${T}_RESOURCE_TYPE_FAN]);

        for (uint32_t i = 0; i < info.numResourcesByType[${T}_RESOURCE_TYPE_FAN]; i++)
        {
            fprintf(stdout, "Fan %u\n", i);
            ShowFanInfo(hSysmanDevice, i);
        }
}
```

${"##"} <a name="reu">PSU resources resources</a>
Property enumerator: ::${t}_psu_properties_t

These resources provide information about power supply units attached to the device.

- Read maximum amp limit
- Monitor voltage status
- Monitor fan failure
- Monitor heatsink temperature
- Monitor current amps


${"##"} <a name="ret">Temperature sensor resources</a>
Property enumerator: ::${t}_temp_properties_t

These resources provides access to temperature sensors on the device:

- Monitor temperature sensor value


${"##"} <a name="ren">Fan resources</a>
Property enumerator: ::${t}_fan_properties_t

These resources provides access to fans on the device:

- Read maximum speed
- Monitor fan speed
- Set fixed fan speed
- Set fan speed table (table of temperature-speed points)

Fan speeds can be given in units of RPM (revolutions per minute) or percentage of maximum RPM.

Software can either request fixed fan speed, including turning the fan off, or depending on hardware capabilities, as a fan speed table. This is a table of temperature/speed
points. When programmed, the hardware will dynamically choose the fan speed based on the maximum temperature measured on the chip. Software should use the function
::${t}SysmanAvailableFanProperties() with the property ::${T}_FAN_PROP_SPEED_TABLE to determine if the hardware supports this mode.


${"##"} <a name="rel">LED resources</a>
Property enumerator: ::${t}_led_properties_t

These resources provide access to LEDs on the device:

- Turn LED on/off
- Change LED color

Not all LEDs support color control. Software should use the function ::${t}SysmanGetLedProperties() with the property ::${T}_LED_PROP_RGB_CAP to determine if the LED
supports programming the R/G/B color values.


${"##"} <a name="rei">Firmware resources</a>
Property enumerator: ::${t}_firmware_properties_t

These resources provide access to firmwares on the device.

- Read firmware name
- Read firmware version
- Verify firmware image
- Flash firmware image

Not all firmwares can be flashed through this API. Software should use the function ::${t}SysmanAvailableFirmwareProperties() with the property ::${T}_FIRMWARE_PROP_FLASH
to determine if write access is permitted.


${"##"} <a name="ref">Frequency domain resources</a>
Property enumerator: ::${t}_freq_properties_t

These resources provide access to device frequencies:

- Get available frequencies
- Monitor frequency
- Monitor frequency throttle stats and reasons
- Set frequency

The performance of accelerator assets is governed in part by the clock frequency that they run at and the maximum power that can be delivered and dissipated as heat. A
device can have one or more frequency domains and each accelerator asset will fall into only one of them.

For example, a PVC device consists of five frequency domains - the base die, the media assets, the compute assets, base-chiplet link and local memory. This means that
::${t}_sysman_info_t.numResourcesByType[::${T}_RESOURCE_TYPE_FREQ] will return 5. It is thus possible to obtain properties each of these 5 frequency domains.

For system management software to effectively control the performance of a device, it needs to know which accelerator assets are in each frequency domain. This is
returned by the property ::{T}_FREQ_PROP_ACCEL_ASSETS. Software can thus read the value of this property for each frequency domain in order to build up an understanding
of which assets are controleld by which frequency. This information is the same for all devices with the same device ID.

The diagram below shows which accelerator asset is controlled by each of the 5 frequency domains on the PVC product:

![Frequency Domains](../images/tools_sysman_freq_domains.png?raw=true) 

There are three types of frequency domains described by the enumerator ::${t}_freq_domain_type_t:

1. PLL - Frequency domain is driven by a phase-locked loop. 
2. Divider - Frequency is linked to another PLL frequency domain by clock divider hardware. The divider ratio can be changed so as to down-clock that part of the circuit.
3. Multiplier - Frequency is a multiplier of another frequency domain. The underlying hardware is a PLL but software is able to request a fixed frequency ratio with another
frequency domain.

${"##"} <a name="rep">Power domain resources</a>
Property enumerator: ::${t}_pwr_properties_t

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

A power domain represents a collection of one or more frequency domains whose total power is being managed and limited by the hardware. If the power limit is reached,
hardware starts capping the associated frequency domains until the total power drops below the limit.

Every frequency domain resource has a property ::${T}_FREQ_PROP_POWER_DOMAIN which gives the resource ID of the power domain of which it is part. In this way, software can
determine the relationship between frequency domains and power domains and accelerator assets. An example of this is illustrated in the diagram below where we see a product
that has only one power domain:

![Power Domains](../images/tools_sysman_pwr_domains.png?raw=true) 

Notice that we are not giving names to the power domains and the frequency domains. The significance of each domain comes from the underlying accelerator assets.

Every PLL frequency domain has a request which is either statically set by external tools or dynamically controlled by a hardware algorithm. Under certain circumstances,
the hardware may need to resolve the request to a lower frequency. This is known as frequency throttling. The reasons for the throttling can be determined using the
property ::${T}_FREQ_PROP_THROTTLE_REASONS. These are given by the enumerator ::${t}_freq_prop_throttle_reasons_t. When a PLL frequency domain is throttled, the
corresponding divider and multiplier frequency domains that depend on that PLL domain will also be throttled and the same throttle reasons as the source PLL domain.

${"##"} <a name="rew">Power-well domain resources</a>
Property enumerator: ::${t}_pwrwell_properties_t

These resources provide access to power-wells:

- Monitor power-gating stats (number of wakes, idle time)
- Set power-gating promotion mode

Power-well domains are parts of a device that can be powered off when there is no activity. While this saves power, it can also come with a performance cost given the
latency exiting from a power-gated (sleep) state. Generally the hardware effectively manages this trade-off, however properties of power-well domain resources enable
software to influence how easy it is for the hardware to promote the hardware to sleep states when idle.

As with frequency and power domains, power-well domains come with a list of enclosed accelerator assets. An asset can be found in only one power-well domain. When the
power-well domain enters a sleep state, all accelerator assets in that domain are no longer connected to power.

${"##"} <a name="rea">Accelerator asset resources</a>
Property enumerator: ::${t}_accel_properties_t

These resources provide access to activity statistics for a device:

- Monitor utilization

An accelerator asset resource enables monitoring the activity of one or more accelerator assets. Activity is defined as the wall time that assets are executing
workloads.

Software can query the accelerator assets that are included in the activity counters. The same accelerator asset resources will be available for all devices with
the device ID. In general, the accelerator asset resource with index 0 will provide the global activity of the entire devices. However this should not be assumed
and software should always enumerate through all these resources and choose the ones that cover the relevant accelerator assets.

The code example below shows how software can determine the indices, if any, of resources that measure only the activity of media accelerators:

```c
void MediaUtilizationResources(${t}_sysman_handle_t hSysmanDevice)
{
    ${t}_sysman_info_t info;
    if (${t}SysmanGetInfo(hSysmanDevice, &info) == ${X}_RESULT_SUCCESS)
    {
        const uint64_t mediaAssetBitfield =
		    (${T}_ACCEL_ASSET_VIDEO_DECODER | ${T}_ACCEL_ASSET_VIDEO_ENCODER | ${T}_ACCEL_ASSET_VIDEO_PROCESSING);
        struct
        {
            ${t}_accel_prop_accel_assets_t assets;
        } data;
        ${t}_accel_property_request_t request{ 0, ${T}_ACCEL_PROP_ACCEL_ASSETS, &data.assets, sizeof(data.assets) };

        fprintf(stdout, "Accelerator asset resources counting only media utilization:\n");
        for (uint32_t i = 0; i < info.numResourcesByType[${T}_RESOURCE_TYPE_ACCEL]; i++)
        {
            request.index = i;
            if (${t}SysmanGetAccelProperties(hSysmanDevice, 1, &request) == XE_RESULT_SUCCESS)
            {
                if ((data.assets.assets & mediaAssetBitfield) == mediaAssetBitfield)
                {
                    fprintf(stdout, "    index=%u: assets=0x%llx\n", i, data.assets.assets);
                }
            }
        }
    }
}
```

${"##"} <a name="rem">Memory resources</a>
Property enumerator: ::${t}_mem_properties_t

Memory resources provide access to memory statistics:

- Monitor memory bandwidth
- Monitor memory utilization

In general, the memory resource with index 0 refers to the local main memory of the device.


${"##"} <a name="rek">Link resources</a>
Property enumerator: ::${t}_link_properties_t

Link resources provide access to link statistics:

- Read available link speeds
- Monitor link bandwidth
- Set link speed range

Software can determine if it is possible to change the link speed (number of lanes, frequency) by calling the function ::${t}SysmanAvailableLinkProperties()
and passing in the property ::${T}_LINK_PROP_SPEED_RANGE. If the resulting value of ::${t}_link_prop_capability_t.access indicates write access, then it is
possible to change the speed of the link.

In general, the link resource with index 0 refers to the PCIe connection to the device. Other resources will relate to peer-to-peer high-speed links.


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
will be returned and the required size if provided. The function ::${t}SysmanGetInfo() can be used to find the total number of errors counters that are available
and hence the total array size that should be passed into the ::${t}SysmanGetRasErrors() function.

Note that for each error, the interpretation of the data depends on the provided error type in ::${t}_ras_error_t.dataType. Some errors may be counters
(::${T}_RAS_DATA_TYPE_COUNTER) while other errors may only indicate that errors have occurred (::${T}_RAS_DATA_TYPE_OCCURRED).

When calling ::${t}SysmanGetRasErrors(), it is possible to request that the error data (counter or occurrence) be cleared. This means that if the filter threshold is set
to 1 or more, the next call to ::${t}SysmanGetRasErrors() will only show new errors that have occurred since the last call. The counters are cleared per
application. This means that if there are multiple threads calling this function and requesting clearing of the counters, only one thread will see the new errors.

The code below shows how to get a list of all available error counters. This is something that an application could do during initialization:

```c
void ShowRasCounters(${t}_sysman_handle_t hSysmanDevice)
{
    xet_sysman_info_t info;
    if ((${t}SysmanGetInfo(hSysmanDevice, &info) == ${X}_RESULT_SUCCESS) && (info.numRas))
    {
        ${t}_ras_filter_t filter = ${T}_RAS_FILTER_ALL_COUNTERS;
        ${t}_ras_error_t* pCounters = (${t}_ras_error_t*)malloc(info.numRas * sizeof(${t}_ras_error_t));

        if (${t}SysmanGetRasErrors(hSysmanDevice, &filter, false, &info.numRas, pCounters)
            == ${X}_RESULT_SUCCESS)
        {
            for (int i = 0; i < info.numRas; i++)
            {
                fprintf(stdout,
                        "RAS error %d: type=0x%x loc=0x%x resource=%d,%u value=%llu\n",
                        i, pCounters[i].type, pCounters[i].loc,
                        pCounters[i].resourceId.type, pCounters[i].resourceId.index,
                        pCounters[i].data);
            }
        }
    }
}
```

The function ::${t}SysmanGetInfo(), in addition to returning the total number of RAS error counters available on a device class, also returns a list of all types and
structural locations. This is not a list of all counters but a merging of all type and location bitfields into ::${t}_sysman_info_t.rasTypes and
::${t}_sysman_info_t.rasLocations. This permits an application to quickly determine if the API is likely to provide specific types of counters.

If ::${t}_sysman_info_t.rasLocations is not zero, it indicates the structural locations where RAS is supported. The function ::${t}SysmanRasSetup() can be used to
enable/disable RAS at any of those structural locations. On return, the function indicates the structual locations where RAS is enabled. The code below
shows how to determine if RAS is enabled for the local memory:

```c
void LocalMemoryRasConfig(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_info_t info;
    if (xetSysmanGetInfo(hSysmanDevice, &info) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "Local memory:\n");
        if (info.rasLocations & XET_RAS_ERROR_LOC_MAIN_MEM)
        {
            uint32_t enabled;
            fprintf(stdout, "    RAS support: yes\n");
            if (xetSysmanRasSetup(hSysmanDevice, 0, 0, &enabled) == XE_RESULT_SUCCESS)
            {
                fprintf(stdout, "    RAS enabled: %s\n", (enabled & XET_RAS_ERROR_LOC_MAIN_MEM) ? "yes" : "no");
            }
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

${"#"} <a name="iv">Inventory</a>
Device properties ::${t}_device_properties_t can be used to obtain inventory information:

- Serial number
- Board number
- Device ID
- Vendor ID
- Driver version
- PCI bars


${"#"} <a name="rt">Reset</a>
A device can be reset (PCI device reset) can be achieved using the function ::${t}SysmanSetDeviceProperties() with the property ::${T}_DEVICE_PROP_RESET.


${"#"} <a name="pd">Product reference</a>


${"##"} <a name="pdp">PVC</a>
The following sections give specific details of the PVC device.


${"###"} <a name="pdpu">PVC - PSU resources</a>
Not supported - no read/write access to any properties.


${"###"} <a name="pdpt">PVC - Temperature sensor resources</a>
One temperature sensor resource is available.


${"###"} <a name="pdpn">PVC - Fan resources</a>
Not supported - no read/write access to any properties.


${"###"} <a name="pdpl">PVC - LED resources</a>
Not supported - no read/write access to any properties.


${"###"} <a name="pdpi">PVC - Firmware resources</a>
Multiple firmwares will be enumerated.


${"###"} <a name="pdpf">PVC - Frequency domain resources</a>
Not supported - no read/write access to any properties.

The diagram below shows the 5 frequency domains that will be enumerated by this API, including the resource indices:

![PVC frequency domains](../images/tools_sysman_pvc_freq_domains.png?raw=true) 

By default, the hardware will dynamically set the frequency of all domains to achieve best performance as workloads run and optimized for efficiency when the
device is power/temperature limited. In some cases, external software may want to take control of the frequencies and the comments that follow intend to
give an overview of the restrictions that should be considered when doing this.

The base die contains many common assets including memory controller and L3 cache. The frequency is controlled by a PLL. To ensure that memory and cache access
is not a bottleneck when compute workloads are running, it is recommended that the frequency of the base die be set to 1.2x the frequency of the chiplet die.

The frequency of media assets (encode/decode) is directly related to the frequency of the base die by a divider. There are two divider values:

- 1:1 - This means that the media assets will run at the same frequency as the base die.
- 1:2 - This means that the media assets will run at half the frequency of the base die.

The API will reveal that the base die has a maximum frequency of 2GHz whereas the media frequency domain has a maximum frequency of 1.4GHz (these are examples
and may differ based on the part - use ::${t}SysmanGetFreqProperties() with property ::${T}_FREQ_PROP_AVAIL_CLOCKS to find the exact values). Since the media
frequency domain is dependent on the base die frequency domain, this means that when media assets are in use, the base domain frequency will be limited to the
maximum frequency of the media frequency domain. For example, if the current frequency request for the base domain is 2GHz and the media frequency domain
divider is 1:1, then the media frequency domain will need to run at 2GHz. However, since it is limited to run at 1.4GHz, the hardware will limit the base
frequency domain to 1.4GHz. Since the base die contains the PCIe controller and the L3 cache, this can affect performance if the media workloads are bandwidth
limited at that frequency. The solution is to change the media frequency domain divider to 1:2. In this case, the resulting frequency of the media frequency domain
will be 2GHz / 2 = 1GHz. This is less than the maximum frequency of the media frequency domain and so the frequency of the base die will not be throttled. However,
setting the divider to 1:2 has resulted in a lower maximum frequency for the media frequency domain. The tradeoff between using divider 1:1 and having a lower base
frequency or using divider 1:2 and having a lower media frequency is workload specific. It also depends on whether compute assets are running concurrently - if
it is more important to give performance to them, it is preferable to run with 1:2 ratio so that the base can run at a higher frequency.

By default, the hardware will attempt to dynamically choose the media frequency domain divider value to optimize most scenarios. However, there are workloads
that will benefit from statically fixing the media frequency domain divider using the property ::${T}_FREQ_PROP_FREQ_DIVIDER.

Memory traffic between the chiplet die (compute and systolic resources) and the base die (PCIe, L3 cache, HBM) goes across the link frequency domain. The frequency
of the link domain is critical to providing adequate bandwidth to sustain workload performance. By default, the hardware will set the frequency of the link domain to
1.5x the frequency request of the chiplet frequency domain. In some cases, this might be excessive or might not be enough and the API can be used to change the
frequency to a more suitable value using the property ::${T}_FREQ_PROP_FREQ_MULTIPLIER.

The chiplet contains a systolic array. When the compute units execute instructions requiring this array, the maximum frequency of the chiplet is reduced. There
is no way to control this behavior but it should be kept in mind.

The HBM memory frequency cannot be controlled by software. As such, software will not have write permissions to the property ::${T}_FREQ_PROP_FREQ_REQUEST for
this domain.

${"###"} <a name="pdpp">PVC - Power domain resources</a>
Not supported - no read/write access to any properties.

PVC has only one power domain. The Punit measures the entire consumption of device and when it exceeds the various limits (peak/burst/sustained) the independent
frequency domains are limited.


${"###"} <a name="pdpw">PVC - Power-well domain resources</a>
Not supported - no read/write access to any properties.

PVC has three power-wells, as shown in the diagram below. The base power-well is always on when the PCIe device is in a power-on state.

![PVC power-well domains](../images/tools_sysman_pvc_pwrwell_domains.png?raw=true)


${"###"} <a name="pdpa">PVC - Accelerator asset resources</a>
The following activity resources will be available:

- Index 0: Total activity of media and compute assets combined.
- Index 1: Activity of the compute assets.
- Index 2: Activity of all media assets combined.
- Index 3-8: Activity of each video decoder.


${"###"} <a name="pdpm">PVC - Memory resources</a>
One memory resource will be exposed for the device HBM memory.


${"###"} <a name="pdpk">PVC - Link resources</a>
Link with index 0 will be the PCIe link.

Links with index 1+ will be the peer-to-peer connections, one for each peer device that is accessible through the link.


${"###"} <a name="pdps">PVC - Reliability, availability and serviceability (RAS)</a>
The following RAS counters are available:

| Error type | Structural location | Comments |
| :--:       | :--:                | :--:     |
| TBD        | TBD                 | TBD      |

