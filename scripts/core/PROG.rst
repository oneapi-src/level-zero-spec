
<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
.. _core-programming-guide:

========================
 Core Programming Guide
========================

Drivers and Devices
===================

The API architecture exposes both physical and logical abstraction of the underlying devices capabilities.
The device, sub-device and memory are exposed at physical level while command queues, events and
synchronization methods are defined as logical entities.
All logical entities will be bound to device level physical capabilities.

Device discovery APIs enumerate the accelerators functional features.
These APIs provide interface to query information like compute unit count within the device or sub device, 
available memory and affinity to the compute, user managed cache size and work submission command queues.

Drivers
-------

A driver object represents a collection of physical devices in the system accessed by the same Level-Zero driver.

- The application may query the number of Level-Zero drivers installed on the system, and their respective handles, using ${x}DriverGet.
- More than one driver may be available in the system. For example, one driver may support two GPUs from one vendor, another driver supports a GPU from a different vendor, and finally a different driver may support an FPGA.
- Driver objects are read-only, global constructs. i.e. Multiple calls to ${x}DriverGet will return identical driver handles.
- A driver handle is primarily used during device discovery and during creation and management of contexts.

Device
------

A device object represents a physical device in the system that supports Level-Zero.

- The application may query the number devices supported by a driver, and their respective handles, using ${x}DeviceGet.
- Device objects are read-only, global constructs. i.e. Multiple calls to ${x}DeviceGet will return identical device handles.
- A device handle is primarily used during creation and management of resources that are specific to a device.
- The application is responsible for sharing memory and explicit submission and synchronization across multiple devices.
- Device may expose sub-devices that allow finer-grained control of physical or logical partitions of a device.

The following diagram illustrates the relationship between the driver, device and other objects described in this document.

.. image:: ../images/core_device.png

Initialization and Discovery
----------------------------

The Level-Zero API must be initialized by calling ${x}Init before calling any other API function.
This function will load all Level-Zero driver(s) in the system into memory for the current process, for use by all Host threads.
Simultaneous calls to ${x}Init are thread-safe and only one instance of each driver will be loaded. 

The following pseudo-code demonstrates a basic initialization and device discovery sequence:

.. parsed-literal::

       // Initialize the driver
       ${x}Init(0);

       // Discover all the driver instances
       uint32_t driverCount = 0;
       ${x}DriverGet(&driverCount, nullptr);

       ${x}_driver_handle_t* allDrivers = allocate(driverCount * sizeof(${x}_driver_handle_t));
       ${x}DriverGet(&driverCount, allDrivers);

       // Find a driver instance with a GPU device
       ${x}_driver_handle_t hDriver = nullptr;
       ${x}_device_handle_t hDevice = nullptr;
       for(i = 0; i < driverCount; ++i) {
           uint32_t deviceCount = 0;
           ${x}DeviceGet(allDrivers[i], &deviceCount, nullptr);

           ${x}_device_handle_t* allDevices = allocate(deviceCount * sizeof(${x}_device_handle_t));
           ${x}DeviceGet(allDrivers[i], &deviceCount, allDevices);

           for(d = 0; d < deviceCount; ++d) {
               ${x}_device_properties_t device_properties;
               ${x}DeviceGetProperties(allDevices[d], &device_properties);
       
               if(${X}_DEVICE_TYPE_GPU == device_properties.type) {
                   hDriver = allDrivers[i];
                   hDevice = allDevices[d];
                   break;
               }
           }

           free(allDevices);
           if(nullptr != hDriver) {
               break;
           }
       }

       free(allDrivers);
       if(nullptr == hDevice)
           return; // no GPU devices found

       ...

Contexts
========

A context is a logical object used by the driver for managing all memory, command queues/lists, modules, synchronization objects, etc.

- A context handle is primarily used during creation and management of resources that may be used by multiple devices.
- For example, memory is not implicitly shared across all devices supported by a driver. However, it is available to be explicitly shared.

The following pseudo-code demonstrates a basic context creation:

.. parsed-literal::

        // Create context
        ${x}_context_desc_t ctxtDesc = {
           ${X}_STRUCTURE_TYPE_CONTEXT_DESC,
           nullptr,
           0
        };
        ${x}ContextCreate(hDriver, &ctxtDesc, &hContext);


An application may optionally create multiple contexts using ${x}ContextCreate.

- The primary usage-model for multiple contexts is isolation of memory and objects for multiple libraries within the same process.
- The same context may be used simultaneously on multiple Host threads.

The following pseudo-code demonstrates a basic context creation and activation sequence:

.. parsed-literal::

        // Create context(s)
        ${x}ContextCreate(hDriver, &ctxtDesc, &hContextA);
        ${x}ContextCreate(hDriver, &ctxtDesc, &hContextB);

        ${x}MemAllocHost(hContextA, &desc, 80, 0, &ptrA);
        ${x}MemAllocHost(hContextB, &desc, 88, 0, &ptrB);

        memcpy(ptrA, ptrB, 0xe); // ok
        ${x}MemGetAllocProperties(hContextA, ptrB, &props, &hDevice); // illegal: Context A has no knowledge of ptrB


If a device was hung or reset, then the context is no longer valid and all APIs will return ${X}_RESULT_ERROR_DEVICE_LOST when any object associated with that context is used.
All pointers to memory allocations and handles to objects (including other contexts) created on the context will be invalid and should no longer be used.
An application can use ${x}ContextGetStatus at any time to check the status of a context.

In order to recover, the context must be destroyed using ${x}ContextDestroy.
After the device is reset, the application can create a new context and continue operation.
An application must call ${x}DeviceGetStatus to confirm the device has been reset and update the OS handle attached to the device handle.
Otherwise, even after the device has been reset, the call to ${x}ContextCreate will fail.

Memory and Images
=================

Memory is visible to the upper-level software stack as unified memory with a single virtual address space
covering both the Host and a specific device.

For GPUs, the API exposes two levels of the device memory hierarchy:

1. Local Device Memory: can be managed at the device and/or sub device level.
2. Device Cache(s):

    + Last Level Cache (L3) can be controlled through memory allocation APIs.
    + Low Level Cache (L1) can be controlled through program language intrinsics.

The API allows allocation of buffers and images at device and sub device granularity with full cacheablity hints.

- Buffers are transparent memory accessed through virtual address pointers
- Images are opaque objects accessed through handles

The memory APIs provide allocation methods to allocate either device, host or shared memory.
The APIs enable both implicit and explicit management of the resources by the application or runtimes.
The interface also provides query capabilities for all memory objects.

There are two types of allocations:

1. :ref:`LinearMemory` - linear, unformatted allocations for direct access from both the host and device.
2. :ref:`Images` - non-linear, formatted allocations for direct access from the device.

.. _LinearMemory:

Memory
------

Linear, unformatted memory allocations are represented as pointers in the host application.
A pointer on the Host has the same size as a pointer on the device.

Types
~~~~~

Three types of allocations are supported.
The type of allocation describes the *ownership* of the allocation:

1. **Host** allocations are owned by the host and are intended to be allocated out of system memory.

    + Host allocations are accessible by the host and one or more devices.
    + The same pointer to a host allocation may be used on the host and all supported devices; they have *address equivalence*.
    + Host allocations are not expected to migrate between system memory and device local memory.
    + Host allocations trade off wide accessibility and transfer benefits for potentially higher per-access costs, such as over PCI express.

2. **Device** allocations are owned by a specific device and are intended to be allocated out of device local memory, if present.

    + Device allocations generally trade off access limitations for higher performance.
    + With very few exceptions, device allocations may only be accessed by the specific device that they are allocated on, 
      or copied to another device or Host allocation.
    + The same pointer to a device allocation may be used on any supported device.

3. **Shared** allocations share ownership and are intended to migrate between the host and one or more devices.

    + Shared allocations are accessible by at least the host and an associated device.
    + Shared allocations may be accessed by other devices in some cases.
    + Shared allocations trade off transfer costs for per-access benefits.
    + The same pointer to a shared allocation may be used on the host and all supported devices.

A **Shared System** allocation is a sub-class of a **Shared** allocation,
where the memory is allocated by a *system allocator* (such as ``malloc`` or ``new``) rather than by an allocation API.
Shared system allocations have no associated device; they are inherently cross-device.
Like other shared allocations, shared system allocations are intended to migrate between the host and supported devices,
and the same pointer to a shared system allocation may be used on the host and all supported devices.

In summary:

+-------------------+---------------------------------------+-----------------+----------------------------+----------------+----------+
| Name              | Initial Location                      | Accessible By   |                            | Migratable To  |          |
+===================+=======================================+=================+============================+================+==========+
| **Host**          | Host                                  | Host            | Yes                        | Host           | N/A      |
|                   |                                       +-----------------+----------------------------+----------------+----------+
|                   |                                       | Any Device      | Yes (perhaps over PCIe)    | Device         | No       |
+-------------------+---------------------------------------+-----------------+----------------------------+----------------+----------+
| **Device**        | Specific Device                       | Host            | No                         | Host           | No       |
|                   |                                       +-----------------+----------------------------+----------------+----------+
|                   |                                       | Specific Device | Yes                        | Device         | N/A      |
|                   |                                       +-----------------+----------------------------+----------------+----------+
|                   |                                       | Another Device  | Optional (may require p2p) | Another Device | No       |
+-------------------+---------------------------------------+-----------------+----------------------------+----------------+----------+
| **Shared**        | Host, Specific Device, or Unspecified | Host            | Yes                        | Host           | Yes      |
|                   |                                       +-----------------+----------------------------+----------------+----------+
|                   |                                       | Specific Device | Yes                        | Device         | Yes      |
|                   |                                       +-----------------+----------------------------+----------------+----------+
|                   |                                       | Another Device  | Optional (may require p2p) | Another Device | Optional |
+-------------------+---------------------------------------+-----------------+----------------------------+----------------+----------+
| **Shared System** | Host                                  | Host            | Yes                        | Host           | Yes      |
|                   |                                       +-----------------+----------------------------+----------------+----------+
|                   |                                       | Device          | Yes                        | Device         | Yes      |
+-------------------+---------------------------------------+-----------------+----------------------------+----------------+----------+

