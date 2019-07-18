# Programming Guide (Sysman)

[DO NOT EDIT]: # (generated from /scripts/tools/SYSMAN.md)

The following documents the high-level programming models and guidelines.

NOTE: This is a **PRELIMINARY** specification, provided for review and feedback.

## Table of Contents
* [Introduction](#in)
* [Sysman handle](#hd)
* [Properties](#pr)
    + [Property groups and lists](#prg)
    + [Property availability](#pra)
    + [Property value access](#prw)
* [Resources](#pr)
* [Accelerator assets](#pr)
* [Reliability and Stability](#pr)
* [Events](#pr)

# <a name="in">Introduction</a>
Sysman is the System Resource Management Interface (SMI) used to monitor and control accelerator power and performance..

The diagram below shows 
![Introduction](../images/tools_sysman_object_hierarchy.png?raw=true) 

# <a name="pr">Properties</a>
Most telemetry and configuration controls are accessed through **properties**.

## <a name="prg">Property groups and lists</a>
Properties are broken into groups. For each group, there is an enumerator for all properties (property list)

| Property group         | C API key | Property list |Description                                                                                                      |
| :--:                   | :--:      | :--:                         | :--:                                                                                             |
| **Device**             | device    | ::xet_device_properties_t   | Properties provide device and driver inventory information and the ability to reset.             |
| **PSU**                | psu       | ::xet_psu_properties_t      | Properties provide status information about power supplies.                                      |
| **Temperature sensor** | temp      | ::xet_temp_properties_t     | Properties permit monitoring temperature sensors.                                                |
| **Fan**                | fan       | ::xet_fan_properties_t      | Properties permit monitoring and controlling fans.                                               |
| **LED**                | led       | ::xet_led_properties_t      | Properties permit changing the behavior of LEDs.                                                 |
| **Firmware**           | firmware  | ::xet_firmware_properties_t | Properties provide firmware version and uploading new images.                                    |
| **Power domain**       | pwr       | ::xet_pwr_properties_t      | Properties permit monitoring of power consumption and setting operating power limits.            |
| **Frequency domain**   | freq      | ::xet_freq_properties_t     | Properties permit monitoring of frequency and setting frequency limits.                          |
| **Power-well domain**  | pwrwell   | ::xet_pwrwell_properties_t  | Properties permit monitoring the sleep states of the chip and changing the sleep state behavior. |
| **Accelerator asset**  | accel     | ::xet_accel_properties_t    | Properties permit monitoring of activity of accelerator assets.                                  |
| **Memory**             | mem       | ::xet_mem_properties_t      | Properties permit monitoring of memory utilization and errors.                                   |
| **Link**               | link      | ::xet_link_properties_t     | Properties permit monitoring utilization and errors of peer-to-peer links.                       |

For each group, there are separate API functions that determine access capabilities for a property and to read/write property values.
Separation of the API in this way groups common functionality together.

## <a name="pra">Property availability</a>
Determining if properties are supported and accessible is achieved by calling the API function xetSysmanAvailableXxxProperties(), where **xxx** is replaced with the
C API key from the table above for the appropriate group (**Xxx** means that the first character in the key is capitalized, **XXX** means that all characters in the key are capitalized).

Each function xetSysmanAvailableXxxProperties() receives an array or requests. Each request specifies a property. On return from the function, each request will indicate the API support
(one of ::xet_prop_support_t) and the access permissions (::xet_prop_access_t). API support indicates if the property is supported by the current version of the API, the device class
and the device. It is possible that the API supports a property but not for a particular device class or device. Access permissions are specific to a device and so should be checked for
every device.

The table below gives the function and request structure needed to determine the availability for any property in each group:

| Property group         | Function                                 | Request structure                 | Properties                   |
| :--:                   | :--:                                     | :--:                              |  :--:                        |
| **Device**             | ::xetSysmanAvailableDeviceProperties    | ::xet_device_prop_capability_t   | ::xet_device_properties_t   |
| **PSU**                | ::xetSysmanAvailablePsuProperties       | ::xet_psu_prop_capability_t      | ::xet_psu_properties_t      |
| **Temperature sensor** | ::xetSysmanAvailableTempProperties      | ::xet_temp_prop_capability_t     | ::xet_temp_properties_t     |
| **Fan**                | ::xetSysmanAvailableFanProperties       | ::xet_fan_prop_capability_t      | ::xet_fan_properties_t      |
| **LED**                | ::xetSysmanAvailableLedProperties       | ::xet_led_prop_capability_t      | ::xet_led_properties_t      |
| **Firmware**           | ::xetSysmanAvailableFirmwareProperties  | ::xet_firmware_prop_capability_t | ::xet_firmware_properties_t |
| **Power domain**       | ::xetSysmanAvailablePwrProperties       | ::xet_pwr_prop_capability_t      | ::xet_pwr_properties_t      |
| **Frequency domain**   | ::xetSysmanAvailableFreqProperties      | ::xet_freq_prop_capability_t     | ::xet_freq_properties_t     |
| **Power-well domain**  | ::xetSysmanAvailablePwrwellProperties   | ::xet_pwrwell_prop_capability_t  | ::xet_pwrwell_properties_t  |
| **Accelerator asset**  | ::xetSysmanAvailableAccelProperties     | ::xet_accel_prop_capability_t    | ::xet_accel_properties_t    |
| **Memory**             | ::xetSysmanAvailableMemProperties       | ::xet_mem_prop_capability_t      | ::xet_mem_properties_t      |
| **Link**               | ::xetSysmanAvailableLinkProperties      | ::xet_link_prop_capability_t     | ::xet_link_properties_t     |

The example below shows how an application can determine if it can set a fixed fan speed on a specific device:

```c
bool HaveFanControl(xet_sysman_handle_t hSysmanDevice)
{
    bool ret = false;
    xet_fan_prop_capability_t cap;
    cap.property = XET_FAN_PROP_FIXED_SPEED;
    if (xetSysmanAvailableFanProperties(hSysmanDevice, 1, &cap) == XE_RESULT_SUCCESS)
    {
        if ((cap.support & XET_PROP_SUPPORT_DEVICE) &&
            (cap.access & XET_PROP_ACCESS_WRITE_PERMISSIONS))
        {
            ret = true;
        }
    }
    return ret;
}
```

## <a name="prw">Property access</a>