============================================================
Led
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Led Handles
===========


.. _zes-led-handle-t:

zes_led_handle_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumLeds`
   | **Used by:** :ref:`zesLedGetProperties`, :ref:`zesLedGetState`, :ref:`zesLedSetState`, :ref:`zesLedSetColor`
   | **See also:** :ref:`Operations on LEDs (Programming Guide) <LED>`

.. cpp:type:: zes_led_handle_t

    Handle for a Sysman device LED.



Led Functions
=============


.. _zesLedGetProperties:

zesLedGetProperties
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesLedGetProperties
    :project: LevelZero


.. _zesLedGetState:

zesLedGetState
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesLedGetState
    :project: LevelZero


.. _zesLedSetState:

zesLedSetState
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesLedSetState
    :project: LevelZero


.. _zesLedSetColor:

zesLedSetColor
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesLedSetColor
    :project: LevelZero




 
Led Structures
==============


.. _zes-led-properties-t:

zes_led_properties_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesLedGetProperties`

.. doxygenstruct:: zes_led_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-led-color-t:

zes_led_color_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesLedSetColor`
   | **Member of:** :ref:`zes-led-state-t`

.. doxygenstruct:: zes_led_color_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-led-state-t:

zes_led_state_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesLedGetState`

.. doxygenstruct:: zes_led_state_t
    :project: LevelZero
    :members:
    :undoc-members:

