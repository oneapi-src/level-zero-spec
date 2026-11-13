============================================================
RTAS Parallel Operation - Extensions
============================================================
oneAPI Level Zero Specification - Version 1.21.26


RTAS Parallel Operation - Extension Handles
===========================================


.. _ze-rtas-parallel-operation-ext-handle-t:

ze_rtas_parallel_operation_ext_handle_t
---------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Obtained from:** :ref:`zeRTASParallelOperationCreateExt`
   | **Used by:** :ref:`zeRTASBuilderBuildExt`, :ref:`zeRTASParallelOperationGetPropertiesExt`, :ref:`zeRTASParallelOperationJoinExt`, :ref:`zeRTASParallelOperationDestroyExt`
   | **See also:** :doc:`../../EXT_RTAS`

.. cpp:type:: ze_rtas_parallel_operation_ext_handle_t

    Handle of ray tracing acceleration structure builder parallel operation object.



RTAS Parallel Operation - Extension Functions
=============================================


.. _zeRTASParallelOperationCreateExt:

zeRTASParallelOperationCreateExt
--------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeRTASParallelOperationCreateExt
    :project: LevelZero


.. _zeRTASParallelOperationGetPropertiesExt:

zeRTASParallelOperationGetPropertiesExt
---------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeRTASParallelOperationGetPropertiesExt
    :project: LevelZero


.. _zeRTASParallelOperationJoinExt:

zeRTASParallelOperationJoinExt
------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeRTASParallelOperationJoinExt
    :project: LevelZero


.. _zeRTASParallelOperationDestroyExt:

zeRTASParallelOperationDestroyExt
---------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeRTASParallelOperationDestroyExt
    :project: LevelZero



RTAS Parallel Operation - Extension Enums
=========================================


.. _ze-rtas-parallel-operation-ext-flags-t:

ze_rtas_parallel_operation_ext_flags_t
--------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-parallel-operation-ext-properties-t`

.. doxygentypedef:: ze_rtas_parallel_operation_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_parallel_operation_ext_flag_t
    :project: LevelZero


 
RTAS Parallel Operation - Extension Structures
==============================================


.. _ze-rtas-parallel-operation-ext-properties-t:

ze_rtas_parallel_operation_ext_properties_t
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Used by:** :ref:`zeRTASParallelOperationGetPropertiesExt`

.. doxygenstruct:: ze_rtas_parallel_operation_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

