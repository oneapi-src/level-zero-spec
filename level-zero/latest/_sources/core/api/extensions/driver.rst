============================================================
Driver - Extensions
============================================================
oneAPI Level Zero Specification - Version 1.21.26




Driver - Extension Functions
============================


.. _zeDriverRTASFormatCompatibilityCheckExt:

zeDriverRTASFormatCompatibilityCheckExt
---------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeDriverRTASFormatCompatibilityCheckExt
    :project: LevelZero



Driver - Extension Enums
========================


.. _ze-driver-memory-free-policy-ext-flags-t:

ze_driver_memory_free_policy_ext_flags_t
----------------------------------------

.. rst-class:: api-version

*Added in version 1.3*

.. container:: api-usage

   | **Member of:** :ref:`ze-driver-memory-free-ext-properties-t`, :ref:`ze-memory-free-ext-desc-t`

.. doxygentypedef:: ze_driver_memory_free_policy_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_driver_memory_free_policy_ext_flag_t
    :project: LevelZero


.. _ze-driver-ddi-handle-ext-flags-t:

ze_driver_ddi_handle_ext_flags_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-driver-ddi-handles-ext-properties-t`

.. doxygentypedef:: ze_driver_ddi_handle_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_driver_ddi_handle_ext_flag_t
    :project: LevelZero


 
Driver - Extension Structures
=============================


.. _ze-driver-memory-free-ext-properties-t:

ze_driver_memory_free_ext_properties_t
--------------------------------------

.. rst-class:: api-version

*Added in version 1.3*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-driver-properties-t`

.. doxygenstruct:: ze_driver_memory_free_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-driver-ddi-handles-ext-properties-t:

ze_driver_ddi_handles_ext_properties_t
--------------------------------------

.. rst-class:: api-version

*Added in version 1.12*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-driver-properties-t`

.. doxygenstruct:: ze_driver_ddi_handles_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

