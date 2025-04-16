

==============================
Core API
==============================
oneAPI Level Zero Specification - Version 1.13.0

 

 

Common
============================================================
* Enumerations


    * :ref:`ze-result-t`
    * :ref:`ze-structure-type-t`
    * :ref:`ze-external-memory-type-flags-t`
    * :ref:`ze-bandwidth-unit-t`
    * :ref:`ze-latency-unit-t`

 
* Structures


    * :ref:`ze-ipc-mem-handle-t`
    * :ref:`ze-ipc-event-pool-handle-t`
    * :ref:`ze-uuid-t`
    * :ref:`ze-base-cb-params-t`
    * :ref:`ze-base-properties-t`
    * :ref:`ze-base-desc-t`




Common Enums
------------------------------------------------------------------------------


.. _ze-result-t:

ze_result_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_result_t
    :project: LevelZero


.. _ze-structure-type-t:

ze_structure_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_structure_type_t
    :project: LevelZero


.. _ze-external-memory-type-flags-t:

ze_external_memory_type_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_external_memory_type_flag_t
    :project: LevelZero


.. _ze-bandwidth-unit-t:

ze_bandwidth_unit_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_bandwidth_unit_t
    :project: LevelZero


.. _ze-latency-unit-t:

ze_latency_unit_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_latency_unit_t
    :project: LevelZero

 
Common Structures
------------------------------------------------------------------------------

.. _ze-ipc-mem-handle-t:

ze_ipc_mem_handle_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_ipc_mem_handle_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-ipc-event-pool-handle-t:

ze_ipc_event_pool_handle_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_ipc_event_pool_handle_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-uuid-t:

ze_uuid_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-base-cb-params-t:

ze_base_cb_params_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_base_cb_params_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-base-properties-t:

ze_base_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_base_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-base-desc-t:

ze_base_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_base_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Driver
============================================================
* Functions


    * :ref:`zeInit`
    * :ref:`zeDriverGet`
    * :ref:`zeInitDrivers`
    * :ref:`zeDriverGetApiVersion`
    * :ref:`zeDriverGetProperties`
    * :ref:`zeDriverGetIpcProperties`
    * :ref:`zeDriverGetExtensionProperties`
    * :ref:`zeDriverGetExtensionFunctionAddress`
    * :ref:`zeDriverGetLastErrorDescription`

 
* Enumerations


    * :ref:`ze-init-flags-t`
    * :ref:`ze-init-driver-type-flags-t`
    * :ref:`ze-api-version-t`
    * :ref:`ze-ipc-property-flags-t`

 
* Structures


    * :ref:`ze-init-driver-type-desc-t`
    * :ref:`ze-driver-uuid-t`
    * :ref:`ze-driver-properties-t`
    * :ref:`ze-driver-ipc-properties-t`
    * :ref:`ze-driver-extension-properties-t`


Driver Functions
------------------------------------------------------------------------------


.. _zeInit:

zeInit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeInit
    :project: LevelZero


.. _zeDriverGet:

zeDriverGet
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDriverGet
    :project: LevelZero


.. _zeInitDrivers:

zeInitDrivers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeInitDrivers
    :project: LevelZero


.. _zeDriverGetApiVersion:

zeDriverGetApiVersion
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDriverGetApiVersion
    :project: LevelZero


.. _zeDriverGetProperties:

zeDriverGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDriverGetProperties
    :project: LevelZero


.. _zeDriverGetIpcProperties:

zeDriverGetIpcProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDriverGetIpcProperties
    :project: LevelZero


.. _zeDriverGetExtensionProperties:

zeDriverGetExtensionProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDriverGetExtensionProperties
    :project: LevelZero


.. _zeDriverGetExtensionFunctionAddress:

zeDriverGetExtensionFunctionAddress
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDriverGetExtensionFunctionAddress
    :project: LevelZero


.. _zeDriverGetLastErrorDescription:

zeDriverGetLastErrorDescription
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDriverGetLastErrorDescription
    :project: LevelZero



Driver Enums
------------------------------------------------------------------------------


.. _ze-init-flags-t:

ze_init_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_init_flag_t
    :project: LevelZero


.. _ze-init-driver-type-flags-t:

ze_init_driver_type_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_init_driver_type_flag_t
    :project: LevelZero


.. _ze-api-version-t:

ze_api_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_api_version_t
    :project: LevelZero


.. _ze-ipc-property-flags-t:

ze_ipc_property_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_ipc_property_flag_t
    :project: LevelZero

 
Driver Structures
------------------------------------------------------------------------------

.. _ze-init-driver-type-desc-t:

ze_init_driver_type_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_init_driver_type_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-driver-uuid-t:

ze_driver_uuid_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_driver_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-driver-properties-t:

ze_driver_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_driver_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-driver-ipc-properties-t:

ze_driver_ipc_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_driver_ipc_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-driver-extension-properties-t:

ze_driver_extension_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_driver_extension_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Device
============================================================
* Functions


    * :ref:`zeDeviceGet`
    * :ref:`zeDeviceGetRootDevice`
    * :ref:`zeDeviceGetSubDevices`
    * :ref:`zeDeviceGetProperties`
    * :ref:`zeDeviceGetComputeProperties`
    * :ref:`zeDeviceGetModuleProperties`
    * :ref:`zeDeviceGetCommandQueueGroupProperties`
    * :ref:`zeDeviceGetMemoryProperties`
    * :ref:`zeDeviceGetMemoryAccessProperties`
    * :ref:`zeDeviceGetCacheProperties`
    * :ref:`zeDeviceGetImageProperties`
    * :ref:`zeDeviceGetExternalMemoryProperties`
    * :ref:`zeDeviceGetP2PProperties`
    * :ref:`zeDeviceCanAccessPeer`
    * :ref:`zeDeviceGetStatus`
    * :ref:`zeDeviceGetGlobalTimestamps`

 
* Enumerations


    * :ref:`ze-device-type-t`
    * :ref:`ze-device-property-flags-t`
    * :ref:`ze-device-module-flags-t`
    * :ref:`ze-device-fp-flags-t`
    * :ref:`ze-command-queue-group-property-flags-t`
    * :ref:`ze-device-memory-property-flags-t`
    * :ref:`ze-memory-access-cap-flags-t`
    * :ref:`ze-device-cache-property-flags-t`
    * :ref:`ze-device-p2p-property-flags-t`

 
* Structures


    * :ref:`ze-device-uuid-t`
    * :ref:`ze-device-properties-t`
    * :ref:`ze-device-thread-t`
    * :ref:`ze-device-compute-properties-t`
    * :ref:`ze-native-kernel-uuid-t`
    * :ref:`ze-device-module-properties-t`
    * :ref:`ze-command-queue-group-properties-t`
    * :ref:`ze-device-memory-properties-t`
    * :ref:`ze-device-memory-access-properties-t`
    * :ref:`ze-device-cache-properties-t`
    * :ref:`ze-device-image-properties-t`
    * :ref:`ze-device-external-memory-properties-t`
    * :ref:`ze-device-p2p-properties-t`


Device Functions
------------------------------------------------------------------------------


.. _zeDeviceGet:

zeDeviceGet
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGet
    :project: LevelZero


.. _zeDeviceGetRootDevice:

zeDeviceGetRootDevice
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetRootDevice
    :project: LevelZero


.. _zeDeviceGetSubDevices:

zeDeviceGetSubDevices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetSubDevices
    :project: LevelZero


.. _zeDeviceGetProperties:

zeDeviceGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetProperties
    :project: LevelZero


.. _zeDeviceGetComputeProperties:

zeDeviceGetComputeProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetComputeProperties
    :project: LevelZero


.. _zeDeviceGetModuleProperties:

zeDeviceGetModuleProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetModuleProperties
    :project: LevelZero


.. _zeDeviceGetCommandQueueGroupProperties:

zeDeviceGetCommandQueueGroupProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetCommandQueueGroupProperties
    :project: LevelZero


.. _zeDeviceGetMemoryProperties:

zeDeviceGetMemoryProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetMemoryProperties
    :project: LevelZero


.. _zeDeviceGetMemoryAccessProperties:

zeDeviceGetMemoryAccessProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetMemoryAccessProperties
    :project: LevelZero


.. _zeDeviceGetCacheProperties:

zeDeviceGetCacheProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetCacheProperties
    :project: LevelZero


.. _zeDeviceGetImageProperties:

zeDeviceGetImageProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetImageProperties
    :project: LevelZero


.. _zeDeviceGetExternalMemoryProperties:

zeDeviceGetExternalMemoryProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetExternalMemoryProperties
    :project: LevelZero


.. _zeDeviceGetP2PProperties:

zeDeviceGetP2PProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetP2PProperties
    :project: LevelZero


.. _zeDeviceCanAccessPeer:

zeDeviceCanAccessPeer
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceCanAccessPeer
    :project: LevelZero


.. _zeDeviceGetStatus:

zeDeviceGetStatus
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetStatus
    :project: LevelZero


.. _zeDeviceGetGlobalTimestamps:

zeDeviceGetGlobalTimestamps
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetGlobalTimestamps
    :project: LevelZero



Device Enums
------------------------------------------------------------------------------


.. _ze-device-type-t:

ze_device_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_type_t
    :project: LevelZero


.. _ze-device-property-flags-t:

ze_device_property_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_property_flag_t
    :project: LevelZero


.. _ze-device-module-flags-t:

ze_device_module_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_module_flag_t
    :project: LevelZero


.. _ze-device-fp-flags-t:

ze_device_fp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_fp_flag_t
    :project: LevelZero


.. _ze-command-queue-group-property-flags-t:

ze_command_queue_group_property_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_command_queue_group_property_flag_t
    :project: LevelZero


.. _ze-device-memory-property-flags-t:

ze_device_memory_property_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_memory_property_flag_t
    :project: LevelZero


.. _ze-memory-access-cap-flags-t:

ze_memory_access_cap_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_memory_access_cap_flag_t
    :project: LevelZero


.. _ze-device-cache-property-flags-t:

ze_device_cache_property_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_cache_property_flag_t
    :project: LevelZero


.. _ze-device-p2p-property-flags-t:

ze_device_p2p_property_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_p2p_property_flag_t
    :project: LevelZero

 
Device Structures
------------------------------------------------------------------------------

.. _ze-device-uuid-t:

ze_device_uuid_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-properties-t:

ze_device_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-thread-t:

ze_device_thread_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_thread_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-compute-properties-t:

ze_device_compute_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_compute_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-native-kernel-uuid-t:

ze_native_kernel_uuid_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_native_kernel_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-module-properties-t:

ze_device_module_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_module_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-command-queue-group-properties-t:

ze_command_queue_group_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_command_queue_group_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-memory-properties-t:

ze_device_memory_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_memory_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-memory-access-properties-t:

ze_device_memory_access_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_memory_access_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-cache-properties-t:

ze_device_cache_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_cache_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-image-properties-t:

ze_device_image_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_image_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-external-memory-properties-t:

ze_device_external_memory_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_external_memory_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-p2p-properties-t:

ze_device_p2p_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_p2p_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Context
============================================================
* Functions


    * :ref:`zeContextCreate`
    * :ref:`zeContextCreateEx`
    * :ref:`zeContextDestroy`
    * :ref:`zeContextGetStatus`

 
* Enumerations


    * :ref:`ze-context-flags-t`

 
* Structures


    * :ref:`ze-context-desc-t`


Context Functions
------------------------------------------------------------------------------


.. _zeContextCreate:

zeContextCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeContextCreate
    :project: LevelZero


.. _zeContextCreateEx:

zeContextCreateEx
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeContextCreateEx
    :project: LevelZero


.. _zeContextDestroy:

zeContextDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeContextDestroy
    :project: LevelZero


.. _zeContextGetStatus:

zeContextGetStatus
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeContextGetStatus
    :project: LevelZero



Context Enums
------------------------------------------------------------------------------


.. _ze-context-flags-t:

ze_context_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_context_flag_t
    :project: LevelZero

 
Context Structures
------------------------------------------------------------------------------

.. _ze-context-desc-t:

ze_context_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_context_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Cmdqueue
============================================================
* Functions


    * :ref:`zeCommandQueueCreate`
    * :ref:`zeCommandQueueDestroy`
    * :ref:`zeCommandQueueExecuteCommandLists`
    * :ref:`zeCommandQueueSynchronize`
    * :ref:`zeCommandQueueGetOrdinal`
    * :ref:`zeCommandQueueGetIndex`

 
* Enumerations


    * :ref:`ze-command-queue-flags-t`
    * :ref:`ze-command-queue-mode-t`
    * :ref:`ze-command-queue-priority-t`

 
* Structures


    * :ref:`ze-command-queue-desc-t`


