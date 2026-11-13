============================================================
RTAS Parallel Operation - Deprecated
============================================================
oneAPI Level Zero Specification - Version 1.21.26


RTAS Parallel Operation - Deprecated Handles
============================================


.. _ze-rtas-parallel-operation-exp-handle-t:

ze_rtas_parallel_operation_exp_handle_t
---------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ZE_extension_rtas <ZE_extension_rtas>` instead.

.. container:: api-usage

   | **Obtained from:** :ref:`zeRTASParallelOperationCreateExp`
   | **Used by:** :ref:`zeRTASBuilderBuildExp`, :ref:`zeRTASParallelOperationGetPropertiesExp`, :ref:`zeRTASParallelOperationJoinExp`, :ref:`zeRTASParallelOperationDestroyExp`
   | **See also:** :doc:`../../EXT_Exp_RTASBuilder`

.. cpp:type:: ze_rtas_parallel_operation_exp_handle_t

    Handle of ray tracing acceleration structure builder parallel operation object.



RTAS Parallel Operation - Deprecated Functions
==============================================


.. _zeRTASParallelOperationCreateExp:

zeRTASParallelOperationCreateExp
--------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`zeRTASParallelOperationCreateExt` instead.

.. doxygenfunction:: zeRTASParallelOperationCreateExp
    :project: LevelZero


.. _zeRTASParallelOperationGetPropertiesExp:

zeRTASParallelOperationGetPropertiesExp
---------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`zeRTASParallelOperationGetPropertiesExt` instead.

.. doxygenfunction:: zeRTASParallelOperationGetPropertiesExp
    :project: LevelZero


.. _zeRTASParallelOperationJoinExp:

zeRTASParallelOperationJoinExp
------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`zeRTASParallelOperationJoinExt` instead.

.. doxygenfunction:: zeRTASParallelOperationJoinExp
    :project: LevelZero


.. _zeRTASParallelOperationDestroyExp:

zeRTASParallelOperationDestroyExp
---------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`zeRTASParallelOperationDestroyExt` instead.

.. doxygenfunction:: zeRTASParallelOperationDestroyExp
    :project: LevelZero



RTAS Parallel Operation - Deprecated Enums
==========================================


.. _ze-rtas-parallel-operation-exp-flags-t:

ze_rtas_parallel_operation_exp_flags_t
--------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-parallel-operation-ext-flags-t` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-parallel-operation-exp-properties-t`

.. doxygentypedef:: ze_rtas_parallel_operation_exp_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_parallel_operation_exp_flag_t
    :project: LevelZero


 
RTAS Parallel Operation - Deprecated Structures
===============================================


.. _ze-rtas-parallel-operation-exp-properties-t:

ze_rtas_parallel_operation_exp_properties_t
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-parallel-operation-ext-properties-t` instead.

.. container:: api-usage

   | **Used by:** :ref:`zeRTASParallelOperationGetPropertiesExp`

.. doxygenstruct:: ze_rtas_parallel_operation_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

