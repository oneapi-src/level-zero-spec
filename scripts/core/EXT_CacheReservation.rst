<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_cache_reservation:

=============================
 Cache Reservation Extension
=============================

API
----

* Functions

    * ${x}DeviceReserveCacheExt
    * ${x}DeviceSetCacheAdviceExt

* Enumerations

    * ${x}_cache_reservation_ext_version_t
    * ${x}_cache_ext_region_t
 
* Structures

    * ${x}_cache_reservation_ext_desc_t
