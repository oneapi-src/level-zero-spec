<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_float_atomics:

=========================
 Float Atomics Extension
=========================

API
----

* Enumerations


    * ${x}_float_atomics_ext_version_t
    * ${x}_device_fp_atomic_ext_flags_t

 
* Structures


    * ${x}_float_atomic_ext_properties_t
