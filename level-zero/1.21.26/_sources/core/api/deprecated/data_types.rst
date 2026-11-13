============================================================
Data Types - Deprecated
============================================================
oneAPI Level Zero Specification - Version 1.21.26






Data Types - Deprecated Enums
=============================


.. _ze-relaxed-allocation-limits-exp-version-t:

ze_relaxed_allocation_limits_exp_version_t
------------------------------------------

.. rst-class:: api-version

*Added in version 1.1*

.. rst-class:: api-deprecated

**Deprecated** since 1.17. Use :ref:`ZE_extension_relaxed_allocation_limits <ZE_extension_relaxed_allocation_limits>` instead.

.. container:: api-usage

   | **Extension:** :ref:`ZE_experimental_relaxed_allocation_limits`

.. doxygenenum:: ze_relaxed_allocation_limits_exp_version_t
    :project: LevelZero


.. _ze-image-view-exp-version-t:

ze_image_view_exp_version_t
---------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. rst-class:: api-deprecated

**Deprecated** since 1.5. Use :ref:`ZE_extension_image_view <ZE_extension_image_view>` instead.

.. container:: api-usage

   | **Extension:** :ref:`ZE_experimental_image_view`

.. doxygenenum:: ze_image_view_exp_version_t
    :project: LevelZero


.. _ze-image-view-planar-exp-version-t:

ze_image_view_planar_exp_version_t
----------------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. rst-class:: api-deprecated

**Deprecated** since 1.5. Use :ref:`ZE_extension_image_view_planar <ZE_extension_image_view_planar>` instead.

.. container:: api-usage

   | **Extension:** :ref:`ZE_experimental_image_view_planar`

.. doxygenenum:: ze_image_view_planar_exp_version_t
    :project: LevelZero


.. _ze-rtas-builder-exp-version-t:

ze_rtas_builder_exp_version_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ZE_extension_rtas <ZE_extension_rtas>` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-builder-exp-desc-t`
   | **Extension:** :ref:`ZE_experimental_rtas_builder`

.. doxygenenum:: ze_rtas_builder_exp_version_t
    :project: LevelZero


.. _ze-event-pool-counter-based-exp-version-t:

ze_event_pool_counter_based_exp_version_t
-----------------------------------------

.. rst-class:: api-version

*Added in version 1.8*

.. rst-class:: api-deprecated

**Deprecated** since 1.15. Use :ref:`zeEventCounterBasedCreate` instead.

.. container:: api-usage

   | **Extension:** :ref:`ZE_experimental_event_pool_counter_based`

.. doxygenenum:: ze_event_pool_counter_based_exp_version_t
    :project: LevelZero


.. _ze-command-list-clone-exp-version-t:

ze_command_list_clone_exp_version_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.17. Mutable command lists replace command list cloning. Use :ref:`ZE_extension_mutable_command_list <ZE_extension_mutable_command_list>` instead.

.. container:: api-usage

   | **Extension:** :ref:`ZE_experimental_command_list_clone`

.. doxygenenum:: ze_command_list_clone_exp_version_t
    :project: LevelZero


.. _ze-immediate-command-list-append-exp-version-t:

ze_immediate_command_list_append_exp_version_t
----------------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.16. Use :ref:`zeCommandListImmediateAppendCommandListsWithParameters` instead.

.. container:: api-usage

   | **Extension:** :ref:`ZE_experimental_immediate_command_list_append`

.. doxygenenum:: ze_immediate_command_list_append_exp_version_t
    :project: LevelZero


.. _ze-mutable-command-list-exp-version-t:

ze_mutable_command_list_exp_version_t
-------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.20. Use :ref:`ZE_extension_mutable_command_list <ZE_extension_mutable_command_list>` instead.

.. container:: api-usage

   | **Extension:** :ref:`ZE_experimental_mutable_command_list`

.. doxygenenum:: ze_mutable_command_list_exp_version_t
    :project: LevelZero


.. _ze-power-saving-hint-exp-version-t:

ze_power_saving_hint_exp_version_t
----------------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. rst-class:: api-deprecated

**Deprecated** since 1.18. Use :ref:`ZE_extension_power_saving_hint <ZE_extension_power_saving_hint>` instead.

