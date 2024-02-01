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

.. _ZES_experimental_sysman_device_mapping:

=====================================
 Sysman Device mapping Extension
=====================================

API
----

* Functions

    * ${s}DriverGetDeviceByUuidExp
    * ${s}DeviceGetSubDevicePropertiesExp

* Enumerations

    * ${s}_sysman_device_mapping_exp_version_t

* Structures

    * ${s}_subdevice_exp_properties_t


Sysman Device Mapping
~~~~~~~~~~~~~~~~~~~~~

Three types of device hierarchy models FLAT, COMPOSITE and COMBINED are exposed by Level Zero driver implementation.
Core could use any model it needs for better performance, while SYSMAN keeps a uniform view of the system.

This extension is defined with intent to provide an interface to the user for mapping core device 
handle to sysman device or vice versa using UUID. 


The following pseudo-code demonstrates a sequence for querying the sub device properties
and also how to query sysman device handle from the UUID.

.. parsed-literal::

    // Query Sysman device handle corresponding to given UUID
    uint32_t subDeviceId = 0;
    bool onSubDevice = false;
    ${s}_uuid_t coreDeviceUuid;
    ${s}_device_handle_t* phDevice = (${s}_device_handle_t*)allocate(sizeof(${s}_device_handle_t));
    ${s}DriverGetDeviceByUuidExp(pSysmanDriverHandle, coreDeviceUuid, phDevice, &subDeviceId, &onSubDevice);

    // Query for number of sub devices of the sysman device
    uint32_t subDeviceCount = 0;
    ${s}DeviceGetSubDevicePropertiesExp(pSysmanDeviceHandle, &subDeviceCount, nullptr);

    ${s}_subdevice_exp_properties_t* subDeviceProperties = (${s}_subdevice_exp_properties_t*) allocate(subDeviceCount * sizeof(${s}_subdevice_exp_properties_t));

    //Query sub device properties
    ${s}DeviceGetSubDevicePropertiesExp(pSysmanDeviceHandle, &subDeviceCount, subDeviceProperties);

    // Print sub device property details
    for(uint32_t i = 0; i < subDeviceCount; i++) {
        output(" Sub Device Id : %lu \\n", subDeviceProperties[i]->subdeviceId);
        output("UUID : \\n");
        for (uint32_t j = 0; j < ZE_MAX_UUID_SIZE; j++) {
             output("%x  ",subDeviceProperties[i]->uuid.id[j]);
        }
        output("\\n");
    }

