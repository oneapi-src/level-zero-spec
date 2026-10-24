============================================================
Power - Deprecated
============================================================
oneAPI Level Zero Specification - Version 1.20.41


Power - Deprecated Functions
============================


.. _zesPowerGetLimits:

zesPowerGetLimits
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.5. Use :ref:`zesPowerGetLimitsExt` instead.

.. doxygenfunction:: zesPowerGetLimits
    :project: LevelZero


.. _zesPowerSetLimits:

zesPowerSetLimits
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.5. Use :ref:`zesPowerSetLimitsExt` instead.

.. doxygenfunction:: zesPowerSetLimits
    :project: LevelZero



 
Power - Deprecated Structures
=============================


.. _zes-power-sustained-limit-t:

zes_power_sustained_limit_t
---------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.8. One descriptor per limit level replaces this struct. Use :ref:`zes-power-limit-ext-desc-t` instead.

.. doxygenstruct:: zes_power_sustained_limit_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-power-burst-limit-t:

zes_power_burst_limit_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.8. One descriptor per limit level replaces this struct. Use :ref:`zes-power-limit-ext-desc-t` instead.

.. doxygenstruct:: zes_power_burst_limit_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-power-peak-limit-t:

zes_power_peak_limit_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.8. One descriptor per limit level replaces this struct. Use :ref:`zes-power-limit-ext-desc-t` instead.

.. doxygenstruct:: zes_power_peak_limit_t
    :project: LevelZero
    :members:
    :undoc-members:

