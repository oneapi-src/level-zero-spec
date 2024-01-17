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

.. _ZES_extension_sysman_device_mapping:

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

    * ${s}_subdevice_properties_exp_t


Sysman Device Mapping
~~~~~~~~~~~~~~~~~~~~~

Three types of device hierarchy models FLAT, COMPOSITE and COMBINED are exposed by Level Zero driver implementation.
Core could use any model it needs for better performance, while SYSMAN keeps a uniform view of the system.

This extension is defined with intent to provide an interface to the user for mapping core device 
handle to sysman device or vice versa using UUID. 
    
