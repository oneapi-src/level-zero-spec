
:orphan:

.. _ZE_extension_ipc_mem_handle_type:

=================================
 IPC Memory Handle Type Extension
=================================

API
----

* Enumerations


    * :ref:`ze-ipc-mem-handle-type-ext-version-t`
    * :ref:`ze-ipc-mem-handle-type-flags-t`

* Structures


    * :ref:`ze-ipc-mem-handle-type-ext-desc-t`

* Functions

    * :ref:`zeMemGetIpcHandleWithProperties`

Overview
--------

When users are requesting IPC handles for L0 memory, there may be requirements for advanced features in the handle itself. One such feature is the ability to share the handle across a fabric, enabling memory sharing between devices or processes that are connected via a high-speed interconnect.

To facilitate this, the IPC Memory Handle Type Extension provides a mechanism to specify the type of IPC handle to be created during memory allocation or when obtaining an IPC handle for existing memory.

Physical memory handles (``ze_physical_mem_handle_t``) may be used as a source for IPC handles via
:ref:`zeMemGetIpcHandleWithProperties`\. The ``ptr`` argument may be either:

- A virtual address that was mapped to a physical memory object via :ref:`zeVirtualMemMap`\, or
- A value returned directly from :ref:`zePhysicalMemCreate`\.

Only one physical memory object may be associated with a single IPC handle at a time. When the
resulting IPC handle is opened in the receiving process via :ref:`zeMemOpenIpcHandle`\, the driver
assigns a new virtual address in the importing process without requiring a separate
:ref:`zeVirtualMemReserve` or :ref:`zeVirtualMemMap` call.

Checking IPC Support
~~~~~~~~~~~~~~~~~~~~~

Before requesting a specific IPC handle type, users can query the driver to determine what IPC handle types are supported by checking the IPC property flags:

.. parsed-literal::

    :ref:`ze-driver-ipc-properties-t` ipcProps;
    :ref:`zeDriverGetIpcProperties`\(hDriver, &ipcProps);
    
    if (ipcProps.flags & :ref:`ZE_IPC_PROPERTY_FLAG_FABRIC_ACCESSIBLE <ze-ipc-property-flags-t>`\) {
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

    If the driver does not support ``ZE_IPC_MEM_HANDLE_TYPE_FLAG_FABRIC_ACCESSIBLE``, the function will return ``ZE_RESULT_ERROR_UNSUPPORTED_FEATURE``. Applications can proactively check for support by querying ``:ref:`ze-driver-ipc-properties-t`\`` as shown in the "Checking IPC Support" section above.

Get IPC Handle from Physical Memory Example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To obtain an IPC handle from a physical memory object, the ``ptr`` argument passed to
:ref:`zeMemGetIpcHandleWithProperties` may be either the physical memory handle cast to a pointer,
or a virtual address previously mapped to the physical memory object via :ref:`zeVirtualMemMap`\.
The following example demonstrates the mapped VA case:

**Sending process:**

.. parsed-literal::

    // Create a physical memory object
    ze_physical_mem_desc_t pmemDesc = {
        .stype = ZE_STRUCTURE_TYPE_PHYSICAL_MEM_DESC,
        .pNext = NULL,
        .flags = 0,
        .size = physicalSize
    };
    ze_physical_mem_handle_t hPhysicalMem;
    zePhysicalMemCreate(hContext, hDevice, &pmemDesc, &hPhysicalMem);

    // Reserve VA and map the physical memory
    void* ptr = NULL;
    zeVirtualMemReserve(hContext, NULL, physicalSize, &ptr);
    zeVirtualMemMap(hContext, ptr, physicalSize, hPhysicalMem, 0,
        ZE_MEMORY_ACCESS_ATTRIBUTE_READWRITE);

    // Request a fabric-accessible IPC handle for the mapped physical memory
    ze_ipc_mem_handle_type_ext_desc_t desc = {
        .stype = ZE_STRUCTURE_TYPE_IPC_MEM_HANDLE_TYPE_EXT_DESC,
        .pNext = NULL,
        .typeFlags = ZE_IPC_MEM_HANDLE_TYPE_FLAG_FABRIC_ACCESSIBLE
    };
    ze_ipc_mem_handle_t ipcHandle;
    ze_result_t result = zeMemGetIpcHandleWithProperties(hContext, ptr, &ipcHandle, &desc);

    // NOTE: Transferring IPC handles is not a Level Zero API. The application is responsible
    // for sending the handle to the receiving process using its preferred out of band method
    // (e.g., Shared memory, TCP/IP, fabric, etc.)

**Receiving process:**

.. parsed-literal::

    // NOTE: Receiving IPC handles is not a Level Zero API. The application is responsible
    // for receiving the handle from the sending process using its preferred out of band method
    // (e.g., Shared memory, TCP/IP, fabric, etc.)
    ze_ipc_mem_handle_t ipcHandle;

    // Opening the handle assigns a new VA in this process for the physical memory.
    void* remotePtr = NULL;
    zeMemOpenIpcHandle(hContext, hDevice, ipcHandle, 0, &remotePtr);

.. note::

    Only one physical memory object may be mapped per IPC handle. Passing a ``ptr`` that spans
    multiple physical memory mappings will result in an error.


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

    If the driver does not support ``ZE_IPC_MEM_HANDLE_TYPE_FLAG_FABRIC_ACCESSIBLE``, the memory allocation functions (``zeMemAllocDevice``, ``zeMemAllocHost``, ``zePhysicalMemCreate``) will return ``ZE_RESULT_ERROR_UNSUPPORTED_FEATURE``. Applications can proactively check for support by querying ``:ref:`ze-driver-ipc-properties-t`\`` as shown in the "Checking IPC Support" section above.