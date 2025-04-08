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

.. _ZES_extension_device_ecc_default_properties:

=====================================
 Device-ECC default properties Extension
=====================================

API
----

* Structures

    * ${s}_device_ecc_default_properties_ext_t

 Device-ECC properties
~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, {s}DeviceGetEccState returns the current state of the ECC counters. 

Additionally to get default ECC state, pass ${s}_device_ecc_default_properties_ext_t to {s}DeviceGetEccState
as pNext member of ${s}_device_ecc_properties_t.

.. parsed-literal::

    ${s}_device_ecc_properties_t getState = {${s}_STRUCTURE_TYPE_DEVICE_ECC_PROPERTIES};
    ${s}_device_ecc_default_properties_ext_t ext = {${s}_STRUCTURE_TYPE_DEVICE_ECC_DEFAULT_PROPERTIES_EXT};
    getState.pNext = &ext;
    ${x}_result_t = ${s}DeviceGetEccState(device, &getState);
