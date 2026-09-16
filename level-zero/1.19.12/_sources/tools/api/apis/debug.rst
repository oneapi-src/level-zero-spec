============================================================
Debug
============================================================
oneAPI Level Zero Specification - Version 1.19.12


Debug Functions
===============


.. _zetDebugAttach:

zetDebugAttach
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugAttach
    :project: LevelZero


.. _zetDebugDetach:

zetDebugDetach
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugDetach
    :project: LevelZero


.. _zetDebugReadEvent:

zetDebugReadEvent
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugReadEvent
    :project: LevelZero


.. _zetDebugAcknowledgeEvent:

zetDebugAcknowledgeEvent
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugAcknowledgeEvent
    :project: LevelZero


.. _zetDebugInterrupt:

zetDebugInterrupt
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugInterrupt
    :project: LevelZero


.. _zetDebugResume:

zetDebugResume
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugResume
    :project: LevelZero


.. _zetDebugReadMemory:

zetDebugReadMemory
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugReadMemory
    :project: LevelZero


.. _zetDebugWriteMemory:

zetDebugWriteMemory
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugWriteMemory
    :project: LevelZero


.. _zetDebugGetRegisterSetProperties:

zetDebugGetRegisterSetProperties
--------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugGetRegisterSetProperties
    :project: LevelZero


.. _zetDebugReadRegisters:

zetDebugReadRegisters
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugReadRegisters
    :project: LevelZero


.. _zetDebugWriteRegisters:

zetDebugWriteRegisters
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetDebugWriteRegisters
    :project: LevelZero


.. _zetDebugGetThreadRegisterSetProperties:

zetDebugGetThreadRegisterSetProperties
--------------------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zetDebugGetThreadRegisterSetProperties
    :project: LevelZero



Debug Enums
===========


.. _zet-debug-event-flags-t:

zet_debug_event_flags_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zet_debug_event_flag_t
    :project: LevelZero


.. _zet-debug-event-type-t:

zet_debug_event_type_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zet_debug_event_type_t
    :project: LevelZero


.. _zet-debug-detach-reason-t:

zet_debug_detach_reason_t
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zet_debug_detach_reason_t
    :project: LevelZero


.. _zet-debug-page-fault-reason-t:

zet_debug_page_fault_reason_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.1*

.. doxygenenum:: zet_debug_page_fault_reason_t
    :project: LevelZero


.. _zet-debug-memory-space-type-t:

zet_debug_memory_space_type_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zet_debug_memory_space_type_t
    :project: LevelZero


.. _zet-debug-regset-flags-t:

zet_debug_regset_flags_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zet_debug_regset_flag_t
    :project: LevelZero

 
Debug Structures
================


.. _zet-debug-config-t:

zet_debug_config_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zet_debug_config_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zet-debug-event-info-detached-t:

zet_debug_event_info_detached_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zet_debug_event_info_detached_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zet-debug-event-info-module-t:

zet_debug_event_info_module_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zet_debug_event_info_module_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zet-debug-event-info-thread-stopped-t:

zet_debug_event_info_thread_stopped_t
-------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zet_debug_event_info_thread_stopped_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zet-debug-event-info-page-fault-t:

zet_debug_event_info_page_fault_t
---------------------------------

.. rst-class:: api-version

*Added in version 1.1*

.. doxygenstruct:: zet_debug_event_info_page_fault_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zet-debug-event-info-t:

zet_debug_event_info_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenunion:: zet_debug_event_info_t
    :project: LevelZero


.. _zet-debug-event-t:

zet_debug_event_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zet_debug_event_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zet-debug-memory-space-desc-t:

zet_debug_memory_space_desc_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zet_debug_memory_space_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zet-debug-regset-properties-t:

zet_debug_regset_properties_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zet_debug_regset_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