Cmdqueue Functions
------------------------------------------------------------------------------


.. _zeCommandQueueCreate:

zeCommandQueueCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandQueueCreate
    :project: LevelZero


.. _zeCommandQueueDestroy:

zeCommandQueueDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandQueueDestroy
    :project: LevelZero


.. _zeCommandQueueExecuteCommandLists:

zeCommandQueueExecuteCommandLists
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandQueueExecuteCommandLists
    :project: LevelZero


.. _zeCommandQueueSynchronize:

zeCommandQueueSynchronize
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandQueueSynchronize
    :project: LevelZero


.. _zeCommandQueueGetOrdinal:

zeCommandQueueGetOrdinal
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandQueueGetOrdinal
    :project: LevelZero


.. _zeCommandQueueGetIndex:

zeCommandQueueGetIndex
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandQueueGetIndex
    :project: LevelZero



Cmdqueue Enums
------------------------------------------------------------------------------


.. _ze-command-queue-flags-t:

ze_command_queue_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_command_queue_flag_t
    :project: LevelZero


.. _ze-command-queue-mode-t:

ze_command_queue_mode_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_command_queue_mode_t
    :project: LevelZero


.. _ze-command-queue-priority-t:

ze_command_queue_priority_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_command_queue_priority_t
    :project: LevelZero

 
Cmdqueue Structures
------------------------------------------------------------------------------

.. _ze-command-queue-desc-t:

ze_command_queue_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_command_queue_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Cmdlist
============================================================
* Functions


    * :ref:`zeCommandListCreate`
    * :ref:`zeCommandListCreateImmediate`
    * :ref:`zeCommandListDestroy`
    * :ref:`zeCommandListClose`
    * :ref:`zeCommandListReset`
    * :ref:`zeCommandListAppendWriteGlobalTimestamp`
    * :ref:`zeCommandListHostSynchronize`
    * :ref:`zeCommandListGetDeviceHandle`
    * :ref:`zeCommandListGetContextHandle`
    * :ref:`zeCommandListGetOrdinal`
    * :ref:`zeCommandListImmediateGetIndex`
    * :ref:`zeCommandListIsImmediate`

 
* Enumerations


    * :ref:`ze-command-list-flags-t`

 
* Structures


    * :ref:`ze-command-list-desc-t`


Cmdlist Functions
------------------------------------------------------------------------------


.. _zeCommandListCreate:

zeCommandListCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListCreate
    :project: LevelZero


.. _zeCommandListCreateImmediate:

zeCommandListCreateImmediate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListCreateImmediate
    :project: LevelZero


.. _zeCommandListDestroy:

zeCommandListDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListDestroy
    :project: LevelZero


.. _zeCommandListClose:

zeCommandListClose
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListClose
    :project: LevelZero


.. _zeCommandListReset:

zeCommandListReset
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListReset
    :project: LevelZero


.. _zeCommandListAppendWriteGlobalTimestamp:

zeCommandListAppendWriteGlobalTimestamp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendWriteGlobalTimestamp
    :project: LevelZero


.. _zeCommandListHostSynchronize:

zeCommandListHostSynchronize
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListHostSynchronize
    :project: LevelZero


.. _zeCommandListGetDeviceHandle:

zeCommandListGetDeviceHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListGetDeviceHandle
    :project: LevelZero


.. _zeCommandListGetContextHandle:

zeCommandListGetContextHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListGetContextHandle
    :project: LevelZero


.. _zeCommandListGetOrdinal:

zeCommandListGetOrdinal
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListGetOrdinal
    :project: LevelZero


.. _zeCommandListImmediateGetIndex:

zeCommandListImmediateGetIndex
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListImmediateGetIndex
    :project: LevelZero


.. _zeCommandListIsImmediate:

zeCommandListIsImmediate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListIsImmediate
    :project: LevelZero



Cmdlist Enums
------------------------------------------------------------------------------


.. _ze-command-list-flags-t:

ze_command_list_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_command_list_flag_t
    :project: LevelZero

 
Cmdlist Structures
------------------------------------------------------------------------------

.. _ze-command-list-desc-t:

ze_command_list_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_command_list_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Barrier
============================================================
* Functions


    * :ref:`zeCommandListAppendBarrier`
    * :ref:`zeCommandListAppendMemoryRangesBarrier`
    * :ref:`zeContextSystemBarrier`

 

 


Barrier Functions
------------------------------------------------------------------------------


.. _zeCommandListAppendBarrier:

zeCommandListAppendBarrier
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendBarrier
    :project: LevelZero


.. _zeCommandListAppendMemoryRangesBarrier:

zeCommandListAppendMemoryRangesBarrier
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendMemoryRangesBarrier
    :project: LevelZero


.. _zeContextSystemBarrier:

zeContextSystemBarrier
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeContextSystemBarrier
    :project: LevelZero



 

 

Copy
============================================================
* Functions


    * :ref:`zeCommandListAppendMemoryCopy`
    * :ref:`zeCommandListAppendMemoryFill`
    * :ref:`zeCommandListAppendMemoryCopyRegion`
    * :ref:`zeCommandListAppendMemoryCopyFromContext`
    * :ref:`zeCommandListAppendImageCopy`
    * :ref:`zeCommandListAppendImageCopyRegion`
    * :ref:`zeCommandListAppendImageCopyToMemory`
    * :ref:`zeCommandListAppendImageCopyFromMemory`
    * :ref:`zeCommandListAppendMemoryPrefetch`
    * :ref:`zeCommandListAppendMemAdvise`

 
* Enumerations


    * :ref:`ze-memory-advice-t`

 
* Structures


    * :ref:`ze-copy-region-t`
    * :ref:`ze-image-region-t`


Copy Functions
------------------------------------------------------------------------------


.. _zeCommandListAppendMemoryCopy:

zeCommandListAppendMemoryCopy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendMemoryCopy
    :project: LevelZero


.. _zeCommandListAppendMemoryFill:

zeCommandListAppendMemoryFill
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendMemoryFill
    :project: LevelZero


.. _zeCommandListAppendMemoryCopyRegion:

zeCommandListAppendMemoryCopyRegion
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendMemoryCopyRegion
    :project: LevelZero


.. _zeCommandListAppendMemoryCopyFromContext:

zeCommandListAppendMemoryCopyFromContext
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendMemoryCopyFromContext
    :project: LevelZero


.. _zeCommandListAppendImageCopy:

zeCommandListAppendImageCopy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendImageCopy
    :project: LevelZero


.. _zeCommandListAppendImageCopyRegion:

zeCommandListAppendImageCopyRegion
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendImageCopyRegion
    :project: LevelZero


.. _zeCommandListAppendImageCopyToMemory:

zeCommandListAppendImageCopyToMemory
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendImageCopyToMemory
    :project: LevelZero


.. _zeCommandListAppendImageCopyFromMemory:

zeCommandListAppendImageCopyFromMemory
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendImageCopyFromMemory
    :project: LevelZero


.. _zeCommandListAppendMemoryPrefetch:

zeCommandListAppendMemoryPrefetch
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendMemoryPrefetch
    :project: LevelZero


.. _zeCommandListAppendMemAdvise:

zeCommandListAppendMemAdvise
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendMemAdvise
    :project: LevelZero



Copy Enums
------------------------------------------------------------------------------


.. _ze-memory-advice-t:

ze_memory_advice_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_memory_advice_t
    :project: LevelZero

 
Copy Structures
------------------------------------------------------------------------------

.. _ze-copy-region-t:

ze_copy_region_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_copy_region_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-image-region-t:

ze_image_region_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_image_region_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Event
============================================================
* Functions


    * :ref:`zeEventPoolCreate`
    * :ref:`zeEventPoolDestroy`
    * :ref:`zeEventCreate`
    * :ref:`zeEventDestroy`
    * :ref:`zeEventPoolGetIpcHandle`
    * :ref:`zeEventPoolPutIpcHandle`
    * :ref:`zeEventPoolOpenIpcHandle`
    * :ref:`zeEventPoolCloseIpcHandle`
    * :ref:`zeCommandListAppendSignalEvent`
    * :ref:`zeCommandListAppendWaitOnEvents`
    * :ref:`zeEventHostSignal`
    * :ref:`zeEventHostSynchronize`
    * :ref:`zeEventQueryStatus`
    * :ref:`zeCommandListAppendEventReset`
    * :ref:`zeEventHostReset`
    * :ref:`zeEventQueryKernelTimestamp`
    * :ref:`zeCommandListAppendQueryKernelTimestamps`
    * :ref:`zeEventGetEventPool`
    * :ref:`zeEventGetSignalScope`
    * :ref:`zeEventGetWaitScope`
    * :ref:`zeEventPoolGetContextHandle`
    * :ref:`zeEventPoolGetFlags`

 
* Enumerations


    * :ref:`ze-event-pool-flags-t`
    * :ref:`ze-event-scope-flags-t`

 
* Structures


    * :ref:`ze-event-pool-desc-t`
    * :ref:`ze-event-desc-t`
    * :ref:`ze-kernel-timestamp-data-t`
    * :ref:`ze-kernel-timestamp-result-t`


Event Functions
------------------------------------------------------------------------------


.. _zeEventPoolCreate:

zeEventPoolCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventPoolCreate
    :project: LevelZero


.. _zeEventPoolDestroy:

zeEventPoolDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventPoolDestroy
    :project: LevelZero


.. _zeEventCreate:

zeEventCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventCreate
    :project: LevelZero


.. _zeEventDestroy:

zeEventDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventDestroy
    :project: LevelZero


.. _zeEventPoolGetIpcHandle:

zeEventPoolGetIpcHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventPoolGetIpcHandle
    :project: LevelZero


.. _zeEventPoolPutIpcHandle:

zeEventPoolPutIpcHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventPoolPutIpcHandle
    :project: LevelZero


.. _zeEventPoolOpenIpcHandle:

zeEventPoolOpenIpcHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventPoolOpenIpcHandle
    :project: LevelZero


.. _zeEventPoolCloseIpcHandle:

zeEventPoolCloseIpcHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventPoolCloseIpcHandle
    :project: LevelZero


.. _zeCommandListAppendSignalEvent:

zeCommandListAppendSignalEvent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendSignalEvent
    :project: LevelZero


.. _zeCommandListAppendWaitOnEvents:

zeCommandListAppendWaitOnEvents
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendWaitOnEvents
    :project: LevelZero


.. _zeEventHostSignal:

zeEventHostSignal
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventHostSignal
    :project: LevelZero


.. _zeEventHostSynchronize:

zeEventHostSynchronize
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventHostSynchronize
    :project: LevelZero


.. _zeEventQueryStatus:

zeEventQueryStatus
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventQueryStatus
    :project: LevelZero


.. _zeCommandListAppendEventReset:

zeCommandListAppendEventReset
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendEventReset
    :project: LevelZero


.. _zeEventHostReset:

zeEventHostReset
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventHostReset
    :project: LevelZero


.. _zeEventQueryKernelTimestamp:

zeEventQueryKernelTimestamp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventQueryKernelTimestamp
    :project: LevelZero


.. _zeCommandListAppendQueryKernelTimestamps:

zeCommandListAppendQueryKernelTimestamps
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendQueryKernelTimestamps
    :project: LevelZero


.. _zeEventGetEventPool:

zeEventGetEventPool
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventGetEventPool
    :project: LevelZero


.. _zeEventGetSignalScope:

zeEventGetSignalScope
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventGetSignalScope
    :project: LevelZero


.. _zeEventGetWaitScope:

zeEventGetWaitScope
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventGetWaitScope
    :project: LevelZero


.. _zeEventPoolGetContextHandle:

zeEventPoolGetContextHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventPoolGetContextHandle
    :project: LevelZero


.. _zeEventPoolGetFlags:

zeEventPoolGetFlags
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventPoolGetFlags
    :project: LevelZero



Event Enums
------------------------------------------------------------------------------


.. _ze-event-pool-flags-t:

ze_event_pool_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_event_pool_flag_t
    :project: LevelZero


.. _ze-event-scope-flags-t:

ze_event_scope_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_event_scope_flag_t
    :project: LevelZero

 
Event Structures
------------------------------------------------------------------------------

.. _ze-event-pool-desc-t:

ze_event_pool_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_event_pool_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-event-desc-t:

ze_event_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_event_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-kernel-timestamp-data-t:

ze_kernel_timestamp_data_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_kernel_timestamp_data_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-kernel-timestamp-result-t:

ze_kernel_timestamp_result_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_kernel_timestamp_result_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Fence
============================================================
* Functions


    * :ref:`zeFenceCreate`
    * :ref:`zeFenceDestroy`
    * :ref:`zeFenceHostSynchronize`
    * :ref:`zeFenceQueryStatus`
    * :ref:`zeFenceReset`

 
* Enumerations


    * :ref:`ze-fence-flags-t`

 
* Structures


    * :ref:`ze-fence-desc-t`


Fence Functions
------------------------------------------------------------------------------


.. _zeFenceCreate:

zeFenceCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFenceCreate
    :project: LevelZero


.. _zeFenceDestroy:

zeFenceDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFenceDestroy
    :project: LevelZero


.. _zeFenceHostSynchronize:

zeFenceHostSynchronize
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFenceHostSynchronize
    :project: LevelZero


.. _zeFenceQueryStatus:

zeFenceQueryStatus
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFenceQueryStatus
    :project: LevelZero


.. _zeFenceReset:

zeFenceReset
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFenceReset
    :project: LevelZero



Fence Enums
------------------------------------------------------------------------------


.. _ze-fence-flags-t:

ze_fence_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_fence_flag_t
    :project: LevelZero

 
Fence Structures
------------------------------------------------------------------------------

.. _ze-fence-desc-t:

ze_fence_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_fence_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Image
============================================================
* Functions


    * :ref:`zeImageGetProperties`
    * :ref:`zeImageCreate`
    * :ref:`zeImageDestroy`

 
* Enumerations


    * :ref:`ze-image-flags-t`
    * :ref:`ze-image-type-t`
    * :ref:`ze-image-format-layout-t`
    * :ref:`ze-image-format-type-t`
    * :ref:`ze-image-format-swizzle-t`
    * :ref:`ze-image-sampler-filter-flags-t`

 
* Structures


    * :ref:`ze-image-format-t`
    * :ref:`ze-image-desc-t`
    * :ref:`ze-image-properties-t`


Image Functions
------------------------------------------------------------------------------


.. _zeImageGetProperties:

zeImageGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeImageGetProperties
    :project: LevelZero


.. _zeImageCreate:

zeImageCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeImageCreate
    :project: LevelZero


.. _zeImageDestroy:

zeImageDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeImageDestroy
    :project: LevelZero



Image Enums
------------------------------------------------------------------------------


.. _ze-image-flags-t:

ze_image_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_flag_t
    :project: LevelZero


.. _ze-image-type-t:

ze_image_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_type_t
    :project: LevelZero


.. _ze-image-format-layout-t:

ze_image_format_layout_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_format_layout_t
    :project: LevelZero


.. _ze-image-format-type-t:

ze_image_format_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_format_type_t
    :project: LevelZero


.. _ze-image-format-swizzle-t:

ze_image_format_swizzle_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_format_swizzle_t
    :project: LevelZero


.. _ze-image-sampler-filter-flags-t:

ze_image_sampler_filter_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_sampler_filter_flag_t
    :project: LevelZero

 
Image Structures
------------------------------------------------------------------------------

.. _ze-image-format-t:

ze_image_format_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_image_format_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-image-desc-t:

ze_image_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_image_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-image-properties-t:

ze_image_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_image_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Memory
============================================================
* Functions


    * :ref:`zeMemAllocShared`
    * :ref:`zeMemAllocDevice`
    * :ref:`zeMemAllocHost`
    * :ref:`zeMemFree`
    * :ref:`zeMemGetAllocProperties`
    * :ref:`zeMemGetAddressRange`
    * :ref:`zeMemGetIpcHandle`
    * :ref:`zeMemGetIpcHandleFromFileDescriptorExp`
    * :ref:`zeMemGetFileDescriptorFromIpcHandleExp`
    * :ref:`zeMemPutIpcHandle`
    * :ref:`zeMemOpenIpcHandle`
    * :ref:`zeMemCloseIpcHandle`
    * :ref:`zeMemSetAtomicAccessAttributeExp`
    * :ref:`zeMemGetAtomicAccessAttributeExp`

 
* Enumerations


    * :ref:`ze-device-mem-alloc-flags-t`
    * :ref:`ze-host-mem-alloc-flags-t`
    * :ref:`ze-memory-type-t`
    * :ref:`ze-ipc-memory-flags-t`
    * :ref:`ze-memory-atomic-attr-exp-flags-t`

 
* Structures


    * :ref:`ze-device-mem-alloc-desc-t`
    * :ref:`ze-host-mem-alloc-desc-t`
    * :ref:`ze-memory-allocation-properties-t`
    * :ref:`ze-external-memory-export-desc-t`
    * :ref:`ze-external-memory-import-fd-t`
    * :ref:`ze-external-memory-export-fd-t`
    * :ref:`ze-external-memory-import-win32-handle-t`
    * :ref:`ze-external-memory-export-win32-handle-t`


Memory Functions
------------------------------------------------------------------------------


.. _zeMemAllocShared:

zeMemAllocShared
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemAllocShared
    :project: LevelZero


.. _zeMemAllocDevice:

zeMemAllocDevice
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemAllocDevice
    :project: LevelZero


.. _zeMemAllocHost:

zeMemAllocHost
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemAllocHost
    :project: LevelZero


.. _zeMemFree:

zeMemFree
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemFree
    :project: LevelZero


.. _zeMemGetAllocProperties:

zeMemGetAllocProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemGetAllocProperties
    :project: LevelZero


.. _zeMemGetAddressRange:

zeMemGetAddressRange
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemGetAddressRange
    :project: LevelZero


.. _zeMemGetIpcHandle:

zeMemGetIpcHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemGetIpcHandle
    :project: LevelZero


.. _zeMemGetIpcHandleFromFileDescriptorExp:

zeMemGetIpcHandleFromFileDescriptorExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemGetIpcHandleFromFileDescriptorExp
    :project: LevelZero


.. _zeMemGetFileDescriptorFromIpcHandleExp:

zeMemGetFileDescriptorFromIpcHandleExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemGetFileDescriptorFromIpcHandleExp
    :project: LevelZero


.. _zeMemPutIpcHandle:

zeMemPutIpcHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemPutIpcHandle
    :project: LevelZero


.. _zeMemOpenIpcHandle:

zeMemOpenIpcHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemOpenIpcHandle
    :project: LevelZero


.. _zeMemCloseIpcHandle:

zeMemCloseIpcHandle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemCloseIpcHandle
    :project: LevelZero


.. _zeMemSetAtomicAccessAttributeExp:

zeMemSetAtomicAccessAttributeExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemSetAtomicAccessAttributeExp
    :project: LevelZero


.. _zeMemGetAtomicAccessAttributeExp:

zeMemGetAtomicAccessAttributeExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemGetAtomicAccessAttributeExp
    :project: LevelZero



Memory Enums
------------------------------------------------------------------------------


.. _ze-device-mem-alloc-flags-t:

ze_device_mem_alloc_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_mem_alloc_flag_t
    :project: LevelZero


.. _ze-host-mem-alloc-flags-t:

ze_host_mem_alloc_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_host_mem_alloc_flag_t
    :project: LevelZero


.. _ze-memory-type-t:

ze_memory_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_memory_type_t
    :project: LevelZero


.. _ze-ipc-memory-flags-t:

ze_ipc_memory_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_ipc_memory_flag_t
    :project: LevelZero


.. _ze-memory-atomic-attr-exp-flags-t:

ze_memory_atomic_attr_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_memory_atomic_attr_exp_flag_t
    :project: LevelZero

 
Memory Structures
------------------------------------------------------------------------------

.. _ze-device-mem-alloc-desc-t:

ze_device_mem_alloc_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_mem_alloc_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-host-mem-alloc-desc-t:

ze_host_mem_alloc_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_host_mem_alloc_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-memory-allocation-properties-t:

ze_memory_allocation_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_memory_allocation_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-external-memory-export-desc-t:

ze_external_memory_export_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_external_memory_export_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-external-memory-import-fd-t:

ze_external_memory_import_fd_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_external_memory_import_fd_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-external-memory-export-fd-t:

ze_external_memory_export_fd_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_external_memory_export_fd_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-external-memory-import-win32-handle-t:

ze_external_memory_import_win32_handle_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_external_memory_import_win32_handle_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-external-memory-export-win32-handle-t:

ze_external_memory_export_win32_handle_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_external_memory_export_win32_handle_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Module
============================================================
* Functions


    * :ref:`zeModuleCreate`
    * :ref:`zeModuleDestroy`
    * :ref:`zeModuleDynamicLink`
    * :ref:`zeModuleBuildLogDestroy`
    * :ref:`zeModuleBuildLogGetString`
    * :ref:`zeModuleGetNativeBinary`
    * :ref:`zeModuleGetGlobalPointer`
    * :ref:`zeModuleGetKernelNames`
    * :ref:`zeModuleGetProperties`
    * :ref:`zeKernelCreate`
    * :ref:`zeKernelDestroy`
    * :ref:`zeModuleGetFunctionPointer`
    * :ref:`zeKernelSetGroupSize`
    * :ref:`zeKernelSuggestGroupSize`
    * :ref:`zeKernelSuggestMaxCooperativeGroupCount`
    * :ref:`zeKernelSetArgumentValue`
    * :ref:`zeKernelSetIndirectAccess`
    * :ref:`zeKernelGetIndirectAccess`
    * :ref:`zeKernelGetSourceAttributes`
    * :ref:`zeKernelSetCacheConfig`
    * :ref:`zeKernelGetProperties`
    * :ref:`zeKernelGetName`
    * :ref:`zeCommandListAppendLaunchKernel`
    * :ref:`zeCommandListAppendLaunchCooperativeKernel`
    * :ref:`zeCommandListAppendLaunchKernelIndirect`
    * :ref:`zeCommandListAppendLaunchMultipleKernelsIndirect`

 
* Enumerations


    * :ref:`ze-module-format-t`
    * :ref:`ze-module-property-flags-t`
    * :ref:`ze-kernel-flags-t`
    * :ref:`ze-kernel-indirect-access-flags-t`
    * :ref:`ze-cache-config-flags-t`

 
* Structures


    * :ref:`ze-module-constants-t`
    * :ref:`ze-module-desc-t`
    * :ref:`ze-module-properties-t`
    * :ref:`ze-kernel-desc-t`
    * :ref:`ze-kernel-uuid-t`
    * :ref:`ze-kernel-properties-t`
    * :ref:`ze-kernel-preferred-group-size-properties-t`
    * :ref:`ze-group-count-t`


Module Functions
------------------------------------------------------------------------------


.. _zeModuleCreate:

zeModuleCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleCreate
    :project: LevelZero


.. _zeModuleDestroy:

zeModuleDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleDestroy
    :project: LevelZero


.. _zeModuleDynamicLink:

zeModuleDynamicLink
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleDynamicLink
    :project: LevelZero


.. _zeModuleBuildLogDestroy:

zeModuleBuildLogDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleBuildLogDestroy
    :project: LevelZero


.. _zeModuleBuildLogGetString:

zeModuleBuildLogGetString
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleBuildLogGetString
    :project: LevelZero


.. _zeModuleGetNativeBinary:

zeModuleGetNativeBinary
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleGetNativeBinary
    :project: LevelZero


.. _zeModuleGetGlobalPointer:

zeModuleGetGlobalPointer
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleGetGlobalPointer
    :project: LevelZero


.. _zeModuleGetKernelNames:

zeModuleGetKernelNames
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleGetKernelNames
    :project: LevelZero


.. _zeModuleGetProperties:

zeModuleGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleGetProperties
    :project: LevelZero


.. _zeKernelCreate:

zeKernelCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelCreate
    :project: LevelZero


.. _zeKernelDestroy:

zeKernelDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelDestroy
    :project: LevelZero


.. _zeModuleGetFunctionPointer:

zeModuleGetFunctionPointer
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleGetFunctionPointer
    :project: LevelZero


.. _zeKernelSetGroupSize:

zeKernelSetGroupSize
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelSetGroupSize
    :project: LevelZero


.. _zeKernelSuggestGroupSize:

zeKernelSuggestGroupSize
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelSuggestGroupSize
    :project: LevelZero


.. _zeKernelSuggestMaxCooperativeGroupCount:

zeKernelSuggestMaxCooperativeGroupCount
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelSuggestMaxCooperativeGroupCount
    :project: LevelZero


.. _zeKernelSetArgumentValue:

zeKernelSetArgumentValue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelSetArgumentValue
    :project: LevelZero


.. _zeKernelSetIndirectAccess:

zeKernelSetIndirectAccess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelSetIndirectAccess
    :project: LevelZero


.. _zeKernelGetIndirectAccess:

zeKernelGetIndirectAccess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelGetIndirectAccess
    :project: LevelZero


.. _zeKernelGetSourceAttributes:

zeKernelGetSourceAttributes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelGetSourceAttributes
    :project: LevelZero


