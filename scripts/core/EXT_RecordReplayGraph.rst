<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_record_replay_graph:

===================================
 Record and Replay Graph Extension
===================================

API
----

* Functions


    * ${x}GraphCreateExt
    * ${x}CommandListBeginGraphCaptureExt
    * ${x}CommandListBeginCaptureIntoGraphExt
    * ${x}CommandListIsGraphCaptureEnabledExt
    * ${x}CommandListEndGraphCaptureExt
    * ${x}CommandListGetGraphExt
    * ${x}GraphGetPrimaryCommandListExt
    * ${x}GraphSetDestructionCallbackExt
    * ${x}GraphInstantiateExt
    * ${x}CommandListAppendGraphExt
    * ${x}ExecutableGraphGetSourceGraphExt
    * ${x}GraphIsEmptyExt
    * ${x}GraphDumpContentsExt
    * ${x}ExecutableGraphDestroyExt
    * ${x}GraphDestroyExt
    * ${x}GraphPauseCaptureExt
    * ${x}GraphResumeCaptureExt
    * ${x}GraphGetIdExt

* Enumerations


    * ${x}_record_replay_graph_ext_version_t
    * ${x}_record_replay_graph_ext_flags_t
    * ${x}_record_replay_graph_ext_dump_mode_t
    * ${x}_event_ext_flags_t


* Structures


    * ${x}_record_replay_graph_ext_properties_t
    * ${x}_record_replay_graph_ext_dump_desc_t
    * ${x}_event_ext_flags_desc_t

Record and Replay Graph
~~~~~~~~~~~~~~~~~~~~~~~

This extension allows applications to capture append operations from immediate command lists into a graph, instantiate that graph, and replay it efficiently.

Applications can query support and capabilities using ${x}_record_replay_graph_ext_properties_t and ${x}_record_replay_graph_ext_flags_t. Captured graphs can be inspected with ${x}GraphDumpContentsExt, and ${x}_record_replay_graph_ext_dump_desc_t controls dump behavior.

Querying the driver and the device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Query the driver to determine if the Record and Replay extension is available.
2. Query the device to determine which graph capabilities are available.
3. Immutable graph support is the minimum required for a functional record and replay graph.

.. parsed-literal::

    ${x}_driver_handle_t hDriver; // initialized driver
    ${x}_device_handle_t hDevice; // created device out of the driver

    // query extension count
    uint32_t extensionsCount = 0;
    ${x}DriverGetExtensionProperties(hDriver, &extensionsCount, nullptr);

    ${x}_driver_extension_properties_t \*driverExtensions; // allocate memory under this pointer to fit extensionsCount elements
    ${x}DriverGetExtensionProperties(hDriver, &extensionsCount, driverExtensions);

    // discover graph extension
    const char \*extensionName = "ZE_extension_record_replay_graph";
    size_t extensionNameLength = strlen(extensionName);

    for (uint32_t i = 0; i < extensionsCount; i++) {
        if (strncmp(driverExtensions[i].name, extensionName, extensionNameLength) == 0) {
            printf("Extension %s found at version %u.%u\n",
                   extensionName,
                   ${X}_MAJOR_VERSION(driverExtensions[i].version),
                   ${X}_MINOR_VERSION(driverExtensions[i].version));
        }
    }

    ${x}_record_replay_graph_ext_properties_t graphProperties = {
        ${X}_STRUCTURE_TYPE_RECORD_REPLAY_GRAPH_EXT_PROPERTIES
    };

    ${x}_device_properties_t deviceProps = {
        ${X}_STRUCTURE_TYPE_DEVICE_PROPERTIES_1_2   // ${X}_STRUCTURE_TYPE_DEVICE_PROPERTIES deprecated since 1.17
    };
    deviceProps.pNext = &graphProperties;

    ${x}DeviceGetProperties(hDevice, &deviceProps);
    if (!(graphProperties.graphFlags & ${X}_RECORD_REPLAY_GRAPH_EXT_FLAG_IMMUTABLE_GRAPH)) {
        printf("Basic graph functionality for this device is not available\n");
    }

