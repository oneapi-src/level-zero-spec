
============
 Extensions
============

Objective
=========

Features which are device- or vendor-specific can be exposed as extensions.

There are two types of extensions defined by this specification:

1. **Standard** - extensions ratified for inclusion into the current and all future versions of the specification.
2. **Experimental** - extensions require additional experimentation and feedback from application vendors
   before ratification, therefore applications should not rely on experimental extensions in production.

In addition to above, an implementation may choose to provide non-standard extensions which are
not defined in this specification.

It is the responsibility of the implementation to define and document such non-standard extensions
and also to ensure these extensions do not conflict or interfere with any features or extensions of the standard 
core or sysman APIs.

The following table summarizes the APIs to be used for discovery of different types of extensions. Aside
from :ref:`zeDriverGetExtensionProperties` which has been available since inception of this specification,
the other APIs have been added subsequently. The versions of spec in which the APIs were added is also
noted in following table.

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

- Extensions must use globally unique names for macros, enums, structures and functions
- Extensions must have globally unique extension names reported from :ref:`zeDriverGetExtensionProperties`\, :ref:`zesDriverGetExtensionProperties`
- All extensions must be defined in this specification
- Extensions must not break backwards compatibility of the standard APIs defined in this specification
- Standard extension versions must be backwards compatible with prior versions

Naming Convention
-----------------

The following naming conventions must be followed for **standard** extensions:

  - All extension functions must be postfixed with `Ext`
  - All macros must use all caps with the appropriate prefix. Core macros shall use `ZE_NAME_EXT`, Sysman macros shall use `ZES_NAME_EXT`
  - All structures, enumerations and other types must follow snake case convention with appropriate prefix. Core structures and enumerations shall use `ze_name_ext_t` and Sysman shall use `zes_name_ext_t`
  - All enumerator values must use all caps with appropriate prefix. Core enumerator values shall use `ZE_ENUM_EXT_ETOR_NAME` and Sysman shall use `ZES_ENUM_EXT_ETOR_NAME`
  - All handle types must end with `ext_handle_t`
  - All descriptor structures must end with `ext_desc_t`
  - All property structures must end with `ext_properties_t`
  - All flag enumerations must end with `ext_flags_t`

The following naming conventions must be followed for **experimental** extensions:

  - Experimental extensions may be added and removed from the driver at any time.
  - Experimental extensions are not guaranteed to be forward- or backward-compatible between versions.
  - Experimental extensions are not guaranteed to be supported in production driver releases; and may appear and disappear from release to release.
  - All extension functions must be postfixed with `Exp`. The vendor name must follow the `ze` or `zes` prefix and follow CamelCase convention.
  - All macros must use all caps with the appropriate prefix. Core macros shall use `ZE_NAME_EXP`, Sysman macros shall use `ZES_NAME_EXP`. The vendor name must follow `ZE` or `ZES` prefix.
  - All structures, enumerations and other types must follow snake case convention with appropriate prefix. Core structures and enumerations shall use `ze_name_exp_t` and Sysman shall use `zes_name_exp_t`. The vendor name must follow `ze` or `ZES` prefix.
  - All enumerator values must use all caps with appropriate prefix. Core enumerator values shall use `ZE_ENUM_EXP_ETOR_NAME` and Sysman shall use `ZES_ENUM_EXP_ETOR_NAME`. The vendor name must follow `ZE` or `ZES` prefix.
  - All handle types must end with `exp_handle_t`
  - All descriptor structures must end with `exp_desc_t`
  - All property structures must end with `exp_properties_t`
  - All flag enumerations must end with `exp_flags_t`

Extending Enumerations
----------------------

Any existing enumeration may be extended by adding new etors.
Etors must still use extension naming convention and values should be assigned to avoid future compatibility issues.

Extending Structures
--------------------

Any structure derived from base descriptor or base property structure types may be extended using structure chains.
While it is possible to use other methods, this is the required method for extending existing structures.

A structure chain can contain more than one extension structure, in any order. Therefore, extensions should not be
dependent on their order relative to other extensions and the implementation must be order agnostic. In addition,
the implementation will ignore extended structures that it does not support.

The extension must document the specific structures and functions that may be extended using the structure chain.

