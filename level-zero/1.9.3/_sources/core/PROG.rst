




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

- The application may query the number of Level-Zero drivers installed on the system, and their respective handles, using :ref:`zeDriverGet`\.
- More than one driver may be available in the system. For example, one driver may support two GPUs from one vendor, another driver supports a GPU from a different vendor, and finally a different driver may support an FPGA.
- Driver objects are read-only, global constructs. i.e. Multiple calls to :ref:`zeDriverGet` will return identical driver handles.
- A driver handle is primarily used during device discovery and during creation and management of contexts.

Device
------

A device object represents a physical device in the system that supports Level-Zero.

- The application may query the number devices supported by a driver, and their respective handles, using :ref:`zeDeviceGet`\.
- Device objects are read-only, global constructs. i.e. Multiple calls to :ref:`zeDeviceGet` will return identical device handles.
- A device handle is primarily used during creation and management of resources that are specific to a device.
- The application is responsible for sharing memory and explicit submission and synchronization across multiple devices.
- Device may expose sub-devices that allow finer-grained control of physical or logical partitions of a device.

The following diagram illustrates the relationship between the driver, device and other objects described in this document.

.. image:: ../images/core_device.png

Level Zero device model hierarchy is composed of **Root Devices** and **Sub-Devices**: A root-device may contain two or more sub-devices and a sub-device shall belong to a single root-device.
A root-device may not contain a single sub-device, as that would be the same root-device. A root device may also be a device with no sub-devices.

Sub-devices belonging to a root-device may be queried using :ref:`zeDeviceGetSubDevices`\. The root-device of a sub-device may be queried using :ref:`zeDeviceGetRootDevice`\.
The definition of what a root-device and a sub-device is for a specific device is implementation specific.

Initialization and Discovery
----------------------------

The Level-Zero API must be initialized by calling :ref:`zeInit` before calling any other API function.
This function will load all Level-Zero driver(s) in the system into memory for the current process, for use by all Host threads.
Simultaneous calls to :ref:`zeInit` are thread-safe and only one instance of each driver will be loaded.

The following pseudo-code demonstrates a basic initialization and device discovery sequence:

.. parsed-literal::

       // Initialize the driver
       :ref:`zeInit`\(0);

       // Discover all the driver instances
       uint32_t driverCount = 0;
       :ref:`zeDriverGet`\(&driverCount, nullptr);

       ze_driver_handle_t* allDrivers = allocate(driverCount * sizeof(ze_driver_handle_t));
       :ref:`zeDriverGet`\(&driverCount, allDrivers);

       // Find a driver instance with a GPU device
       ze_driver_handle_t hDriver = nullptr;
       ze_device_handle_t hDevice = nullptr;
       for(i = 0; i < driverCount; ++i) {
           uint32_t deviceCount = 0;
           :ref:`zeDeviceGet`\(allDrivers[i], &deviceCount, nullptr);

           ze_device_handle_t* allDevices = allocate(deviceCount * sizeof(ze_device_handle_t));
           :ref:`zeDeviceGet`\(allDrivers[i], &deviceCount, allDevices);

           for(d = 0; d < deviceCount; ++d) {
               :ref:`ze-device-properties-t` device_properties {};
               device_properties.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>`\;
               :ref:`zeDeviceGetProperties`\(allDevices[d], &device_properties);

               if(:ref:`ZE_DEVICE_TYPE_GPU <ze-device-type-t>` == device_properties.type) {
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
        :ref:`ze-context-desc-t` ctxtDesc = {
           :ref:`ZE_STRUCTURE_TYPE_CONTEXT_DESC <ze-structure-type-t>`\,
           nullptr,
           0
        };
        :ref:`zeContextCreate`\(hDriver, &ctxtDesc, &hContext);


An application may optionally create multiple contexts using :ref:`zeContextCreate`\.

- The primary usage-model for multiple contexts is isolation of memory and objects for multiple libraries within the same process.
- The same context may be used simultaneously on multiple Host threads.

The following pseudo-code demonstrates a basic context creation and activation sequence:

.. parsed-literal::

        // Create context(s)
        :ref:`zeContextCreate`\(hDriver, &ctxtDesc, &hContextA);
        :ref:`zeContextCreate`\(hDriver, &ctxtDesc, &hContextB);

        :ref:`zeMemAllocHost`\(hContextA, &desc, 80, 0, &ptrA);
        :ref:`zeMemAllocHost`\(hContextB, &desc, 88, 0, &ptrB);

        memcpy(ptrA, ptrB, 0xe); // ok
        :ref:`zeMemGetAllocProperties`\(hContextA, ptrB, &props, &hDevice); // illegal: Context A has no knowledge of ptrB


If a device was hung or reset, then the context is no longer valid and all APIs will return :ref:`ZE_RESULT_ERROR_DEVICE_LOST <ze-result-t>` when any object associated with that context is used.
All pointers to memory allocations and handles to objects (including other contexts) created on the context will be invalid and should no longer be used.
An application can use :ref:`zeContextGetStatus` at any time to check the status of a context.

In order to recover, the context must be destroyed using :ref:`zeContextDestroy`\.
After the device is reset, the application can create a new context and continue operation.
An application must call :ref:`zeDeviceGetStatus` to confirm the device has been reset and update the OS handle attached to the device handle.
Otherwise, even after the device has been reset, the call to :ref:`zeContextCreate` will fail.

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

At a minimum, drivers will assign unique physical pages for each device and shared memory allocation.
However, it is undefined behavior for an application to access memory outside of the allocation size requested.
The actual page size used for an allocation can be queried from :ref:`ze-memory-allocation-properties-t`\.pageSize using :ref:`zeMemGetAllocProperties`\.
Applications should implement usage-specific allocators from device memory pools (e.g., small and/or fixed-sized allocations, lock-free, etc.).

Furthermore, drivers may *oversubscribe* some **shared** allocations.
When and how such oversubscription occurs, including which allocations are evicted when the working set changes, are considered implementation details.

Access Capabilities
~~~~~~~~~~~~~~~~~~~

Devices may support different access capabilities for each type of allocation. Supported capabilities are:

1. **Host Allocations**: Assume a buffer allocated on the host via :ref:`zeMemAllocHost` that is accessed from device hDevice:

    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_RW <ze-memory-access-cap-flags-t>`\: Buffer can be accessed (read from as well as written to) from hDevice as well as from the host.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_ATOMIC <ze-memory-access-cap-flags-t>`\: Buffer can be atomically accessed from hDevice. Atomic operations may include relaxed consistency read-modify-write atomics and atomic operations that enforce memory consistency for non-atomic operations.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT <ze-memory-access-cap-flags-t>`\: Buffer can be accessed from hDevice concurrently with another device that also supports concurrent access as well as with the host itself. Concurrent access is at the granularity of the whole allocation. This capability makes no guarantees about coherency or memory consistency. Undefined behavior occurs if concurrent accesses are made to an allocation from devices that do not support concurrent access. Devices that support concurrent access but do not support concurrent atomic access must write to unique non-overlapping memory locations to avoid data races and hence undefined behavior.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC <ze-memory-access-cap-flags-t>`\: Buffer can be atomically accessed from hDevice concurrently with another device that also supports concurrent atomic access as well as with the host itself. Concurrent atomic access is at the granularity of the whole allocation. Memory consistency can be enforced between the host & devices that support concurrent atomic access using atomic operations. Undefined behavior occurs if concurrent atomic accesses are made to an allocation from devices that do not support concurrent atomic access.

2. **Device Allocations**: Assume a buffer allocated on device hDevice via :ref:`zeMemAllocDevice`\:

    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_RW <ze-memory-access-cap-flags-t>`\: Buffer can be accessed (read from as well as written to) from hDevice.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_ATOMIC <ze-memory-access-cap-flags-t>`\: Buffer can be atomically accessed from hDevice. Atomic operations may include relaxed consistency read-modify-write atomics and atomic operations that enforce memory consistency for non-atomic operations.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT <ze-memory-access-cap-flags-t>`\: Buffer can be accessed from hDevice concurrently with another device that also supports concurrent access. By symmetry, the buffer could be located on either device and be accessed concurrently from both devices. Concurrent access is at the granularity of the whole allocation. This capability makes no guarantees about coherency or memory consistency. Undefined behavior occurs if concurrent accesses are made to an allocation from devices that do not support concurrent access. Devices that support concurrent access but do not support concurrent atomic access must write to unique non-overlapping memory locations to avoid data races and hence undefined behavior. A device can concurrently access a buffer on another device if both devices support concurrent access and both devices also support peer-to-peer access. If one device does not permit concurrent access, but peer-to-peer access is permitted, then the devices support peer-to-peer access but not concurrently to the same buffer.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC <ze-memory-access-cap-flags-t>`\: Buffer can be atomically accessed from hDevice concurrently with another device that also supports concurrent atomic access. By symmetry, the buffer could be located on either device and be atomically accessed concurrently from both devices. Concurrent atomic access is at the granularity of the whole allocation. Memory consistency can be enforced between devices that support concurrent atomic access using atomic operations. Undefined behavior occurs if concurrent atomic accesses are made to an allocation from devices that do not support concurrent atomic access. A device can concurrently perform atomic access to a device buffer on another device if both devices support concurrent atomic access and both devices also support peer-to-peer atomic access. If one device does not permit concurrent atomic access, but peer-to-peer atomic access is permitted, then the devices support peer-to-peer atomic access but not concurrently to the same buffer.

3. **Shared Single Device Allocations**: Assume a shared allocation across the host & device hDevice created via :ref:`zeMemAllocShared`

    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_RW <ze-memory-access-cap-flags-t>`\: Buffer can be accessed (read from as well as written to) from hDevice as well as from the host.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_ATOMIC <ze-memory-access-cap-flags-t>`\: Buffer can be atomically accessed from hDevice as well as from the host. Atomic operations may include relaxed consistency read-modify-write atomics and atomic operations that enforce memory consistency for non-atomic operations.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT <ze-memory-access-cap-flags-t>`\: Buffer can be accessed from hDevice concurrently with the host. Concurrent access is at the granularity of the whole allocation. This capability makes no guarantees about coherency or memory consistency. Undefined behavior occurs if concurrent accesses are made to the allocation from the host and from hDevice if it does not support concurrent access. A devices that supports concurrent access but does not support concurrent atomic access must write to unique non-overlapping (with the host) memory locations to avoid data races and hence undefined behavior.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC <ze-memory-access-cap-flags-t>`\: Buffer can be atomically accessed from hDevice concurrently with the host. Concurrent atomic access is at the granularity of the whole allocation. Memory consistency can be enforced between devices that support concurrent atomic access using atomic operations. Undefined behavior occurs if concurrent atomic accesses are made to the allocation from the host & hDevice if it does not support concurrent atomic access.

4. **Shared Cross Device Allocations**: Assume a shared allocation across the host & the set of devices that support cross-device shared access capabilities created via :ref:`zeMemAllocShared` that is accessed from device hDevice:

    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_RW <ze-memory-access-cap-flags-t>`\: Buffer can be accessed (read from as well as written to) from hDevice as well as from the host.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_ATOMIC <ze-memory-access-cap-flags-t>`\: Buffer can be atomically accessed from hDevice as well as from the host. Atomic operations may include relaxed consistency read-modify-write atomics and atomic operations that enforce memory consistency for non-atomic operations.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT <ze-memory-access-cap-flags-t>`\: Buffer can be accessed from hDevice concurrently with another device that also supports concurrent access and from the host. Concurrent access is at the granularity of the whole allocation. This capability makes no guarantees about coherency or memory consistency. Undefined behavior occurs if concurrent accesses are made to an allocation from devices that do not support concurrent access. Devices that support concurrent access but do not support concurrent atomic access must write to unique non-overlapping memory locations to avoid data races and hence undefined behavior.
    + :ref:`ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC <ze-memory-access-cap-flags-t>`\: Buffer can be atomically accessed from hDevice concurrently with another device that also supports concurrent atomic access and from the host. Concurrent atomic access is at the granularity of the whole allocation. Memory consistency can be enforced between devices that support concurrent atomic access using atomic operations. Undefined behavior occurs if concurrent atomic accesses are made to an allocation from devices that do not support concurrent atomic access.

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

**Shared** allocations may be prefetched to a supporting device via the :ref:`zeCommandListAppendMemoryPrefetch` API.
Prefetching may allow memory transfers to be scheduled concurrently with other computations and may improve performance.

Additionally, an application may provide memory advice for a **shared** allocation via the :ref:`zeCommandListAppendMemAdvise` API,
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

Virtual memory can be reserved using :ref:`zeVirtualMemReserve`\. The reservation starting address
and size must be page aligned. Applications should query the page size for the allocation
using :ref:`zeVirtualMemQueryPageSize`\.

The following pseudo-code demonstrates a basic sequence for reserving virtual memory:

.. parsed-literal::

        // Query page size for our 1MB allocation.
        size_t pageSize;
        size_t allocationSize = 1048576;
        :ref:`zeVirtualMemQueryPageSize`\(hContext, hDevice, allocationSize, &pageSize);

        // Reserve 1MB of virtual address space.
        size_t reserveSize = align(allocationSize, pageSize);

        void* ptr = nullptr;
        :ref:`zeVirtualMemReserve`\(hContext, nullptr, reserveSize, &ptr);

Growing Virtual Address Reservations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

An application may wish to reserve an address range starting at a specific virtual address.
This may be useful when there is a need to grow a reservation. However, if the
implementation is not able to reserve the new allocation at the requested starting address
then it will find a new suitable range with a different starting address. If the application
requires a specific starting address then the application should ensure that the return
address from :ref:`zeVirtualMemReserve` matches the starting address it wants. If they
are different then the application may want to create a new larger reservation and remap
the physical memory from the first reservation to this new reservation and free the
old reservation.

.. parsed-literal::

        // Reserve another 1MB of virtual address space that is contiguous with previous reservation.
        void* newptr = (uint8_t*)ptr + reserveSize;
        void* retptr;
        :ref:`zeVirtualMemReserve`\(hContext, newptr, reserveSize, &retptr);

        if (retptr != newptr)
        {
            // Free new reservation as it's not what we want due to incorrect starting address.
            :ref:`zeVirtualMemFree`\(hContext, retptr, reserveSize);

            // Make new larger 2MB reservation and remap physical pages to this.
            size_t pageSize;
            size_t largerAllocationSize = 2097152;
            :ref:`zeVirtualMemQueryPageSize`\(hContext, hDevice, largerAllocationSize, &pageSize);

            // Reserve 2MB of virtual address space.
            size_t largerReserveSize = align(largerAllocationSize, pageSize);

            void* ptr = nullptr;
            :ref:`zeVirtualMemReserve`\(hContext, nullptr, largerReserveSize, &ptr);

            // Remap physical pages from original reservation to our new larger reservation.
            ...

            // Free original reservation that we were trying to grow.
            :ref:`zeVirtualMemFree`\(hContext, ptr, reserveSize);
        }

Physical Memory
~~~~~~~~~~~~~~~

Physical memory is explicitly represented in the API as physical memory objects
that are reservations of physical pages. The application will use :ref:`zePhysicalMemCreate`
to create a physical memory object.

The following pseudo-code demonstrates a basic sequence for creating a physical memory object:

.. parsed-literal::

        // Create 1MB physical memory object
        ze_physical_mem_handle_t hPhysicalAlloc;
        size_t physicalSize = align(allocationSize, pageSize);
        :ref:`ze-physical-mem-desc-t` pmemDesc = {
            :ref:`ZE_STRUCTURE_TYPE_PHYSICAL_MEM_DESC <ze-structure-type-t>`\,
            nullptr,
            0, // flags
            physicalSize // size
        };

        :ref:`zePhysicalMemCreate`\(hContext, hDevice, &pmemDesc, &hPhysicalAlloc);

Mapping Virtual Memory Pages
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Reserved virtual memory pages can be mapped to physical memory using :ref:`zeVirtualMemMap`\.
An application can map the entire reserved virtual address range or can sparsely map the
reserved virtual address range using one or more physical memory objects. Once mapped, the
physical pages for a physical memory object can be faulted in for devices that support
on-demand paging. In addition, the residency API can be used to control residency of
these physical pages.

The following pseudo-code demonstrates mapping a 1MB reservation into physical memory:

.. parsed-literal::

        // Map entire 1MB reservation and set access to read/write.
        :ref:`zeVirtualMemMap`\(hContext, ptr, reserveSize, hPhysicalAlloc, 0,
            :ref:`ZE_MEMORY_ACCESS_ATTRIBUTE_READWRITE <ze-memory-access-attribute-t>`\);


Access Attributes
~~~~~~~~~~~~~~~~~
Access attributes can be set for a range of pages when mapping virtual memory
pages with :ref:`zeVirtualMemMap` or with :ref:`zeVirtualMemSetAccessAttribute`\.
In addition, an application can query access attributes for a page aligned
virtual memory range.

.. parsed-literal::

        size_t accessRangeSize;
        :ref:`ze-memory-access-attribute-t` access;
        :ref:`zeVirtualMemGetAccessAttribute`\(hContext, ptr, reserveSize, &access, &accessRangeSize);

        // Expecting entire range to have the same access attribute and it be read/write.
        assert(accessRangeSize == reserveSize);
        assert(access == :ref:`ZE_MEMORY_ACCESS_ATTRIBUTE_READWRITE <ze-memory-access-attribute-t>`\);

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
        :ref:`zeVirtualMemQueryPageSize`\(hContext, hDevice, allocationSize, &pageSize);

        size_t reserveSize = align(allocationSize, pageSize);

        void* ptr = nullptr;
        :ref:`zeVirtualMemReserve`\(hContext, nullptr, reserveSize, &ptr);

        ...

        // Sub-allocate 128KB of our 1GB allocation.
        size_t subAllocSize = 131072;
        :ref:`zeVirtualMemQueryPageSize`\(hContext, hDevice, subAllocSize, &pageSize);

        // Create physical memory object for our 128KB sub-allocation.
        size_t subAllocAlignedSize = align(subAllocSize, pageSize);
        :ref:`ze-physical-mem-desc-t` pmemDesc = {
            :ref:`ZE_STRUCTURE_TYPE_PHYSICAL_MEM_DESC <ze-structure-type-t>`\,
            nullptr,
            0, // flags
            subAllocAlignedSize // size
        };
        ze_physical_mem_handle_t hPhysicalAlloc;
        :ref:`zePhysicalMemCreate`\(hContext, hDevice, &pmemDesc, &hPhysicalAlloc);

        // Find suitable 128KB sub-allocation that matches page alignments.
        ...

        :ref:`zeVirtualMemMap`\(hContext, subAllocPtr, subAllocAlignedSize, hPhysicalAlloc, 0,
            :ref:`ZE_MEMORY_ACCESS_ATTRIBUTE_READWRITE <ze-memory-access-attribute-t>`\);

        ...

        // Sub-allocate 8MB of our 1GB allocation.
        size_t subAllocDiffSize = 8388608;
        :ref:`zeVirtualMemQueryPageSize`\(hContext, hDevice, subAllocDiffSize, &pageSize);
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
       :ref:`ze-image-format-t` format = {
           :ref:`ZE_IMAGE_FORMAT_LAYOUT_32 <ze-image-format-layout-t>`\, :ref:`ZE_IMAGE_FORMAT_TYPE_FLOAT <ze-image-format-type-t>`\,
           :ref:`ZE_IMAGE_FORMAT_SWIZZLE_R <ze-image-format-swizzle-t>`\, :ref:`ZE_IMAGE_FORMAT_SWIZZLE_0 <ze-image-format-swizzle-t>`\, :ref:`ZE_IMAGE_FORMAT_SWIZZLE_0 <ze-image-format-swizzle-t>`\, :ref:`ZE_IMAGE_FORMAT_SWIZZLE_1 <ze-image-format-swizzle-t>`
       };

       :ref:`ze-image-desc-t` imageDesc = {
           :ref:`ZE_STRUCTURE_TYPE_IMAGE_DESC <ze-structure-type-t>`\,
           nullptr,
           0, // read-only
           :ref:`ZE_IMAGE_TYPE_2D <ze-image-type-t>`\,
           format,
           128, 128, 0, 0, 0
       };
       ze_image_handle_t hImage;
       :ref:`zeImageCreate`\(hContext, hDevice, &imageDesc, &hImage);

       // upload contents from host pointer
       :ref:`zeCommandListAppendImageCopyFromMemory`\(hCommandList, hImage, nullptr, pImageData, nullptr, 0, nullptr);
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
       :ref:`zeKernelSetCacheConfig`\(hKernel, :ref:`ZE_CACHE_CONFIG_FLAG_LARGE_SLM <ze-cache-config-flags-t>`\);


.. _external-memory:

External Memory Import and Export
---------------------------------

External memory handles may be imported from other APIs, or exported for use in other APIs.
Importing and exporting external memory is an optional feature.
Devices may describe the types of external memory handles they support using :ref:`zeDeviceGetExternalMemoryProperties`\.

Importing and exporting external memory is supported for device and host memory allocations and images.

The following pseudo-code demonstrates how to allocate and export an external memory handle for a device memory allocation as a Linux dma_buf:

.. parsed-literal::

        // Set up the request for an exportable allocation
        :ref:`ze-external-memory-export-desc-t` export_desc = {
            :ref:`ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_DESC <ze-structure-type-t>`\,
            nullptr, // pNext
            :ref:`ZE_EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF <ze-external-memory-type-flags-t>`
        };

        // Link the request into the allocation descriptor and allocate
        alloc_desc.pNext = &export_desc;
        :ref:`zeMemAllocDevice`\(hContext, &alloc_desc, size, alignment, hDevice, &ptr);

        ...

        // Set up the request to export the external memory handle
        :ref:`ze-external-memory-export-fd-t` export_fd = {
            :ref:`ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_FD <ze-structure-type-t>`\,
            nullptr, // pNext
            :ref:`ZE_EXTERNAL_MEMORY_TYPE_FLAG_OPAQUE_FD <ze-external-memory-type-flags-t>`\,
            0 // [out] fd
        };

        // Link the export request into the query
        alloc_props.pNext = &export_fd;
        :ref:`zeMemGetAllocProperties`\(hContext, ptr, &alloc_props, nullptr);

The following pseudo-code demonstrates how to import a Linux dma_buf as an external memory handle for a device memory allocation:

.. parsed-literal::

        // Set up the request to import the external memory handle
        :ref:`ze-external-memory-import-fd-t` import_fd = {
            :ref:`ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD <ze-structure-type-t>`\,
            nullptr, // pNext
            :ref:`ZE_EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF <ze-external-memory-type-flags-t>`\,
            fd
        };

        // Link the request into the allocation descriptor and allocate
        alloc_desc.pNext = &import_fd;
        :ref:`zeMemAllocDevice`\(hContext, &alloc_desc, size, alignment, hDevice, &ptr);

Another example, which the following pseudo-code demonstrates, is how to import a Linux dma_buf as an external
memory handle for :ref:`Images`:

.. parsed-literal::

        // Set up the request to import the external memory handle
        :ref:`ze-external-memory-import-fd-t` import_fd = {
            :ref:`ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD <ze-structure-type-t>`\,
            nullptr, // pNext
            :ref:`ZE_EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF <ze-external-memory-type-flags-t>`\,
            fd
        };

        // Link the request into the allocation descriptor and allocate
        image_desc.pNext = &import_fd; // extend ze_image_desc_t

        // Setup matching image properties for imported image.
        image_desc.width = import_width;
        ...

        :ref:`zeImageCreate`\(hContext, hDevice, &image_desc, &hImage);


Command Queues and Command Lists
================================

The following are the motivations for separating a command queue from a command list:

- Command queues are mostly associated with physical device properties, such as the number of input streams.
- Command queues provide (near) zero-latency access to the device.
- Command lists are mostly associated with Host threads for simultaneous construction.
- Command list construction can occur independently of command queue submission.

The following diagram illustrates the hierarchy of command lists and command queues to the device:

.. image:: ../images/core_queue.png

Command Queue Groups
--------------------

A command queue group represents a physical input stream, which represents one or more physical device engines.


Discovery
~~~~~~~~~

- The number and properties of command queue groups is queried by using :ref:`zeDeviceGetCommandQueueGroupProperties`\.
- The number of physical engines within a group is queried from :ref:`ze-command-queue-group-properties-t`\.numQueues.
- The types of commands supported by the group is queried from :ref:`ze-command-queue-group-properties-t`\.flags.
- For example, if a command list is meant to be submitted to a copy-only engine,
  then it must be created using a command queue group ordinal with
  :ref:`ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY <ze-command-queue-group-property-flags-t>` set and :ref:`ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE <ze-command-queue-group-property-flags-t>` not set,
  and submitted to a command queue created using the same ordinal.

The following pseudo-code demonstrates a basic sequence for discovery of command queue groups:

.. parsed-literal::

    // Discover all command queue groups
    uint32_t cmdqueueGroupCount = 0;
    :ref:`zeDeviceGetCommandQueueGroupProperties`\(hDevice, &cmdqueueGroupCount, nullptr);

    :ref:`ze-command-queue-group-properties-t`\* cmdqueueGroupProperties = (:ref:`ze-command-queue-group-properties-t`\*)
        allocate(cmdqueueGroupCount * sizeof(:ref:`ze-command-queue-group-properties-t`\));
    cmdqueueGroupProperties[ i ].stype = :ref:`ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES <ze-structure-type-t>`\;
    cmdqueueGroupProperties[ i ].pNext = nullptr;
    :ref:`zeDeviceGetCommandQueueGroupProperties`\(hDevice, &cmdqueueGroupCount, cmdqueueGroupProperties);


    // Find a command queue type that support compute
    uint32_t computeQueueGroupOrdinal = cmdqueueGroupCount;
    for( uint32_t i = 0; i < cmdqueueGroupCount; ++i ) {
        if( cmdqueueGroupProperties[ i ].flags & :ref:`ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE <ze-command-queue-group-property-flags-t>` ) {
            computeQueueGroupOrdinal = i;
            break;
        }
    }

    if(computeQueueGroupOrdinal == cmdqueueGroupCount)
        return; // no compute queues found


Command Queues
--------------

A command queue represents a logical input stream to the device, tied to a physical input stream.

Creation
~~~~~~~~

- At creation time, the command queue is explicitly bound to a command queue group via its ordinal.
- Multiple command queues may be created that use the same command queue group. For example,
  an application may create a command queue per Host thread with different scheduling priorities.
- Multiple command queues created for the same command queue group on the same context,
  may also share the same physical hardware context.
- The maximum number of command queues an application can create is limited by device-specific
  resources; e.g., the maximum number of logical hardware contexts supported by the device.
  This can be queried from :ref:`ze-device-properties-t`\.maxHardwareContexts.
- The physical engine within a command queue group on which a command queue executes is virtualized
  via its index, limited by the number of physical engines of the type of the command queue group,
  i.e. :ref:`ze-command-queue-group-properties-t`\.numQueues.
- The command queue index provides a mechanism for an application to indicate which command queues
  can execute concurrently (different indices).
- Command queues that do not share the same index may launch and execute concurrently.
- Command queues that share the same index launch sequentially but may execute concurrently.
- All command lists executed on a command queue are guaranteed to **only** execute on an engine from the
  command queue group to which it is assigned; e.g., copy commands in a compute command list / queue will
  execute via the compute engine, not the copy engine.
- There is no guarantee that command lists submitted to command queues with different indices will execute concurrently,
  only a possibility that they might execute concurrently.

The following pseudo-code demonstrates a basic sequence for creation of command queues:

.. parsed-literal::

    // Create a command queue
    :ref:`ze-command-queue-desc-t` commandQueueDesc = {
        :ref:`ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC <ze-structure-type-t>`\,
        nullptr,
        computeQueueGroupOrdinal,
        0, // index
        0, // flags
        :ref:`ZE_COMMAND_QUEUE_MODE_DEFAULT <ze-command-queue-mode-t>`\,
        :ref:`ZE_COMMAND_QUEUE_PRIORITY_NORMAL <ze-command-queue-priority-t>`
    };
    ze_command_queue_handle_t hCommandQueue;
    :ref:`zeCommandQueueCreate`\(hContext, hDevice, &commandQueueDesc, &hCommandQueue);
    ...

Execution
~~~~~~~~~

- Command lists submitted to a command queue are **immediately** submitted to the device for execution.
- Submitting multiple commands lists in a single submission allows an implementation the opportunity to optimize across command lists.
- Command queue submission is free-threaded, allowing multiple Host threads to share the same command queue.
- If multiple Host threads enter the same command queue simultaneously, then execution order is undefined.
- Command lists can only be executed on a command queue with an identical command queue group ordinal.
- If a device contains multiple sub-devices, then command lists submitted to a device-level command queue
  may be optimized by the driver to fully exploit the concurrency of the sub-devices by distributing command lists across sub-devices.
- If the application prefers to opt-out of these optimizations, such as when the application plans to perform this distribution itself,
  then it should use :ref:`ZE_COMMAND_QUEUE_FLAG_EXPLICIT_ONLY <ze-command-queue-flags-t>`\. Only command lists created using :ref:`ZE_COMMAND_LIST_FLAG_EXPLICIT_ONLY <ze-command-list-flags-t>`
  can be executed on a command queue created using :ref:`ZE_COMMAND_QUEUE_FLAG_EXPLICIT_ONLY <ze-command-queue-flags-t>`\.


Destruction
~~~~~~~~~~~

- The application is responsible for making sure the device is not currently
  executing from a command queue before it is deleted. This is
  typically done by tracking command queue fences, but may also be
  handled by calling :ref:`zeCommandQueueSynchronize`\.

Command Lists
-------------

A command list represents a sequence of commands for execution on a command queue.

.. _creation-1:

Creation
~~~~~~~~

- A command list is created for a device to allow device-specific appending of commands.
- A command list is created for execution on a specific type of command queue, specified using
  the command queue group ordinal.
- A command list can be copied to create another command list. The application may use this
  to copy a command list for use on a different device.

Appending
~~~~~~~~~

- There is no implicit binding of command lists to Host threads. Therefore, an
  application may share a command list handle across multiple Host threads. However,
  the application is responsible for ensuring that multiple Host threads do not access
  the same command list simultaneously.
- By default, commands are started in the same order in which they are appended.
  However, an application may allow the driver to optimize the ordering by using
  :ref:`ZE_COMMAND_LIST_FLAG_RELAXED_ORDERING <ze-command-list-flags-t>`\. Reordering is guaranteed to only occur
  between barriers and synchronization primitives.
- By default, commands submitted to a command list are optimized for execution by
  balancing both device throughput and Host latency.
- For very low-level latency usage-models, applications should use immediate command lists.
- For usage-models where maximum throughput is desired, applications should
  use :ref:`ZE_COMMAND_LIST_FLAG_MAXIMIZE_THROUGHPUT <ze-command-list-flags-t>`\. This flag will indicate to the driver
  it may perform additional device-specific optimizations.
- If a device contains multiple sub-devices, then commands submitted to a device-level
  command list may be optimized by the driver to fully exploit the concurrency of the
  sub-devices by distributing commands across sub-devices. If the application prefers
  to opt-out of these optimizations, such as when the application plans to perform this
  distribution itself, then it should use :ref:`ZE_COMMAND_LIST_FLAG_EXPLICIT_ONLY <ze-command-list-flags-t>`\.

The following pseudo-code demonstrates a basic sequence for creation of command lists:

.. parsed-literal::

       // Create a command list
       :ref:`ze-command-list-desc-t` commandListDesc = {
           :ref:`ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC <ze-structure-type-t>`\,
           nullptr,
           computeQueueGroupOrdinal,
           0 // flags
       };
       ze_command_list_handle_t hCommandList;
       :ref:`zeCommandListCreate`\(hContext, hDevice, &commandListDesc, &hCommandList);
       ...

Submission
~~~~~~~~~~

- There is no implicit association between a command list and a command queue.
  Therefore, a command list may be submitted to any or multiple command queues.
- By definition, a command list cannot be executed concurrently on multiple command queues.
- The application is responsible for calling close before submission to a command queue.
- Command lists do not inherit state from other command lists executed on the same
  command queue.  i.e. each command list begins execution in its own default state.
- A command list may be submitted multiple times.  It is up to the application to ensure
  that the command list can be executed multiple times.
  For example, events must be explicitly reset prior to re-execution.

The following pseudo-code demonstrates submission of commands to a command queue, via a command list:

.. parsed-literal::

       ...
       // finished appending commands (typically done on another thread)
       :ref:`zeCommandListClose`\(hCommandList);

       // Execute command list in command queue
       :ref:`zeCommandQueueExecuteCommandLists`\(hCommandQueue, 1, &hCommandList, nullptr);

       // synchronize host and device
       :ref:`zeCommandQueueSynchronize`\(hCommandQueue, UINT32_MAX);

       // Reset (recycle) command list for new commands
       :ref:`zeCommandListReset`\(hCommandList);
       ...

Recycling
~~~~~~~~~

- A command list may be recycled to avoid the overhead of frequent creation and destruction.
- The application is responsible for making sure the device is not currently
  executing from a command list before it is reset. This should be
  handled by tracking a completion event associated with the command list.
- The application is responsible for making sure the device is not currently
  executing from a command list before it is deleted. This should be
  handled by tracking a completion event associated with the command list.

Low-Latency Immediate Command Lists
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A special type of command list can be used for very low-latency submission usage-models.

- An immediate command list is both a command list and an implicit command queue.
- An immediate command list is created using a command queue descriptor.
- Commands appended into an immediate command list are immediately executed on the device.
- Commands appended into an immediate command list may execute synchronously, by blocking until the command is complete.
- An immediate command list is not required to be closed or reset. However, usage will be honored, and expected behaviors will be followed.

The following pseudo-code demonstrates a basic sequence for creation and usage of immediate command lists:

.. parsed-literal::

       // Create an immediate command list
       :ref:`ze-command-queue-desc-t` commandQueueDesc = {
           :ref:`ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC <ze-structure-type-t>`\,
           nullptr,
           computeQueueGroupOrdinal,
           0, // index
           0, // flags
           :ref:`ZE_COMMAND_QUEUE_MODE_DEFAULT <ze-command-queue-mode-t>`\,
           :ref:`ZE_COMMAND_QUEUE_PRIORITY_NORMAL <ze-command-queue-priority-t>`
       };
       ze_command_list_handle_t hCommandList;
       :ref:`zeCommandListCreateImmediate`\(hContext, hDevice, &commandQueueDesc, &hCommandList);

       // Immediately submit a kernel to the device
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);
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
       :ref:`ze-fence-desc-t` fenceDesc = {
           :ref:`ZE_STRUCTURE_TYPE_FENCE_DESC <ze-structure-type-t>`\,
           nullptr,
           0 // flags
       };
       ze_fence_handle_t hFence;
       :ref:`zeFenceCreate`\(hCommandQueue, &fenceDesc, &hFence);

       // Execute a command list with a signal of the fence
       :ref:`zeCommandQueueExecuteCommandLists`\(hCommandQueue, 1, &hCommandList, hFence);

       // Wait for fence to be signaled
       :ref:`zeFenceHostSynchronize`\(hFence, UINT32_MAX);
       :ref:`zeFenceReset`\(hFence);
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
       :ref:`ze-event-pool-desc-t` eventPoolDesc = {
           :ref:`ZE_STRUCTURE_TYPE_EVENT_POOL_DESC <ze-structure-type-t>`\,
           nullptr,
           :ref:`ZE_EVENT_POOL_FLAG_HOST_VISIBLE <ze-event-pool-flags-t>`\, // all events in pool are visible to Host
           1 // count
       };
       ze_event_pool_handle_t hEventPool;
       :ref:`zeEventPoolCreate`\(hContext, &eventPoolDesc, 0, nullptr, &hEventPool);

       :ref:`ze-event-desc-t` eventDesc = {
           :ref:`ZE_STRUCTURE_TYPE_EVENT_DESC <ze-structure-type-t>`\,
           nullptr,
           0, // index
           0, // no additional memory/cache coherency required on signal
           :ref:`ZE_EVENT_SCOPE_FLAG_HOST <ze-event-scope-flags-t>`  // ensure memory coherency across device and Host after event completes
       };
       ze_event_handle_t hEvent;
       :ref:`zeEventCreate`\(hEventPool, &eventDesc, &hEvent);

       // Append a signal of an event into the command list after the kernel executes
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel1, &launchArgs, hEvent, 0, nullptr);

       // Execute the command list with the signal
       :ref:`zeCommandQueueExecuteCommandLists`\(hCommandQueue, 1, &hCommandList, nullptr);

       // Wait on event to complete
       :ref:`zeEventHostSynchronize`\(hEvent, 0);
       ...

The following diagram illustrates a dependency between command lists using events:

.. image:: ../images/core_event.png

Kernel Timestamp Events
~~~~~~~~~~~~~~~~~~~~~~~

A kernel timestamp event is a special type of event that records device timestamps at the start and end of the execution of kernels. The primary motivation for kernel timestamps is to provide a duration of execution.  For consistency and orthogonality, kernel timestamps are also supported for non-kernel operations. Kernel timestamps execute along a device timeline but because of limited range may wrap unexpectedly. Because of this, the temporal order of two kernel timestamps shouldn't be inferred despite coincidental START/END values. :ref:`zeCommandListAppendWriteGlobalTimestamp` provides a similar mechanism but with maximum range. Timestamps from :ref:`zeCommandListAppendWriteGlobalTimestamp` and kernel timestamp events should not be inferred as equivalent even if reported within identical ranges.

- The duration of a kernel timestamp for :ref:`zeCommandListAppendSignalEvent` and :ref:`zeEventHostSignal` is undefined. However, for consistency and orthogonality the event will report correctly as signaled when used by other event API functionality.
- A kernel timestamp event result can be queried using either :ref:`zeEventQueryKernelTimestamp` or :ref:`zeCommandListAppendQueryKernelTimestamps`
- The :ref:`ze-kernel-timestamp-result-t` contains both the per-context and global timestamp values at the start and end of the kernel's execution
- Since these counters are only 32bits, the application must detect and handle counter wrapping when calculating execution time

