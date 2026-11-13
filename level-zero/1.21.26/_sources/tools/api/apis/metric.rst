============================================================
Metric
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Metric Handles
==============


.. _zet-metric-handle-t:

zet_metric_handle_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zetMetricGet`, :ref:`zetMetricCreateFromProgrammableExp2`, :ref:`zetMetricCreateFromProgrammableExp`, :ref:`zetMetricDecoderGetDecodableMetricsExp`
   | **Used by:** :ref:`zetMetricGetProperties`, :ref:`zetDeviceCreateMetricGroupsFromMetricsExp`, :ref:`zetMetricGroupAddMetricExp`, :ref:`zetMetricGroupRemoveMetricExp`, :ref:`zetMetricDestroyExp`, :ref:`zetMetricTracerDecodeExp`
   | **See also:** `Metrics (Programming Guide) <../../PROG.html#metrics>`__

.. cpp:type:: zet_metric_handle_t

    Handle of metric's object.



Metric Functions
================


.. _zetMetricGet:

zetMetricGet
------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetMetricGet
    :project: LevelZero


.. _zetMetricGetProperties:

zetMetricGetProperties
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetMetricGetProperties
    :project: LevelZero



Metric Enums
============


.. _zet-metric-type-t:

zet_metric_type_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zet-metric-properties-t`

.. doxygenenum:: zet_metric_type_t
    :project: LevelZero


 
Metric Structures
=================


.. _zet-metric-properties-t:

zet_metric_properties_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zetMetricGetProperties`
   | **pNext may point to:** :ref:`zet-export-dma-buf-exp-properties-t`

.. doxygenstruct:: zet_metric_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

