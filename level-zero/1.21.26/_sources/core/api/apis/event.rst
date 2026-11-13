============================================================
Event
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Event Handles
=============


.. _ze-event-handle-t:

ze_event_handle_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeEventCreate`, :ref:`zeEventCounterBasedCreate`, :ref:`zeEventCounterBasedOpenIpcHandle`
   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-ze-event-handle-t-3"><span class="api-usage-links">` :ref:`zeCommandListAppendWriteGlobalTimestamp`, :ref:`zeCommandListAppendBarrier`, :ref:`zeCommandListAppendMemoryRangesBarrier`, :ref:`zeCommandListAppendMemoryCopy`, :ref:`zeCommandListAppendMemoryCopyWithParameters`, :ref:`zeCommandListAppendMemoryFill`, :ref:`zeCommandListAppendMemoryFillWithParameters`, :ref:`zeCommandListAppendMemoryCopyRegion`, :ref:`zeCommandListAppendMemoryCopyFromContext`, :ref:`zeCommandListAppendImageCopy`, :ref:`zeCommandListAppendImageCopyRegion`, :ref:`zeCommandListAppendImageCopyToMemory`, :ref:`zeCommandListAppendImageCopyFromMemory`, :ref:`zeEventDestroy`, :ref:`zeEventCounterBasedGetIpcHandle`, :ref:`zeEventCounterBasedCloseIpcHandle`, :ref:`zeEventCounterBasedGetDeviceAddress`, :ref:`zeCommandListAppendSignalEvent`, :ref:`zeCommandListAppendSignalEventWithParameters`, :ref:`zeCommandListAppendWaitOnEvents`, :ref:`zeCommandListAppendWaitOnEventsWithParameters`, :ref:`zeEventHostSignal`, :ref:`zeEventHostSynchronize`, :ref:`zeEventQueryStatus`, :ref:`zeCommandListAppendEventReset`, :ref:`zeEventHostReset`, :ref:`zeEventQueryKernelTimestamp`, :ref:`zeCommandListAppendQueryKernelTimestamps`, :ref:`zeEventGetEventPool`, :ref:`zeEventGetSignalScope`, :ref:`zeEventGetWaitScope`, :ref:`zeEventGetCounterBasedFlags`, :ref:`zeCommandListAppendLaunchKernel`, :ref:`zeCommandListAppendLaunchKernelWithParameters`, :ref:`zeCommandListAppendLaunchKernelWithArguments`, :ref:`zeCommandListAppendLaunchCooperativeKernel`, :ref:`zeCommandListAppendLaunchKernelIndirect`, :ref:`zeCommandListAppendLaunchMultipleKernelsIndirect`, :ref:`zeEventQueryTimestampsExp`, :ref:`zeCommandListAppendImageCopyToMemoryExt`, :ref:`zeCommandListAppendImageCopyFromMemoryExt`, :ref:`zeEventQueryKernelTimestampsExt`, :ref:`zeCommandListImmediateAppendCommandListsExp`, :ref:`zeCommandListImmediateAppendCommandListsWithParameters`, :ref:`zeCommandListUpdateMutableCommandSignalEventExp`, :ref:`zeCommandListUpdateMutableCommandWaitEventsExp`, :ref:`zeCommandListAppendSignalExternalSemaphoreExt`, :ref:`zeCommandListAppendWaitExternalSemaphoreExt`, :ref:`zeCommandQueueSignalExternalSemaphoreExt`, :ref:`zeCommandQueueWaitExternalSemaphoreExt`, :ref:`zeRTASBuilderCommandListAppendCopyExt`, :ref:`zeCommandListAppendGraphExt`, :ref:`zeCommandListAppendHostFunction`, :ref:`zeCommandListUpdateMutableCommandSignalEventExt`, :ref:`zeCommandListUpdateMutableCommandWaitEventsExt` :raw-html:`</span><label for="usage-ze-event-handle-t-3"><span class="more">Show all 55</span><span class="less">Show less</span></label></span>`
   | **Used by (Tools):** :ref:`zetMetricStreamerOpen`, :ref:`zetCommandListAppendMetricQueryEnd`, :ref:`zetMetricTracerCreateExp`
   | **Passed to callback in:** :ref:`ze-command-visit-ext-desc-t`
   | **See also:** :ref:`Events (Programming Guide) <Events>`

.. cpp:type:: ze_event_handle_t

    Handle of driver's event object.



Event Functions
===============


.. _zeEventCreate:

zeEventCreate
-------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventCreate
    :project: LevelZero


.. _zeEventDestroy:

zeEventDestroy
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventDestroy
    :project: LevelZero


.. _zeEventHostSignal:

zeEventHostSignal
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventHostSignal
    :project: LevelZero


.. _zeEventHostSynchronize:

zeEventHostSynchronize
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventHostSynchronize
    :project: LevelZero


.. _zeEventQueryStatus:

zeEventQueryStatus
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventQueryStatus
    :project: LevelZero


.. _zeEventHostReset:

zeEventHostReset
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventHostReset
    :project: LevelZero


