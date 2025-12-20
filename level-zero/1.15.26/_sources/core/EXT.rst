
============
 Extensions
============

Objective
=========

Features which are device- or vendor-specific can be exposed as extensions.

There are three types of extensions defined by this specification:

1. **Standard** - extensions ratified for inclusion into the current and all future versions of the specification.
2. **Experimental** - extensions require additional experimentation and feedback from application vendors
   before ratification, therefore applications should not rely on experimental extensions in production.
3. **Implementation non-standard** - extensions provided by a Level Zero driver that are not defined in this specification.

For **Implementation non-standard** extensions, it is the responsibility of the Level Zero Driver to define and document such non-standard extensions
and also to ensure these extensions do not conflict or interfere with any features or extensions of the specification APIs or features.

The following table summarizes the APIs used for discovery of different extension types.
:ref:`zeDriverGetExtensionProperties` has been available since inception of this specification, while other APIs were added in later versions as noted below.

=============== =================== ============================= ========================================
 API Category   Version API added   Extension Type                Extension Discovery API
=============== =================== ============================= ========================================
 Core           NA                  Standard                      :ref:`zeDriverGetExtensionProperties`
 Core           NA                  Experimental                  :ref:`zeDriverGetExtensionProperties`
 Core           1.1                 Implementation non-standard   :ref:`zeDriverGetExtensionFunctionAddress`
 Sysman         1.8                 Standard                      :ref:`zesDriverGetExtensionProperties`
 Sysman         1.8                 Experimental                  :ref:`zesDriverGetExtensionProperties`
 Sysman         1.8                 Implementation non-standard   :ref:`zesDriverGetExtensionFunctionAddress`
=============== =================== ============================= ========================================

Requirements
============

- Extensions must use globally unique names for macros, enums, structures, and functions
- Extensions must have globally unique extension names reported from :ref:`zeDriverGetExtensionProperties` and :ref:`zesDriverGetExtensionProperties`
- All standard and experimental extensions must be defined in this specification
- Extensions must not break backwards compatibility of standard APIs
- Standard extension versions must be backwards compatible with prior versions

Naming Convention
-----------------

The following naming conventions must be followed for **standard** extensions:

  - **Functions:** Must be postfixed with `Ext`

  - Example: zeDeviceImportExternalSemaphoreExt

  - **Macros:** All caps with appropriate prefix

    - Core: `ZE_NAME_EXT_*`
    - Sysman: `ZES_NAME_EXT_*`

    - Example: ZE_MAX_FABRIC_EDGE_MODEL_EXT_SIZE

  - **Structures, enumerations, and other types:** Snake case with appropriate prefix

    - Core: `ze_name_ext_*_t`
    - Sysman: `zes_name_ext_*_t`

    - Example(s): ze_device_ip_version_ext_t or ze_cache_reservation_ext_desc_t

  - **Enumerator values:** All caps with appropriate prefix

    - Core: `ZE_ENUM_EXT_ETOR_NAME`
    - Sysman: `ZES_ENUM_EXT_ETOR_NAME`

    - Example: ZE_RTAS_BUILDER_EXT_FLAG_RESERVED

  - **Handle types:** Must end with `ext_handle_t`

  - Example: ze_external_semaphore_ext_handle_t 

  - **Descriptor structures:** Must end with `ext_desc_t`

  - Example: ze_cache_reservation_ext_desc_t

  - **Property structures:** Must end with `ext_properties_t`

  - Example: ze_driver_ddi_handles_ext_properties_t

  - **Flag enumerations:** Must end with `ext_flags_t`

  - Example: ze_device_raytracing_ext_flags_t

