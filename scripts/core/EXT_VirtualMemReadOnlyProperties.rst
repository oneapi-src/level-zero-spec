<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_virtual_mem_readonly_properties:

================================================
 Virtual Memory Read-Only Properties Extension
================================================

API
----

* Enumerations

    * ${x}_virtual_mem_readonly_properties_ext_version_t
    * ${x}_device_readonly_memory_capability_t

* Structures

    * ${x}_device_readonly_memory_ext_properties_t

Virtual Memory Read-Only Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

${OneApi} Level-Zero provides the ${X}_MEMORY_ACCESS_ATTRIBUTE_READONLY attribute
for virtual memory page mappings via ${x}VirtualMemSetAccessAttribute. However,
the actual behavior when this attribute is applied varies across drivers and hardware.

This extension introduces the ${x}_device_readonly_memory_ext_properties_t struct,
which can be chained via the ``pNext`` member of ${x}_device_properties_t to query
the read-only capability supported by the device.

The ``readonlyCapability`` field reports one of the following values:

- ``${X}_DEVICE_READONLY_MEMORY_CAPABILITY_NONE``: The read-only attribute has no effect.
- ``${X}_DEVICE_READONLY_MEMORY_CAPABILITY_HINT``: The read-only attribute is forwarded to the OS as a performance hint.
- ``${X}_DEVICE_READONLY_MEMORY_CAPABILITY_ENFORCED``: The read-only attribute is hardware-enforced.

The following pseudo-code demonstrates how to query the read-only memory capability:

.. parsed-literal::

       // Query device properties with read-only memory capability extension
       ${x}_device_readonly_memory_ext_properties_t roProps = {};
       roProps.stype = ${X}_STRUCTURE_TYPE_DEVICE_READONLY_MEMORY_EXT_PROPERTIES;
       roProps.pNext = nullptr;

       ${x}_device_properties_t devProps = {};
       devProps.stype = ${X}_STRUCTURE_TYPE_DEVICE_PROPERTIES_1_2; // ${X}_STRUCTURE_TYPE_DEVICE_PROPERTIES deprecated since 1.17
       devProps.pNext = &roProps;

       ${x}DeviceGetProperties(hDevice, &devProps);

       if (roProps.readonlyCapability == ${X}_DEVICE_READONLY_MEMORY_CAPABILITY_ENFORCED) {
           // Hardware enforces read-only; writes will fault
       } else if (roProps.readonlyCapability == ${X}_DEVICE_READONLY_MEMORY_CAPABILITY_HINT) {
           // Read-only is a hint; writes may still succeed
       } else {
           // No read-only support; attribute has no effect
       }
