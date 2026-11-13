============================================================
Metric Query Pool
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Metric Query Pool Handles
=========================


.. _zet-metric-query-pool-handle-t:

zet_metric_query_pool_handle_t
------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zetMetricQueryPoolCreate`
   | **Used by:** :ref:`zetMetricQueryPoolDestroy`, :ref:`zetMetricQueryCreate`
   | **See also:** :ref:`Metric Query (Programming Guide) <Event-based>`

.. cpp:type:: zet_metric_query_pool_handle_t

    Handle of metric query pool's object.



Metric Query Pool Functions
===========================


.. _zetMetricQueryPoolCreate:

zetMetricQueryPoolCreate
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetMetricQueryPoolCreate
    :project: LevelZero


.. _zetMetricQueryPoolDestroy:

zetMetricQueryPoolDestroy
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetMetricQueryPoolDestroy
    :project: LevelZero



Metric Query Pool Enums
=======================


.. _zet-metric-query-pool-type-t:

zet_metric_query_pool_type_t
----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zet-metric-query-pool-desc-t`

.. doxygenenum:: zet_metric_query_pool_type_t
    :project: LevelZero


 
Metric Query Pool Structures
============================


.. _zet-metric-query-pool-desc-t:

zet_metric_query_pool_desc_t
----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zetMetricQueryPoolCreate`

.. doxygenstruct:: zet_metric_query_pool_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

