<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _compiler-info-query:

=======================================================
 Compiler-Info Query
=======================================================

API
----

* Enumerations
    * ${x}_device_compiler_info_t

* Structures
    * ${x}_compiler_name_version_t

* Functions
    * ${x}DeviceGetCompilerInfo

Summary:
~~~~~~~~~~~~~~~~~~~~~~

This provides a single, compiler-scoped device query, ${x}DeviceGetCompilerInfo. The value selected
by ${x}_device_compiler_info_t determines which compiler-info list is returned; see the enumeration
for the available selectors and their payload layout. The result uses the standard two-call
convention with a single in/out size parameter: query the size with ``pData`` null, allocate, then
call again to fill.

Example usage:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. parsed-literal::
    size_t size = 0;
    ${x}DeviceGetCompilerInfo(hDevice, ${X}_DEVICE_COMPILER_INFO_SPIRV_CAPABILITIES, nullptr, &size, nullptr);
    std::vector<uint32_t> caps(size / sizeof(uint32_t));
    ${x}DeviceGetCompilerInfo(hDevice, ${X}_DEVICE_COMPILER_INFO_SPIRV_CAPABILITIES, nullptr, &size, caps.data());
