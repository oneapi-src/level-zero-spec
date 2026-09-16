
:orphan:

.. _ZET_experimental_metric_source_id:

====================================
Metric Source ID Support Extension
====================================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.13*

API
----

* Structures

    * :ref:`zet-metric-source-id-exp-t`


Metric Source ID
~~~~~~~~~~~~~~~~~

Devices can include more than one HW architecture for profiling.
Each individual profiling architecture can generate separate metrics data and can behave as individual Metric Source.
The Metric Sources can be identified by an unique ID that can be retrieved using :ref:`zet-metric-source-id-exp-t`\.
Metrics in a metric group are associated with the same specific Metric Source. Therefore, the property is queried from the metric group.

Sample Code
------------

The following pseudo-code demonstrates how Metric source ID can be retrieved.

.. parsed-literal::

    // 1. Select the metric group for the metrics to be collected using zetMetricGroupGet

    // 2. Identify sourceId of the selected metric in the metric group
    :ref:`zet-metric-source-id-exp-t` metricGroupSourceId{};
    metricGroupSourceId.stype = :ref:`ZET_STRUCTURE_TYPE_METRIC_SOURCE_ID_EXP <zet-structure-type-t>`\;
    metricGroupSourceId.pNext = nullptr;

    :ref:`zet-metric-group-properties-t` metricGroupProperties;
    metricGroupProperties.stype = :ref:`ZET_STRUCTURE_TYPE_METRIC_GROUP_PROPERTIES <zet-structure-type-t>`\;
    metricGroupProperties.pNext = &metricGroupSourceId;

    // Get the SourceId from the metricGroupProperties
    :ref:`zetMetricGroupGetProperties`\(hInterestedMetricGroup, &metricGroupProperties); 
    uint32_t metricSourceId = metricGroupSourceId.sourceId;