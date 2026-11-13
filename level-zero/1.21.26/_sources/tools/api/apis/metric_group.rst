============================================================
Metric Group
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Metric Group Handles
====================


.. _zet-metric-group-handle-t:

zet_metric_group_handle_t
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zetMetricGroupGet`, :ref:`zetDeviceCreateMetricGroupsFromMetricsExp`, :ref:`zetMetricGroupCreateExp`, :ref:`zetDeviceGetConcurrentMetricGroupsExp`
   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-zet-metric-group-handle-t-3"><span class="api-usage-links">` :ref:`zetMetricGroupGetProperties`, :ref:`zetMetricGroupCalculateMetricValues`, :ref:`zetMetricGet`, :ref:`zetContextActivateMetricGroups`, :ref:`zetMetricStreamerOpen`, :ref:`zetMetricQueryPoolCreate`, :ref:`zetMetricGroupCalculateMultipleMetricValuesExp`, :ref:`zetMetricGroupGetGlobalTimestampsExp`, :ref:`zetMetricGroupGetExportDataExp`, :ref:`zetMetricGroupAddMetricExp`, :ref:`zetMetricGroupRemoveMetricExp`, :ref:`zetMetricGroupCloseExp`, :ref:`zetMetricGroupDestroyExp`, :ref:`zetMetricTracerCreateExp`, :ref:`zetCommandListAppendMarkerExp` :raw-html:`</span><label for="usage-zet-metric-group-handle-t-3"><span class="more">Show all 15</span><span class="less">Show less</span></label></span>`
   | **See also:** `Metric Groups (Programming Guide) <../../PROG.html#metric-groups>`__

.. cpp:type:: zet_metric_group_handle_t

    Handle of metric group's object.



Metric Group Functions
======================


.. _zetMetricGroupGet:

zetMetricGroupGet
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetMetricGroupGet
    :project: LevelZero


.. _zetMetricGroupGetProperties:

zetMetricGroupGetProperties
---------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetMetricGroupGetProperties
    :project: LevelZero


.. _zetMetricGroupCalculateMetricValues:

zetMetricGroupCalculateMetricValues
-----------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetMetricGroupCalculateMetricValues
    :project: LevelZero



Metric Group Enums
==================


.. _zet-metric-group-sampling-type-flags-t:

zet_metric_group_sampling_type_flags_t
--------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zetMetricGroupCreateExp`
   | **Member of:** :ref:`zet-metric-group-properties-t`, :ref:`zet-metric-programmable-exp-properties-t`

.. doxygentypedef:: zet_metric_group_sampling_type_flags_t
    :project: LevelZero

.. doxygenenum:: zet_metric_group_sampling_type_flag_t
    :project: LevelZero


.. _zet-metric-group-calculation-type-t:

zet_metric_group_calculation_type_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zetMetricGroupCalculateMetricValues`, :ref:`zetMetricGroupCalculateMultipleMetricValuesExp`, :ref:`zetMetricGroupCalculateMetricExportDataExp`

.. doxygenenum:: zet_metric_group_calculation_type_t
    :project: LevelZero


 
Metric Group Structures
=======================


.. _zet-metric-group-properties-t:

zet_metric_group_properties_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zetMetricGroupGetProperties`
   | **pNext may point to:** :ref:`zet-metric-global-timestamps-resolution-exp-t`, :ref:`zet-metric-group-type-exp-t`, :ref:`zet-export-dma-buf-exp-properties-t`, :ref:`zet-metric-source-id-exp-t`

.. doxygenstruct:: zet_metric_group_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

