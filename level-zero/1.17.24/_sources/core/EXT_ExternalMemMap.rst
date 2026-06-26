
:orphan:

.. _ZE_extension_external_memmap_sysmem:

======================================
 External Memory Mapping Extension
======================================

API
----
* Enumerations


    * :ref:`ze-external-memmap-sysmem-ext-version-t`


* Structures


    * :ref:`ze-external-memmap-sysmem-ext-desc-t`

Mapping External Memory to Host Allocation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Accelerator devices can map existing host system memory into a host allocation. The :ref:`ze-external-memmap-sysmem-ext-desc-t` struct defines the system memory being mapped as part of the :ref:`zeMemAllocHost` call.
The user may use this extension to specify, as part of the pNext member of the :ref:`ze-host-mem-alloc-desc-t`\, the system memory that needs to be mapped as part of the allocation being created with a call to :ref:`zeMemAllocHost`\.

The following rules apply when mapping external system memory:

* The ``pSystemMemory`` pointer and ``size`` must be aligned to the host page size. The host page size must be obtained using operating-system-specific calls; the mapped memory originates from the system allocator rather than from Level-Zero, so there is no Level-Zero query for this value.
* On success, the pointer returned from :ref:`zeMemAllocHost` is identical to ``pSystemMemory``. The virtual address is preserved, so the same address is valid on both the host and the device.
* Memory from the application's heap, stack, or statically-allocated (global) storage is supported. Support for memory obtained by other means is platform- and driver-dependent and is not guaranteed. If ``pSystemMemory`` points to a memory type that cannot be mapped, :ref:`zeMemAllocHost` returns :ref:`ZE_RESULT_ERROR_INVALID_ARGUMENT <ze-result-t>`\.
* Read-only host memory can only be mapped successfully when the :ref:`ZE_HOST_MEM_ALLOC_FLAG_MEM_READ_ONLY <ze-host-mem-alloc-flags-t>` flag is set in :ref:`ze-host-mem-alloc-desc-t`\. In that case device access to the mapped memory is read-only.
* The system memory referenced by ``pSystemMemory`` must remain valid for the entire lifetime of the resulting allocation. Freeing or unmapping the underlying system memory before the allocation is released results in undefined behavior.
* Mapped memory ranges must not overlap. Releasing a mapping with :ref:`zeMemFree` tears down the device page-table entries for its virtual address range. Because these page tables are shared across imports, releasing a mapping that overlaps another import also tears down the overlapping device page-table entries, leaving the other allocation invalid for device access. The host system memory itself is unaffected.
* After mapping, :ref:`zeMemGetAllocProperties` reports the allocation type as :ref:`ZE_MEMORY_TYPE_HOST_IMPORTED <ze-memory-type-t>`\.
* The mapping is released by passing the pointer to :ref:`zeMemFree`\, like any other host allocation.

