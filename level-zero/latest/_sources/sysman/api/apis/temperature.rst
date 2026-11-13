============================================================
Temperature
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Temperature Handles
===================


.. _zes-temp-handle-t:

zes_temp_handle_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumTemperatureSensors`
   | **Used by:** :ref:`zesTemperatureGetProperties`, :ref:`zesTemperatureGetConfig`, :ref:`zesTemperatureSetConfig`, :ref:`zesTemperatureGetState`
   | **See also:** :ref:`Querying temperature (Programming Guide) <Temperature>`

.. cpp:type:: zes_temp_handle_t

    Handle for a Sysman device temperature sensor.



Temperature Functions
=====================


.. _zesTemperatureGetProperties:

zesTemperatureGetProperties
---------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesTemperatureGetProperties
    :project: LevelZero


.. _zesTemperatureGetConfig:

zesTemperatureGetConfig
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesTemperatureGetConfig
    :project: LevelZero


.. _zesTemperatureSetConfig:

zesTemperatureSetConfig
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesTemperatureSetConfig
    :project: LevelZero


.. _zesTemperatureGetState:

zesTemperatureGetState
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesTemperatureGetState
    :project: LevelZero



Temperature Enums
=================


.. _zes-temp-sensors-t:

zes_temp_sensors_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-temp-properties-t`

.. doxygenenum:: zes_temp_sensors_t
    :project: LevelZero


 
Temperature Structures
======================


.. _zes-temp-properties-t:

zes_temp_properties_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesTemperatureGetProperties`

.. doxygenstruct:: zes_temp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-temp-threshold-t:

zes_temp_threshold_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-temp-config-t`

.. doxygenstruct:: zes_temp_threshold_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-temp-config-t:

zes_temp_config_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesTemperatureGetConfig`, :ref:`zesTemperatureSetConfig`

.. doxygenstruct:: zes_temp_config_t
    :project: LevelZero
    :members:
    :undoc-members:

