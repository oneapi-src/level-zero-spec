<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_copy_bandwidth_properties:

======================================
Copy Bandwidth Extension Properties
======================================

API
----

* Structures


    * ${x}_copy_bandwidth_exp_properties_t

Copy Bandwidth Properties
~~~~~~~~~~~~~~~~~~~~~~~~~

Engines from different command queue groups may drive differing amounts of bandwidth over the same link between two devices. The copy bandwidth of the engines within each command queue group is provided to help users determine which command queue group to pick an engine from for driving each copy operation given constraints such as the maximum bandwidth that a link supports, current usage of engines, etc... For example, some command queue groups that support copy may afford engines that support a higher copy bandwidth as compared to those from a different command queue group. For driving copies from local memory to local memory, it may be advisable to use an engine from a higher copy bandwidth group. For performing copies between devices interconnected with a lower bandwidth link, it may suffice to use an engine from a lower copy bandwidth group.

The following pseudo-code demonstrates a sequence for obtaining the copy bandwidth of the engines in each command queue group:

.. parsed-literal::

    // Discover all command queue groups
    uint32_t cmdqueueGroupCount = 0;
    ${x}DeviceGetCommandQueueGroupProperties(hDevice, &cmdqueueGroupCount, nullptr);

    ${x}_command_queue_group_properties_t* cmdqueueGroupProperties = (${x}_command_queue_group_properties_t*)
        allocate(cmdqueueGroupCount * sizeof(${x}_command_queue_group_properties_t));
    ${x}_copy_bandwidth_exp_properties_t* cmdqueueGroupBandwidth = (${x}_copy_bandwidth_exp_properties_t*)
            allocate(cmdqueueGroupCount * sizeof(${x}_copy_bandwidth_exp_properties_t));
    for( uint32_t i = 0; i < cmdqueueGroupCount; ++i ) {
        cmdqueueGroupProperties[i].pNext = &cmdqueueGroupBandwidth[i];
    }
    ${x}DeviceGetCommandQueueGroupProperties(hDevice, &cmdqueueGroupCount, cmdqueueGroupProperties);


    // Find a command queue type that supports copy & print the copy bandwidth
    uint32_t computeQueueGroupOrdinal = cmdqueueGroupCount;
    for( uint32_t i = 0; i < cmdqueueGroupCount; ++i ) {
        if( cmdqueueGroupProperties[ i ].flags & ${X}_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY ) {
            computeQueueGroupOrdinal = i;
            printf("copyBandwidth: %ul\n", cmdqueueGroupBandwidth[i].copyBandwith)
            break;
        }
    }

    if(computeQueueGroupOrdinal == cmdqueueGroupCount)
        return; // no compute queues found
