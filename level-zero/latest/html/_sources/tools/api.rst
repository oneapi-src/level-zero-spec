

==============================
Tools API
==============================
oneAPI Level Zero Specification - Version 1.13.0

 

 

Common
============================================================
* Enumerations


    * :ref:`zet-structure-type-t`
    * :ref:`zet-value-type-t`

 
* Structures


    * :ref:`zet-base-properties-t`
    * :ref:`zet-base-desc-t`
    * :ref:`zet-value-t`
    * :ref:`zet-typed-value-t`




Common Enums
------------------------------------------------------------------------------


.. _zet-structure-type-t:

zet_structure_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_structure_type_t
    :project: LevelZero


.. _zet-value-type-t:

zet_value_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_value_type_t
    :project: LevelZero

 
Common Structures
------------------------------------------------------------------------------

.. _zet-base-properties-t:

zet_base_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_base_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-base-desc-t:

zet_base_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_base_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-value-t:

zet_value_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenunion:: zet_value_t
    :project: LevelZero

.. _zet-typed-value-t:

zet_typed_value_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_typed_value_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

 




 

 

 

 




 

 

 

 




 

 

Module
============================================================
* Functions


    * :ref:`zetModuleGetDebugInfo`

 
* Enumerations


    * :ref:`zet-module-debug-info-format-t`

 


Module Functions
------------------------------------------------------------------------------


.. _zetModuleGetDebugInfo:

zetModuleGetDebugInfo
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetModuleGetDebugInfo
    :project: LevelZero



Module Enums
------------------------------------------------------------------------------


.. _zet-module-debug-info-format-t:

zet_module_debug_info_format_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_module_debug_info_format_t
    :project: LevelZero

 

 

Debug
============================================================
* Functions


    * :ref:`zetDeviceGetDebugProperties`
    * :ref:`zetDebugAttach`
    * :ref:`zetDebugDetach`
    * :ref:`zetDebugReadEvent`
    * :ref:`zetDebugAcknowledgeEvent`
    * :ref:`zetDebugInterrupt`
    * :ref:`zetDebugResume`
    * :ref:`zetDebugReadMemory`
    * :ref:`zetDebugWriteMemory`
    * :ref:`zetDebugGetRegisterSetProperties`
    * :ref:`zetDebugGetThreadRegisterSetProperties`
    * :ref:`zetDebugReadRegisters`
    * :ref:`zetDebugWriteRegisters`

 
* Enumerations


    * :ref:`zet-device-debug-property-flags-t`
    * :ref:`zet-debug-event-flags-t`
    * :ref:`zet-debug-event-type-t`
    * :ref:`zet-debug-detach-reason-t`
    * :ref:`zet-debug-page-fault-reason-t`
    * :ref:`zet-debug-memory-space-type-t`
    * :ref:`zet-debug-regset-flags-t`

 
* Structures


    * :ref:`zet-device-debug-properties-t`
    * :ref:`zet-debug-config-t`
    * :ref:`zet-debug-event-info-detached-t`
    * :ref:`zet-debug-event-info-module-t`
    * :ref:`zet-debug-event-info-thread-stopped-t`
    * :ref:`zet-debug-event-info-page-fault-t`
    * :ref:`zet-debug-event-info-t`
    * :ref:`zet-debug-event-t`
    * :ref:`zet-debug-memory-space-desc-t`
    * :ref:`zet-debug-regset-properties-t`


Debug Functions
------------------------------------------------------------------------------


.. _zetDeviceGetDebugProperties:

zetDeviceGetDebugProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDeviceGetDebugProperties
    :project: LevelZero


.. _zetDebugAttach:

zetDebugAttach
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugAttach
    :project: LevelZero


.. _zetDebugDetach:

zetDebugDetach
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugDetach
    :project: LevelZero


.. _zetDebugReadEvent:

zetDebugReadEvent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugReadEvent
    :project: LevelZero


.. _zetDebugAcknowledgeEvent:

zetDebugAcknowledgeEvent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugAcknowledgeEvent
    :project: LevelZero


.. _zetDebugInterrupt:

zetDebugInterrupt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugInterrupt
    :project: LevelZero


.. _zetDebugResume:

zetDebugResume
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugResume
    :project: LevelZero


.. _zetDebugReadMemory:

zetDebugReadMemory
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugReadMemory
    :project: LevelZero


.. _zetDebugWriteMemory:

zetDebugWriteMemory
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugWriteMemory
    :project: LevelZero


.. _zetDebugGetRegisterSetProperties:

zetDebugGetRegisterSetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugGetRegisterSetProperties
    :project: LevelZero


.. _zetDebugGetThreadRegisterSetProperties:

zetDebugGetThreadRegisterSetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugGetThreadRegisterSetProperties
    :project: LevelZero


.. _zetDebugReadRegisters:

zetDebugReadRegisters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugReadRegisters
    :project: LevelZero


.. _zetDebugWriteRegisters:

zetDebugWriteRegisters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDebugWriteRegisters
    :project: LevelZero



Debug Enums
------------------------------------------------------------------------------


.. _zet-device-debug-property-flags-t:

zet_device_debug_property_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_device_debug_property_flag_t
    :project: LevelZero


.. _zet-debug-event-flags-t:

zet_debug_event_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_debug_event_flag_t
    :project: LevelZero


.. _zet-debug-event-type-t:

zet_debug_event_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_debug_event_type_t
    :project: LevelZero


.. _zet-debug-detach-reason-t:

zet_debug_detach_reason_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_debug_detach_reason_t
    :project: LevelZero


.. _zet-debug-page-fault-reason-t:

zet_debug_page_fault_reason_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_debug_page_fault_reason_t
    :project: LevelZero


.. _zet-debug-memory-space-type-t:

zet_debug_memory_space_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_debug_memory_space_type_t
    :project: LevelZero


.. _zet-debug-regset-flags-t:

zet_debug_regset_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_debug_regset_flag_t
    :project: LevelZero

 
Debug Structures
------------------------------------------------------------------------------

.. _zet-device-debug-properties-t:

zet_device_debug_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_device_debug_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-debug-config-t:

zet_debug_config_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_debug_config_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-debug-event-info-detached-t:

zet_debug_event_info_detached_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_debug_event_info_detached_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-debug-event-info-module-t:

zet_debug_event_info_module_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_debug_event_info_module_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-debug-event-info-thread-stopped-t:

zet_debug_event_info_thread_stopped_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_debug_event_info_thread_stopped_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-debug-event-info-page-fault-t:

zet_debug_event_info_page_fault_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_debug_event_info_page_fault_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-debug-event-info-t:

zet_debug_event_info_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenunion:: zet_debug_event_info_t
    :project: LevelZero

.. _zet-debug-event-t:

zet_debug_event_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_debug_event_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-debug-memory-space-desc-t:

zet_debug_memory_space_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_debug_memory_space_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-debug-regset-properties-t:

zet_debug_regset_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_debug_regset_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Metric
============================================================
* Functions


    * :ref:`zetMetricGroupGet`
    * :ref:`zetMetricGroupGetProperties`
    * :ref:`zetMetricGroupCalculateMetricValues`
    * :ref:`zetMetricGet`
    * :ref:`zetMetricGetProperties`
    * :ref:`zetContextActivateMetricGroups`
    * :ref:`zetMetricStreamerOpen`
    * :ref:`zetCommandListAppendMetricStreamerMarker`
    * :ref:`zetMetricStreamerClose`
    * :ref:`zetMetricStreamerReadData`
    * :ref:`zetMetricQueryPoolCreate`
    * :ref:`zetMetricQueryPoolDestroy`
    * :ref:`zetMetricQueryCreate`
    * :ref:`zetMetricQueryDestroy`
    * :ref:`zetMetricQueryReset`
    * :ref:`zetCommandListAppendMetricQueryBegin`
    * :ref:`zetCommandListAppendMetricQueryEnd`
    * :ref:`zetCommandListAppendMetricMemoryBarrier`
    * :ref:`zetMetricQueryGetData`

 
