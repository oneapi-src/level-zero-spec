============================================================
Command List
============================================================
oneAPI Level Zero Specification - Version 1.21.26




Command List Functions
======================


.. _zeCommandListAppendLaunchMultipleKernelsIndirect:

zeCommandListAppendLaunchMultipleKernelsIndirect
------------------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeCommandListAppendLaunchMultipleKernelsIndirect
    :project: LevelZero


.. _zeCommandListHostSynchronize:

zeCommandListHostSynchronize
----------------------------

.. rst-class:: api-version

*Added in version 1.6*

.. doxygenfunction:: zeCommandListHostSynchronize
    :project: LevelZero


.. _zeCommandListGetDeviceHandle:

zeCommandListGetDeviceHandle
----------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeCommandListGetDeviceHandle
    :project: LevelZero


.. _zeCommandListGetContextHandle:

zeCommandListGetContextHandle
-----------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeCommandListGetContextHandle
    :project: LevelZero


.. _zeCommandListGetOrdinal:

zeCommandListGetOrdinal
-----------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeCommandListGetOrdinal
    :project: LevelZero


.. _zeCommandListImmediateGetIndex:

zeCommandListImmediateGetIndex
------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeCommandListImmediateGetIndex
    :project: LevelZero


.. _zeCommandListIsImmediate:

zeCommandListIsImmediate
------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeCommandListIsImmediate
    :project: LevelZero


.. _zeCommandListAppendLaunchKernelWithParameters:

zeCommandListAppendLaunchKernelWithParameters
---------------------------------------------

.. rst-class:: api-version

*Added in version 1.14*

.. doxygenfunction:: zeCommandListAppendLaunchKernelWithParameters
    :project: LevelZero


.. _zeCommandListAppendLaunchKernelWithArguments:

zeCommandListAppendLaunchKernelWithArguments
--------------------------------------------

.. rst-class:: api-version

*Added in version 1.14*

.. doxygenfunction:: zeCommandListAppendLaunchKernelWithArguments
    :project: LevelZero


.. _zeCommandListAppendMemoryCopyWithParameters:

zeCommandListAppendMemoryCopyWithParameters
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.16*

.. doxygenfunction:: zeCommandListAppendMemoryCopyWithParameters
    :project: LevelZero


.. _zeCommandListAppendMemoryFillWithParameters:

zeCommandListAppendMemoryFillWithParameters
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.16*

.. doxygenfunction:: zeCommandListAppendMemoryFillWithParameters
    :project: LevelZero


.. _zeCommandListImmediateAppendCommandListsWithParameters:

zeCommandListImmediateAppendCommandListsWithParameters
------------------------------------------------------

.. rst-class:: api-version

*Added in version 1.16*

.. doxygenfunction:: zeCommandListImmediateAppendCommandListsWithParameters
    :project: LevelZero


.. _zeCommandListGetFlags:

zeCommandListGetFlags
---------------------

.. rst-class:: api-version

*Added in version 1.17*

.. doxygenfunction:: zeCommandListGetFlags
    :project: LevelZero


.. _zeCommandListImmediateGetFlags:

zeCommandListImmediateGetFlags
------------------------------

.. rst-class:: api-version

*Added in version 1.17*

.. doxygenfunction:: zeCommandListImmediateGetFlags
    :project: LevelZero


.. _zeCommandListImmediateGetMode:

zeCommandListImmediateGetMode
-----------------------------

.. rst-class:: api-version

*Added in version 1.17*

.. doxygenfunction:: zeCommandListImmediateGetMode
    :project: LevelZero


.. _zeCommandListImmediateGetPriority:

zeCommandListImmediateGetPriority
---------------------------------

.. rst-class:: api-version

*Added in version 1.17*

.. doxygenfunction:: zeCommandListImmediateGetPriority
    :project: LevelZero


.. _zeCommandListAppendHostFunction:

zeCommandListAppendHostFunction
-------------------------------

.. rst-class:: api-version

*Added in version 1.17*

.. doxygenfunction:: zeCommandListAppendHostFunction
    :project: LevelZero


.. _zeCommandListAppendSignalEventWithParameters:

zeCommandListAppendSignalEventWithParameters
--------------------------------------------

.. rst-class:: api-version

*Added in version 1.18*

.. doxygenfunction:: zeCommandListAppendSignalEventWithParameters
    :project: LevelZero


.. _zeCommandListAppendWaitOnEventsWithParameters:

zeCommandListAppendWaitOnEventsWithParameters
---------------------------------------------

.. rst-class:: api-version

*Added in version 1.18*

.. doxygenfunction:: zeCommandListAppendWaitOnEventsWithParameters
    :project: LevelZero



Command List Enums
==================


.. _ze-command-list-flags-t:

ze_command_list_flags_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandListGetFlags`
   | **Member of:** :ref:`ze-command-list-desc-t`

.. doxygentypedef:: ze_command_list_flags_t
    :project: LevelZero

.. doxygenenum:: ze_command_list_flag_t
    :project: LevelZero


.. _ze-memory-advice-t:

ze_memory_advice_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandListAppendMemAdvise`

.. doxygenenum:: ze_memory_advice_t
    :project: LevelZero


 
Command List Structures
=======================


.. _ze-command-list-desc-t:

ze_command_list_desc_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandListCreate`

.. doxygenstruct:: ze_command_list_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-copy-region-t:

ze_copy_region_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandListAppendMemoryCopyRegion`

.. doxygenstruct:: ze_copy_region_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-image-region-t:

ze_image_region_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandListAppendImageCopyRegion`, :ref:`zeCommandListAppendImageCopyToMemory`, :ref:`zeCommandListAppendImageCopyFromMemory`, :ref:`zeCommandListAppendImageCopyToMemoryExt`, :ref:`zeCommandListAppendImageCopyFromMemoryExt`

.. doxygenstruct:: ze_image_region_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-command-list-append-launch-kernel-param-cooperative-desc-t:

ze_command_list_append_launch_kernel_param_cooperative_desc_t
-------------------------------------------------------------

.. rst-class:: api-version

*Added in version 1.14*

.. doxygenstruct:: ze_command_list_append_launch_kernel_param_cooperative_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-group-count-t:

ze_group_count_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandListAppendLaunchKernel`, :ref:`zeCommandListAppendLaunchKernelWithParameters`, :ref:`zeCommandListAppendLaunchKernelWithArguments`, :ref:`zeCommandListAppendLaunchCooperativeKernel`, :ref:`zeCommandListAppendLaunchKernelIndirect`, :ref:`zeCommandListAppendLaunchMultipleKernelsIndirect`
   | **Member of:** :ref:`ze-mutable-group-count-exp-desc-t`, :ref:`ze-mutable-group-count-ext-desc-t`

.. doxygenstruct:: ze_group_count_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-group-size-t:

ze_group_size_t
---------------

.. rst-class:: api-version

*Added in version 1.14*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandListAppendLaunchKernelWithArguments`

.. doxygenstruct:: ze_group_size_t
    :project: LevelZero
    :members:
    :undoc-members:


.. raw:: html

   <nav class="api-pager" aria-label="Page navigation"><a class="prev" href="command_list.html">&lsaquo; Prev</a><a href="command_list.html">1</a><strong class="current">2</strong><span class="next disabled">Next &rsaquo;</span></nav>
