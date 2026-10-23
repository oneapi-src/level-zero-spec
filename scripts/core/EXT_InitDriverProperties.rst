<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_init_driver_properties:

===================================
 Init Driver Properties Extension
===================================

API
----
* Enumerations


    * ${x}_init_driver_properties_ext_version_t
    * ${x}_init_driver_properties_ext_flags_t


* Structures


    * ${x}_init_driver_properties_ext_desc_t

Declaring Driver-Wide Properties at Initialization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This extension lets an application declare driver-wide properties for the driver(s) being initialized. The application supplies the properties in a ${x}_init_driver_properties_ext_desc_t struct, chained from the ``pNext`` member of ${x}_init_driver_type_desc_t when calling ${x}InitDrivers. It is a general-purpose extension point: additional flags may be added to ${x}_init_driver_properties_ext_flags_t in the future without requiring a new structure or a new ${x}_structure_type_t value.

Supported flags:

* ``OPTIMIZE_MEMORY`` requests that the driver(s) being initialized reduce their memory footprint, mirroring ${X}_CONTEXT_FLAG_OPTIMIZE_MEMORY but applied at driver initialization instead of per-context.
* ``OPTIMIZE_PERFORMANCE`` explicitly requests that the driver(s) being initialized optimize for performance, mirroring ${X}_CONTEXT_FLAG_OPTIMIZE_PERFORMANCE but applied at driver initialization instead of per-context.

The following rules apply:

* When the ``OPTIMIZE_MEMORY`` flag is set, it establishes the default memory-optimization behavior for the driver(s) initialized by this call.
* When the ``OPTIMIZE_PERFORMANCE`` flag is set, it establishes the default performance-optimization behavior for the driver(s) initialized by this call. ``OPTIMIZE_MEMORY`` and ``OPTIMIZE_PERFORMANCE`` are mutually exclusive; if both are set, ${x}InitDrivers returns ${X}_RESULT_ERROR_INVALID_ARGUMENT.
* If neither flag is set, the memory/performance trade-off for the driver(s) initialized by this call is driver implementation specific.
* Contexts subsequently created via ${x}ContextCreate or ${x}ContextCreateEx without an explicit ${X}_CONTEXT_FLAG_OPTIMIZE_MEMORY or ${X}_CONTEXT_FLAG_OPTIMIZE_PERFORMANCE flag inherit this driver-level default, if one was established; otherwise the trade-off remains driver implementation specific.
* A context that explicitly sets its own ${x}_context_flags_t flags overrides the driver-level default for that context.
* The default context returned by ${x}DriverGetDefaultContext is created by the driver itself, not via ${x}ContextCreate or ${x}ContextCreateEx, so the application cannot supply ${x}_context_flags_t for it. The default context follows the driver-level default established by this structure, if one was established; otherwise its memory/performance trade-off is driver implementation specific.
* If this structure is not provided, the driver must assume no driver-wide properties were requested and fall back to its standard default behavior for each unset flag.
* This structure has no effect on drivers already initialized by a prior call to ${x}InitDrivers or ${x}Init; those drivers keep whatever behavior was in effect when they were first initialized.