Devices may support different capabilities for each type of allocation. Supported capabilities are:

* ${X}_MEMORY_ACCESS_CAP_FLAG_RW - if a device supports access (read or write) to allocations of the specified type.
* ${X}_MEMORY_ACCESS_CAP_FLAG_ATOMIC - if a device support atomic operations on allocations of the specified type. Atomic operations may include relaxed consistency read-modify-write atomics and atomic operations that enforce memory consistency for non-atomic operations.
* ${X}_MEMORY_ACCESS_CAP_FLAG_CONCURRENT - if a device supports concurrent access to allocations of the specified type. Concurrent access may be from another device that supports concurrent access, or from the host. Devices that support concurrent access but do not support concurrent atomic access must write to unique non-overlapping memory locations to avoid data races and hence undefined behavior.
* ${X}_MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC - if a device supports concurrent atomic operations on allocations of the specified type. Concurrent atomic operations may be from another device that supports concurrent atomic access, or from the host. Devices that support concurrent atomic access may use atomic operations to enforce memory consistency with other devices that support concurrent atomic access, or with the host.

At a minimum, drivers will assign unique physical pages for each device and shared memory allocation.
However, it is undefined behavior for an application to access memory outside of the allocation size requested.
The actual page size used for an allocation can be queried from ${x}_memory_allocation_properties_t.pageSize using ${x}MemGetAllocProperties.
Applications should implement usage-specific allocators from device memory pools (e.g., small and/or fixed-sized allocations, lock-free, etc.).

Furthermore, drivers may *oversubscribe* some **shared** allocations. 
When and how such oversubscription occurs, including which allocations are evicted when the working set changes, are considered implementation details.

The required matrix of capabilities are:

+----------------------------------+-----------+---------------+-------------------+--------------------------+
| Allocation Type                  | RW Access | Atomic Access | Concurrent Access | Concurrent Atomic Access |
+==================================+===========+===============+===================+==========================+
| **Host**                         | Required  | Optional      | Optional          | Optional                 |
+----------------------------------+-----------+---------------+-------------------+--------------------------+
| **Device**                       | Required  | Optional      | Optional          | Optional                 |
+----------------------------------+-----------+---------------+-------------------+--------------------------+
| **Shared**                       | Required  | Optional      | Optional          | Optional                 |
+----------------------------------+-----------+---------------+-------------------+--------------------------+
| **Shared** (Cross-Device)        | Optional  | Optional      | Optional          | Optional                 |
+----------------------------------+-----------+---------------+-------------------+--------------------------+
| **Shared System** (Cross-Device) | Optional  | Optional      | Optional          | Optional                 |
+----------------------------------+-----------+---------------+-------------------+--------------------------+

Cache Hints, Prefetch, and Memory Advice
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Cacheability hints may be provided via separate host and device allocation flags when memory is allocated.

**Shared** allocations may be prefetched to a supporting device via the ${x}CommandListAppendMemoryPrefetch API.
Prefetching may allow memory transfers to be scheduled concurrently with other computations and may improve performance.

Additionally, an application may provide memory advice for a **shared** allocation via the ${x}CommandListAppendMemAdvise API,
to override driver heuristics or migration policies.
Memory advice may avoid unnecessary or unprofitable memory transfers and may improve performance.

Both prefetch and memory advice are asynchronous operations that are appended into command lists.

Reserved Device Allocations
---------------------------

If an application needs finer grained control of physical memory consumption for device allocations then it
can reserve a range of the virtual address space and map this to physical memory as needed. This provides
flexibility for applications to manage large dynamic data structures which can grow and shrink over time
while maintaining optimal physical memory usage.

Reserving Virtual Address Space
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Virtual memory can be reserved using ${x}VirtualMemReserve. The reservation starting address
and size must be page aligned. Applications should query the page size for the allocation
using ${x}VirtualMemQueryPageSize.

The following pseudo-code demonstrates a basic sequence for reserving virtual memory:

.. parsed-literal::

        // Query page size for our 1MB allocation.
        size_t pageSize;
        size_t allocationSize = 1048576;
        ${x}VirtualMemQueryPageSize(hContext, hDevice, allocationSize, &pageSize);

        // Reserve 1MB of virtual address space.
        size_t reserveSize = align(allocationSize, pageSize);

        void* ptr = nullptr;
        ${x}VirtualMemReserve(hContext, nullptr, reserveSize, &ptr);

Growing Virtual Address Reservations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

An application may wish to reserve an address range starting at a specific virtual address.
This may be useful when there is a need to grow a reservation. However, if the
implementation is not able to reserve the new allocation at the requested starting address
then it will find a new suitable range with a different starting address. If the application
requires a specific starting address then the application should ensure that the return
address from ${x}VirtualMemReserve matches the starting address it wants. If they
are different then the application may want to create a new larger reservation and remap
the physical memory from the first reservation to this new reservation and free the
old reservation.

.. parsed-literal::

        // Reserve another 1MB of virtual address space that is contiguous with previous reservation.
        void* newptr = (uint8_t*)ptr + reserveSize;
        void* retptr;
        ${x}VirtualMemReserve(hContext, newptr, reserveSize, &retptr);

        if (retptr != newptr)
        {
            // Free new reservation as it's not what we want due to incorrect starting address.
            ${x}VirtualMemFree(hContext, retptr, reserveSize);

            // Make new larger 2MB reservation and remap physical pages to this.
            size_t pageSize;
            size_t largerAllocationSize = 2097152;
            ${x}VirtualMemQueryPageSize(hContext, hDevice, largerAllocationSize, &pageSize);

            // Reserve 2MB of virtual address space.
            size_t largerReserveSize = align(largerAllocationSize, pageSize);

            void* ptr = nullptr;
            ${x}VirtualMemReserve(hContext, nullptr, largerReserveSize, &ptr);

            // Remap physical pages from original reservation to our new larger reservation.
            ...

            // Free original reservation that we were trying to grow.
            ${x}VirtualMemFree(hContext, ptr, reserveSize);
        }

Physical Memory
~~~~~~~~~~~~~~~

Physical memory is explicitly represented in the API as physical memory objects
that are reservations of physical pages. The application will use ${x}PhysicalMemCreate
to create a physical memory object.

The following pseudo-code demonstrates a basic sequence for creating a physical memory object:

.. parsed-literal::

        // Create 1MB physical memory object
        ${x}_physical_mem_handle_t hPhysicalAlloc;
        size_t physicalSize = align(allocationSize, pageSize);
        ${x}_physical_mem_desc_t pmemDesc = {
            ${X}_STRUCTURE_TYPE_PHYSICAL_MEM_DESC,
            nullptr,
            0, // flags
            physicalSize // size
        };

        ${x}PhysicalMemCreate(hContext, hDevice, &pmemDesc, &hPhysicalAlloc);

Mapping Virtual Memory Pages
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Reserved virtual memory pages can be mapped to physical memory using ${x}VirtualMemMap.
An application can map the entire reserved virtual address range or can sparsely map the
reserved virtual address range using one or more physical memory objects. Once mapped, the
physical pages for a physical memory object can be faulted in for devices that support
on-demand paging. In addition, the residency API can be used to control residency of
these physical pages.

The following pseudo-code demonstrates mapping a 1MB reservation into physical memory:

.. parsed-literal::

        // Map entire 1MB reservation and set access to read/write.
        ${x}VirtualMemMap(hContext, ptr, reserveSize, hPhysicalAlloc, 0,
            ${X}_MEMORY_ACCESS_ATTRIBUTE_READWRITE);


Access Attributes
~~~~~~~~~~~~~~~~~
Access attributes can be set for a range of pages when mapping virtual memory
pages with ${x}VirtualMemMap or with ${x}VirtualMemSetAccessAttribute.
In addition, an application can query access attributes for a page aligned
virtual memory range.

.. parsed-literal::

        size_t accessRangeSize;
        ${x}_memory_access_attribute_t access;
        ${x}VirtualMemGetAccessAttribute(hContext, ptr, reserveSize, &access, &accessRangeSize);

        // Expecting entire range to have the same access attribute and it be read/write.
        assert(accessRangeSize == reserveSize);
        assert(access == ${X}_MEMORY_ACCESS_ATTRIBUTE_READWRITE);

Sparse Mappings
~~~~~~~~~~~~~~~

Applications may desire to reserve large virtual address ranges to make available
to its custom allocators. These ranges can be sparsely mapped using one or more physical
memory objects. It is recommended that the application queries the page size for each
suballocation to ensure the implementation can use an optimal page size for the mappings
based on the alignments used for starting address and size used.

The following example makes a 1GB reserved allocation and then makes both 128KB and 8MB sub-allocations.

.. image:: ../images/core_reserved_suballocations.png

.. parsed-literal::

        // Reserve 1GB of virtual address space to manage.
        size_t pageSize;
        size_t allocationSize = 1048576000;
        ${x}VirtualMemQueryPageSize(hContext, hDevice, allocationSize, &pageSize);

        size_t reserveSize = align(allocationSize, pageSize);

        void* ptr = nullptr;
        ${x}VirtualMemReserve(hContext, nullptr, reserveSize, &ptr);

        ...

        // Sub-allocate 128KB of our 1GB allocation.
        size_t subAllocSize = 131072;
        ${x}VirtualMemQueryPageSize(hContext, hDevice, subAllocSize, &pageSize);
        
        // Create physical memory object for our 128KB sub-allocation.
        size_t subAllocAlignedSize = align(subAllocSize, pageSize);
        ${x}_physical_mem_desc_t pmemDesc = {
            ${X}_STRUCTURE_TYPE_PHYSICAL_MEM_DESC,
            nullptr,
            0, // flags
            subAllocAlignedSize // size
        };
        ${x}_physical_mem_handle_t hPhysicalAlloc;
        ${x}PhysicalMemCreate(hContext, hDevice, &pmemDesc, &hPhysicalAlloc);

        // Find suitable 128KB sub-allocation that matches page alignments.
        ...

        ${x}VirtualMemMap(hContext, subAllocPtr, subAllocAlignedSize, hPhysicalAlloc, 0,
            ${X}_MEMORY_ACCESS_ATTRIBUTE_READWRITE);

        ...

        // Sub-allocate 8MB of our 1GB allocation.
        size_t subAllocDiffSize = 8388608;
        ${x}VirtualMemQueryPageSize(hContext, hDevice, subAllocDiffSize, &pageSize);
        ...

.. _Images:

Images
------

An image is used to store multi-dimensional and format-defined memory. 
An image's contents may be stored in an implementation-specific encoding 
and layout in memory for optimal device access
(e.g., tile swizzle patterns, lossless compression, etc.).
There is no support for direct Host access to an image's content.
However, when an image is copied to a Host-accessible memory allocation,
its contents will be implicitly decoded to be implementation-independent.

.. parsed-literal::

       // Specify single component FLOAT32 format
       ${x}_image_format_t format = {
           ${X}_IMAGE_FORMAT_LAYOUT_32, ${X}_IMAGE_FORMAT_TYPE_FLOAT,
           ${X}_IMAGE_FORMAT_SWIZZLE_R, ${X}_IMAGE_FORMAT_SWIZZLE_0, ${X}_IMAGE_FORMAT_SWIZZLE_0, ${X}_IMAGE_FORMAT_SWIZZLE_1
       };

       ${x}_image_desc_t imageDesc = {
           ${X}_STRUCTURE_TYPE_IMAGE_DESC,
           nullptr,
           0, // read-only
           ${X}_IMAGE_TYPE_2D,
           format,
           128, 128, 0, 0, 0
       };
       ${x}_image_handle_t hImage;
       ${x}ImageCreate(hContext, hDevice, &imageDesc, &hImage);

       // upload contents from host pointer
       ${x}CommandListAppendImageCopyFromMemory(hCommandList, hImage, nullptr, pImageData, nullptr, 0, nullptr);
       ...

A format descriptor is a combination of a format layout, type, and a swizzle.
The format layout describes the number of components and their corresponding bit
widths. The type describes the data type for all of these components with some
exceptions that are described below. The swizzles associate how the image
components are mapped into XYZW/RGBA channels of the kernel. It is allowed
to replicate components into the channels.

The following table describes which types are required for each layout.

+---------------+-------------+-------------+-------------+-------------+-------------+
| Format layout | UINT        | SINT        | UNORM       | SNORM       | FLOAT       |
+===============+=============+=============+=============+=============+=============+
| 8             | Required    | Required    | Required    | Required    | Unsupported |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 8_8           | Required    | Required    | Required    | Required    | Unsupported |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 8_8_8_8       | Required    | Required    | Required    | Required    | Unsupported |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 16            | Required    | Required    | Required    | Required    | Required    |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 16_16         | Required    | Required    | Required    | Required    | Required    |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 16_16_16_16   | Required    | Required    | Required    | Required    | Required    |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 32            | Required    | Required    | Required    | Required    | Required    |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 32_32         | Required    | Required    | Required    | Required    | Required    |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 32_32_32_32   | Required    | Required    | Required    | Required    | Required    |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 10_10_10_2    | Required    | Required    | Required    | Required    | Required    |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 11_11_10      | Unsupported | Unsupported | Unsupported | Unsupported | Required    |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 5_6_5         | Unsupported | Unsupported | Required    | Unsupported | Unsupported |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 5_5_5_1       | Unsupported | Unsupported | Required    | Unsupported | Unsupported |
+---------------+-------------+-------------+-------------+-------------+-------------+
| 4_4_4_4       | Unsupported | Unsupported | Required    | Unsupported | Unsupported |
+---------------+-------------+-------------+-------------+-------------+-------------+

Device Cache Settings
---------------------

There are two methods for device and kernel cache control:

1. Cache Size Configuration: Ability to configure larger size for SLM vs Data per Kernel instance.
2. Runtime Hint/preference for application to allow access to be Cached or not in Device Caches. For GPU device this is provided via two ways:

       - During Image creation via Flag
       - Kernel instruction

The following pseudo-code demonstrates a basic sequence for Cache size
configuration:

.. parsed-literal::

       // Configure cache to support larger SLM
       // Note: The cache setting is applied to each kernel.
       ${x}KernelSetCacheConfig(hKernel, ${X}_CACHE_CONFIG_FLAG_LARGE_SLM);


.. _external-memory:

External Memory Import and Export
---------------------------------

External memory handles may be imported from other APIs, or exported for use in other APIs.
Importing and exporting external memory is an optional feature.
Devices may describe the types of external memory handles they support using ${x}DeviceGetExternalMemoryProperties.

Importing and exporting external memory is supported for device memory allocations and images.

The following pseudo-code demonstrates how to allocate and export an external memory handle for a device memory allocation as a Linux dma_buf:

.. parsed-literal::

        // Set up the request for an exportable allocation
        ${x}_external_memory_export_desc_t export_desc = {
            ${X}_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_DESC,
            nullptr, // pNext
            ${X}_EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF
        };

        // Link the request into the allocation descriptor and allocate
        alloc_desc.pNext = &export_desc;
        ${x}MemAllocDevice(hContext, &alloc_desc, size, alignment, hDevice, &ptr);

        ...

        // Set up the request to export the external memory handle
        ${x}_external_memory_export_fd_t export_fd = {
            ${X}_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_FD,
            nullptr, // pNext
            ${X}_EXTERNAL_MEMORY_TYPE_FLAG_OPAQUE_FD,
            0 // [out] fd
        };

        // Link the export request into the query
        alloc_props.pNext = &export_fd;
        ${x}MemGetAllocProperties(hContext, ptr, &alloc_props, nullptr);

The following pseudo-code how to import a Linux dma_buf as an external memory handle for a device memory allocation:

.. parsed-literal::

        // Set up the request to import the external memory handle
        ${x}_external_memory_import_fd_t import_fd = {
            ${X}_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD,
            nullptr, // pNext
            ${X}_EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF,
            fd
        };

        // Link the request into the allocation descriptor and allocate
        alloc_desc.pNext = &import_fd;
        ${x}MemAllocDevice(hContext, &alloc_desc, size, alignment, hDevice, &ptr);

Command Queues and Command Lists
================================

The following are the motivations for separating a command queue from a command list:

- Command queues are mostly associated with physical device properties, such as the number of input streams.
- Command queues provide (near) zero-latency access to the device.
- Command lists are mostly associated with Host threads for simultaneous construction.
- Command list construction can occur independently of command queue submission.

The following diagram illustrates the hierarchy of command lists and command queues to the device:

.. image:: ../images/core_queue.png

Command Queues
--------------

A command queue represents a logical input stream to the device, tied to a physical input
stream.

Creation
~~~~~~~~

-  At creation time, the logical command queue is explicitly bound to a physical command queue.
-  The number and properties of physical command queues is queried by using ${x}DeviceGetCommandQueueGroupProperties.
-  Multiple logical command queues may be created that use the same physical command queue. For example,
   an application may create a logical command queue per Host thread with different scheduling priorities.
-  Multiple logical command queues created for the same physical command queue on the same context,
   also share the same physcial hardware context.
-  The maximum number of logical command queues an application can create is limited by device-specific
   resources; e.g., the maximum number of logical hardware contexts supported by the device. 
   This can be queried from ${x}_device_properties_t.maxHardwareContexts.
-  All command lists executed on a logical command queue are guaranteed to **only** execute on the physical
   command queue which it is assigned; e.g., copy commands in a compute command list / queue will
   execute via the compute engine, not the copy engine.

The following pseudo-code demonstrates a basic sequence for creation of command queues:

.. parsed-literal::

    // Discover all command queue types
    uint32_t cmdqueueGroupCount = 0;_
    ${x}DeviceGetCommandQueueGroupProperties(hDevice, &cmdqueueGroupCount, nullptr);

    ${x}_command_queue_group_properties_t* cmdqueueGroupProperties = (${x}_command_queue_group_properties_t*)
        malloc(cmdqueueGroupCount * sizeof(${x}_command_queue_group_properties_t));
    ${x}DeviceGetCommandQueueGroupProperties(hDevice, &cmdqueueGroupCount, allQueues);


    // Find a proper command queue
    for(uint32_t i = 0; i < cmdqueueGroupCount; ++i) {
        if( cmdqueueGroupProperties.flags & ${X}_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE ) {
            command_queue_ordinal = i;
            break;
        }
    }

    if(computeQueueGroupOrdinal == cmdqueueGroupCount)
        return; // no compute queues found

    // Create a command queue
    ${x}_command_queue_desc_t commandQueueDesc = {
        ${X}_STRUCTURE_TYPE_COMMAND_QUEUE_DESC,
        nullptr,
        computeQueueGroupOrdinal,
        0, // index
        0, // flags
        ${X}_COMMAND_QUEUE_MODE_DEFAULT,
        ${X}_COMMAND_QUEUE_PRIORITY_NORMAL
    };
    ${x}_command_queue_handle_t hCommandQueue;
    ${x}CommandQueueCreate(hContext, hDevice, &commandQueueDesc, &hCommandQueue);
    ...

