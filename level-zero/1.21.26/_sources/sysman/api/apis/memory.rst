============================================================
Memory
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Memory Handles
==============


.. _zes-mem-handle-t:

zes_mem_handle_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumMemoryModules`
   | **Used by:** :ref:`zesMemoryGetProperties`, :ref:`zesMemoryGetState`, :ref:`zesMemoryGetBandwidth`
   | **See also:** :ref:`Querying Memory Modules (Programming Guide) <Memory>`

.. cpp:type:: zes_mem_handle_t

    Handle for a Sysman device memory module.



Memory Functions
================


.. _zesMemoryGetProperties:

zesMemoryGetProperties
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesMemoryGetProperties
    :project: LevelZero


.. _zesMemoryGetState:

zesMemoryGetState
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesMemoryGetState
    :project: LevelZero


.. _zesMemoryGetBandwidth:

zesMemoryGetBandwidth
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesMemoryGetBandwidth
    :project: LevelZero



Memory Enums
============


.. _zes-mem-type-t:

zes_mem_type_t
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-mem-properties-t`

.. doxygenenum:: zes_mem_type_t
    :project: LevelZero


.. _zes-mem-loc-t:

zes_mem_loc_t
-------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-mem-properties-t`, :ref:`zes-vf-util-mem-exp2-t`

.. doxygenenum:: zes_mem_loc_t
    :project: LevelZero


.. _zes-mem-health-t:

zes_mem_health_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-mem-state-t`

.. doxygenenum:: zes_mem_health_t
    :project: LevelZero


 
Memory Structures
=================


.. _zes-mem-properties-t:

zes_mem_properties_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesMemoryGetProperties`
   | **pNext may point to:** :ref:`zes-memory-vendor-info-ext-properties-t`, :ref:`zes-mem-bandwidth-counter-bits-exp-properties-t`

.. doxygenstruct:: zes_mem_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-mem-state-t:

zes_mem_state_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesMemoryGetState`
   | **pNext may point to:** :ref:`zes-mem-page-offline-state-exp-t`

.. doxygenstruct:: zes_mem_state_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-mem-bandwidth-t:

zes_mem_bandwidth_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesMemoryGetBandwidth`

.. doxygenstruct:: zes_mem_bandwidth_t
    :project: LevelZero
    :members:
    :undoc-members:

