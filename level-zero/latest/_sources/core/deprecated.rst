============================================================
Core - Deprecated
============================================================

Everything below is deprecated. Use the replacement where one is listed.

The reference pages are under :doc:`Deprecated APIs <api/deprecated/index>`.

Extensions
----------

.. list-table::
   :header-rows: 1
   :widths: 28 6 28 38
   :class: deprecated-table

   * - Name
     - Since
     - Replacement
     - Notes
   * - :doc:`ZE_experimental_command_list_clone <EXT_Exp_CommandListClone>`
     - 1.17
     - :ref:`ZE_extension_mutable_command_list <ZE_extension_mutable_command_list>`
     - Mutable command lists replace command list cloning.
   * - :doc:`ZE_experimental_event_pool_counter_based <EXT_Exp_CounterBasedEventPools>`
     - 1.15
     - :ref:`zeEventCounterBasedCreate`
     - 
   * - :doc:`ZE_experimental_image_view <EXT_Exp_ImageView>`
     - 1.5
     - :ref:`ZE_extension_image_view <ZE_extension_image_view>`
     - 
   * - :doc:`ZE_experimental_image_view_planar <EXT_Exp_ImageViewPlanar>`
     - 1.5
     - :ref:`ZE_extension_image_view_planar <ZE_extension_image_view_planar>`
     - 
   * - :doc:`ZE_experimental_immediate_command_list_append <EXT_Exp_ImmediateCommandListAppend>`
     - 1.16
     - :ref:`zeCommandListImmediateAppendCommandListsWithParameters`
     - 
   * - :doc:`ZE_experimental_mutable_command_list <EXT_Exp_MutableCommandList>`
     - 1.20
     - :ref:`ZE_extension_mutable_command_list <ZE_extension_mutable_command_list>`
     - 
   * - :doc:`ZE_experimental_power_saving_hint <EXT_Exp_PowerSavingHint>`
     - 1.18
     - :ref:`ZE_extension_power_saving_hint <ZE_extension_power_saving_hint>`
     - 
   * - :doc:`ZE_experimental_relaxed_allocation_limits <EXT_Exp_RelaxedAllocLimits>`
     - 1.17
     - :ref:`ZE_extension_relaxed_allocation_limits <ZE_extension_relaxed_allocation_limits>`
     - 
   * - :doc:`ZE_experimental_rtas_builder <EXT_Exp_RTASBuilder>`
     - 1.13
     - :ref:`ZE_extension_rtas <ZE_extension_rtas>`
     - 

Functions
---------

.. list-table::
   :header-rows: 1
   :widths: 28 6 28 38
   :class: deprecated-table

   * - Name
     - Since
     - Replacement
     - Notes
   * - :ref:`zeCommandListImmediateAppendCommandListsExp`
     - 1.16
     - :ref:`zeCommandListImmediateAppendCommandListsWithParameters`
     - 
   * - :ref:`zeDriverGet`
     - 1.10
     - :ref:`zeInitDrivers`
     - 
   * - :ref:`zeImageViewCreateExp`
     - 1.5
     - :ref:`zeImageViewCreateExt`
     - 
   * - :ref:`zeInit`
     - 1.10
     - :ref:`zeInitDrivers`
     - 

Enumerations
------------

.. list-table::
   :header-rows: 1
   :widths: 28 6 28 38
   :class: deprecated-table

   * - Name
     - Since
     - Replacement
     - Notes
   * - :ref:`ze-image-view-exp-version-t`
     - 1.5
     - :ref:`ZE_extension_image_view <ZE_extension_image_view>`
     - 
   * - :ref:`ze-image-view-planar-exp-version-t`
     - 1.5
     - :ref:`ZE_extension_image_view_planar <ZE_extension_image_view_planar>`
     - 
   * - :ref:`ze-immediate-command-list-append-exp-version-t`
     - 1.16
     - :ref:`zeCommandListImmediateAppendCommandListsWithParameters`
     - 
   * - :ref:`ze-power-saving-hint-exp-version-t`
     - 1.18
     - :ref:`ZE_extension_power_saving_hint <ZE_extension_power_saving_hint>`
     - 
   * - :ref:`ze-power-saving-hint-type-t`
     - 1.18
     - :ref:`ze-power-saving-hint-ext-type-t`
     - 
   * - :ref:`ze-relaxed-allocation-limits-exp-flags-t`
     - 1.17
     - :ref:`ze-relaxed-allocation-limits-ext-flags-t`
     - 
   * - :ref:`ze-relaxed-allocation-limits-exp-version-t`
     - 1.17
     - :ref:`ZE_extension_relaxed_allocation_limits <ZE_extension_relaxed_allocation_limits>`
     - 