The following naming conventions must be followed for **experimental** extensions:

  **Important:** Experimental extensions may be added and removed at any time, are not guaranteed to be forward- or backward-compatible between versions, and may not be supported in production driver releases.

  - **Functions:** Must be postfixed with `Exp`

    - Example: zeCommandListCreateCloneExp

  - **Macros:** All caps with appropriate prefix

    - Core: `ZE_NAME_EXP_*`
    - Sysman: `ZES_NAME_EXP_*`

    - Example: ZE_MODULE_PROGRAM_EXP_NAME

  - **Structures, enumerations, and other types:** Snake case with appropriate prefix

    - Core: `ze_name_exp_*_t`
    - Sysman: `zes_name_exp_*_t`

    - Example(s): ze_command_list_clone_exp_version_t or ze_image_memory_properties_exp_t

  - **Enumerator values:** All caps with appropriate prefix

    - Core: `ZE_ENUM_EXP_ETOR_NAME`
    - Sysman: `ZES_ENUM_EXP_ETOR_NAME`

    - Example: ZE_COMMAND_LIST_CLONE_EXP_VERSION_CURRENT

  - **Handle types:** Must end with `exp_handle_t`

  - Example: ze_rtas_builder_exp_handle_t

  - **Descriptor structures:** Must end with `exp_desc_t`

  - Example: ze_mutable_command_id_exp_desc_t

  - **Property structures:** Must end with `exp_properties_t`

  - Example: ze_fabric_vertex_exp_properties_t

  - **Flag enumerations:** Must end with `exp_flags_t`

  - Example: ze_rtas_device_exp_flags_t


Extending Enumerations
----------------------

Any existing enumeration may be extended by adding new etors (enumerator values).
Etors must still use extension naming convention and values should be assigned to avoid future compatibility issues.

Extending Structures
--------------------

Structures derived from base descriptor or base property types may be extended using structure chains.
This is the required method for extending existing structures.

Structure chains can contain multiple extension structures in any order. Extensions must not depend on 
their order relative to other extensions, and implementations must be order agnostic. Implementations 
will ignore extended structures that are not supported.

Each extension must document which specific structures and functions can be extended using the structure chain.

List of Standard Core Extensions
================================
    - :ref:`"ZE_extension_device_cache_line_size" <ZE_extension_device_cache_line_size>`
    - :ref:`"ZE_extension_eu_count" <ZE_extension_eu_count>`
    - :ref:`"ZE_extension_pci_properties" <ZE_extension_pci_properties>`
    - :ref:`"ZE_extension_rtas" <ZE_extension_rtas>`
    - :ref:`"ZE_extension_srgb" <ZE_extension_srgb>`
    - :ref:`"ZE_extension_bfloat16_conversions" <ZE_extension_bfloat16_conversions>`
    - :ref:`"ZE_extension_cache_reservation" <ZE_extension_cache_reservation>`
    - :ref:`"ZE_extension_device_luid" <ZE_extension_device_luid>`
    - :ref:`"ZE_extension_device_vector_sizes" <ZE_extension_device_vector_sizes>`
    - :ref:`"ZE_extension_device_ip_version" <ZE_extension_device_ip_version>`
    - :ref:`"ZE_extension_device_usablemem_size_properties" <ZE_extension_device_usablemem_size_properties>`
    - :ref:`"ZE_extension_driver_ddi_handles" <ZE_extension_driver_ddi_handles>`
    - :ref:`"ZE_extension_event_query_kernel_timestamps" <ZE_extension_event_query_kernel_timestamps>`
    - :ref:`"ZE_extension_external_memmap_sysmem" <ZE_extension_external_memmap_sysmem>`
    - :ref:`"ZE_extension_float_atomics" <ZE_extension_float_atomics>`
    - :ref:`"ZE_extension_image_copy" <ZE_extension_image_copy>`
    - :ref:`"ZE_extension_image_format_support" <ZE_extension_image_format_support>`
    - :ref:`"ZE_extension_image_query_alloc_properties" <ZE_extension_image_query_alloc_properties>`
    - :ref:`"ZE_extension_image_view" <ZE_extension_image_view>`
    - :ref:`"ZE_extension_image_view_planar" <ZE_extension_image_view_planar>`
    - :ref:`"ZE_extension_ipc_mem_handle_type" <ZE_extension_ipc_mem_handle_type>`
    - :ref:`"ZE_extension_kernel_max_group_size_properties" <ZE_extension_kernel_max_group_size_properties>`
    - :ref:`"ZE_extension_linkage_inspection" <ZE_extension_linkage_inspection>`
    - :ref:`"ZE_extension_linkonce_odr" <ZE_extension_linkonce_odr>`
    - :ref:`"ZE_extension_memory_compression_hints" <ZE_extension_memory_compression_hints>`
    - :ref:`"ZE_extension_memory_free_policies" <ZE_extension_memory_free_policies>`
    - :ref:`"ZE_extension_device_memory_properties" <ZE_extension_device_memory_properties>`
    - :ref:`"ZE_extension_raytracing" <ZE_extension_raytracing>`
    - :ref:`"ZE_extension_subgroups" <ZE_extension_subgroups>`

List of Standard Tools Extensions
=================================

List of Standard Sysman Extensions
==================================
    - :ref:`"ZES_extension_device_ecc_default_properties" <ZES_extension_device_ecc_default_properties>`
    - :ref:`"ZES_extension_engine_activity" <ZES_extension_engine_activity>`
    - :ref:`"ZES_extension_pci_link_speed_downgrade" <ZES_extension_pci_link_speed_downgrade>`
    - :ref:`"ZES_extension_power_limits" <ZES_extension_power_limits>`

List of Standard Runtime Extensions
===================================

List of All Experimental Extensions
===================================

    - :ref:`"ZE_experimental_rtas_builder" <ZE_experimental_rtas_builder>`
    - :ref:`"ZE_experimental_bandwidth_properties" <ZE_experimental_bandwidth_properties>`
    - :ref:`"ZE_experimental_bindless_image" <ZE_experimental_bindless_image>`
    - :ref:`"ZE_experimental_command_list_clone" <ZE_experimental_command_list_clone>`
    - :ref:`"ZE_experimental_event_pool_counter_based" <ZE_experimental_event_pool_counter_based>`
    - :ref:`"ZE_experimental_event_query_timestamps" <ZE_experimental_event_query_timestamps>`
    - :ref:`"ZE_experimental_fabric" <ZE_experimental_fabric>`
    - :ref:`"ZE_experimental_global_offset" <ZE_experimental_global_offset>`
    - :ref:`"ZE_experimental_image_memory_properties" <ZE_experimental_image_memory_properties>`
    - :ref:`"ZE_experimental_image_view" <ZE_experimental_image_view>`
    - :ref:`"ZE_experimental_image_view_planar" <ZE_experimental_image_view_planar>`
    - :ref:`"ZE_experimental_immediate_command_list_append" <ZE_experimental_immediate_command_list_append>`
    - :ref:`"ZE_experimental_kernel_allocation_properties" <ZE_experimental_kernel_allocation_properties>`
    - :ref:`"ZE_extension_kernel_binary_exp" <ZE_extension_kernel_binary_exp>`
    - :ref:`"ZE_experimental_scheduling_hints" <ZE_experimental_scheduling_hints>`
    - :ref:`"ZE_experimental_mutable_command_list" <ZE_experimental_mutable_command_list>`
    - :ref:`"ZE_experimental_power_saving_hint" <ZE_experimental_power_saving_hint>`
    - :ref:`"ZE_experimental_module_program" <ZE_experimental_module_program>`
    - :ref:`"ZE_experimental_relaxed_allocation_limits" <ZE_experimental_relaxed_allocation_limits>`
    - :ref:`"ZE_experimental_sub_allocations" <ZE_experimental_sub_allocations>`
    - :ref:`"ZET_experimental_global_metric_timestamps" <ZET_experimental_global_metric_timestamps>`
    - :ref:`"ZET_experimental_concurrent_metric_groups" <ZET_experimental_concurrent_metric_groups>`
    - :ref:`"ZET_experimental_metric_export_data" <ZET_experimental_metric_export_data>`
    - :ref:`"ZET_experimental_metric_group_marker" <ZET_experimental_metric_group_marker>`
    - :ref:`"ZET_experimental_programmable_metrics" <ZET_experimental_programmable_metrics>`
    - :ref:`"ZET_experimental_metrics_runtime_enable_disable" <ZET_experimental_metrics_runtime_enable_disable>`
    - :ref:`"ZET_experimental_metric_tracer" <ZET_experimental_metric_tracer>`
    - :ref:`"ZET_experimental_calculate_multiple_metrics" <ZET_experimental_calculate_multiple_metrics>`
    - :ref:`"ZET_experimental_api_tracing" <ZET_experimental_api_tracing>`
    - :ref:`"ZES_experimental_firmware_security_version" <ZES_experimental_firmware_security_version>`
    - :ref:`"ZES_extension_mem_state" <ZES_extension_mem_state>`
    - :ref:`"ZES_extension_power_domain_properties" <ZES_extension_power_domain_properties>`
    - :ref:`"ZES_extension_ras_state" <ZES_extension_ras_state>`
    - :ref:`"ZES_experimental_sysman_device_mapping" <ZES_experimental_sysman_device_mapping>`
    - :ref:`"ZES_experimental_virtual_function_management" <ZES_experimental_virtual_function_management>`