* Enumerations


    * :ref:`zet-metric-group-sampling-type-flags-t`
    * :ref:`zet-metric-type-t`
    * :ref:`zet-metric-group-calculation-type-t`
    * :ref:`zet-metric-query-pool-type-t`

 
* Structures


    * :ref:`zet-metric-group-properties-t`
    * :ref:`zet-metric-properties-t`
    * :ref:`zet-metric-streamer-desc-t`
    * :ref:`zet-metric-query-pool-desc-t`


Metric Functions
------------------------------------------------------------------------------


.. _zetMetricGroupGet:

zetMetricGroupGet
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupGet
    :project: LevelZero


.. _zetMetricGroupGetProperties:

zetMetricGroupGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupGetProperties
    :project: LevelZero


.. _zetMetricGroupCalculateMetricValues:

zetMetricGroupCalculateMetricValues
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupCalculateMetricValues
    :project: LevelZero


.. _zetMetricGet:

zetMetricGet
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGet
    :project: LevelZero


.. _zetMetricGetProperties:

zetMetricGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGetProperties
    :project: LevelZero


.. _zetContextActivateMetricGroups:

zetContextActivateMetricGroups
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetContextActivateMetricGroups
    :project: LevelZero


.. _zetMetricStreamerOpen:

zetMetricStreamerOpen
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricStreamerOpen
    :project: LevelZero


.. _zetCommandListAppendMetricStreamerMarker:

zetCommandListAppendMetricStreamerMarker
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetCommandListAppendMetricStreamerMarker
    :project: LevelZero


.. _zetMetricStreamerClose:

zetMetricStreamerClose
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricStreamerClose
    :project: LevelZero


.. _zetMetricStreamerReadData:

zetMetricStreamerReadData
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricStreamerReadData
    :project: LevelZero


.. _zetMetricQueryPoolCreate:

zetMetricQueryPoolCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricQueryPoolCreate
    :project: LevelZero


.. _zetMetricQueryPoolDestroy:

zetMetricQueryPoolDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricQueryPoolDestroy
    :project: LevelZero


.. _zetMetricQueryCreate:

zetMetricQueryCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricQueryCreate
    :project: LevelZero


.. _zetMetricQueryDestroy:

zetMetricQueryDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricQueryDestroy
    :project: LevelZero


.. _zetMetricQueryReset:

zetMetricQueryReset
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricQueryReset
    :project: LevelZero


.. _zetCommandListAppendMetricQueryBegin:

zetCommandListAppendMetricQueryBegin
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetCommandListAppendMetricQueryBegin
    :project: LevelZero


.. _zetCommandListAppendMetricQueryEnd:

zetCommandListAppendMetricQueryEnd
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetCommandListAppendMetricQueryEnd
    :project: LevelZero


.. _zetCommandListAppendMetricMemoryBarrier:

zetCommandListAppendMetricMemoryBarrier
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetCommandListAppendMetricMemoryBarrier
    :project: LevelZero


.. _zetMetricQueryGetData:

zetMetricQueryGetData
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricQueryGetData
    :project: LevelZero



Metric Enums
------------------------------------------------------------------------------


.. _zet-metric-group-sampling-type-flags-t:

zet_metric_group_sampling_type_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_metric_group_sampling_type_flag_t
    :project: LevelZero


.. _zet-metric-type-t:

zet_metric_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_metric_type_t
    :project: LevelZero


.. _zet-metric-group-calculation-type-t:

zet_metric_group_calculation_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_metric_group_calculation_type_t
    :project: LevelZero


.. _zet-metric-query-pool-type-t:

zet_metric_query_pool_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_metric_query_pool_type_t
    :project: LevelZero

 
Metric Structures
------------------------------------------------------------------------------

.. _zet-metric-group-properties-t:

zet_metric_group_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_group_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-metric-properties-t:

zet_metric_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-metric-streamer-desc-t:

zet_metric_streamer_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_streamer_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-metric-query-pool-desc-t:

zet_metric_query_pool_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_query_pool_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Pin
============================================================
* Functions


    * :ref:`zetKernelGetProfileInfo`

 
