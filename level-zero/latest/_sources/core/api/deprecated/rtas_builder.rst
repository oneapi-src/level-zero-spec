============================================================
RTAS Builder - Deprecated
============================================================
oneAPI Level Zero Specification - Version 1.21.26


RTAS Builder - Deprecated Handles
=================================


.. _ze-rtas-builder-exp-handle-t:

ze_rtas_builder_exp_handle_t
----------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ZE_extension_rtas <ZE_extension_rtas>` instead.

.. container:: api-usage

   | **Obtained from:** :ref:`zeRTASBuilderCreateExp`
   | **Used by:** :ref:`zeRTASBuilderGetBuildPropertiesExp`, :ref:`zeRTASBuilderBuildExp`, :ref:`zeRTASBuilderDestroyExp`
   | **See also:** :doc:`../../EXT_Exp_RTASBuilder`

.. cpp:type:: ze_rtas_builder_exp_handle_t

    Handle of ray tracing acceleration structure builder object.



RTAS Builder - Deprecated Functions
===================================


.. _zeRTASBuilderCreateExp:

zeRTASBuilderCreateExp
----------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`zeRTASBuilderCreateExt` instead.

.. doxygenfunction:: zeRTASBuilderCreateExp
    :project: LevelZero


.. _zeRTASBuilderGetBuildPropertiesExp:

zeRTASBuilderGetBuildPropertiesExp
----------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`zeRTASBuilderGetBuildPropertiesExt` instead.

.. doxygenfunction:: zeRTASBuilderGetBuildPropertiesExp
    :project: LevelZero


.. _zeRTASBuilderBuildExp:

zeRTASBuilderBuildExp
---------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`zeRTASBuilderBuildExt` instead.

.. doxygenfunction:: zeRTASBuilderBuildExp
    :project: LevelZero


.. _zeRTASBuilderDestroyExp:

zeRTASBuilderDestroyExp
-----------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`zeRTASBuilderDestroyExt` instead.

.. doxygenfunction:: zeRTASBuilderDestroyExp
    :project: LevelZero



RTAS Builder - Deprecated Enums
===============================


.. _ze-rtas-builder-exp-flags-t:

ze_rtas_builder_exp_flags_t
---------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-ext-flags-t` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-exp-properties-t`

.. doxygentypedef:: ze_rtas_builder_exp_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_builder_exp_flag_t
    :project: LevelZero


.. _ze-rtas-builder-geometry-exp-flags-t:

ze_rtas_builder_geometry_exp_flags_t
------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-geometry-ext-flags-t` instead.

.. container:: api-usage

   | **Packed as:** :ref:`ze-rtas-builder-packed-geometry-exp-flags-t`

.. doxygentypedef:: ze_rtas_builder_geometry_exp_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_builder_geometry_exp_flag_t
    :project: LevelZero


.. _ze-rtas-builder-instance-exp-flags-t:

ze_rtas_builder_instance_exp_flags_t
------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-instance-ext-flags-t` instead.

.. container:: api-usage

   | **Packed as:** :ref:`ze-rtas-builder-packed-instance-exp-flags-t`

.. doxygentypedef:: ze_rtas_builder_instance_exp_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_builder_instance_exp_flag_t
    :project: LevelZero


.. _ze-rtas-builder-build-op-exp-flags-t:

ze_rtas_builder_build_op_exp_flags_t
------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-build-op-ext-flags-t` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-build-op-exp-desc-t`

.. doxygentypedef:: ze_rtas_builder_build_op_exp_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_builder_build_op_exp_flag_t
    :project: LevelZero


.. _ze-rtas-builder-build-quality-hint-exp-t:

ze_rtas_builder_build_quality_hint_exp_t
----------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-build-quality-hint-ext-t` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-build-op-exp-desc-t`

.. doxygenenum:: ze_rtas_builder_build_quality_hint_exp_t
    :project: LevelZero


.. _ze-rtas-builder-geometry-type-exp-t:

ze_rtas_builder_geometry_type_exp_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-geometry-type-ext-t` instead.

.. container:: api-usage

   | **Packed as:** :ref:`ze-rtas-builder-packed-geometry-type-exp-t`

.. doxygenenum:: ze_rtas_builder_geometry_type_exp_t
    :project: LevelZero


.. _ze-rtas-builder-input-data-format-exp-t:

