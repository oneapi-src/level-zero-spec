============================================================
Sysman - Deprecated
============================================================

Everything below is deprecated. Use the replacement where one is listed.

The reference pages are under :doc:`Deprecated APIs <api/deprecated/index>`.

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
   * - :ref:`zesDeviceEnumActiveVFExp`
     - 1.11
     - :ref:`zesDeviceEnumEnabledVFExp`
     - No longer supported.
   * - :ref:`zesDeviceGetCardPowerDomain`
     - 1.8
     - Related: :ref:`zesDeviceEnumPowerDomains`
     - Enumerate power domains; the card domain reports ZES_POWER_DOMAIN_CARD in zes_power_ext_properties_t.
   * - :ref:`zesFrequencyOcGetCapabilities`
     - 1.8
     - :ref:`zesOverclockGetDomainProperties`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesFrequencyOcGetFrequencyTarget`
     - 1.8
     - :ref:`zesOverclockGetControlCurrentValue`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesFrequencyOcGetIccMax`
     - 1.8
     - :ref:`zesOverclockGetControlCurrentValue`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesFrequencyOcGetMode`
     - 1.8
     - :ref:`zesOverclockGetControlCurrentValue`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesFrequencyOcGetTjMax`
     - 1.8
     - :ref:`zesOverclockGetControlCurrentValue`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesFrequencyOcGetVoltageTarget`
     - 1.8
     - :ref:`zesOverclockGetControlCurrentValue`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesFrequencyOcSetFrequencyTarget`
     - 1.8
     - :ref:`zesOverclockSetControlUserValue`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesFrequencyOcSetIccMax`
     - 1.8
     - :ref:`zesOverclockSetControlUserValue`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesFrequencyOcSetMode`
     - 1.8
     - :ref:`zesOverclockSetControlUserValue`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesFrequencyOcSetTjMax`
     - 1.8
     - :ref:`zesOverclockSetControlUserValue`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesFrequencyOcSetVoltageTarget`
     - 1.8
     - :ref:`zesOverclockSetControlUserValue`
     - Overclocking moved to the Overclock API.
   * - :ref:`zesPowerGetLimits`
     - 1.5
     - :ref:`zesPowerGetLimitsExt`
     - 
   * - :ref:`zesPowerSetLimits`
     - 1.5
     - :ref:`zesPowerSetLimitsExt`
     - 
   * - :ref:`zesRasGetConfig`
     - 1.16
     - :ref:`zesRasGetConfigExp`
     - 
   * - :ref:`zesRasSetConfig`
     - 1.16
     - :ref:`zesRasSetConfigExp`
     - 
   * - :ref:`zesSchedulerSetComputeUnitDebugMode`
     - 1.8
     - Related: :ref:`zetDebugAttach`
     - Enable debugging with ZET_ENABLE_PROGRAM_DEBUGGING, and select devices with ZE_AFFINITY_MASK.
   * - :ref:`zesVFManagementGetVFCapabilitiesExp`
     - 1.12
     - :ref:`zesVFManagementGetVFCapabilitiesExp2`
     - No longer supported.
   * - :ref:`zesVFManagementGetVFEngineUtilizationExp`
     - 1.11
     - :ref:`zesVFManagementGetVFEngineUtilizationExp2`
     - No longer supported.
   * - :ref:`zesVFManagementGetVFMemoryUtilizationExp`
     - 1.11
     - :ref:`zesVFManagementGetVFMemoryUtilizationExp2`
     - No longer supported.
   * - :ref:`zesVFManagementGetVFPropertiesExp`
     - 1.11
     - :ref:`zesVFManagementGetVFCapabilitiesExp2`
     - No longer supported.
   * - :ref:`zesVFManagementSetVFTelemetryModeExp`
     - 1.11
     - Related: :ref:`zesVFManagementGetVFEngineUtilizationExp2`
     - Utilization telemetry needs no enabling; query it directly (memory: zesVFManagementGetVFMemoryUtilizationExp2).
   * - :ref:`zesVFManagementSetVFTelemetrySamplingIntervalExp`
     - 1.11
     - Related: :ref:`zesVFManagementGetVFEngineUtilizationExp2`
     - Utilization telemetry needs no sampling setup; query it directly (memory: zesVFManagementGetVFMemoryUtilizationExp2).

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
   * - :ref:`zes-oc-mode-t`
     - 1.8
     - :ref:`zes-overclock-mode-t`
     - Overclocking moved to the Overclock API.
   * - :ref:`zes-vf-info-mem-type-exp-flags-t`
     - 1.10
     - :ref:`zes-mem-loc-t`
     - 
   * - :ref:`zes-vf-info-util-exp-flags-t`
     - 1.10
     - Related: :ref:`zesVFManagementGetVFEngineUtilizationExp2`
     - The Exp2 utilization queries report what is available: memory by zes_mem_loc_t, engines by zes_engine_group_t.

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
   * - :ref:`zes-mem-ext-bandwidth-t`
     - 1.8
     - :ref:`zes-mem-bandwidth-counter-bits-exp-properties-t`
     - The original struct lacked an stype field.
   * - :ref:`zes-oc-capabilities-t`
     - 1.8
     - :ref:`zes-overclock-properties-t`
     - Overclocking moved to the Overclock API.
   * - :ref:`zes-power-burst-limit-t`
     - 1.8
     - :ref:`zes-power-limit-ext-desc-t`
     - One descriptor per limit level replaces this struct.
   * - :ref:`zes-power-peak-limit-t`
     - 1.8
     - :ref:`zes-power-limit-ext-desc-t`
     - One descriptor per limit level replaces this struct.
   * - :ref:`zes-power-sustained-limit-t`
     - 1.8
     - :ref:`zes-power-limit-ext-desc-t`
     - One descriptor per limit level replaces this struct.
   * - :ref:`zes-vf-exp-capabilities-t`
     - 1.12
     - :ref:`zes-vf-exp2-capabilities-t`
     - 
   * - :ref:`zes-vf-exp-properties-t`
     - 1.10
     - :ref:`zes-vf-exp2-capabilities-t`
     - 
   * - :ref:`zes-vf-util-engine-exp-t`
     - 1.10
     - :ref:`zes-vf-util-engine-exp2-t`
     - 
   * - :ref:`zes-vf-util-mem-exp-t`
     - 1.10
     - :ref:`zes-vf-util-mem-exp2-t`
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
   * - :ref:`ZES_ENGINE_GROUP_3D_ALL <zes-engine-group-t>`
     - 1.8
     - Related: :ref:`ZES_ENGINE_GROUP_RENDER_ALL <zes-engine-group-t>`
     - Render engines process 3D content and compute kernels.
   * - :ref:`ZES_ENGINE_GROUP_3D_RENDER_COMPUTE_ALL <zes-engine-group-t>`
     - 1.8
     - Related: :ref:`ZES_ENGINE_GROUP_RENDER_ALL <zes-engine-group-t>`
     - Combine ZES_ENGINE_GROUP_RENDER_ALL with ZES_ENGINE_GROUP_COMPUTE_ALL for the same view.
   * - :ref:`ZES_ENGINE_GROUP_3D_SINGLE <zes-engine-group-t>`
     - 1.8
     - Related: :ref:`ZES_ENGINE_GROUP_RENDER_SINGLE <zes-engine-group-t>`
     - Render engines process 3D content and compute kernels.
   * - :ref:`ZES_ENGINE_GROUP_MEDIA_DECODE_SINGLE <zes-engine-group-t>`
     - 1.8
     - :ref:`ZES_ENGINE_GROUP_MEDIA_CODEC_SINGLE <zes-engine-group-t>`
     - 
   * - :ref:`ZES_ENGINE_GROUP_MEDIA_ENCODE_SINGLE <zes-engine-group-t>`
     - 1.8
     - :ref:`ZES_ENGINE_GROUP_MEDIA_CODEC_SINGLE <zes-engine-group-t>`
     - 
   * - :ref:`ZES_SCHED_MODE_COMPUTE_UNIT_DEBUG <zes-sched-mode-t>`
     - 1.8
     - Related: :ref:`zetDebugAttach`
     - Enable debugging with ZET_ENABLE_PROGRAM_DEBUGGING, and select devices with ZE_AFFINITY_MASK.
   * - :ref:`ZES_VF_MANAGEMENT_EXP_VERSION_1_0 <zes-vf-management-exp-version-t>`
     - 1.10
     - :ref:`ZES_VF_MANAGEMENT_EXP_VERSION_1_2 <zes-vf-management-exp-version-t>`
     - Superseded by a newer version.
   * - :ref:`ZES_VF_MANAGEMENT_EXP_VERSION_1_1 <zes-vf-management-exp-version-t>`
     - 1.11
     - :ref:`ZES_VF_MANAGEMENT_EXP_VERSION_1_2 <zes-vf-management-exp-version-t>`
     - Superseded by a newer version.

Structure members
-----------------

.. list-table::
   :header-rows: 1
   :widths: 28 6 28 38
   :class: deprecated-table

   * - Name
     - Since
     - Replacement
     - Notes
   * - :ref:`zes_device_properties_t.core <zes-device-properties-t>`
     - 1.7
     - :ref:`zes-device-ext-properties-t`
     - 
   * - :ref:`zes_mem_state_t.size <zes-mem-state-t>`
     - 1.15
     - :ref:`ze-device-usablemem-size-ext-properties-t`
     - This member can no longer track the allocatable memory reliably.
   * - :ref:`zes_power_properties_t.defaultLimit <zes-power-properties-t>`
     - 1.5
     - :ref:`zes-power-limit-ext-desc-t`
     - 
   * - :ref:`zes_power_properties_t.maxLimit <zes-power-properties-t>`
     - 1.5
     - :ref:`zes-power-limit-ext-desc-t`
     - 
   * - :ref:`zes_power_properties_t.minLimit <zes-power-properties-t>`
     - 1.5
     - :ref:`zes-power-limit-ext-desc-t`
     - 
