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

* Structures


    * ${x}_event_query_kernel_timestamps_ext_properties_t
    * ${x}_event_query_kernel_timestamps_ext_desc_t
    * ${x}_event_query_kernel_timestamps_raw_ext_desc_t
    * ${x}_event_query_kernel_timestamps_synchronized_ext_desc_t


* Functions


    * ${x}EventQueryKernelTimestampsExt


* Enumerations


    * ${x}_event_query_kernel_timestamps_ext_version_t
    * ${x}_event_query_kernel_timestamps_ext_flags_t


Event Query Kernel Timestamps
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This extension enables the querying of synchronized event timestamps.

- *Synchronized event timestamps* are raw Device timestamps synchronized to Host time domain.

**Notes**

- The querying of synchronized event timestamps has a performance cost.
- This extension is designed to complement and eventually replace all usages of ${x}EventQueryTimestampsExp and ${x}EventQueryKernelTimestamp.
- The value returned by the `pCount` parameter of ${x}EventQueryKernelTimestampsExt is implementation specific.

.. parsed-literal::

    ${x}_device_module_properties_t modProps;
    ${x}_event_query_kernel_timestamps_ext_properties_t tsProps;

    modProps.stype = ${X}_STRUCTURE_TYPE_DEVICE_MODULE_PROPERTIES;
    modProps.pNext = &tsProps;

    tsProps.stype = ${X}_STRUCTURE_TYPE_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_PROPERTIES;
    tsProps.pNext = nullptr;

    // Determine the level of support by getting the module properties
    ${x}DeviceGetModuleProperties(hDevice, &modProps);

    const bool supportsRaw = (0 != (tsProps.flags & ${X}_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_FLAG_RAW));
    const bool supportsSynchronized = (0 != (tsProps.flags & ${X}_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_FLAG_HOST_TIME_DOMAIN_SYNCHRONIZED));

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
        std::vector<${x}_kernel_timestamp_result_t> rawDeviceTimestamps(count);

        // Allocate storage for synchronized event timestamps, in nanoseconds
        std::vector<uint64_t> synchronizedEventTimestamps(count);

        // Build event query kernel timestamps descriptors
        ${x}_event_query_kernel_timestamps_ext_desc_t desc;
        ${x}_event_query_kernel_timestamps_raw_ext_desc_t rawDesc;
        ${x}_event_query_kernel_timestamps_synchronized_ext_desc_t syncDesc;

        desc.stype = ${X}_STRUCTURE_TYPE_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_DESC;
        desc.pNext = &rawDesc;
        desc.reserved = 0;

        rawDesc.stype = ${X}_STRUCTURE_TYPE_EVENT_QUERY_KERNEL_TIMESTAMPS_RAW_EXT_DESC;
        rawDesc.pNext = &syncDesc;
        rawDesc.pBuffer = rawDeviceTimestamps.data();

        syncDesc.stype = ${X}_STRUCTURE_TYPE_EVENT_QUERY_KERNEL_TIMESTAMPS_SYNCHRONIZED_EXT_DESC;
        syncDesc.pNext = nullptr;
        syncDesc.pBuffer = synchronizedEventTimestamps.data();

        // Query the event timestamps
        ${x}EventQueryKernelTimestampsExt(hEvent, hDevice, &count, &desc);
    }
