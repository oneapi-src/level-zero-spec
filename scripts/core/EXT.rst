<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    s=tags['$s']
    S=s.upper()
    t=tags['$t']
    T=t.upper()
    r=tags['$r']
    R=r.upper()
%>
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
${x}DriverGetExtensionProperties has been available since inception of this specification, while other APIs were added in later versions as noted below.

=============== =================== ============================= ========================================
 API Category   Version API added   Extension Type                Extension Discovery API
=============== =================== ============================= ========================================
 Core           NA                  Standard                      ${x}DriverGetExtensionProperties
 Core           NA                  Experimental                  ${x}DriverGetExtensionProperties
 Core           1.1                 Implementation non-standard   ${x}DriverGetExtensionFunctionAddress
 Sysman         1.8                 Standard                      ${s}DriverGetExtensionProperties
 Sysman         1.8                 Experimental                  ${s}DriverGetExtensionProperties
 Sysman         1.8                 Implementation non-standard   ${s}DriverGetExtensionFunctionAddress
=============== =================== ============================= ========================================

Requirements
============

- Extensions must use globally unique names for macros, enums, structures, and functions
- Extensions must have globally unique extension names reported from ${x}DriverGetExtensionProperties and ${s}DriverGetExtensionProperties
- All standard and experimental extensions must be defined in this specification
- Extensions must not break backwards compatibility of standard APIs
- Standard extension versions must be backwards compatible with prior versions

Naming Convention
-----------------

The following naming conventions must be followed for **standard** extensions:

## --validate=off
  - **Functions:** Must be postfixed with `Ext`

  - Example: ${x}DeviceImportExternalSemaphoreExt

  - **Macros:** All caps with appropriate prefix

    - Core: `${X}_NAME_EXT_*`
    - Sysman: `${S}_NAME_EXT_*`

    - Example: ${X}_MAX_FABRIC_EDGE_MODEL_EXT_SIZE

  - **Structures, enumerations, and other types:** Snake case with appropriate prefix

    - Core: `${x}_name_ext_*_t`
    - Sysman: `${s}_name_ext_*_t`

    - Example(s): ${x}_device_ip_version_ext_t or ${x}_cache_reservation_ext_desc_t

  - **Enumerator values:** All caps with appropriate prefix

    - Core: `${X}_ENUM_EXT_ETOR_NAME`
    - Sysman: `${S}_ENUM_EXT_ETOR_NAME`

    - Example: ${X}_RTAS_BUILDER_EXT_FLAG_RESERVED

  - **Handle types:** Must end with `ext_handle_t`

  - Example: ${x}_external_semaphore_ext_handle_t 

  - **Descriptor structures:** Must end with `ext_desc_t`

  - Example: ${x}_cache_reservation_ext_desc_t

  - **Property structures:** Must end with `ext_properties_t`

  - Example: ${x}_driver_ddi_handles_ext_properties_t

  - **Flag enumerations:** Must end with `ext_flags_t`

  - Example: ${x}_device_raytracing_ext_flags_t
## --validate=on

The following naming conventions must be followed for **experimental** extensions:

## --validate=off
  **Important:** Experimental extensions may be added and removed at any time, are not guaranteed to be forward- or backward-compatible between versions, and may not be supported in production driver releases.

  - **Functions:** Must be postfixed with `Exp`

    - Example: ${x}CommandListCreateCloneExp

  - **Macros:** All caps with appropriate prefix

    - Core: `${X}_NAME_EXP_*`
    - Sysman: `${S}_NAME_EXP_*`

    - Example: ${X}_MODULE_PROGRAM_EXP_NAME

  - **Structures, enumerations, and other types:** Snake case with appropriate prefix

    - Core: `${x}_name_exp_*_t`
    - Sysman: `${s}_name_exp_*_t`

    - Example(s): ${x}_command_list_clone_exp_version_t or ${x}_image_memory_properties_exp_t

  - **Enumerator values:** All caps with appropriate prefix

    - Core: `${X}_ENUM_EXP_ETOR_NAME`
    - Sysman: `${S}_ENUM_EXP_ETOR_NAME`

    - Example: ${X}_COMMAND_LIST_CLONE_EXP_VERSION_CURRENT

  - **Handle types:** Must end with `exp_handle_t`

  - Example: ${x}_rtas_builder_exp_handle_t

  - **Descriptor structures:** Must end with `exp_desc_t`

  - Example: ${x}_mutable_command_id_exp_desc_t

  - **Property structures:** Must end with `exp_properties_t`

  - Example: ${x}_fabric_vertex_exp_properties_t

  - **Flag enumerations:** Must end with `exp_flags_t`

  - Example: ${x}_rtas_device_exp_flags_t

## --validate=on

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
## --validate=off
%for name in meta['macro']:
%if name.endswith("EXT_NAME") and name.startswith('$X' + '_'):
    - :ref:`${th.subt(namespace, tags, meta['macro'][name]['values'][0])} <${th.subt(namespace, tags, meta['macro'][name]['values'][0]).replace('"', '')}>`\

%endif
%endfor
## --validate=on

List of Standard Tools Extensions
=================================
## --validate=off
%for name in meta['macro']:
%if name.endswith("EXT_NAME") and name.startswith('$T' + '_'):
    - :ref:`${th.subt(namespace, tags, meta['macro'][name]['values'][0])} <${th.subt(namespace, tags, meta['macro'][name]['values'][0]).replace('"', '')}>`\

%endif
%endfor
## --validate=on

List of Standard Sysman Extensions
==================================
## --validate=off
%for name in meta['macro']:
%if name.endswith("EXT_NAME") and name.startswith('$S' + '_'):
    - :ref:`${th.subt(namespace, tags, meta['macro'][name]['values'][0])} <${th.subt(namespace, tags, meta['macro'][name]['values'][0]).replace('"', '')}>`\

%endif
%endfor
## --validate=on

List of Standard Runtime Extensions
===================================
## --validate=off
%for name in meta['macro']:
%if name.endswith("EXT_NAME") and name.startswith('$R' + '_'):
    - :ref:`${th.subt(namespace, tags, meta['macro'][name]['values'][0])} <${th.subt(namespace, tags, meta['macro'][name]['values'][0]).replace('"', '')}>`\

%endif
%endfor
## --validate=on

List of All Experimental Extensions
===================================

%for name in meta['macro']:
%if name.endswith("EXP_NAME"):
    - :ref:`${th.subt(namespace, tags, meta['macro'][name]['values'][0])} <${th.subt(namespace, tags, meta['macro'][name]['values'][0]).replace('"', '')}>`\

%endif
%endfor

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

  - Reported from ${x}DriverGetExtensionProperties or ${s}DriverGetExtensionProperties
  - Retrievable using ${x}DriverGetExtensionFunctionAddress or ${s}DriverGetExtensionFunctionAddress

- Extensions with structure types (`stypes`) must use unique values

  - Values must not conflict with existing or future standard APIs
  - Values must be defined within the range reserved for driver extensions based on the driver type:

  - GPU Drivers: **0x00030000 to 0x0005ffff**

  - NPU Drivers: **0x00060000 to 0x0007ffff**

  - **Important** Identifiers outside of these ranges may conflict with future standard APIs and must be avoided.


Naming Convention
-----------------
The following naming conventions must be followed for **driver extensions**:

## --validate=off
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
## --validate=on