List of Standard Core Extensions
================================

    - :ref:`"ZE_extension_eu_count" <ZE_extension_eu_count>`
    - :ref:`"ZE_extension_pci_properties" <ZE_extension_pci_properties>`
    - :ref:`"ZE_extension_srgb" <ZE_extension_srgb>`
    - :ref:`"ZE_extension_bfloat16_conversions" <ZE_extension_bfloat16_conversions>`
    - :ref:`"ZE_extension_cache_reservation" <ZE_extension_cache_reservation>`
    - :ref:`"ZE_extension_device_luid" <ZE_extension_device_luid>`
    - :ref:`"ZE_extension_device_ip_version" <ZE_extension_device_ip_version>`
    - :ref:`"ZE_extension_event_query_kernel_timestamps" <ZE_extension_event_query_kernel_timestamps>`
    - :ref:`"ZE_extension_float_atomics" <ZE_extension_float_atomics>`
    - :ref:`"ZE_extension_image_copy" <ZE_extension_image_copy>`
    - :ref:`"ZE_extension_image_query_alloc_properties" <ZE_extension_image_query_alloc_properties>`
    - :ref:`"ZE_extension_image_view" <ZE_extension_image_view>`
    - :ref:`"ZE_extension_image_view_planar" <ZE_extension_image_view_planar>`
    - :ref:`"ZE_extension_kernel_max_group_size_properties" <ZE_extension_kernel_max_group_size_properties>`
    - :ref:`"ZE_extension_linkage_inspection" <ZE_extension_linkage_inspection>`
    - :ref:`"ZE_extension_linkonce_odr" <ZE_extension_linkonce_odr>`
    - :ref:`"ZE_extension_memory_compression_hints" <ZE_extension_memory_compression_hints>`
    - :ref:`"ZE_extension_memory_free_policies" <ZE_extension_memory_free_policies>`
    - :ref:`"ZE_extension_device_memory_properties" <ZE_extension_device_memory_properties>`
    - :ref:`"ZE_extension_raytracing" <ZE_extension_raytracing>`
    - :ref:`"ZE_extension_subgroups" <ZE_extension_subgroups>`
    - :ref:`"ZES_extension_engine_activity" <ZES_extension_engine_activity>`


List of Experimental Extensions
===============================

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
    - :ref:`"ZE_experimental_scheduling_hints" <ZE_experimental_scheduling_hints>`
    - :ref:`"ZE_experimental_mutable_command_list" <ZE_experimental_mutable_command_list>`
    - :ref:`"ZE_experimental_power_saving_hint" <ZE_experimental_power_saving_hint>`
    - :ref:`"ZE_experimental_module_program" <ZE_experimental_module_program>`
    - :ref:`"ZE_experimental_relaxed_allocation_limits" <ZE_experimental_relaxed_allocation_limits>`
    - :ref:`"ZE_experimental_sub_allocations" <ZE_experimental_sub_allocations>`
    - :ref:`"ZET_experimental_global_metric_timestamps" <ZET_experimental_global_metric_timestamps>`
    - :ref:`"ZET_experimental_metric_export_data" <ZET_experimental_metric_export_data>`
    - :ref:`"ZET_experimental_programmable_metrics" <ZET_experimental_programmable_metrics>`
    - :ref:`"ZET_experimental_calculate_multiple_metrics" <ZET_experimental_calculate_multiple_metrics>`
    - :ref:`"ZET_experimental_api_tracing" <ZET_experimental_api_tracing>`
    - :ref:`"ZES_experimental_firmware_security_version" <ZES_experimental_firmware_security_version>`
    - :ref:`"ZES_extension_mem_state" <ZES_extension_mem_state>`
    - :ref:`"ZES_extension_power_domain_properties" <ZES_extension_power_domain_properties>`
    - :ref:`"ZES_extension_ras_state" <ZES_extension_ras_state>`
    - :ref:`"ZES_experimental_sysman_device_mapping" <ZES_experimental_sysman_device_mapping>`
    - :ref:`"ZES_experimental_virtual_function_management" <ZES_experimental_virtual_function_management>`

List of Standard Sysman Extensions
==================================

    - :ref:`"ZES_extension_power_limits" <ZES_extension_power_limits>`
