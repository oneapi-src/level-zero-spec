============================================================
Command List - Deprecated
============================================================
oneAPI Level Zero Specification - Version 1.20.41


Command List - Deprecated Functions
===================================


.. _zeCommandListCreateCloneExp:

zeCommandListCreateCloneExp
---------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.17. Mutable command lists replace command list cloning. Use :ref:`ZE_extension_mutable_command_list <ZE_extension_mutable_command_list>` instead.

.. doxygenfunction:: zeCommandListCreateCloneExp
    :project: LevelZero


.. _zeCommandListImmediateAppendCommandListsExp:

zeCommandListImmediateAppendCommandListsExp
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.16. Use :ref:`zeCommandListImmediateAppendCommandListsWithParameters` instead.

.. doxygenfunction:: zeCommandListImmediateAppendCommandListsExp
    :project: LevelZero


.. _zeCommandListGetNextCommandIdExp:

zeCommandListGetNextCommandIdExp
--------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`zeCommandListGetNextCommandIdExt` instead.

.. doxygenfunction:: zeCommandListGetNextCommandIdExp
    :project: LevelZero


.. _zeCommandListUpdateMutableCommandsExp:

zeCommandListUpdateMutableCommandsExp
-------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`zeCommandListUpdateMutableCommandsExt` instead.

.. doxygenfunction:: zeCommandListUpdateMutableCommandsExp
    :project: LevelZero


.. _zeCommandListUpdateMutableCommandSignalEventExp:

zeCommandListUpdateMutableCommandSignalEventExp
-----------------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`zeCommandListUpdateMutableCommandSignalEventExt` instead.

.. doxygenfunction:: zeCommandListUpdateMutableCommandSignalEventExp
    :project: LevelZero


.. _zeCommandListUpdateMutableCommandWaitEventsExp:

zeCommandListUpdateMutableCommandWaitEventsExp
----------------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`zeCommandListUpdateMutableCommandWaitEventsExt` instead.

.. doxygenfunction:: zeCommandListUpdateMutableCommandWaitEventsExp
    :project: LevelZero


.. _zeCommandListGetNextCommandIdWithKernelsExp:

zeCommandListGetNextCommandIdWithKernelsExp
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.10*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`zeCommandListGetNextCommandIdWithKernelsExt` instead.

.. doxygenfunction:: zeCommandListGetNextCommandIdWithKernelsExp
    :project: LevelZero


.. _zeCommandListUpdateMutableCommandKernelsExp:

zeCommandListUpdateMutableCommandKernelsExp
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.10*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`zeCommandListUpdateMutableCommandKernelsExt` instead.

.. doxygenfunction:: zeCommandListUpdateMutableCommandKernelsExp
    :project: LevelZero


.. _zeCommandListIsMutableExp:

zeCommandListIsMutableExp
-------------------------

.. rst-class:: api-version

*Added in version 1.17*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`zeCommandListIsMutableExt` instead.

.. doxygenfunction:: zeCommandListIsMutableExp
    :project: LevelZero



Command List - Deprecated Enums
===============================


.. _ze-mutable-command-exp-flags-t:

ze_mutable_command_exp_flags_t
------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-command-ext-flags-t` instead.

.. doxygenenum:: ze_mutable_command_exp_flag_t
    :project: LevelZero


.. _ze-mutable-command-list-exp-flags-t:

ze_mutable_command_list_exp_flags_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-command-list-ext-flags-t` instead.

.. doxygenenum:: ze_mutable_command_list_exp_flag_t
    :project: LevelZero

 
Command List - Deprecated Structures
====================================


.. _ze-mutable-command-id-exp-desc-t:

ze_mutable_command_id_exp_desc_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-command-id-ext-desc-t` instead.

.. doxygenstruct:: ze_mutable_command_id_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-mutable-command-list-exp-properties-t:

ze_mutable_command_list_exp_properties_t
----------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-command-list-ext-properties-t` instead.

.. doxygenstruct:: ze_mutable_command_list_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-mutable-command-list-exp-desc-t:

ze_mutable_command_list_exp_desc_t
----------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-command-list-ext-desc-t` instead.

.. doxygenstruct:: ze_mutable_command_list_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-mutable-commands-exp-desc-t:

ze_mutable_commands_exp_desc_t
------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-commands-ext-desc-t` instead.

.. doxygenstruct:: ze_mutable_commands_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-mutable-kernel-argument-exp-desc-t:

ze_mutable_kernel_argument_exp_desc_t
-------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-kernel-argument-ext-desc-t` instead.

.. doxygenstruct:: ze_mutable_kernel_argument_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-mutable-group-count-exp-desc-t:

ze_mutable_group_count_exp_desc_t
---------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-group-count-ext-desc-t` instead.

.. doxygenstruct:: ze_mutable_group_count_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-mutable-group-size-exp-desc-t:

ze_mutable_group_size_exp_desc_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-group-size-ext-desc-t` instead.

.. doxygenstruct:: ze_mutable_group_size_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-mutable-global-offset-exp-desc-t:

ze_mutable_global_offset_exp_desc_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-global-offset-ext-desc-t` instead.

.. doxygenstruct:: ze_mutable_global_offset_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-mutable-graph-argument-exp-desc-t:

ze_mutable_graph_argument_exp_desc_t
------------------------------------

.. rst-class:: api-version

*Added in version 1.10*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ze-mutable-graph-argument-ext-desc-t` instead.

.. doxygenstruct:: ze_mutable_graph_argument_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

