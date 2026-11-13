============================================================
Command List
============================================================

.. toctree::
   :hidden:

   command_list-2

oneAPI Level Zero Specification - Version 1.21.26


Command List Handles
====================


.. _ze-command-list-handle-t:

ze_command_list_handle_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeCommandListCreate`, :ref:`zeCommandListCreateImmediate`, :ref:`zeCommandListCreateCloneExp`, :ref:`zeGraphGetPrimaryCommandListExt`
   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-ze-command-list-handle-t-3"><span class="api-usage-links">` :ref:`zeCommandQueueExecuteCommandLists`, :ref:`zeCommandListDestroy`, :ref:`zeCommandListClose`, :ref:`zeCommandListReset`, :ref:`zeCommandListAppendWriteGlobalTimestamp`, :ref:`zeCommandListHostSynchronize`, :ref:`zeCommandListGetDeviceHandle`, :ref:`zeCommandListGetContextHandle`, :ref:`zeCommandListGetOrdinal`, :ref:`zeCommandListImmediateGetIndex`, :ref:`zeCommandListIsImmediate`, :ref:`zeCommandListGetFlags`, :ref:`zeCommandListImmediateGetFlags`, :ref:`zeCommandListImmediateGetMode`, :ref:`zeCommandListImmediateGetPriority`, :ref:`zeCommandListAppendBarrier`, :ref:`zeCommandListAppendMemoryRangesBarrier`, :ref:`zeCommandListAppendMemoryCopy`, :ref:`zeCommandListAppendMemoryCopyWithParameters`, :ref:`zeCommandListAppendMemoryFill`, :ref:`zeCommandListAppendMemoryFillWithParameters`, :ref:`zeCommandListAppendMemoryCopyRegion`, :ref:`zeCommandListAppendMemoryCopyFromContext`, :ref:`zeCommandListAppendImageCopy`, :ref:`zeCommandListAppendImageCopyRegion`, :ref:`zeCommandListAppendImageCopyToMemory`, :ref:`zeCommandListAppendImageCopyFromMemory`, :ref:`zeCommandListAppendMemoryPrefetch`, :ref:`zeCommandListAppendMemAdvise`, :ref:`zeCommandListAppendSignalEvent`, :ref:`zeCommandListAppendSignalEventWithParameters`, :ref:`zeCommandListAppendWaitOnEvents`, :ref:`zeCommandListAppendWaitOnEventsWithParameters`, :ref:`zeCommandListAppendEventReset`, :ref:`zeCommandListAppendQueryKernelTimestamps`, :ref:`zeCommandListAppendLaunchKernel`, :ref:`zeCommandListAppendLaunchKernelWithParameters`, :ref:`zeCommandListAppendLaunchKernelWithArguments`, :ref:`zeCommandListAppendLaunchCooperativeKernel`, :ref:`zeCommandListAppendLaunchKernelIndirect`, :ref:`zeCommandListAppendLaunchMultipleKernelsIndirect`, :ref:`zeCommandListAppendImageCopyToMemoryExt`, :ref:`zeCommandListAppendImageCopyFromMemoryExt`, :ref:`zeCommandListCreateCloneExp`, :ref:`zeCommandListImmediateAppendCommandListsExp`, :ref:`zeCommandListImmediateAppendCommandListsWithParameters`, :ref:`zeCommandListGetNextCommandIdExp`, :ref:`zeCommandListGetNextCommandIdWithKernelsExp`, :ref:`zeCommandListUpdateMutableCommandsExp`, :ref:`zeCommandListIsMutableExp`, :ref:`zeCommandListUpdateMutableCommandSignalEventExp`, :ref:`zeCommandListUpdateMutableCommandWaitEventsExp`, :ref:`zeCommandListUpdateMutableCommandKernelsExp`, :ref:`zeCommandListAppendSignalExternalSemaphoreExt`, :ref:`zeCommandListAppendWaitExternalSemaphoreExt`, :ref:`zeRTASBuilderCommandListAppendCopyExt`, :ref:`zeCommandListBeginGraphCaptureExt`, :ref:`zeCommandListBeginCaptureIntoGraphExt`, :ref:`zeCommandListIsGraphCaptureEnabledExt`, :ref:`zeCommandListEndGraphCaptureExt`, :ref:`zeCommandListGetGraphExt`, :ref:`zeCommandListAppendGraphExt`, :ref:`zeCommandListAppendHostFunction`, :ref:`zeCommandListVisitExt`, :ref:`zeCommandListGetNextCommandIdExt`, :ref:`zeCommandListGetNextCommandIdWithKernelsExt`, :ref:`zeCommandListUpdateMutableCommandsExt`, :ref:`zeCommandListIsMutableExt`, :ref:`zeCommandListUpdateMutableCommandSignalEventExt`, :ref:`zeCommandListUpdateMutableCommandWaitEventsExt`, :ref:`zeCommandListUpdateMutableCommandKernelsExt` :raw-html:`</span><label for="usage-ze-command-list-handle-t-3"><span class="more">Show all 71</span><span class="less">Show less</span></label></span>`
   | **Member of:** :ref:`ze-command-visit-ext-desc-t`
   | **See also:** `Command Lists (Programming Guide) <../../PROG.html#command-lists>`__