.. _zeKernelSetCacheConfig:

zeKernelSetCacheConfig
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelSetCacheConfig
    :project: LevelZero


.. _zeKernelGetProperties:

zeKernelGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelGetProperties
    :project: LevelZero


.. _zeKernelGetName:

zeKernelGetName
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelGetName
    :project: LevelZero


.. _zeCommandListAppendLaunchKernel:

zeCommandListAppendLaunchKernel
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendLaunchKernel
    :project: LevelZero


.. _zeCommandListAppendLaunchCooperativeKernel:

zeCommandListAppendLaunchCooperativeKernel
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendLaunchCooperativeKernel
    :project: LevelZero


.. _zeCommandListAppendLaunchKernelIndirect:

zeCommandListAppendLaunchKernelIndirect
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendLaunchKernelIndirect
    :project: LevelZero


.. _zeCommandListAppendLaunchMultipleKernelsIndirect:

zeCommandListAppendLaunchMultipleKernelsIndirect
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendLaunchMultipleKernelsIndirect
    :project: LevelZero



Module Enums
------------------------------------------------------------------------------


.. _ze-module-format-t:

ze_module_format_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_module_format_t
    :project: LevelZero


.. _ze-module-property-flags-t:

ze_module_property_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_module_property_flag_t
    :project: LevelZero


.. _ze-kernel-flags-t:

ze_kernel_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_kernel_flag_t
    :project: LevelZero


.. _ze-kernel-indirect-access-flags-t:

ze_kernel_indirect_access_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_kernel_indirect_access_flag_t
    :project: LevelZero


.. _ze-cache-config-flags-t:

ze_cache_config_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_cache_config_flag_t
    :project: LevelZero

 
Module Structures
------------------------------------------------------------------------------

.. _ze-module-constants-t:

ze_module_constants_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_module_constants_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-module-desc-t:

ze_module_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_module_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-module-properties-t:

ze_module_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_module_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-kernel-desc-t:

ze_kernel_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_kernel_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-kernel-uuid-t:

ze_kernel_uuid_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_kernel_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-kernel-properties-t:

ze_kernel_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_kernel_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-kernel-preferred-group-size-properties-t:

ze_kernel_preferred_group_size_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_kernel_preferred_group_size_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-group-count-t:

ze_group_count_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_group_count_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Program
============================================================
* Enumerations


    * :ref:`ze-module-program-exp-version-t`

 
* Structures


    * :ref:`ze-module-program-exp-desc-t`




Program Enums
------------------------------------------------------------------------------


.. _ze-module-program-exp-version-t:

ze_module_program_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_module_program_exp_version_t
    :project: LevelZero

 
Program Structures
------------------------------------------------------------------------------

.. _ze-module-program-exp-desc-t:

ze_module_program_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_module_program_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Raytracing
============================================================
* Enumerations


    * :ref:`ze-raytracing-ext-version-t`
    * :ref:`ze-device-raytracing-ext-flags-t`
    * :ref:`ze-raytracing-mem-alloc-ext-flags-t`

 
* Structures


    * :ref:`ze-device-raytracing-ext-properties-t`
    * :ref:`ze-raytracing-mem-alloc-ext-desc-t`




Raytracing Enums
------------------------------------------------------------------------------


.. _ze-raytracing-ext-version-t:

ze_raytracing_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_raytracing_ext_version_t
    :project: LevelZero


.. _ze-device-raytracing-ext-flags-t:

ze_device_raytracing_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_raytracing_ext_flag_t
    :project: LevelZero


.. _ze-raytracing-mem-alloc-ext-flags-t:

ze_raytracing_mem_alloc_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_raytracing_mem_alloc_ext_flag_t
    :project: LevelZero

 
Raytracing Structures
------------------------------------------------------------------------------

.. _ze-device-raytracing-ext-properties-t:

ze_device_raytracing_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_raytracing_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-raytracing-mem-alloc-ext-desc-t:

ze_raytracing_mem_alloc_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_raytracing_mem_alloc_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Residency
============================================================
* Functions


    * :ref:`zeContextMakeMemoryResident`
    * :ref:`zeContextEvictMemory`
    * :ref:`zeContextMakeImageResident`
    * :ref:`zeContextEvictImage`

 

 


Residency Functions
------------------------------------------------------------------------------


.. _zeContextMakeMemoryResident:

zeContextMakeMemoryResident
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeContextMakeMemoryResident
    :project: LevelZero


.. _zeContextEvictMemory:

zeContextEvictMemory
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeContextEvictMemory
    :project: LevelZero


.. _zeContextMakeImageResident:

zeContextMakeImageResident
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeContextMakeImageResident
    :project: LevelZero


.. _zeContextEvictImage:

zeContextEvictImage
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeContextEvictImage
    :project: LevelZero



 

 

Sampler
============================================================
* Functions


    * :ref:`zeSamplerCreate`
    * :ref:`zeSamplerDestroy`

 
* Enumerations


    * :ref:`ze-sampler-address-mode-t`
    * :ref:`ze-sampler-filter-mode-t`

 
* Structures


    * :ref:`ze-sampler-desc-t`


Sampler Functions
------------------------------------------------------------------------------


.. _zeSamplerCreate:

zeSamplerCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeSamplerCreate
    :project: LevelZero


.. _zeSamplerDestroy:

zeSamplerDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeSamplerDestroy
    :project: LevelZero



Sampler Enums
------------------------------------------------------------------------------


.. _ze-sampler-address-mode-t:

ze_sampler_address_mode_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_sampler_address_mode_t
    :project: LevelZero


.. _ze-sampler-filter-mode-t:

ze_sampler_filter_mode_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_sampler_filter_mode_t
    :project: LevelZero

 
Sampler Structures
------------------------------------------------------------------------------

.. _ze-sampler-desc-t:

ze_sampler_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_sampler_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Virtual
============================================================
* Functions


    * :ref:`zeVirtualMemReserve`
    * :ref:`zeVirtualMemFree`
    * :ref:`zeVirtualMemQueryPageSize`
    * :ref:`zePhysicalMemCreate`
    * :ref:`zePhysicalMemDestroy`
    * :ref:`zeVirtualMemMap`
    * :ref:`zeVirtualMemUnmap`
    * :ref:`zeVirtualMemSetAccessAttribute`
    * :ref:`zeVirtualMemGetAccessAttribute`

 
* Enumerations


    * :ref:`ze-memory-access-attribute-t`
    * :ref:`ze-physical-mem-flags-t`

 
* Structures


    * :ref:`ze-physical-mem-desc-t`


Virtual Functions
------------------------------------------------------------------------------


.. _zeVirtualMemReserve:

zeVirtualMemReserve
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeVirtualMemReserve
    :project: LevelZero


.. _zeVirtualMemFree:

zeVirtualMemFree
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeVirtualMemFree
    :project: LevelZero


.. _zeVirtualMemQueryPageSize:

zeVirtualMemQueryPageSize
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeVirtualMemQueryPageSize
    :project: LevelZero


.. _zePhysicalMemCreate:

zePhysicalMemCreate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zePhysicalMemCreate
    :project: LevelZero


.. _zePhysicalMemDestroy:

zePhysicalMemDestroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zePhysicalMemDestroy
    :project: LevelZero


.. _zeVirtualMemMap:

zeVirtualMemMap
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeVirtualMemMap
    :project: LevelZero


.. _zeVirtualMemUnmap:

zeVirtualMemUnmap
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeVirtualMemUnmap
    :project: LevelZero


.. _zeVirtualMemSetAccessAttribute:

zeVirtualMemSetAccessAttribute
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeVirtualMemSetAccessAttribute
    :project: LevelZero


.. _zeVirtualMemGetAccessAttribute:

zeVirtualMemGetAccessAttribute
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeVirtualMemGetAccessAttribute
    :project: LevelZero



Virtual Enums
------------------------------------------------------------------------------


.. _ze-memory-access-attribute-t:

ze_memory_access_attribute_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_memory_access_attribute_t
    :project: LevelZero


.. _ze-physical-mem-flags-t:

ze_physical_mem_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_physical_mem_flag_t
    :project: LevelZero

 
Virtual Structures
------------------------------------------------------------------------------

.. _ze-physical-mem-desc-t:

ze_physical_mem_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_physical_mem_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Floatatomics
============================================================
* Enumerations


    * :ref:`ze-float-atomics-ext-version-t`
    * :ref:`ze-device-fp-atomic-ext-flags-t`

 
* Structures


    * :ref:`ze-float-atomic-ext-properties-t`




Floatatomics Enums
------------------------------------------------------------------------------


.. _ze-float-atomics-ext-version-t:

ze_float_atomics_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_float_atomics_ext_version_t
    :project: LevelZero


.. _ze-device-fp-atomic-ext-flags-t:

ze_device_fp_atomic_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_fp_atomic_ext_flag_t
    :project: LevelZero

 
Floatatomics Structures
------------------------------------------------------------------------------

.. _ze-float-atomic-ext-properties-t:

ze_float_atomic_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_float_atomic_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Globaloffset
============================================================
* Functions


    * :ref:`zeKernelSetGlobalOffsetExp`

 
* Enumerations


    * :ref:`ze-global-offset-exp-version-t`

 


Globaloffset Functions
------------------------------------------------------------------------------


.. _zeKernelSetGlobalOffsetExp:

zeKernelSetGlobalOffsetExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelSetGlobalOffsetExp
    :project: LevelZero



Globaloffset Enums
------------------------------------------------------------------------------


.. _ze-global-offset-exp-version-t:

ze_global_offset_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_global_offset_exp_version_t
    :project: LevelZero

 

 

 

Relaxedalloclimits
============================================================
* Enumerations


    * :ref:`ze-relaxed-allocation-limits-exp-version-t`
    * :ref:`ze-relaxed-allocation-limits-exp-flags-t`

 
* Structures


    * :ref:`ze-relaxed-allocation-limits-exp-desc-t`




Relaxedalloclimits Enums
------------------------------------------------------------------------------


.. _ze-relaxed-allocation-limits-exp-version-t:

ze_relaxed_allocation_limits_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_relaxed_allocation_limits_exp_version_t
    :project: LevelZero


.. _ze-relaxed-allocation-limits-exp-flags-t:

ze_relaxed_allocation_limits_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_relaxed_allocation_limits_exp_flag_t
    :project: LevelZero

 
Relaxedalloclimits Structures
------------------------------------------------------------------------------

.. _ze-relaxed-allocation-limits-exp-desc-t:

ze_relaxed_allocation_limits_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_relaxed_allocation_limits_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Kernelbinary
============================================================
* Functions


    * :ref:`zeKernelGetBinaryExp`

 
* Enumerations


    * :ref:`ze-kernel-get-binary-exp-version-t`

 


Kernelbinary Functions
------------------------------------------------------------------------------


.. _zeKernelGetBinaryExp:

zeKernelGetBinaryExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelGetBinaryExp
    :project: LevelZero



Kernelbinary Enums
------------------------------------------------------------------------------


.. _ze-kernel-get-binary-exp-version-t:

ze_kernel_get_binary_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_kernel_get_binary_exp_version_t
    :project: LevelZero

 

 

 

Driverddihandles
============================================================
* Enumerations


    * :ref:`ze-driver-ddi-handles-ext-version-t`
    * :ref:`ze-driver-ddi-handle-ext-flags-t`

 
* Structures


    * :ref:`ze-driver-ddi-handles-ext-properties-t`




Driverddihandles Enums
------------------------------------------------------------------------------


.. _ze-driver-ddi-handles-ext-version-t:

ze_driver_ddi_handles_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_driver_ddi_handles_ext_version_t
    :project: LevelZero


.. _ze-driver-ddi-handle-ext-flags-t:

ze_driver_ddi_handle_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_driver_ddi_handle_ext_flag_t
    :project: LevelZero

 
Driverddihandles Structures
------------------------------------------------------------------------------

.. _ze-driver-ddi-handles-ext-properties-t:

ze_driver_ddi_handles_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_driver_ddi_handles_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Externalsemaphores
============================================================
* Functions


    * :ref:`zeDeviceImportExternalSemaphoreExt`
    * :ref:`zeDeviceReleaseExternalSemaphoreExt`
    * :ref:`zeCommandListAppendSignalExternalSemaphoreExt`
    * :ref:`zeCommandListAppendWaitExternalSemaphoreExt`

 
* Enumerations


    * :ref:`ze-external-semaphore-ext-version-t`
    * :ref:`ze-external-semaphore-ext-flags-t`

 
* Structures


    * :ref:`ze-external-semaphore-ext-desc-t`
    * :ref:`ze-external-semaphore-win32-ext-desc-t`
    * :ref:`ze-external-semaphore-fd-ext-desc-t`
    * :ref:`ze-external-semaphore-signal-params-ext-t`
    * :ref:`ze-external-semaphore-wait-params-ext-t`


