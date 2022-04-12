<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_device_p2p_bandwidth_properties:

============================================
Device P2P Bandwidth Extension Properties
============================================

API
----

* Structures

    * ${x}_device_p2p_bandwidth_exp_properties_t

Device P2P Bandwidth Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Devices and subdevices within a system may be connected using different link technologies as well as differing numbers of links. Two devices (or subdevices) may be logically but not physically connected to each other, meaning that memory accesses and copies between the devices have to go over intervening devices which limits the maximum bandwidth to the lowest bandwidth link along the connection while increasing the latency to the sum total of the latencies of the links along the connection. The net bandwidth & latency for two logically connected devices accounts for link technology, number of links, number of hops between the devices, etc... The net bandwidth & latency for two physically connected devices are zero unless the devices are directly connected to each other by a fabric, and accounts for link technology, number of links, etc...

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
