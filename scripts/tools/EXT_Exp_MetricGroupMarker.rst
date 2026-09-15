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

.. _ZET_experimental_metric_group_marker:

====================================
MetricGroup Marker Support Extension
====================================

API
----

* Functions

    * ${t}CommandListAppendMarkerExp

MetricGroup Marker
~~~~~~~~~~~~~~~~~~~

Markers could be added to command list to uniquely identify profiling data that are generated before and after the marker.
MetricGroups enumerated from a Metric Source could be used to generate Marker using that specific Metric Source.

Sample Code
------------

The following pseudo-code demonstrates how Metric Group Markers could be generated and collected.

.. parsed-literal::

    // 1. Select the metric group for the metrics to be collected using zetMetricGroupGet

    // 2. Identify sourceId of the selected metric group. See ZET_experimental_metric_source_id for details.
     ${t}_metric_source_id_exp_t metricGroupSourceId{};
    metricGroupSourceId.stype = ${T}_STRUCTURE_TYPE_METRIC_SOURCE_ID_EXP;
    metricGroupSourceId.pNext = nullptr;

    ${t}_metric_group_properties_t metricGroupProperties;
    metricGroupProperties.stype = ${T}_STRUCTURE_TYPE_METRIC_GROUP_PROPERTIES;
    metricGroupProperties.pNext = &metricGroupSourceId;

    // Get the SourceId from the metricGroupProperties
    ${t}MetricGroupGetProperties(hInterestedMetricGroup, &metricGroupProperties); 
    uint32_t markerSourceId = metricGroupSourceId.sourceId;   // retrieve from ZET_experimental_metric_source_id

    // 3. Get Metric Group which support Marker Generation for that Metric Source
    zet_metric_group_handle_t hMarkerMetricGroup{};
    for (hMetricGroup : allMetricGroups){
        ${t}_metric_group_type_exp_t metricGroupType{};
        metricGroupType.stype = ${T}_STRUCTURE_TYPE_METRIC_GROUP_TYPE_EXP;
        metricGroupType.pNext = &metricGroupSourceId;

        // Get Metric Group Type and Source Id using zetMetricGroupGetProperties
        metricGroupProperties.pNext = &metricGroupType;
        
        ${t}MetricGroupGetProperties(hMetricGroup, &metricGroupProperties);

        if(metricGroupType.type == ZET_METRIC_GROUP_TYPE_EXP_FLAG_MARKER &&
            markerSourceId == metricGroupSourceId.sourceId){
            hMarkerMetricGroup = hMetricGroup;
        }
    }

    // 4. Generate marker using the interested MetricGroup
    ${t}CommandListAppendMarkerExp(hCommandList, hMarkerMetricGroup, 100);

    // 5. Collect metrics for the hMarkerMetricGroup using tracer (or) streamer sampling type