* Enumerations


    * :ref:`zet-profile-flags-t`
    * :ref:`zet-profile-token-type-t`

 
* Structures


    * :ref:`zet-profile-properties-t`
    * :ref:`zet-profile-free-register-token-t`
    * :ref:`zet-profile-register-sequence-t`


Pin Functions
------------------------------------------------------------------------------


.. _zetKernelGetProfileInfo:

zetKernelGetProfileInfo
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetKernelGetProfileInfo
    :project: LevelZero



Pin Enums
------------------------------------------------------------------------------


.. _zet-profile-flags-t:

zet_profile_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_profile_flag_t
    :project: LevelZero


.. _zet-profile-token-type-t:

zet_profile_token_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_profile_token_type_t
    :project: LevelZero

 
Pin Structures
------------------------------------------------------------------------------

.. _zet-profile-properties-t:

zet_profile_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_profile_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-profile-free-register-token-t:

zet_profile_free_register_token_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_profile_free_register_token_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-profile-register-sequence-t:

zet_profile_register_sequence_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_profile_register_sequence_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Tracing
============================================================
* Functions


    * :ref:`zetTracerExpCreate`
    * :ref:`zetTracerExpDestroy`
    * :ref:`zetTracerExpSetPrologues`
    * :ref:`zetTracerExpSetEpilogues`
    * :ref:`zetTracerExpSetEnabled`

 
* Enumerations


    * :ref:`zet-api-tracing-exp-version-t`

 
* Structures


    * :ref:`zet-tracer-exp-desc-t`


Tracing Functions
------------------------------------------------------------------------------


.. _zetTracerExpCreate:

zetTracerExpCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetTracerExpCreate
    :project: LevelZero


.. _zetTracerExpDestroy:

zetTracerExpDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetTracerExpDestroy
    :project: LevelZero


.. _zetTracerExpSetPrologues:

zetTracerExpSetPrologues
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetTracerExpSetPrologues
    :project: LevelZero


.. _zetTracerExpSetEpilogues:

zetTracerExpSetEpilogues
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetTracerExpSetEpilogues
    :project: LevelZero


.. _zetTracerExpSetEnabled:

zetTracerExpSetEnabled
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetTracerExpSetEnabled
    :project: LevelZero



Tracing Enums
------------------------------------------------------------------------------


.. _zet-api-tracing-exp-version-t:

zet_api_tracing_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_api_tracing_exp_version_t
    :project: LevelZero

 
Tracing Structures
------------------------------------------------------------------------------

.. _zet-tracer-exp-desc-t:

zet_tracer_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_tracer_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Concurrentmetricgroup
============================================================
* Functions


    * :ref:`zetDeviceGetConcurrentMetricGroupsExp`

 
* Enumerations


    * :ref:`zet-concurrent-metric-groups-exp-version-t`

 


Concurrentmetricgroup Functions
------------------------------------------------------------------------------


.. _zetDeviceGetConcurrentMetricGroupsExp:

zetDeviceGetConcurrentMetricGroupsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDeviceGetConcurrentMetricGroupsExp
    :project: LevelZero



Concurrentmetricgroup Enums
------------------------------------------------------------------------------


.. _zet-concurrent-metric-groups-exp-version-t:

zet_concurrent_metric_groups_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_concurrent_metric_groups_exp_version_t
    :project: LevelZero

 

 

Metrictracer
============================================================
* Functions


    * :ref:`zetMetricTracerCreateExp`
    * :ref:`zetMetricTracerDestroyExp`
    * :ref:`zetMetricTracerEnableExp`
    * :ref:`zetMetricTracerDisableExp`
    * :ref:`zetMetricTracerReadDataExp`
    * :ref:`zetMetricDecoderCreateExp`
    * :ref:`zetMetricDecoderDestroyExp`
    * :ref:`zetMetricDecoderGetDecodableMetricsExp`
    * :ref:`zetMetricTracerDecodeExp`

 
* Enumerations


    * :ref:`zet-metric-tracer-exp-version-t`

 
* Structures


    * :ref:`zet-metric-tracer-exp-desc-t`
    * :ref:`zet-metric-entry-exp-t`


Metrictracer Functions
------------------------------------------------------------------------------


.. _zetMetricTracerCreateExp:

zetMetricTracerCreateExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricTracerCreateExp
    :project: LevelZero


.. _zetMetricTracerDestroyExp:

zetMetricTracerDestroyExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricTracerDestroyExp
    :project: LevelZero


.. _zetMetricTracerEnableExp:

zetMetricTracerEnableExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricTracerEnableExp
    :project: LevelZero


.. _zetMetricTracerDisableExp:

zetMetricTracerDisableExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricTracerDisableExp
    :project: LevelZero


.. _zetMetricTracerReadDataExp:

zetMetricTracerReadDataExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricTracerReadDataExp
    :project: LevelZero


.. _zetMetricDecoderCreateExp:

zetMetricDecoderCreateExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricDecoderCreateExp
    :project: LevelZero


.. _zetMetricDecoderDestroyExp:

zetMetricDecoderDestroyExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricDecoderDestroyExp
    :project: LevelZero


.. _zetMetricDecoderGetDecodableMetricsExp:

zetMetricDecoderGetDecodableMetricsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricDecoderGetDecodableMetricsExp
    :project: LevelZero


.. _zetMetricTracerDecodeExp:

zetMetricTracerDecodeExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricTracerDecodeExp
    :project: LevelZero



Metrictracer Enums
------------------------------------------------------------------------------


.. _zet-metric-tracer-exp-version-t:

zet_metric_tracer_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_metric_tracer_exp_version_t
    :project: LevelZero

 
Metrictracer Structures
------------------------------------------------------------------------------

.. _zet-metric-tracer-exp-desc-t:

zet_metric_tracer_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_tracer_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-metric-entry-exp-t:

zet_metric_entry_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_entry_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Metricexportmemory
============================================================
* Enumerations


    * :ref:`zet-metric-group-type-exp-flags-t`

 
* Structures


    * :ref:`zet-metric-group-type-exp-t`
    * :ref:`zet-export-dma-buf-exp-properties-t`




Metricexportmemory Enums
------------------------------------------------------------------------------


.. _zet-metric-group-type-exp-flags-t:

zet_metric_group_type_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_metric_group_type_exp_flag_t
    :project: LevelZero

 
Metricexportmemory Structures
------------------------------------------------------------------------------

.. _zet-metric-group-type-exp-t:

zet_metric_group_type_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_group_type_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-export-dma-buf-exp-properties-t:

zet_export_dma_buf_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_export_dma_buf_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Metricgroupmarker
============================================================
* Functions


    * :ref:`zetCommandListAppendMarkerExp`

 
* Enumerations


    * :ref:`zet-metric-group-marker-exp-version-t`

 
* Structures


    * :ref:`zet-metric-source-id-exp-t`


Metricgroupmarker Functions
------------------------------------------------------------------------------


.. _zetCommandListAppendMarkerExp:

zetCommandListAppendMarkerExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetCommandListAppendMarkerExp
    :project: LevelZero



Metricgroupmarker Enums
------------------------------------------------------------------------------


.. _zet-metric-group-marker-exp-version-t:

zet_metric_group_marker_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_metric_group_marker_exp_version_t
    :project: LevelZero

 
Metricgroupmarker Structures
------------------------------------------------------------------------------

.. _zet-metric-source-id-exp-t:

zet_metric_source_id_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_source_id_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Metricruntimeenabledisable
============================================================
* Functions


    * :ref:`zetDeviceEnableMetricsExp`
    * :ref:`zetDeviceDisableMetricsExp`

 
* Enumerations


    * :ref:`zet-metrics-runtime-enable-disable-exp-version-t`

 


Metricruntimeenabledisable Functions
------------------------------------------------------------------------------


.. _zetDeviceEnableMetricsExp:

zetDeviceEnableMetricsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDeviceEnableMetricsExp
    :project: LevelZero


.. _zetDeviceDisableMetricsExp:

zetDeviceDisableMetricsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDeviceDisableMetricsExp
    :project: LevelZero



