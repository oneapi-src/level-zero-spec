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

.. _ZET_experimental_metric_export_data:

==========================================
Metrics Export Data Experimental Extension
==========================================

API
----

* Structures

    * ${t}_metric_calculate_exp_desc_t

* Functions

    * ${t}MetricGroupGetExportDataExp
    * ${t}MetricGroupCalculateMetricExportDataExp

Sample Code
------------

The following code shows how to export metrics raw data for a metric group.

.. parsed-literal::

    // Get size for export data
    size_t exportDataSize = 0;
    uint32_t dataCount = 0;
    uint32_t totalMetricCount = 0;
    ${t}_metric_group_calculation_type_t type = ${T}_METRIC_GROUP_CALCULATION_TYPE_METRIC_VALUES;
    ${t}MetricGroupCalculateMetricExportDataExp (hDriver, type, &exportDataSize, nullptr, nullptr, &dataCount, &totalMetricCount, nullptr, nullptr);

    // Allocate buffer for export data
    uint8_t* pExportData = malloc(exportDataSize);

    // Retrieve export data and data format
    ${t}MetricGroupCalculateMetricExportDataExp (hDriver, type, &exportDataSize, pExportData, nullptr, &dataCount, &totalMetricCount, nullptr, nullptr);


The following code shows how to perform metrics calculation of collected data, which can be done in a different system than where data was collected.

.. parsed-literal::

    // Get data count and total metric count
    ${t}_metric_group_calculation_type_t type = ${T}_METRIC_GROUP_CALCULATION_TYPE_METRIC_VALUES;
    ${t}_metric_calculate_exp_desc_t calculateDesc;
    calculateDesc.rawReportSkipCount = 0;
    ${t}MetricGroupCalculateMetricExportDataExp(hDriver, type, exportDataSize, pExportData, &calculateDesc,
                        &dataCount, &totalMetricCount, nullptr, nullptr);

    void* pMetricCounts = malloc(dataCount * sizeof(uint32_t));
    void* pMetricValues = malloc(totalMetricCount * sizeof(zet_typed_value_t));

    // Get metric counts and metric values
    ${t}MetricGroupCalculateMetricExportDataExp(hDriver, type, exportDataSize, pExportData, &calculateDesc,
                        &dataCount, &totalMetricCount, pMetricCounts, pMetricValues);
