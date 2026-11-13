============================================================
Performance Factor
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Performance Factor Handles
==========================


.. _zes-perf-handle-t:

zes_perf_handle_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumPerformanceFactorDomains`
   | **Used by:** :ref:`zesPerformanceFactorGetProperties`, :ref:`zesPerformanceFactorGetConfig`, :ref:`zesPerformanceFactorSetConfig`
   | **See also:** :ref:`Tuning workload performance (Programming Guide) <Performance-Factor>`

.. cpp:type:: zes_perf_handle_t

    Handle for a Sysman device performance factors.



Performance Factor Functions
============================


.. _zesPerformanceFactorGetProperties:

zesPerformanceFactorGetProperties
---------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesPerformanceFactorGetProperties
    :project: LevelZero


.. _zesPerformanceFactorGetConfig:

zesPerformanceFactorGetConfig
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesPerformanceFactorGetConfig
    :project: LevelZero


.. _zesPerformanceFactorSetConfig:

zesPerformanceFactorSetConfig
-----------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesPerformanceFactorSetConfig
    :project: LevelZero




 
Performance Factor Structures
=============================


.. _zes-perf-properties-t:

zes_perf_properties_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesPerformanceFactorGetProperties`

.. doxygenstruct:: zes_perf_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

