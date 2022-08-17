<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_device_memory_properties:

======================================
 Device Memory Properties Extension
======================================

API
----

* Enumerations


    * ${x}_device_memory_properties_ext_version_t
    * ${x}_device_memory_ext_type_t


* Structures


    * ${x}_device_memory_ext_properties_t

Extended Device Memory Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Users may wish to build a cost model for computation on accelerators exposed through ${OneApi} Level-Zero. Such cost models require detailed information about the properties of the accelerator such as memory bandwidth. This extension provides extended information about the memories exposed as part of a device. The extension introduces the ${x}_device_memory_ext_properties_t struct which can be passed to ${x}DeviceGetMemoryProperties via the `pNext` member of ${x}_device_memory_properties_t.

The following psuedo-code demonstrates a sequence for obtaining extended information about the memory properties of a memory module exposed as part of a device:

.. parsed-literal::

       ...
       // Discover memories on device
       uint32_t memCount = 0;
       ${x}DeviceGetMemoryProperties(hDevice, &memCount, nullptr);

       // Allocate properties structs
       ${x}_device_memory_properties_t* pMemProps = allocate(memCount*sizeof(${x}_device_memory_properties_t));
       ${x}_device_memory_ext_properties_t* pExtMemProps = allocate(memCount*sizeof(${x}_device_memory_ext_properties_t));

       // Make pNext in memProps point at corresponding extMemProps
       for (uint32_t i = 0; i < memCount; ++i) {
         pMemProps[i].stype = ${X}_STRUCTURE_TYPE_DEVICE_MEMORY_PROPERTIES;
         pMemProps[i].pNext = &pExtMemProps[i];
         pExtMemProps[i].stype = ${X}_STRUCTURE_TYPE_DEVICE_MEMORY_EXT_PROPERTIES;
         pExtMemProps[i].pNext = nullptr;
       }

       // Obtain memory & extended memory properties
       ${x}DeviceGetMemoryProperties(hDevice, &memCount, pMemProps);
