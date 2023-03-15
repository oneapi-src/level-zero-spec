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

    * ${t}_metric_export_data_format_exp_t
    * ${t}_metric_calculate_exp_desc_t

* Functions

    * ${t}MetricGroupGetExportDataExp
    * ${x}DriverCalculateMetricExportDataExp

Sample Code
------------

The following code shows how to export metrics raw data.

.. parsed-literal::

    // Get size for export data and count for data format
    size_t exportDataSize = 0;
    uint32_t exportDataFormatCount = 0;
    ${t}MetricGroupGetExportDataExp (hMetricGroup, rawData, rawDataSize,
                                &exportDataSize, &exportDataFormatCount, nullptr, nullptr);

    // Allocate buffer for export data and data format
    uint8_t* pExportData = malloc(exportDataSize);
    ${t}_metric_export_data_format_exp_t* pExportFormatData =
                            malloc(sizeof(${t}_metric_export_data_format_exp_t) * exportDataFormatCount);

    // Retrieve export data and data format
    ${t}MetricGroupGetExportDataExp (hMetricGroup, rawData, rawDataSize,
                        &exportDataSize, &exportDataFormatCount, pExportData, pExportFormatData);



The following code shows how to perform metrics calculation of collected data, which can be done in a different system.

.. parsed-literal::

    // Get data count and total metric count
    uint32_t dataCount = 0;
    uint32_t totalMetricCount = 0;
    ${t}_metric_group_calculation_type_t type = ${T}_METRIC_GROUP_CALCULATION_TYPE_METRIC_VALUES;
    ${t}_metric_calculate_exp_desc_t calculateDesc;
    calculateDesc.rawReportSkipCount = 0;
    ${x}DriverCalculateMetricExportDataExp(hDriver, type, exportDataSize, pExportData, &calculateDesc,
                        &dataCount, &totalMetricCount, nullptr, nullptr);

    void* pMetricCounts = malloc(dataCount * sizeof(uint32_t));
    void* pMetricValues = malloc(totalMetricCount * sizeof(zet_typed_value_t));

    // Get metric counts and metric values
    ${x}DriverCalculateMetricExportDataExp(hDriver, type, exportDataSize, pExportData, &calculateDesc,
                        &dataCount, &totalMetricCount, pMetricCounts, pMetricValues);


The following code shows how to optionally process exported data format elements.

.. parsed-literal::

    // Optional: Processing of Data format elements
    while(exportDataFormatCount--){

    if(strcmp(pDataFormat->name, "GlobalSymbolName") == 0){
        // Read Global Symbol Name
        const char* symbolName = (const char*)pExportData;

        // Do appropriate handling for "GlobalSymbolName"
    }

    if(strcmp(pDataFormat->name, "GlobalSymbolValue") == 0){
        // Read Global Symbol Value
        if(pDataFormat->type == ZET_VALUE_TYPE_UINT16){
            uint16_t value = 0;
            memcpy(&value, pExportData, sizeof(uint16_t);
        }

        // Do appropriate handling for "GlobalSymbolValue"
    }

    pExportData += pDataFormat->lengthInBytes;
    pDataFormat++;
    }
