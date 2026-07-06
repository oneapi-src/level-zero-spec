<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_command_queue_set_priority:

=====================================
 Command Queue Set Priority Extension
=====================================

Overview
--------

The Command Queue Set Priority extension lets an application change the scheduling
priority of an existing command queue at runtime, without destroying and recreating
it. It complements the initial priority specified through ${x}_command_queue_desc_t
at creation and the value reported by ${x}CommandQueueGetPriority.

The point at which a new priority takes effect, whether it influences work already
submitted to the queue or only work submitted afterward, is implementation-defined.

API
----

* Functions

    * ${x}CommandQueueSetPriorityExt

* Enumerations

    * ${x}_command_queue_set_priority_ext_version_t
