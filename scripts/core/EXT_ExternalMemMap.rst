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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Accelerator devices can map external memory as a host allocation. The ${x}_external_memmap_sysmem_ext_desc_t struct defines the system memory being mapped as part of the ${x}MemAllocHost.
The user may use this extention to specify, as part of the pNext member of the ${x}_host_mem_alloc_desc_t , the system memory that needs to be mapped as part of the allocation being created with a call to ${x}MemAllocHost.
For read-only system memory $(X}_HOST_MEM_ALLOC_FLAG_MEM_READ_ONLY flag should be set in ${x}_host_mem_alloc_desc_t.

