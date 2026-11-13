============================================================
Device - Extensions
============================================================
oneAPI Level Zero Specification - Version 1.21.26




Device - Extension Functions
============================


.. _zeDeviceReserveCacheExt:

zeDeviceReserveCacheExt
-----------------------

.. rst-class:: api-version

*Added in version 1.2*

.. doxygenfunction:: zeDeviceReserveCacheExt
    :project: LevelZero


.. _zeDeviceSetCacheAdviceExt:

zeDeviceSetCacheAdviceExt
-------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. doxygenfunction:: zeDeviceSetCacheAdviceExt
    :project: LevelZero


.. _zeDevicePciGetPropertiesExt:

zeDevicePciGetPropertiesExt
---------------------------

.. rst-class:: api-version

*Added in version 1.3*

.. doxygenfunction:: zeDevicePciGetPropertiesExt
    :project: LevelZero


.. _zeDeviceImportExternalSemaphoreExt:

zeDeviceImportExternalSemaphoreExt
----------------------------------

.. rst-class:: api-version

*Added in version 1.12*

.. doxygenfunction:: zeDeviceImportExternalSemaphoreExt
    :project: LevelZero


.. _zeDeviceReleaseExternalSemaphoreExt:

zeDeviceReleaseExternalSemaphoreExt
-----------------------------------

.. rst-class:: api-version

*Added in version 1.12*

.. doxygenfunction:: zeDeviceReleaseExternalSemaphoreExt
    :project: LevelZero


.. _zeDeviceGetVectorWidthPropertiesExt:

zeDeviceGetVectorWidthPropertiesExt
-----------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeDeviceGetVectorWidthPropertiesExt
    :project: LevelZero



Device - Extension Enums
========================


.. _ze-device-fp-atomic-ext-flags-t:

ze_device_fp_atomic_ext_flags_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.1*

.. container:: api-usage

   | **Member of:** :ref:`ze-float-atomic-ext-properties-t`

.. doxygentypedef:: ze_device_fp_atomic_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_device_fp_atomic_ext_flag_t
    :project: LevelZero


.. _ze-cache-ext-region-t:

ze_cache_ext_region_t
---------------------

.. rst-class:: api-version

*Added in version 1.2*

.. container:: api-usage

   | **Used by:** :ref:`zeDeviceSetCacheAdviceExt`

.. doxygenenum:: ze_cache_ext_region_t
    :project: LevelZero


.. _ze-device-memory-ext-type-t:

ze_device_memory_ext_type_t
---------------------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Member of:** :ref:`ze-device-memory-ext-properties-t`

.. doxygenenum:: ze_device_memory_ext_type_t
    :project: LevelZero


.. _ze-rtas-device-ext-flags-t:

ze_rtas_device_ext_flags_t
--------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-device-ext-properties-t`

.. doxygentypedef:: ze_rtas_device_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_device_ext_flag_t
    :project: LevelZero


.. _ze-rtas-format-ext-t:

ze_rtas_format_ext_t
--------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Used by:** :ref:`zeDriverRTASFormatCompatibilityCheckExt`
   | **Member of:** :ref:`ze-rtas-device-ext-properties-t`, :ref:`ze-rtas-builder-build-op-ext-desc-t`

.. doxygenenum:: ze_rtas_format_ext_t
    :project: LevelZero


 
Device - Extension Structures
=============================


.. _ze-device-compute-dotproduct-ext-properties-t:

ze_device_compute_dotproduct_ext_properties_t
---------------------------------------------

.. rst-class:: api-version

*Added in version 1.16*

.. doxygenstruct:: ze_device_compute_dotproduct_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-float-atomic-ext-properties-t:

ze_float_atomic_ext_properties_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.1*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-module-properties-t`

.. doxygenstruct:: ze_float_atomic_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-cache-reservation-ext-desc-t:

ze_cache_reservation_ext_desc_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-cache-properties-t`

.. doxygenstruct:: ze_cache_reservation_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-eu-count-ext-t:

ze_eu_count_ext_t
-----------------

.. rst-class:: api-version

*Added in version 1.3*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-properties-t`

.. doxygenstruct:: ze_eu_count_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-pci-address-ext-t:

ze_pci_address_ext_t
--------------------

.. rst-class:: api-version

*Added in version 1.3*

.. container:: api-usage

   | **Member of:** :ref:`ze-pci-ext-properties-t`

.. doxygenstruct:: ze_pci_address_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-pci-speed-ext-t:

ze_pci_speed_ext_t
------------------

.. rst-class:: api-version

*Added in version 1.3*

.. container:: api-usage

   | **Member of:** :ref:`ze-pci-ext-properties-t`

.. doxygenstruct:: ze_pci_speed_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-pci-ext-properties-t:

ze_pci_ext_properties_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeDevicePciGetPropertiesExt`

.. doxygenstruct:: ze_pci_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-device-luid-ext-properties-t:

ze_device_luid_ext_properties_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-properties-t`

.. doxygenstruct:: ze_device_luid_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-device-memory-ext-properties-t:

ze_device_memory_ext_properties_t
---------------------------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-memory-properties-t`

.. doxygenstruct:: ze_device_memory_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-device-ip-version-ext-t:

ze_device_ip_version_ext_t
--------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-properties-t`

.. doxygenstruct:: ze_device_ip_version_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-device-cache-line-size-ext-t:

ze_device_cache_line_size_ext_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-cache-properties-t`

.. doxygenstruct:: ze_device_cache_line_size_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-device-ext-properties-t:

ze_rtas_device_ext_properties_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-properties-t`

.. doxygenstruct:: ze_rtas_device_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-device-vector-width-properties-ext-t:

ze_device_vector_width_properties_ext_t
---------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Used by:** :ref:`zeDeviceGetVectorWidthPropertiesExt`

.. doxygenstruct:: ze_device_vector_width_properties_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-device-usablemem-size-ext-properties-t:

ze_device_usablemem_size_ext_properties_t
-----------------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-properties-t`

.. doxygenstruct:: ze_device_usablemem_size_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-device-readonly-memory-ext-properties-t:

ze_device_readonly_memory_ext_properties_t
------------------------------------------

.. rst-class:: api-version

*Added in version 1.17*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-properties-t`

.. doxygenstruct:: ze_device_readonly_memory_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-device-npu-properties-ext-t:

ze_device_npu_properties_ext_t
------------------------------

.. rst-class:: api-version

*Added in version 1.18*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-device-properties-t`

.. doxygenstruct:: ze_device_npu_properties_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

