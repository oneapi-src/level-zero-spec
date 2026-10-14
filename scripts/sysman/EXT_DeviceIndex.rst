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

.. _ZES_extension_device_index:

=============================
 Device Index Extension
=============================

API
----
* Enumerations

    * ${s}_device_index_ext_version_t

* Structures

    * ${s}_device_index_ext_properties_t

* Macros

    * ${S}_DEVICE_INDEX_EXT_NAME

Device Index Overview
~~~~~~~~~~~~~~~~~~~~~

The Device Index extension provides the ability to query the device index (GPU ID),
an integer identifier for a Sysman device handle.

Applications can retrieve the device index by passing the extension structure via
the pNext chain when querying device properties.

The device index is set at ${s}Init(), subsequent calls may add new devices but will
not change existing indexes. To identify a device across processes or reboots, it is
recommended that devices be looked up by their PCI IDs or UUID.

The following pseudo-code demonstrates the usage pattern for querying the device index.

**Querying Device Index**

.. parsed-literal::

    // Query device properties with device index extension
    ${s}_device_properties_t deviceProps = {};
    deviceProps.stype = ${S}_STRUCTURE_TYPE_DEVICE_PROPERTIES;

    ${s}_device_index_ext_properties_t deviceIndexProps = {};
    deviceIndexProps.stype = ${S}_STRUCTURE_TYPE_DEVICE_INDEX_EXT_PROPERTIES;
    deviceIndexProps.pNext = nullptr;

    deviceProps.pNext = &deviceIndexProps;

    if (${s}DeviceGetProperties(hDevice, &deviceProps) == ${X}_RESULT_SUCCESS) {
        output("Device Index: %u\\n", deviceIndexProps.deviceIndex);
    }
