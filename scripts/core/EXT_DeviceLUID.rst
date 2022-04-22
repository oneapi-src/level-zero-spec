<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_device_luid:

==========================================
 Device Local Identifier (LUID) Extension
==========================================

API
----

* Enumerations


    * ${x}_device_luid_ext_version_t


* Structures

    * ${x}_device_luid_ext_t
    * ${x}_device_luid_ext_properties_t
