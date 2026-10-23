<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>

<%!
    from parse_specs import _version_compare_gequal
%>

:orphan:

.. _ZE_experimental_relaxed_allocation_limits:

=====================================
 Relaxed Allocation Limits Extension
=====================================

API
----

* Enumerations


    * ${x}_relaxed_allocation_limits_exp_version_t
    * ${x}_relaxed_allocation_limits_exp_flags_t

 
* Structures


    * ${x}_relaxed_allocation_limits_exp_desc_t
