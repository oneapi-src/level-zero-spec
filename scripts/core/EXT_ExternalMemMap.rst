<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_external_memmap_sysmem:

======================================
 External Memory Mapping Extension
======================================

API
----
* Enumerations


    * ${x}_external_memmap_sysmem_ext_version_t


* Structures


    * ${x}_external_memmap_sysmem_ext_desc_t

Mapping External Memory to Host Allocation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Accelerator devices can map existing host system memory into a host allocation. The ${x}_external_memmap_sysmem_ext_desc_t struct defines the system memory being mapped as part of the ${x}MemAllocHost call.
The user may use this extension to specify, as part of the pNext member of the ${x}_host_mem_alloc_desc_t, the system memory that needs to be mapped as part of the allocation being created with a call to ${x}MemAllocHost.

The following rules apply when mapping external system memory:

* The ``pSystemMemory`` pointer and ``size`` must be aligned to the host page size. The host page size must be obtained using operating-system-specific calls; the mapped memory originates from the system allocator rather than from Level-Zero, so there is no Level-Zero query for this value.
* On success, the pointer returned from ${x}MemAllocHost is identical to ``pSystemMemory``. The virtual address is preserved, so the same address is valid on both the host and the device.
* Memory from the application's heap, stack, or statically-allocated (global) storage is supported. Support for memory obtained by other means is platform- and driver-dependent and is not guaranteed. If ``pSystemMemory`` points to a memory type that cannot be mapped, ${x}MemAllocHost returns ${X}_RESULT_ERROR_INVALID_ARGUMENT.
* Read-only host memory can only be mapped successfully when the ${X}_HOST_MEM_ALLOC_FLAG_MEM_READ_ONLY flag is set in ${x}_host_mem_alloc_desc_t. In that case device access to the mapped memory is read-only.
* The system memory referenced by ``pSystemMemory`` must remain valid for the entire lifetime of the resulting allocation. Freeing or unmapping the underlying system memory before the allocation is released results in undefined behavior.
* Mapped memory ranges must not overlap. Releasing a mapping with ${x}MemFree tears down the device page-table entries for its virtual address range. Because these page tables are shared across imports, releasing a mapping that overlaps another import also tears down the overlapping device page-table entries, leaving the other allocation invalid for device access. The host system memory itself is unaffected.
* After mapping, ${x}MemGetAllocProperties reports the allocation type as ${X}_MEMORY_TYPE_HOST_IMPORTED.
* The mapping is released by passing the pointer to ${x}MemFree, like any other host allocation.

