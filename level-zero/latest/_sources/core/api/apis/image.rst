============================================================
Image
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Image Handles
=============


.. _ze-image-handle-t:

ze_image_handle_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeImageCreate`, :ref:`zeImageViewCreateExt`, :ref:`zeImageViewCreateExp`
   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-ze-image-handle-t-3"><span class="api-usage-links">` :ref:`zeCommandListAppendImageCopy`, :ref:`zeCommandListAppendImageCopyRegion`, :ref:`zeCommandListAppendImageCopyToMemory`, :ref:`zeCommandListAppendImageCopyFromMemory`, :ref:`zeImageDestroy`, :ref:`zeContextMakeImageResident`, :ref:`zeContextEvictImage`, :ref:`zeImageGetMemoryPropertiesExp`, :ref:`zeImageViewCreateExt`, :ref:`zeImageViewCreateExp`, :ref:`zeCommandListAppendImageCopyToMemoryExt`, :ref:`zeCommandListAppendImageCopyFromMemoryExt`, :ref:`zeImageGetAllocPropertiesExt`, :ref:`zeImageGetDeviceOffsetExp` :raw-html:`</span><label for="usage-ze-image-handle-t-3"><span class="more">Show all 14</span><span class="less">Show less</span></label></span>`
   | **See also:** :ref:`Images (Programming Guide) <Images>`

.. cpp:type:: ze_image_handle_t

    Handle of driver's image object.



Image Functions
===============


.. _zeImageGetProperties:

zeImageGetProperties
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeImageGetProperties
    :project: LevelZero


.. _zeImageCreate:

zeImageCreate
-------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeImageCreate
    :project: LevelZero


.. _zeImageDestroy:

zeImageDestroy
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeImageDestroy
    :project: LevelZero



Image Enums
===========


.. _ze-image-flags-t:

ze_image_flags_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-image-desc-t`

.. doxygentypedef:: ze_image_flags_t
    :project: LevelZero

.. doxygenenum:: ze_image_flag_t
    :project: LevelZero


.. _ze-image-type-t:

ze_image_type_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-image-desc-t`

.. doxygenenum:: ze_image_type_t
    :project: LevelZero


.. _ze-image-format-layout-t:

ze_image_format_layout_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-image-format-t`

.. doxygenenum:: ze_image_format_layout_t
    :project: LevelZero


.. _ze-image-format-type-t:

ze_image_format_type_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-image-format-t`

.. doxygenenum:: ze_image_format_type_t
    :project: LevelZero


.. _ze-image-format-swizzle-t:

ze_image_format_swizzle_t
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-image-format-t`

.. doxygenenum:: ze_image_format_swizzle_t
    :project: LevelZero


.. _ze-image-sampler-filter-flags-t:

ze_image_sampler_filter_flags_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-image-properties-t`

.. doxygentypedef:: ze_image_sampler_filter_flags_t
    :project: LevelZero

.. doxygenenum:: ze_image_sampler_filter_flag_t
    :project: LevelZero


 
Image Structures
================


.. _ze-image-format-t:

ze_image_format_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-image-desc-t`

.. doxygenstruct:: ze_image_format_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-image-desc-t:

ze_image_desc_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeImageGetProperties`, :ref:`zeImageCreate`, :ref:`zeImageViewCreateExt`, :ref:`zeImageViewCreateExp`
   | **pNext may point to:** :ref:`ze-external-memory-export-desc-t`, :ref:`ze-external-memory-import-fd-t`, :ref:`ze-external-memory-import-win32-handle-t`, :ref:`ze-srgb-ext-desc-t`, :ref:`ze-memory-compression-hints-ext-desc-t`, :ref:`ze-image-bindless-exp-desc-t`, :ref:`ze-image-pitched-exp-desc-t`

.. doxygenstruct:: ze_image_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-image-properties-t:

ze_image_properties_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeImageGetProperties`
   | **pNext may point to:** :ref:`ze-image-format-support-ext-properties-t`

.. doxygenstruct:: ze_image_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

