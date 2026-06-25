
:orphan:

.. _ZE_extension_record_replay_graph:

===================================
 Record and Replay Graph Extension
===================================

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


* Enumerations


    * :ref:`ze-record-replay-graph-ext-version-t`
    * :ref:`ze-record-replay-graph-ext-flags-t`
    * :ref:`ze-record-replay-graph-ext-dump-mode-t`


* Structures


    * :ref:`ze-record-replay-graph-ext-properties-t`
    * :ref:`ze-record-replay-graph-ext-dump-desc-t`

Record and Replay Graph
~~~~~~~~~~~~~~~~~~~~~~~

This extension allows applications to capture append operations from immediate command lists into a graph, instantiate that graph, and replay it efficiently.

Applications can query support and capabilities using :ref:`ze-record-replay-graph-ext-properties-t` and :ref:`ze-record-replay-graph-ext-flags-t`\. Captured graphs can be inspected with :ref:`zeGraphDumpContentsExt`\, and :ref:`ze-record-replay-graph-ext-dump-desc-t` controls dump behavior.

Typical Flow
~~~~~~~~~~~~

1. Create a graph with :ref:`zeGraphCreateExt`\, or begin capture directly on an immediate command list with :ref:`zeCommandListBeginGraphCaptureExt`\.
2. Record append operations and optionally query capture state via :ref:`zeCommandListIsGraphCaptureEnabledExt` and :ref:`zeCommandListGetGraphExt`\.
3. End capture using :ref:`zeCommandListEndGraphCaptureExt`\.
4. Instantiate an executable graph with :ref:`zeGraphInstantiateExt`\.
5. Submit the executable graph using :ref:`zeCommandListAppendGraphExt`\.
6. Optionally dump graph contents with :ref:`zeGraphDumpContentsExt`\.
7. Destroy executable and recorded graph objects using :ref:`zeExecutableGraphDestroyExt` and :ref:`zeGraphDestroyExt`\.