
:orphan:

.. _ZE_experimental_sub_allocations:

=====================================
 Sub-Allocation Properties Extension
=====================================

API
----

* Enumerations


    * :ref:`ze-sub-allocations-exp-version-t`


* Structures


    * :ref:`ze-memory-sub-allocations-exp-properties-t`

Sub-Allocation Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~

Driver implementations may choose to create a device allocation as a series of sub-allocations. For instance,
an allocation created against a parent device may be allocated internally as set of N sub-allocations, with
N being the number of sub-devices associated with the parent device.

The sub-allocation properties extension may be used to get the properties, i.e. base address and size, for
each of those sub-allocations. The following pseudo-code demonstrates a basic use-case of this extension:

.. parsed-literal::

    :ref:`zeMemAllocDevice`\(context, &desc, size, alignment, device, &ptr);

    :ref:`ze-memory-sub-allocations-exp-properties-t` subAllocationDesc {};
    uitn32_t numberOfSuballocations = 0;
    subAllocationDesc.stype = :ref:`ZE_STRUCTURE_TYPE_MEMORY_SUB_ALLOCATIONS_EXP_PROPERTIES <ze-structure-type-t>`\;
    subAllocationDesc.pCount = &numberOfSuballocations;

    :ref:`ze-memory-allocation-properties-t` memAllocProperties {};
    memAllocProperties.stype = :ref:`ZE_STRUCTURE_TYPE_MEMORY_ALLOCATION_PROPERTIES <ze-structure-type-t>`\;
    memAllocProperties.pNext = &subAllocationDesc;

    // Get number of sub-allocations
    :ref:`zeMemGetAllocProperties`\(context, ptr, &memAllocProperties, nullptr);

    // if more than 1 sub-allocation, then allocation has been split
    if (numberOfSuballocations > 1) {
        std::vector<:ref:`ze-sub-allocation-t`\> subAllocationMemAllocProperties(numberOfSuballocations);
        subAllocationDesc.pSubAllocations = subAllocationMemAllocProperties.data();

        :ref:`zeMemGetAllocProperties`\(context, ptr, &memAllocProperties, nullptr);

        // retrieve the properties of each sub-allocation
        for (auto &subAllocationProperty : subAllocationMemAllocProperties) {
            void * base = subAllocationProperty.base;
            size_t size = subAllocationProperty.size;
        }
    }
    ...