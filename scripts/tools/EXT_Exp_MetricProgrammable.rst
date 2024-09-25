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

.. _ZET_experimental_programmable_metrics:

==========================================
Metric Programmable Experimental Extension
==========================================

API
----
* Enumerations

    * ${t}_metric_programmable_param_type_exp_t
    * ${t}_value_info_type_exp_t
    * ${t}_metric_programmable_exp_version_t

* Structures

    * ${t}_metric_programmable_exp_properties_t
    * ${t}_metric_programmable_param_info_exp_t
    * ${t}_metric_programmable_param_value_exp_t
    * ${t}_metric_programmable_param_value_info_exp_t
    * ${t}_value_info_exp_t
    * ${t}_value_uint64_range_exp_t

* Functions

    * ${t}MetricProgrammableGetExp
    * ${t}MetricProgrammableGetPropertiesExp
    * ${t}MetricProgrammableGetParamInfoExp
    * ${t}MetricProgrammableGetParamValueInfoExp
    * ${t}MetricCreateFromProgrammable1Exp
    * ${t}DeviceCreateMetricGroupsFromMetricsExp
    * ${t}MetricGroupAddMetricExp
    * ${t}MetricGroupRemoveMetricExp
    * ${t}MetricGroupCloseExp
    * ${t}MetricDestroyExp
    * ${t}MetricGroupDestroyExp

Metric Programmable
~~~~~~~~~~~~~~~~~~~

Application can use ${t}MetricGroupGet to enumerate the list of metric groups and ${t}MetricGet for the metrics available for collection.
However Applications may also want to collect custom metrics which are not listed as part of the enumeration.
This is made possible by making a list of programmable metrics available to the application, so that it may choose different parameter values for preparing custom metrics.

Sample Code
------------

The following pseudo-code demonstrates how programmable metrics could be enumerated and custom values could be set to the metric parameters.

.. parsed-literal::

    ${t}_metric_handle_t * metricHandles = null_ptr;
    uint32_t metricHandleCount = 0;

    // Query and Get metric programmable handles
    uint32_t programmableCount = 0;
    ${t}MetricProgrammableGetExp(device, &programmableCount, nullptr);
    ${t}_metric_programmable_exp_handle_t * metricProgrammableHandles = allocate(sizeof(${t}_metric_programmable_exp_handle_t) * programmableCount);
    ${t}MetricProgrammableGetExp(device, &programmableCount, metricProgrammableHandles);

    // Create metrics from metric programmable handles
    for(uint32_t i = 0; i < programmableCount; i++){

        ${t}_metric_programmable_exp_handle_t programmableHandle = metricProgrammableHandles[i];
        ${t}_metric_programmable_exp_properties_t programmableProperties{};
        ${t}MetricProgrammableGetPropertiesExp(programmableHandle, &programmableProperties);

        // Choose programmable handle of interest
        if(strcmp(programmableProperties.name, "EU_ACTIVE" ) == 0){

            // Get Parameter info
            ${t}_metric_programmable_param_info_exp_t * paramInfo = allocate (sizeof(${t}_metric_programmable_param_info_exp_t) * programmableProperties.parameterCount);
            ${t}MetricProgrammableGetParamInfoExp(programmableHandle, programmableProperties.parameterCount, paramInfo);

            // Get Parameter Value info for the 0th parameter
            ${t}_metric_programmable_param_value_info_exp_t * paramValueInfo = allocate(sizeof(${t}_metric_programmable_param_value_info_exp_t) * paramInfo[0].valueInfoCount);
            ${t}MetricProgrammableGetParamValueInfoExp(programmableHandle, 0, paramInfo[0].valueInfoCount, paramValueInfo);

            // Setting value for the 0th parameter
            ${t}_metric_programmable_param_value_exp_t parameterValue;
            parameterValue.value = paramValueInfo[0].valueInfo.ui64;

            // Create Metric
            char metricName[ZET_MAX_METRIC_NAME] = "eu_active_minimum";
            char metricDescription[ZET_MAX_METRIC_DESCRIPTION] = "eu_active_minimum_desc";
            ${t}MetricCreateFromProgrammable1Exp(programmableHandle, &parameterValue, 1, metricName, metricDescription, &metricHandleCount, nullptr);
            ${t}_metric_handle_t * metricHandles = allocate(sizeof(${t}_metric_handle_t) * metricHandleCount);
            ${t}MetricCreateFromProgrammable1Exp(programmableHandle, &parameterValue, 1, metricName, metricDescription, &metricHandleCount, metricHandles);
        }
    }

    //Create Metric Group from metrics
    char metricGroupNamePrefix[ZET_MAX_METRIC_GROUP_NAME_PREFIX_EXP] = "eu_active";
    char metricGroupDescription[ZET_MAX_METRIC_GROUP_DESCRIPTION] = "eu_active_desc";
    uint32_t metricGroupCount = 0;
    ${t}DeviceCreateMetricGroupsFromMetricsExp(device, 1, &metricHandles[0], metricGroupNamePrefix, metricGroupDescription, &metricGroupCount, nullptr);
    ${t}_metric_group_handle_t * metricGroupHandles = allocate(sizeof(${t}_metric_group_handle_t) * metricGroupCount);
    ${t}DeviceCreateMetricGroupsFromMetricsExp(device, 1, &metricHandles[0], metricGroupNamePrefix, metricGroupDescription, &metricGroupCount, metricGroupHandles);
    ${t}MetricGroupAddMetricExp(metricGroupHandles[0], &metricHandles[1], nullptr, nullptr);
    ${t}MetricGroupCloseExp(metricGroupHandles[0]);

    //Activate Metric group
    //Collect Metric group using available sampling types

    //Cleanup
    ${t}MetricGroupDestroyExp(metricGroup);

    for(uint32_t j = 0; j < metricHandleCount; j++){
        ${t}MetricDestroyExp(metricHandles[j]);
    }