.. cpp:type:: ze_command_list_handle_t

    Handle of driver's command list object.



Command List Functions
======================


.. _zeCommandListCreate:

zeCommandListCreate
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListCreate
    :project: LevelZero


.. _zeCommandListCreateImmediate:

zeCommandListCreateImmediate
----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListCreateImmediate
    :project: LevelZero


.. _zeCommandListDestroy:

zeCommandListDestroy
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListDestroy
    :project: LevelZero


.. _zeCommandListClose:

zeCommandListClose
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListClose
    :project: LevelZero


.. _zeCommandListReset:

zeCommandListReset
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListReset
    :project: LevelZero


.. _zeCommandListAppendWriteGlobalTimestamp:

zeCommandListAppendWriteGlobalTimestamp
---------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendWriteGlobalTimestamp
    :project: LevelZero


.. _zeCommandListAppendBarrier:

zeCommandListAppendBarrier
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendBarrier
    :project: LevelZero


.. _zeCommandListAppendMemoryRangesBarrier:

zeCommandListAppendMemoryRangesBarrier
--------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendMemoryRangesBarrier
    :project: LevelZero


.. _zeCommandListAppendMemoryCopy:

zeCommandListAppendMemoryCopy
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendMemoryCopy
    :project: LevelZero


.. _zeCommandListAppendMemoryFill:

zeCommandListAppendMemoryFill
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendMemoryFill
    :project: LevelZero


.. _zeCommandListAppendMemoryCopyRegion:

zeCommandListAppendMemoryCopyRegion
-----------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendMemoryCopyRegion
    :project: LevelZero


.. _zeCommandListAppendMemoryCopyFromContext:

zeCommandListAppendMemoryCopyFromContext
----------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendMemoryCopyFromContext
    :project: LevelZero


.. _zeCommandListAppendImageCopy:

zeCommandListAppendImageCopy
----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendImageCopy
    :project: LevelZero


.. _zeCommandListAppendImageCopyRegion:

zeCommandListAppendImageCopyRegion
----------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendImageCopyRegion
    :project: LevelZero


.. _zeCommandListAppendImageCopyToMemory:

zeCommandListAppendImageCopyToMemory
------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendImageCopyToMemory
    :project: LevelZero


.. _zeCommandListAppendImageCopyFromMemory:

zeCommandListAppendImageCopyFromMemory
--------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendImageCopyFromMemory
    :project: LevelZero


.. _zeCommandListAppendMemoryPrefetch:

zeCommandListAppendMemoryPrefetch
---------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendMemoryPrefetch
    :project: LevelZero


.. _zeCommandListAppendMemAdvise:

zeCommandListAppendMemAdvise
----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendMemAdvise
    :project: LevelZero


.. _zeCommandListAppendSignalEvent:

zeCommandListAppendSignalEvent
------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendSignalEvent
    :project: LevelZero


.. _zeCommandListAppendWaitOnEvents:

zeCommandListAppendWaitOnEvents
-------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendWaitOnEvents
    :project: LevelZero


.. _zeCommandListAppendEventReset:

zeCommandListAppendEventReset
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendEventReset
    :project: LevelZero


.. _zeCommandListAppendQueryKernelTimestamps:

zeCommandListAppendQueryKernelTimestamps
----------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendQueryKernelTimestamps
    :project: LevelZero


.. _zeCommandListAppendLaunchKernel:

zeCommandListAppendLaunchKernel
-------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendLaunchKernel
    :project: LevelZero


.. _zeCommandListAppendLaunchCooperativeKernel:

zeCommandListAppendLaunchCooperativeKernel
------------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendLaunchCooperativeKernel
    :project: LevelZero


.. _zeCommandListAppendLaunchKernelIndirect:

zeCommandListAppendLaunchKernelIndirect
---------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendLaunchKernelIndirect
    :project: LevelZero




 

.. raw:: html

   <nav class="api-pager" aria-label="Page navigation"><span class="prev disabled">&lsaquo; Prev</span><strong class="current">1</strong><a href="command_list-2.html">2</a><a class="next" href="command_list-2.html">Next &rsaquo;</a></nav>