Driver Extensions (ie Implementation non-standard)
==================================================
Vendors may provide driver extensions that are similar to experimental extensions but vendor-specific. 
These extensions are either previews of functionality planned for future specifications or features not intended for ratification into the Level Zero specification.

Driver extensions may be added or removed at any time and are not guaranteed to be forward- or backward-compatible between versions. 
They may not be supported in production driver releases and can appear or disappear from release to release.

Requirements
------------
- Extensions must use globally unique names for all macros, enums, structures, and functions

  - Names must not conflict with existing or future standard APIs in the Level Zero specification

- Extensions must have globally unique extension names

  - Reported from :ref:`zeDriverGetExtensionProperties` or :ref:`zesDriverGetExtensionProperties`
  - Retrievable using :ref:`zeDriverGetExtensionFunctionAddress` or :ref:`zesDriverGetExtensionFunctionAddress`

- Extensions with structure types (`stypes`) must use unique values

  - Values must not conflict with existing or future standard APIs
  - Values must be defined within the range reserved for driver extensions based on the driver type:

  - GPU Drivers: **0x00030000 to 0x0005ffff**

  - NPU Drivers: **0x00060000 to 0x0007ffff**

  - **Important** Identifiers outside of these ranges may conflict with future standard APIs and must be avoided.


Naming Convention
-----------------
The following naming conventions must be followed for **driver extensions**:

  - **Entrypoints:** ze<Vendor>*Exp

    - Example: `zeIntelImageGetFormatModifiersSupportedExp`

  - **Macros:** ZE_<VENDOR>_*EXP

    - Example: `ZE_INTEL_KERNEL_GET_PROGRAM_BINARY_EXP_NAME`

  - **Structures:** ze_<vendor>_*_exp_*_t

    - Example: `ze_intel_queue_allocate_msix_hint_exp_desc_t`

  - **Enums:** ZE_<VENDOR>_<ENUM_NAME>*_EXP_*

    - Example: `ZE_INTEL_DEVICE_BLOCK_ARRAY_EXP_PROPERTIES_VERSION_CURRENT`

  - **Descriptors:** ZE_<VENDOR>_STRUCTURE_TYPE_*_EXP_DESC

    - Example: `ZE_INTEL_STRUCTURE_TYPE_DEVICE_COMMAND_LIST_WAIT_ON_MEMORY_DATA_SIZE_EXP_DESC`