.. parsed-literal::

       // Get timestamp frequency
       const double timestampFreq = NS_IN_SEC / device_properties.timerResolution;
       const uint64_t timestampMaxValue = ~(-1L << device_properties.kernelTimestampValidBits);

       // Create event pool
       :ref:`ze-event-pool-desc-t` tsEventPoolDesc = {
           :ref:`ZE_STRUCTURE_TYPE_EVENT_POOL_DESC <ze-structure-type-t>`\,
           nullptr,
           :ref:`ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP <ze-event-pool-flags-t>`\, // all events in pool are kernel timestamps
           1 // count
       };
       ze_event_pool_handle_t hTSEventPool;
       :ref:`zeEventPoolCreate`\(hContext, &tsEventPoolDesc, 0, nullptr, &hTSEventPool);

       :ref:`ze-event-desc-t` tsEventDesc = {
           :ref:`ZE_STRUCTURE_TYPE_EVENT_DESC <ze-structure-type-t>`\,
           nullptr,
           0, // index
           0, // no additional memory/cache coherency required on signal
           0  // no additional memory/cache coherency required on wait
       };
       ze_event_handle_t hTSEvent;
       :ref:`zeEventCreate`\(hEventPool, &tsEventDesc, &hTSEvent);

       // allocate memory for results
       :ref:`ze-device-mem-alloc-desc-t` tsResultDesc = {
           :ref:`ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC <ze-structure-type-t>`\,
           nullptr,
           0, // flags
           0  // ordinal
       };
       :ref:`ze-kernel-timestamp-result-t`\* tsResult = nullptr;
       :ref:`zeMemAllocDevice`\(hContext, &tsResultDesc, sizeof(:ref:`ze-kernel-timestamp-result-t`\), sizeof(uint32_t), hDevice, &tsResult);

       // Append a signal of a timestamp event into the command list after the kernel executes
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel1, &launchArgs, hTSEvent, 0, nullptr);

       // Append a query of a timestamp event into the command list
       :ref:`zeCommandListAppendQueryKernelTimestamps`\(hCommandList, 1, &hTSEvent, tsResult, nullptr, hEvent, 1, &hTSEvent);

       // Execute the command list with the signal
       :ref:`zeCommandQueueExecuteCommandLists`\(hCommandQueue, 1, &hCommandList, nullptr);

       // Wait on event to complete
       :ref:`zeEventHostSynchronize`\(hEvent, 0);

       // Calculation execution time(s)
       double globalTimeInNs = ( tsResult->global.kernelEnd >= tsResult->global.kernelStart )
           ? ( tsResult->global.kernelEnd - tsResult->global.kernelStart ) * timestampFreq
           : (( timestampMaxValue - tsResult->global.kernelStart) + tsResult->global.kernelEnd + 1 ) * timestampFreq;

       double contextTimeInNs = ( tsResult->context.kernelEnd >= tsResult->context.kernelStart )
           ? ( tsResult->context.kernelEnd - tsResult->context.kernelStart ) * timestampFreq
           : (( timestampMaxValue - tsResult->context.kernelStart) + tsResult->context.kernelEnd + 1 ) * timestampFreq;
       ...


Barriers
========

There are two types of barriers:

1. **Execution Barriers** - used to communicate execution dependencies between commands within a command list or across command queues, devices and/or Host.
2. **Memory Barriers** - used to communicate memory coherency dependencies between commands within a command list or across command queues, devices and/or Host.

The following pseudo-code demonstrates a sequence for submission of a brute-force execution and global memory barrier:

.. parsed-literal::

       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

       // Append a barrier into a command list to ensure hKernel1 completes before hKernel2 begins
       :ref:`zeCommandListAppendBarrier`\(hCommandList, nullptr, 0, nullptr);

       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);
       ...

Execution Barriers
------------------

Commands executed on a command list are only guaranteed to start in the same order in which they are submitted; i.e. there is no implicit definition of the order of completion.

- Fences provide implicit, coarse-grain control to indicate that all previous commands must complete prior to the fence being signaled.
- Events provide explicit, fine-grain control over execution dependencies between commands; allowing more opportunities for concurrent execution and higher device utilization.

The following pseudo-code demonstrates a sequence for submission of a fine-grain execution-only dependency using events:

.. parsed-literal::

       :ref:`ze-event-desc-t` event1Desc = {
           :ref:`ZE_STRUCTURE_TYPE_EVENT_DESC <ze-structure-type-t>`\,
           nullptr,
           0, // index
           0, // no additional memory/cache coherency required on signal
           0  // no additional memory/cache coherency required on wait
       };
       ze_event_handle_t hEvent1;
       :ref:`zeEventCreate`\(hEventPool, &event1Desc, &hEvent1);

       // Ensure hKernel1 completes before signaling hEvent1
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel1, &launchArgs, hEvent1, 0, nullptr);

       // Ensure hEvent1 is signaled before starting hKernel2
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel2, &launchArgs, nullptr, 1, &hEvent1);
       ...

