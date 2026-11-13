============================================================
Device
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Device Handles
==============


.. _zet-device-handle-t:

zet_device_handle_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-zet-device-handle-t-3"><span class="api-usage-links">` :ref:`zetDeviceGetDebugProperties`, :ref:`zetDebugAttach`, :ref:`zetDebugGetRegisterSetProperties`, :ref:`zetMetricGroupGet`, :ref:`zetContextActivateMetricGroups`, :ref:`zetMetricStreamerOpen`, :ref:`zetMetricQueryPoolCreate`, :ref:`zetMetricProgrammableGetExp`, :ref:`zetDeviceCreateMetricGroupsFromMetricsExp`, :ref:`zetMetricGroupCreateExp`, :ref:`zetDeviceGetConcurrentMetricGroupsExp`, :ref:`zetMetricTracerCreateExp`, :ref:`zetDeviceEnableMetricsExp`, :ref:`zetDeviceDisableMetricsExp` :raw-html:`</span><label for="usage-zet-device-handle-t-3"><span class="more">Show all 14</span><span class="less">Show less</span></label></span>`
   | **Alias of:** :ref:`ze-device-handle-t`

.. cpp:type:: zet_device_handle_t

    Handle of device object.



Device Functions
================


.. _zetDeviceGetDebugProperties:

zetDeviceGetDebugProperties
---------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDeviceGetDebugProperties
    :project: LevelZero



Device Enums
============


.. _zet-device-debug-property-flags-t:

zet_device_debug_property_flags_t
---------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zet-device-debug-properties-t`

.. doxygentypedef:: zet_device_debug_property_flags_t
    :project: LevelZero

.. doxygenenum:: zet_device_debug_property_flag_t
    :project: LevelZero


 
Device Structures
=================


.. _zet-device-debug-properties-t:

zet_device_debug_properties_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zetDeviceGetDebugProperties`

.. doxygenstruct:: zet_device_debug_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

