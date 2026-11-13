============================================================
Physical Mem
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Physical Mem Handles
====================


.. _ze-physical-mem-handle-t:

ze_physical_mem_handle_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zePhysicalMemCreate`
   | **Used by:** :ref:`zePhysicalMemGetProperties`, :ref:`zePhysicalMemDestroy`, :ref:`zeVirtualMemMap`
   | **See also:** `Physical Memory (Programming Guide) <../../PROG.html#physical-memory>`__

.. cpp:type:: ze_physical_mem_handle_t

    Handle of physical memory object.



Physical Mem Functions
======================


.. _zePhysicalMemCreate:

zePhysicalMemCreate
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zePhysicalMemCreate
    :project: LevelZero


.. _zePhysicalMemDestroy:

zePhysicalMemDestroy
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zePhysicalMemDestroy
    :project: LevelZero


.. _zePhysicalMemGetProperties:

zePhysicalMemGetProperties
--------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. doxygenfunction:: zePhysicalMemGetProperties
    :project: LevelZero



Physical Mem Enums
==================


.. _ze-physical-mem-flags-t:

ze_physical_mem_flags_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-physical-mem-desc-t`

.. doxygentypedef:: ze_physical_mem_flags_t
    :project: LevelZero

.. doxygenenum:: ze_physical_mem_flag_t
    :project: LevelZero


 
Physical Mem Structures
=======================


.. _ze-physical-mem-desc-t:

ze_physical_mem_desc_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zePhysicalMemCreate`
   | **pNext may point to:** :ref:`ze-external-memory-export-desc-t`, :ref:`ze-external-memory-import-fd-t`, :ref:`ze-external-memory-import-win32-handle-t`

.. doxygenstruct:: ze_physical_mem_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-physical-mem-properties-t:

ze_physical_mem_properties_t
----------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. container:: api-usage

   | **Used by:** :ref:`zePhysicalMemGetProperties`
   | **pNext may point to:** :ref:`ze-external-memory-export-fd-t`, :ref:`ze-external-memory-export-win32-handle-t`

.. doxygenstruct:: ze_physical_mem_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

