
:orphan:

.. _ZET_experimental_calculate_multiple_metrics:

==========================================
 Calculating Multiple Metrics Extension
==========================================

API
----

* Functions

    * :ref:`zetMetricGroupCalculateMultipleMetricValuesExp`

Sample Code
------------

The following code demonstrates how to calculate and process multiple metric values:

.. parsed-literal::

       // Get data count and total metric count
       uint32_t dataCount = 0;
       uint32_t totalMetricCount = 0;
       :ref:`zetMetricGroupCalculateMultipleMetricValuesExp`\(hMetricGroup, type, rawDataSize, pRawData, &dataCount, &totalMetricCount, nullptr, nullptr);

       // Get metric counts and metric values
       std::vector<uint32_t> metricCounts(dataCount);
       std::vector<:ref:`zet-typed-value-t`\> metricValues(totalMetricCount);
       :ref:`zetMetricGroupCalculateMultipleMetricValuesExp`\(hMetricGroup, type, rawDataSize, pRawData, &dataCount, &totalMetricCount, metricCounts.data(), metricValues.data());

       // Example showing how to process the metric values

       // Setup
       uint32_t metricCount = 0;
       :ref:`zetMetricGet`\(hMetricGroup, &metricCount, nullptr);

       zet_metric_handle_t* phMetrics = malloc(metricCount * sizeof(zet_metric_handle_t));
       :ref:`zetMetricGet`\(hMetricGroup, &metricCount, phMetrics);

       // This loop over metric data is new for this extension
       uint32_t startIndex = 0;
       for (uint32_t dataIndex = 0; dataIndex < dataCount; dataIndex++) {

           // Processing each metric data is the same as for the single
           // calculate metric values
           const uint32_t metricCountForDataIndex = metricCounts[dataIndex];
           const uint32_t reportCount = metricCountForDataIndex / metricCount;
           for (uint32_t report = 0; report < reportCount; report++) {
               for (uint32_t metric = 0; metric < metricCount ; metric++) {
                   const size_t metricIndex = report * metricCount + metric;
                   process_metric_value(metricValues[startIndex + metricIndex]));
               }
           }

           startIndex += metricCountForDataIndex;
       }
       assert(startIndex == totalMetricCount);