Externalsemaphores Functions
------------------------------------------------------------------------------


.. _zeDeviceImportExternalSemaphoreExt:

zeDeviceImportExternalSemaphoreExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceImportExternalSemaphoreExt
    :project: LevelZero


.. _zeDeviceReleaseExternalSemaphoreExt:

zeDeviceReleaseExternalSemaphoreExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceReleaseExternalSemaphoreExt
    :project: LevelZero


.. _zeCommandListAppendSignalExternalSemaphoreExt:

zeCommandListAppendSignalExternalSemaphoreExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendSignalExternalSemaphoreExt
    :project: LevelZero


.. _zeCommandListAppendWaitExternalSemaphoreExt:

zeCommandListAppendWaitExternalSemaphoreExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendWaitExternalSemaphoreExt
    :project: LevelZero



Externalsemaphores Enums
------------------------------------------------------------------------------


.. _ze-external-semaphore-ext-version-t:

ze_external_semaphore_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_external_semaphore_ext_version_t
    :project: LevelZero


.. _ze-external-semaphore-ext-flags-t:

ze_external_semaphore_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_external_semaphore_ext_flag_t
    :project: LevelZero

 
Externalsemaphores Structures
------------------------------------------------------------------------------

.. _ze-external-semaphore-ext-desc-t:

ze_external_semaphore_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_external_semaphore_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-external-semaphore-win32-ext-desc-t:

ze_external_semaphore_win32_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_external_semaphore_win32_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-external-semaphore-fd-ext-desc-t:

ze_external_semaphore_fd_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_external_semaphore_fd_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-external-semaphore-signal-params-ext-t:

ze_external_semaphore_signal_params_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_external_semaphore_signal_params_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-external-semaphore-wait-params-ext-t:

ze_external_semaphore_wait_params_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_external_semaphore_wait_params_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Cachelinesize
============================================================
* Enumerations


    * :ref:`ze-device-cache-line-size-ext-version-t`

 
* Structures


    * :ref:`ze-device-cache-line-size-ext-t`




Cachelinesize Enums
------------------------------------------------------------------------------


.. _ze-device-cache-line-size-ext-version-t:

ze_device_cache_line_size_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_cache_line_size_ext_version_t
    :project: LevelZero

 
Cachelinesize Structures
------------------------------------------------------------------------------

.. _ze-device-cache-line-size-ext-t:

ze_device_cache_line_size_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_cache_line_size_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Rtas
============================================================
* Functions


    * :ref:`zeRTASBuilderCreateExt`
    * :ref:`zeRTASBuilderGetBuildPropertiesExt`
    * :ref:`zeDriverRTASFormatCompatibilityCheckExt`
    * :ref:`zeRTASBuilderBuildExt`
    * :ref:`zeRTASBuilderCommandListAppendCopyExt`
    * :ref:`zeRTASBuilderDestroyExt`
    * :ref:`zeRTASParallelOperationCreateExt`
    * :ref:`zeRTASParallelOperationGetPropertiesExt`
    * :ref:`zeRTASParallelOperationJoinExt`
    * :ref:`zeRTASParallelOperationDestroyExt`

 
* Enumerations


    * :ref:`ze-rtas-builder-ext-version-t`
    * :ref:`ze-rtas-device-ext-flags-t`
    * :ref:`ze-rtas-format-ext-t`
    * :ref:`ze-rtas-builder-ext-flags-t`
    * :ref:`ze-rtas-parallel-operation-ext-flags-t`
    * :ref:`ze-rtas-builder-geometry-ext-flags-t`
    * :ref:`ze-rtas-builder-instance-ext-flags-t`
    * :ref:`ze-rtas-builder-build-op-ext-flags-t`
    * :ref:`ze-rtas-builder-build-quality-hint-ext-t`
    * :ref:`ze-rtas-builder-geometry-type-ext-t`
    * :ref:`ze-rtas-builder-input-data-format-ext-t`

 
* Structures


    * :ref:`ze-rtas-builder-ext-desc-t`
    * :ref:`ze-rtas-builder-ext-properties-t`
    * :ref:`ze-rtas-parallel-operation-ext-properties-t`
    * :ref:`ze-rtas-device-ext-properties-t`
    * :ref:`ze-rtas-float3-ext-t`
    * :ref:`ze-rtas-transform-float3x4-column-major-ext-t`
    * :ref:`ze-rtas-transform-float3x4-aligned-column-major-ext-t`
    * :ref:`ze-rtas-transform-float3x4-row-major-ext-t`
    * :ref:`ze-rtas-aabb-ext-t`
    * :ref:`ze-rtas-triangle-indices-uint32-ext-t`
    * :ref:`ze-rtas-quad-indices-uint32-ext-t`
    * :ref:`ze-rtas-builder-geometry-info-ext-t`
    * :ref:`ze-rtas-builder-triangles-geometry-info-ext-t`
    * :ref:`ze-rtas-builder-quads-geometry-info-ext-t`
    * :ref:`ze-rtas-geometry-aabbs-ext-cb-params-t`
    * :ref:`ze-rtas-builder-procedural-geometry-info-ext-t`
    * :ref:`ze-rtas-builder-instance-geometry-info-ext-t`
    * :ref:`ze-rtas-builder-build-op-ext-desc-t`


Rtas Functions
------------------------------------------------------------------------------


.. _zeRTASBuilderCreateExt:

zeRTASBuilderCreateExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASBuilderCreateExt
    :project: LevelZero


.. _zeRTASBuilderGetBuildPropertiesExt:

zeRTASBuilderGetBuildPropertiesExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASBuilderGetBuildPropertiesExt
    :project: LevelZero


.. _zeDriverRTASFormatCompatibilityCheckExt:

zeDriverRTASFormatCompatibilityCheckExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDriverRTASFormatCompatibilityCheckExt
    :project: LevelZero


.. _zeRTASBuilderBuildExt:

zeRTASBuilderBuildExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASBuilderBuildExt
    :project: LevelZero


.. _zeRTASBuilderCommandListAppendCopyExt:

zeRTASBuilderCommandListAppendCopyExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASBuilderCommandListAppendCopyExt
    :project: LevelZero


.. _zeRTASBuilderDestroyExt:

zeRTASBuilderDestroyExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASBuilderDestroyExt
    :project: LevelZero


.. _zeRTASParallelOperationCreateExt:

zeRTASParallelOperationCreateExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASParallelOperationCreateExt
    :project: LevelZero


.. _zeRTASParallelOperationGetPropertiesExt:

zeRTASParallelOperationGetPropertiesExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASParallelOperationGetPropertiesExt
    :project: LevelZero


.. _zeRTASParallelOperationJoinExt:

zeRTASParallelOperationJoinExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASParallelOperationJoinExt
    :project: LevelZero


.. _zeRTASParallelOperationDestroyExt:

zeRTASParallelOperationDestroyExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASParallelOperationDestroyExt
    :project: LevelZero



Rtas Enums
------------------------------------------------------------------------------


.. _ze-rtas-builder-ext-version-t:

ze_rtas_builder_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_ext_version_t
    :project: LevelZero


.. _ze-rtas-device-ext-flags-t:

ze_rtas_device_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_device_ext_flag_t
    :project: LevelZero


.. _ze-rtas-format-ext-t:

ze_rtas_format_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_format_ext_t
    :project: LevelZero


.. _ze-rtas-builder-ext-flags-t:

ze_rtas_builder_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_ext_flag_t
    :project: LevelZero


.. _ze-rtas-parallel-operation-ext-flags-t:

ze_rtas_parallel_operation_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_parallel_operation_ext_flag_t
    :project: LevelZero


.. _ze-rtas-builder-geometry-ext-flags-t:

ze_rtas_builder_geometry_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_geometry_ext_flag_t
    :project: LevelZero


.. _ze-rtas-builder-instance-ext-flags-t:

ze_rtas_builder_instance_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_instance_ext_flag_t
    :project: LevelZero


.. _ze-rtas-builder-build-op-ext-flags-t:

ze_rtas_builder_build_op_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_build_op_ext_flag_t
    :project: LevelZero


.. _ze-rtas-builder-build-quality-hint-ext-t:

ze_rtas_builder_build_quality_hint_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_build_quality_hint_ext_t
    :project: LevelZero


.. _ze-rtas-builder-geometry-type-ext-t:

ze_rtas_builder_geometry_type_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_geometry_type_ext_t
    :project: LevelZero


.. _ze-rtas-builder-input-data-format-ext-t:

ze_rtas_builder_input_data_format_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_input_data_format_ext_t
    :project: LevelZero

 
Rtas Structures
------------------------------------------------------------------------------

.. _ze-rtas-builder-ext-desc-t:

ze_rtas_builder_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-ext-properties-t:

ze_rtas_builder_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-parallel-operation-ext-properties-t:

ze_rtas_parallel_operation_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_parallel_operation_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-device-ext-properties-t:

ze_rtas_device_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_device_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-float3-ext-t:

ze_rtas_float3_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_float3_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-transform-float3x4-column-major-ext-t:

ze_rtas_transform_float3x4_column_major_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_transform_float3x4_column_major_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-transform-float3x4-aligned-column-major-ext-t:

ze_rtas_transform_float3x4_aligned_column_major_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_transform_float3x4_aligned_column_major_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-transform-float3x4-row-major-ext-t:

ze_rtas_transform_float3x4_row_major_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_transform_float3x4_row_major_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-aabb-ext-t:

ze_rtas_aabb_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_aabb_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-triangle-indices-uint32-ext-t:

ze_rtas_triangle_indices_uint32_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_triangle_indices_uint32_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-quad-indices-uint32-ext-t:

ze_rtas_quad_indices_uint32_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_quad_indices_uint32_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-geometry-info-ext-t:

ze_rtas_builder_geometry_info_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_geometry_info_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-triangles-geometry-info-ext-t:

ze_rtas_builder_triangles_geometry_info_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_triangles_geometry_info_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-quads-geometry-info-ext-t:

ze_rtas_builder_quads_geometry_info_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_quads_geometry_info_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-geometry-aabbs-ext-cb-params-t:

ze_rtas_geometry_aabbs_ext_cb_params_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_geometry_aabbs_ext_cb_params_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-procedural-geometry-info-ext-t:

ze_rtas_builder_procedural_geometry_info_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_procedural_geometry_info_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-instance-geometry-info-ext-t:

ze_rtas_builder_instance_geometry_info_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_instance_geometry_info_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-build-op-ext-desc-t:

ze_rtas_builder_build_op_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_build_op_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Devicevectorsizes
============================================================
* Functions


    * :ref:`zeDeviceGetVectorWidthPropertiesExt`

 
* Enumerations


    * :ref:`ze-device-vector-sizes-ext-version-t`

 
* Structures


    * :ref:`ze-device-vector-width-properties-ext-t`


Devicevectorsizes Functions
------------------------------------------------------------------------------


.. _zeDeviceGetVectorWidthPropertiesExt:

zeDeviceGetVectorWidthPropertiesExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetVectorWidthPropertiesExt
    :project: LevelZero



Devicevectorsizes Enums
------------------------------------------------------------------------------


.. _ze-device-vector-sizes-ext-version-t:

ze_device_vector_sizes_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_vector_sizes_ext_version_t
    :project: LevelZero

 
Devicevectorsizes Structures
------------------------------------------------------------------------------

.. _ze-device-vector-width-properties-ext-t:

ze_device_vector_width_properties_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_vector_width_properties_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Cachereservation
============================================================
* Functions


    * :ref:`zeDeviceReserveCacheExt`
    * :ref:`zeDeviceSetCacheAdviceExt`

 
* Enumerations


    * :ref:`ze-cache-reservation-ext-version-t`
    * :ref:`ze-cache-ext-region-t`

 
* Structures


    * :ref:`ze-cache-reservation-ext-desc-t`


Cachereservation Functions
------------------------------------------------------------------------------


.. _zeDeviceReserveCacheExt:

zeDeviceReserveCacheExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceReserveCacheExt
    :project: LevelZero


.. _zeDeviceSetCacheAdviceExt:

zeDeviceSetCacheAdviceExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceSetCacheAdviceExt
    :project: LevelZero



Cachereservation Enums
------------------------------------------------------------------------------


.. _ze-cache-reservation-ext-version-t:

ze_cache_reservation_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_cache_reservation_ext_version_t
    :project: LevelZero


.. _ze-cache-ext-region-t:

ze_cache_ext_region_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_cache_ext_region_t
    :project: LevelZero

 
