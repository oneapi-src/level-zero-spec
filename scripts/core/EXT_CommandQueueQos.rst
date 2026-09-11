<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_command_queue_qos:

================================
 Command Queue QoS Extension
================================

Overview
--------

The Command Queue QoS extension lets an application express the desired
power/energy characteristics ("Quality of Service") of a command queue,
independent of its scheduling priority (${x}_command_queue_priority_t).

The requested level is described by ${x}_command_queue_qos_ext_desc_t, which
may be specified at creation time by chaining it to the `pNext` member of
${x}_command_queue_desc_t, and/or passed at runtime to
${x}CommandQueueSetQosExt. Setting the descriptor's `qos` member to
${X}_COMMAND_QUEUE_QOS_EXT_DEFAULT requests the driver/OS-selected default
rather than an explicit level, so a zero-initialized descriptor requests no
change in behavior.

${x}CommandQueueGetQosExt reports the effective level of a command queue
through ${x}_command_queue_qos_ext_properties_t, along with an
`isOverridden` flag indicating whether that level was specified by the
application or selected by the driver/OS. This lets a layered runtime
distinguish a deliberately requested level from the default on a command
queue it did not configure itself.

Applications must not perform relational comparisons (e.g. less-than,
greater-than) between QoS levels; only equality checks are guaranteed to be
meaningful. The numeric values are not guaranteed to be ordered by energy
efficiency, and future levels may be added without preserving any such order.

API
----

* Functions

    * ${x}CommandQueueSetQosExt
    * ${x}CommandQueueGetQosExt

* Enumerations

    * ${x}_command_queue_qos_ext_version_t
    * ${x}_command_queue_qos_ext_t

* Structures

    * ${x}_command_queue_qos_ext_desc_t
    * ${x}_command_queue_qos_ext_properties_t
