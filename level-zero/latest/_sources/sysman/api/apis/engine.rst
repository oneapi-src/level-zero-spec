============================================================
Engine
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Engine Handles
==============


.. _zes-engine-handle-t:

zes_engine_handle_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumEngineGroups`
   | **Used by:** :ref:`zesEngineGetProperties`, :ref:`zesEngineGetActivity`, :ref:`zesEngineGetActivityExt`
   | **See also:** :ref:`Operations on engine groups (Programming Guide) <Engines>`

.. cpp:type:: zes_engine_handle_t

    Handle for a Sysman device engine group.



Engine Functions
================


.. _zesEngineGetProperties:

zesEngineGetProperties
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesEngineGetProperties
    :project: LevelZero


.. _zesEngineGetActivity:

zesEngineGetActivity
--------------------

.. rst-class:: api-version

*Added in version 1.7*

.. doxygenfunction:: zesEngineGetActivity
    :project: LevelZero



Engine Enums
============


.. _zes-engine-group-t:

zes_engine_group_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-engine-properties-t`, :ref:`zes-vf-util-engine-exp-t`, :ref:`zes-vf-util-engine-exp2-t`

.. doxygenenum:: zes_engine_group_t
    :project: LevelZero


 
Engine Structures
=================


.. _zes-engine-properties-t:

zes_engine_properties_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesEngineGetProperties`
   | **pNext may point to:** :ref:`zes-engine-ext-properties-t`

.. doxygenstruct:: zes_engine_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-engine-stats-t:

zes_engine_stats_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesEngineGetActivity`, :ref:`zesEngineGetActivityExt`

.. doxygenstruct:: zes_engine_stats_t
    :project: LevelZero
    :members:
    :undoc-members:

