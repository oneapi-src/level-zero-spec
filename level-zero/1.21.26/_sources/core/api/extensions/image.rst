============================================================
Image - Extensions
============================================================
oneAPI Level Zero Specification - Version 1.21.26




Image - Extension Functions
===========================


.. _zeImageGetAllocPropertiesExt:

zeImageGetAllocPropertiesExt
----------------------------

.. rst-class:: api-version

*Added in version 1.3*

.. doxygenfunction:: zeImageGetAllocPropertiesExt
    :project: LevelZero


.. _zeImageViewCreateExt:

zeImageViewCreateExt
--------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zeImageViewCreateExt
    :project: LevelZero




 
Image - Extension Structures
============================


.. _ze-image-view-planar-ext-desc-t:

ze_image_view_planar_ext_desc_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenstruct:: ze_image_view_planar_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-srgb-ext-desc-t:

ze_srgb_ext_desc_t
------------------

.. rst-class:: api-version

*Added in version 1.3*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-image-desc-t`

.. doxygenstruct:: ze_srgb_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-image-allocation-ext-properties-t:

ze_image_allocation_ext_properties_t
------------------------------------

.. rst-class:: api-version

*Added in version 1.3*

.. container:: api-usage

   | **Used by:** :ref:`zeImageGetAllocPropertiesExt`
   | **pNext may point to:** :ref:`ze-external-memory-export-fd-t`, :ref:`ze-external-memory-export-win32-handle-t`

.. doxygenstruct:: ze_image_allocation_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-image-format-support-ext-properties-t:

ze_image_format_support_ext_properties_t
----------------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-image-properties-t`

.. doxygenstruct:: ze_image_format_support_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