Typical Flow
~~~~~~~~~~~~

1. Create a graph with ${x}GraphCreateExt, or begin capture directly on an immediate command list with ${x}CommandListBeginGraphCaptureExt.
2. Record append operations and optionally query capture state via ${x}CommandListIsGraphCaptureEnabledExt and ${x}CommandListGetGraphExt.
3. End capture using ${x}CommandListEndGraphCaptureExt.
4. Instantiate an executable graph with ${x}GraphInstantiateExt.
5. Submit the executable graph using ${x}CommandListAppendGraphExt.
6. Optionally dump graph contents with ${x}GraphDumpContentsExt.
7. Destroy executable and recorded graph objects using ${x}ExecutableGraphDestroyExt and ${x}GraphDestroyExt.

External Events
~~~~~~~~~~~~~~~

1. Counter based events created with ${X}_EVENT_COUNTER_BASED_FLAG_GRAPH_EXTERNAL can be used for synchronization outside of a graph, both on the device and on the host.
2. Counter based events created without this flag can also act as GRAPH_EXTERNAL events when used while recording a graph with 
    ${x}CommandListAppendWaitOnEventsWithParameters or ${x}CommandListAppendSignalEventWithParameters and an event flags descriptor specifying ${X}_EVENT_EXT_FLAG_APPEND_GRAPH_EXTERNAL.
3. The flag affects only the wait or signal operation for which it is specified and does not modify the event object itself.
4. The state of an external wait event is refreshed when ${x}CommandListAppendGraphExt is called.
    Therefore, if the event was signaled from an immediate command list or from a different graph, the current wait state is propagated to the graph before graph execution.
5. The state of an external signal event is reattached to the current graph when ${x}CommandListAppendGraphExt is called.
    Therefore, if the event was previously used by a different graph or an immediate command list, it becomes associated with the current graph and subsequent event state updates are driven by the current graph execution.
    As a result, ${x}EventQueryStatus may return ${X}_RESULT_NOT_READY.

.. parsed-literal::

    ${x}_command_list_handle_t hCommandList; // immediate command list in record mode for the root branch
    ${x}_command_list_handle_t hChildCommandList; // immediate command list used for the fork branch
    ${x}_event_handle_t hEvent; // counter based event not created with ${X}_EVENT_COUNTER_BASED_FLAG_GRAPH_EXTERNAL

    ${x}_event_ext_flags_desc_t graphExternalDesc = {
        ${X}_STRUCTURE_TYPE_EVENT_EXT_FLAGS_DESC,      // stype
        nullptr,                                       // pNext
        ${X}_EVENT_EXT_FLAG_APPEND_GRAPH_EXTERNAL      // flags
    };

    // now the event acts as an external wait event, can receive the signals from outside the graph (for example from another graph, an immediate command list or a mutable command list)
    ${x}CommandListAppendWaitOnEventsWithParameters(hCommandList, &graphExternalDesc, 1, &hEvent);

    // now the event acts as an internal signal event to pass a signal within the graph to the fork branch
    ${x}CommandListAppendSignalEvent(hCommandList, hEvent);

    // now the event acts as an internal wait event used to receive the signal from the root branch
    ${x}CommandListAppendWaitOnEvents(hChildCommandList, 1, &hEvent);

    // some work inside the fork branch
    /// ...

    // now the event acts as an internal signal event to pass a signal from the fork branch back to the root branch
    ${x}CommandListAppendSignalEvent(hChildCommandList, hEvent);

    // now the event acts as an internal wait event used to receive the signal from the fork branch
    ${x}CommandListAppendWaitOnEvents(hCommandList, 1, &hEvent);

    // some work inside the root branch
    // ...

    // now the event acts as an external signal event; the event can be used outside the graph for host or device synchronization
    ${x}CommandListAppendSignalEventWithParameters(hCommandList, &graphExternalDesc, hEvent);
