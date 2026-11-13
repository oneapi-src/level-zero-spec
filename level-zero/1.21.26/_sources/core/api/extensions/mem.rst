============================================================
Mem - Extensions
============================================================
oneAPI Level Zero Specification - Version 1.21.26




Mem - Extension Functions
=========================


.. _zeMemFreeExt:

zeMemFreeExt
------------

.. rst-class:: api-version

*Added in version 1.3*

.. doxygenfunction:: zeMemFreeExt
    :project: LevelZero



Mem - Extension Enums
=====================


.. _ze-relaxed-allocation-limits-ext-flags-t:

ze_relaxed_allocation_limits_ext_flags_t
----------------------------------------

.. rst-class:: api-version

*Added in version 1.17*

.. container:: api-usage

   | **Member of:** :ref:`ze-relaxed-allocation-limits-ext-desc-t`

.. doxygentypedef:: ze_relaxed_allocation_limits_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_relaxed_allocation_limits_ext_flag_t
    :project: LevelZero


.. _ze-memory-compression-hints-ext-flags-t:

ze_memory_compression_hints_ext_flags_t
---------------------------------------

.. rst-class:: api-version

*Added in version 1.3*

.. container:: api-usage

   | **Member of:** :ref:`ze-memory-compression-hints-ext-desc-t`

.. doxygentypedef:: ze_memory_compression_hints_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_memory_compression_hints_ext_flag_t
    :project: LevelZero


 
Mem - Extension Structures
==========================


.. _ze-relaxed-allocation-limits-ext-desc-t:

ze_relaxed_allocation_limits_ext_desc_t
---------------------------------------

.. rst-class:: api-version

*Added in version 1.17*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-mem-alloc-desc-t`, :ref:`ze-host-mem-alloc-desc-t`

.. doxygenstruct:: ze_relaxed_allocation_limits_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-memory-compression-hints-ext-desc-t:

ze_memory_compression_hints_ext_desc_t
--------------------------------------

.. rst-class:: api-version

*Added in version 1.3*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-mem-alloc-desc-t`, :ref:`ze-host-mem-alloc-desc-t`, :ref:`ze-image-desc-t`

.. doxygenstruct:: ze_memory_compression_hints_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-memory-free-ext-desc-t:

ze_memory_free_ext_desc_t
-------------------------

.. rst-class:: api-version

*Added in version 1.3*

.. container:: api-usage

   | **Used by:** :ref:`zeMemFreeExt`

.. doxygenstruct:: ze_memory_free_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-external-memmap-sysmem-ext-desc-t:

ze_external_memmap_sysmem_ext_desc_t
------------------------------------

.. rst-class:: api-version

*Added in version 1.14*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-host-mem-alloc-desc-t`

.. doxygenstruct:: ze_external_memmap_sysmem_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-ipc-mem-handle-type-ext-desc-t:

ze_ipc_mem_handle_type_ext_desc_t
---------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. doxygenstruct:: ze_ipc_mem_handle_type_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-ipc-phys-mem-handle-range-ext-desc-t:

ze_ipc_phys_mem_handle_range_ext_desc_t
---------------------------------------

.. rst-class:: api-version

*Added in version 1.18*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`zeMemGetIpcHandleWithProperties`

.. doxygenstruct:: ze_ipc_phys_mem_handle_range_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

