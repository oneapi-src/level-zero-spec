============================================================
Firmware
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Firmware Handles
================


.. _zes-firmware-handle-t:

zes_firmware_handle_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumFirmwares`
   | **Used by:** :ref:`zesFirmwareGetProperties`, :ref:`zesFirmwareFlash`, :ref:`zesFirmwareGetFlashProgress`, :ref:`zesFirmwareGetConsoleLogs`, :ref:`zesFirmwareGetSecurityVersionExp`, :ref:`zesFirmwareSetSecurityVersionExp`
   | **See also:** :ref:`Operations on firmwares (Programming Guide) <Firmware>`

.. cpp:type:: zes_firmware_handle_t

    Handle for a Sysman device firmware.



Firmware Functions
==================


.. _zesFirmwareGetProperties:

zesFirmwareGetProperties
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesFirmwareGetProperties
    :project: LevelZero


.. _zesFirmwareFlash:

zesFirmwareFlash
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesFirmwareFlash
    :project: LevelZero


.. _zesFirmwareGetFlashProgress:

zesFirmwareGetFlashProgress
---------------------------

.. rst-class:: api-version

*Added in version 1.8*

.. doxygenfunction:: zesFirmwareGetFlashProgress
    :project: LevelZero


.. _zesFirmwareGetConsoleLogs:

zesFirmwareGetConsoleLogs
-------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zesFirmwareGetConsoleLogs
    :project: LevelZero




 
Firmware Structures
===================


.. _zes-firmware-properties-t:

zes_firmware_properties_t
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesFirmwareGetProperties`

.. doxygenstruct:: zes_firmware_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

