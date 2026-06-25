
:orphan:

.. _ZET_experimental_metric_export_data:

==========================================
Metrics Export Data Experimental Extension
==========================================

API
----

* Structures

    * :ref:`zet-metric-calculate-exp-desc-t`

* Functions

    * :ref:`zetMetricGroupGetExportDataExp`
    * :ref:`zetMetricGroupCalculateMetricExportDataExp`

Sample Code
------------

The following code shows how to export metrics raw data for a metric group.

.. parsed-literal::

    // Get size for export data
    size_t exportDataSize = 0;
    :ref:`zetMetricGroupGetExportDataExp`\(hMetricGroup, rawData, rawDataSize, &exportDataSize, nullptr);

    // Allocate buffer for export data
    uint8_t* pExportData = malloc(exportDataSize);

    // Retrieve export data
    :ref:`zetMetricGroupGetExportDataExp`\(hMetricGroup, rawData, rawDataSize, &exportDataSize, pExportData);


The following code shows how to perform metrics calculation of collected data, which can be done in a different system than where data was collected.

.. parsed-literal::

    // Get data count and total metric count
    :ref:`zet-metric-group-calculation-type-t` type = :ref:`ZET_METRIC_GROUP_CALCULATION_TYPE_METRIC_VALUES <zet-metric-group-calculation-type-t>`\;
    :ref:`zet-metric-calculate-exp-desc-t` calculateDesc;
    calculateDesc.rawReportSkipCount = 0;
    :ref:`zetMetricGroupCalculateMetricExportDataExp`\(hDriver, type, exportDataSize, pExportData, &calculateDesc, &dataCount, &totalMetricCount, nullptr, nullptr);

    void* pMetricCounts = malloc(dataCount * sizeof(uint32_t));
    void* pMetricValues = malloc(totalMetricCount * sizeof(zet_typed_value_t));

    // Get metric counts and metric values
    :ref:`zetMetricGroupCalculateMetricExportDataExp`\(hDriver, type, exportDataSize, pExportData, &calculateDesc, &dataCount, &totalMetricCount, pMetricCounts, pMetricValues);
