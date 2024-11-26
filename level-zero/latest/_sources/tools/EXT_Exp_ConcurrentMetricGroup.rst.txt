
:orphan:

.. _ZET_experimental_concurrent_metric_groups:

==========================================
Concurrent Metric Groups Experimental Extension
==========================================

API
----

* Functions

    * :ref:`zetDeviceGetConcurrentMetricGroupsExp`

Concurrent Metric Groups
~~~~~~~~~~~~~~~~~~~~~~~~

Metric groups enumerated or created cannot be collected or activated concurrently if the metric groups use shared HW resources.
Currently Metric "Domains" are used to determine if a metric group can be collected along with another metric group.
Since Metric "Domains" are at a metric group level, it cannot represent metric level HW dependencies.
This API replaces using "domain" property of metric group to determine independent HW usage and provides sets of metric groups which could be collected concurrently.
:ref:`zetDeviceGetConcurrentMetricGroupsExp` allows an input list of metric groups to be re-arranged to sequential sets of metric groups which could be collected concurrently.
This API also allows the application to calculate the number of replays or workload executions necessary to collect a set of overlapping metric groups.


Sample Code
------------

The following pseudo-code shows how an application could query for sets of concurrent metric groups within a list of metric groups

.. parsed-literal::

    // Input metric group count;
    uint32_t inputMetricGroupCount;

    // Input and output list of metric groups
    zet_metric_group_handle_t * phMetricGroups;

    // Output concurrent group information
    uint32_t concurrentGroupCount = 0;

    // Get number of concurrent groups / number of replays necessary
    :ref:`zetDeviceGetConcurrentMetricGroupsExp`\(hDevice, inputMetricGroupCount, phMetricGroups, &concurrentGroupCount, nullptr);

    // Allocate for count per concurrent group
    uint32_t * pCountPerConcurrentGroup = malloc(sizeof(uint32_t) * concurrentGroupCount);

    // Retrieve the rearranged metric groups along with the count per concurrent group
    :ref:`zetDeviceGetConcurrentMetricGroupsExp`\(hDevice, inputMetricGroupCount, phMetricGroups, &concurrentGroupCount, pCountPerConcurrentGroup);

    // Activate the concurrent groups and Replay the workload
    for(uint32_t concurrentGroupIndex = 0; concurrentGroupIndex < concurrentGroupCount; concurrentGroupIndex ++){
        :ref:`zetContextActivateMetricGroups`\(hContext, hDevice, pCountPerConcurrentGroup[concurrentGroupIndex], phMetricGroups);

        // run workload

        phMetricGroups += pCountPerConcurrentGroup[concurrentGroupIndex];
    }