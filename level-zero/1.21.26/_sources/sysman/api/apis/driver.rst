============================================================
Driver
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Driver Handles
==============


.. _zes-driver-handle-t:

zes_driver_handle_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDriverGet`
   | **Used by:** :ref:`zesDriverGetProperties`, :ref:`zesDriverGetApiVersion`, :ref:`zesDriverGetExtensionProperties`, :ref:`zesDriverGetExtensionFunctionAddress`, :ref:`zesDeviceGet`, :ref:`zesDriverEventRegisterExt`, :ref:`zesDriverEventListenExt`, :ref:`zesDriverGetDeviceByUuidExp`, :ref:`zesDriverEnumInfoLogsExt`, :ref:`zesDriverGetPciDeviceProperties`

.. cpp:type:: zes_driver_handle_t

    Handle to a driver instance.



Driver Functions
================


.. _zesDriverEventListen:

zesDriverEventListen
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesDriverEventListen
    :project: LevelZero


.. _zesDriverEventListenEx:

zesDriverEventListenEx
----------------------

.. rst-class:: api-version

*Added in version 1.1*

.. doxygenfunction:: zesDriverEventListenEx
    :project: LevelZero


.. _zesDriverGet:

zesDriverGet
------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesDriverGet
    :project: LevelZero


.. _zesDriverGetExtensionProperties:

zesDriverGetExtensionProperties
-------------------------------

.. rst-class:: api-version

*Added in version 1.8*

.. doxygenfunction:: zesDriverGetExtensionProperties
    :project: LevelZero


.. _zesDriverGetExtensionFunctionAddress:

zesDriverGetExtensionFunctionAddress
------------------------------------

.. rst-class:: api-version

*Added in version 1.8*

.. doxygenfunction:: zesDriverGetExtensionFunctionAddress
    :project: LevelZero


.. _zesDriverGetProperties:

zesDriverGetProperties
----------------------

.. rst-class:: api-version

*Added in version 1.19*

.. doxygenfunction:: zesDriverGetProperties
    :project: LevelZero


.. _zesDriverGetPciDeviceProperties:

zesDriverGetPciDeviceProperties
-------------------------------

.. rst-class:: api-version

*Added in version 1.20*

.. doxygenfunction:: zesDriverGetPciDeviceProperties
    :project: LevelZero


.. _zesDriverGetApiVersion:

zesDriverGetApiVersion
----------------------

.. rst-class:: api-version

*Added in version 1.21*

.. doxygenfunction:: zesDriverGetApiVersion
    :project: LevelZero



Driver Enums
============


.. _zes-api-version-t:

zes_api_version_t
-----------------

.. rst-class:: api-version

*Added in version 1.21*

.. container:: api-usage

   | **Used by:** :ref:`zesDriverGetApiVersion`

.. doxygenenum:: zes_api_version_t
    :project: LevelZero


.. _zes-event-type-flags-t:

zes_event_type_flags_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDeviceEventRegister`, :ref:`zesDriverEventListen`, :ref:`zesDriverEventListenEx`, :ref:`zesDriverEventRegisterExt`, :ref:`zesDriverEventListenExt`

.. doxygentypedef:: zes_event_type_flags_t
    :project: LevelZero

.. doxygenenum:: zes_event_type_flag_t
    :project: LevelZero


 
Driver Structures
=================


.. _zes-driver-properties-t:

zes_driver_properties_t
-----------------------

.. rst-class:: api-version

*Added in version 1.19*

.. container:: api-usage

   | **Used by:** :ref:`zesDriverGetProperties`

.. doxygenstruct:: zes_driver_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-driver-extension-properties-t:

zes_driver_extension_properties_t
---------------------------------

.. rst-class:: api-version

*Added in version 1.8*

.. container:: api-usage

   | **Used by:** :ref:`zesDriverGetExtensionProperties`

.. doxygenstruct:: zes_driver_extension_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-driver-pci-device-properties-t:

zes_driver_pci_device_properties_t
----------------------------------

.. rst-class:: api-version

*Added in version 1.20*

.. container:: api-usage

   | **Used by:** :ref:`zesDriverGetPciDeviceProperties`

.. doxygenstruct:: zes_driver_pci_device_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