Memory Barriers
---------------

Commands executed on a command list are *not* guaranteed to maintain memory coherency with other commands;
i.e. there is no implicit memory or cache coherency.

- Fences provide implicit, coarse-grain control to indicate that all caches and memory are coherent across the device and Host prior to the fence being signaled.
- Events provide explicit, fine-grain control over cache and memory coherency dependencies between commands; allowing more opportunities for concurrent execution and higher device utilization.

The following pseudo-code demonstrates a sequence for submission of a fine-grain memory dependency using events:

.. parsed-literal::

       :ref:`ze-event-desc-t` event1Desc = {
           :ref:`ZE_STRUCTURE_TYPE_EVENT_DESC <ze-structure-type-t>`\,
           nullptr,
           0, // index
           :ref:`ZE_EVENT_SCOPE_FLAG_DEVICE <ze-event-scope-flags-t>`\, // ensure memory coherency across device before event signaled
           0  // no additional memory/cache coherency required on wait
       };
       ze_event_handle_t hEvent1;
       :ref:`zeEventCreate`\(hEventPool, &event1Desc, &hEvent1);

       // Ensure hKernel1 memory writes are fully coherent across the device before signaling hEvent1
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel1, &launchArgs, hEvent1, 0, nullptr);

       // Ensure hEvent1 is signaled before starting hKernel2
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel2, &launchArgs, nullptr, 1, &hEvent1);
       ...

Range-based Memory Barriers
---------------------------

Range-based memory barriers provide explicit control of which cachelines
require coherency.

The following pseudo-code demonstrates a sequence for submission of a range-based memory barrier:

.. parsed-literal::

       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel1, &launchArgs, nullptr, 0, nullptr);

       // Ensure memory range is fully coherent across the device after hKernel1 and before hKernel2
       :ref:`zeCommandListAppendMemoryRangesBarrier`\(hCommandList, 1, &size, &ptr, nullptr, 0, nullptr);

       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel2, &launchArgs, nullptr, 0, nullptr);
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

Modules can be created from an IL or directly from native format using :ref:`zeModuleCreate`\.

- :ref:`zeModuleCreate` takes a format argument that specifies the input format.
- :ref:`zeModuleCreate` performs a compilation step when format is IL.

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
       :ref:`ze-module-desc-t` moduleDesc = {
           :ref:`ZE_STRUCTURE_TYPE_MODULE_DESC <ze-structure-type-t>`\,
           nullptr,
           :ref:`ZE_MODULE_FORMAT_IL_SPIRV <ze-module-format-t>`\,
           ilSize,
           pImageScalingIL,
           nullptr,
           nullptr
       };
       ze_module_handle_t hModule;
       :ref:`zeModuleCreate`\(hContext, hDevice, &moduleDesc, &hModule, nullptr);
       ...

Module Build Options
~~~~~~~~~~~~~~~~~~~~

Module build options can be passed with :ref:`ze-module-desc-t` as a string.

+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| Build Option                               | Description                                                                                                                                          | Default  | Device Support |
+============================================+======================================================================================================================================================+==========+================+
| -ze-opt-disable                            | Disable optimizations.                                                                                                                               | Disabled | All            |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| -ze-opt-level                              | Specifies optimization level for compiler. Levels are implementation specific.                                                                       | 2        | All            |
|                                            |                                                                                                                                                      |          |                |
|                                            |    * 0 is no optimizations (equivalent to ze-opt-disable)                                                                                            |          |                |
|                                            |    * 1 is optimize minimally (may be the same as 2)                                                                                                  |          |                |
|                                            |    * 2 is optimize more (default)                                                                                                                    |          |                |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| -ze-opt-greater-than-4GB-buffer-required   | Use 64-bit offset calculations for buffers.                                                                                                          | Disabled | GPU            |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| -ze-opt-large-register-file                | Increase number of registers available to threads.                                                                                                   | Disabled | GPU            |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| -ze-opt-has-buffer-offset-arg              | Extend stateless to stateful optimization to more cases with the use of additional offset (e.g. 64-bit pointer to binding table with 32-bit offset). | Disabled | GPU            |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+
| -g                                         | Include debugging information.                                                                                                                       | Disabled | GPU            |
+--------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------+----------+----------------+


Module Specialization Constants
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SPIR-V supports specialization constants that allow certain constants to be updated to new
values during runtime execution. Each specialization constant in SPIR-V has an identifier
and default value. The :ref:`zeModuleCreate` function allows for an array of constants and their
corresponding identifiers to be passed in to override the constants in the SPIR-V module.

.. parsed-literal::

       // Spec constant overrides for group size.
       :ref:`ze-module-constants-t` specConstants = {
           3,
           pGroupSizeIds,
           pGroupSizeValues
       };
       // OpenCL C kernel has been compiled to SPIRV IL (pImageScalingIL)
       :ref:`ze-module-desc-t` moduleDesc = {
           :ref:`ZE_STRUCTURE_TYPE_MODULE_DESC <ze-structure-type-t>`\,
           nullptr,
           :ref:`ZE_MODULE_FORMAT_IL_SPIRV <ze-module-format-t>`\,
           ilSize,
           pImageScalingIL,
           nullptr,
           &specConstants
       };
       ze_module_handle_t hModule;
       :ref:`zeModuleCreate`\(hContext, hDevice, &moduleDesc, &hModule, nullptr);
       ...

Note: Specialization constants are only handled at module create time and therefore if
you need to change them then you'll need to compile a new module.

Module Build Log
~~~~~~~~~~~~~~~~

The :ref:`zeModuleCreate` function can optionally generate a build log object ze_module_build_log_handle_t.

.. parsed-literal::

       ...
       ze_module_build_log_handle_t buildlog;
       :ref:`ze-result-t` result = :ref:`zeModuleCreate`\(hContext, hDevice, &desc, &module, &buildlog);

       // Only save build logs for module creation errors.
       if (result != :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\)
       {
           size_t szLog = 0;
           :ref:`zeModuleBuildLogGetString`\(buildlog, &szLog, nullptr);

           char_t* strLog = allocate(szLog);
           :ref:`zeModuleBuildLogGetString`\(buildlog, &szLog, strLog);

           // Save log to disk.
           ...

           free(strLog);
       }

       :ref:`zeModuleBuildLogDestroy`\(buildlog);

Dynamically Linked Modules
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Modules may be interdependent, i.e., a module may contain functions and global variables that are used and defined by different modules. Such a module is said to have both import as well as export linkage requirements. Private variables are not transferrable between linked modules, i.e., their visibility is limited to the module in which they are defined. Only global variables or static values passed to linked functions are visible between linked modules. All the import linkage requirements of a module must be satisfied before a kernel can be created from that module. Modules that have no imports do not need to be linked. Dynamically linking modules together is performed using :ref:`zeModuleDynamicLink`\. Modules cannot have ambiguous import dependencies, i.e., imported functions and global variables must only be defined once in any given set of modules passed to :ref:`zeModuleDynamicLink`\. Imports are linked only once. Once all the import dependencies of a module have been linked, the use of that fully import-linked module in subsequent calls to :ref:`zeModuleDynamicLink` will not cause the imports of the module to be re-linked.

The :ref:`zeModuleDynamicLink` function can optionally generate a link log object ze_module_build_log_handle_t.



.. parsed-literal::

       ...
       ze_module_build_log_handle_t linklog;
       :ref:`ze-result-t` result = :ref:`zeModuleDynamicLink`\(numModules, &hModules, &hLinklog);

       // Check if there are linking errors
       if (result == :ref:`ZE_RESULT_ERROR_MODULE_LINK_FAILURE <ze-result-t>`\) {
         size_t szLog = 0;
         :ref:`zeModuleBuildLogGetString`\(linklog, &szLog, nullptr);

         char_t* strLog = allocate(szLog);
         :ref:`zeModuleBuildLogGetString`\(linklog, &szLog, strLog);

         // Save log to disk.
         ...

         free(strLog);
       }

       :ref:`zeModuleBuildLogDestroy`\(linklog);

Module Caching with Native Binaries
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Disk caching of modules is not supported by the driver. If a disk cache for modules is desired, then it is the
responsibility of the application to implement this using :ref:`zeModuleGetNativeBinary`\.

