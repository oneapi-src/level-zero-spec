============================================================
Scheduler
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Scheduler Handles
=================


.. _zes-sched-handle-t:

zes_sched_handle_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumSchedulers`
   | **Used by:** :ref:`zesSchedulerGetProperties`, :ref:`zesSchedulerGetCurrentMode`, :ref:`zesSchedulerGetTimeoutModeProperties`, :ref:`zesSchedulerGetTimesliceModeProperties`, :ref:`zesSchedulerSetTimeoutMode`, :ref:`zesSchedulerSetTimesliceMode`, :ref:`zesSchedulerSetExclusiveMode`, :ref:`zesSchedulerSetComputeUnitDebugMode`
   | **See also:** :ref:`Scheduler operations (Programming Guide) <Scheduler>`

.. cpp:type:: zes_sched_handle_t

    Handle for a Sysman device scheduler queue.



Scheduler Functions
===================


.. _zesSchedulerGetProperties:

zesSchedulerGetProperties
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesSchedulerGetProperties
    :project: LevelZero


.. _zesSchedulerGetCurrentMode:

zesSchedulerGetCurrentMode
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesSchedulerGetCurrentMode
    :project: LevelZero


.. _zesSchedulerGetTimeoutModeProperties:

zesSchedulerGetTimeoutModeProperties
------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesSchedulerGetTimeoutModeProperties
    :project: LevelZero


.. _zesSchedulerGetTimesliceModeProperties:

zesSchedulerGetTimesliceModeProperties
--------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesSchedulerGetTimesliceModeProperties
    :project: LevelZero


.. _zesSchedulerSetTimeoutMode:

zesSchedulerSetTimeoutMode
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesSchedulerSetTimeoutMode
    :project: LevelZero


.. _zesSchedulerSetTimesliceMode:

zesSchedulerSetTimesliceMode
----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesSchedulerSetTimesliceMode
    :project: LevelZero


.. _zesSchedulerSetExclusiveMode:

zesSchedulerSetExclusiveMode
----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesSchedulerSetExclusiveMode
    :project: LevelZero




 
Scheduler Structures
====================


.. _zes-sched-properties-t:

zes_sched_properties_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesSchedulerGetProperties`

.. doxygenstruct:: zes_sched_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

