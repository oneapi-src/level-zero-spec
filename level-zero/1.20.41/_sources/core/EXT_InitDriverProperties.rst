
:orphan:

.. _ZE_extension_init_driver_properties:

===================================
 Init Driver Properties Extension
===================================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.20*

API
----
* Enumerations


    * :ref:`ze-init-driver-properties-ext-version-t`
    * :ref:`ze-init-driver-properties-ext-flags-t`


* Structures


    * :ref:`ze-init-driver-properties-ext-desc-t`

Declaring Driver-Wide Properties at Initialization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This extension lets an application declare driver-wide properties for the driver(s) being initialized. The application supplies the properties in a :ref:`ze-init-driver-properties-ext-desc-t` struct, chained from the ``pNext`` member of :ref:`ze-init-driver-type-desc-t` when calling :ref:`zeInitDrivers`\. It is a general-purpose extension point: additional flags may be added to :ref:`ze-init-driver-properties-ext-flags-t` in the future without requiring a new structure or a new :ref:`ze-structure-type-t` value.

Supported flags:

* ``OPTIMIZE_MEMORY`` requests that the driver(s) being initialized reduce their memory footprint, mirroring :ref:`ZE_CONTEXT_FLAG_OPTIMIZE_MEMORY <ze-context-flags-t>` but applied at driver initialization instead of per-context.
* ``OPTIMIZE_PERFORMANCE`` explicitly requests that the driver(s) being initialized optimize for performance, mirroring :ref:`ZE_CONTEXT_FLAG_OPTIMIZE_PERFORMANCE <ze-context-flags-t>` but applied at driver initialization instead of per-context.

The following rules apply:

* When the ``OPTIMIZE_MEMORY`` flag is set, it establishes the default memory-optimization behavior for the driver(s) initialized by this call.
* When the ``OPTIMIZE_PERFORMANCE`` flag is set, it establishes the default performance-optimization behavior for the driver(s) initialized by this call. ``OPTIMIZE_MEMORY`` and ``OPTIMIZE_PERFORMANCE`` are mutually exclusive; if both are set, :ref:`zeInitDrivers` returns :ref:`ZE_RESULT_ERROR_INVALID_ARGUMENT <ze-result-t>`\.
* If neither flag is set, the memory/performance trade-off for the driver(s) initialized by this call is driver implementation specific.
* Contexts subsequently created via :ref:`zeContextCreate` or :ref:`zeContextCreateEx` without an explicit :ref:`ZE_CONTEXT_FLAG_OPTIMIZE_MEMORY <ze-context-flags-t>` or :ref:`ZE_CONTEXT_FLAG_OPTIMIZE_PERFORMANCE <ze-context-flags-t>` flag inherit this driver-level default, if one was established; otherwise the trade-off remains driver implementation specific.
* A context that explicitly sets its own :ref:`ze-context-flags-t` flags overrides the driver-level default for that context.
* The default context returned by :ref:`zeDriverGetDefaultContext` is created by the driver itself, not via :ref:`zeContextCreate` or :ref:`zeContextCreateEx`\, so the application cannot supply :ref:`ze-context-flags-t` for it. The default context follows the driver-level default established by this structure, if one was established; otherwise its memory/performance trade-off is driver implementation specific.
* If this structure is not provided, the driver must assume no driver-wide properties were requested and fall back to its standard default behavior for each unset flag.
* This structure has no effect on drivers already initialized by a prior call to :ref:`zeInitDrivers` or :ref:`zeInit`\; those drivers keep whatever behavior was in effect when they were first initialized.
