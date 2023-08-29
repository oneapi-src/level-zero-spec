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

.. _ZET_experimental_programmable_metric:

==========================================
Metric Programmable Experimental Extension
==========================================

API
----
* Enumerations

    * ${t}_metric_programmable_param_type_exp_t

* Structures

    * ${t}_metric_programmable_exp_properties_t
    * ${t}_metric_programmable_param_exp_desc_t
    * ${t}_metric_programmable_param_value_exp_t
    * ${t}_metric_programmable_param_value_exp_desc_t
    * ${t}_value_exp_desc_t
    * ${t}_value_uint64_range_exp_t

* Functions

    * ${t}MetricProgrammableGetExp
    * ${t}MetricProgrammableGetPropertiesExp
    * ${t}MetricProgrammableGetParamDescriptionExp
    * ${t}MetricProgrammableGetParamValueDescriptionExp
    * ${t}MetricCreateFromProgrammableExp
    * ${t}MetricGroupCreateExp
    * ${t}MetricGroupAddMetricExp
    * ${t}MetricGroupRemoveMetricExp
    * ${t}MetricDestroyExp
    * ${t}MetricGroupDestroyExp

Metric Programmable
~~~~~~~~~~~~~~~~~~~

Application can use ${t}MetricGroupGet to enumerate the list of metric groups and the metrics available for collection.
However Applications may also want to collect custom metrics which are not listed as part of the enumeration.
This is made possible by making a list of programmable metrics available to the application, so that it choose different parameter values for the preparing custom metrics.

Sample Code
------------

The following pseudo-code demonstrates how programmable metrics could be enumerated and custom values could be set to the metric parameters.

.. parsed-literal::

    ${t}_metric_handle_t * metricHandles = null_ptr;
    uint32_t metricHandleCount = 0;
    ${t}_metric_group_handle_t metricGroup;

    // Query and Get metric programmable handles
    uint32_t programmableCount = 0;
    ${t}MetricProgrammableGetExp(device, &programmableCount, nullptr);
    ${t}_metric_programmable_exp_handle_t * metricProgrammableHandles = allocate(sizeof(${t}_metric_programmable_exp_handle_t) * programmableCount);
    ${t}MetricProgrammableGetExp(device, &programmableCount, metricProgrammableHandles);

    // Create metrics from metric programmable handles
    for(uint32_t i = 0; i < programmableCount; i++){

        ${t}_metric_programmable_exp_handle_t * programmableHandle = metricProgrammableHandles[i];
        ${t}_metric_programmable_exp_properties_t programmableProperties{};
        ${t}MetricProgrammableGetPropertiesExp(programmableHandle, &programmableProperties);

        // Choose programmable handle of interest
        if(strcmp(programmableProperties.name, "EU_ACTIVE" ) == 0){

            // Get Parameter descriptions
            ${t}_metric_programmable_param_exp_desc_t * paramDescription = allocate (sizeof(${t}_metric_programmable_param_exp_desc_t) * programmableProperties.parameterCount);
            ${t}MetricProgrammableGetParamDescriptionExp(programmableHandle, programmableProperties.parameterCount, paramDescription);

            // Get Parameter Value descriptions for the 0th parameter
            ${t}_metric_programmable_param_value_exp_desc_t * valueDesc = allocate(sizeof(${t}_metric_programmable_param_value_exp_desc_t) * paramDescription[0].valueDescriptionCount);
            ${t}MetricProgrammableGetParamValueDescriptionExp(programmableHandle, 0, paramDescription[0].valueDescriptionCount, valueDesc);

            // Setting value for the 0th parameter
            ${t}_metric_programmable_param_value_exp_t parameterValue;
            parameterValue.value = valueDesc[0].valueDesc.ui64;

            // Create Metric
            ${t}_metric_handle_t metricHandle{};
            char metricName[ZET_MAX_METRIC_NAME] = "eu_active_minimum";
            char metricDescription[ZET_MAX_METRIC_DESCRIPTION] = "eu_active_minimum_desc";
            ${t}MetricCreateFromProgrammableExp(programmableHandle, &parameterValue, 1, metricName, metricDescription, &metricHandleCount, null_ptr);
            metricHandles = allocate(sizeof(${t}_metric_handle_t) * metricHandleCount);
            ${t}MetricCreateFromProgrammableExp(programmableHandle, &parameterValue, 1, metricName, metricDescription, &metricHandleCount, metricHandles);
        }

        //Create Metric Group from metrics
        uint32_t handlesSize = metricHandlesUsed.size();
        char metricGroupName[ZET_MAX_METRIC_GROUP_NAME] = "eu_active";
        char metricGroupDescription[ZET_MAX_METRIC_GROUP_DESCRIPTION] = "eu_active_desc";
        ${t}MetricGroupCreateExp(device, metricGroupName, metricGroupDescription, &metricGroup);
        ${t}MetricGroupAddMetricExp(metricGroup, &metricHandlesUsed[0], null_ptr, null_ptr);
    }

    //Activate Metric group
    //Collect Metric group using available sampling types

    //Cleanup
    ${t}MetricGroupDestroyExp(metricGroup);

    for(uint32_t j = 0; j < metricHandleCount; j++){
        ${t}MetricDestroyExp(metricHandles[j]);
    }