.. container:: api-usage

   | **Extension:** :ref:`ZE_experimental_power_saving_hint`

.. doxygenenum:: ze_power_saving_hint_exp_version_t
    :project: LevelZero


 
Data Types - Deprecated Structures
==================================


.. _ze-rtas-float3-exp-t:

ze_rtas_float3_exp_t
--------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-float3-ext-t` instead.

.. container:: api-usage

   | **Member of:** :ref:`ze-rtas-aabb-exp-t`
   | **Format value:** :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_FLOAT3 <ze-rtas-builder-input-data-format-exp-t>`
   | **Buffer data for:** :ref:`ze-rtas-builder-triangles-geometry-info-exp-t`, :ref:`ze-rtas-builder-quads-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_float3_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-transform-float3x4-column-major-exp-t:

ze_rtas_transform_float3x4_column_major_exp_t
---------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-transform-float3x4-column-major-ext-t` instead.

.. container:: api-usage

   | **Format value:** :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_FLOAT3X4_COLUMN_MAJOR <ze-rtas-builder-input-data-format-exp-t>`
   | **Buffer data for:** :ref:`ze-rtas-builder-instance-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_transform_float3x4_column_major_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-transform-float3x4-aligned-column-major-exp-t:

ze_rtas_transform_float3x4_aligned_column_major_exp_t
-----------------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-transform-float3x4-aligned-column-major-ext-t` instead.

.. container:: api-usage

   | **Format value:** :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_FLOAT3X4_ALIGNED_COLUMN_MAJOR <ze-rtas-builder-input-data-format-exp-t>`
   | **Buffer data for:** :ref:`ze-rtas-builder-instance-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_transform_float3x4_aligned_column_major_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-transform-float3x4-row-major-exp-t:

ze_rtas_transform_float3x4_row_major_exp_t
------------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-transform-float3x4-row-major-ext-t` instead.

.. container:: api-usage

   | **Format value:** :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_FLOAT3X4_ROW_MAJOR <ze-rtas-builder-input-data-format-exp-t>`
   | **Buffer data for:** :ref:`ze-rtas-builder-instance-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_transform_float3x4_row_major_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-aabb-exp-t:

ze_rtas_aabb_exp_t
------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-aabb-ext-t` instead.

.. container:: api-usage

   | **Used by:** :ref:`zeRTASBuilderBuildExp`
   | **Member of:** :ref:`ze-rtas-geometry-aabbs-exp-cb-params-t`, :ref:`ze-rtas-builder-instance-geometry-info-exp-t`
   | **Format value:** :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_AABB <ze-rtas-builder-input-data-format-exp-t>`

.. doxygenstruct:: ze_rtas_aabb_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-triangle-indices-uint32-exp-t:

ze_rtas_triangle_indices_uint32_exp_t
-------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-triangle-indices-uint32-ext-t` instead.

.. container:: api-usage

   | **Format value:** :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_TRIANGLE_INDICES_UINT32 <ze-rtas-builder-input-data-format-exp-t>`
   | **Buffer data for:** :ref:`ze-rtas-builder-triangles-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_triangle_indices_uint32_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-quad-indices-uint32-exp-t:

ze_rtas_quad_indices_uint32_exp_t
---------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-quad-indices-uint32-ext-t` instead.

.. container:: api-usage

   | **Format value:** :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_QUAD_INDICES_UINT32 <ze-rtas-builder-input-data-format-exp-t>`
   | **Buffer data for:** :ref:`ze-rtas-builder-quads-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_quad_indices_uint32_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-rtas-geometry-aabbs-exp-cb-params-t:

ze_rtas_geometry_aabbs_exp_cb_params_t
--------------------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. rst-class:: api-deprecated

**Deprecated** since 1.13. Use :ref:`ze-rtas-geometry-aabbs-ext-cb-params-t` instead.

.. container:: api-usage

   | **Passed to callback in:** :ref:`ze-rtas-builder-procedural-geometry-info-exp-t`

.. doxygenstruct:: ze_rtas_geometry_aabbs_exp_cb_params_t
    :project: LevelZero
    :members:
    :undoc-members:

