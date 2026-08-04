<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_init_driver_app_version:

============================================
 Init Driver Application Version Extension
============================================

API
----
* Enumerations


    * ${x}_init_driver_app_version_ext_version_t


* Structures


    * ${x}_init_driver_app_version_ext_desc_t

Declaring the Application-Supported API Version
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This extension lets an application pass the driver a hint describing the maximum core ${OneApi} Level-Zero API version it was built against and is able to handle. The application supplies the hint in a ${x}_init_driver_app_version_ext_desc_t struct, chained from the ``pNext`` member of ${x}_init_driver_type_desc_t when calling ${x}InitDrivers.

The hint is advisory: a driver is free to ignore it. ${x}DriverGetApiVersion continues to report the version supported by the *driver*, independently of any version the application declares.

The following rules apply:

* The ``apiVersionHint`` field declares the maximum core ${OneApi} Level-Zero API version the application was built against and is able to handle.
* A driver may use the hint to gate version-dependent behavior for backward compatibility, for example only reporting enumerants or memory types introduced in newer API versions to applications that understand them.
* If this structure is not provided, the driver must assume the application supports only the baseline behavior and must not rely on any version-gated behavior being understood by the application.
* A driver that acts on the hint should clamp version-gated behavior to the minimum of the version it supports and the version the application declares.
