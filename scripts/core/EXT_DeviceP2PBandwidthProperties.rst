<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_device_p2p_bandwidth_properties:

==========================================
Device P2P Bandwidth Extension Properties
==========================================

API
----

* Structures


    * ${x}_device_p2p_bandwidth_ext_properties_t

Device P2P Bandwidth Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Engines from different command queue groups may drive differing amounts of bandwidth over the same link between two devices. The copy bandwidth of the engines within each command queue group is provided to help users determine which command queue group to pick an engine from for driving each copy operation given constraints such as the maximum bandwidth that a link supports, current usage of engines, etc... For example, some command queue groups that support copy may afford engines that support a higher copy bandwidth as compared to those from a different command queue group. For driving copies from local memory to local memory, it may be advisable to use an engine from a higher copy bandwidth group. For performing copies between devices interconnected with a lower bandwidth link, it may suffice to use an engine from a lower copy bandwidth group.

The following psuedo-code demonstrates a sequence for obtaining the p2p bandwidth between two devices:

.. parsed-literal::

    // devCount is the count of the number of devices in the system
    uint32_t **bwTable
    uint32_t **latTable

    bwTable = (uint32_t **)allocate(devCount*sizeof(uint32_t *));
    latTable = (uint32_t **)allocate(devCount*sizeof(uint32_t *));

    ${x}_device_p2p_properties_t P2PProps;
    ${x}_device_p2p_bandwidth_ext_properties_t P2PBandwidthProps;
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
