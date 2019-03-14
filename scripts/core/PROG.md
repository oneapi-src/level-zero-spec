${"#"} Programming Guide (Core)

[DO NOT EDIT]: # (generated from /scripts/core/PROG.md)

The following documents the high-level programming models and guidelines.  

NOTE: This is a **PRELIMINARY** specification, provided for review and feedback.

${"##"} Table of Contents
* [Driver and Device](#dnd)
* [Command Queues and Command Lists](#cnc)
* [Barriers](#brr)
* [Synchronization Primitives](#sp)
* [Memory and Image Management](#mim)
* [Modules and Functions](#mnf)
* [OpenCL Interoperability](#oi)
* [Inter-Process Communication](#ipc)
* [Experimental](#exp)
* [Debug and Instrumentation Layers](#dbg)
* [Future](#fut)

${"#"} <a name="dnd">Driver and Device</a>
The following diagram illustrates the hierarchy of devices to the driver:  
![Driver](../images/core_driver.png?raw=true)  
@image latex core_driver.png

${"##"} Driver
A driver represents an instance of a ${Xx} driver being loaded and initialized into the current process.
- Only one instance of a driver per process can be loaded.
- Multiple calls to ::${x}DriverInit are silently ignored.
- A driver has minimal global state associated; only that which is sufficient for querying devices recognized by the driver.
- There is no explicit unload or shutdown of the driver.
- Any global resources acquired during ::${x}DriverInit will be released during process detach.

${"##"} Device
A device represents a physical device in the system that can support ${Xx}.
- More than one device may be available in the system.
- The driver will only report devices that are recognized by the driver.
- The application is responsible for sharing memory and explicit submission and synchronization across multiple devices.
- Device can expose sub-devices that allow finer-grained control of multi-tile devices.

${"##"} Initialization
The driver must be initizalized by calling ::${x}DriverInit before any other function.
This function will query the available physical adapters in the system and make this information available to all threads in the current process.

The following sample code demonstrates a basic initialization sequence:
```c
    // NOTE: Sample code in this document contains little or no error checking for brevity and clarity.
    //       However, proper error checking is highly recommended and necessary in many cases.

    // Initialize the driver
    ${x}DriverInit(${X}_INIT_FLAG_NONE);

    // Get number of devices supporting ${Xx}
    uint32_t deviceCount = 0;
    ${x}DriverGetDeviceCount(&deviceCount);
    if(0 == deviceCount)
    {
        printf("There is no device supporting ${Xx}!\n");
        return;
    }

    ${x}_device_uuid_t* pUUIDs = (uint32_t*)malloc(deviceCount * sizeof(${x}_device_uuid_t));
    ${x}DriverGetDeviceUniqueIds(deviceCount, pUUIDs);

    // Get the handle for device that supports required API version
    ${x}_device_handle_t hDevice;
    for(uint32_t i = 0; i < deviceCount; ++i)
    {
        ${x}DriverGetDevice(pUUIDs[i], &hDevice);
        
        ${x}_api_version_t version;
        ${x}DeviceGetApiVersion(hDevice, &version);
        if(${X}_API_VERSION_1_0 <= version)
            break;

        if(i == deviceCount)
        {
            printf("There is no device that supporting ${Xx} version required!\n");
            return;
        }
    }
    ...

```
${"##"} Sub-Device Support
A multi-tile device consists of tiles that are tied together by high-speed interconnects. Each tile
has local memory that is shared to other tiles through these interconnects. The API represents tiles
as sub-devices and there are functions to query and obtain a sub-device. Outside of these functions
there are no distinction between sub-devices and devices. 

![Subdevice](../images/core_subdevice.png?raw=true)  
@image latex core_subdevice.png

Query device properties using ::${x}DeviceGetProperties to confirm subdevices are supported with
::${x}_device_properties_t.numSubDevices. Use ::${x}DeviceGetSubDevice to obtain a sub-device handle.
There are additional device properties in ::${x}_device_properties_t for sub-devices to confirm a
device is a sub-device and to query the id. This is useful when needing to pass a sub-device
handle to another library.

To allocate memory and dispatch tasks to a particular sub-device then obtain the sub-device
handle and use this with memory and command queue/lists APIs. One thing to note is that the ordinal
that is used when creating a command queue is relative to the sub-device. This ordinal specifies which
physical compute queue on the device or sub-device to map the logical queue to. You need to query
::${x}_device_properties_t.numAsyncComputeEngines from the sub-device to determine how to set this ordinal.
See ::${x}_command_queue_desc_t for more details.

```c
    ...
    ${x}DeviceGetProperties(device, &deviceProps);
    ...

    // Code assumes a specific device configuration.
    assert(deviceProps.numSubDevices == 4);

    // Desire is to allocate and dispatch work to sub-device 2.
    uint32_t subdeviceId = 2;
    ${x}DeviceGetSubDevice(device, subdeviceId, &subdevice);

    // Query sub-device properties.
    ${x}_device_properties_t subdeviceProps;
    ${x}DeviceGetProperties(subdevice, &subdeviceProps);

    assert(subdeviceProps.isSubdevice == true); // Ensure that we have a handle to a sub-device.
    assert(subdeviceProps.subdeviceId == 2);    // Ensure that we have a handle to the sub-device we asked for.

    ...
    ${x}_mem_allocator_handle_t hAllocator;
    ${x}CreateMemAllocator(hAllocator);

    void* pMemForSubDevice2;
    ${x}MemAlloc(hAllocator, subDevice, ${X}_DEVICE_MEM_ALLOC_FLAG_DEFAULT, memSize, sizeof(uint32_t), &pMemForSubDevice2);
    ...

    ...
    // Check that cmd queue ordinal that was chosen is valid.
    assert(desc.ordinal < subdeviceProps.numAsyncComputeEngines);

    ${x}_command_queue_handle_t commandQueueForSubDevice2;
    ${x}DeviceCreateCommandQueue(subdevice, desc, &commandQueueForSubDevice2);
    ...
```

${"#"} <a name="cnc">Command Queues and Command Lists</a>
The following are the motivations for seperating a command queue from a command list:
- Command queues are mostly associated with physical device properties,
  such as the number of input streams.
- Command queues provide (near) zero-latency access to the device.
- Command lists are mostly associated with Host threads for simultaneous construction.
- Command list encodeing can occur independently of command queue submission.
- Command list submission can occur to more than one command queue.

The following diagram illustrates the hierarchy of command lists and command queues to the device:  
![Queue](../images/core_queue.png?raw=true)  
@image latex core_queue.png

${"##"} Command Queues
A command queue represents a logical input stream to the device, tied to a physical input
stream via an ordinal at creation time.

${"###"} Creation
- The application may explicitly bind the command queue to a physical input stream, or
  allow the driver to choose dynamically, based on usage.
- Multiple command queues may be created that use the same physical input stream. For example,
  an application may create a command queue per Host thread with different scheduling priorities.
- However, an application should avoid creating multiple command queues for the same physical
  input stream with the same priority due to possible performance penalties with hardware
  context switching.
- The number of simultaneous compute command queues per device is queried from 
  ::${x}_device_properties_t.numAsyncComputeEngines.
- The number of simultaneous copy command queues per device is queried from 
  ::${x}_device_properties_t.numAsyncCopyEngines.

The following sample code demonstrates a basic sequence for creation of command queues:
```c
    // Create a command queue
    ${x}_command_queue_desc_t commandQueueDesc = {
        ${X}_COMMAND_QUEUE_DESC_VERSION_CURRENT,
        ${X}_COMMAND_QUEUE_FLAG_NONE,
        ${X}_COMMAND_QUEUE_MODE_DEFAULT,
        ${X}_COMMAND_QUEUE_PRIORITY_NORMAL,
        0
    };
    ${x}_command_queue_handle_t hCommandQueue;
    ${x}DeviceCreateCommandQueue(hDevice, &commandQueueDesc, &hCommandQueue);
    ...
```

${"###"} Execution
- Command lists submitted to a command queue are **immediately** executed in a fifo manner.
- Command queue submission is free-treaded, allowing multiple Host threads to
  share the same command queue.
- If multiple Host threads enter the same command queue simultaneously, then execution order
  is undefined.
- Command lists created with ::${X}_COMMAND_LIST_FLAG_COPY_ONLY may only be submitted to
  command queues created with ::${X}_COMMAND_QUEUE_FLAG_COPY_ONLY.

${"###"} Destruction
- The application is responsible for making sure the device is not currently
  executing from a command queue before it is deleted.  This is 
  typically done by tracking command queue fences, but may also be
  handled by calling ::${x}CommandQueueSynchronize.

${"##"} Command Lists
A command list represents a sequence of commands for execution on a command queue.

${"###"} Creation
- A command list is created for a device to allow device-specific encoding of commands.
- A command list can be copied to create another command list. The application may use this
  to copy a command list for use on a different device.

${"###"} Encoding
- There is no implicit binding of command lists to Host threads. Therefore, an 
  application may share a command list handle across multiple Host threads. However,
  the application is responsible for ensuring that multiple Host threads do not access
  the same command list simultaneously.
- By default, commands are executed in the same order in which they are submitted.
  However, an application may allow the driver to optimize the ordering by using
  ::${X}_COMMAND_LIST_FLAG_RELAXED_ORDERING.  Reordering is guarenteed to be only occur
  between barriers and synchronization primitives.
- The command list maintains some machine state, which is inherited by subsequent
  commands. See ::${x}_command_list_parameter_t for details.
- A command list can be called from another command list (nested). In this case, state
  may be inherited and leaked by the nested command list.

The following sample code demonstrates a basic sequence for creation of command lists:
```c
    // Create a command list
    ${x}_command_list_desc_t commandListDesc = {
        ${X}_COMMAND_LIST_DESC_VERSION_CURRENT,
        ${X}_COMMAND_LIST_FLAG_NONE
    };
    ${x}_command_list_handle_t hCommandList;
    ${x}DeviceCreateCommandList(hDevice, &commandListDesc, &hCommandList);
    ...
```

${"###"} Submission
- There is no implicit association between a command list and a command queue. 
  Therefore, a command list may be submitted to any, or multiple command queues.
  However, if a command list is meant to be submitted to a copy-only command queue
  then the ::${X}_COMMAND_LIST_FLAG_COPY_ONLY must be set at creation.
- The application is responsible for calling close before submission to a command queue.
- Command lists do not inherit state from other command lists executed on the same
  command queue.  i.e. each command list begins execution in its own default state.

The following sample code demonstrates submission of commands to a command queue, via a command list:
```c
    ...
    // finished encoding commands (typically done on another thread)
    ${x}CommandListClose(hCommandList);

    // Enqueue command list execution into command queue
    ${x}CommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

    // synchronize host and device
    ${x}CommandQueueSynchronize(hCommandQueue, MAX_UINT32);

    // Reset (recycle) command list for new commands
    ${x}CommandListReset(hCommandList);
    ...
```

${"###"} Recycling
- A command list may be recycled to avoid the overhead of frequent creation and destruction.
- The application is responsible for making sure the device is not currently
  executing from a command list before it is reset.  This should be
  handled by tracking a completion event associated with the command list.
- The application is responsible for making sure the device is not currently
  executing from a command list before it is deleted.  This should be
  handled by tracking a completion event associated with the command list.

${"#"} <a name="brr">Barriers</a>
There are two types of barriers:
1. **Execution Barriers** - used to insert execution dependency between commands _within_ a command list.
2. **Memory Barriers** - used to insert a dependency between memory access across command queues, devices or Host.

${"##"} Execution Barriers
- Commands submitted to a command list are only guarenteed to start in the same order in which they are submitted;
  there is no implicit control of which order they complete.
- Execution barriers provide explicit control to indicate that previous commands must complete prior to
  starting the following commands.
- Execution barriers are implicitly added by the driver after each batch of command lists submitted to a command queue.
- Execution barriers are implicitly added by the driver prior to synchronization primitives.

The following sample code demonstrates a sequence for submission of an execution barrier:
```c
    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, &dispatchArgs, nullptr);

    // Encode a barrier into a command list to ensure hFunctionFunction1 completes before hFunction2 begins
    ${x}CommandListEncodeExecutionBarrier(hCommandList);

    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, &dispatchArgs, nullptr);
    ...
```

${"##"} Memory Barriers
- Memory barriers are implicitly added by the driver after each batch of command lists submitted to a command queue.
- Memory barriers are implicitly added by the driver prior to synchronization primitives.

${"#"} <a name="sp">Synchronization Primitives</a>
There are two types of synchronization primitives:
1. [**Fences**](#fnc) - used to communicate to the host that command queue execution has completed.
2. [**Events**](#evnt) - used as fine-grain host-to-device, device-to-host or device-to-device waits and signals within a command list.

The following diagram illustrats the relationship of capabilities of these types of synchronization primitives:  
![Graph](../images/core_sync.png?raw=true)  
@image latex core_sync.png

The following are the motivations for seperating the different types of synchronization primitives:
- Allows device-specific optimizations for certain types of primitives:
    + fences may share device memory with all other fences for the queue or device.
    + events may be implemented using pipelined operations as part of the program execution.
    + fences and events implicitly cause execution and memory barriers.
- Allows distinction on which type of primitive may be shared across devices.

${"##"} <a name="fnc">Fences</a>
A fence is a lightweight synchronization primitive used to communicate to the host that command queue execution has completed.
- A fence is associated with single command queue.
- A fence can only be signaled from a device's command queue (e.g. between execution of command lists)
  and can only be waited upon from the host.
- A fence only has two states: not signaled and signaled.
- A fence can only be reset from the Host.
- A fence cannot be shared across processes.

The primary usage model(s) for fences are to notify the Host when a command list has finished execution to allow:
- Recycling of memory and images
- Recycling of command lists
- Recycling of other synchronization primitives
- Explicit memory residency.

The following diagram illustrates an example of fences:  
![Fence](../images/core_fence.png?raw=true)  
@image latex core_fence.png

The following sample code demonstrates a sequence for creation, submission and querying of a fence:
```c
    // Create fence
    ${x}_fence_desc_t fenceDesc = {
        ${X}_FENCE_DESC_VERSION_CURRENT,
        ${X}_FENCE_FLAG_NONE
    };
    ${x}_fence_handle_t hFence;
    ${x}CommandQueueCreateFence(hCommandQueue, &fenceDesc, &hFence);

    // Enqueue a signal of the fence into the command queue
    ${x}CommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, hFence);

    // Wait for fence to be signaled
    ${x}FenceHostSynchronize(hFence, MAX_UINT32);
    ${x}FenceReset(hFence);
    ...
```

${"##"} <a name="evnt">Events</a>
An event is used as fine-grain host-to-device, device-to-host or device-to-device waits and signals from within a command list.
- An event can be __either__:
  + signaled from within a device's command list (e.g. between execution of kernels) and waited upon from the host, another command queue or another device, **or**
  + signaled from the host, and waited upon from within a device's command list.
- An event only has two states: not signaled and signaled.
- An event can be reset from the Host or device.
- An event can be encoded into any command list from the same device.
- An event cannot be signaled and waited upon in the same command list or command queue.
- An event can be encoded into multiple command lists simultaneously.
- An event can be shared across processes.
- An event imposes an implicit execution and memory barrier; therefore should be used sparingly to avoid device underutilization.
- There are no protections against events causing deadlocks, such as circular waits scenarios. 
  + These problems are left to the application to avoid.
- An event intended to be signaled by the host, another command queue or another device after command list submission to a command queue may prevent 
  subsequent forward progress within the command queue itself.
  + This can create create bubbles in the pipeline or deadlock situations if not correctly scheduled.

Events are generic synchronization primitives that can be used across many different usage-models, includes those of fences and semaphores.
However, this generality comes with some cost in efficiency.

Events do **not** represent intra-command list dependencies between programs.

The following diagram illustrates an example of events:  
![Event](../images/core_event.png?raw=true)  
@image latex core_event.png

The following sample code demonstrates a sequence for creation and submission of an event:
```c
    // Create event
    ${x}_event_desc_t eventDesc = {
        ${X}_EVENT_DESC_VERSION_CURRENT,
        ${X}_EVENT_FLAG_NONE
    };
    ${x}_event_handle_t hEvent;
    ${x}DeviceCreateEvent(hDevice, &eventDesc, &hEvent);

    // Encode a wait on an event into a command list
    ${x}CommandListEncodeWaitOnEvent(hCommandList, hEvent);

    // Enqueue wait via the command list into a command queue
    ${x}CommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

    // Signal the device
    ${x}EventHostSignal(hEvent);
    ...
```

${"##"} Performance Metrics
Events can be used to provide different types of device performance metrics:
1. Timestamps - records the value of the device timer at the completion of the event.
2. Counters - records a collection of device-specific counters at the completion of the event.

${"###"} Timestamps
Timestamps are used to measure the time between two events signalled by the same device.
- An application can use ::${x}EventQueryElapsedTime to calculate the time (in milliseconds) between two events.
- Both events must be created with ::${X}_EVENT_FLAG_TIMESTAMP
- Both events must be signalled

The following sample code demonstrates a sequence for measuring time between events:
```c
    // Encode the function call to measure
    ${x}CommandListEncodeSignalEvent(hCommandList, hEventBegin);
    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, &dispatchArgs, hEventEnd);

    // Enqueue the command list into a command queue
    ${x}CommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

    // Wait for the last event to complete
    ${x}EventHostSynchronize(hEventEnd, MAX_UINT32);

    // calculate the delta time
    double time = 0.f;
    ${x}EventQueryElapsedTime(hEventBegin, hEventEnd, &time);
    ...
```

${"###"} Counters
Counters are used to collect various device-specific values between two events signalled by the same device.
- An application can use ::${x}EventQueryMetricsData to calculate the time (in milliseconds) between two events.
- Both events must be created with ::${X}_EVENT_FLAG_PERFORMANCE_METRICS
- Both events must be signalled

The following sample code demonstrates a sequence for collecting counters between events:
```c
    // Encode the function call to measure
    ${x}CommandListEncodeSignalEvent(hCommandList, hEventBegin);
    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, &dispatchArgs, hEventEnd);

    // Enqueue the command list into a command queue
    ${x}CommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

    // Wait for the last event to complete
    ${x}EventHostSynchronize(hEventEnd, MAX_UINT32);

    // calculate the delta counter values
    uint32_t counters[64] = {};
    ${x}EventQueryMetricsData(hEventBegin, hEventEnd, sizeof(counters), &counters);
    ...
```

${"#"} <a name="mim">Memory and Image Management</a>
There are two types of allocations:
1. **Memory** - linear, unformatted allocations for direct access from both the host and device.
2. **Images** - non-linear, formatted allocations for direct access from the device.

${"##"} Memory
Linear, unformatted memory allocations are represented as pointers in the host application.
A pointer on the host has the same size as a pointer on the device.

Three types of allocations are supported.
The type of allocation describes the _ownership_ of the allocation:
1. **Host** allocations are owned by the host and are intended to be allocated out of system memory.
  Host allocations are accessible by the host and one or more devices.
  The same pointer to a host allocation may be used on the host and all supported devices; they have _address equivalence_.
  Host allocations are not expected to migrate between system memory and device local memory.
  Host allocations trade off wide accessibility and transfer benefits for potentially higher per-access costs, such as over PCI express.
2. **Device** allocations are owned by a specific device and are intended to be allocated out of device local memory, if present.
  Device allocations generally trade off access limitations for higher performance.
  With very few exceptions, device allocations may only be accessed by the specific device that they are allocated on, or copied to a host or another device allocation.
  The same pointer to a device allocation may be used on any supported device.
3. **Shared** allocations share ownership and are intended to migrate between the host and one or more devices.
  Shared allocations are accessible by at least the host and an associated device.
  Shared allocations may be accessed by other devices in some cases.
  Shared allocations trade off transfer costs for per-access benefits.
  The same pointer to a shared allocation may be used on the host and all supported devices.

A **Shared System** allocation is a sub-class of a **Shared** allocation, where the memory is allocated by a _system allocator_ - such as `malloc` or `new` - rather than by a driver allocation API.
Shared system allocations have no associated device - they are inherently cross-device.
Like other shared allocations, shared system allocations are intended to migrate between the host and supported devices, and the same pointer to a shared system allocation may be used on the host and all supported devices.

In summary:
| Name | Initial Location | Accessible By || Migratable To ||
| :--: | :--: | :--: | :--: | :--: | :--: |
| **Host** | Host | Host | Yes | Host | N/A |
| ^ | ^ | Any Device | Yes (perhaps over PCIe) | Device | No |
| **Device** | Specific Device | Host | No | Host | No |
| ^ | ^ | Specific Device | Yes | Device | N/A |
| ^ | ^ | Another Device | Optional (may require p2p) | Another Device | No |
| **Shared** | Host, or Specific Device, Or Unspecified | Host | Yes | Host | Yes |
| ^ | ^ | Specific Device | Yes | Device | Yes |
| ^ | ^ | Another Device | Optional (may require p2p) | Another Device | Optional |
| **Shared System** | Host | Host | Yes | Host | Yes |
| ^ | ^ | Device | Yes | Device | Yes |

Devices may support different capabilities for each type of allocation.
Supported capabilities are:
* ::${X}_MEMORY_ACCESS - if a device supports access (read or write) to allocations of the specified type.
* ::${X}_MEMORY_ATOMIC_ACCESS - if a device support atomic access to allocations of the specified type.
* ::${X}_MEMORY_CONCURRENT_ACCESS - if a device supports concurrent access to allocations of the specified type, or another device's allocation of the specified type.
* ::${X}_MEMORY_CONCURRENT_ATOMIC_ACCESS - if a device supports concurrent atomic access to allocations of the specified type, or another device's allocations of the specified type.

Some devices may _oversubscribe_ some **shared** allocations.
When and how such oversubscription occurs, including which allocations are evicted when the working set changes, are considered implementation details.

The required matrix of capabilities are:
| Allocation Type                  | Access   | Atomic Access | Concurrent Access | Concurrent Atomic Access |
| :--:                             | :--:     | :--:          | :--:              | :--:                     |
| **Host**                         | Required | Optional      | Optional          | Optional                 |
| **Device**                       | Required | Optional      | Optional          | Optional                 |
| **Shared**                       | Required | Optional      | Optional          | Optional                 |
| **Shared** (Cross-Device)        | Optional | Optional      | Optional          | Optional                 |
| **Shared System** (Cross-Device) | Optional | Optional      | Optional          | Optional                 |

${"###"} Cache Hints, Prefetch, and Memory Advice
Cacheability hints may be provided via separate host and device allocation flags when memory is allocated.

**Shared** allocations may be prefetched to a supporting device via the ::${x}CommandListEncodeMemoryPrefetch API.
Prefetching may allow memory transfers to be scheduled concurrently with other computations and may improve performance.

Additionally, an application may provide memory advice for a **shared** allocation via the ::${x}CommandListEncodeMemAdvise API, to override driver heuristics or migration policies.
Memory advice may avoid unnecessary or unprofitable memory transfers and may improve performance.

Both prefetch and memory advice are asynchronous operations that are encoded into command lists.

${"##"} Images
An image is used to store multi-dimensional and format-defined memory for optimal device access.
An image's contents can be copied to and from other images, as well as host-accessable memory allocations.
This is the only method for host access to the contents of an image.
This methodology allows for device-specific encoding of image contents (e.g., tile swizzle patterns, loseless compression, etc.) 
and avoids exposing these details in the API in a backwards compatible fashion.

```c
    ${x}_image_desc_t imageDesc = {
        ${X}_IMAGE_DESC_VERSION_CURRENT,
        ${X}_IMAGE_FLAG_PROGRAM_READ,
        ${X}_IMAGE_TYPE_2D,
        ${X}_IMAGE_FORMAT_FLOAT32, 1,
        128, 128, 0, 0, 0
    };
    ${x}_image_handle_t hImage;
    ${x}DeviceCreateImage(hDevice, &imageDesc, &hImage);

    // upload contents from host pointer
    ${x}CommandListEncodeImageCopyFromMemory(hCommandList, hImage, nullptr, pImageData);
    ...
```

${"##"} Device Cache Settings
For device support cache control and config, there are two methods for cache control:
1. Cache Size Configuration: Ability to configure larger size for SLM vs Data globally for Device
2. Runtime Hint/prefrence for application to allow access to be Cached or not in Device Caches. For GPU device this is provided via two ways  
      -  During Image creation via Flag
      -  Kernel instruction 

The following sample code demonstrates a basic sequence for Cache size configuration:
```c
    // Large SLM for Intermediate and Last Level cache
    ${x}DeviceSetIntermediateCacheConfig(hDevice, ${X}_CACHE_CONFIG_LARGE_SLM);
    ${x}DeviceSetLastLevelCacheConfig(hDevice, ${X}_CACHE_CONFIG_LARGE_SLM);
    ...
```
The following sample code demonstrates a basic sequence for Runtime Hint/Prefrence for Cache:

${"##"} Device Residency
For devices that do not support page-faults, the driver must ensure that all pages that will be accessed by the kernel are resident before program execution.
This can be determined by checking ::${x}_device_memory_properties_t.onDemandPageFaults.

In most cases, the driver implicitly handles residency of allocations for device access.
This can be done by inspecting API parameters, including function arguments.
However, in cases where the devices does **not** support page-faulting _and_ the driver is incapable of determining whether an allocation will be accessed by the device,
such as multiple levels of indirection, there are two methods available:
1. the application may set the ::${X}_FUNCTION_FLAG_FORCE_RESIDENCY flag during program creation to force all device allocations to be resident during execution.
 + in addition, the application should indicate the type of allocations that will be indirectly accessed using ::${x}_function_set_attribute_t
 + if the driver is unable to make all allocations resident, then the call to ::${x}CommandQueueEnqueueCommandLists will return ${X}_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
2. explcit ::${x}DeviceMakeMemoryResident APIs are included for the application to dynamically change residency as needed. (Windows-only)
 + if the application over-commits device memory, then a call to ::${x}DeviceMakeMemoryResident will return ${X}_RESULT_ERROR_OUT_OF_DEVICE_MEMORY

If the application does not properly manage residency for these cases then the device may experience unrecoverable page-faults.

The following sample code demonstrate a sequence for using coarse-grain residency control for indirect arguments:
```c
    struct node {
        node* next;
    };
    node* begin = nullptr;
    ${x}HostMemAlloc(hAllocator, ${X}_HOST_MEM_ALLOC_FLAG_DEFAULT, sizeof(node), 1, &begin);
    ${x}HostMemAlloc(hAllocator, ${X}_HOST_MEM_ALLOC_FLAG_DEFAULT, sizeof(node), 1, &begin->next);
    ${x}HostMemAlloc(hAllocator, ${X}_HOST_MEM_ALLOC_FLAG_DEFAULT, sizeof(node), 1, &begin->next->next);

    // 'begin' is passed as function argument and encoded into command list
    ${x}FunctionSetAttribute(hFuncArgs, ${X}_FUNCTION_SET_ATTR_INDIRECT_HOST_ACCESS, TRUE);
    ${x}FunctionSetArgumentValue(hFunction, 0, sizeof(node*), &begin);
    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, &dispatchArgs, nullptr);
    ...

    ${x}CommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, nullptr);
    ...
```

The following sample code demonstrate a sequence for using fine-grain residency control for indirect arguments:
```c
    struct node {
        node* next;
    };
    node* begin = nullptr;
    ${x}HostMemAlloc(hAllocator, ${X}_HOST_MEM_ALLOC_FLAG_DEFAULT, sizeof(node), 1, &begin);
    ${x}HostMemAlloc(hAllocator, ${X}_HOST_MEM_ALLOC_FLAG_DEFAULT, sizeof(node), 1, &begin->next);
    ${x}HostMemAlloc(hAllocator, ${X}_HOST_MEM_ALLOC_FLAG_DEFAULT, sizeof(node), 1, &begin->next->next);

    // 'begin' is passed as function argument and encoded into command list
    ${x}FunctionSetArgumentValue(hFunction, 0, sizeof(node*), &begin);
    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, &dispatchArgs, nullptr);
    ...

    // Make indirect allocations resident before enqueuing
    ${x}DeviceMakeMemoryResident(hDevice, begin->next, sizeof(node));
    ${x}DeviceMakeMemoryResident(hDevice, begin->next->next, sizeof(node));

    ${x}CommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, hFence);

    // wait until complete
    ${x}FenceHostSynchronize(hFence, MAX_UINT32);

    // Finally, evict to free device resources
    ${x}DeviceEvictMemory(hDevice, begin->next, sizeof(node));
    ${x}DeviceEvictMemory(hDevice, begin->next->next, sizeof(node));
    ...
```

${"#"} <a name="mnf">Modules and Functions</a>
There are multiple levels of constructs needed for executing functions on the device:
1. A [**Module**](#mod) represents a single translation unit that consists of functions that have been compiled together.
2. A [**Function**](#func) represents the function within the module that will be dispatched directly from a command list.

${"##"} <a name="mod">Modules</a>
Modules can be created from an IL or directly from native format using ::${x}DeviceCreateModule.
- ::${x}DeviceCreateModule takes a format argument that specifies the input format.
- ::${x}DeviceCreateModule performs a compilation step when format is IL.

The following sample code demonstrates a sequence for creating a module from an OpenCL function:
```c
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
```

```c
    // OpenCL C function has been compiled to SPIRV IL (pImageScalingIL)
    ${x}_module_desc_t moduleDesc = {
        ${X}_MODULE_DESC_VERSION_CURRENT,
        ${X}_MODULE_FORMAT_IL_SPIRV,
        ilSize,
        pImageScalingIL,
        nullptr
    };
    ${x}_module_handle_t hModule;
    ${x}DeviceCreateModule(hDevice, &moduleDesc, &hModule, nullptr);
    ...
```

${"###"} Module Build Options
Build options can be passed with ::${x}_module_desc_t as a string.

| Build Option                                  | Description                                           | Default  |
| :--                                           | :--                                                   | :--      |
| -${x}-opt-disable                             | Disable optimizations.                                | Disabled |
| -${x}-opt-greater-than-4GB-buffer-required    | Use 64-bit offset calculations for buffers.           | Disabled |
| -${x}-opt-large-register-file                 | Increase number of registers available to threads.    | Disabled |

${"###"} Module Build Log
The ::${x}DeviceCreateModule function can optionally generate a build log object ::${x}_module_build_log_handle_t.

```c
    ...
    ${x}_module_build_log_handle_t buildlog;
    ${x}_result_t result = ${x}DeviceCreateModule(hDevice, &desc, &module, &buildlog);

    // Only save build logs for module creation errors.
    if (result != ${X}_RESULT_SUCCESS)
    {
        uint32_t buildlogSize;
        char_t* pBuildLogString;
        result = ${x}ModuleBuildLogGetString(buildlog, &buildlogSize, &pBuildLogString);

        // Save log to disk.
        ...
    }

    ${x}ModuleBuildLogDestroy(buildlog);
```

${"###"} Module Caching with Native Binaries
Disk caching of modules is not supported by the driver. If a disk cache for modules is desired then it is the
responsibility of the application to implement this using ::${x}ModuleGetNativeBinary.

```c
    ...
    // compute hash for pIL and check cache.
    ...

    if (cacheUpdateNeeded)
    {
        uint32_t size;
        char_t* pNativeBinary;  // Pointer to native binary.
        ${x}ModuleGetNativeBinary(hModule, &size, &pNativeBinary);

        // cache pNativeBinary for corresponding IL
        ...
    }
```
Also, note that the native binary will retain all debug information that is associated with the module. This allows debug
capabilities for modules that are created from native binaries.

${"###"} Built-in Functions
Built-in functions are not supported but can be implemented by an upper level runtime or library using the native binary
interface.

${"##"} <a name="func">Functions</a>
A Function is a reference to a function within a module. The Function object supports both explicit and implicit function
arguments along with data needed for dispatch.

The following sample code demonstrates a sequence for creating a function from a module:
```c
    ${x}_function_desc_t functionDesc = {
        ${X}_FUNCTION_DESC_VERSION_CURRENT,
        ${X}_FUNCTION_FLAG_NONE,
        "image_scaling"
    };
    ${x}_function_handle_t hFunction;
    ${x}ModuleCreateFunction(hModule, &functionDesc, &hFunction);
    ...
```

${"###"} Function Attributes
Use ::${x}FunctionGetAttribute to query attributes from a function object.

```c
    ...
    uint32_t numRegisters;

    // Number of hardware registers used by function.
    ${x}FunctionGetAttribute(hFunction, ${X}_FUNCTION_GET_ATTR_MAX_REGS_USED, &numRegisters);
    ...
```
See ::${x}_function_get_attribute_t for more information on the "get" attributes.

Use ::${x}FunctionSetAttribute to set attributes from a function object.

```c
    // Function performs indirect device access.
    ${x}FunctionSetAttribute(hFunction, ${X}_FUNCTION_SET_ATTR_INDIRECT_DEVICE_ACCESS, true);
    ...
```

See ::${x}_function_set_attribute_t for more information on the "set" attributes.

${"##"} Execution

${"###"} Function Group Size
The group size for a function can be set using ::${x}FunctionSetGroupSize. If a group size is not
set prior to encoding a dispatch function into a command list then a default will be chosen.
The group size can updated over a series of encode dispatch operations. The driver will copy the
group size information when encoding the dispatch function into the command list.

```c
    ${x}FunctionSetGroupSize(function, groupSizeX, groupSizeY, 1);

    ...
```

The API supports a query for suggested group size when providing the global size. This function ignores the
group size that was set on the function using ::${x}FunctionSetGroupSize.

```c
    // Find suggested group size for processing image.
    uint32_t groupSizeX;
    uint32_t groupSizeY;
    ${x}FunctionSuggestGroupSize(function, imageWidth, imageHeight, 1, &groupSizeX, &groupSizeY, nullptr);

    ${x}FunctionSetGroupSize(function, groupSizeX, groupSizeY, 1);

    ...
```

${"###"} <a name="arg">Function Arguments</a>
Function arguments represent only the explicit function arguments that are within "brackets" e.g. func(arg1, arg2, ...).
- Use ::${x}FunctionSetArgumentValue to setup arguments for a function dispatch.
- The EncodeDispatchFunction command will make a copy the function arguments to send to the device.
- Function arguments can be updated at anytime and used across multiple dispatches.

The following sample code demonstrates a sequence for creating function args and dispatching the function:
```c
    // Bind arguments
    ${x}FunctionSetArgumentValue(hFunction, 0, sizeof(${x}_image_handle_t), &src_image);
    ${x}FunctionSetArgumentValue(hFunction, 1, sizeof(${x}_image_handle_t), &dest_image);
    ${x}FunctionSetArgumentValue(hFunction, 2, sizeof(uint32_t), &width);
    ${x}FunctionSetArgumentValue(hFunction, 3, sizeof(uint32_t), &height);

    xe_dispatch_function_arguments_t dispatchArgs = {
        pixelRegionWidth, pixelRegionHeight, 1,
        numRegionsX, numRegionsY, 1
        };

    // Encode dispatch command
    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, &dispatchArgs, nullptr);

    // Update image pointers to copy and scale next image.
    ${x}FunctionSetArgumentValue(hFunction, 0, sizeof(${x}_image_handle_t), &src2_image);
    ${x}FunctionSetArgumentValue(hFunction, 1, sizeof(${x}_image_handle_t), &dest2_image);

    // Encode dispatch command
    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, &dispatchArgs, nullptr);

    ...
```

${"###"} <a name="arg">Function Dispatch</a>
In order to invoke a function on the device you must call one of the CommandListEncodeDispatch* functions for
a command list. The most basic version of these is ::${x}CommandListEncodeDispatchFunction which takes a
command list, function, dispatch arguments, and an optional synchronization event used to signal completion.
The dispatch arguments contain group dispatch dimensions.

```c
    // compute number of groups to dispatch based on image size and function group size.
    uint32_t numGroupsX = imageWidth / groupSizeX;
    uint32_t numGroupsY = imageHeight / groupSizeY;

    ${x}_dispatch_function_arguments_t dispatchArgs = { numGroupsX, numGroupsY, 1 };

    // Encode dispatch command
    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, &dispatchArgs, nullptr);
```

::${x}CommandListEncodeDispatchFunctionIndirect allows the dispatch parameters to be supplied indirectly in a
buffer that the device reads instead of the command itself. This allows for the previous operations on the
device to generate the parameters.

```c
    ${x}_dispatch_function_arguments_t* pDispatchArgs;
    
    ...
    ${x}MemAlloc(hMemAlloc, hDevice, flags, sizeof(${x}_dispatch_function_arguments_t), sizeof(uint32_t), &pDispatchArgs);

    // Encode dispatch command
    ${x}CommandListEncodeDispatchFunctionIndirect(hCommandList, hFunction, &pDispatchArgs, nullptr);
```

${"##"} <a name="arg">Sampler</a>
The API supports Sampler objects that represent state needed for sampling images from within
Module functions.  The ::${x}DeviceCreateSampler function takes a sampler descriptor (::${x}_sampler_desc_t):

| Sampler Field    | Description                                           |
| :--              | :--                                                   |
| Address Mode     | Determines how out-of-bounds accessse are handled. See ::${x}_sampler_address_mode_t. |
| Filter Mode      | Specifies which filtering mode to use. See ::${x}_sampler_filter_mode_t               |
| Normalized       | Specifies whether coordinates for addressing image are normalized [0,1] or not.       |

The following is sample for code creating a sampler object and passing it as a Function argument.

```c
    // Setup sampler for linear filtering and clamp out of bounds accesses to edge.
    ${x}_sampler_desc_t desc = {
        ${X}_SAMPLER_DESC_VERSION_CURRENT,
        XE_SAMPLER_ADDRESS_MODE_CLAMP,
        XE_SAMPLER_FILTER_MODE_LINEAR,
        false
        };
    ${x}_sampler_handle_t sampler;
    ${x}DeviceCreateSampler(hDevice, &desc, &sampler);
    ...
    
    // The sampler can be passed as a function argument.
    ${x}FunctionSetArgumentValue(hFunction, 0, sizeof(${x}_sampler_handle_t), &sampler);

    // Encode dispatch command
    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, &dispatchArgs, nullptr);
```

${"#"} <a name="oi">OpenCL Interoperability</a>
Interoperability with OpenCL is currently only supported _from_ OpenCL _to_ ${Xx} for a subset of types.
The APIs are designed to be OS agnostics and allow implementations to optimize for unified device drivers;
while allowing less-optimal interopability across different device types and/or vendors.

There are three OpenCL types that can be shared for interoperability:
1. **cl_mem** - an OpenCL buffer object
2. **cl_program** - an OpenCL program object
3. **cl_command_queue** - an OpenCL command queue object

${"##"} cl_mem
OpenCL buffer objects may be registered for use as an ${Xx} device memory allocation.
Registering an OpenCL buffer object with ${Xx} merely obtains a pointer to the underlying device memory
allocation and does not alter the lifetime of the device memory underlying the OpenCL buffer object.
Freeing the ${Xx} device memory allocation effectively "un-registers" the allocation from ${Xx}, 
and should be performed before the OpenCL buffer object is destroyed.
Using the ${Xx} device memory allocation after destroying its associated OpenCL buffer object will
result in undefined behavior.

Applications are responsible for enforcing memory consistency for shared buffer objects using existing OpenCL and/or ${Xx} APIs.

${"##"} cl_program
${Xx} modules are always in a compiled state and therefore prior to retrieving an ::${x}_module_handle_t from
a cl_program the caller must ensure the cl_program is compiled and linked.

${"##"} cl_command_queue
Sharing OpenCL command queues provide opportunities to minimize transition costs when submitting work from
an OpenCL queue followed by submitting work to ${Xx} command queue and vice-versa.  Enqueuing ${Xx} command lists
to ${Xx} command queues are immediately dispatched to the device.  OpenCL implementations, however, may not
necessarily dispatch tasks to the device unless forced by explicit OpenCL API such as clFlush or clFinish.
To minimize overhead between sharing command queues, applications must explicitly dispatch OpenCL command 
queues using clFlush, clFinish or similar dispatch operations prior to enqueuing an ${Xx} command list.
Failing to explicitly dispatch device work may result in undefined behavior.  

Sharing an OpenCL command queue doesn't alter the lifetime of the API object.  It provides knowledge for the
driver to potentially reuse some internal resources which may have noticeable overhead when switching the resources.

Memory contents as reflected by any caching schemes will be consistent such that, for example, a memory write
in an OpenCL command queue can be read by a subsequent ${Xx} command list without any special application action. 
The cost to ensure memory consistency may be implementation dependent.  The performance of sharing command queues
will be no worse than an application submitting work to OpenCL, calling clFinish followed by submitting an
::${x} command list.  In most cases, command queue sharing may be much more efficient. 

${"#"} <a name="ipc">Inter-Process Communication</a>
The ${Xx} Inter-Process Communication (IPC) APIs allow device memory allocations to be used across processes.
The following code examples demonstrate how to use the IPC APIs:

1. First, the allocation is made, packaged, and sent on the sending process:
```c
    void* dptr = nullptr;
    ${x}MemAlloc(hMemAlloc, hDevice, flags, size, alignment, &dptr);

    ${x}_ipc_mem_handle_t hIPC;
    ${x}IpcGetMemHandle(hMemAlloc, dptr, &hIPC);

    // Method of sending to receiving process is not defined by ${Xx}:
    send_to_receiving_process(hIPC);
```

2. Next, the allocation is received and un-packaged on the receiving process:
```c
    // Method of receiving from sending process is not defined by ${Xx}:
    ${x}_ipc_mem_handle_t hIPC;
    hIPC = receive_from_sending_process();

    void* dptr = nullptr;
    ${x}IpcOpenMemHandle(hMemAlloc, hDevice, hIPC, ${X}_IPC_MEMORY_FLAG_NONE, &dptr);
```

3. Each process may now refer to the same device memory allocation via its `dptr`.
Note, there is no guaranteed address equivalence for the values of `dptr` in each process.

4. To cleanup, first close the handle in the receiving process:
```c
    ${x}IpcCloseMemHandle(hMemAlloc, dptr);
```

5. Finally, free the device pointer in the sending process:
```c
    ${x}MemFree(hMemAlloc, dptr);
```

${"#"} <a name="exp">Experimental</a>
The following experimental features are provided only for the development and refinement of future APIs.
These APIs are **not** supported by production drivers without explicit end-user opt-in.

${"##"} Device-Specific Commands
::${x}CommandListReserveSpace provides direct access to the command list's command buffers in order to allow unrestricted access the device's capabilities.
The application is solely responsible for ensuring the commands are valid and correct for the specific device.

```c
    void* ptr = nullptr;
    ${x}CommandListReserveSpace(hCommandList, sizeof(blob), &ptr);
    ::memcpy(ptr, blob, sizeof(blob));
```

${"#"} <a name="dbg">Debug and Instrumentation Layers</a>

${"#"} <a name="fut">Future</a>
The following is a list a features that are still being defined for inclusion:
- **Command Graphs**
    + ability to represent non-linear dependencies between programs to be executed
    + ability to represent flow-control
    + ability to represent scheduling and distribution across multiple sub-devices
- **Predicated Execution**
    + ability to cull program execution within a command list, based on device-generated value(s)
- **Execution Flow-Control**
    + ability to describe loops and if-else-then type program execution within a command list, based on device-generated value(s)
- **Execute Indirect**
    + ability for the device to generate and enqueue more work (better version of device-side enqueue)
- **C++ Interfaces**
    + ability to choose between C and C++ interfaces (e.g., by wrapping C++ interfaces with C interfaces)
