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
This feature adds the ability to retrieve telemetry from PF domain for monitoring per VF memory and engine utilization. 
This telemetry is used to determine if a VM has oversubscribed GPU memory or observe engine business for a targeted workload.
If VF has no activity value to report, then implementation shall reflect that appropriately in ${s}_vf_util_engine_exp_t struct so that percentage
calculation results in value of 0.

The following pseudo-code demonstrates a sequence for obtaining the engine activity for all Virtual Functions from Physical Function environment:

.. parsed-literal::

// Gather count of VF handles
uint32_t numVf = 0;
${s}_vf_exp_properties_t vfProps {};
${s}DeviceEnumActiveVFExp(hDevice, &numVf, nullptr);

//Allocate memory for vf handles and call back in to gather handles
std::vector<zes_vf_handle_t> vfs(numVf, nullptr);
${s}DeviceEnumActiveVFExp(hDevice, &numVf, vfs.data());

// Gather VF properties
std::vector <zes_vf_properties_t> vfProps(numVf);
for (uint32_t i = 0; i < numVf; i++) {
    ${s}VFManagementGetVFPropertiesExp(vfs[i], &vfProps[i]);
}

//Detect the info types a particular VF supports

//Using VF# 0 to demonstrate how to detect engine info type and query engine util info
${s}_zes_vf_handle_t activeVf = vfs[0];
if (vfProps[0].flags & ZES_VF_INFO_ENGINE) {
    ${s}_vf_util_engine_exp_t engineUtil0 = {};
    {s}VFManagementGetVFEngineUtilizationExp(activeVf, &engineUtil0);
    sleep(1)
    ${s}_vf_util_engine_exp_t engineUtil1 = {};
    ${s}VFManagementGetVFEngineUtilizationExp(activeVf, &engineUtil1);
    // Use formula to calculate engine utilization % based on the 2 snapshots above
}

// Demonstrate using setter to switch off Engine telemetry for VF0 and then check if Getter returns INVALID
${s}VFManagementSetVFTelemetryModeExp(activeVf,  ZES_VF_INFO_ENGINE, false); 
zes_result_t res = ${s}VFManagementGetVFEngineUtilizationExp(activeVf, &engineUtil0);
if (res != ZES_RESULT_SUCCESS) {
    printf("Engine utilization successfully disabled for VF");
}
