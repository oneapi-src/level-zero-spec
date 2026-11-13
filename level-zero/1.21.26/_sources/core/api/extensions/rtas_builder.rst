============================================================
RTAS Builder - Extensions
============================================================
oneAPI Level Zero Specification - Version 1.21.26


RTAS Builder - Extension Handles
================================


.. _ze-rtas-builder-ext-handle-t:

ze_rtas_builder_ext_handle_t
----------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Obtained from:** :ref:`zeRTASBuilderCreateExt`
   | **Used by:** :ref:`zeRTASBuilderGetBuildPropertiesExt`, :ref:`zeRTASBuilderBuildExt`, :ref:`zeRTASBuilderDestroyExt`
   | **See also:** :doc:`../../EXT_RTAS`

.. cpp:type:: ze_rtas_builder_ext_handle_t

    Handle of ray tracing acceleration structure builder object.



RTAS Builder - Extension Functions
==================================


.. _zeRTASBuilderCreateExt:

zeRTASBuilderCreateExt
----------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeRTASBuilderCreateExt
    :project: LevelZero


.. _zeRTASBuilderGetBuildPropertiesExt:

zeRTASBuilderGetBuildPropertiesExt
----------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeRTASBuilderGetBuildPropertiesExt
    :project: LevelZero


.. _zeRTASBuilderBuildExt:

zeRTASBuilderBuildExt
---------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeRTASBuilderBuildExt
    :project: LevelZero


.. _zeRTASBuilderCommandListAppendCopyExt:

zeRTASBuilderCommandListAppendCopyExt
-------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeRTASBuilderCommandListAppendCopyExt
    :project: LevelZero


.. _zeRTASBuilderDestroyExt:

zeRTASBuilderDestroyExt
-----------------------

.. rst-class:: api-version

*Added in version 1.13*

.. doxygenfunction:: zeRTASBuilderDestroyExt
    :project: LevelZero



RTAS Builder - Extension Enums
==============================


.. _ze-rtas-builder-ext-flags-t:

ze_rtas_builder_ext_flags_t
---------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-ext-properties-t`

.. doxygentypedef:: ze_rtas_builder_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_builder_ext_flag_t
    :project: LevelZero


.. _ze-rtas-builder-geometry-ext-flags-t:

ze_rtas_builder_geometry_ext_flags_t
------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Packed as:** :ref:`ze-rtas-builder-packed-geometry-ext-flags-t`

.. doxygentypedef:: ze_rtas_builder_geometry_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_builder_geometry_ext_flag_t
    :project: LevelZero


.. _ze-rtas-builder-instance-ext-flags-t:

ze_rtas_builder_instance_ext_flags_t
------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Packed as:** :ref:`ze-rtas-builder-packed-instance-ext-flags-t`

.. doxygentypedef:: ze_rtas_builder_instance_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_builder_instance_ext_flag_t
    :project: LevelZero


.. _ze-rtas-builder-build-op-ext-flags-t:

ze_rtas_builder_build_op_ext_flags_t
------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-build-op-ext-desc-t`

.. doxygentypedef:: ze_rtas_builder_build_op_ext_flags_t
    :project: LevelZero

.. doxygenenum:: ze_rtas_builder_build_op_ext_flag_t
    :project: LevelZero


.. _ze-rtas-builder-build-quality-hint-ext-t:

ze_rtas_builder_build_quality_hint_ext_t
----------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-build-op-ext-desc-t`

.. doxygenenum:: ze_rtas_builder_build_quality_hint_ext_t
    :project: LevelZero


.. _ze-rtas-builder-geometry-type-ext-t:

ze_rtas_builder_geometry_type_ext_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Packed as:** :ref:`ze-rtas-builder-packed-geometry-type-ext-t`

.. doxygenenum:: ze_rtas_builder_geometry_type_ext_t
    :project: LevelZero


.. _ze-rtas-builder-input-data-format-ext-t:

ze_rtas_builder_input_data_format_ext_t
---------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Packed as:** :ref:`ze-rtas-builder-packed-input-data-format-ext-t`

.. doxygenenum:: ze_rtas_builder_input_data_format_ext_t
    :project: LevelZero


RTAS Builder - Extension Typedefs
=================================


.. _ze-rtas-builder-packed-geometry-ext-flags-t:

ze_rtas_builder_packed_geometry_ext_flags_t
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-triangles-geometry-info-ext-t`, :ref:`ze-rtas-builder-quads-geometry-info-ext-t`, :ref:`ze-rtas-builder-procedural-geometry-info-ext-t`
   | **Packed form of:** :ref:`ze-rtas-builder-geometry-ext-flags-t`

