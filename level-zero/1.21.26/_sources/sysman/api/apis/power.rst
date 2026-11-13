============================================================
Power
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Power Handles
=============


.. _zes-pwr-handle-t:

zes_pwr_handle_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumPowerDomains`, :ref:`zesDeviceGetCardPowerDomain`
   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-zes-pwr-handle-t-3"><span class="api-usage-links">` :ref:`zesPowerGetProperties`, :ref:`zesPowerGetEnergyCounter`, :ref:`zesPowerGetLimits`, :ref:`zesPowerSetLimits`, :ref:`zesPowerGetEnergyThreshold`, :ref:`zesPowerSetEnergyThreshold`, :ref:`zesPowerGetUsage`, :ref:`zesPowerGetLimitsExt`, :ref:`zesPowerSetLimitsExt`, :ref:`zesPowerGetLimitsExt2`, :ref:`zesPowerSetLimitsExt2` :raw-html:`</span><label for="usage-zes-pwr-handle-t-3"><span class="more">Show all 11</span><span class="less">Show less</span></label></span>`
   | **See also:** :ref:`Operations on power domains (Programming Guide) <Power>`

.. cpp:type:: zes_pwr_handle_t

    Handle for a Sysman device power domain.



Power Functions
===============


.. _zesPowerGetProperties:

zesPowerGetProperties
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesPowerGetProperties
    :project: LevelZero


.. _zesPowerGetEnergyCounter:

zesPowerGetEnergyCounter
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesPowerGetEnergyCounter
    :project: LevelZero


.. _zesPowerGetEnergyThreshold:

zesPowerGetEnergyThreshold
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesPowerGetEnergyThreshold
    :project: LevelZero


.. _zesPowerSetEnergyThreshold:

zesPowerSetEnergyThreshold
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesPowerSetEnergyThreshold
    :project: LevelZero


.. _zesPowerGetUsage:

zesPowerGetUsage
----------------

.. rst-class:: api-version

*Added in version 1.16*

.. doxygenfunction:: zesPowerGetUsage
    :project: LevelZero


.. _zesPowerGetLimitsExt2:

zesPowerGetLimitsExt2
---------------------

.. rst-class:: api-version

*Added in version 1.16*

.. doxygenfunction:: zesPowerGetLimitsExt2
    :project: LevelZero


.. _zesPowerSetLimitsExt2:

zesPowerSetLimitsExt2
---------------------

.. rst-class:: api-version

*Added in version 1.16*

.. doxygenfunction:: zesPowerSetLimitsExt2
    :project: LevelZero



Power Enums
===========


.. _zes-power-domain-t:

zes_power_domain_t
------------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Member of:** :ref:`zes-power-ext-properties-t`, :ref:`zes-power-domain-exp-properties-t`

.. doxygenenum:: zes_power_domain_t
    :project: LevelZero


.. _zes-power-level-t:

zes_power_level_t
-----------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Member of:** :ref:`zes-power-limit-ext-desc-t`

.. doxygenenum:: zes_power_level_t
    :project: LevelZero


.. _zes-power-source-t:

zes_power_source_t
------------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Member of:** :ref:`zes-power-limit-ext-desc-t`

.. doxygenenum:: zes_power_source_t
    :project: LevelZero


.. _zes-limit-unit-t:

zes_limit_unit_t
----------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Member of:** :ref:`zes-power-limit-ext-desc-t`

.. doxygenenum:: zes_limit_unit_t
    :project: LevelZero


 
Power Structures
================


.. _zes-power-properties-t:

zes_power_properties_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesPowerGetProperties`
   | **pNext may point to:** :ref:`zes-power-ext-properties-t`, :ref:`zes-power-domain-exp-properties-t`

.. doxygenstruct:: zes_power_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-power-energy-counter-t:

zes_power_energy_counter_t
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesPowerGetEnergyCounter`

.. doxygenstruct:: zes_power_energy_counter_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-energy-threshold-t:

zes_energy_threshold_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesPowerGetEnergyThreshold`

.. doxygenstruct:: zes_energy_threshold_t
    :project: LevelZero
    :members:
    :undoc-members:

