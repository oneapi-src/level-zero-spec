<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_ipc_mem_handle_type:

=================================
 IPC Memory Handle Type Extension
=================================

API
----

* Enumerations


    * ${x}_ipc_mem_handle_type_ext_version_t
    * ${x}_ipc_mem_handle_type_flags_t

* Structures


    * ${x}_ipc_mem_handle_type_ext_desc_t

* Functions

    * ${x}MemGetIpcHandleWithProperties

Overview
--------

When users are requesting IPC handles for L0 memory, there may be requirements for advanced features in the handle itself. One such feature is the ability to share the handle across a fabric, enabling memory sharing between devices or processes that are connected via a high-speed interconnect.

To facilitate this, the IPC Memory Handle Type Extension provides a mechanism to specify the type of IPC handle to be created during memory allocation or when obtaining an IPC handle for existing memory.

Checking IPC Support
~~~~~~~~~~~~~~~~~~~~~

Before requesting a specific IPC handle type, users can query the driver to determine what IPC handle types are supported by checking the IPC property flags:

.. parsed-literal::

    ${x}_ipc_properties_t ipcProps;
    ${x}DeviceGetIpcProperties(hDevice, &ipcProps);
    
    if (ipcProps.flags & ${X}_IPC_PROPERTY_FLAG_FABRIC_ACCESSIBLE) {
        // Driver supports fabric accessible IPC handles
    } else {
        // Fabric accessible IPC handles are not supported
    }

This approach allows applications to determine available IPC capabilities before attempting to create handles or allocate memory with specific IPC requirements.

Get IPC Handle Usage Example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To request an IPC handle for L0 memory that is fabric accessible, the user would populate the descriptor as follows:

.. parsed-literal::

    ze_ipc_mem_handle_type_ext_desc_t desc = {
        .stype = ZE_STRUCTURE_TYPE_IPC_MEM_HANDLE_TYPE_EXT_DESC,
        .pNext = NULL,
        .typeFlags = ZE_IPC_MEM_HANDLE_TYPE_FLAG_FABRIC_ACCESSIBLE
    };

    ze_ipc_mem_handle_t ipcHandle;
    ze_result_t result = zeMemGetIpcHandleWithProperties(hContext, ptr, &ipcHandle, &desc);

.. note::

    If the driver does not support ``ZE_IPC_MEM_HANDLE_TYPE_FLAG_FABRIC_ACCESSIBLE``, the function will return ``ZE_RESULT_ERROR_UNSUPPORTED_FEATURE``. Applications can proactively check for support by querying ``${x}_ipc_properties_t`` as shown in the "Checking IPC Support" section above.


Memory Allocation Usage Example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To allocate L0 memory with an IPC handle that is fabric accessible, the user would populate the descriptor as follows:

.. parsed-literal::

    ze_ipc_mem_handle_type_ext_desc_t desc = {
        .stype = ZE_STRUCTURE_TYPE_IPC_MEM_HANDLE_TYPE_EXT_DESC,
        .pNext = NULL,
        .typeFlags = ZE_IPC_MEM_HANDLE_TYPE_FLAG_FABRIC_ACCESSIBLE
    };

    ze_device_mem_alloc_desc_t deviceDesc = {
        .stype = ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC,
        .pNext = &desc,
        .flags = 0,
        .ordinal = 0
    };

    void* device_ptr = NULL;
    ze_result_t result = zeMemAllocDevice(hContext, hDevice, &deviceDesc, size, alignment, &device_ptr);

    ze_host_mem_alloc_desc_t hostDesc = {
        .stype = ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC,
        .pNext = &desc,
        .flags = 0
    };
    void* host_ptr = NULL;
    ze_result_t result = zeMemAllocHost(hContext, &hostDesc, size, alignment, &host_ptr);

    ze_physical_mem_desc_t physicalDesc = {
        .stype = ZE_STRUCTURE_TYPE_PHYSICAL_MEM_DESC,
        .pNext = &desc,
        .flags = 0,
        .size = size
    };
    void* physical_ptr = NULL;
    ze_result_t result = zePhysicalMemCreate(hContext, &physicalDesc, &physical_ptr);

.. note::

    If the driver does not support ``ZE_IPC_MEM_HANDLE_TYPE_FLAG_FABRIC_ACCESSIBLE``, the memory allocation functions (``zeMemAllocDevice``, ``zeMemAllocHost``, ``zePhysicalMemCreate``) will return ``ZE_RESULT_ERROR_UNSUPPORTED_FEATURE``. Applications can proactively check for support by querying ``${x}_ipc_properties_t`` as shown in the "Checking IPC Support" section above.