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


* Enumerations


    * ${x}_record_replay_graph_ext_version_t
    * ${x}_record_replay_graph_ext_flags_t
    * ${x}_record_replay_graph_ext_dump_mode_t


* Structures


    * ${x}_record_replay_graph_ext_properties_t
    * ${x}_record_replay_graph_ext_dump_desc_t

Record and Replay Graph
~~~~~~~~~~~~~~~~~~~~~~~

This extension allows applications to capture append operations from immediate command lists into a graph, instantiate that graph, and replay it efficiently.

Applications can query support and capabilities using ${x}_record_replay_graph_ext_properties_t and ${x}_record_replay_graph_ext_flags_t. Captured graphs can be inspected with ${x}GraphDumpContentsExt, and ${x}_record_replay_graph_ext_dump_desc_t controls dump behavior.

Typical Flow
~~~~~~~~~~~~

1. Create a graph with ${x}GraphCreateExt, or begin capture directly on an immediate command list with ${x}CommandListBeginGraphCaptureExt.
2. Record append operations and optionally query capture state via ${x}CommandListIsGraphCaptureEnabledExt and ${x}CommandListGetGraphExt.
3. End capture using ${x}CommandListEndGraphCaptureExt.
4. Instantiate an executable graph with ${x}GraphInstantiateExt.
5. Submit the executable graph using ${x}CommandListAppendGraphExt.
6. Optionally dump graph contents with ${x}GraphDumpContentsExt.
7. Destroy executable and recorded graph objects using ${x}ExecutableGraphDestroyExt and ${x}GraphDestroyExt.