.. parsed-literal::

       ...
       // compute hash for pIL and check cache.
       ...

       if (cacheUpdateNeeded)
       {
           size_t szBinary = 0;
           :ref:`zeModuleGetNativeBinary`\(hModule, &szBinary, nullptr);

           uint8_t* pBinary = allocate(szBinary);
           :ref:`zeModuleGetNativeBinary`\(hModule, &szBinary, pBinary);

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

       :ref:`ze-kernel-desc-t` kernelDesc = {
           :ref:`ZE_STRUCTURE_TYPE_KERNEL_DESC <ze-structure-type-t>`\,
           nullptr,
           0, // flags
           "image_scaling"
       };
       ze_kernel_handle_t hKernel;
       :ref:`ze-result-t` result = :ref:`zeKernelCreate`\(hModule, &kernelDesc, &hKernel);

       // Check if there are unresolved imports
       if (result == :ref:`ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED <ze-result-t>`\) {
          // Un-resolvable import dependencies found in module!
          ...
       }

       // Check to see if the kernel "image_scaling" was found in the supplied module
       if (result == :ref:`ZE_RESULT_ERROR_INVALID_KERNEL_NAME <ze-result-t>`\) {
          // Kernel "image_scaling" not found in module!
          ...
       }

       ...

Kernel Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Use :ref:`zeKernelGetProperties` to query invariant properties from a Kernel object.

.. parsed-literal::

    ...
    :ref:`ze-kernel-properties-t` kernelProperties;
    :ref:`zeKernelGetProperties`\(hKernel, &kernelProperties);
    ...

See :ref:`ze-kernel-properties-t` for more information for kernel properties.

.. _execution-1:

Execution
---------

Kernel Group Size
~~~~~~~~~~~~~~~~~

The group size for a kernel can be set using :ref:`zeKernelSetGroupSize`\. If a group size is not
set prior to appending a kernel into a command list then a default will be chosen.
The group size can be updated over a series of append operations. The driver will copy the
group size information when appending the kernel into the command list.

.. parsed-literal::

       :ref:`zeKernelSetGroupSize`\(hKernel, groupSizeX, groupSizeY, 1);

       ...

The API supports a query for suggested group size when providing the global size. This function ignores the
group size that was set on the kernel using :ref:`zeKernelSetGroupSize`\.

.. parsed-literal::

       // Find suggested group size for processing image.
       uint32_t groupSizeX;
       uint32_t groupSizeY;
       :ref:`zeKernelSuggestGroupSize`\(hKernel, imageWidth, imageHeight, 1, &groupSizeX, &groupSizeY, nullptr);

       :ref:`zeKernelSetGroupSize`\(hKernel, groupSizeX, groupSizeY, 1);

       ...

Kernel Arguments
~~~~~~~~~~~~~~~~

Kernel arguments represent only the explicit kernel arguments that are within brackets e.g. func(arg1, arg2, ...).

- Use :ref:`zeKernelSetArgumentValue` to setup arguments for a kernel launch.
- The :ref:`zeCommandListAppendLaunchKernel` et al. functions will make a copy of the kernel arguments to send to the device.
- Kernel arguments can be updated at any time and used across multiple append calls.

The following pseudo-code demonstrates a sequence for setting kernel arguments and launching the kernel:

.. parsed-literal::

       // Bind arguments
       :ref:`zeKernelSetArgumentValue`\(hKernel, 0, sizeof(ze_image_handle_t), &src_image);
       :ref:`zeKernelSetArgumentValue`\(hKernel, 1, sizeof(ze_image_handle_t), &dest_image);
       :ref:`zeKernelSetArgumentValue`\(hKernel, 2, sizeof(uint32_t), &width);
       :ref:`zeKernelSetArgumentValue`\(hKernel, 3, sizeof(uint32_t), &height);

       :ref:`ze-group-count-t` launchArgs = { numGroupsX, numGroupsY, 1 };

       // Append launch kernel
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

       // Update image pointers to copy and scale next image.
       :ref:`zeKernelSetArgumentValue`\(hKernel, 0, sizeof(ze_image_handle_t), &src2_image);
       :ref:`zeKernelSetArgumentValue`\(hKernel, 1, sizeof(ze_image_handle_t), &dest2_image);

       // Append launch kernel
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

       ...

Kernel Launch
~~~~~~~~~~~~~

In order to launch a kernel on the device an application must call one of the AppendLaunchKernel-style functions for
a command list. The most basic version of these is :ref:`zeCommandListAppendLaunchKernel` which takes a
command list, kernel handle, launch arguments, and an optional synchronization event used to signal completion.
The launch arguments contain thread group dimensions.

.. parsed-literal::

       // compute number of groups to launch based on image size and group size.
       uint32_t numGroupsX = imageWidth / groupSizeX;
       uint32_t numGroupsY = imageHeight / groupSizeY;

       :ref:`ze-group-count-t` launchArgs = { numGroupsX, numGroupsY, 1 };

       // Append launch kernel
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

The function :ref:`zeCommandListAppendLaunchKernelIndirect` allows the launch parameters to be supplied indirectly in a
buffer that the device reads instead of the command itself. This allows for the previous operations on the
device to generate the parameters.

.. parsed-literal::

       :ref:`ze-group-count-t`\* pIndirectArgs;

       ...
       :ref:`zeMemAllocDevice`\(hContext, &desc, sizeof(:ref:`ze-group-count-t`\), sizeof(uint32_t), hDevice, &pIndirectArgs);

       // Append launch kernel - indirect
       :ref:`zeCommandListAppendLaunchKernelIndirect`\(hCommandList, hKernel, &pIndirectArgs, nullptr, 0, nullptr);

Cooperative Kernels
~~~~~~~~~~~~~~~~~~~

Cooperative kernels allow sharing of data and synchronization across all launched groups in a safe manner. To support this
there is a :ref:`zeCommandListAppendLaunchCooperativeKernel` that allows launching groups that can cooperate with each other.
The command list must be submitted to a command queue that was created with an ordinal of a command queue group
that has the :ref:`ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COOPERATIVE_KERNELS <ze-command-queue-group-property-flags-t>` flags set. The maximum number of groups for a
cooperative kernel launch may be determined by calling :ref:`zeKernelSuggestMaxCooperativeGroupCount`\.

.. parsed-literal::

       // query the maximum cooperative kernel launch for the kernel
       uint32_t maxGroupCount;
       :ref:`zeKernelSuggestMaxCooperativeGroupCount`\(hKernel, &maxGroupCount);

       // the total group count must be smaller than the queried maximum
       assert(numGroupsX * numGroupsY * numGroupsZ < maxGroupCount);

       :ref:`ze-group-count-t` launchArgs = { numGroupsX, numGroupsY, numGroupsZ };

       // Append launch cooperative kernel
       :ref:`zeCommandListAppendLaunchCooperativeKernel`\(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);


Sampler
-------

The API supports Sampler objects that represent state needed for sampling images from within
kernels. The :ref:`zeSamplerCreate` function takes a sampler descriptor (:ref:`ze-sampler-desc-t`\):

+-----------------------------------+-----------------------------------------+
| Sampler Field                     | Description                             |
+===================================+=========================================+
| Address Mode                      | Determines how out-of-bounds            |
|                                   | accesses are handled. See               |
|                                   | :ref:`ze-sampler-address-mode-t`\.      |
+-----------------------------------+-----------------------------------------+
| Filter Mode                       | Specifies which filtering mode to       |
|                                   | use. See                                |
|                                   | :ref:`ze-sampler-filter-mode-t`\.       |
+-----------------------------------+-----------------------------------------+
| Normalized                        | Specifies whether coordinates for       |
|                                   | addressing image are normalized         |
|                                   | [0,1] or not.                           |
+-----------------------------------+-----------------------------------------+

The following pseudo-code demonstrates the creation of a sampler object and passing it as a kernel argument:

.. parsed-literal::

       // Setup sampler for linear filtering and clamp out of bounds accesses to edge.
       :ref:`ze-sampler-desc-t` desc = {
           :ref:`ZE_STRUCTURE_TYPE_SAMPLER_DESC <ze-structure-type-t>`\,
           nullptr,
           :ref:`ZE_SAMPLER_ADDRESS_MODE_CLAMP <ze-sampler-address-mode-t>`\,
           :ref:`ZE_SAMPLER_FILTER_MODE_LINEAR <ze-sampler-filter-mode-t>`\,
           false
           };
       ze_sampler_handle_t sampler;
       :ref:`zeSamplerCreate`\(hContext, hDevice, &desc, &sampler);
       ...

       // The sampler can be passed as a kernel argument.
       :ref:`zeKernelSetArgumentValue`\(hKernel, 0, sizeof(ze_sampler_handle_t), &sampler);

       // Append launch kernel
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

Formatted Output
----------------

The API supports the ability to print formatted output from a kernel using functions such as ``printf``.
Calls to print formatted output will cause data to be written to an internal buffer, where the size of the internal buffer is given by :ref:`ze-device-module-properties-t`\.printfBufferSize.
When the internal buffer becomes full, additional calls to print formatted output will return an error code.

There is no ordering guarantee for the formatted output.
If multiple work-items make multiple calls to ``printf``, the output from one work-item may appear intermixed with output from other work-items.

On some devices, the internal buffer may not contain the formatted output itself, and instead the formatting may occur on the host.
Additionally, the final formatting may not occur and the output may not be flushed to the output stream until the event associated with the kernel launch is complete.
To ensure all output has been flushed to the output stream, wait on the event associated with the kernel launch, or wait for the kernel launch to complete using a coarser-grained synchronization method such as :ref:`zeFenceHostSynchronize` or :ref:`zeCommandQueueSynchronize`\.

Advanced
========

Environment Variables
---------------------

The following table documents the supported knobs for overriding default functional behavior.



+-----------------+-------------------------------------+-----------------------------------+-----------------------------------------------------------------------------------+
| Category        | Name                                | Values                            | Description                                                                       |
+=================+=====================================+===================================+===================================================================================+
| Device          | ZE_FLAT_DEVICE_HIERARCHY            | {**COMPOSITE**, FLAT, COMBINED}   | Defines device hierarchy model exposed by Level Zero driver implementation        |
+                 +-------------------------------------+-----------------------------------+-----------------------------------------------------------------------------------+
|                 | ZE_AFFINITY_MASK                    | list                              | Forces driver to only report devices (and sub-devices) as specified by values     |
+                 +-------------------------------------+-----------------------------------+-----------------------------------------------------------------------------------+
|                 | ZE_ENABLE_PCI_ID_DEVICE_ORDER       | {**0**, 1}                        | Forces driver to report devices from lowest to highest PCI bus ID                 |
+-----------------+-------------------------------------+-----------------------------------+-----------------------------------------------------------------------------------+
| Memory          | ZE_SHARED_FORCE_DEVICE_ALLOC        | {**0**, 1}                        | Forces all shared allocations into device memory                                  |
+-----------------+-------------------------------------+-----------------------------------+-----------------------------------------------------------------------------------+


Device Hierarchy
~~~~~~~~~~~~~~~~

ZE_FLAT_DEVICE_HIERARCHY allows users to select the device hierarchy model with which the underlying hardware is exposed and the types of devices returned with :ref:`zeDeviceGet`\.

When setting to `COMPOSITE`, :ref:`zeDeviceGet` returns all the devices that do not have a root-device. Traversing the device hierarchy is possible by querying sub-devices with :ref:`zeDeviceGetSubDevices` and root-devices with :ref:`zeDeviceGetRootDevice`\. Driver implementation may perform implicit optimizations to submissions and allocations done in the root-devices.

When setting to `FLAT`, :ref:`zeDeviceGet` returns all the devices that do not have sub-devices. Traversing the device hierarchy is **not** possible, with :ref:`zeDeviceGetSubDevices` returning always a count of 0 device handles and :ref:`zeDeviceGetRootDevice` returning nullptr. This mode allows Level Zero driver implementations to optimize execution and memory allocations by removing any overhead required to account for simultaneous use of root-devices and sub-devices in the same application.

When setting to `COMBINED`, :ref:`zeDeviceGet` returns all the devices that do not have sub-devices. Traversing the device hierarchy is possible by querying sub-devices with :ref:`zeDeviceGetSubDevices` and root-devices with :ref:`zeDeviceGetRootDevice`\. Driver implementation may perform implicit optimizations to submissions and allocations done in the root-devices.

Devices returned by SYSMAN APIs are not affected by ZE_FLAT_DEVICE_HIERARCHY and always return the top-level device handles corresponding to the physical devices.


Affinity Mask
~~~~~~~~~~~~~

The affinity mask allows an application or tool to restrict which devices, and sub-devices, are visible to 3rd-party libraries or applications in another process, respectively.
The affinity mask affects the number of handles returned from :ref:`zeDeviceGet` and :ref:`zeDeviceGetSubDevices`\.
The affinity mask is specified via an environment variable as a comma-seperated list of device and/or subdevice ordinals.
The values are specific to system configuration; e.g., the number of devices and the number of sub-devices for each device.
The values are specific to the order in which devices are reported by the driver; i.e., the first device maps to ordinal 0, the second device to ordinal 1, and so forth.
If the affinity mask is not set, then all devices and sub-devices are reported; as is the default behavior.

The affinity mask masks the devices as defined by value set in the ZE_FLAT_DEVICE_HIERARCHY environment variable, i.e., a Level Zero driver shall read
first ZE_FLAT_DEVICE_HIERARCHY to determine the device handles to be used by the application and then interpret the values passed in ZE_AFFINITY_MASK
based on the device model selected.

The order of the devices reported by the :ref:`zeDeviceGet` is implementation-specific and not affected by the order of devices in the affinity mask.

The order of the devices reported by the :ref:`zeDeviceGet` can be forced to be consistent by setting the ZE_ENABLE_PCI_ID_DEVICE_ORDER environment variable.


The following examples demonstrate proper usage for a system configuration composed of two physical devices, each of which can be further
sub-divided into four smaller devices. For the purpose of these examples, we will refer to the two physical devices as `parent devices`
and to the smaller sub-devices as `tiles`.

When setting the ZE_AFFINITY_MASK with different values, and ZE_FLAT_DEVICE_HIERARCHY to `COMPOSITE`, the following scenarios may occur:

ZE_AFFINITY_MASK = `0, 1`: all parent devices and tiles are reported (same as default):

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  Yes    | Device handle 0, sub-device handle 0   |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  Yes    | Device handle 0, sub-device handle 1   |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  Yes    | Device handle 0, sub-device handle 2   |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  Yes    | Device handle 0, sub-device handle 3   |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  Yes    | Device handle 1, sub-device handle 0   |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  Yes    | Device handle 1, sub-device handle 1   |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  Yes    | Device handle 1, sub-device handle 2   |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  Yes    | Device handle 1, sub-device handle 3   |
+---------------+------+---------+----------------------------------------+

ZE_AFFINITY_MASK = `0`: only parent device 0 is reported as device handle 0, with all its tiles reported as sub-device handles:

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  Yes    | Device handle 0, sub-device handle 0   |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  Yes    | Device handle 0, sub-device handle 1   |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  Yes    | Device handle 0, sub-device handle 2   |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  Yes    | Device handle 0, sub-device handle 3   |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+


ZE_AFFINITY_MASK = `1`: only parent device 1 is reported as device handle 0, with all its tiles reported as sub-device handles:

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  Yes    | Device handle 0, sub-device handle 0   |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  Yes    | Device handle 0, sub-device handle 1   |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  Yes    | Device handle 0, sub-device handle 2   |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  Yes    | Device handle 0, sub-device handle 3   |
+---------------+------+---------+----------------------------------------+


ZE_AFFINITY_MASK = `0.0`: only tile 0 in parent device 0 is reported as device handle 0:

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  Yes    | Device handle 0                        |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+


ZE_AFFINITY_MASK = `1.1, 1.2`: only parent device 1 is reported as device handle 0; with its tiles 1 and 2 reported as its sub-devices 0 and 1, respectively:

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  Yes    | Device handle 0, sub-device handle 0   |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  Yes    | Device handle 0, sub-device handle 1   |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+


ZE_AFFINITY_MASK = `0.2, 1.3, 1.0, 0.3`: both parent devices 0 and 1 are reported as device handles 0 and 1, respectively; parent device 0 reports its tiles 2 and 3 as sub-devices 0 and 1, respectively; parent device 1 reports tiles 0 and 3 as sub-devices 0 and 1, respectively; the order is unchanged:

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  Yes    | Device handle 0, sub-device handle 0   |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  Yes    | Device handle 0, sub-device handle 1   |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  Yes    | Device handle 1, sub-device handle 0   |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  Yes    | Device handle 1, sub-device handle 1   |
+---------------+------+---------+----------------------------------------+


The following examples show the use of different values in the ZE_AFFINITY_MASK when setting ZE_FLAT_DEVICE_HIERARCHY to `FLAT`, in the
same system with two parent devices and four tiles each. When setting ZE_FLAT_DEVICE_HIERARCHY to `FLAT`, only the tiles are reported by
:ref:`zeDeviceGet`\, which means that in this system :ref:`zeDeviceGet` would report up to 8 device handles, with device handles 0 to 3 corresponding
to the four tiles in parent device 0, and device handles 4 to 5 corresponding to the four tiles in parent device 1:

ZE_AFFINITY_MASK = `0, 1, 2, 3, 4, 5, 6, 7`: all tiles are reported as device handles by :ref:`zeDeviceGet` (same as default):

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  Yes    | Device handle 0                        |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  Yes    | Device handle 1                        |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  Yes    | Device handle 2                        |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  Yes    | Device handle 3                        |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  Yes    | Device handle 4                        |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  Yes    | Device handle 5                        |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  Yes    | Device handle 6                        |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  Yes    | Device handle 7                        |
+---------------+------+---------+----------------------------------------+


ZE_AFFINITY_MASK = `0`: only tile 0 in parent device 0 is reported as device handle 0:

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  Yes    | Device handle 0                        |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+


ZE_AFFINITY_MASK = `1`: only tile 1 in parent device 0 is reported as device handle 0.

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  Yes    | Device handle 0                        |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+


ZE_AFFINITY_MASK = `0, 4`: tile 0 from parent device 0 is reported as device handle 0 and tile 0 in parent device 1 is reported as device handle 1:

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  Yes    | Device handle 0                        |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  Yes    | Device handle 1                        |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+


ZE_AFFINITY_MASK = `1, 2, 7`: tile 1 from parent device 0 is reported as device handle 0, tile 2 in parent device 0 is reported as device handle 1, and tile 3 in parent device 1 is reported as device handle 2:

+---------------+------+---------+----------------------------------------+
| Parent Device | Tile | Exposed | Device Handle Used                     |
+===============+======+=========+========================================+
|       0       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       0       |  1   |  Yes    | Device handle 0                        |
+---------------+------+---------+----------------------------------------+
|       0       |  2   |  Yes    | Device handle 1                        |
+---------------+------+---------+----------------------------------------+
|       0       |  3   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  0   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  1   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  2   |  No     |                                        |
+---------------+------+---------+----------------------------------------+
|       1       |  3   |  Yes    | Device handle 2                        |
+---------------+------+---------+----------------------------------------+

ZE_AFFINITY_MASK = `0.0`: is not valid, as with ZE_FLAT_DEVICE_HIERARCHY set to 1, the device handles reported by :ref:`zeDeviceGet` are those which do not contain further sub-devices.

Sub-Device Support
------------------

The API allows support for sub-devices which can enable finer-grained control of scheduling and memory allocation to a sub-partition of the device.
There are functions to query and obtain sub-devices, but outside of these functions there are no distinctions between sub-devices and devices.
Sub-devices are not required to represent unique partitions of a device; i.e. multiple sub-devices may share the same physical hardware.
Furthermore, a sub-device can be partitioned into more sub-devices; e.g. down to a single slice.

Use :ref:`zeDeviceGetSubDevices` to confirm sub-devices are supported and to obtain a sub-device handle.
There are additional device properties in :ref:`ze-device-properties-t` for sub-devices.
These can be used to confirm a device is a sub-device and to query the sub-device id.
This may be used by libraries to determine if an input device handle represents a device or sub-device.

A driver is required to make device memory allocations on the parent device visible to its sub-devices.
However, when using a sub-device handle, the driver will attempt to place any device memory allocations in the local memory that is attached to the sub-device.
These allocations are only visible to the sub-device, its sub-devices, and so forth.
If the API call returns :ref:`ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY <ze-result-t>`\, then the application may attempt to retry using the parent device.

When creating command queues for a sub-device,
the application must determine the ordinal from calling :ref:`zeDeviceGetCommandQueueGroupProperties` using the sub-device handle.
See :ref:`ze-command-queue-desc-t` for more details.

A 16-byte unique device identifier (uuid) can be obtained for a device
or sub-device using :ref:`zeDeviceGetProperties`\.

.. parsed-literal::

       // Query for all sub-devices of the device
       uint32_t subdeviceCount = 0;
       :ref:`zeDeviceGetSubDevices`\(hDevice, &subdeviceCount, nullptr);

       ze_device_handle_t* allSubDevices = allocate(subdeviceCount * sizeof(ze_device_handle_t));
       :ref:`zeDeviceGetSubDevices`\(hDevice, &subdeviceCount, &allSubDevices);

       // Desire is to allocate and dispatch work to sub-device 2.
       assert(subdeviceCount >= 3);
       ze_device_handle_t hSubdevice = allSubDevices[2];

       // Query sub-device properties.
       :ref:`ze-device-properties-t` subdeviceProps {};
       subDeviceProps.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>`\;
       :ref:`zeDeviceGetProperties`\(hSubdevice, &subdeviceProps);

       assert(subdeviceProps.flags & :ref:`ZE_DEVICE_PROPERTY_FLAG_SUBDEVICE <ze-device-property-flags-t>`\); // Ensure that we have a handle to a sub-device.
       assert(subdeviceProps.subdeviceId == 2);    // Ensure that we have a handle to the sub-device we asked for.

       void* pMemForSubDevice2;
       :ref:`zeMemAllocDevice`\(hContext, &desc, memSize, sizeof(uint32_t), hSubdevice, &pMemForSubDevice2);
       ...

Device Residency
----------------

For devices that do not support page-faults, the driver must ensure that all pages that will be accessed by the kernel are resident before program execution.
This can be determined by checking :ref:`ze-device-properties-t`\.flags for :ref:`ZE_DEVICE_PROPERTY_FLAG_ONDEMANDPAGING <ze-device-property-flags-t>`\.

In most cases, the driver implicitly handles residency of allocations for device access.
This can be done by inspecting API parameters, including kernel arguments.
However, in cases where the devices does **not** support page-faulting *and* the driver is incapable of determining whether an allocation will be accessed by the device,
such as multiple levels of indirection, there are two methods available:

1. The application may set the :ref:`ZE_KERNEL_FLAG_FORCE_RESIDENCY <ze-kernel-flags-t>` flag during program creation to force all device allocations to be resident during execution.

    + The application should specify which allocation types will be indirectly accessed, using :ref:`zeKernelSetIndirectAccess` and the following flags, to optimize which allocations are made resident.

        * :ref:`ZE_KERNEL_INDIRECT_ACCESS_FLAG_HOST <ze-kernel-indirect-access-flags-t>`
        * :ref:`ZE_KERNEL_INDIRECT_ACCESS_FLAG_DEVICE <ze-kernel-indirect-access-flags-t>`
        * :ref:`ZE_KERNEL_INDIRECT_ACCESS_FLAG_SHARED <ze-kernel-indirect-access-flags-t>`

    + If the driver is unable to make all allocations resident, then the call to :ref:`zeCommandQueueExecuteCommandLists` will return :ref:`ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY <ze-result-t>`

2. Explicit :ref:`zeContextMakeMemoryResident` APIs are included for the application to dynamically change residency as needed.

    + If the application over-commits device memory, then a call to :ref:`zeContextMakeMemoryResident` will return :ref:`ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY <ze-result-t>`

If the application does not properly manage residency for these cases then the device may experience unrecoverable page-faults.

The following pseudo-code demonstrates a sequence for using coarse-grain residency control for indirect arguments:

.. parsed-literal::

       struct node {
           node* next;
       };
       node* begin = nullptr;
       :ref:`zeMemAllocHost`\(hContext, &desc, sizeof(node), 1, &begin);
       :ref:`zeMemAllocHost`\(hContext, &desc, sizeof(node), 1, &begin->next);
       :ref:`zeMemAllocHost`\(hContext, &desc, sizeof(node), 1, &begin->next->next);

       // 'begin' is passed as kernel argument and appended into command list
       :ref:`zeKernelSetIndirectAccess`\(hKernel, :ref:`ZE_KERNEL_INDIRECT_ACCESS_FLAG_HOST <ze-kernel-indirect-access-flags-t>`\);
       :ref:`zeKernelSetArgumentValue`\(hKernel, 0, sizeof(node*), &begin);
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);

       ...

       :ref:`zeCommandQueueExecuteCommandLists`\(hCommandQueue, 1, &hCommandList, nullptr);
       ...

The following pseudo-code demonstrates a sequence for using fine-grain residency control for indirect arguments:

.. parsed-literal::

       struct node {
           node* next;
       };
       node* begin = nullptr;
       :ref:`zeMemAllocHost`\(hContext, &desc, sizeof(node), 1, &begin);
       :ref:`zeMemAllocHost`\(hContext, &desc, sizeof(node), 1, &begin->next);
       :ref:`zeMemAllocHost`\(hContext, &desc, sizeof(node), 1, &begin->next->next);

       // 'begin' is passed as kernel argument and appended into command list
       :ref:`zeKernelSetArgumentValue`\(hKernel, 0, sizeof(node*), &begin);
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &launchArgs, nullptr, 0, nullptr);
       ...

       // Make indirect allocations resident before enqueuing
       :ref:`zeContextMakeMemoryResident`\(hContext, hDevice, begin->next, sizeof(node));
       :ref:`zeContextMakeMemoryResident`\(hContext, hDevice, begin->next->next, sizeof(node));

       :ref:`zeCommandQueueExecuteCommandLists`\(hCommandQueue, 1, &hCommandList, hFence);

       // wait until complete
       :ref:`zeFenceHostSynchronize`\(hFence, UINT32_MAX);

       // Finally, evict to free device resources
       :ref:`zeContextEvictMemory`\(hContext, hDevice, begin->next, sizeof(node));
       :ref:`zeContextEvictMemory`\(hContext, hDevice, begin->next->next, sizeof(node));
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
format binaries, see :ref:`zeModuleGetNativeBinary` and :ref:`ZE_MODULE_FORMAT_NATIVE <ze-module-format-t>`\.

The following pseudo-code demonstrates interoperability with OpenCL *from* a OpenCL cl_program *to* a Level-Zero Kernel:

.. parsed-literal::

        void* clDeviceBinary;
        size_t clDeviceBinarySize;
        clGetProgramInfo(cl_program, CL_PROGRAM_BINARIES, clDeviceBinary, &clDeviceBinarySize);

        :ref:`ze-module-desc-t` desc = {
            :ref:`ZE_STRUCTURE_TYPE_MODULE_DESC <ze-structure-type-t>`\,
            nullptr,
            :ref:`ZE_MODULE_FORMAT_NATIVE <ze-module-format-t>`\,
            clDeviceBinarySize,
            clDeviceBinary
        };
        :ref:`zeModuleCreate`\(hContext, hDevice, &desc, &hModule, nullptr);
        :ref:`zeKernelCreate`\(hModule, nullptr, hKernel); // same Kernel as OpenCL in Level-Zero


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
       :ref:`zeMemAllocDevice`\(hContext, &desc, size, alignment, hDevice, &dptr);

       :ref:`ze-ipc-mem-handle-t` hIPC;
       :ref:`zeMemGetIpcHandle`\(hContext, dptr, &hIPC);

       // Method of sending to receiving process is not defined by Level-Zero:
       send_to_receiving_process(hIPC);
       

2. Next, the allocation is received and un-packaged on the receiving
   process:

.. parsed-literal::

       // Method of receiving from sending process is not defined by Level-Zero:
       :ref:`ze-ipc-mem-handle-t` hIPC;
       hIPC = receive_from_sending_process();

       void* dptr = nullptr;
       :ref:`zeMemOpenIpcHandle`\(hContext, hDevice, hIPC, 0, &dptr);
       

3. Each process may now refer to the same device memory allocation via its ``dptr``.
   Note, there is no guaranteed address equivalence for the values of ``dptr`` in each process.

4. To cleanup, first close the handle in the receiving process:

.. parsed-literal::

       :ref:`zeMemCloseIpcHandle`\(hContext, dptr);
       

5. Finally, return the IPC handle to the driver with  :ref:`zeMemPutIpcHandle` and
   free the device pointer in the sending process. If :ref:`zeMemPutIpcHandle` is not called,
   any actions performed by that call are eventually done by :ref:`zeMemFree`\.

.. parsed-literal::

       :ref:`zeMemPutIpcHandle`\(hContext, hIpc);
       :ref:`zeMemFree`\(hContext, dptr);

.. _events-1:

Events
~~~~~~

The following code examples demonstrate how to use the event IPC APIs:

1. First, the event pool is created, packaged, and sent on the sending process:

.. parsed-literal::

       // create event pool
       :ref:`ze-event-pool-desc-t` eventPoolDesc = {
           :ref:`ZE_STRUCTURE_TYPE_EVENT_POOL_DESC <ze-structure-type-t>`\,
           nullptr,
           :ref:`ZE_EVENT_POOL_FLAG_IPC <ze-event-pool-flags-t>` | :ref:`ZE_EVENT_POOL_FLAG_HOST_VISIBLE <ze-event-pool-flags-t>`\,
           10 // count
       };
       ze_event_pool_handle_t hEventPool;
       :ref:`zeEventPoolCreate`\(hContext, &eventPoolDesc, 1, &hDevice, &hEventPool);

       // get IPC handle and send to another process
       :ref:`ze-ipc-event-pool-handle-t` hIpcEvent;
       :ref:`zeEventPoolGetIpcHandle`\(hEventPool, &hIpcEventPool);
       send_to_receiving_process(hIpcEventPool);

2. Next, the event pool is received and un-packaged on the receiving process:

.. parsed-literal::

       // get IPC handle from other process
       :ref:`ze-ipc-event-pool-handle-t` hIpcEventPool;
       receive_from_sending_process(&hIpcEventPool);

       // open event pool
       ze_event_pool_handle_t hEventPool;
       :ref:`zeEventPoolOpenIpcHandle`\(hContext, hIpcEventPool, &hEventPool);

3. Each process may now refer to the same device event allocation via its handle:

Receiving process creates event at location

.. parsed-literal::

       ze_event_handle_t hEvent;
       :ref:`ze-event-desc-t` eventDesc = {
           :ref:`ZE_STRUCTURE_TYPE_EVENT_DESC <ze-structure-type-t>`\,
           nullptr,
           5, // index
           0, // no additional memory/cache coherency required on signal
           :ref:`ZE_EVENT_SCOPE_FLAG_HOST <ze-event-scope-flags-t>`\, // ensure memory coherency across device and Host after event signaled
       };
       :ref:`zeEventCreate`\(hEventPool, &eventDesc, &hEvent);

       // submit kernel and signal event when complete
       :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &args, hEvent, 0, nullptr);
       :ref:`zeCommandListClose`\(hCommandList);
       :ref:`zeCommandQueueExecuteCommandLists`\(hCommandQueue, 1, &hCommandList, nullptr);

Sending process creates event at same location

.. parsed-literal::

       ze_event_handle_t hEvent;
       :ref:`ze-event-desc-t` eventDesc = {
           :ref:`ZE_STRUCTURE_TYPE_EVENT_DESC <ze-structure-type-t>`\,
           nullptr,
           5,
           0, // no additional memory/cache coherency required on signal
           :ref:`ZE_EVENT_SCOPE_FLAG_HOST <ze-event-scope-flags-t>`\, // ensure memory coherency across device and Host after event signaled
       };
       :ref:`zeEventCreate`\(hEventPool, &eventDesc, &hEvent);

       :ref:`zeEventHostSynchronize`\(hEvent, UINT32_MAX);


Note, there is no guaranteed address equivalence for the values of ``hEvent`` in each process.

4. To cleanup, first close the pool handle in the receiving process:

.. parsed-literal::

       :ref:`zeEventDestroy`\(hEvent);
       :ref:`zeEventPoolCloseIpcHandle`\(&hEventPool);

5. Finally, return the IPC handle to the driver with :ref:`zeEventPoolPutIpcHandle` and
   free the event pool in the sending process. If :ref:`zeEventPoolPutIpcHandle` is not called,
   any actions performed by that call are eventually done by :ref:`zeEventPoolDestroy`\.

.. parsed-literal::

       :ref:`zeEventDestroy`\(hEvent);
       :ref:`zeEventPoolPutIpcHandle`\(hContext, hIpcEventPool);
       :ref:`zeEventPoolDestroy`\(hEventPool);

Peer-to-Peer Access and Queries
-------------------------------

Peer to Peer API's provide capabilities to marshal data across Host to
Device, Device to Host and Device to Device. The data marshalling API
can be scheduled as asynchronous operations or can be synchronized with
kernel execution through command queues. Data coherency is maintained by
the driver without any explicit involvement from the application.

Cards may be linked together within a node by a scale-up fabric and depending on the configuration,
the fabric can support remote access, atomics, and data copies.

The following Peer-to-Peer functionalities are provided through the API:

- Check for remote memory access capability between two devices/subdevices: :ref:`zeDeviceCanAccessPeer`

       The following rules apply to :ref:`zeDeviceCanAccessPeer` queries

       + A device/subdevice is always its own peer, i.e. it can always access itself.

- Query remote memory access, atomic capabilities, logical & physical bandwidth & latency for peer-to-peer: :ref:`zeDeviceGetP2PProperties` + :ref:`ZE_experimental_bandwidth_properties`.

       The following rules apply to :ref:`zeDeviceGetP2PProperties` queries

       + A device/subdevice is always its own peer, i.e. it can always access itself and also do so atomically.

- Copy data between devices over peer-to-peer fabric: :ref:`zeCommandListAppendMemoryCopy`

Both :ref:`zeDeviceCanAccessPeer` & :ref:`zeDeviceGetP2PProperties` return the same information - do two devices support peer-to-peer access? :ref:`zeDeviceGetP2PProperties` provides more detail than :ref:`zeDeviceCanAccessPeer`\, such as support for atomics, bandwidths, latencies, etc...

