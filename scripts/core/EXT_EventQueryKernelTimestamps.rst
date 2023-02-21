<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_event_query_kernel_timestamps:

=========================================
 Event Query Kernel Timestamps Extension
=========================================

API
----

* Functions


    * ${x}EventQueryKernelTimestampsExt


* Enumerations


    * ${x}_event_query_kernel_timestamps_ext_version_t


Event Query Kernel Timestamps
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This extension enables the query of event timestamps to provide up to three views of the data, for a given event on a given device:

1. Host timestamps, normalized with Device timestamps
2. Device timestamps, normalized with Host timestamps
3. Raw device timestamps

Each view requires unique backing, provided by the caller.

**Notes**

- There is a slight performance implication to consider when requesting normalized timestamp data as the runtime must perform some calculations on behalf of the caller.
- This extension is designed to compliment and eventually replace all usages of ${x}EventQueryTimestampsExp and ${x}EventQueryKernelTimestamp.

.. parsed-literal::

    // Storage for normalized Host timestamps that correlate with Device timestamps, in nanoseconds
    std::vector<uint64_t> hostTimestamps;

    // Storage for normalized Device timestamps that correlate with Host timestamps, in nanoseconds
    std::vector<uint64_t> deviceTimestamps;

    // Storage for raw device timestamps
    std::vector<${x}_kernel_timestamp_result_t> rawDeviceTimestamps;

    // ...
    // launch kernel
    // synchronize host
    // ...

    // Number of event timestamps
    uint32_t count = 0;

    // Get the number of timestamps associated with the event.
    ${x}EventQueryKernelTimestampsExt(hEvent, hDevice, &count, nullptr, nullptr, nullptr);

    // Allocate storage for timestamp data
    hostTimestamps.resize(count);
    deviceTimestamps.resize(count);
    rawDeviceTimestamps.resize(count);

    // Query the event timestamps
    ${x}EventQueryKernelTimestampsExt(hEvent, hDevice, &count,
        hostTimestamps.data(),          /\* [optional] normalized event host timestamp data that correlates to device timestamps \*/
        deviceTimestamps.data(),        /\* [optional] normalized event device timestamp data that correlates to host timestamps \*/
        rawDeviceTimestamps.data());    /\* [optional] raw event device timestamp data \*/
