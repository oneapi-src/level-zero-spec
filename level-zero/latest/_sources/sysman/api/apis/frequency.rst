============================================================
Frequency
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Frequency Handles
=================


.. _zes-freq-handle-t:

zes_freq_handle_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumFrequencyDomains`
   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-zes-freq-handle-t-3"><span class="api-usage-links">` :ref:`zesFrequencyGetProperties`, :ref:`zesFrequencyGetAvailableClocks`, :ref:`zesFrequencyGetRange`, :ref:`zesFrequencySetRange`, :ref:`zesFrequencyGetState`, :ref:`zesFrequencyGetThrottleTime`, :ref:`zesFrequencyOcGetCapabilities`, :ref:`zesFrequencyOcGetFrequencyTarget`, :ref:`zesFrequencyOcSetFrequencyTarget`, :ref:`zesFrequencyOcGetVoltageTarget`, :ref:`zesFrequencyOcSetVoltageTarget`, :ref:`zesFrequencyOcSetMode`, :ref:`zesFrequencyOcGetMode`, :ref:`zesFrequencyOcGetIccMax`, :ref:`zesFrequencyOcSetIccMax`, :ref:`zesFrequencyOcGetTjMax`, :ref:`zesFrequencyOcSetTjMax` :raw-html:`</span><label for="usage-zes-freq-handle-t-3"><span class="more">Show all 17</span><span class="less">Show less</span></label></span>`
   | **See also:** :ref:`Operations on frequency domains (Programming Guide) <Frequency>`

.. cpp:type:: zes_freq_handle_t

    Handle for a Sysman device frequency domain.



Frequency Functions
===================


.. _zesFrequencyGetProperties:

zesFrequencyGetProperties
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesFrequencyGetProperties
    :project: LevelZero


.. _zesFrequencyGetAvailableClocks:

zesFrequencyGetAvailableClocks
------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesFrequencyGetAvailableClocks
    :project: LevelZero


.. _zesFrequencyGetRange:

zesFrequencyGetRange
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesFrequencyGetRange
    :project: LevelZero


.. _zesFrequencySetRange:

zesFrequencySetRange
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesFrequencySetRange
    :project: LevelZero


.. _zesFrequencyGetState:

zesFrequencyGetState
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesFrequencyGetState
    :project: LevelZero


.. _zesFrequencyGetThrottleTime:

zesFrequencyGetThrottleTime
---------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesFrequencyGetThrottleTime
    :project: LevelZero



Frequency Enums
===============


.. _zes-freq-throttle-reason-flags-t:

zes_freq_throttle_reason_flags_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-freq-state-t`

.. doxygentypedef:: zes_freq_throttle_reason_flags_t
    :project: LevelZero

.. doxygenenum:: zes_freq_throttle_reason_flag_t
    :project: LevelZero


 
Frequency Structures
====================


.. _zes-freq-properties-t:

zes_freq_properties_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesFrequencyGetProperties`

.. doxygenstruct:: zes_freq_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-freq-range-t:

zes_freq_range_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesFrequencyGetRange`, :ref:`zesFrequencySetRange`

.. doxygenstruct:: zes_freq_range_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-freq-state-t:

zes_freq_state_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesFrequencyGetState`

.. doxygenstruct:: zes_freq_state_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-freq-throttle-time-t:

zes_freq_throttle_time_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesFrequencyGetThrottleTime`

.. doxygenstruct:: zes_freq_throttle_time_t
    :project: LevelZero
    :members:
    :undoc-members:

