============================================================
Overclock
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Overclock Handles
=================


.. _zes-overclock-handle-t:

zes_overclock_handle_t
----------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumOverclockDomains`
   | **Used by:** :ref:`zesOverclockGetDomainProperties`, :ref:`zesOverclockGetDomainVFProperties`, :ref:`zesOverclockGetDomainControlProperties`, :ref:`zesOverclockGetControlCurrentValue`, :ref:`zesOverclockGetControlPendingValue`, :ref:`zesOverclockSetControlUserValue`, :ref:`zesOverclockGetControlState`, :ref:`zesOverclockGetVFPointValues`, :ref:`zesOverclockSetVFPointValues`
   | **See also:** `Frequency/Voltage overclocking (Programming Guide) <../../PROG.html#frequency-voltage-overclocking>`__

.. cpp:type:: zes_overclock_handle_t

    Handle for a Sysman device overclock domain.



Overclock Functions
===================


.. _zesOverclockGetDomainProperties:

zesOverclockGetDomainProperties
-------------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesOverclockGetDomainProperties
    :project: LevelZero


.. _zesOverclockGetDomainVFProperties:

zesOverclockGetDomainVFProperties
---------------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesOverclockGetDomainVFProperties
    :project: LevelZero


.. _zesOverclockGetDomainControlProperties:

zesOverclockGetDomainControlProperties
--------------------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesOverclockGetDomainControlProperties
    :project: LevelZero


.. _zesOverclockGetControlCurrentValue:

zesOverclockGetControlCurrentValue
----------------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesOverclockGetControlCurrentValue
    :project: LevelZero


.. _zesOverclockGetControlPendingValue:

zesOverclockGetControlPendingValue
----------------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesOverclockGetControlPendingValue
    :project: LevelZero


.. _zesOverclockSetControlUserValue:

zesOverclockSetControlUserValue
-------------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesOverclockSetControlUserValue
    :project: LevelZero


.. _zesOverclockGetControlState:

zesOverclockGetControlState
---------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesOverclockGetControlState
    :project: LevelZero


.. _zesOverclockGetVFPointValues:

zesOverclockGetVFPointValues
----------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesOverclockGetVFPointValues
    :project: LevelZero


.. _zesOverclockSetVFPointValues:

zesOverclockSetVFPointValues
----------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesOverclockSetVFPointValues
    :project: LevelZero



Overclock Enums
===============


.. _zes-overclock-control-t:

zes_overclock_control_t
-----------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Used by:** :ref:`zesOverclockGetDomainControlProperties`, :ref:`zesOverclockGetControlCurrentValue`, :ref:`zesOverclockGetControlPendingValue`, :ref:`zesOverclockSetControlUserValue`, :ref:`zesOverclockGetControlState`

.. doxygenenum:: zes_overclock_control_t
    :project: LevelZero


.. _zes-overclock-mode-t:

zes_overclock_mode_t
--------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Used by:** :ref:`zesDeviceReadOverclockState`

.. doxygenenum:: zes_overclock_mode_t
    :project: LevelZero


.. _zes-control-state-t:

zes_control_state_t
-------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Used by:** :ref:`zesOverclockGetControlState`

.. doxygenenum:: zes_control_state_t
    :project: LevelZero


.. _zes-pending-action-t:

zes_pending_action_t
--------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Used by:** :ref:`zesDeviceReadOverclockState`, :ref:`zesOverclockSetControlUserValue`, :ref:`zesOverclockGetControlState`

.. doxygenenum:: zes_pending_action_t
    :project: LevelZero


.. _zes-vf-program-type-t:

zes_vf_program_type_t
---------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Member of:** :ref:`zes-overclock-properties-t`

.. doxygenenum:: zes_vf_program_type_t
    :project: LevelZero


.. _zes-vf-type-t:

zes_vf_type_t
-------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Used by:** :ref:`zesOverclockGetVFPointValues`, :ref:`zesOverclockSetVFPointValues`

.. doxygenenum:: zes_vf_type_t
    :project: LevelZero


.. _zes-vf-array-type-t:

zes_vf_array_type_t
-------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Used by:** :ref:`zesOverclockGetVFPointValues`

.. doxygenenum:: zes_vf_array_type_t
    :project: LevelZero


 
Overclock Structures
====================


.. _zes-overclock-properties-t:

zes_overclock_properties_t
--------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Used by:** :ref:`zesOverclockGetDomainProperties`

.. doxygenstruct:: zes_overclock_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-control-property-t:

zes_control_property_t
----------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Used by:** :ref:`zesOverclockGetDomainControlProperties`

.. doxygenstruct:: zes_control_property_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-vf-property-t:

zes_vf_property_t
-----------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Used by:** :ref:`zesOverclockGetDomainVFProperties`

.. doxygenstruct:: zes_vf_property_t
    :project: LevelZero
    :members:
    :undoc-members:

