<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_sub_allocations:

=====================================
 Sub-Allocation Properties Extension
=====================================

API
----

* Enumerations


    * ${x}_sub_allocations_exp_version_t


* Structures


    * ${x}_memory_sub_allocations_exp_properties_t

Sub-Allocation Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~

Driver implementations may choose to create a device allocation as a series of sub-allocations. For instance,
an allocation created against a parent device may be allocated internally as set of N sub-allocations, with
N being the number of sub-devices associated with the parent device.

The sub-allocation properties extension may be used to get the properties, i.e. base address and size, for
each of those sub-allocations. The following pseudo-code demonstrates a basic use-case of this extension:

.. parsed-literal::

    ${x}MemAllocDevice(context, &desc, size, alignment, device, &ptr);

    ${x}_memory_sub_allocations_exp_properties_t subAllocationDesc {};
    uitn32_t numberOfSuballocations = 0;
    subAllocationDesc.stype = ${X}_STRUCTURE_TYPE_MEMORY_SUB_ALLOCATIONS_EXP_PROPERTIES;
    subAllocationDesc.pCount = &numberOfSuballocations;

    ${x}_memory_allocation_properties_t memAllocProperties {};
    memAllocProperties.stype = ${X}_STRUCTURE_TYPE_MEMORY_ALLOCATION_PROPERTIES;
    memAllocProperties.pNext = &subAllocationDesc;

    // Get number of sub-allocations
    ${x}MemGetAllocProperties(context, ptr, &memAllocProperties, nullptr);

    // if more than 1 sub-allocation, then allocation has been split
    if (numberOfSuballocations > 1) {
        std::vector<${x}_sub_allocation_t> subAllocationMemAllocProperties(numberOfSuballocations);
        subAllocationDesc.pSubAllocations = subAllocationMemAllocProperties.data();

        ${x}MemGetAllocProperties(context, ptr, &memAllocProperties, nullptr);

        // retrieve the properties of each sub-allocation
        for (auto &subAllocationProperty : subAllocationMemAllocProperties) {
            void * base = subAllocationProperty.base;
            size_t size = subAllocationProperty.size;
        }
    }
    ...