.. _zeEventQueryKernelTimestamp:

zeEventQueryKernelTimestamp
---------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventQueryKernelTimestamp
    :project: LevelZero


.. _zeEventGetEventPool:

zeEventGetEventPool
-------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeEventGetEventPool
    :project: LevelZero


.. _zeEventGetSignalScope:

zeEventGetSignalScope
---------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeEventGetSignalScope
    :project: LevelZero


.. _zeEventGetWaitScope:

zeEventGetWaitScope
-------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeEventGetWaitScope
    :project: LevelZero


.. _zeEventCounterBasedCreate:

zeEventCounterBasedCreate
-------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. doxygenfunction:: zeEventCounterBasedCreate
    :project: LevelZero


.. _zeEventCounterBasedGetIpcHandle:

zeEventCounterBasedGetIpcHandle
-------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. doxygenfunction:: zeEventCounterBasedGetIpcHandle
    :project: LevelZero


.. _zeEventCounterBasedOpenIpcHandle:

zeEventCounterBasedOpenIpcHandle
--------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. doxygenfunction:: zeEventCounterBasedOpenIpcHandle
    :project: LevelZero


.. _zeEventCounterBasedCloseIpcHandle:

zeEventCounterBasedCloseIpcHandle
---------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. doxygenfunction:: zeEventCounterBasedCloseIpcHandle
    :project: LevelZero


.. _zeEventCounterBasedGetDeviceAddress:

zeEventCounterBasedGetDeviceAddress
-----------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. doxygenfunction:: zeEventCounterBasedGetDeviceAddress
    :project: LevelZero


.. _zeEventGetCounterBasedFlags:

zeEventGetCounterBasedFlags
---------------------------

.. rst-class:: api-version

*Added in version 1.17*

.. doxygenfunction:: zeEventGetCounterBasedFlags
    :project: LevelZero



Event Enums
===========


.. _ze-event-scope-flags-t:

ze_event_scope_flags_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeEventGetSignalScope`, :ref:`zeEventGetWaitScope`
   | **Member of:** :ref:`ze-event-desc-t`, :ref:`ze-event-counter-based-desc-t`

.. doxygentypedef:: ze_event_scope_flags_t
    :project: LevelZero

.. doxygenenum:: ze_event_scope_flag_t
    :project: LevelZero


.. _ze-event-counter-based-flags-t:

ze_event_counter_based_flags_t
------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. container:: api-usage

   | **Used by:** :ref:`zeEventGetCounterBasedFlags`
   | **Member of:** :ref:`ze-event-counter-based-desc-t`

.. doxygentypedef:: ze_event_counter_based_flags_t
    :project: LevelZero

.. doxygenenum:: ze_event_counter_based_flag_t
    :project: LevelZero


.. _ze-event-sync-mode-flags-t:

ze_event_sync_mode_flags_t
--------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. container:: api-usage

   | **Member of:** :ref:`ze-event-sync-mode-desc-t`

.. doxygentypedef:: ze_event_sync_mode_flags_t
    :project: LevelZero

.. doxygenenum:: ze_event_sync_mode_flag_t
    :project: LevelZero


 
Event Structures
================


.. _ze-device-event-properties-t:

ze_device_event_properties_t
----------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-properties-t`

.. doxygenstruct:: ze_device_event_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-event-sync-mode-desc-t:

ze_event_sync_mode_desc_t
-------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. doxygenstruct:: ze_event_sync_mode_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-event-desc-t:

ze_event_desc_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeEventCreate`

.. doxygenstruct:: ze_event_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-event-counter-based-desc-t:

ze_event_counter_based_desc_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. container:: api-usage

   | **Used by:** :ref:`zeEventCounterBasedCreate`
   | **pNext may point to:** :ref:`ze-event-counter-based-external-sync-allocation-desc-t`, :ref:`ze-event-counter-based-external-aggregate-storage-desc-t`

.. doxygenstruct:: ze_event_counter_based_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-event-counter-based-external-sync-allocation-desc-t:

ze_event_counter_based_external_sync_allocation_desc_t
------------------------------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-event-counter-based-desc-t`

.. doxygenstruct:: ze_event_counter_based_external_sync_allocation_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-event-counter-based-external-aggregate-storage-desc-t:

ze_event_counter_based_external_aggregate_storage_desc_t
--------------------------------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-event-counter-based-desc-t`

.. doxygenstruct:: ze_event_counter_based_external_aggregate_storage_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-kernel-timestamp-data-t:

ze_kernel_timestamp_data_t
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-kernel-timestamp-result-t`

.. doxygenstruct:: ze_kernel_timestamp_data_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-kernel-timestamp-result-t:

ze_kernel_timestamp_result_t
----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeEventQueryKernelTimestamp`, :ref:`zeEventQueryTimestampsExp`, :ref:`zeCommandListAppendQueryKernelTimestamps`
   | **Member of:** :ref:`ze-event-query-kernel-timestamps-results-ext-properties-t`

.. doxygenstruct:: ze_kernel_timestamp_result_t
    :project: LevelZero
    :members:
    :undoc-members:

