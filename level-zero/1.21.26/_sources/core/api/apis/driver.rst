============================================================
Driver
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Driver Handles
==============


.. _ze-driver-handle-t:

ze_driver_handle_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeDriverGet`, :ref:`zeInitDrivers`
   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-ze-driver-handle-t-3"><span class="api-usage-links">` :ref:`zeDriverGetApiVersion`, :ref:`zeDriverGetProperties`, :ref:`zeDriverGetIpcProperties`, :ref:`zeDriverGetExtensionProperties`, :ref:`zeDriverGetExtensionFunctionAddress`, :ref:`zeDriverGetLastErrorDescription`, :ref:`zeDriverGetDefaultContext`, :ref:`zeDeviceGet`, :ref:`zeContextCreate`, :ref:`zeContextCreateEx`, :ref:`zeFabricVertexGetExp`, :ref:`zeRTASBuilderCreateExp`, :ref:`zeDriverRTASFormatCompatibilityCheckExp`, :ref:`zeRTASParallelOperationCreateExp`, :ref:`zeRTASBuilderCreateExt`, :ref:`zeDriverRTASFormatCompatibilityCheckExt`, :ref:`zeRTASParallelOperationCreateExt` :raw-html:`</span><label for="usage-ze-driver-handle-t-3"><span class="more">Show all 17</span><span class="less">Show less</span></label></span>`
   | **Used by (Tools):** :ref:`zetMetricGroupCalculateMetricExportDataExp`
   | **Used by (Sysman):** :ref:`zesDriverEventListen`, :ref:`zesDriverEventListenEx`
   | **See also:** `Drivers (Programming Guide) <../../PROG.html#drivers>`__

.. cpp:type:: ze_driver_handle_t

    Handle of a driver instance.



Driver Functions
================


.. _zeDriverGetApiVersion:

zeDriverGetApiVersion
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeDriverGetApiVersion
    :project: LevelZero


.. _zeDriverGetProperties:

zeDriverGetProperties
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeDriverGetProperties
    :project: LevelZero


.. _zeDriverGetIpcProperties:

zeDriverGetIpcProperties
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeDriverGetIpcProperties
    :project: LevelZero


.. _zeDriverGetExtensionProperties:

zeDriverGetExtensionProperties
------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeDriverGetExtensionProperties
    :project: LevelZero


.. _zeDriverGetExtensionFunctionAddress:

zeDriverGetExtensionFunctionAddress
-----------------------------------

.. rst-class:: api-version

*Added in version 1.1*

.. doxygenfunction:: zeDriverGetExtensionFunctionAddress
    :project: LevelZero


.. _zeDriverGetLastErrorDescription:

zeDriverGetLastErrorDescription
-------------------------------

.. rst-class:: api-version

*Added in version 1.6*

.. doxygenfunction:: zeDriverGetLastErrorDescription
    :project: LevelZero


.. _zeDriverGetDefaultContext:

zeDriverGetDefaultContext
-------------------------

.. rst-class:: api-version

*Added in version 1.14*

.. doxygenfunction:: zeDriverGetDefaultContext
    :project: LevelZero



Driver Enums
============


.. _ze-api-version-t:

ze_api_version_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeDriverGetApiVersion`
   | **Member of:** :ref:`ze-init-driver-app-version-ext-desc-t`

.. doxygenenum:: ze_api_version_t
    :project: LevelZero


.. _ze-ipc-property-flags-t:

ze_ipc_property_flags_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-driver-ipc-properties-t`

.. doxygentypedef:: ze_ipc_property_flags_t
    :project: LevelZero

.. doxygenenum:: ze_ipc_property_flag_t
    :project: LevelZero


 
Driver Structures
=================


.. _ze-driver-properties-t:

ze_driver_properties_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeDriverGetProperties`
   | **pNext may point to:** :ref:`ze-driver-memory-free-ext-properties-t`, :ref:`ze-driver-ddi-handles-ext-properties-t`

.. doxygenstruct:: ze_driver_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-driver-ipc-properties-t:

ze_driver_ipc_properties_t
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeDriverGetIpcProperties`

.. doxygenstruct:: ze_driver_ipc_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-driver-extension-properties-t:

ze_driver_extension_properties_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeDriverGetExtensionProperties`

.. doxygenstruct:: ze_driver_extension_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

