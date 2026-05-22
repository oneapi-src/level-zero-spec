
:orphan:

.. _ZE_experimental_kernel_allocation_properties:

===========================================
 Get Kernel Allocation Properties Extension
===========================================

API
---

* Enumerations

    * :ref:`ze-kernel-get-allocation-properties-exp-version-t`

* Structs
    * :ref:`ze-kernel-allocation-exp-properties-t`

* Functions

    * :ref:`zeKernelGetAllocationPropertiesExp`


=================================
 Get Kernel Allocation Properties
=================================

The goal of the extension is to report in unified form GPU memory ranges used by kernel,
both explicit like kernel arguments and implicit ones made by driver like printf surface,
scratch surface, etc. This information later can be used for some kernel instrumentation
to detect out-of-bound accesses, kernel profiling and so on.
There is a 2-step process to obtain this information. The first step is
to find the count of memory allocations owned by kernel, so the buffer is large enough
to store this number of :ref:`ze-kernel-allocation-exp-properties-t` must be allocated later.
This is done by providing an input allocation properties pointer with nullptr value.
After allocating a storage array of this size, the user then provides the valid size and
storage location to retrieve the data.

The following pseudo-code shows how to print information about kernel allocations:

.. parsed-literal::

    #include <iostream>
    //hKernel = valid kernel handle
    uint32_t numAllocs = 0;
    :ref:`zeKernelGetAllocationPropertiesExp`\(hKernel, &numAllocs, nullptr);
    std::vector<:ref:`ze-kernel-allocation-exp-properties-t`\> allocProps(numAlloc);
    :ref:`zeKernelGetAllocationPropertiesExp`\(hKernel, &numAllocs, allocProps.data());

    auto toStr = [](:ref:`ze-memory-type-t` type) {
        switch (type) {
        default: return "ZE_MEMORY_TYPE_UNKNOWN";
    #define CASE(_X_) case _X_ : return #_X_;
        CASE(ZE_MEMORY_TYPE_UNKNOWN);
        CASE(ZE_MEMORY_TYPE_HOST);
        CASE(ZE_MEMORY_TYPE_DEVICE);
        CASE(ZE_MEMORY_TYPE_SHARED);
    #undef  CASE
        }
    };

    for (uint32_t i = 0; i < allocCount; ++i) {
        std::cout << "Allocation " << i << ": " << std::hex << "0x" << allocaProps[i].base << ", size: " << std::dec << allocProps[i].size
                  << " argIndex: " << (int)allocProps[i].argIndex << " type: " << toStr(allocProps[i].type) << "\n";
    }

Possible output:

    Allocation 0: 0x14d9ff00000, size: 65536 argIndex: 0 type: ZE_MEMORY_TYPE_SHARED
    Allocation 1: 0x14d9fef0000, size: 65536 argIndex: 2 type: ZE_MEMORY_TYPE_SHARED
    Allocation 2: 0x14d9ff20000, size: 4194304 argIndex: -1 type: ZE_MEMORY_TYPE_UNKNOWN
    Allocation 3: 0xffff80010010b000, size: 4096 argIndex: -1 type: ZE_MEMORY_TYPE_UNKNOWN
