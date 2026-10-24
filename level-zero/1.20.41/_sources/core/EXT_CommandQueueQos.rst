
:orphan:

.. _ZE_extension_command_queue_qos:

================================
 Command Queue QoS Extension
================================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.19*

Overview
--------

The Command Queue QoS extension lets an application express the desired
power/energy characteristics ("Quality of Service") of a command queue,
independent of its scheduling priority (:ref:`ze-command-queue-priority-t`\).

The requested level is described by :ref:`ze-command-queue-qos-ext-desc-t`\, which
may be specified at creation time by chaining it to the `pNext` member of
:ref:`ze-command-queue-desc-t`\, and/or passed at runtime to
:ref:`zeCommandQueueSetQosExt`\. Setting the descriptor's `qos` member to
:ref:`ZE_COMMAND_QUEUE_QOS_EXT_DEFAULT <ze-command-queue-qos-ext-t>` requests the driver/OS-selected default
rather than an explicit level, so a zero-initialized descriptor requests no
change in behavior.

:ref:`zeCommandQueueGetQosExt` reports the effective level of a command queue
through :ref:`ze-command-queue-qos-ext-properties-t`\, along with an
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

    * :ref:`zeCommandQueueSetQosExt`
    * :ref:`zeCommandQueueGetQosExt`

* Enumerations

    * :ref:`ze-command-queue-qos-ext-version-t`
    * :ref:`ze-command-queue-qos-ext-t`

* Structures

    * :ref:`ze-command-queue-qos-ext-desc-t`
    * :ref:`ze-command-queue-qos-ext-properties-t`
