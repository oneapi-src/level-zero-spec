
:orphan:

.. _ZE_extension_record_replay_graph:

===================================
 Record and Replay Graph Extension
===================================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.17*

API
----

* Functions


    * :ref:`zeGraphCreateExt`
    * :ref:`zeCommandListBeginGraphCaptureExt`
    * :ref:`zeCommandListBeginCaptureIntoGraphExt`
    * :ref:`zeCommandListIsGraphCaptureEnabledExt`
    * :ref:`zeCommandListEndGraphCaptureExt`
    * :ref:`zeCommandListGetGraphExt`
    * :ref:`zeGraphGetPrimaryCommandListExt`
    * :ref:`zeGraphSetDestructionCallbackExt`
    * :ref:`zeGraphInstantiateExt`
    * :ref:`zeCommandListAppendGraphExt`
    * :ref:`zeExecutableGraphGetSourceGraphExt`
    * :ref:`zeGraphIsEmptyExt`
    * :ref:`zeGraphDumpContentsExt`
    * :ref:`zeExecutableGraphDestroyExt`
    * :ref:`zeGraphDestroyExt`
    * :ref:`zeGraphPauseCaptureExt`
    * :ref:`zeGraphResumeCaptureExt`
    * :ref:`zeGraphGetIdExt`

* Enumerations


    * :ref:`ze-record-replay-graph-ext-version-t`
    * :ref:`ze-record-replay-graph-ext-flags-t`
    * :ref:`ze-record-replay-graph-ext-dump-mode-t`
    * :ref:`ze-event-ext-flags-t`


* Structures


    * :ref:`ze-record-replay-graph-ext-properties-t`
    * :ref:`ze-record-replay-graph-ext-dump-desc-t`
    * :ref:`ze-event-ext-flags-desc-t`

Record and Replay Graph
~~~~~~~~~~~~~~~~~~~~~~~

This extension allows applications to capture append operations from immediate command lists into a graph, instantiate that graph, and replay it efficiently.

Applications can query support and capabilities using :ref:`ze-record-replay-graph-ext-properties-t` and :ref:`ze-record-replay-graph-ext-flags-t`\. Captured graphs can be inspected with :ref:`zeGraphDumpContentsExt`\, and :ref:`ze-record-replay-graph-ext-dump-desc-t` controls dump behavior.

Querying the driver and the device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Query the driver to determine if the Record and Replay extension is available.
2. Query the device to determine which graph capabilities are available.
3. Immutable graph support is the minimum required for a functional record and replay graph.

.. parsed-literal::

    ze_driver_handle_t hDriver; // initialized driver
    ze_device_handle_t hDevice; // created device out of the driver

    // query extension count
    uint32_t extensionsCount = 0;
    :ref:`zeDriverGetExtensionProperties`\(hDriver, &extensionsCount, nullptr);

    :ref:`ze-driver-extension-properties-t` \*driverExtensions; // allocate memory under this pointer to fit extensionsCount elements
    :ref:`zeDriverGetExtensionProperties`\(hDriver, &extensionsCount, driverExtensions);

    // discover graph extension
    const char \*extensionName = "ZE_extension_record_replay_graph";
    size_t extensionNameLength = strlen(extensionName);

    for (uint32_t i = 0; i < extensionsCount; i++) {
        if (strncmp(driverExtensions[i].name, extensionName, extensionNameLength) == 0) {
            printf("Extension %s found at version %u.%u\n",
                   extensionName,
                   ZE_MAJOR_VERSION(driverExtensions[i].version),
                   ZE_MINOR_VERSION(driverExtensions[i].version));
        }
    }

    :ref:`ze-record-replay-graph-ext-properties-t` graphProperties = {
        :ref:`ZE_STRUCTURE_TYPE_RECORD_REPLAY_GRAPH_EXT_PROPERTIES <ze-structure-type-t>`
    };

    :ref:`ze-device-properties-t` deviceProps = {
        :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES_1_2 <ze-structure-type-t>`   // :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>` deprecated since 1.17
    };
    deviceProps.pNext = &graphProperties;

    :ref:`zeDeviceGetProperties`\(hDevice, &deviceProps);
    if (!(graphProperties.graphFlags & :ref:`ZE_RECORD_REPLAY_GRAPH_EXT_FLAG_IMMUTABLE_GRAPH <ze-record-replay-graph-ext-flags-t>`\)) {
        printf("Basic graph functionality for this device is not available\n");
    }

