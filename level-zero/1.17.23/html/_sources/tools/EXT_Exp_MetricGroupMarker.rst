
:orphan:

.. _ZET_experimental_metric_group_marker:

====================================
MetricGroup Marker Support Extension
====================================

API
----

* Structures

    * :ref:`zet-metric-source-id-exp-t`

* Functions

    * :ref:`zetCommandListAppendMarkerExp`


Metric Source ID
~~~~~~~~~~~~~~~~~

Devices can include more than one HW architecture for profiling.
Each individual profiling architecture can generate separate metrics data and can behave as individual Metric Source.
The Metric Sources can be identified by an unique id that can be retrieved using {t}_metric_source_id_exp_t

MetricGroup Marker
~~~~~~~~~~~~~~~~~~~

Markers could be added to command list to uniquely identify profiling data that are generated before and after the marker.
MetricGroups enumerated from a Metric Source could be used to generate Marker using that specific Metric Source.

Sample Code
------------

The following pseudo-code demonstrates how Metric Group Markers could be generated and collected.

.. parsed-literal::

    // 1. Select the metric group for the metrics to be collected using zetMetricGroupGet

    // 2. Identify sourceId of the selected metric group
    :ref:`zet-metric-source-id-exp-t` metricGroupSourceId{};
    metricGroupSourceId.stype = ZET_STRUCTURE_TYPE_METRIC_SOURCE_ID_EXP;

    :ref:`zet-metric-group-properties-t` metricGroupProperties;
    metricGroupProperties.pNext = &metricGroupSourceId;

    // Get the SourceId from the metricGroupProperties
    :ref:`zetMetricGroupGetProperties`\(hInterestedMetricGroup, &metricGroupProperties); 
    uint32_t markerSourceId = metricGroupSourceId.sourceId;

    // 3. Get Metric Group which support Marker Generation for that Metric Source
    zet_metric_group_handle_t hMarkerMetricGroup{};
    for (hMetricGroup : allMetricGroups){
        :ref:`zet-metric-group-type-exp-t` metricGroupType{};
        metricGroupType.stype = {ZET_STRUCTURE_TYPE_METRIC_GROUP_TYPE_EXP};

        // Get Metric Group Type and Source Id using zetMetricGroupGetProperties
        metricGroupProperties.pNext = &metricGroupType;
        metricGroupType.pNext = &metricGroupSourceId;
        :ref:`zetMetricGroupGetProperties`\(hMetricGroup, &metricGroupProperties);

        if(metricGroupType.type == ZET_METRIC_GROUP_TYPE_EXP_FLAG_MARKER &&
            markerSourceId == metricGroupSourceId.sourceId){
            hMarkerMetricGroup = hMetricGroup;
        }
    }

    // 4. Generate marker using the interested MetricGroup
    :ref:`zetCommandListAppendMarkerExp`\(hCommandList, hMarkerMetricGroup, 100);

    // 5. Collect metrics for the hMarkerMetricGroup using tracer (or) streamer sampling type

