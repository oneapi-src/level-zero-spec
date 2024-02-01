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
:orphan:

.. _ZES_experimental_virtual_function_management:

========================================
 Virtual Function Management Extension
========================================

API
----

* Functions

    * ${s}DeviceEnumActiveVFExp
    * ${s}VFManagementGetVFPropertiesExp
    * ${s}VFManagementGetVFMemoryUtilizationExp
    * ${s}VFManagementGetVFEngineUtilizationExp
    * ${s}VFManagementSetVFTelemetryModeExp
    * ${s}VFManagementSetVFTelemetrySamplingIntervalExp

* Enumerations

    * ${s}_vf_management_exp_version_t
    * ${s}_vf_info_mem_type_exp_t
    * ${s}_vf_info_util_exp_flags_t
   
* Structures

    * ${s}_vf_exp_properties_t
    * ${s}_vf_util_mem_exp_t
    * ${s}_vf_util_engine_exp_t
   
Virtual Function Management
~~~~~~~~~~~~~~~~~~~~~~~~~~~
