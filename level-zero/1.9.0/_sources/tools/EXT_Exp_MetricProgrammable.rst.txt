
:orphan:

.. _ZET_experimental_programmable_metrics:

==========================================
Metric Programmable Experimental Extension
==========================================

API
----
* Enumerations

    * :ref:`zet-metric-programmable-param-type-exp-t`
    * :ref:`zet-value-info-type-exp-t`
    * :ref:`zet-metric-programmable-exp-version-t`

* Structures

    * :ref:`zet-metric-programmable-exp-properties-t`
    * :ref:`zet-metric-programmable-param-info-exp-t`
    * :ref:`zet-metric-programmable-param-value-exp-t`
    * :ref:`zet-metric-programmable-param-value-info-exp-t`
    * :ref:`zet-value-info-exp-t`
    * :ref:`zet-value-uint64-range-exp-t`

* Functions

    * :ref:`zetMetricProgrammableGetExp`
    * :ref:`zetMetricProgrammableGetPropertiesExp`
    * :ref:`zetMetricProgrammableGetParamInfoExp`
    * :ref:`zetMetricProgrammableGetParamValueInfoExp`
    * :ref:`zetMetricCreateFromProgrammableExp`
    * :ref:`zetMetricGroupCreateExp`
    * :ref:`zetMetricGroupAddMetricExp`
    * :ref:`zetMetricGroupRemoveMetricExp`
    * :ref:`zetMetricGroupCloseExp`
    * :ref:`zetMetricDestroyExp`
    * :ref:`zetMetricGroupDestroyExp`

Metric Programmable
~~~~~~~~~~~~~~~~~~~

Application can use :ref:`zetMetricGroupGet` to enumerate the list of metric groups and :ref:`zetMetricGet` for the metrics available for collection.
However Applications may also want to collect custom metrics which are not listed as part of the enumeration.
This is made possible by making a list of programmable metrics available to the application, so that it may choose different parameter values for preparing custom metrics.

Sample Code
------------

The following pseudo-code demonstrates how programmable metrics could be enumerated and custom values could be set to the metric parameters.

.. parsed-literal::

    zet_metric_handle_t * metricHandles = null_ptr;
    uint32_t metricHandleCount = 0;
    zet_metric_group_handle_t metricGroup;

    // Query and Get metric programmable handles
    uint32_t programmableCount = 0;
    :ref:`zetMetricProgrammableGetExp`\(device, &programmableCount, nullptr);
    zet_metric_programmable_exp_handle_t * metricProgrammableHandles = allocate(sizeof(zet_metric_programmable_exp_handle_t) * programmableCount);
    :ref:`zetMetricProgrammableGetExp`\(device, &programmableCount, metricProgrammableHandles);

    // Create metrics from metric programmable handles
    for(uint32_t i = 0; i < programmableCount; i++){

        zet_metric_programmable_exp_handle_t programmableHandle = metricProgrammableHandles[i];
        :ref:`zet-metric-programmable-exp-properties-t` programmableProperties{};
        :ref:`zetMetricProgrammableGetPropertiesExp`\(programmableHandle, &programmableProperties);

        // Choose programmable handle of interest
        if(strcmp(programmableProperties.name, "EU_ACTIVE" ) == 0){

            // Get Parameter info
            :ref:`zet-metric-programmable-param-info-exp-t` * paramInfo = allocate (sizeof(:ref:`zet-metric-programmable-param-info-exp-t`\) * programmableProperties.parameterCount);
            :ref:`zetMetricProgrammableGetParamInfoExp`\(programmableHandle, programmableProperties.parameterCount, paramInfo);

            // Get Parameter Value info for the 0th parameter
            :ref:`zet-metric-programmable-param-value-info-exp-t` * paramValueInfo = allocate(sizeof(:ref:`zet-metric-programmable-param-value-info-exp-t`\) * paramInfo[0].valueInfoCount);
            :ref:`zetMetricProgrammableGetParamValueInfoExp`\(programmableHandle, 0, paramInfo[0].valueInfoCount, paramValueInfo);

            // Setting value for the 0th parameter
            :ref:`zet-metric-programmable-param-value-exp-t` parameterValue;
            parameterValue.value = paramValueInfo[0].valueInfo.ui64;

            // Create Metric
            char metricName[ZET_MAX_METRIC_NAME] = "eu_active_minimum";
            char metricDescription[ZET_MAX_METRIC_DESCRIPTION] = "eu_active_minimum_desc";
            :ref:`zetMetricCreateFromProgrammableExp`\(programmableHandle, &parameterValue, 1, metricName, metricDescription, &metricHandleCount, null_ptr);
            zet_metric_handle_t * metricHandles = allocate(sizeof(zet_metric_handle_t) * metricHandleCount);
            :ref:`zetMetricCreateFromProgrammableExp`\(programmableHandle, &parameterValue, 1, metricName, metricDescription, &metricHandleCount, metricHandles);
        }
    }

    //Create Metric Group from metrics
    zet_metric_group_handle_t metricGroupHandle{};
    char metricGroupName[ZET_MAX_METRIC_GROUP_NAME] = "eu_active";
    char metricGroupDescription[ZET_MAX_METRIC_GROUP_DESCRIPTION] = "eu_active_desc";
    :ref:`zetMetricGroupCreateExp`\(device, metricGroupName, metricGroupDescription, ZET_METRIC_GROUP_SAMPLING_TYPE_FLAG_TIME_BASED, &metricGroup);
    :ref:`zetMetricGroupAddMetricExp`\(metricGroup, &metricHandles[0], null_ptr, null_ptr);
    :ref:`zetMetricGroupCloseExp`\(metricGroup);

    //Activate Metric group
    //Collect Metric group using available sampling types

    //Cleanup
    :ref:`zetMetricGroupDestroyExp`\(metricGroup);

    for(uint32_t j = 0; j < metricHandleCount; j++){
        :ref:`zetMetricDestroyExp`\(metricHandles[j]);
    }


