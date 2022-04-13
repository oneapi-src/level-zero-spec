<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_bandwidth_properties:

=================================
Bandwidth Extension Properties
=================================

API
----

* Structures


    * ${x}_device_p2p_bandwidth_exp_properties_t

    * ${x}_copy_bandwidth_exp_properties_t


Bandwidth Properties
~~~~~~~~~~~~~~~~~~~~~

Properties of interest during data movement and remote access across various accelerators interconnected via a set of fabrics include the bandwidths and latencies provided by the fabrics (logical as well as physical) but also the bandwidths that can be driven by the various engines present in the accelerators, i.e. the copy bandwidth. In order to saturate the interconnecting fabrics, the copy bandwidth used to drive a transfer must be matched to the bandwidth provided by the fabric. This may be achieved by utilizing one or more engines to drive the transfer. The extensions provided here allow users to query both the fabric bandwidth & latencies as well the copy bandwidth provided by the various engines present on each accelerator.

Accelerators within a system may be connected using different link technologies as well as differing numbers of links. Two accelerators may be logically but not physically connected to each other, meaning that memory accesses and copies between the accelerators have to go over intervening accelerators. This limits the maximum bandwidth to the lowest bandwidth link along the connection while increasing the latency to the sum total of the latencies of the links along the connection. The net bandwidth & latency for two logically connected accelerators accounts for link technology, number of links, number of hops between the accelerators, etc... The net physical bandwidth & physical latency between two accelerators are zero unless the accelerators are directly connected to each other by a fabric, and account for link technology, number of links, etc...

The following pseudo-code demonstrates a sequence for obtaining the p2p bandwidth & latency between two devices:

.. parsed-literal::

    // devCount is the count of the number of devices in the system
    uint32_t **bwTable
    uint32_t **latTable

    bwTable = (uint32_t **)allocate(devCount*sizeof(uint32_t *));
    latTable = (uint32_t **)allocate(devCount*sizeof(uint32_t *));

    ${x}_device_p2p_properties_t P2PProps;
    ${x}_device_p2p_bandwidth_exp_properties_t P2PBandwidthProps;
    P2Props.pNext = &P2PbandwidthProps;

    // Assume devices are stored in array called devices
    for (uint32_t dev = 0; dev < devCount; ++dev) {
        bwTable[dev] = (uint32_t *)allocate(devCount*sizeof(uint32_t));
        latTable[dev] = (uint32_t *)allocate(devCount*sizeof(uint32_t));
        for (uint32_t peer_dev = 0; peer_dev < devCount; ++peer_dev) {
            zeDeviceGetP2PProperties(devices[dev], devices[peer_dev], &P2PProps);
            bwTable[dev][peer_dev] = P2PProps.pNext->bandwith;
            latTable[dev][peer_dev] = P2PProps.pNext->latency;
        }
    }


Engines from different command queue groups may drive differing amounts of bandwidth over the same link between two accelerators. The copy bandwidth of the engines within each command queue group is provided to help users determine which command queue group to pick the right types and numbers of engines from the accelerator for driving each copy operation given constraints such as the maximum bandwidth that a link supports, current usage of engines, etc... For example, some command queue groups that support copy may afford engines that support a higher copy bandwidth as compared to those from a different command queue group. For driving copies from local memory to local memory, it may be advisable to use an engine from a higher copy bandwidth group. For performing copies between devices interconnected with a lower bandwidth link, it may suffice to use an engine from a lower copy bandwidth group.

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
