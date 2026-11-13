============================================================
Image - Experimental
============================================================
oneAPI Level Zero Specification - Version 1.21.26




Image - Experimental Functions
==============================


.. _zeImageGetMemoryPropertiesExp:

zeImageGetMemoryPropertiesExp
-----------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. doxygenfunction:: zeImageGetMemoryPropertiesExp
    :project: LevelZero


.. _zeImageGetDeviceOffsetExp:

zeImageGetDeviceOffsetExp
-------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeImageGetDeviceOffsetExp
    :project: LevelZero



Image - Experimental Enums
==========================


.. _ze-image-bindless-exp-flags-t:

ze_image_bindless_exp_flags_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. container:: api-usage

   | **Member of:** :ref:`ze-image-bindless-exp-desc-t`

.. doxygentypedef:: ze_image_bindless_exp_flags_t
    :project: LevelZero

.. doxygenenum:: ze_image_bindless_exp_flag_t
    :project: LevelZero


 
Image - Experimental Structures
===============================


.. _ze-image-memory-properties-exp-t:

ze_image_memory_properties_exp_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. container:: api-usage

   | **Used by:** :ref:`zeImageGetMemoryPropertiesExp`

.. doxygenstruct:: ze_image_memory_properties_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-image-bindless-exp-desc-t:

ze_image_bindless_exp_desc_t
----------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. container:: api-usage

   | **pNext may point to:** :ref:`ze-sampler-desc-t`
   | **Goes in pNext of:** :ref:`ze-image-desc-t`

.. doxygenstruct:: ze_image_bindless_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-image-pitched-exp-desc-t:

ze_image_pitched_exp_desc_t
---------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. container:: api-usage

   | **pNext may point to:** :ref:`ze-custom-pitch-exp-desc-t`
   | **Goes in pNext of:** :ref:`ze-image-desc-t`

.. doxygenstruct:: ze_image_pitched_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

