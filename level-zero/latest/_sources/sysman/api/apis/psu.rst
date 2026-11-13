============================================================
Psu
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Psu Handles
===========


.. _zes-psu-handle-t:

zes_psu_handle_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumPsus`
   | **Used by:** :ref:`zesPsuGetProperties`, :ref:`zesPsuGetState`
   | **See also:** :ref:`Operations on power supplies (Programming Guide) <PSU>`

.. cpp:type:: zes_psu_handle_t

    Handle for a Sysman device power supply.



Psu Functions
=============


.. _zesPsuGetProperties:

zesPsuGetProperties
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesPsuGetProperties
    :project: LevelZero


.. _zesPsuGetState:

zesPsuGetState
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesPsuGetState
    :project: LevelZero



Psu Enums
=========


.. _zes-psu-voltage-status-t:

zes_psu_voltage_status_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-psu-state-t`

.. doxygenenum:: zes_psu_voltage_status_t
    :project: LevelZero


 
Psu Structures
==============


.. _zes-psu-properties-t:

zes_psu_properties_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesPsuGetProperties`

.. doxygenstruct:: zes_psu_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-psu-state-t:

zes_psu_state_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesPsuGetState`

.. doxygenstruct:: zes_psu_state_t
    :project: LevelZero
    :members:
    :undoc-members:

