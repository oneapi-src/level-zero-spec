<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    s=tags['$s']
    S=s.upper()
%>
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
from ${x}DriverGetExtensionProperties which has been available since inception of this specification,
the other APIs have been added subsequently. The versions of spec in which the APIs were added is also
noted in following table.

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

- Extensions must use globally unique names for macros, enums, structures and functions
- Extensions must have globally unique extension names reported from ${x}DriverGetExtensionProperties, ${s}DriverGetExtensionProperties
- All extensions must be defined in this specification
- Extensions must not break backwards compatibility of the standard APIs defined in this specification
- Standard extension versions must be backwards compatible with prior versions

Naming Convention
-----------------

The following naming conventions must be followed for **standard** extensions:

## --validate=off
  - All extension functions must be postfixed with `Ext`
  - All macros must use all caps with the appropriate prefix. Core macros shall use `${X}_NAME_EXT`, Sysman macros shall use `${S}_NAME_EXT`
  - All structures, enumerations and other types must follow snake case convention with appropriate prefix. Core structures and enumerations shall use `${x}_name_ext_t` and Sysman shall use `${s}_name_ext_t`
  - All enumerator values must use all caps with appropriate prefix. Core enumerator values shall use `${X}_ENUM_EXT_ETOR_NAME` and Sysman shall use `${S}_ENUM_EXT_ETOR_NAME`
  - All handle types must end with `ext_handle_t`
  - All descriptor structures must end with `ext_desc_t`
  - All property structures must end with `ext_properties_t`
  - All flag enumerations must end with `ext_flags_t`
## --validate=on

The following naming conventions must be followed for **experimental** extensions:

## --validate=off
  - Experimental extensions may be added and removed from the driver at any time.
  - Experimental extensions are not guaranteed to be forward- or backward-compatible between versions.
  - Experimental extensions are not guaranteed to be supported in production driver releases; and may appear and disappear from release to release.
  - All extension functions must be postfixed with `Exp`. The vendor name must follow the `${x}` or `${s}` prefix and follow CamelCase convention.
  - All macros must use all caps with the appropriate prefix. Core macros shall use `${X}_NAME_EXP`, Sysman macros shall use `${S}_NAME_EXP`. The vendor name must follow `${X}` or `${S}` prefix.
  - All structures, enumerations and other types must follow snake case convention with appropriate prefix. Core structures and enumerations shall use `${x}_name_exp_t` and Sysman shall use `${s}_name_exp_t`. The vendor name must follow `${x}` or `${S}` prefix.
  - All enumerator values must use all caps with appropriate prefix. Core enumerator values shall use `${X}_ENUM_EXP_ETOR_NAME` and Sysman shall use `${S}_ENUM_EXP_ETOR_NAME`. The vendor name must follow `${X}` or `${S}` prefix.
  - All handle types must end with `exp_handle_t`
  - All descriptor structures must end with `exp_desc_t`
  - All property structures must end with `exp_properties_t`
  - All flag enumerations must end with `exp_flags_t`
## --validate=on

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

%for name in meta['macro']:
%if name.endswith("EXT_NAME"):
%if not name.endswith("POWER_LIMITS_EXT_NAME"):
    - :ref:`${th.subt(namespace, tags, meta['macro'][name]['values'][0])} <${th.subt(namespace, tags, meta['macro'][name]['values'][0]).replace('"', '')}>`\

%endif
%endif
%endfor


List of Experimental Extensions
===============================

%for name in meta['macro']:
%if name.endswith("EXP_NAME"):
    - :ref:`${th.subt(namespace, tags, meta['macro'][name]['values'][0])} <${th.subt(namespace, tags, meta['macro'][name]['values'][0]).replace('"', '')}>`\

%endif
%endfor

List of Standard Sysman Extensions
==================================

%for name in meta['macro']:
%if name.endswith("EXT_NAME"):
%if name.endswith("POWER_LIMITS_EXT_NAME"):
    - :ref:`${th.subt(namespace, tags, meta['macro'][name]['values'][0])} <${th.subt(namespace, tags, meta['macro'][name]['values'][0]).replace('"', '')}>`\

%endif
%endif
%endfor