Execution
~~~~~~~~~

- Command lists submitted to a command queue are **immediately** executed in a fifo manner.
- Command queue submission is free-treaded, allowing multiple Host threads to
  share the same command queue.
- If multiple Host threads enter the same command queue simultaneously, then execution order
  is undefined.
- Command lists can only be executed on a command queue with an identical command queue group ordinal,
  see more details below.
- If a device contains multiple sub-devices, then command lists submitted to a device-level command queue
  may be optimized by the driver to fully exploit the concurrency of the sub-devices by distributing command lists across sub-devices.
  If the application prefers to opt-out of these optimizations, such as when the application plans to perform this distribution itself,
  then it should use ${X}_COMMAND_QUEUE_FLAG_EXPLICIT_ONLY. Only command lists created using ${X}_COMMAND_LIST_FLAG_EXPLICIT_ONLY
  can be executed on a command queue created using ${X}_COMMAND_QUEUE_FLAG_EXPLICIT_ONLY.

Destruction
~~~~~~~~~~~

-  The application is responsible for making sure the device is not currently
   executing from a command queue before it is deleted. This is
   typically done by tracking command queue fences, but may also be
   handled by calling ${x}CommandQueueSynchronize.

Command Lists
-------------

A command list represents a sequence of commands for execution on a command queue.

.. _creation-1:

Creation
~~~~~~~~

-  A command list is created for a device to allow device-specific appending of commands.
-  A command list is created for execution on a specific type of command queue, specified using
   the command queue group ordinal.
-  A command list can be copied to create another command list. The application may use this
   to copy a command list for use on a different device.

Appending
~~~~~~~~~

-  There is no implicit binding of command lists to Host threads. Therefore, an
   application may share a command list handle across multiple Host threads. However,
   the application is responsible for ensuring that multiple Host threads do not access
   the same command list simultaneously.
-  By default, commands are started in the same order in which they are appended.
   However, an application may allow the driver to optimize the ordering by using
   ${X}_COMMAND_LIST_FLAG_RELAXED_ORDERING. Reordering is guaranteed to only occur
   between barriers and synchronization primitives.
-  By default, commands submitted to a command list are optimized for execution by
   balancing both device throughput and Host latency. 
-  For very low-level latency usage-models, applications should use immediate command lists. 
-  For usage-models where maximum throughput is desired, applications should 
   use ${X}_COMMAND_LIST_FLAG_MAXIMIZE_THROUGHPUT. This flag will indicate to the driver
   it may perform additional device-specific optimizations.
-  If a device contains multiple sub-devices, then commands submitted to a device-level
   command list may be optimized by the driver to fully exploit the concurrency of the
   sub-devices by distributing commands across sub-devices. If the application prefers
   to opt-out of these optimizations, such as when the application plans to perform this
   distribution itself, then it should use ${X}_COMMAND_LIST_FLAG_EXPLICIT_ONLY.

The following pseudo-code demonstrates a basic sequence for creation of command lists:

.. parsed-literal::

       // Create a command list
       ${x}_command_list_desc_t commandListDesc = {
           ${X}_STRUCTURE_TYPE_COMMAND_LIST_DESC,
           nullptr,
           computeQueueGroupOrdinal,
           0 // flags
       };
       ${x}_command_list_handle_t hCommandList;
       ${x}CommandListCreate(hContext, hDevice, &commandListDesc, &hCommandList);
       ...

Submission
~~~~~~~~~~

- There is no implicit association between a command list and a logical command queue. 
  Therefore, a command list may be submitted to any or multiple logical command queues.
- By definition, a command list cannot be executed concurrently on multiple physical command queues.
- If a command list is meant to be submitted to a physical copy-only command queue,
  then it must be created using a command queue group ordinal with
  ${X}_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY set and ${X}_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE not set,
  and submitted to a logical command queue created using the same ordinal.  
- The application is responsible for calling close before submission to a command queue.
- Command lists do not inherit state from other command lists executed on the same
  command queue.  i.e. each command list begins execution in its own default state.
- A command list may be submitted multiple times.  It is up to the application to ensure 
  that the command list can be executed multiple times.
  For example, event must be explicitly reset prior to re-execution.

The following pseudo-code demonstrates submission of commands to a command queue, via a command list:

.. parsed-literal::

       ...
       // finished appending commands (typically done on another thread)
       ${x}CommandListClose(hCommandList);

       // Execute command list in command queue
       ${x}CommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

       // synchronize host and device
       ${x}CommandQueueSynchronize(hCommandQueue, UINT32_MAX);

       // Reset (recycle) command list for new commands
       ${x}CommandListReset(hCommandList);
       ...

Recycling
~~~~~~~~~

-  A command list may be recycled to avoid the overhead of frequent creation and destruction.
-  The application is responsible for making sure the device is not currently
   executing from a command list before it is reset. This should be
   handled by tracking a completion event associated with the command list.
-  The application is responsible for making sure the device is not currently
   executing from a command list before it is deleted. This should be
   handled by tracking a completion event associated with the command list.

Low-Latency Immediate Command Lists
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A special type of command list can be used for very low-latency submission usage-models.

- An immediate command list is both a command list and an implicit command queue.
- An immediate command list is created using a command queue descriptor.
- Commands submitted to an immediate command list are immediately executed on the device.
- An immediate command list is not required to be closed or reset. However, usage will be honored, and expected behaviors will be followed.

The following pseudo-code demonstrates a basic sequence for creation and usage of immediate command lists:

.. parsed-literal::

       // Create an immediate command list
       ${x}_command_queue_desc_t commandQueueDesc = {
           ${X}_STRUCTURE_TYPE_COMMAND_QUEUE_DESC,
           nullptr,
           computeQueueGroupOrdinal,
           0, // index
           0, // flags
           ${X}_COMMAND_QUEUE_MODE_DEFAULT,
           ${X}_COMMAND_QUEUE_PRIORITY_NORMAL
       };
       ${x}_command_list_handle_t hCommandList;
       ${x}CommandListCreateImmediate(hContext, hDevice, &commandQueueDesc, &hCommandList);

       // Immediately submit a kernel to the device
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);
       ...

Synchronization Primitives
==========================

There are two types of synchronization primitives:

1. Fences_ - used to communicate to the host that command queue execution has completed.
2. Events_ - used as fine-grain host-to-device, device-to-host or device-to-device execution and memory dependencies.

The following are the motivations for separating the different types of synchronization primitives:

- Allows device-specific optimizations for certain types of primitives:

    + Fences may share device memory with all other fences within the same command queue.
    + Events may be implemented using pipelined operations as part of the program execution.
    + Fences are implicit, coarse-grain execution and memory barriers.
    + Events optionally cause fine-grain execution and memory barriers.

- Allows distinction on which type of primitive may be shared across devices.

Generally. Events are generic synchronization primitives that can be used across many different usage-models, including those of fences.
However, this generality comes with some cost in memory overhead and efficiency.

.. _Fences:

Fences
------

A fence is a heavyweight synchronization primitive used to communicate to the host that command list execution has completed.

- A fence is associated with a single command queue.
- A fence can only be signaled from a device's command queue (e.g. between execution of command lists) and can only be waited upon from the host.
- A fence guarantees both execution completion and memory coherency, across the device and host, prior to being signaled.
- A fence only has two states: not signaled and signaled.
- A fence doesn't implicitly reset. Signaling a signaled fence (or resetting an unsignaled fence) is valid and has no effect on the state of the fence.
- A fence can only be reset from the Host.
- A fence cannot be shared across processes.

The following pseudo-code demonstrates a sequence for creation, submission and querying of a fence:

.. parsed-literal::

       // Create fence
       ${x}_fence_desc_t fenceDesc = {
           ${X}_STRUCTURE_TYPE_FENCE_DESC,
           nullptr,
           0 // flags
       };
       ${x}_fence_handle_t hFence;
       ${x}FenceCreate(hCommandQueue, &fenceDesc, &hFence);

       // Execute a command list with a signal of the fence
       ${x}CommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, hFence);

       // Wait for fence to be signaled
       ${x}FenceHostSynchronize(hFence, UINT32_MAX);
       ${x}FenceReset(hFence);
       ...

The primary usage model for fences is to notify the Host when a command list has finished execution to allow:

- Recycling of memory and images
- Recycling of command lists
- Recycling of other synchronization primitives
- Explicit memory residency.

The following diagram illustrates fences signaled after command lists on execution:

.. image:: ../images/core_fence.png

.. _Events:

Events
------

An event is used to communicate fine-grain host-to-device, device-to-host or device-to-device dependencies have completed.

- An event can be:

    + Signaled from within a device's command list and waited upon within the same command list
    + Signaled from within a device's command list and waited upon from the host, another command queue or another device
    + Signaled from the host, and waited upon from within a device's command list.

- An event only has two states: not signaled and signaled.
- An event doesn't implicitly reset. Signaling a signaled event (or resetting an unsignaled event) is valid and has no effect on the state of the event.
- An event can be explicitly reset from the Host or device.
- An event can be appended into multiple command lists simultaneously.
- An event can be shared across devices and processes.
- An event can invoke an execution and/or memory barrier; which should be used sparingly to avoid device underutilization.
- There are no protections against events causing deadlocks, such as circular waits scenarios.

    + These problems are left to the application to avoid.

- An event intended to be signaled by the host, another command queue or another device after command list submission to a command queue may prevent subsequent forward progress within the command queue itself.

    + This can create bubbles in the pipeline or deadlock situations if not correctly scheduled.

An event pool is used for creation of individual events:

- An event pool reduces the cost of creating multiple events by allowing underlying device allocations to be shared by events with the same properties
- An event pool can be shared via :ref:`inter-process-communication`; allowing sharing blocks of events rather than sharing each individual event

The following pseudo-code demonstrates a sequence for creation and submission of an event:

.. parsed-literal::

       // Create event pool
       ${x}_event_pool_desc_t eventPoolDesc = {
           ${X}_STRUCTURE_TYPE_EVENT_POOL_DESC,
           nullptr,
           ${X}_EVENT_POOL_FLAG_HOST_VISIBLE, // all events in pool are visible to Host
           1 // count
       };
       ${x}_event_pool_handle_t hEventPool;
       ${x}EventPoolCreate(hContext, &eventPoolDesc, 0, nullptr, &hEventPool);

       ${x}_event_desc_t eventDesc = {
           ${X}_STRUCTURE_TYPE_EVENT_DESC,
           nullptr,
           0, // index
           0, // no memory/cache coherency required on signal
           ${X}_EVENT_SCOPE_FLAG_HOST  // ensure memory coherency across device and Host after event completes
       };
       ${x}_event_handle_t hEvent;
       ${x}EventCreate(hEventPool, &eventDesc, &hEvent);

       // Append a signal of an event into the command list after the kernel executes
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel1, &launchArgs, hEvent, 0, nullptr);

       // Execute the command list with the signal
       ${x}CommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

       // Wait on event to complete
       ${x}EventHostSynchronize(hEvent, 0);
       ...

The following diagram illustrates a dependency between command lists using events:

.. image:: ../images/core_event.png

Kernel Timestamp Events
~~~~~~~~~~~~~~~~~~~~~~~

A kernel timestamp event is a special type of event that records device timestamps at the start and end of the execution of kernels.

- A kernel timestamp event can only be signaled from ${x}CommandListAppendLaunchKernel et al. functions
- A kernel timestamp event result can be queried using either ${x}EventQueryKernelTimestamp or ${x}CommandListAppendQueryKernelTimestamps
- The ${x}_kernel_timestamp_result_t contains both the per-context and global timestamp values at the start and end of the kernel's execution
- Since these counters are only 32bits, the application must detect and handle counter wrapping when calculating execution time

.. parsed-literal::

       // Get timestamp frequency
       const uint64_t timestampFreq = device_properties.timerResolution;
       const uint64_t timestampMaxValue = ~(-1 << device_properties.kernelTimestampValidBits);

       // Create event pool
       ${x}_event_pool_desc_t tsEventPoolDesc = {
           ${X}_STRUCTURE_TYPE_EVENT_POOL_DESC,
           nullptr,
           ${X}_EVENT_POOL_FLAG_KERNEL_TIMESTAMP, // all events in pool are kernel timestamps
           1 // count
       };
       ${x}_event_pool_handle_t hTSEventPool;
       ${x}EventPoolCreate(hContext, &tsEventPoolDesc, 0, nullptr, &hTSEventPool);

       ${x}_event_desc_t tsEventDesc = {
           ${X}_STRUCTURE_TYPE_EVENT_DESC,
           nullptr,
           0, // index
           0, // no memory/cache coherency required on signal
           0  // no memory/cache coherency required on wait
       };
       ${x}_event_handle_t hTSEvent;
       ${x}EventCreate(hEventPool, &tsEventDesc, &hTSEvent);

       // allocate memory for results
       ${x}_device_mem_alloc_desc_t tsResultDesc = {
           ${X}_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC,
           nullptr,
           0, // flags
           0  // ordinal
       };
       ${x}_kernel_timestamp_result_t* tsResult = nullptr;
       ${x}MemAllocDevice(hContext, &tsResultDesc, sizeof(${x}_kernel_timestamp_result_t), sizeof(uint32_t), hDevice, &tsResult);

       // Append a signal of a timestamp event into the command list after the kernel executes
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel1, &launchArgs, hTSEvent, 0, nullptr);

       // Append a query of a timestamp event into the command list
       ${x}CommandListAppendQueryKernelTimestamps(hCommandList, 1, &hTSEvent, tsResult, nullptr, hEvent, 1, &hTSEvent);

       // Execute the command list with the signal
       ${x}CommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

       // Wait on event to complete
       ${x}EventHostSynchronize(hEvent, 0);

       // Calculation execution time(s)
       double globalTimeInNs = ( tsResult->global.kernelEnd >= tsResult->global.kernelStart ) 
           ? ( tsResult->global.kernelEnd - tsResult->global.kernelStart ) * (double)timestampFreq
           : (( timestampMaxValue - tsResult->global.kernelStart) + tsResult->global.kernelEnd + 1 ) * (double)timestampFreq;

       double contextTimeInNs = ( tsResult->context.kernelEnd >= tsResult->context.kernelStart )
           ? ( tsResult->context.kernelEnd - tsResult->context.kernelStart ) * (double)timestampFreq
           : (( timestampMaxValue - tsResult->context.kernelStart) + tsResult->context.kernelEnd + 1 ) * (double)timestampFreq;
       ...


Barriers
========

There are two types of barriers:

1. **Execution Barriers** - used to communicate execution dependencies between commands within a command list or across command queues, devices and/or Host.
2. **Memory Barriers** - used to communicate memory coherency dependencies between commands within a command list or across command queues, devices and/or Host.

The following pseudo-code demonstrates a sequence for submission of a brute-force execution and global memory barrier:

.. parsed-literal::

       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

       // Append a barrier into a command list to ensure hKernel1 completes before hKernel2 begins
       ${x}CommandListAppendBarrier(hCommandList, nullptr, 0, nullptr);

       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);
       ...

Execution Barriers
------------------

Commands executed on a command list are only guaranteed to start in the same order in which they are submitted; i.e. there is no implicit definition of the order of completion.

- Fences provide implicit, coarse-grain control to indicate that all previous commands must complete prior to the fence being signaled.
- Events provide explicit, fine-grain control over execution dependencies between commands; allowing more opportunities for concurrent execution and higher device utilization.

The following pseudo-code demonstrates a sequence for submission of a fine-grain execution-only dependency using events:

.. parsed-literal::

       ${x}_event_desc_t event1Desc = {
           ${X}_STRUCTURE_TYPE_EVENT_DESC,
           nullptr,
           0, // index
           0, // no memory/cache coherency required on signal
           0  // no memory/cache coherency required on wait
       };
       ${x}_event_handle_t hEvent1;
       ${x}EventCreate(hEventPool, &event1Desc, &hEvent1);

       // Ensure hKernel1 completes before signaling hEvent1
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel1, &launchArgs, hEvent1, 0, nullptr);

       // Ensure hEvent1 is signaled before starting hKernel2
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel2, &launchArgs, nullptr, 1, &hEvent1);
       ...

Memory Barriers
---------------

Commands executed on a command list are *not* guaranteed to maintain memory coherency with other commands;
i.e. there is no implicit memory or cache coherency.

- Fences provide implicit, coarse-grain control to indicate that all caches and memory are coherent across the device and Host prior to the fence being signaled.
- Events provide explicit, fine-grain control over cache and memory coherency dependencies between commands; allowing more opportunities for concurrent execution and higher device utilization.

The following pseudo-code demonstrates a sequence for submission of a fine-grain memory dependency using events:

.. parsed-literal::

       ${x}_event_desc_t event1Desc = {
           ${X}_STRUCTURE_TYPE_EVENT_DESC,
           nullptr,
           0, // index
           ${X}_EVENT_SCOPE_FLAG_DEVICE, // ensure memory coherency across device before event signaled
           0  // no memory/cache coherency required on wait
       };
       ${x}_event_handle_t hEvent1;
       ${x}EventCreate(hEventPool, &event1Desc, &hEvent1);

       // Ensure hKernel1 memory writes are fully coherent across the device before signaling hEvent1
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel1, &launchArgs, hEvent1, 0, nullptr);

       // Ensure hEvent1 is signaled before starting hKernel2
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel2, &launchArgs, nullptr, 1, &hEvent1);
       ...

Range-based Memory Barriers
---------------------------

Range-based memory barriers provide explicit control of which cachelines
require coherency.

The following pseudo-code demonstrates a sequence for submission of a range-based memory barrier:

.. parsed-literal::

       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel1, &launchArgs, nullptr, 0, nullptr);

       // Ensure memory range is fully coherent across the device after hKernel1 and before hKernel2
       ${x}CommandListAppendMemoryRangesBarrier(hCommandList, 1, &size, &ptr, nullptr, 0, nullptr);

       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel2, &launchArgs, nullptr, 0, nullptr);
       ...

Modules and Kernels
===================

There are multiple levels of constructs needed for executing kernels on the device:

1. Modules_ represent a single translation unit that consists of kernels that have been compiled together.
2. Kernels_ represent the kernel within the module that will be launched directly from a command list.

The following diagram provides a high-level overview of the major parts
of the system.

.. image:: ../images/core_module.png

.. _Modules:

Modules
-------

Modules can be created from an IL or directly from native format using ${x}ModuleCreate.

- ${x}ModuleCreate takes a format argument that specifies the input format.
- ${x}ModuleCreate performs a compilation step when format is IL.

The following pseudo-code demonstrates a sequence for creating a module from an OpenCL kernel:

.. parsed-literal::

       __kernel void image_scaling( __read_only  image2d_t src_img,
                                    __write_only image2d_t dest_img,
                                                 uint WIDTH,     // resized width
                                                 uint HEIGHT )   // resized height
       {
           int2       coor = (int2)( get_global_id(0), get_global_id(1) );
           float2 normCoor = convert_float2(coor) / (float2)( WIDTH, HEIGHT );

           float4    color = read_imagef( src_img, SMPL_PREF, normCoor );

           write_imagef( dest_img, coor, color );
       }
       ...

.. parsed-literal::

       // OpenCL C kernel has been compiled to SPIRV IL (pImageScalingIL)
       ${x}_module_desc_t moduleDesc = {
           ${X}_STRUCTURE_TYPE_MODULE_DESC,
           nullptr,
           ${X}_MODULE_FORMAT_IL_SPIRV,
           ilSize,
           pImageScalingIL,
           nullptr,
           nullptr
       };
       ${x}_module_handle_t hModule;
       ${x}ModuleCreate(hContext, hDevice, &moduleDesc, &hModule, nullptr);
       ...

Module Build Options
~~~~~~~~~~~~~~~~~~~~

Module build options can be passed with ${x}_module_desc_t as a string.

## --validate=off
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| Build Option                               | Description                                                                                                                                          | Default  | Device Support |
+============================================+======================================================================================================================================================+==========+================+
| -${x}-opt-disable                            | Disable optimizations.                                                                                                                               | Disabled | All            |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| -${x}-opt-greater-than-4GB-buffer-required   | Use 64-bit offset calculations for buffers.                                                                                                          | Disabled | GPU            |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| -${x}-opt-large-register-file                | Increase number of registers available to threads.                                                                                                   | Disabled | GPU            |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| -${x}-opt-has-buffer-offset-arg              | Extend stateless to stateful optimization to more cases with the use of additional offset (e.g. 64-bit pointer to binding table with 32-bit offset). | Disabled | GPU            |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| -g                                         | Increase number of registers available to threads.                                                                                                   | Disabled | GPU            |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+

## --validate=on

Module Specialization Constants
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SPIR-V supports specialization constants that allow certain constants to be updated to new
values during runtime execution. Each specialization constant in SPIR-V has an identifier
and default value. The ${x}ModuleCreate function allows for an array of constants and their
corresponding identifiers to be passed in to override the constants in the SPIR-V module.

.. parsed-literal::

       // Spec constant overrides for group size.
       ${x}_module_constants_t specConstants = {
           3,
           pGroupSizeIds,
           pGroupSizeValues
       };
       // OpenCL C kernel has been compiled to SPIRV IL (pImageScalingIL)
       ${x}_module_desc_t moduleDesc = {
           ${X}_STRUCTURE_TYPE_MODULE_DESC,
           nullptr,
           ${X}_MODULE_FORMAT_IL_SPIRV,
           ilSize,
           pImageScalingIL,
           nullptr,
           &specConstants
       };
       ${x}_module_handle_t hModule;
       ${x}ModuleCreate(hContext, hDevice, &moduleDesc, &hModule, nullptr);
       ...

Note: Specialization constants are only handled at module create time and therefore if
you need to change them then you'll need to compile a new module.

Module Build Log
~~~~~~~~~~~~~~~~

The ${x}ModuleCreate function can optionally generate a build log object ${x}_module_build_log_handle_t.

.. parsed-literal::

       ...
       ${x}_module_build_log_handle_t buildlog;
       ${x}_result_t result = ${x}ModuleCreate(hContext, hDevice, &desc, &module, &buildlog);

       // Only save build logs for module creation errors.
       if (result != ${X}_RESULT_SUCCESS)
       {
           size_t szLog = 0;
           ${x}ModuleBuildLogGetString(buildlog, &szLog, nullptr);
           
           char_t* strLog = allocate(szLog);
           ${x}ModuleBuildLogGetString(buildlog, &szLog, strLog);

           // Save log to disk.
           ...

           free(strLog);
       }

       ${x}ModuleBuildLogDestroy(buildlog);

Module Caching with Native Binaries
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Disk caching of modules is not supported by the driver. If a disk cache for modules is desired, then it is the
responsibility of the application to implement this using ${x}ModuleGetNativeBinary.

.. parsed-literal::

       ...
       // compute hash for pIL and check cache.
       ...

       if (cacheUpdateNeeded)
       {
           size_t szBinary = 0;
           ${x}ModuleGetNativeBinary(hModule, &szBinary, nullptr);

           uint8_t* pBinary = allocate(szBinary);
           ${x}ModuleGetNativeBinary(hModule, &szBinary, pBinary);

           // cache pBinary for corresponding IL
           ...

           free(pBinary);
       }

Also, note that the native binary will retain all debug information that is associated with the module. This allows debug
capabilities for modules that are created from native binaries.

Built-in Kernels
~~~~~~~~~~~~~~~~

Built-in kernels are not supported but can be implemented by an upper level runtime or library using the native binary
interface.

.. _Kernels:

Kernels
-------

A Kernel is a reference to a kernel within a module and it supports both explicit and implicit kernel
arguments along with data needed for launch.

The following pseudo-code demonstrates a sequence for creating a kernel from a module:

.. parsed-literal::

       ${x}_kernel_desc_t kernelDesc = {
           ${X}_STRUCTURE_TYPE_KERNEL_DESC,
           nullptr,
           0, // flags
           "image_scaling"
       };
       ${x}_kernel_handle_t hKernel;
       ${x}KernelCreate(hModule, &kernelDesc, &hKernel);
       ...

Kernel Attributes and Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Use ${x}KernelSetAttribute to set attributes for a Kernel.

.. parsed-literal::

    // Kernel performs indirect device access.
    bool_t isIndirect = true;
    ${x}KernelSetAttribute(hKernel, ${X}_KERNEL_ATTRIBUTE_INDIRECT_DEVICE_ACCESS, sizeof(bool_t), &isIndirect);
    ...

Use ${x}KernelSetAttribute to get attributes for a Kernel.

.. parsed-literal::

    // Does kernel perform indirect device access.
    ${x}KernelGetAttribute(hKernel, ${X}_KERNEL_ATTRIBUTE_INDIRECT_DEVICE_ACCESS, sizeof(bool_t), &isIndirect);
    ...
    
    uint32_t strSize = 0; // Size of string + null terminator
    ${x}KernelGetAttribute(hKernel, ${X}_KERNEL_ATTRIBUTE_SOURCE_ATTRIBUTE, &strSize, nullptr );
    char* pAttributes = allocate(strSize);
    ${x}KernelGetAttribute(hKernel, ${X}_KERNEL_ATTRIBUTE_SOURCE_ATTRIBUTE, &strSize, pAttributes );
    ...

See ${x}_kernel_attribute_t for more information on the "set" and "get" attributes.

Use ${x}KernelGetProperties to query invariant properties from a Kernel object.

.. parsed-literal::

    ...
    ${x}_kernel_properties_t kernelProperties;

    // 
    ${x}KernelGetProperties(hKernel, &kernelProperties);
    ...

See ${x}_kernel_properties_t for more information for kernel properties.

.. _execution-1:

Execution
---------

Kernel Group Size
~~~~~~~~~~~~~~~~~

The group size for a kernel can be set using ${x}KernelSetGroupSize. If a group size is not
set prior to appending a kernel into a command list then a default will be chosen.
The group size can be updated over a series of append operations. The driver will copy the
group size information when appending the kernel into the command list.

.. parsed-literal::

       ${x}KernelSetGroupSize(hKernel, groupSizeX, groupSizeY, 1);

       ...

The API supports a query for suggested group size when providing the global size. This function ignores the
group size that was set on the kernel using ${x}KernelSetGroupSize.

.. parsed-literal::

       // Find suggested group size for processing image.
       uint32_t groupSizeX;
       uint32_t groupSizeY;
       ${x}KernelSuggestGroupSize(hKernel, imageWidth, imageHeight, 1, &groupSizeX, &groupSizeY, nullptr);

       ${x}KernelSetGroupSize(hKernel, groupSizeX, groupSizeY, 1);

       ...

Kernel Arguments
~~~~~~~~~~~~~~~~

Kernel arguments represent only the explicit kernel arguments that are within brackets e.g. func(arg1, arg2, ...).

- Use ${x}KernelSetArgumentValue to setup arguments for a kernel launch.
- The ${x}CommandListAppendLaunchKernel et al. functions will make a copy of the kernel arguments to send to the device.
- Kernel arguments can be updated at any time and used across multiple append calls.

The following pseudo-code demonstrates a sequence for setting kernel arguments and launching the kernel:

.. parsed-literal::

       // Bind arguments
       ${x}KernelSetArgumentValue(hKernel, 0, sizeof(${x}_image_handle_t), &src_image);
       ${x}KernelSetArgumentValue(hKernel, 1, sizeof(${x}_image_handle_t), &dest_image);
       ${x}KernelSetArgumentValue(hKernel, 2, sizeof(uint32_t), &width);
       ${x}KernelSetArgumentValue(hKernel, 3, sizeof(uint32_t), &height);

       ${x}_group_count_t launchArgs = { numGroupsX, numGroupsY, 1 };

       // Append launch kernel
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

       // Update image pointers to copy and scale next image.
       ${x}KernelSetArgumentValue(hKernel, 0, sizeof(${x}_image_handle_t), &src2_image);
       ${x}KernelSetArgumentValue(hKernel, 1, sizeof(${x}_image_handle_t), &dest2_image);

       // Append launch kernel
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

       ...

Kernel Launch
~~~~~~~~~~~~~

In order to launch a kernel on the device an application must call one of the AppendLaunchKernel-style functions for
a command list. The most basic version of these is ${x}CommandListAppendLaunchKernel which takes a
command list, kernel handle, launch arguments, and an optional synchronization event used to signal completion.
The launch arguments contain thread group dimensions.

.. parsed-literal::

       // compute number of groups to launch based on image size and group size.
       uint32_t numGroupsX = imageWidth / groupSizeX;
       uint32_t numGroupsY = imageHeight / groupSizeY;

       ${x}_group_count_t launchArgs = { numGroupsX, numGroupsY, 1 };

       // Append launch kernel
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