Metricruntimeenabledisable Enums
------------------------------------------------------------------------------


.. _zet-metrics-runtime-enable-disable-exp-version-t:

zet_metrics_runtime_enable_disable_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_metrics_runtime_enable_disable_exp_version_t
    :project: LevelZero

 

 

Multimetricvalues
============================================================
* Functions


    * :ref:`zetMetricGroupCalculateMultipleMetricValuesExp`

 
* Enumerations


    * :ref:`ze-calculate-multiple-metrics-exp-version-t`

 


Multimetricvalues Functions
------------------------------------------------------------------------------


.. _zetMetricGroupCalculateMultipleMetricValuesExp:

zetMetricGroupCalculateMultipleMetricValuesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupCalculateMultipleMetricValuesExp
    :project: LevelZero



Multimetricvalues Enums
------------------------------------------------------------------------------


.. _ze-calculate-multiple-metrics-exp-version-t:

ze_calculate_multiple_metrics_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_calculate_multiple_metrics_exp_version_t
    :project: LevelZero

 

 

Globaltimestamps
============================================================
* Functions


    * :ref:`zetMetricGroupGetGlobalTimestampsExp`

 
* Enumerations


    * :ref:`ze-metric-global-timestamps-exp-version-t`

 
* Structures


    * :ref:`zet-metric-global-timestamps-resolution-exp-t`


Globaltimestamps Functions
------------------------------------------------------------------------------


.. _zetMetricGroupGetGlobalTimestampsExp:

zetMetricGroupGetGlobalTimestampsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupGetGlobalTimestampsExp
    :project: LevelZero



Globaltimestamps Enums
------------------------------------------------------------------------------


.. _ze-metric-global-timestamps-exp-version-t:

ze_metric_global_timestamps_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_metric_global_timestamps_exp_version_t
    :project: LevelZero

 
Globaltimestamps Structures
------------------------------------------------------------------------------

.. _zet-metric-global-timestamps-resolution-exp-t:

zet_metric_global_timestamps_resolution_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_global_timestamps_resolution_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Metricexportdata
============================================================
* Functions


    * :ref:`zetMetricGroupGetExportDataExp`
    * :ref:`zetMetricGroupCalculateMetricExportDataExp`

 
* Enumerations


    * :ref:`zet-export-metric-data-exp-version-t`

 
* Structures


    * :ref:`zet-metric-calculate-exp-desc-t`


Metricexportdata Functions
------------------------------------------------------------------------------


.. _zetMetricGroupGetExportDataExp:

zetMetricGroupGetExportDataExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupGetExportDataExp
    :project: LevelZero


.. _zetMetricGroupCalculateMetricExportDataExp:

zetMetricGroupCalculateMetricExportDataExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupCalculateMetricExportDataExp
    :project: LevelZero



Metricexportdata Enums
------------------------------------------------------------------------------


.. _zet-export-metric-data-exp-version-t:

zet_export_metric_data_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_export_metric_data_exp_version_t
    :project: LevelZero

 
Metricexportdata Structures
------------------------------------------------------------------------------

.. _zet-metric-calculate-exp-desc-t:

zet_metric_calculate_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_calculate_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Metricprogrammable
============================================================
* Functions


    * :ref:`zetMetricProgrammableGetExp`
    * :ref:`zetMetricProgrammableGetPropertiesExp`
    * :ref:`zetMetricProgrammableGetParamInfoExp`
    * :ref:`zetMetricProgrammableGetParamValueInfoExp`
    * :ref:`zetMetricCreateFromProgrammableExp2`
    * :ref:`zetMetricCreateFromProgrammableExp`
    * :ref:`zetDeviceCreateMetricGroupsFromMetricsExp`
    * :ref:`zetMetricGroupCreateExp`
    * :ref:`zetMetricGroupAddMetricExp`
    * :ref:`zetMetricGroupRemoveMetricExp`
    * :ref:`zetMetricGroupCloseExp`
    * :ref:`zetMetricGroupDestroyExp`
    * :ref:`zetMetricDestroyExp`

 
