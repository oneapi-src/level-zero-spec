<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_memory_free_policies:

=================================
 Memory Free Policies Extension
=================================

API
----

* Functions

    * ${x}MemFreeExt

* Enumerations

    * ${x}_memory_free_policies_ext_version_t
    * ${x}_driver_memory_free_policy_ext_flags_t

* Structures

    * ${x}_driver_memory_free_ext_properties_t
    * ${x}_memory_free_ext_desc_t

