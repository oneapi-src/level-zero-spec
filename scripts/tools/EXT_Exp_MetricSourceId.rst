<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    t=tags['$t']
    T=t.upper()
%>
:orphan:

.. _ZET_experimental_metric_source_id:

====================================
Metric Source ID Support Extension
====================================

API
----

* Structures

    * ${t}_metric_source_id_exp_t


Metric Source ID
~~~~~~~~~~~~~~~~~

Devices can include more than one HW architecture for profiling.
Each individual profiling architecture can generate separate metrics data and can behave as individual Metric Source.
The Metric Sources can be identified by an unique ID that can be retrieved using ${t}_metric_source_id_exp_t.
Metrics in a metric group are associated with the same specific Metric Source. Therefore, the property is queried from the metric group.

Sample Code
------------

The following pseudo-code demonstrates how Metric source ID can be retrieved.

.. parsed-literal::

    // 1. Select the metric group for the metrics to be collected using zetMetricGroupGet

    // 2. Identify sourceId of the selected metric in the metric group
    ${t}_metric_source_id_exp_t metricGroupSourceId{};
    metricGroupSourceId.stype = ${T}_STRUCTURE_TYPE_METRIC_SOURCE_ID_EXP;
    metricGroupSourceId.pNext = nullptr;

    ${t}_metric_group_properties_t metricGroupProperties;
    metricGroupProperties.stype = ${T}_STRUCTURE_TYPE_METRIC_GROUP_PROPERTIES;
    metricGroupProperties.pNext = &metricGroupSourceId;

    // Get the SourceId from the metricGroupProperties
    ${t}MetricGroupGetProperties(hInterestedMetricGroup, &metricGroupProperties); 
    uint32_t metricSourceId = metricGroupSourceId.sourceId;