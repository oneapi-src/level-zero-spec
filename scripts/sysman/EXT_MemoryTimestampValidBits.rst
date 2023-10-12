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

.. _ZES_extension_mem_timestamp_valid_bits:

========================================
 Memory Timestamp Valid Bits Extension
========================================

API
----

* Enumerations

    * ${s}_mem_timestamp_bits_exp_version_t

* Structures

    * ${s}_mem_timestamp_bits_exp_t
