============================================================
Standby
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Standby Handles
===============


.. _zes-standby-handle-t:

zes_standby_handle_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumStandbyDomains`
   | **Used by:** :ref:`zesStandbyGetProperties`, :ref:`zesStandbyGetMode`, :ref:`zesStandbySetMode`
   | **See also:** :ref:`Operations on standby domains (Programming Guide) <Standby>`

.. cpp:type:: zes_standby_handle_t

    Handle for a Sysman device standby control.



Standby Functions
=================


.. _zesStandbyGetProperties:

zesStandbyGetProperties
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesStandbyGetProperties
    :project: LevelZero


.. _zesStandbyGetMode:

zesStandbyGetMode
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesStandbyGetMode
    :project: LevelZero


.. _zesStandbySetMode:

zesStandbySetMode
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesStandbySetMode
    :project: LevelZero



Standby Enums
=============


.. _zes-standby-type-t:

zes_standby_type_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-standby-properties-t`

.. doxygenenum:: zes_standby_type_t
    :project: LevelZero


.. _zes-standby-promo-mode-t:

zes_standby_promo_mode_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesStandbyGetMode`, :ref:`zesStandbySetMode`

.. doxygenenum:: zes_standby_promo_mode_t
    :project: LevelZero


 
Standby Structures
==================


.. _zes-standby-properties-t:

zes_standby_properties_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesStandbyGetProperties`

.. doxygenstruct:: zes_standby_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