The function ${x}CommandListAppendLaunchKernelIndirect allows the launch parameters to be supplied indirectly in a
buffer that the device reads instead of the command itself. This allows for the previous operations on the
device to generate the parameters.

.. parsed-literal::

       ${x}_group_count_t* pIndirectArgs;
       
       ...
       ${x}MemAllocDevice(hContext, &desc, sizeof(${x}_group_count_t), sizeof(uint32_t), hDevice, &pIndirectArgs);

       // Append launch kernel - indirect
       ${x}CommandListAppendLaunchKernelIndirect(hCommandList, hKernel, &pIndirectArgs, nullptr, 0, nullptr);

Cooperative Kernels
~~~~~~~~~~~~~~~~~~~

Cooperative kernels allow sharing of data and synchronization across all launched groups in a safe manner. To support this
there is a ${x}CommandListAppendLaunchCooperativeKernel that allows launching groups that can cooperate with each other.
The command list must be submitted to a logical command queue that was created with an ordinal of a physical command queue
that has the ${X}_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COOPERATIVE_KERNELS flags set .
Finally, there is a ${x}KernelSuggestMaxCooperativeGroupCount function that suggests a maximum group count size that
the device supports.

Sampler
-------

The API supports Sampler objects that represent state needed for sampling images from within
kernels. The ${x}SamplerCreate function takes a sampler descriptor (${x}_sampler_desc_t):

+-----------------------------------+-----------------------------------------+
| Sampler Field                     | Description                             |
+===================================+=========================================+
| Address Mode                      | Determines how out-of-bounds            |
|                                   | accesses are handled. See               |
|                                   | ${x}_sampler_address_mode_t.      |
+-----------------------------------+-----------------------------------------+
| Filter Mode                       | Specifies which filtering mode to       |
|                                   | use. See                                |
|                                   | ${x}_sampler_filter_mode_t.       |
+-----------------------------------+-----------------------------------------+
| Normalized                        | Specifies whether coordinates for       |
|                                   | addressing image are normalized         |
|                                   | [0,1] or not.                           |
+-----------------------------------+-----------------------------------------+

The following pseudo-code demonstrates the creation of a sampler object and passing it as a kernel argument:

.. parsed-literal::

       // Setup sampler for linear filtering and clamp out of bounds accesses to edge.
       ${x}_sampler_desc_t desc = {
           ${X}_STRUCTURE_TYPE_SAMPLER_DESC,
           nullptr,
           ${X}_SAMPLER_ADDRESS_MODE_CLAMP,
           ${X}_SAMPLER_FILTER_MODE_LINEAR,
           false
           };
       ${x}_sampler_handle_t sampler;
       ${x}SamplerCreate(hContext, hDevice, &desc, &sampler);
       ...
       
       // The sampler can be passed as a kernel argument.
       ${x}KernelSetArgumentValue(hKernel, 0, sizeof(${x}_sampler_handle_t), &sampler);

       // Append launch kernel
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

Advanced
========

Environment Variables
---------------------

The following table documents the supported knobs for overriding default functional behavior.

+-----------------+-------------------------------------+------------+-----------------------------------------------------------------------------------+
| Category        | Name                                | Values     | Description                                                                       |
+=================+=====================================+============+===================================================================================+
| Device          | ${X}_AFFINITY_MASK                    | list       | Forces driver to only report devices (and sub-devices) as specified by values     |
+                 +-------------------------------------+------------+-----------------------------------------------------------------------------------+
|                 | ${X}_ENABLE_PCI_ID_DEVICE_ORDER       | {**0**, 1} | Forces driver to report devices from lowest to highest PCI bus ID                 |
+-----------------+-------------------------------------+------------+-----------------------------------------------------------------------------------+
| Memory          | ${X}_SHARED_FORCE_DEVICE_ALLOC        | {**0**, 1} | Forces all shared allocations into device memory                                  |
+-----------------+-------------------------------------+------------+-----------------------------------------------------------------------------------+

Affinity Mask
~~~~~~~~~~~~~

The affinity mask allows an application or tool to restrict which devices, and sub-devices, are visible to 3rd-party libraries or applications in another process, respectively. 
The affinity mask affects the number of handles returned from ${x}DeviceGet and ${x}DeviceGetSubDevices.
The affinity mask is specified via an environment variable as a comma-seperated list of device and/or subdevice ordinals.
The values are specific to system configuration; e.g., the number of devices and the number of sub-devices for each device.
The values are specific to the order in which devices are reported by the driver; i.e., the first device maps to ordinal 0, the second device to ordinal 1, and so forth.
If the affinity mask is not set, then all devices and sub-devices are reported; as is the default behavior.

The order of the devices reported by the ${x}DeviceGet is implementation-specific and not affected by the order of devices in the affinity mask.
The order of the devices reported by the ${x}DeviceGet can be forced to be consistent by setting the ${X}_ENABLE_PCI_ID_DEVICE_ORDER environment variable.

The following examples demonstrate proper usage for a system configuration of two devices, each with four sub-devices:

- `0, 1`: all devices and sub-devices are reported (same as default)
- `0`: only device 0 is reported;with all its sub-devices
- `1`: only device 1 is reported as device 0; with all its sub-devices
- `0.0`: only device 0, sub-device 0 is reported as device 0
- `1.1, 1.2`: only device 1 is reported as device 0; with its sub-devices 1 and 2 reported as sub-devices 0 and 1, respectively
- `0.2, 1.3, 1.0, 0.3`: both device 0 and 1 are reported; device 0 reports sub-devices 2 and 3 as sub-devices 0 and 1, respectively; device 1 reports sub-devices 0 and 3 as sub-devices 0 and 1, respectively; the order is unchanged.

Sub-Device Support
------------------

The API allows support for sub-devices which can enable finer-grained control of scheduling and memory allocation to a sub-partition of the device.
There are functions to query and obtain sub-devices, but outside of these functions there are no distinctions between sub-devices and devices.
Sub-devices are not required to represent unique partitions of a device; i.e. multiple sub-devices may share the same physical hardware.
Furthermore, a sub-device can be partitioned into more sub-devices; e.g. down to a single slice.

Use ${x}DeviceGetSubDevices to confirm sub-devices are supported and to obtain a sub-device handle.
There are additional device properties in ${x}_device_properties_t for sub-devices.
These can be used to confirm a device is a sub-device and to query the sub-device id.
This may be used by libraries to determine if an input device handle represents a device or sub-device.

A driver is required to make device memory allocations on the parent device visible to its sub-devices.
However, when using a sub-device handle, the driver will attempt to place any device memory allocations in the local memory that is attached to the sub-device.
These allocations are only visible to the sub-device, its sub-devices, and so forth.
If the API call returns ${X}_RESULT_ERROR_OUT_OF_DEVICE_MEMORY, then the application may attempt to retry using the parent device.

When creating command queues for a sub-device,
the application must determine the ordinal from calling ${x}DeviceGetCommandQueueGroupProperties using the sub-device handle.
See ${x}_command_queue_desc_t for more details.

A 16-byte unique device identifier (uuid) can be obtained for a device
or sub-device using ${x}DeviceGetProperties.

.. parsed-literal::

       // Query for all sub-devices of the device
       uint32_t subdeviceCount = 0;
       ${x}DeviceGetSubDevices(hDevice, &subdeviceCount, nullptr);

       ${x}_device_handle_t* allSubDevices = allocate(subdeviceCount * sizeof(${x}_device_handle_t));
       ${x}DeviceGetSubDevices(hDevice, &subdeviceCount, &allSubDevices);

       // Desire is to allocate and dispatch work to sub-device 2.
       assert(subdeviceCount >= 3);
       ${x}_device_handle_t hSubdevice = allSubDevices[2];

       // Query sub-device properties.
       ${x}_device_properties_t subdeviceProps;
       ${x}DeviceGetProperties(hSubdevice, &subdeviceProps);

       assert(subdeviceProps.flags & ${X}_DEVICE_PROPERTY_FLAG_SUBDEVICE); // Ensure that we have a handle to a sub-device.
       assert(subdeviceProps.subdeviceId == 2);    // Ensure that we have a handle to the sub-device we asked for.

       void* pMemForSubDevice2;
       ${x}MemAllocDevice(hContext, &desc, memSize, sizeof(uint32_t), hSubdevice, &pMemForSubDevice2);
       ...

Device Residency
----------------

For devices that do not support page-faults, the driver must ensure that all pages that will be accessed by the kernel are resident before program execution. 
This can be determined by checking ${x}_device_properties_t.flags for ${X}_DEVICE_PROPERTY_FLAG_ONDEMANDPAGING.

In most cases, the driver implicitly handles residency of allocations for device access.
This can be done by inspecting API parameters, including kernel arguments.
However, in cases where the devices does **not** support page-faulting *and* the driver is incapable of determining whether an allocation will be accessed by the device,
such as multiple levels of indirection, there are two methods available:

1. The application may set the ${X}_KERNEL_FLAG_FORCE_RESIDENCY flag during program creation to force all device allocations to be resident during execution.

    + The application should specify which allocations will be indirectly accessed, using ${x}KernelSetAttribute and the following, to optimize which allocations are made resident.
           
        * ${X}_KERNEL_ATTRIBUTE_INDIRECT_HOST_ACCESS
        * ${X}_KERNEL_ATTRIBUTE_INDIRECT_DEVICE_ACCESS
        * ${X}_KERNEL_ATTRIBUTE_INDIRECT_SHARED_ACCESS

    + If the driver is unable to make all allocations resident, then the call to ${x}CommandQueueExecuteCommandLists will return ${X}_RESULT_ERROR_OUT_OF_DEVICE_MEMORY

2. Explcit ${x}ContextMakeMemoryResident APIs are included for the application to dynamically change residency as needed. (Windows-only)

    + If the application over-commits device memory, then a call to ${x}ContextMakeMemoryResident will return ${X}_RESULT_ERROR_OUT_OF_DEVICE_MEMORY

If the application does not properly manage residency for these cases then the device may experience unrecoverable page-faults.

The following pseudo-code demonstrates a sequence for using coarse-grain residency control for indirect arguments:

.. parsed-literal::

       struct node {
           node* next;
       };
       node* begin = nullptr;
       ${x}MemAllocHost(hContext, &desc, sizeof(node), 1, &begin);
       ${x}MemAllocHost(hContext, &desc, sizeof(node), 1, &begin->next);
       ${x}MemAllocHost(hContext, &desc, sizeof(node), 1, &begin->next->next);

       // 'begin' is passed as kernel argument and appended into command list
       bool hasIndirectHostAccess = true;
       ${x}KernelSetAttribute(hFuncArgs, ${X}_KERNEL_ATTRIBUTE_INDIRECT_HOST_ACCESS, sizeof(bool), &hasIndirectHostAccess);
       ${x}KernelSetArgumentValue(hKernel, 0, sizeof(node*), &begin);
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

       ...

       ${x}CommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, nullptr);
       ...

The following pseudo-code demonstrates a sequence for using fine-grain residency control for indirect arguments:

.. parsed-literal::

       struct node {
           node* next;
       };
       node* begin = nullptr;
       ${x}MemAllocHost(hContext, &desc, sizeof(node), 1, &begin);
       ${x}MemAllocHost(hContext, &desc, sizeof(node), 1, &begin->next);
       ${x}MemAllocHost(hContext, &desc, sizeof(node), 1, &begin->next->next);

       // 'begin' is passed as kernel argument and appended into command list
       ${x}KernelSetArgumentValue(hKernel, 0, sizeof(node*), &begin);
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);
       ...

       // Make indirect allocations resident before enqueuing
       ${x}ContextMakeMemoryResident(hContext, hDevice, begin->next, sizeof(node));
       ${x}ContextMakeMemoryResident(hContext, hDevice, begin->next->next, sizeof(node));

       ${x}CommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, hFence);

       // wait until complete
       ${x}FenceHostSynchronize(hFence, UINT32_MAX);

       // Finally, evict to free device resources
       ${x}ContextEvictMemory(hContext, hDevice, begin->next, sizeof(node));
       ${x}ContextEvictMemory(hContext, hDevice, begin->next->next, sizeof(node));
       ...

Interoperability with Other APIs
--------------------------------
Level-Zero includes general-purpose interoperability mechanisms for
memory allocations (both images and device memory) and modules.

Memory allocations may be shared between Level-Zero and other APIs via
:ref:`external-memory`.
Level-Zero supports exporting memory allocations for use in other APIs
and importing memory allocations from other APIs.

Modules may be shared between Level-Zero and other APIs via native
format binaries, see ${x}ModuleGetNativeBinary and ${X}_MODULE_FORMAT_NATIVE.

The following pseudo-code demonstrates interoperability with OpenCL *from* a OpenCL cl_program *to* a Level-Zero Kernel:

.. parsed-literal::

        void *clDeviceBinary;
        size_t clDeviceBinarySize;
        clGetProgramInfo(cl_program, CL_PROGRAM_BINARIES, clDeviceBinary, &clDeviceBinarySize);

        ${x}_module_desc_t desc = {
            ${X}_MODULE_FORMAT_NATIVE,
            clDeviceBinarySize,
            clDeviceBinary
        };
        ${x}ModuleCreate(hContext, hDevice, &desc, &hModule, nullptr);
        ${x}KernelCreate(hModule, nullptr, hKernel); // same Kernel as OpenCL in Level-Zero


.. _inter-process-communication:

Inter-Process Communication
---------------------------

The API allows sharing of memory objects across different device
processes. Since each process has its own virtual address space, there
is no guarantee that the same virtual address will be available when the
memory object is shared in new process. There are a set of APIs that
makes it easier to share the memory objects with ease.

There are two types of Inter-Process Communication (IPC) APIs for using
Level-Zero allocations across processes:

1. :ref:`Memory<memory-1>`
2. :ref:`Events<events-1>`

.. _memory-1:

Memory
~~~~~~

The following code examples demonstrate how to use the memory IPC APIs:

1. First, the allocation is made, packaged, and sent on the sending
   process:

.. parsed-literal::

       void* dptr = nullptr;
       ${x}MemAllocDevice(hContext, &desc, size, alignment, hDevice, &dptr);

       ${x}_ipc_mem_handle_t hIPC;
       ${x}MemGetIpcHandle(hContext, dptr, &hIPC);

       // Method of sending to receiving process is not defined by Level-Zero:
       send_to_receiving_process(hIPC);

2. Next, the allocation is received and un-packaged on the receiving
   process:

.. parsed-literal::

       // Method of receiving from sending process is not defined by Level-Zero:
       ${x}_ipc_mem_handle_t hIPC;
       hIPC = receive_from_sending_process();

       void* dptr = nullptr;
       ${x}MemOpenIpcHandle(hContext, hDevice, hIPC, 0, &dptr);

3. Each process may now refer to the same device memory allocation via its ``dptr``.
   Note, there is no guaranteed address equivalence for the values of ``dptr`` in each process.

4. To cleanup, first close the handle in the receiving process:

.. parsed-literal::

       ${x}MemCloseIpcHandle(hContext, dptr);

5. Finally, free the device pointer in the sending process:

.. parsed-literal::

       ${x}MemFree(hContext, dptr);

.. _events-1:

Events
~~~~~~

The following code examples demonstrate how to use the event IPC APIs:

1. First, the event pool is created, packaged, and sent on the sending process:

.. parsed-literal::

       // create event pool
       ${x}_event_pool_desc_t eventPoolDesc = {
           ${X}_STRUCTURE_TYPE_EVENT_POOL_DESC,
           nullptr,
           ${X}_EVENT_POOL_FLAG_IPC | ${X}_EVENT_POOL_FLAG_HOST_VISIBLE,
           10 // count
       };
       ${x}_event_pool_handle_t hEventPool;
       ${x}EventPoolCreate(hContext, &eventPoolDesc, 1, &hDevice, &hEventPool);
    
       // get IPC handle and send to another process
       ${x}_ipc_event_pool_handle_t hIpcEvent;
       ${x}EventPoolGetIpcHandle(hEventPool, &hIpcEventPool);
       send_to_receiving_process(hIpcEventPool);

2. Next, the event pool is received and un-packaged on the receiving process:

.. parsed-literal::

       // get IPC handle from other process
       ${x}_ipc_event_pool_handle_t hIpcEventPool;
       receive_from_sending_process(&hIpcEventPool);

       // open event pool
       ${x}_event_pool_handle_t hEventPool;
       ${x}EventPoolOpenIpcHandle(hContext, hIpcEventPool, &hEventPool);

3. Each process may now refer to the same device event allocation via its handle:

   a. Receiving process creates event at location

.. parsed-literal::

       ${x}_event_handle_t hEvent;
       ${x}_event_desc_t eventDesc = {
           ${X}_STRUCTURE_TYPE_EVENT_DESC,
           nullptr,
           5, // index
           0, // no memory/cache coherency required on signal
           ${X}_EVENT_SCOPE_FLAG_HOST, // ensure memory coherency across device and Host after event signaled
       };
       ${x}EventCreate(hEventPool, &eventDesc, &hEvent);

       // submit kernel and signal event when complete
       ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &args, hEvent, 0, nullptr);
       ${x}CommandListClose(hCommandList);
       ${x}CommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

   b. Sending process creates event at same location

.. parsed-literal::

       ${x}_event_handle_t hEvent;
       ${x}_event_desc_t eventDesc = {
           ${X}_STRUCTURE_TYPE_EVENT_DESC,
           nullptr,
           5,
           0, // no memory/cache coherency required on signal
           ${X}_EVENT_SCOPE_FLAG_HOST, // ensure memory coherency across device and Host after event signaled
       };
       ${x}EventCreate(hEventPool, &eventDesc, &hEvent);

       ${x}EventHostSynchronize(hEvent, UINT32_MAX);

   Note, there is no guaranteed address equivalence for the values of ``hEvent`` in each process.

4. To cleanup, first close the pool handle in the receiving process:

.. parsed-literal::

       ${x}EventDestroy(hEvent);
       ${x}EventPoolCloseIpcHandle(&hEventPool);

5. Finally, free the event pool handle in the sending process:

.. parsed-literal::

       ${x}EventDestroy(hEvent);
       ${x}EventPoolDestroy(hEventPool);

Peer-to-Peer Access and Queries
-------------------------------

Peer to Peer API's provide capabilities to marshall data across Host to
Device, Device to Host and Device to Device. The data marshalling API
can be scheduled as asynchronous operations or can be synchronized with
kernel execution through command queues. Data coherency is maintained by
the driver without any explicit involvement from the application.

Devices may be linked together within a node by a scale-up fabric and depending on the configuration,
the fabric can support atomics, compute kernel remote access, and data copies.

The following Peer-to-Peer functionalities are provided through the API:

- Check for existence of peer-to-peer fabric between two devices.

       + ${x}DeviceCanAccessPeer

- Query remote memory access and atomic capabilities for peer-to-peer

       + ${x}DeviceGetP2PProperties

- Copy data between devices over peer-to-peer fabric.

       + ${x}CommandListAppendMemoryCopy

.. |Device| image:: ../images/core_device.png?raw=true
.. |Queue| image:: ../images/core_queue.png?raw=true
.. |Graph| image:: ../images/core_sync.png?raw=true
.. |Fence| image:: ../images/core_fence.png?raw=true
.. |Event| image:: ../images/core_event.png?raw=true
.. |Module| image:: ../images/core_module.png?raw=true
