
:orphan:

.. _ZE_extension_event_query_kernel_timestamps:

=========================================
 Event Query Kernel Timestamps Extension
=========================================

API
----

* Enumerations


    * :ref:`ze-event-query-kernel-timestamps-ext-version-t`
    * :ref:`ze-event-query-kernel-timestamps-ext-flags-t`


* Structures


    * :ref:`ze-event-query-kernel-timestamps-ext-properties-t`
    * :ref:`ze-event-query-kernel-timestamps-results-ext-properties-t`
    * :ref:`ze-synchronized-timestamp-data-ext-t`
    * :ref:`ze-synchronized-timestamp-result-ext-t`


* Functions


    * :ref:`zeEventQueryKernelTimestampsExt`


Event Query Kernel Timestamps
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This extension enables the querying of synchronized event timestamps.

- *Synchronized event timestamps* are device timestamps synchronized to the host time domain.

**Notes**

- The querying of synchronized event timestamps has a performance cost.
- This extension is designed to complement and eventually replace all usages of :ref:`zeEventQueryTimestampsExp` and :ref:`zeEventQueryKernelTimestamp`\.
- The value returned by the `pCount` parameter of :ref:`zeEventQueryKernelTimestampsExt` is implementation specific.

.. parsed-literal::

    :ref:`ze-device-properties-t` devProps;
    :ref:`ze-event-query-kernel-timestamps-ext-properties-t` tsProps;

    devProps.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>`\;
    devProps.pNext = &tsProps;

    tsProps.stype = :ref:`ZE_STRUCTURE_TYPE_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_PROPERTIES <ze-structure-type-t>`\;
    tsProps.pNext = nullptr;

    // Determine the level of support by getting the module properties
    :ref:`zeDeviceGetProperties`\(hDevice, &devProps);

    const bool supportsKernelTimestamps = (0 != (tsProps.flags & :ref:`ZE_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_FLAG_KERNEL <ze-event-query-kernel-timestamps-ext-flags-t>`\));
    const bool supportsSynchronizedTimestamps = (0 != (tsProps.flags & :ref:`ZE_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_FLAG_SYNCHRONIZED <ze-event-query-kernel-timestamps-ext-flags-t>`\));

    // Assumption: hEvent was created with :ref:`ZE_EVENT_POOL_FLAG_KERNEL_MAPPED_TIMESTAMP <ze-event-pool-flags-t>`

    // ...
    // launch kernel
    // synchronize host
    // ...

    if (supportsKernelTimestamps || supportsSynchronizedTimestamps) {
        // Number of event timestamps
        uint32_t count = 0;

        // Get the number of timestamps associated with the event.
        :ref:`zeEventQueryKernelTimestampsExt`\(hEvent, hDevice, &count, nullptr);

        // Allocate storage for kernel timestamp results
        std::vector<:ref:`ze-kernel-timestamp-result-t`\> kernelTimestamps(count);

        // Allocate storage for synchronized timestamp results
        std::vector<:ref:`ze-synchronized-timestamp-result-ext-t`\> synchronizedTimestamps(count);

        // Build event query kernel timestamps descriptors
        :ref:`ze-event-query-kernel-timestamps-results-ext-properties-t` resultsProps;

        resultsProps.stype = :ref:`ZE_STRUCTURE_TYPE_EVENT_QUERY_KERNEL_TIMESTAMPS_RESULTS_EXT_PROPERTIES <ze-structure-type-t>`\;
        resultsProps.pNext = nullptr;
        resultsProps.pKernelTimestampsBuffer = supportsKernelTimestamps ? kernelTimestamps.data() : nullptr;
        resultsProps.pSynchronizedTimestampsBuffer = supportsSynchronizedTimestamps ? synchronizedTimestamps.data() : nullptr;

        // Query the event timestamps
        :ref:`zeEventQueryKernelTimestampsExt`\(hEvent, hDevice, &count, &resultsProps);
    }