Cachereservation Structures
------------------------------------------------------------------------------

.. _ze-cache-reservation-ext-desc-t:

ze_cache_reservation_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_cache_reservation_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Eventquerytimestamps
============================================================
* Functions


    * :ref:`zeEventQueryTimestampsExp`

 
* Enumerations


    * :ref:`ze-event-query-timestamps-exp-version-t`

 


Eventquerytimestamps Functions
------------------------------------------------------------------------------


.. _zeEventQueryTimestampsExp:

zeEventQueryTimestampsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventQueryTimestampsExp
    :project: LevelZero



Eventquerytimestamps Enums
------------------------------------------------------------------------------


.. _ze-event-query-timestamps-exp-version-t:

ze_event_query_timestamps_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_event_query_timestamps_exp_version_t
    :project: LevelZero

 

 

Imagememoryproperties
============================================================
* Functions


    * :ref:`zeImageGetMemoryPropertiesExp`

 
* Enumerations


    * :ref:`ze-image-memory-properties-exp-version-t`

 
* Structures


    * :ref:`ze-image-memory-properties-exp-t`


Imagememoryproperties Functions
------------------------------------------------------------------------------


.. _zeImageGetMemoryPropertiesExp:

zeImageGetMemoryPropertiesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeImageGetMemoryPropertiesExp
    :project: LevelZero



Imagememoryproperties Enums
------------------------------------------------------------------------------


.. _ze-image-memory-properties-exp-version-t:

ze_image_memory_properties_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_memory_properties_exp_version_t
    :project: LevelZero

 
Imagememoryproperties Structures
------------------------------------------------------------------------------

.. _ze-image-memory-properties-exp-t:

ze_image_memory_properties_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_image_memory_properties_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Imageview
============================================================
* Functions


    * :ref:`zeImageViewCreateExt`
    * :ref:`zeImageViewCreateExp`

 
* Enumerations


    * :ref:`ze-image-view-ext-version-t`
    * :ref:`ze-image-view-exp-version-t`

 


Imageview Functions
------------------------------------------------------------------------------


.. _zeImageViewCreateExt:

zeImageViewCreateExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeImageViewCreateExt
    :project: LevelZero


.. _zeImageViewCreateExp:

zeImageViewCreateExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeImageViewCreateExp
    :project: LevelZero



Imageview Enums
------------------------------------------------------------------------------


.. _ze-image-view-ext-version-t:

ze_image_view_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_view_ext_version_t
    :project: LevelZero


.. _ze-image-view-exp-version-t:

ze_image_view_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_view_exp_version_t
    :project: LevelZero

 

 

 

Imageviewplanar
============================================================
* Enumerations


    * :ref:`ze-image-view-planar-ext-version-t`
    * :ref:`ze-image-view-planar-exp-version-t`

 
* Structures


    * :ref:`ze-image-view-planar-ext-desc-t`
    * :ref:`ze-image-view-planar-exp-desc-t`




Imageviewplanar Enums
------------------------------------------------------------------------------


.. _ze-image-view-planar-ext-version-t:

ze_image_view_planar_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_view_planar_ext_version_t
    :project: LevelZero


.. _ze-image-view-planar-exp-version-t:

ze_image_view_planar_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_view_planar_exp_version_t
    :project: LevelZero

 
Imageviewplanar Structures
------------------------------------------------------------------------------

.. _ze-image-view-planar-ext-desc-t:

ze_image_view_planar_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_image_view_planar_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-image-view-planar-exp-desc-t:

ze_image_view_planar_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_image_view_planar_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Kernelschedulinghints
============================================================
* Functions


    * :ref:`zeKernelSchedulingHintExp`

 
* Enumerations


    * :ref:`ze-scheduling-hints-exp-version-t`
    * :ref:`ze-scheduling-hint-exp-flags-t`

 
* Structures


    * :ref:`ze-scheduling-hint-exp-properties-t`
    * :ref:`ze-scheduling-hint-exp-desc-t`


Kernelschedulinghints Functions
------------------------------------------------------------------------------


.. _zeKernelSchedulingHintExp:

zeKernelSchedulingHintExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeKernelSchedulingHintExp
    :project: LevelZero



Kernelschedulinghints Enums
------------------------------------------------------------------------------


.. _ze-scheduling-hints-exp-version-t:

ze_scheduling_hints_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_scheduling_hints_exp_version_t
    :project: LevelZero


.. _ze-scheduling-hint-exp-flags-t:

ze_scheduling_hint_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_scheduling_hint_exp_flag_t
    :project: LevelZero

 
Kernelschedulinghints Structures
------------------------------------------------------------------------------

.. _ze-scheduling-hint-exp-properties-t:

ze_scheduling_hint_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_scheduling_hint_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-scheduling-hint-exp-desc-t:

ze_scheduling_hint_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_scheduling_hint_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Linkonceodr
============================================================
* Enumerations


    * :ref:`ze-linkonce-odr-ext-version-t`

 




Linkonceodr Enums
------------------------------------------------------------------------------


.. _ze-linkonce-odr-ext-version-t:

ze_linkonce_odr_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_linkonce_odr_ext_version_t
    :project: LevelZero

 

 

 

Powersavinghint
============================================================
* Enumerations


    * :ref:`ze-power-saving-hint-exp-version-t`
    * :ref:`ze-power-saving-hint-type-t`

 
* Structures


    * :ref:`ze-context-power-saving-hint-exp-desc-t`




Powersavinghint Enums
------------------------------------------------------------------------------


.. _ze-power-saving-hint-exp-version-t:

ze_power_saving_hint_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_power_saving_hint_exp_version_t
    :project: LevelZero


.. _ze-power-saving-hint-type-t:

ze_power_saving_hint_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_power_saving_hint_type_t
    :project: LevelZero

 
Powersavinghint Structures
------------------------------------------------------------------------------

.. _ze-context-power-saving-hint-exp-desc-t:

ze_context_power_saving_hint_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_context_power_saving_hint_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Subgroups
============================================================
* Enumerations


    * :ref:`ze-subgroup-ext-version-t`

 




Subgroups Enums
------------------------------------------------------------------------------


.. _ze-subgroup-ext-version-t:

ze_subgroup_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_subgroup_ext_version_t
    :project: LevelZero

 

 

 

Eucount
============================================================
* Enumerations


    * :ref:`ze-eu-count-ext-version-t`

 
* Structures


    * :ref:`ze-eu-count-ext-t`




Eucount Enums
------------------------------------------------------------------------------


.. _ze-eu-count-ext-version-t:

ze_eu_count_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_eu_count_ext_version_t
    :project: LevelZero

 
Eucount Structures
------------------------------------------------------------------------------

.. _ze-eu-count-ext-t:

ze_eu_count_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_eu_count_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Pciproperties
============================================================
* Functions


    * :ref:`zeDevicePciGetPropertiesExt`

 
* Enumerations


    * :ref:`ze-pci-properties-ext-version-t`

 
* Structures


    * :ref:`ze-pci-address-ext-t`
    * :ref:`ze-pci-speed-ext-t`
    * :ref:`ze-pci-ext-properties-t`


Pciproperties Functions
------------------------------------------------------------------------------


.. _zeDevicePciGetPropertiesExt:

zeDevicePciGetPropertiesExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDevicePciGetPropertiesExt
    :project: LevelZero



Pciproperties Enums
------------------------------------------------------------------------------


.. _ze-pci-properties-ext-version-t:

ze_pci_properties_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_pci_properties_ext_version_t
    :project: LevelZero

 
Pciproperties Structures
------------------------------------------------------------------------------

.. _ze-pci-address-ext-t:

ze_pci_address_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_pci_address_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-pci-speed-ext-t:

ze_pci_speed_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_pci_speed_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-pci-ext-properties-t:

ze_pci_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_pci_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Srgb
============================================================
* Enumerations


    * :ref:`ze-srgb-ext-version-t`

 
* Structures


    * :ref:`ze-srgb-ext-desc-t`




Srgb Enums
------------------------------------------------------------------------------


.. _ze-srgb-ext-version-t:

ze_srgb_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_srgb_ext_version_t
    :project: LevelZero

 
Srgb Structures
------------------------------------------------------------------------------

.. _ze-srgb-ext-desc-t:

ze_srgb_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_srgb_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Imagecopy
============================================================
* Functions


    * :ref:`zeCommandListAppendImageCopyToMemoryExt`
    * :ref:`zeCommandListAppendImageCopyFromMemoryExt`

 
* Enumerations


    * :ref:`ze-image-copy-ext-version-t`

 


Imagecopy Functions
------------------------------------------------------------------------------


.. _zeCommandListAppendImageCopyToMemoryExt:

zeCommandListAppendImageCopyToMemoryExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendImageCopyToMemoryExt
    :project: LevelZero


.. _zeCommandListAppendImageCopyFromMemoryExt:

zeCommandListAppendImageCopyFromMemoryExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListAppendImageCopyFromMemoryExt
    :project: LevelZero



Imagecopy Enums
------------------------------------------------------------------------------


.. _ze-image-copy-ext-version-t:

ze_image_copy_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_copy_ext_version_t
    :project: LevelZero

 

 

Imagequeryallocproperties
============================================================
* Functions


    * :ref:`zeImageGetAllocPropertiesExt`

 
* Enumerations


    * :ref:`ze-image-query-alloc-properties-ext-version-t`

 
* Structures


    * :ref:`ze-image-allocation-ext-properties-t`


Imagequeryallocproperties Functions
------------------------------------------------------------------------------


.. _zeImageGetAllocPropertiesExt:

zeImageGetAllocPropertiesExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeImageGetAllocPropertiesExt
    :project: LevelZero



Imagequeryallocproperties Enums
------------------------------------------------------------------------------


.. _ze-image-query-alloc-properties-ext-version-t:

ze_image_query_alloc_properties_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_query_alloc_properties_ext_version_t
    :project: LevelZero

 
Imagequeryallocproperties Structures
------------------------------------------------------------------------------

.. _ze-image-allocation-ext-properties-t:

ze_image_allocation_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_image_allocation_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Linkageinspection
============================================================
* Functions


    * :ref:`zeModuleInspectLinkageExt`

 
* Enumerations


    * :ref:`ze-linkage-inspection-ext-version-t`
    * :ref:`ze-linkage-inspection-ext-flags-t`

 
* Structures


    * :ref:`ze-linkage-inspection-ext-desc-t`


Linkageinspection Functions
------------------------------------------------------------------------------


.. _zeModuleInspectLinkageExt:

zeModuleInspectLinkageExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeModuleInspectLinkageExt
    :project: LevelZero



Linkageinspection Enums
------------------------------------------------------------------------------


.. _ze-linkage-inspection-ext-version-t:

ze_linkage_inspection_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_linkage_inspection_ext_version_t
    :project: LevelZero


.. _ze-linkage-inspection-ext-flags-t:

ze_linkage_inspection_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_linkage_inspection_ext_flag_t
    :project: LevelZero

 
Linkageinspection Structures
------------------------------------------------------------------------------

.. _ze-linkage-inspection-ext-desc-t:

ze_linkage_inspection_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_linkage_inspection_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Memorycompressionhints
============================================================
* Enumerations


    * :ref:`ze-memory-compression-hints-ext-version-t`
    * :ref:`ze-memory-compression-hints-ext-flags-t`

 
* Structures


    * :ref:`ze-memory-compression-hints-ext-desc-t`




Memorycompressionhints Enums
------------------------------------------------------------------------------


.. _ze-memory-compression-hints-ext-version-t:

ze_memory_compression_hints_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_memory_compression_hints_ext_version_t
    :project: LevelZero


.. _ze-memory-compression-hints-ext-flags-t:

ze_memory_compression_hints_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_memory_compression_hints_ext_flag_t
    :project: LevelZero

 
Memorycompressionhints Structures
------------------------------------------------------------------------------

.. _ze-memory-compression-hints-ext-desc-t:

ze_memory_compression_hints_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_memory_compression_hints_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Memoryfreepolicies
============================================================
* Functions


    * :ref:`zeMemFreeExt`

 
* Enumerations


    * :ref:`ze-memory-free-policies-ext-version-t`
    * :ref:`ze-driver-memory-free-policy-ext-flags-t`

 
* Structures


    * :ref:`ze-driver-memory-free-ext-properties-t`
    * :ref:`ze-memory-free-ext-desc-t`


Memoryfreepolicies Functions
------------------------------------------------------------------------------


.. _zeMemFreeExt:

zeMemFreeExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemFreeExt
    :project: LevelZero



Memoryfreepolicies Enums
------------------------------------------------------------------------------


.. _ze-memory-free-policies-ext-version-t:

ze_memory_free_policies_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_memory_free_policies_ext_version_t
    :project: LevelZero


.. _ze-driver-memory-free-policy-ext-flags-t:

ze_driver_memory_free_policy_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_driver_memory_free_policy_ext_flag_t
    :project: LevelZero

 
Memoryfreepolicies Structures
------------------------------------------------------------------------------

.. _ze-driver-memory-free-ext-properties-t:

ze_driver_memory_free_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_driver_memory_free_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-memory-free-ext-desc-t:

ze_memory_free_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_memory_free_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

 

Bandwidth
============================================================
* Structures


    * :ref:`ze-device-p2p-bandwidth-exp-properties-t`
    * :ref:`ze-copy-bandwidth-exp-properties-t`




 
Bandwidth Structures
------------------------------------------------------------------------------

.. _ze-device-p2p-bandwidth-exp-properties-t:

ze_device_p2p_bandwidth_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_p2p_bandwidth_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-copy-bandwidth-exp-properties-t:

ze_copy_bandwidth_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_copy_bandwidth_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Deviceluid
============================================================
* Enumerations


    * :ref:`ze-device-luid-ext-version-t`

 
* Structures


    * :ref:`ze-device-luid-ext-t`
    * :ref:`ze-device-luid-ext-properties-t`




Deviceluid Enums
------------------------------------------------------------------------------


.. _ze-device-luid-ext-version-t:

ze_device_luid_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_luid_ext_version_t
    :project: LevelZero

 
Deviceluid Structures
------------------------------------------------------------------------------

.. _ze-device-luid-ext-t:

ze_device_luid_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_luid_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-luid-ext-properties-t:

ze_device_luid_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_luid_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Fabric
============================================================
* Functions


    * :ref:`zeFabricVertexGetExp`
    * :ref:`zeFabricVertexGetSubVerticesExp`
    * :ref:`zeFabricVertexGetPropertiesExp`
    * :ref:`zeFabricVertexGetDeviceExp`
    * :ref:`zeDeviceGetFabricVertexExp`
    * :ref:`zeFabricEdgeGetExp`
    * :ref:`zeFabricEdgeGetVerticesExp`
    * :ref:`zeFabricEdgeGetPropertiesExp`

 
* Enumerations


    * :ref:`ze-fabric-vertex-exp-type-t`
    * :ref:`ze-fabric-edge-exp-duplexity-t`

 
* Structures


    * :ref:`ze-fabric-vertex-pci-exp-address-t`
    * :ref:`ze-fabric-vertex-exp-properties-t`
    * :ref:`ze-fabric-edge-exp-properties-t`


Fabric Functions
------------------------------------------------------------------------------


.. _zeFabricVertexGetExp:

zeFabricVertexGetExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFabricVertexGetExp
    :project: LevelZero


.. _zeFabricVertexGetSubVerticesExp:

zeFabricVertexGetSubVerticesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFabricVertexGetSubVerticesExp
    :project: LevelZero


.. _zeFabricVertexGetPropertiesExp:

zeFabricVertexGetPropertiesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFabricVertexGetPropertiesExp
    :project: LevelZero


.. _zeFabricVertexGetDeviceExp:

zeFabricVertexGetDeviceExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFabricVertexGetDeviceExp
    :project: LevelZero


.. _zeDeviceGetFabricVertexExp:

zeDeviceGetFabricVertexExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDeviceGetFabricVertexExp
    :project: LevelZero


.. _zeFabricEdgeGetExp:

zeFabricEdgeGetExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFabricEdgeGetExp
    :project: LevelZero


.. _zeFabricEdgeGetVerticesExp:

zeFabricEdgeGetVerticesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFabricEdgeGetVerticesExp
    :project: LevelZero


.. _zeFabricEdgeGetPropertiesExp:

zeFabricEdgeGetPropertiesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeFabricEdgeGetPropertiesExp
    :project: LevelZero



Fabric Enums
------------------------------------------------------------------------------


.. _ze-fabric-vertex-exp-type-t:

ze_fabric_vertex_exp_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_fabric_vertex_exp_type_t
    :project: LevelZero


.. _ze-fabric-edge-exp-duplexity-t:

ze_fabric_edge_exp_duplexity_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_fabric_edge_exp_duplexity_t
    :project: LevelZero

 
Fabric Structures
------------------------------------------------------------------------------

.. _ze-fabric-vertex-pci-exp-address-t:

ze_fabric_vertex_pci_exp_address_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_fabric_vertex_pci_exp_address_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-fabric-vertex-exp-properties-t:

ze_fabric_vertex_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_fabric_vertex_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-fabric-edge-exp-properties-t:

ze_fabric_edge_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_fabric_edge_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Memoryproperties
============================================================
* Enumerations


    * :ref:`ze-device-memory-properties-ext-version-t`
    * :ref:`ze-device-memory-ext-type-t`

 
* Structures


    * :ref:`ze-device-memory-ext-properties-t`




Memoryproperties Enums
------------------------------------------------------------------------------


.. _ze-device-memory-properties-ext-version-t:

ze_device_memory_properties_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_memory_properties_ext_version_t
    :project: LevelZero


.. _ze-device-memory-ext-type-t:

ze_device_memory_ext_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_memory_ext_type_t
    :project: LevelZero

 
Memoryproperties Structures
------------------------------------------------------------------------------

.. _ze-device-memory-ext-properties-t:

ze_device_memory_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_memory_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Bfloat16conversions
============================================================
* Enumerations


    * :ref:`ze-bfloat16-conversions-ext-version-t`

 




Bfloat16conversions Enums
------------------------------------------------------------------------------


.. _ze-bfloat16-conversions-ext-version-t:

ze_bfloat16_conversions_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_bfloat16_conversions_ext_version_t
    :project: LevelZero

 

 

 

Deviceipversion
============================================================
* Enumerations


    * :ref:`ze-device-ip-version-version-t`

 
* Structures


    * :ref:`ze-device-ip-version-ext-t`




Deviceipversion Enums
------------------------------------------------------------------------------


.. _ze-device-ip-version-version-t:

ze_device_ip_version_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_device_ip_version_version_t
    :project: LevelZero

 
Deviceipversion Structures
------------------------------------------------------------------------------

.. _ze-device-ip-version-ext-t:

ze_device_ip_version_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_ip_version_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Kernelmaxgroupsizeproperties
============================================================
* Enumerations


    * :ref:`ze-kernel-max-group-size-properties-ext-version-t`

 
* Structures


    * :ref:`ze-kernel-max-group-size-properties-ext-t`




Kernelmaxgroupsizeproperties Enums
------------------------------------------------------------------------------


.. _ze-kernel-max-group-size-properties-ext-version-t:

ze_kernel_max_group_size_properties_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_kernel_max_group_size_properties_ext_version_t
    :project: LevelZero

 
Kernelmaxgroupsizeproperties Structures
------------------------------------------------------------------------------

.. _ze-kernel-max-group-size-properties-ext-t:

ze_kernel_max_group_size_properties_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_kernel_max_group_size_properties_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Suballocationsproperties
============================================================
* Enumerations


    * :ref:`ze-sub-allocations-exp-version-t`

 
* Structures


    * :ref:`ze-sub-allocation-t`
    * :ref:`ze-memory-sub-allocations-exp-properties-t`




Suballocationsproperties Enums
------------------------------------------------------------------------------


.. _ze-sub-allocations-exp-version-t:

ze_sub_allocations_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_sub_allocations_exp_version_t
    :project: LevelZero

 
Suballocationsproperties Structures
------------------------------------------------------------------------------

.. _ze-sub-allocation-t:

ze_sub_allocation_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_sub_allocation_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-memory-sub-allocations-exp-properties-t:

ze_memory_sub_allocations_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_memory_sub_allocations_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Eventquerykerneltimestamps
============================================================
* Functions


    * :ref:`zeEventQueryKernelTimestampsExt`

 
* Enumerations


    * :ref:`ze-event-query-kernel-timestamps-ext-version-t`
    * :ref:`ze-event-query-kernel-timestamps-ext-flags-t`

 
* Structures


    * :ref:`ze-event-query-kernel-timestamps-ext-properties-t`
    * :ref:`ze-synchronized-timestamp-data-ext-t`
    * :ref:`ze-synchronized-timestamp-result-ext-t`
    * :ref:`ze-event-query-kernel-timestamps-results-ext-properties-t`


Eventquerykerneltimestamps Functions
------------------------------------------------------------------------------


.. _zeEventQueryKernelTimestampsExt:

zeEventQueryKernelTimestampsExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeEventQueryKernelTimestampsExt
    :project: LevelZero



Eventquerykerneltimestamps Enums
------------------------------------------------------------------------------


.. _ze-event-query-kernel-timestamps-ext-version-t:

ze_event_query_kernel_timestamps_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_event_query_kernel_timestamps_ext_version_t
    :project: LevelZero


.. _ze-event-query-kernel-timestamps-ext-flags-t:

ze_event_query_kernel_timestamps_ext_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_event_query_kernel_timestamps_ext_flag_t
    :project: LevelZero

 
Eventquerykerneltimestamps Structures
------------------------------------------------------------------------------

.. _ze-event-query-kernel-timestamps-ext-properties-t:

ze_event_query_kernel_timestamps_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_event_query_kernel_timestamps_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-synchronized-timestamp-data-ext-t:

ze_synchronized_timestamp_data_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_synchronized_timestamp_data_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-synchronized-timestamp-result-ext-t:

ze_synchronized_timestamp_result_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_synchronized_timestamp_result_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-event-query-kernel-timestamps-results-ext-properties-t:

ze_event_query_kernel_timestamps_results_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_event_query_kernel_timestamps_results_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Rtasbuilder
============================================================
* Functions


    * :ref:`zeRTASBuilderCreateExp`
    * :ref:`zeRTASBuilderGetBuildPropertiesExp`
    * :ref:`zeDriverRTASFormatCompatibilityCheckExp`
    * :ref:`zeRTASBuilderBuildExp`
    * :ref:`zeRTASBuilderDestroyExp`
    * :ref:`zeRTASParallelOperationCreateExp`
    * :ref:`zeRTASParallelOperationGetPropertiesExp`
    * :ref:`zeRTASParallelOperationJoinExp`
    * :ref:`zeRTASParallelOperationDestroyExp`

 
* Enumerations


    * :ref:`ze-rtas-builder-exp-version-t`
    * :ref:`ze-rtas-device-exp-flags-t`
    * :ref:`ze-rtas-format-exp-t`
    * :ref:`ze-rtas-builder-exp-flags-t`
    * :ref:`ze-rtas-parallel-operation-exp-flags-t`
    * :ref:`ze-rtas-builder-geometry-exp-flags-t`
    * :ref:`ze-rtas-builder-instance-exp-flags-t`
    * :ref:`ze-rtas-builder-build-op-exp-flags-t`
    * :ref:`ze-rtas-builder-build-quality-hint-exp-t`
    * :ref:`ze-rtas-builder-geometry-type-exp-t`
    * :ref:`ze-rtas-builder-input-data-format-exp-t`

 
* Structures


    * :ref:`ze-rtas-builder-exp-desc-t`
    * :ref:`ze-rtas-builder-exp-properties-t`
    * :ref:`ze-rtas-parallel-operation-exp-properties-t`
    * :ref:`ze-rtas-device-exp-properties-t`
    * :ref:`ze-rtas-float3-exp-t`
    * :ref:`ze-rtas-transform-float3x4-column-major-exp-t`
    * :ref:`ze-rtas-transform-float3x4-aligned-column-major-exp-t`
    * :ref:`ze-rtas-transform-float3x4-row-major-exp-t`
    * :ref:`ze-rtas-aabb-exp-t`
    * :ref:`ze-rtas-triangle-indices-uint32-exp-t`
    * :ref:`ze-rtas-quad-indices-uint32-exp-t`
    * :ref:`ze-rtas-builder-geometry-info-exp-t`
    * :ref:`ze-rtas-builder-triangles-geometry-info-exp-t`
    * :ref:`ze-rtas-builder-quads-geometry-info-exp-t`
    * :ref:`ze-rtas-geometry-aabbs-exp-cb-params-t`
    * :ref:`ze-rtas-builder-procedural-geometry-info-exp-t`
    * :ref:`ze-rtas-builder-instance-geometry-info-exp-t`
    * :ref:`ze-rtas-builder-build-op-exp-desc-t`


Rtasbuilder Functions
------------------------------------------------------------------------------


.. _zeRTASBuilderCreateExp:

zeRTASBuilderCreateExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASBuilderCreateExp
    :project: LevelZero


.. _zeRTASBuilderGetBuildPropertiesExp:

zeRTASBuilderGetBuildPropertiesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASBuilderGetBuildPropertiesExp
    :project: LevelZero


.. _zeDriverRTASFormatCompatibilityCheckExp:

zeDriverRTASFormatCompatibilityCheckExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeDriverRTASFormatCompatibilityCheckExp
    :project: LevelZero


.. _zeRTASBuilderBuildExp:

zeRTASBuilderBuildExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASBuilderBuildExp
    :project: LevelZero


.. _zeRTASBuilderDestroyExp:

zeRTASBuilderDestroyExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASBuilderDestroyExp
    :project: LevelZero


.. _zeRTASParallelOperationCreateExp:

zeRTASParallelOperationCreateExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASParallelOperationCreateExp
    :project: LevelZero


.. _zeRTASParallelOperationGetPropertiesExp:

zeRTASParallelOperationGetPropertiesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASParallelOperationGetPropertiesExp
    :project: LevelZero


.. _zeRTASParallelOperationJoinExp:

zeRTASParallelOperationJoinExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASParallelOperationJoinExp
    :project: LevelZero


.. _zeRTASParallelOperationDestroyExp:

zeRTASParallelOperationDestroyExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeRTASParallelOperationDestroyExp
    :project: LevelZero



Rtasbuilder Enums
------------------------------------------------------------------------------


.. _ze-rtas-builder-exp-version-t:

ze_rtas_builder_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_exp_version_t
    :project: LevelZero


.. _ze-rtas-device-exp-flags-t:

ze_rtas_device_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_device_exp_flag_t
    :project: LevelZero


.. _ze-rtas-format-exp-t:

ze_rtas_format_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_format_exp_t
    :project: LevelZero


.. _ze-rtas-builder-exp-flags-t:

ze_rtas_builder_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_exp_flag_t
    :project: LevelZero


.. _ze-rtas-parallel-operation-exp-flags-t:

ze_rtas_parallel_operation_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_parallel_operation_exp_flag_t
    :project: LevelZero


.. _ze-rtas-builder-geometry-exp-flags-t:

ze_rtas_builder_geometry_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_geometry_exp_flag_t
    :project: LevelZero


.. _ze-rtas-builder-instance-exp-flags-t:

ze_rtas_builder_instance_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_instance_exp_flag_t
    :project: LevelZero


.. _ze-rtas-builder-build-op-exp-flags-t:

ze_rtas_builder_build_op_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_build_op_exp_flag_t
    :project: LevelZero


.. _ze-rtas-builder-build-quality-hint-exp-t:

ze_rtas_builder_build_quality_hint_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_build_quality_hint_exp_t
    :project: LevelZero


.. _ze-rtas-builder-geometry-type-exp-t:

ze_rtas_builder_geometry_type_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_geometry_type_exp_t
    :project: LevelZero


.. _ze-rtas-builder-input-data-format-exp-t:

ze_rtas_builder_input_data_format_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_rtas_builder_input_data_format_exp_t
    :project: LevelZero

 
Rtasbuilder Structures
------------------------------------------------------------------------------

.. _ze-rtas-builder-exp-desc-t:

ze_rtas_builder_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-exp-properties-t:

ze_rtas_builder_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-parallel-operation-exp-properties-t:

ze_rtas_parallel_operation_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_parallel_operation_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-device-exp-properties-t:

ze_rtas_device_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_device_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-float3-exp-t:

ze_rtas_float3_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_float3_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-transform-float3x4-column-major-exp-t:

ze_rtas_transform_float3x4_column_major_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_transform_float3x4_column_major_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-transform-float3x4-aligned-column-major-exp-t:

ze_rtas_transform_float3x4_aligned_column_major_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_transform_float3x4_aligned_column_major_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-transform-float3x4-row-major-exp-t:

ze_rtas_transform_float3x4_row_major_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_transform_float3x4_row_major_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-aabb-exp-t:

ze_rtas_aabb_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_aabb_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-triangle-indices-uint32-exp-t:

ze_rtas_triangle_indices_uint32_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_triangle_indices_uint32_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-quad-indices-uint32-exp-t:

ze_rtas_quad_indices_uint32_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_quad_indices_uint32_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-geometry-info-exp-t:

ze_rtas_builder_geometry_info_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_geometry_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-triangles-geometry-info-exp-t:

ze_rtas_builder_triangles_geometry_info_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_triangles_geometry_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-quads-geometry-info-exp-t:

ze_rtas_builder_quads_geometry_info_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_quads_geometry_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-geometry-aabbs-exp-cb-params-t:

ze_rtas_geometry_aabbs_exp_cb_params_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_geometry_aabbs_exp_cb_params_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-procedural-geometry-info-exp-t:

ze_rtas_builder_procedural_geometry_info_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_procedural_geometry_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-instance-geometry-info-exp-t:

ze_rtas_builder_instance_geometry_info_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_instance_geometry_info_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-rtas-builder-build-op-exp-desc-t:

ze_rtas_builder_build_op_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_rtas_builder_build_op_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Counterbasedeventpool
============================================================
* Enumerations


    * :ref:`ze-event-pool-counter-based-exp-version-t`
    * :ref:`ze-event-pool-counter-based-exp-flags-t`

 
* Structures


    * :ref:`ze-event-pool-counter-based-exp-desc-t`




Counterbasedeventpool Enums
------------------------------------------------------------------------------


.. _ze-event-pool-counter-based-exp-version-t:

ze_event_pool_counter_based_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_event_pool_counter_based_exp_version_t
    :project: LevelZero


.. _ze-event-pool-counter-based-exp-flags-t:

ze_event_pool_counter_based_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_event_pool_counter_based_exp_flag_t
    :project: LevelZero

 
Counterbasedeventpool Structures
------------------------------------------------------------------------------

.. _ze-event-pool-counter-based-exp-desc-t:

ze_event_pool_counter_based_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_event_pool_counter_based_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Bindlessimages
============================================================
* Functions


    * :ref:`zeMemGetPitchFor2dImage`
    * :ref:`zeImageGetDeviceOffsetExp`

 
* Enumerations


    * :ref:`ze-bindless-image-exp-version-t`
    * :ref:`ze-image-bindless-exp-flags-t`

 
* Structures


    * :ref:`ze-image-bindless-exp-desc-t`
    * :ref:`ze-image-pitched-exp-desc-t`
    * :ref:`ze-device-pitched-alloc-exp-properties-t`


Bindlessimages Functions
------------------------------------------------------------------------------


.. _zeMemGetPitchFor2dImage:

zeMemGetPitchFor2dImage
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeMemGetPitchFor2dImage
    :project: LevelZero


.. _zeImageGetDeviceOffsetExp:

zeImageGetDeviceOffsetExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeImageGetDeviceOffsetExp
    :project: LevelZero



Bindlessimages Enums
------------------------------------------------------------------------------


.. _ze-bindless-image-exp-version-t:

ze_bindless_image_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_bindless_image_exp_version_t
    :project: LevelZero


.. _ze-image-bindless-exp-flags-t:

ze_image_bindless_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_image_bindless_exp_flag_t
    :project: LevelZero

 
Bindlessimages Structures
------------------------------------------------------------------------------

.. _ze-image-bindless-exp-desc-t:

ze_image_bindless_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_image_bindless_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-image-pitched-exp-desc-t:

ze_image_pitched_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_image_pitched_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-device-pitched-alloc-exp-properties-t:

ze_device_pitched_alloc_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_device_pitched_alloc_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Commandlistclone
============================================================
* Functions


    * :ref:`zeCommandListCreateCloneExp`

 
* Enumerations


    * :ref:`ze-command-list-clone-exp-version-t`

 


Commandlistclone Functions
------------------------------------------------------------------------------


.. _zeCommandListCreateCloneExp:

zeCommandListCreateCloneExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListCreateCloneExp
    :project: LevelZero



Commandlistclone Enums
------------------------------------------------------------------------------


.. _ze-command-list-clone-exp-version-t:

ze_command_list_clone_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_command_list_clone_exp_version_t
    :project: LevelZero

 

 

Immediatecommandlistappend
============================================================
* Functions


    * :ref:`zeCommandListImmediateAppendCommandListsExp`

 
* Enumerations


    * :ref:`ze-immediate-command-list-append-exp-version-t`

 


Immediatecommandlistappend Functions
------------------------------------------------------------------------------


.. _zeCommandListImmediateAppendCommandListsExp:

zeCommandListImmediateAppendCommandListsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListImmediateAppendCommandListsExp
    :project: LevelZero



Immediatecommandlistappend Enums
------------------------------------------------------------------------------


.. _ze-immediate-command-list-append-exp-version-t:

ze_immediate_command_list_append_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_immediate_command_list_append_exp_version_t
    :project: LevelZero

 

 

Mutablecommandlist
============================================================
* Functions


    * :ref:`zeCommandListGetNextCommandIdExp`
    * :ref:`zeCommandListGetNextCommandIdWithKernelsExp`
    * :ref:`zeCommandListUpdateMutableCommandsExp`
    * :ref:`zeCommandListUpdateMutableCommandSignalEventExp`
    * :ref:`zeCommandListUpdateMutableCommandWaitEventsExp`
    * :ref:`zeCommandListUpdateMutableCommandKernelsExp`

 
* Enumerations


    * :ref:`ze-mutable-command-list-exp-version-t`
    * :ref:`ze-mutable-command-exp-flags-t`
    * :ref:`ze-mutable-command-list-exp-flags-t`

 
* Structures


    * :ref:`ze-mutable-command-id-exp-desc-t`
    * :ref:`ze-mutable-command-list-exp-properties-t`
    * :ref:`ze-mutable-command-list-exp-desc-t`
    * :ref:`ze-mutable-commands-exp-desc-t`
    * :ref:`ze-mutable-kernel-argument-exp-desc-t`
    * :ref:`ze-mutable-group-count-exp-desc-t`
    * :ref:`ze-mutable-group-size-exp-desc-t`
    * :ref:`ze-mutable-global-offset-exp-desc-t`
    * :ref:`ze-mutable-graph-argument-exp-desc-t`


Mutablecommandlist Functions
------------------------------------------------------------------------------


.. _zeCommandListGetNextCommandIdExp:

zeCommandListGetNextCommandIdExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListGetNextCommandIdExp
    :project: LevelZero


.. _zeCommandListGetNextCommandIdWithKernelsExp:

zeCommandListGetNextCommandIdWithKernelsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListGetNextCommandIdWithKernelsExp
    :project: LevelZero


.. _zeCommandListUpdateMutableCommandsExp:

zeCommandListUpdateMutableCommandsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListUpdateMutableCommandsExp
    :project: LevelZero


.. _zeCommandListUpdateMutableCommandSignalEventExp:

zeCommandListUpdateMutableCommandSignalEventExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListUpdateMutableCommandSignalEventExp
    :project: LevelZero


.. _zeCommandListUpdateMutableCommandWaitEventsExp:

zeCommandListUpdateMutableCommandWaitEventsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListUpdateMutableCommandWaitEventsExp
    :project: LevelZero


.. _zeCommandListUpdateMutableCommandKernelsExp:

zeCommandListUpdateMutableCommandKernelsExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zeCommandListUpdateMutableCommandKernelsExp
    :project: LevelZero



Mutablecommandlist Enums
------------------------------------------------------------------------------


.. _ze-mutable-command-list-exp-version-t:

ze_mutable_command_list_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_mutable_command_list_exp_version_t
    :project: LevelZero


.. _ze-mutable-command-exp-flags-t:

ze_mutable_command_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_mutable_command_exp_flag_t
    :project: LevelZero


.. _ze-mutable-command-list-exp-flags-t:

ze_mutable_command_list_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: ze_mutable_command_list_exp_flag_t
    :project: LevelZero

 
Mutablecommandlist Structures
------------------------------------------------------------------------------

.. _ze-mutable-command-id-exp-desc-t:

ze_mutable_command_id_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_mutable_command_id_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-mutable-command-list-exp-properties-t:

ze_mutable_command_list_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_mutable_command_list_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-mutable-command-list-exp-desc-t:

ze_mutable_command_list_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_mutable_command_list_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-mutable-commands-exp-desc-t:

ze_mutable_commands_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_mutable_commands_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-mutable-kernel-argument-exp-desc-t:

ze_mutable_kernel_argument_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_mutable_kernel_argument_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-mutable-group-count-exp-desc-t:

ze_mutable_group_count_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_mutable_group_count_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-mutable-group-size-exp-desc-t:

ze_mutable_group_size_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_mutable_group_size_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-mutable-global-offset-exp-desc-t:

ze_mutable_global_offset_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_mutable_global_offset_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _ze-mutable-graph-argument-exp-desc-t:

ze_mutable_graph_argument_exp_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: ze_mutable_graph_argument_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


