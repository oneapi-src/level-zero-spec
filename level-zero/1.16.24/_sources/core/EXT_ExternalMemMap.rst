
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Accelerator devices can map external memory as a host allocation. The :ref:`ze-external-memmap-sysmem-ext-desc-t` struct defines the system memory being mapped as part of the :ref:`zeMemAllocHost`\.
The user may use this extention to specify, as part of the pNext member of the :ref:`ze-host-mem-alloc-desc-t` , the system memory that needs to be mapped as part of the allocation being created with a call to :ref:`zeMemAllocHost`\.
For read-only system memory $(X}_HOST_MEM_ALLOC_FLAG_MEM_READ_ONLY flag should be set in :ref:`ze-host-mem-alloc-desc-t`\.

