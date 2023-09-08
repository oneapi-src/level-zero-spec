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

.. _ZES_extension_memory_state:

==========================
 Memory State Extension
==========================

API
----

* Functions

    * ${s}MemGetStateExp

* Enumerations

    * ${s}_mem_state_exp_version_t

* Structures

    * ${s}_engine_exp_properties_t

Memory State
~~~~~~~~~~~~

This extension provides capability to user to gather the activity stats for each Virtual Function (VF) associated with memory module.
Intended use case of the feature is to query utilization stats from Physical Function (PF) interface. However, the extension
may return error code ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE if an environment does not support it.
If VF has no memory utilization to report, then implementation shall reflect that appropriately in ${s}_mem_state_t struct so that percentage
allocation calculation results in value of 0. In this case, percentage free could be 100%.
If PF has no memory utilization to report, then implementation shall reflect that appropriately in ${s}_mem_state_t struct which is
at index 0 of the output vector such that allocation calculation results in value of 0. In this case, percentage free could be 100%.

The following pseudo-code demonstrates a sequence for obtaining the memory allocation percentage for all Virtual Functions from Physical Function environment:

.. parsed-literal::

    // Query for memory properties and gather number of VF instances by passing extension structure.
    // Number of VFs is per memory handle and equates to number of VFs actively using
    // the resource represented by the memory handle.
    // Together with pCount from GetStateExp, user can gather the full view of memory state
    // for all VFs and PF as shown below

    ${s}_mem_properties_t memProps;
    ${s}_mem_exp_properties_t memExpProps;
    memProps.stype = ZES_STRUCTURE_TYPE_MEMORY_PROPERTIES;
    memProps.pNext = &memExpProps;
    memExpProps.stype = ZES_STRUCTURE_TYPE_MEMORY_EXP_PROPERTIES;

    ${s}MemGetProperties(hMemory, &memProps);

    // Query count of memory states to gather
    // this count is inclusive of PF and N number of VFs
    // i.e. if memStateCount = 4, then this implies, one PF state at index 0
    //      of output vector followed by memory states for 3 VFs
    uint32_t memStateCount = 0;
    {s}MemGetStateExp(hMemory, &memStateCount, nullptr);

    // Gather memory states for all VFs and PF.
    // memory  allocation per formula in ${s}_mem_state_t
    ${s}_mem_state_t* memStates = (${s}_mem_state_t*) allocate(memStateCount * sizeof(${s}_mem_state_t));
    {s}MemGetStateExp(hMemory, &memStateCount, memStates);

    for (uint32_t idx = 0; idx < memStateCount; ++idx) {
        double allocation = 100 * (memStates[idx].size - memStates[idx].free)/(memStates[idx].size;
        output("%s Allocation of memory module type pertaining to this handle = %.2f\n", (idx == 0) ? "PF" : "VF", allocation);
    }
