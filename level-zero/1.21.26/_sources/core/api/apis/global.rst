============================================================
Global
============================================================
oneAPI Level Zero Specification - Version 1.21.26




Global Functions
================


.. _zeInitDrivers:

zeInitDrivers
-------------

.. rst-class:: api-version

*Added in version 1.10*

.. doxygenfunction:: zeInitDrivers
    :project: LevelZero



Global Enums
============


.. _ze-init-flags-t:

ze_init_flags_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeInit`

.. doxygentypedef:: ze_init_flags_t
    :project: LevelZero

.. doxygenenum:: ze_init_flag_t
    :project: LevelZero


.. _ze-init-driver-type-flags-t:

ze_init_driver_type_flags_t
---------------------------

.. rst-class:: api-version

*Added in version 1.10*

.. container:: api-usage

   | **Member of:** :ref:`ze-init-driver-type-desc-t`

.. doxygentypedef:: ze_init_driver_type_flags_t
    :project: LevelZero

.. doxygenenum:: ze_init_driver_type_flag_t
    :project: LevelZero


 
Global Structures
=================


.. _ze-init-driver-type-desc-t:

ze_init_driver_type_desc_t
--------------------------

.. rst-class:: api-version

*Added in version 1.10*

.. container:: api-usage

   | **Used by:** :ref:`zeInitDrivers`
   | **pNext may point to:** :ref:`ze-init-driver-app-version-ext-desc-t`, :ref:`ze-init-driver-properties-ext-desc-t`

.. doxygenstruct:: ze_init_driver_type_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