* Enumerations


    * :ref:`zet-metric-programmable-exp-version-t`
    * :ref:`zet-metric-programmable-param-type-exp-t`
    * :ref:`zet-value-info-type-exp-t`

 
* Structures


    * :ref:`zet-metric-programmable-exp-properties-t`
    * :ref:`zet-value-uint64-range-exp-t`
    * :ref:`zet-value-fp64-range-exp-t`
    * :ref:`zet-value-info-exp-t`
    * :ref:`zet-metric-programmable-param-info-exp-t`
    * :ref:`zet-metric-programmable-param-value-info-exp-t`
    * :ref:`zet-metric-programmable-param-value-exp-t`


Metricprogrammable Functions
------------------------------------------------------------------------------


.. _zetMetricProgrammableGetExp:

zetMetricProgrammableGetExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricProgrammableGetExp
    :project: LevelZero


.. _zetMetricProgrammableGetPropertiesExp:

zetMetricProgrammableGetPropertiesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricProgrammableGetPropertiesExp
    :project: LevelZero


.. _zetMetricProgrammableGetParamInfoExp:

zetMetricProgrammableGetParamInfoExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricProgrammableGetParamInfoExp
    :project: LevelZero


.. _zetMetricProgrammableGetParamValueInfoExp:

zetMetricProgrammableGetParamValueInfoExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricProgrammableGetParamValueInfoExp
    :project: LevelZero


.. _zetMetricCreateFromProgrammableExp2:

zetMetricCreateFromProgrammableExp2
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricCreateFromProgrammableExp2
    :project: LevelZero


.. _zetMetricCreateFromProgrammableExp:

zetMetricCreateFromProgrammableExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricCreateFromProgrammableExp
    :project: LevelZero


.. _zetDeviceCreateMetricGroupsFromMetricsExp:

zetDeviceCreateMetricGroupsFromMetricsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetDeviceCreateMetricGroupsFromMetricsExp
    :project: LevelZero


.. _zetMetricGroupCreateExp:

zetMetricGroupCreateExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupCreateExp
    :project: LevelZero


.. _zetMetricGroupAddMetricExp:

zetMetricGroupAddMetricExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupAddMetricExp
    :project: LevelZero


.. _zetMetricGroupRemoveMetricExp:

zetMetricGroupRemoveMetricExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupRemoveMetricExp
    :project: LevelZero


.. _zetMetricGroupCloseExp:

zetMetricGroupCloseExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupCloseExp
    :project: LevelZero


.. _zetMetricGroupDestroyExp:

zetMetricGroupDestroyExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricGroupDestroyExp
    :project: LevelZero


.. _zetMetricDestroyExp:

zetMetricDestroyExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zetMetricDestroyExp
    :project: LevelZero



Metricprogrammable Enums
------------------------------------------------------------------------------


.. _zet-metric-programmable-exp-version-t:

zet_metric_programmable_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_metric_programmable_exp_version_t
    :project: LevelZero


.. _zet-metric-programmable-param-type-exp-t:

zet_metric_programmable_param_type_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_metric_programmable_param_type_exp_t
    :project: LevelZero


.. _zet-value-info-type-exp-t:

zet_value_info_type_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zet_value_info_type_exp_t
    :project: LevelZero

 
Metricprogrammable Structures
------------------------------------------------------------------------------

.. _zet-metric-programmable-exp-properties-t:

zet_metric_programmable_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_programmable_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-value-uint64-range-exp-t:

zet_value_uint64_range_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_value_uint64_range_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-value-fp64-range-exp-t:

zet_value_fp64_range_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_value_fp64_range_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-value-info-exp-t:

zet_value_info_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenunion:: zet_value_info_exp_t
    :project: LevelZero

.. _zet-metric-programmable-param-info-exp-t:

zet_metric_programmable_param_info_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_programmable_param_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-metric-programmable-param-value-info-exp-t:

zet_metric_programmable_param_value_info_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_programmable_param_value_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zet-metric-programmable-param-value-exp-t:

zet_metric_programmable_param_value_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zet_metric_programmable_param_value_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