Structures
----------

.. list-table::
   :header-rows: 1
   :widths: 28 6 28 38
   :class: deprecated-table

   * - Name
     - Since
     - Replacement
     - Notes
   * - :ref:`ze-context-power-saving-hint-exp-desc-t`
     - 1.18
     - :ref:`ze-context-power-saving-hint-ext-desc-t`
     - 
   * - :ref:`ze-copy-bandwidth-exp-properties-t`
     - 1.14
     - --
     - No replacement.
   * - :ref:`ze-image-view-planar-exp-desc-t`
     - 1.5
     - :ref:`ze-image-view-planar-ext-desc-t`
     - 
   * - :ref:`ze-relaxed-allocation-limits-exp-desc-t`
     - 1.17
     - :ref:`ze-relaxed-allocation-limits-ext-desc-t`
     - 

Enumeration values
------------------

.. list-table::
   :header-rows: 1
   :widths: 28 6 28 38
   :class: deprecated-table

   * - Name
     - Since
     - Replacement
     - Notes
   * - :ref:`ZE_CACHE_EXT_REGION_ZE_CACHE_NON_RESERVED_REGION <ze-cache-ext-region-t>`
     - 1.7
     - :ref:`ZE_CACHE_EXT_REGION_NON_RESERVED <ze-cache-ext-region-t>`
     - 
   * - :ref:`ZE_CACHE_EXT_REGION_ZE_CACHE_REGION_DEFAULT <ze-cache-ext-region-t>`
     - 1.7
     - :ref:`ZE_CACHE_EXT_REGION_DEFAULT <ze-cache-ext-region-t>`
     - 
   * - :ref:`ZE_CACHE_EXT_REGION_ZE_CACHE_RESERVE_REGION <ze-cache-ext-region-t>`
     - 1.7
     - :ref:`ZE_CACHE_EXT_REGION_RESERVED <ze-cache-ext-region-t>`
     - 
   * - :ref:`ZE_COMMAND_LIST_FLAG_EXP_CLONEABLE <ze-command-list-flags-t>`
     - 1.17
     - :ref:`ZE_extension_mutable_command_list <ZE_extension_mutable_command_list>`
     - Mutable command lists replace command list cloning.
   * - :ref:`ZE_COMMAND_LIST_FLAG_EXPLICIT_ONLY <ze-command-list-flags-t>`
     - 1.13
     - Related: :ref:`zeDeviceGetSubDevices`
     - To place work on specific sub-devices, submit to sub-device handles or set ZE_FLAT_DEVICE_HIERARCHY=FLAT.
   * - :ref:`ZE_COMMAND_QUEUE_FLAG_EXPLICIT_ONLY <ze-command-queue-flags-t>`
     - 1.13
     - Related: :ref:`zeDeviceGetSubDevices`
     - To place work on specific sub-devices, submit to sub-device handles or set ZE_FLAT_DEVICE_HIERARCHY=FLAT.
   * - :ref:`ZE_EVENT_COUNTER_BASED_FLAG_IPC_BIDIRECTIONAL <ze-event-counter-based-flags-t>`
     - 1.20
     - Related: :ref:`ZE_DEVICE_EVENT_PROPERTIES_FLAG_COUNTER_BASED_IPC_BIDIRECTIONAL <ze-device-event-properties-flags-t>`
     - Ignored. The IPC sharing mode depends on the device.
   * - :ref:`ZE_STRUCTURE_TYPE_COPY_BANDWIDTH_EXP_PROPERTIES <ze-structure-type-t>`
     - 1.14
     - --
     - No replacement.
   * - :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>`
     - 1.17
     - :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES_1_2 <ze-structure-type-t>`
     - 
