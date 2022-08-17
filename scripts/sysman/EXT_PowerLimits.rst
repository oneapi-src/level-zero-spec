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

.. _ZES_extension_power_limits:

========================
 Power Limits Extension
========================

API
----

* Functions

    * ${s}PowerGetLimitsExt
    * ${s}PowerSetLimitsExt

* Structures

    * ${s}_power_limit_ext_desc_t
    * ${s}_power_ext_properties_t

Power Limits
~~~~~~~~~~~~~~~~~~

This extension replaces the functionality provided by the ${s}PowerGetLimits & ${s}PowerSetLimits calls in the Sysman API. The correct usage of the new API
is shown in the Sysman Programming Guide.
