<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    s=tags['$s']
    S=s.upper()
%>
:orphan:

.. _ZES_extension_device_soc_uid:

===================================
 Device SOC Unique ID Extension
===================================

API
----
* Enumerations

    * ${s}_device_soc_uid_ext_version_t

* Structures

    * ${s}_device_soc_uid_ext_properties_t

* Macros

    * ${S}_DEVICE_SOC_UID_EXT_NAME

Device SOC Unique ID Overview
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Device SOC Unique ID extension provides the ability to query the unique ID
of the SOC on which the device resides.

Applications can retrieve this property by passing the extension structure via
the pNext chain when calling ${s}DeviceGetProperties. If the SOC unique ID
cannot be determined for the device, it will be set to all zeroes.

Querying the SOC Unique ID
~~~~~~~~~~~~~~~~~~~~~~~~~~

The following pseudo-code demonstrates the usage pattern for querying the SOC
unique ID of the device.

.. parsed-literal::

    // Query device properties with the device SOC unique ID extension
    ${s}_device_properties_t deviceProps = {};
    deviceProps.stype = ${S}_STRUCTURE_TYPE_DEVICE_PROPERTIES;

    ${s}_device_soc_uid_ext_properties_t socUidProps = {};
    socUidProps.stype = ${S}_STRUCTURE_TYPE_DEVICE_SOC_UID_EXT_PROPERTIES;
    socUidProps.pNext = nullptr;

    deviceProps.pNext = &socUidProps;

    ${s}DeviceGetProperties(hDevice, &deviceProps);

    output("SOC unique ID: ");
    for (uint32_t i = 0; i < ${S}_MAX_UUID_SIZE; i++) {
        output("%02x", socUidProps.socUid.id[i]);
    }
    output("\\n");
