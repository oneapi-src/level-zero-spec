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

* Enumerations


    * ${x}_event_query_kernel_timestamps_ext_version_t
    * ${x}_event_query_kernel_timestamps_ext_flags_t


* Structures


    * ${x}_event_query_kernel_timestamps_ext_properties_t
    * ${x}_event_query_kernel_timestamps_data_ext_properties_t


* Functions


    * ${x}EventQueryKernelTimestampsExt


Event Query Kernel Timestamps
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This extension enables the querying of synchronized event timestamps.

- *Synchronized event timestamps* are device timestamps synchronized to the host time domain.

**Notes**

- The querying of synchronized event timestamps has a performance cost.
- This extension is designed to complement and eventually replace all usages of ${x}EventQueryTimestampsExp and ${x}EventQueryKernelTimestamp.
- The value returned by the `pCount` parameter of ${x}EventQueryKernelTimestampsExt is implementation specific.

.. parsed-literal::

    ${x}_device_properties_t devProps;
    ${x}_event_query_kernel_timestamps_ext_properties_t tsProps;

    devProps.stype = ${X}_STRUCTURE_TYPE_DEVICE_MODULE_PROPERTIES;
    devProps.pNext = &tsProps;

    tsProps.stype = ${X}_STRUCTURE_TYPE_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_PROPERTIES;
    tsProps.pNext = nullptr;

    // Determine the level of support by getting the module properties
    ${x}DeviceGetProperties(hDevice, &devProps);

    const bool supportsRaw = (0 != (tsProps.flags & ${X}_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_FLAG_RAW));
    const bool supportsSynchronized = (0 != (tsProps.flags & ${X}_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_FLAG_HOST_SYNCHRONIZED));

    // Assumption: hEvent was created with ${X}_EVENT_POOL_FLAG_KERNEL_MAPPED_TIMESTAMP

    // ...
    // launch kernel
    // synchronize host
    // ...

    if (supportsRaw && supportsSynchronized) {
        // Number of event timestamps
        uint32_t count = 0;

        // Get the number of timestamps associated with the event.
        ${x}EventQueryKernelTimestampsExt(hEvent, hDevice, &count, nullptr);

        // Allocate storage for raw device timestamps
        std::vector<${x}_kernel_timestamp_result_t> rawTimestamps(count);

        // Allocate storage for synchronized event timestamps, in nanoseconds
        std::vector<uint64_t> synchronizedTimestamps(count);

        // Build event query kernel timestamps descriptors
        ${x}_event_query_kernel_timestamps_data_ext_properties_t dataProps;

        dataProps.stype = ${X}_STRUCTURE_TYPE_EVENT_QUERY_KERNEL_TIMESTAMPS_DATA_EXT_PROPERTIES;
        dataProps.pNext = nullptr;
        dataProps.pRawTimestampsBuffer = rawTimestamps.data();
        dataProps.pSynchronizedTimestampsBuffer = synchronizedTimestamps.data();

        // Query the event timestamps
        ${x}EventQueryKernelTimestampsExt(hEvent, hDevice, &count, &dataProps);
    }
