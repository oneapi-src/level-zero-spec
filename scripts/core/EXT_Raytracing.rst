<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_raytracing:

=========================
 Raytracing Extension
=========================

API
----

* Enumerations


    * ${x}_raytracing_ext_version_t
    * ${x}_device_raytracing_ext_flags_t
    * ${x}_raytracing_mem_alloc_ext_flags_t

 
* Structures


    * ${x}_device_raytracing_ext_properties_t
    * ${x}_raytracing_mem_alloc_ext_desc_t

