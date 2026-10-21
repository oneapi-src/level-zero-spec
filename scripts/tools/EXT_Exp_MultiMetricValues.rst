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

.. _ZET_experimental_calculate_multiple_metrics:

==========================================
 Calculating Multiple Metrics Extension
==========================================

API
----

* Functions

    * ${t}MetricGroupCalculateMultipleMetricValuesExp

* Enumerations

    * ${x}_calculate_multiple_metrics_exp_version_t

Sample Code
------------

The following code demonstrates how to calculate and process multiple metric values:

.. parsed-literal::

       // Check that the driver supports the extension and which version it reports
       uint32_t extensionCount = 0;
       ${x}DriverGetExtensionProperties(hDriver, &extensionCount, nullptr);

       std::vector<${x}_driver_extension_properties_t> extensionProperties(extensionCount);
       ${x}DriverGetExtensionProperties(hDriver, &extensionCount, extensionProperties.data());

       uint32_t extensionVersion = 0;
       for (uint32_t i = 0; i < extensionCount; i++) {
           if (strcmp(extensionProperties[i].name, ${T}_MULTI_METRICS_EXP_NAME) == 0) {
               extensionVersion = extensionProperties[i].version;
               break;
           }
       }

       if (extensionVersion == 0) {
           // Extension is not supported by the driver
           return;
       }

       // Get data count and total metric count
       uint32_t dataCount = 0;
       uint32_t totalMetricCount = 0;
       ${t}MetricGroupCalculateMultipleMetricValuesExp(hMetricGroup, type, rawDataSize, pRawData, &dataCount, &totalMetricCount, nullptr, nullptr);

       // Get metric counts and metric values
       std::vector<uint32_t> metricCounts(dataCount);
       std::vector<${t}_typed_value_t> metricValues(totalMetricCount);
       ${t}MetricGroupCalculateMultipleMetricValuesExp(hMetricGroup, type, rawDataSize, pRawData, &dataCount, &totalMetricCount, metricCounts.data(), metricValues.data());

       // Example showing how to process the metric values

       // Setup
       uint32_t metricCount = 0;
       ${t}MetricGet(hMetricGroup, &metricCount, nullptr);

       ${t}_metric_handle_t* phMetrics = malloc(metricCount * sizeof(${t}_metric_handle_t));
       ${t}MetricGet(hMetricGroup, &metricCount, phMetrics);

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
                   process_metric_value(metricValues[startIndex + metricIndex], extensionVersion);
               }
           }

           startIndex += metricCountForDataIndex;
       }
       assert(startIndex == totalMetricCount);