Typical Flow
~~~~~~~~~~~~

1. Create a graph with :ref:`zeGraphCreateExt`\, or begin capture directly on an immediate command list with :ref:`zeCommandListBeginGraphCaptureExt`\.
2. Record append operations and optionally query capture state via :ref:`zeCommandListIsGraphCaptureEnabledExt` and :ref:`zeCommandListGetGraphExt`\.
3. End capture using :ref:`zeCommandListEndGraphCaptureExt`\.
4. Instantiate an executable graph with :ref:`zeGraphInstantiateExt`\.
5. Submit the executable graph using :ref:`zeCommandListAppendGraphExt`\.
6. Optionally dump graph contents with :ref:`zeGraphDumpContentsExt`\.
7. Destroy executable and recorded graph objects using :ref:`zeExecutableGraphDestroyExt` and :ref:`zeGraphDestroyExt`\.

External Events
~~~~~~~~~~~~~~~

1. Counter based events created with :ref:`ZE_EVENT_COUNTER_BASED_FLAG_GRAPH_EXTERNAL <ze-event-counter-based-flags-t>` can be used for synchronization outside of a graph, both on the device and on the host.
2. Counter based events created without this flag can also act as GRAPH_EXTERNAL events when used while recording a graph with 
    :ref:`zeCommandListAppendWaitOnEventsWithParameters` or :ref:`zeCommandListAppendSignalEventWithParameters` and an event flags descriptor specifying :ref:`ZE_EVENT_EXT_FLAG_APPEND_GRAPH_EXTERNAL <ze-event-ext-flags-t>`\.
3. The flag affects only the wait or signal operation for which it is specified and does not modify the event object itself.
4. The state of an external wait event is refreshed when :ref:`zeCommandListAppendGraphExt` is called.
    Therefore, if the event was signaled from an immediate command list or from a different graph, the current wait state is propagated to the graph before graph execution.
5. The state of an external signal event is reattached to the current graph when :ref:`zeCommandListAppendGraphExt` is called.
    Therefore, if the event was previously used by a different graph or an immediate command list, it becomes associated with the current graph and subsequent event state updates are driven by the current graph execution.
    As a result, :ref:`zeEventQueryStatus` may return :ref:`ZE_RESULT_NOT_READY <ze-result-t>`\.

.. parsed-literal::

    ze_command_list_handle_t hCommandList; // immediate command list in record mode for the root branch
    ze_command_list_handle_t hChildCommandList; // immediate command list used for the fork branch
    ze_event_handle_t hEvent; // counter based event not created with :ref:`ZE_EVENT_COUNTER_BASED_FLAG_GRAPH_EXTERNAL <ze-event-counter-based-flags-t>`

    :ref:`ze-event-ext-flags-desc-t` graphExternalDesc = {
        :ref:`ZE_STRUCTURE_TYPE_EVENT_EXT_FLAGS_DESC <ze-structure-type-t>`\,      // stype
        nullptr,                                       // pNext
        :ref:`ZE_EVENT_EXT_FLAG_APPEND_GRAPH_EXTERNAL <ze-event-ext-flags-t>`      // flags
    };

    // now the event acts as an external wait event, can receive the signals from outside the graph (for example from another graph, an immediate command list or a mutable command list)
    :ref:`zeCommandListAppendWaitOnEventsWithParameters`\(hCommandList, &graphExternalDesc, 1, &hEvent);

    // now the event acts as an internal signal event to pass a signal within the graph to the fork branch
    :ref:`zeCommandListAppendSignalEvent`\(hCommandList, hEvent);

    // now the event acts as an internal wait event used to receive the signal from the root branch
    :ref:`zeCommandListAppendWaitOnEvents`\(hChildCommandList, 1, &hEvent);

    // some work inside the fork branch
    /// ...

    // now the event acts as an internal signal event to pass a signal from the fork branch back to the root branch
    :ref:`zeCommandListAppendSignalEvent`\(hChildCommandList, hEvent);

    // now the event acts as an internal wait event used to receive the signal from the fork branch
    :ref:`zeCommandListAppendWaitOnEvents`\(hCommandList, 1, &hEvent);

    // some work inside the root branch
    // ...

    // now the event acts as an external signal event; the event can be used outside the graph for host or device synchronization
    :ref:`zeCommandListAppendSignalEventWithParameters`\(hCommandList, &graphExternalDesc, hEvent);
