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

    * ${s}DeviceEnumEnabledVFExp
    * ${s}DeviceEnumActiveVFExp
    * ${s}VFManagementGetVFCapabilitiesExp
    * ${s}VFManagementGetVFCapabilitiesExp2
    * ${s}VFManagementGetVFMemoryUtilizationExp2
    * ${s}VFManagementGetVFEngineUtilizationExp2    
    * ${s}VFManagementGetVFPropertiesExp
    * ${s}VFManagementGetVFMemoryUtilizationExp
    * ${s}VFManagementGetVFEngineUtilizationExp
    * ${s}VFManagementSetVFTelemetryModeExp
    * ${s}VFManagementSetVFTelemetrySamplingIntervalExp

* Enumerations

    * ${s}_vf_management_exp_version_t
    * ${s}_vf_info_mem_type_exp_flags_t
    * ${s}_vf_info_util_exp_flags_t
   
* Structures

    * ${s}_vf_exp_capabilities_t
    * ${s}_vf_util_mem_exp2_t
    * ${s}_vf_util_engine_exp2_t
    * ${s}_vf_exp_properties_t
    * ${s}_vf_util_mem_exp_t
    * ${s}_vf_util_engine_exp_t
    * ${s}_vf_exp2_capabilities_t
   
Virtual Function Management
~~~~~~~~~~~~~~~~~~~~~~~~~~~
This feature adds the ability to retrieve telemetry from PF domain for monitoring per VF memory and engine utilization. 
This telemetry is used to determine if a VM has oversubscribed GPU memory or observe engine business for a targeted workload.
If VF has no activity value to report, then implementation shall reflect that appropriately in ${s}_vf_util_engine_exp2_t struct so that percentage
calculation results in value of 0.

The following pseudo-code demonstrates a sequence for obtaining the engine activity for all Virtual Functions from Physical Function environment:

.. parsed-literal::

    // Gather count of VF handles
    uint32_t numVf = 0;
    ${s}DeviceEnumEnabledVFExp(hDevice, &numVf, nullptr);

    // Allocate memory for vf handles and call back in to gather handles
    std::vector<${s}_vf_handle_t> vfs(numVf, nullptr);
    ${s}DeviceEnumEnabledVFExp(hDevice, &numVf, vfs.data());

    // Gather VF capabilities
    std::vector <${s}_vf_exp2_capabilities_t> vfCapabs(numVf);
    for (uint32_t i = 0; i < numVf; i++) {
        ${s}VFManagementGetVFCapabilitiesExp2(vfs[i], &vfCapabs[i]);
    }

    // Detect the info types a particular VF supports

    // Using VF# 0 to demonstrate how to detect engine info type and query engine util info
    ${s}_vf_handle_t activeVf = vfs[0];
    uint32_t engineStatCount = 0;
    
    ${s}VFManagementGetVFEngineUtilizationExp2(activeVf, &engineStatCount, nullptr);
    // Allocate memory for vf engine stats
    ${s}_vf_util_engine_exp2_t* engineStats0 = (${s}_vf_util_engine_exp2_t*) allocate(engineStatCount * sizeof(${s}_vf_util_engine_exp2_t));
    ${s}VFManagementGetVFEngineUtilizationExp2(activeVf, &engineStatCount, engineStats0);
    sleep(1)
    ${s}_vf_util_engine_exp2_t* engineStats1 = (${s}_vf_util_engine_exp2_t*) allocate(engineStatCount * sizeof(${s}_vf_util_engine_exp2_t));
    ${s}VFManagementGetVFEngineUtilizationExp2(activeVf, &engineStatCount, &engineStats1);
