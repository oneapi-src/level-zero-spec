
:orphan:

.. _ZE_extension_command_queue_set_priority:

=====================================
 Command Queue Set Priority Extension
=====================================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.18*

Overview
--------

The Command Queue Set Priority extension lets an application change the scheduling
priority of an existing command queue at runtime, without destroying and recreating
it. It complements the initial priority specified through :ref:`ze-command-queue-desc-t`
at creation and the value reported by :ref:`zeCommandQueueGetPriority`\.

The point at which a new priority takes effect, whether it influences work already
submitted to the queue or only work submitted afterward, is implementation-defined.

API
----

* Functions

    * :ref:`zeCommandQueueSetPriorityExt`

* Enumerations

    * :ref:`ze-command-queue-set-priority-ext-version-t`
