<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
============
 Extensions
============

Objective
=========

Features which are device- or vendor-specific can be exposed as extensions.
The list of extensions supported by the driver implementation can be queried using ${x}DriverGetExtensionProperties.

There are two types of extensions:

1. **Standard** - extensions ratified for inclusion into the current and all future versions of the specification.
2. **Experimental** - extensions require additional experimentation and feedback from application vendors
   before ratification, therefore applications should not rely on experimental extensions in production.


Requirements
============

- Extensions must use globally unique names for macros, enums, structures and functions
- Extensions must have globally unique extension names reported from ${x}DriverGetExtensionProperties
- All extensions must be defined in this specification
- Extensions must not break backwards compatibility of the core APIs
- Standard extension versions must be backwards compatible with prior versions

Naming Convention
-----------------

The following naming conventions must be followed for **standard** extensions:

## --validate=off
  - All extension functions must be postfixed with `Ext`
  - All macros must use all caps `${X}_NAME_EXT` convention
  - All structures, enumerations and other types must follow `${x}_name_ext_t` snake case convention
  - All enumerator values must use all caps `${X}_ENUM_EXT_ETOR_NAME` convention
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
  - All extension functions must be postfixed with `Exp`
  - All macros must use all caps `${X}_NAME_EXP` convention
  - All structures, enumerations and other types must follow `${x}_name_exp_t` snake case convention
  - All enumerator values must use all caps `${X}_ENUM_EXP_ETOR_NAME` convention
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

Any structure derived from `${x}_base_desc_t` or `${x}_base_properties_t` can be extended using structure chains.
While it is possible to use other methods, this is the required method for extending existing structures.

A structure chain can contain more than one extension structure, in any order.
Therefore, extensions should not be dependent on their order relative to other extensions and the implementation must be order agnostic.

The extension must document the specific structures and functions that may be extended using the structure chain.

List of Standard Extensions
===========================

%for name in meta['macro']:
%if name.endswith("EXT_NAME"):
- ${th.subt(namespace, tags, meta['macro'][name]['values'][0])}
%endif
%endfor


List of Experimental Extensions
===============================

%for name in meta['macro']:
%if name.endswith("EXP_NAME"):
- ${th.subt(namespace, tags, meta['macro'][name]['values'][0])}
%endif
%endfor
