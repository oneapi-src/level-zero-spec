============================================================
Command Queue
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Command Queue Handles
=====================


.. _ze-command-queue-handle-t:

ze_command_queue_handle_t
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeCommandQueueCreate`
   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-ze-command-queue-handle-t-3"><span class="api-usage-links">` :ref:`zeCommandQueueDestroy`, :ref:`zeCommandQueueExecuteCommandLists`, :ref:`zeCommandQueueSynchronize`, :ref:`zeCommandQueueGetOrdinal`, :ref:`zeCommandQueueGetIndex`, :ref:`zeCommandQueueGetFlags`, :ref:`zeCommandQueueGetMode`, :ref:`zeCommandQueueGetPriority`, :ref:`zeFenceCreate`, :ref:`zeCommandQueueSignalExternalSemaphoreExt`, :ref:`zeCommandQueueWaitExternalSemaphoreExt`, :ref:`zeCommandQueueSetPriorityExt`, :ref:`zeCommandQueueSetQosExt`, :ref:`zeCommandQueueGetQosExt` :raw-html:`</span><label for="usage-ze-command-queue-handle-t-3"><span class="more">Show all 14</span><span class="less">Show less</span></label></span>`
   | **See also:** `Command Queues (Programming Guide) <../../PROG.html#command-queues>`__

.. cpp:type:: ze_command_queue_handle_t

    Handle of driver's command queue object.



Command Queue Functions
=======================


.. _zeCommandQueueCreate:

zeCommandQueueCreate
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandQueueCreate
    :project: LevelZero


.. _zeCommandQueueDestroy:

zeCommandQueueDestroy
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandQueueDestroy
    :project: LevelZero


.. _zeCommandQueueExecuteCommandLists:

zeCommandQueueExecuteCommandLists
---------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandQueueExecuteCommandLists
    :project: LevelZero


.. _zeCommandQueueSynchronize:

zeCommandQueueSynchronize
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandQueueSynchronize
    :project: LevelZero


.. _zeCommandQueueGetOrdinal:

zeCommandQueueGetOrdinal
------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeCommandQueueGetOrdinal
    :project: LevelZero


.. _zeCommandQueueGetIndex:

zeCommandQueueGetIndex
----------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeCommandQueueGetIndex
    :project: LevelZero


.. _zeCommandQueueGetFlags:

zeCommandQueueGetFlags
----------------------

.. rst-class:: api-version

*Added in version 1.17*

.. doxygenfunction:: zeCommandQueueGetFlags
    :project: LevelZero


.. _zeCommandQueueGetMode:

zeCommandQueueGetMode
---------------------

.. rst-class:: api-version

*Added in version 1.17*

.. doxygenfunction:: zeCommandQueueGetMode
    :project: LevelZero


.. _zeCommandQueueGetPriority:

zeCommandQueueGetPriority
-------------------------

.. rst-class:: api-version

*Added in version 1.17*

.. doxygenfunction:: zeCommandQueueGetPriority
    :project: LevelZero



Command Queue Enums
===================


.. _ze-command-queue-flags-t:

ze_command_queue_flags_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandQueueGetFlags`, :ref:`zeCommandListImmediateGetFlags`
   | **Member of:** :ref:`ze-command-queue-desc-t`

.. doxygentypedef:: ze_command_queue_flags_t
    :project: LevelZero

.. doxygenenum:: ze_command_queue_flag_t
    :project: LevelZero


.. _ze-command-queue-mode-t:

ze_command_queue_mode_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandQueueGetMode`, :ref:`zeCommandListImmediateGetMode`
   | **Member of:** :ref:`ze-command-queue-desc-t`

.. doxygenenum:: ze_command_queue_mode_t
    :project: LevelZero


.. _ze-command-queue-priority-t:

ze_command_queue_priority_t
---------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandQueueGetPriority`, :ref:`zeCommandListImmediateGetPriority`, :ref:`zeCommandQueueSetPriorityExt`
   | **Member of:** :ref:`ze-command-queue-desc-t`

.. doxygenenum:: ze_command_queue_priority_t
    :project: LevelZero


 
Command Queue Structures
========================


.. _ze-command-queue-desc-t:

ze_command_queue_desc_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandQueueCreate`, :ref:`zeCommandListCreateImmediate`
   | **pNext may point to:** :ref:`ze-command-queue-qos-ext-desc-t`

.. doxygenstruct:: ze_command_queue_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

