
:orphan:

.. _ZE_extension_init_driver_app_version:

============================================
 Init Driver Application Version Extension
============================================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.18*

API
----
* Enumerations


    * :ref:`ze-init-driver-app-version-ext-version-t`


* Structures


    * :ref:`ze-init-driver-app-version-ext-desc-t`

Declaring the Application-Supported API Version
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This extension lets an application pass the driver a hint describing the maximum core 'oneAPI' Level-Zero API version it was built against and is able to handle. The application supplies the hint in a :ref:`ze-init-driver-app-version-ext-desc-t` struct, chained from the ``pNext`` member of :ref:`ze-init-driver-type-desc-t` when calling :ref:`zeInitDrivers`\.

The hint is advisory: a driver is free to ignore it. :ref:`zeDriverGetApiVersion` continues to report the version supported by the *driver*, independently of any version the application declares.

The following rules apply:

* The ``apiVersionHint`` field declares the maximum core 'oneAPI' Level-Zero API version the application was built against and is able to handle.
* A driver may use the hint to gate version-dependent behavior for backward compatibility, for example only reporting enumerants or memory types introduced in newer API versions to applications that understand them.
* If this structure is not provided, the driver must assume the application supports only the baseline behavior and must not rely on any version-gated behavior being understood by the application.
* A driver that acts on the hint should clamp version-gated behavior to the minimum of the version it supports and the version the application declares.