.. doxygentypedef:: ze_rtas_builder_packed_geometry_ext_flags_t
    :project: LevelZero


.. _ze-rtas-builder-packed-instance-ext-flags-t:

ze_rtas_builder_packed_instance_ext_flags_t
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-instance-geometry-info-ext-t`
   | **Packed form of:** :ref:`ze-rtas-builder-instance-ext-flags-t`

.. doxygentypedef:: ze_rtas_builder_packed_instance_ext_flags_t
    :project: LevelZero


.. _ze-rtas-builder-packed-geometry-type-ext-t:

ze_rtas_builder_packed_geometry_type_ext_t
------------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-geometry-info-ext-t`, :ref:`ze-rtas-builder-triangles-geometry-info-ext-t`, :ref:`ze-rtas-builder-quads-geometry-info-ext-t`, :ref:`ze-rtas-builder-procedural-geometry-info-ext-t`, :ref:`ze-rtas-builder-instance-geometry-info-ext-t`
   | **Packed form of:** :ref:`ze-rtas-builder-geometry-type-ext-t`

.. doxygentypedef:: ze_rtas_builder_packed_geometry_type_ext_t
    :project: LevelZero


.. _ze-rtas-builder-packed-input-data-format-ext-t:

ze_rtas_builder_packed_input_data_format_ext_t
----------------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-triangles-geometry-info-ext-t`, :ref:`ze-rtas-builder-quads-geometry-info-ext-t`, :ref:`ze-rtas-builder-instance-geometry-info-ext-t`
   | **Packed form of:** :ref:`ze-rtas-builder-input-data-format-ext-t`

.. doxygentypedef:: ze_rtas_builder_packed_input_data_format_ext_t
    :project: LevelZero

 
RTAS Builder - Extension Structures
===================================


.. _ze-rtas-builder-ext-desc-t:

ze_rtas_builder_ext_desc_t
--------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Used by:** :ref:`zeRTASBuilderCreateExt`

.. doxygenstruct:: ze_rtas_builder_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-ext-properties-t:

ze_rtas_builder_ext_properties_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Used by:** :ref:`zeRTASBuilderGetBuildPropertiesExt`

.. doxygenstruct:: ze_rtas_builder_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-geometry-info-ext-t:

ze_rtas_builder_geometry_info_ext_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-build-op-ext-desc-t`
   | **Variants:** :ref:`ze-rtas-builder-triangles-geometry-info-ext-t`, :ref:`ze-rtas-builder-quads-geometry-info-ext-t`, :ref:`ze-rtas-builder-procedural-geometry-info-ext-t`, :ref:`ze-rtas-builder-instance-geometry-info-ext-t`

.. doxygenstruct:: ze_rtas_builder_geometry_info_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-triangles-geometry-info-ext-t:

ze_rtas_builder_triangles_geometry_info_ext_t
---------------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Variant of:** :ref:`ze-rtas-builder-geometry-info-ext-t`

.. doxygenstruct:: ze_rtas_builder_triangles_geometry_info_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-quads-geometry-info-ext-t:

ze_rtas_builder_quads_geometry_info_ext_t
-----------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Variant of:** :ref:`ze-rtas-builder-geometry-info-ext-t`

.. doxygenstruct:: ze_rtas_builder_quads_geometry_info_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-procedural-geometry-info-ext-t:

ze_rtas_builder_procedural_geometry_info_ext_t
----------------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Variant of:** :ref:`ze-rtas-builder-geometry-info-ext-t`

.. doxygenstruct:: ze_rtas_builder_procedural_geometry_info_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-instance-geometry-info-ext-t:

ze_rtas_builder_instance_geometry_info_ext_t
--------------------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Variant of:** :ref:`ze-rtas-builder-geometry-info-ext-t`

.. doxygenstruct:: ze_rtas_builder_instance_geometry_info_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-builder-build-op-ext-desc-t:

ze_rtas_builder_build_op_ext_desc_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.13*

.. container:: api-usage

   | **Used by:** :ref:`zeRTASBuilderGetBuildPropertiesExt`, :ref:`zeRTASBuilderBuildExt`

.. doxygenstruct:: ze_rtas_builder_build_op_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

