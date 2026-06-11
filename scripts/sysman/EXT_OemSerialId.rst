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

.. _ZES_extension_oem_serial_id:

=============================
 OEM Serial ID Extension
=============================

API
----
* Enumerations

    * ${s}_oem_serial_id_ext_version_t
   
* Structures

    * ${s}_oem_serial_id_ext_properties_t

* Macros

    * ${S}_OEM_SERIAL_ID_SIZE

OEM Serial ID Overview
~~~~~~~~~~~~~~~~~~~~~~

The OEM Serial ID extension provides the ability to query the OEM-assigned serial ID
of the device. This serial ID is typically programmed during device manufacturing and
uniquely identifies the specific device hardware.

Applications can retrieve the OEM serial ID by passing the extension structure via the 
pNext chain when querying device properties. If the serial ID cannot be determined,
the string will not be populated and the length will be 0.

The following pseudo-code demonstrates the usage pattern for querying the OEM serial ID.

**Querying OEM Serial ID**

.. parsed-literal::

    // Query device properties with OEM serial ID extension
    ${s}_device_properties_t deviceProps = {};
    deviceProps.stype = ${S}_STRUCTURE_TYPE_DEVICE_PROPERTIES;
    
    ${s}_oem_serial_id_ext_properties_t serialIdProps = {};
    serialIdProps.stype = ${S}_STRUCTURE_TYPE_OEM_SERIAL_ID_EXT_PROPERTIES;
    serialIdProps.pNext = nullptr;
    
    deviceProps.pNext = &serialIdProps;
    
    ${s}DeviceGetProperties(hDevice, &deviceProps);
    
    // Check if serial ID was successfully retrieved
    if (serialIdProps.length != 0) {
        output("OEM Serial ID: %s\\n", serialIdProps.oemSerialId);
        output("Serial ID Length: %u\\n", serialIdProps.length);
    } else {
        output("OEM serial ID not available for this device\\n");
    }