ze_rtas_builder_input_data_format_exp_t
---------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-input-data-format-ext-t` instead.

.. container:: api-usage

   | **Packed as:** :ref:`ze-rtas-builder-packed-input-data-format-exp-t`

.. doxygenenum:: ze_rtas_builder_input_data_format_exp_t
    :project: LevelZero


RTAS Builder - Deprecated Typedefs
==================================


.. _ze-rtas-builder-packed-geometry-exp-flags-t:

ze_rtas_builder_packed_geometry_exp_flags_t
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ZE_extension_rtas <ZE_extension_rtas>` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-triangles-geometry-info-exp-t`, :ref:`ze-rtas-builder-quads-geometry-info-exp-t`, :ref:`ze-rtas-builder-procedural-geometry-info-exp-t`
   | **Packed form of:** :ref:`ze-rtas-builder-geometry-exp-flags-t`

.. doxygentypedef:: ze_rtas_builder_packed_geometry_exp_flags_t
    :project: LevelZero


.. _ze-rtas-builder-packed-instance-exp-flags-t:

ze_rtas_builder_packed_instance_exp_flags_t
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ZE_extension_rtas <ZE_extension_rtas>` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-instance-geometry-info-exp-t`
   | **Packed form of:** :ref:`ze-rtas-builder-instance-exp-flags-t`

.. doxygentypedef:: ze_rtas_builder_packed_instance_exp_flags_t
    :project: LevelZero


.. _ze-rtas-builder-packed-geometry-type-exp-t:

ze_rtas_builder_packed_geometry_type_exp_t
------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ZE_extension_rtas <ZE_extension_rtas>` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-geometry-info-exp-t`, :ref:`ze-rtas-builder-triangles-geometry-info-exp-t`, :ref:`ze-rtas-builder-quads-geometry-info-exp-t`, :ref:`ze-rtas-builder-procedural-geometry-info-exp-t`, :ref:`ze-rtas-builder-instance-geometry-info-exp-t`
   | **Packed form of:** :ref:`ze-rtas-builder-geometry-type-exp-t`

.. doxygentypedef:: ze_rtas_builder_packed_geometry_type_exp_t
    :project: LevelZero


.. _ze-rtas-builder-packed-input-data-format-exp-t:

ze_rtas_builder_packed_input_data_format_exp_t
----------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ZE_extension_rtas <ZE_extension_rtas>` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-triangles-geometry-info-exp-t`, :ref:`ze-rtas-builder-quads-geometry-info-exp-t`, :ref:`ze-rtas-builder-instance-geometry-info-exp-t`
   | **Packed form of:** :ref:`ze-rtas-builder-input-data-format-exp-t`

.. doxygentypedef:: ze_rtas_builder_packed_input_data_format_exp_t
    :project: LevelZero

 
RTAS Builder - Deprecated Structures
====================================


.. _ze-rtas-builder-exp-desc-t:

ze_rtas_builder_exp_desc_t
--------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-ext-desc-t` instead.

.. container:: api-usage

   | **Used by:** :ref:`zeRTASBuilderCreateExp`

.. doxygenstruct:: ze_rtas_builder_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-exp-properties-t:

ze_rtas_builder_exp_properties_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-ext-properties-t` instead.

.. container:: api-usage

   | **Used by:** :ref:`zeRTASBuilderGetBuildPropertiesExp`

.. doxygenstruct:: ze_rtas_builder_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-geometry-info-exp-t:

ze_rtas_builder_geometry_info_exp_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-geometry-info-ext-t` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-build-op-exp-desc-t`
   | **Variants:** :ref:`ze-rtas-builder-triangles-geometry-info-exp-t`, :ref:`ze-rtas-builder-quads-geometry-info-exp-t`, :ref:`ze-rtas-builder-procedural-geometry-info-exp-t`, :ref:`ze-rtas-builder-instance-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_builder_geometry_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-triangles-geometry-info-exp-t:

ze_rtas_builder_triangles_geometry_info_exp_t
---------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-triangles-geometry-info-ext-t` instead.

.. container:: api-usage

   | **Variant of:** :ref:`ze-rtas-builder-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_builder_triangles_geometry_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-quads-geometry-info-exp-t:

ze_rtas_builder_quads_geometry_info_exp_t
-----------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-quads-geometry-info-ext-t` instead.

.. container:: api-usage

   | **Variant of:** :ref:`ze-rtas-builder-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_builder_quads_geometry_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-procedural-geometry-info-exp-t:

ze_rtas_builder_procedural_geometry_info_exp_t
----------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-procedural-geometry-info-ext-t` instead.

.. container:: api-usage

   | **Variant of:** :ref:`ze-rtas-builder-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_builder_procedural_geometry_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-instance-geometry-info-exp-t:

ze_rtas_builder_instance_geometry_info_exp_t
--------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-instance-geometry-info-ext-t` instead.

.. container:: api-usage

   | **Variant of:** :ref:`ze-rtas-builder-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_builder_instance_geometry_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-build-op-exp-desc-t:

ze_rtas_builder_build_op_exp_desc_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-builder-build-op-ext-desc-t` instead.

.. container:: api-usage

   | **Used by:** :ref:`zeRTASBuilderGetBuildPropertiesExp`, :ref:`zeRTASBuilderBuildExp`

.. doxygenstruct:: ze_rtas_builder_build_op_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

