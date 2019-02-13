# Programming Guide (Core)

[DO NOT EDIT]: # (generated from /scripts/core/PROG.md)

The following documents the high-level programming models and guidelines.  

NOTE: This is a **PRELIMINARY** specification, provided for review and feedback.

## Table of Contents
* [Driver and Device](#dnd)
* [Command Queues and Command Lists](#cnc)
* [Barriers](#brr)
* [Synchronization Primitives](#sp)
* [Memory and Image Management](#mim)
* [Modules and Functions](#mnf)
* [OpenCL Interoperability](#oi)
* [Inter-Process Communication](#ipc)
* [Future](#fut)

# <a name="dnd">Driver and Device</a>
The following diagram illustrates the hierarchy of devices to the driver:  
![Driver](../images/core_driver.png?raw=true)  
@image latex ../images/core_driver.png

## Driver
A driver represents an instance of a Xe driver being loaded and initialized into the current process.
- Only one instance of a driver per process can be loaded.
- Multiple calls to xeDriverInit are silently ignored.
- A driver has minimal global state associated; only that which is sufficient for querying devices recognized by the driver.
- There is no explicit unload or shutdown of the driver.
- Any global resources acquired during xeDriverInit will be released during process detach.

## Device
A device represents a physical device in the system that can support Xe.
- More than one device may be available in the system.
- The driver will only report devices that are recognized by the driver.
- The application is responsible for sharing memory and explicit submission and synchronization across multiple devices.
- Device can expose sub-devices that allow finer-grained control of multi-tile devices.

## Initialization
The driver must be initizalized by calling xeDriverInit before any other function.
This function will query the available physical adapters in the system and make this information available to all threads in the current process.

The following sample code demonstrates a basic initialization sequence:
```c
    // NOTE: Sample code in this document contains little or no error checking for brevity and clarity.
    //       However, proper error checking is highly recommended and necessary in many cases.

    // Initialize the driver
    xeDriverInit(XE_INIT_FLAG_NONE);

    // Get number of devices supporting Xe
    uint32_t deviceCount = 0;
    xeDriverGetDeviceCount(&deviceCount);
    if(0 == deviceCount)
    {
        printf("There is no device supporting Xe!\n");
        return;
    }

    // Get the handle for device that supports required API version
    xe_device_handle_t hDevice;
    for(uint32_t i = 0; i < deviceCount; ++i)
    {
        xeDriverGetDevice(i, &hDevice);
        
        xe_api_version_t version;
        xeDeviceGetApiVersion(hDevice, &version);
        if(XE_API_VERSION_1_0 <= version)
            break;

        if(i == deviceCount)
        {
            printf("There is no device that supporting Xe version required!\n");
            return;
        }
    }
    ...

```
## Sub-Device Support
A multi-tile device consists of tiles that are tied together by high-speed interconnects. Each tile
has local memory that is shared to other tiles through these interconnects. The API represents tiles
as sub-devices and there are functions to query and obtain a sub-device. Outside of these functions
there are no distinction between sub-devices and devices. 

![Subdevice](../images/core_subdevice.png?raw=true)  
@image latex ../images/core_subdevice.png

Query device properties using xeDeviceGetProperties to confirm subdevices are supported with
$x_device_properties_t.numSubDevices. Use xeDeviceGetSubDevice to obtain a sub-device handle.
There are additional device properties in $x_device_properties_t for sub-devices to confirm a
device is a sub-device and to query the id. This is useful when needing to pass a sub-device
handle to another library.

To allocate memory and dispatch tasks to a particular sub-device then obtain the sub-device
handle and use this with memory and command queue/lists APIs. One thing to note is that the ordinal
that is used when creating a command queue is relative to the sub-device. This ordinal specifies which
physical compute queue on the device or sub-device to map the logical queue to. You need to query
xe_device_properties_t.numAsyncComputeEngines from the sub-device to determine how to set this ordinal.
See xe_command_queue_desc_t for more details.

```c
    ...
    xeDeviceGetProperties(device, &deviceProps);
    ...

    // Code assumes a specific device configuration.
    assert(deviceProps.numSubDevices == 4);

    // Desire is to allocate and dispatch work to sub-device 2.
    uint32_t subdeviceId = 2;
    xeDeviceGetSubDevice(device, subdeviceId, &subdevice);

    // Query sub-device properties.
    xe_device_properties_t subdeviceProps;
    xeDeviceGetProperties(subdevice, &subdeviceProps);

    assert(subdeviceProps.isSubdevice == true); // Ensure that we have a handle to a sub-device.
    assert(subdeviceProps.subdeviceId == 2);    // Ensure that we have a handle to the sub-device we asked for.

    ...
    void* pMemForSubDevice2;
    xeMemAlloc(subDevice, XE_DEVICE_MEM_ALLOC_DEFAULT, memSize, sizeof(uint32_t), &pMemForSubDevice2);
    ...

    ...
    // Check that cmd queue ordinal that was chosen is valid.
    assert(desc.ordinal < subdeviceProps.numAsyncComputeEngines);

    xe_command_queue_handle_t commandQueueForSubDevice2;
    xeDeviceCreateCommandQueue(subdevice, desc, &commandQueueForSubDevice2);
    ...
```

# <a name="cnc">Command Queues and Command Lists</a>
The following are the motivations for seperating a command queue from a command list:
- Command queues are mostly associated with physical device properties,
  such as the number of input streams.
- Command queues provide (near) zero-latency access to the device.
- Command lists are mostly associated with Host threads for simultaneous construction.
- Command list encodeing can occur independently of command queue submission.
- Command list submission can occur to more than one command queue.

The following diagram illustrates the hierarchy of command lists and command queues to the device:  
![Queue](../images/core_queue.png?raw=true)  
@image latex ../images/core_queue.png

## Command Queues
A command queue represents a logical input stream to the device, tied to a physical input
stream via an ordinal at creation time.

### Creation
- The application may explicitly bind the command queue to a physical input stream, or
  allow the driver to choose dynamically, based on usage.
- Multiple command queues may be created that use the same physical input stream. For example,
  an application may create a command queue per Host thread with different scheduling priorities.
- However, an application should avoid creating multiple command queues for the same physical
  input stream with the same priority due to possible performance penalties with hardware
  context switching.
- The number of simultaneous compute command queues per device is queried from 
  ::xe_device_properties_t.numAsyncComputeEngines.
- The number of simultaneous copy command queues per device is queried from 
  ::xe_device_properties_t.numAsyncCopyEngines.

The following sample code demonstrates a basic sequence for creation of command queues:
```c
    // Create a command queue
    xe_command_queue_desc_t commandQueueDesc = {
        XE_COMMAND_QUEUE_DESC_VERSION,
        XE_COMMAND_QUEUE_FLAG_NONE,
        XE_COMMAND_QUEUE_MODE_DEFAULT,
        XE_COMMAND_QUEUE_PRIORITY_NORMAL,
        0
    };
    xe_command_queue_handle_t hCommandQueue;
    xeDeviceCreateCommandQueue(hDevice, &commandQueueDesc, &hCommandQueue);
    ...
```

### Execution
- Command lists submitted to a command queue are **immediately** executed in a fifo manner.
- Command queue submission is free-treaded, allowing multiple Host threads to
  share the same command queue.
- If multiple Host threads enter the same command queue simultaneously, then execution order
  is undefined.
- Command lists created with ::XE_COMMAND_LIST_FLAG_COPY_ONLY may only be submitted to
  command queues created with ::XE_COMMAND_QUEUE_FLAG_COPY_ONLY.

### Destruction
- The application is responsible for making sure the device is not currently
  executing from a command queue before it is deleted.  This is 
  typically done by tracking command queue fences, but may also be
  handled by calling ::xeCommandQueueSynchronize.

## Command Lists
A command list represents a sequence of commands for execution on a command queue.

### Creation
- A command list is created for a device to allow device-specific encoding of commands.
- A command list can be copied to create another command list. The application may use this
  to copy a command list for use on a different device.

### Encoding
- There is no implicit binding of command lists to Host threads. Therefore, an 
  application may share a command list handle across multiple Host threads. However,
  the application is responsible for ensuring that multiple Host threads do not access
  the same command list simultaneously.
- By default, commands are executed in the same order in which they are submitted.
  However, an application may allow the driver to optimize the ordering by using
  ::XE_COMMAND_LIST_FLAG_RELAXED_ORDERING.  Reordering is guarenteed to be only occur
  between barriers and synchronization primitives.
- The command list maintains some machine state, which is inherited by subsequent
  commands. See ::xe_command_list_parameter_t for details.
- A command list can be called from another command list (nested). In this case, state
  may be inherited and leaked by the nested command list.

The following sample code demonstrates a basic sequence for creation of command lists:
```c
    // Create a command list
    xe_command_list_desc_t commandListDesc = {
        XE_COMMAND_LIST_DESC_VERSION,
        XE_COMMAND_LIST_FLAG_NONE
    };
    xe_command_list_handle_t hCommandList;
    xeDeviceCreateCommandList(hDevice, &commandListDesc, &hCommandList);
    ...
```

### Submission
- There is no implicit association between a command list and a command queue. 
  Therefore, a command list may be submitted to any, or multiple command queues.
  However, if a command list is meant to be submitted to a copy-only command queue
  then the ::XE_COMMAND_LIST_FLAG_COPY_ONLY must be set at creation.
- The application is responsible for calling close before submission to a command queue.
- Command lists do not inherit state from other command lists executed on the same
  command queue.  i.e. each command list begins execution in its own default state.

The following sample code demonstrates submission of commands to a command queue, via a command list:
```c
    ...
    // finished encoding commands (typically done on another thread)
    xeCommandListClose(hCommandList);

    // Enqueue command list execution into command queue
    xeCommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

    // synchronize host and device
    xeCommandQueueSynchronize(hCommandQueue);

    // Reset (recycle) command list for new commands
    xeCommandListReset(hCommandList);
    ...
```

### Recycling
- A command list may be recycled to avoid the overhead of frequent creation and destruction.
- The application is responsible for making sure the device is not currently
  executing from a command list before it is reset.  This should be
  handled by tracking a completion event associated with the command list.
- The application is responsible for making sure the device is not currently
  executing from a command list before it is deleted.  This should be
  handled by tracking a completion event associated with the command list.

## Command Graphs (Experimental)
A command graph represents non-linear dependencies between a collection of command lists to be executed.
- An implementation may use this information to reorder the execution of command lists to be optimized for the device.
- An implementation may also parallelize execution across an application-specified maximum number of command queues.
- The application is responsible for ensuring there are no inter-command list dependencies that would cause dead-lock;
  e.g., infinite loops, synchronization primtives, etc. 
- The application is responsible for calling close before submission to a command queue.
- The command graph itself does not allocate any device memory; therefore is mutable immediately after enqueuing.
- The command graph does not modify or copy any of the command lists.
- The command graph does have references to existing command lists, which must be removed prior to the command lists being destroyed.

The following diagram illustrates a representation of a command graph and how batches of command lists may be submitted to command queues:  
![Graph](../images/core_graph.png?raw=true)  
@image latex ../images/core_graph.png

The following sample code demonstrates submission of command lists to a command queue, via a command graph:
```c
    ...
    // create a command graph
    xe_command_graph_desc_t commandGraphDesc = {
        XE_COMMAND_GRAPH_DESC_VERSION,
        XE_COMMAND_GRAPH_FLAG_NONE,
        2, 0
    };
    xe_command_graph_handle_t hCommandGraph;
    xeDeviceCreateCommandGraph(hDevice, &commandGraphDesc, &hCommandGraph);

    // add dependencies between command lists (typically done on another thread)
    xeCommandGraphAddEdge(hCommandGraph, hCommandList1, hCommandList3);
    xeCommandGraphAddEdge(hCommandGraph, hCommandList2, hCommandList3);
    xeCommandGraphClose(hCommandGraph);

    // Enqueue N batches of command lists across M command queue(s)
    uint32_t numbatches = 0;
    xeCommandGraphGetComputeBatchCount(hCommandGraph, &numbatches);

    for( uint32_t batchIndex = 0; batchIndex < numbatches; ++batchIndex )
    {
        uint32_t cqindex = 0; // logical index of command queue to enqueue this batch
                              // must be less than commandGraphDesc.maxComputeQueueCount

        uint32_t clcount = 0; // number of command lists in this batch
        xe_command_list_handle_t* pCommandLists = nullptr; // array of command lists handles in this batch

        xeCommandGraphGetComputeCommandListBatch(hCommandGraph, batchIndex, &cqindex, &clcount, &pCommandLists);
        xeCommandQueueEnqueueCommandLists(phCommandQueue[cqindex], clcount, pCommandLists, nullptr);
    }

    xeCommandGraphReset(hCommandGraph);
    ...
```

# <a name="brr">Barriers</a>
There are two types of barriers:
1. **Execution Barriers** - used to insert execution dependency between commands _within_ a command list.
2. **Memory Barriers** - used to insert a dependency between memory access across command queues, devices or Host.

## Execution Barriers
- Commands submitted to a command list are only guarenteed to start in the same order in which they are submitted;
  there is no implicit control of which order they complete.
- Execution barriers provide explicit control to indicate that previous commands must complete prior to
  starting the following commands.
- Execution barriers are implicitly added by the driver after each batch of command lists submitted to a command queue.
- Execution barriers are implicitly added by the driver prior to synchronization primitives.

The following sample code demonstrates a sequence for submission of an execution barrier:
```c
    xeCommandListEncodeDispatchFunction(hCommandList, hFunction1, ...);

    // Encode a barrier into a command list to ensure hFunction1 completes before hFunction2 begins
    xeCommandListEncodeExecutionBarrier(hCommandList);

    xeCommandListEncodeDispatchFunction(hCommandList, hFunction2, ...);
    ...
```

## Memory Barriers
- Memory barriers are implicitly added by the driver after each batch of command lists submitted to a command queue.
- Memory barriers are implicitly added by the driver prior to synchronization primitives.

@todo [**Brandon**] need to define the rules when _when_ memory barriers occur.

# <a name="sp">Synchronization Primitives</a>
There are three types of synchronization primitives:
1. [**Fences**](#fnc) - used to communicate to the host that command queue execution has completed.
2. [**Events**](#evnt) - used as fine-grain host-to-device, device-to-host or device-to-device waits and signals within a command list.
3. [**Semaphores**](#sema) - used for fine-grain control of command lists execution across multiple, simultaneous command queues within a device.

The following diagram illustrats the relationship of capabilities of these types of synchronization primitives:  
![Graph](../images/core_sync.png?raw=true)  
@image latex ../images/core_sync.png

The following are the motivations for seperating the different types of synchronization primitives:
- Allows device-specific optimizations for certain types of primitives:
    + fences may share device memory with all other fences for the queue or device.
    + events may be implemented using pipelined operations as part of the program execution.
    + semaphores may be implemented without device memory.
    + fences and events implicitly cause execution and memory barriers, while semaphores may only cause execution barriers.
- Allows distinction on which type of primitive may be shared across devices.

## <a name="fnc">Fences</a>
A fence is a lightweight synchronization primitive used to communicate to the host that command queue execution has completed.
- A fence is associated with single command queue.
- A fence can only be signaled from a device's command queue (e.g. between execution of command lists)
  and can only be waited upon from the host.
- A fence only has two states: not signaled and signaled.
- A fence can only be reset from the Host.
- A fence cannot be shared across processes.
- An application can use ::xeFenceQueryElapsedTime to calculate the time (in milliseconds) between two fences' signals.

The primary usage model(s) for fences are to notify the Host when a command list has finished execution to allow:
- Recycling of memory and images
- Recycling of command lists
- Recycling of other synchronization primitives
- Explicit memory residency.

The following diagram illustrates an example of fences:  
![Fence](../images/core_fence.png?raw=true)  
@image latex ../images/core_fence.png

The following sample code demonstrates a sequence for creation, submission and querying of a fence:
```c
    // Create fence
    xe_fence_desc_t fenceDesc = {
        XE_FENCE_DESC_VERSION,
        XE_FENCE_FLAG_NONE
    };
    xe_fence_handle_t hFence;
    xeCommandQueueCreateFence(hCommandQueue, &fenceDesc, &hFence);

    // Enqueue a signal of the fence into the command queue
    xeCommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, hFence);

    // Wait for fence to be signaled
    if(XE_RESULT_SUCCESS != xeFenceQueryStatus(hFence))
    {
        xeHostWaitOnFence(hFence);
    }

    xeFenceReset(hFence);
    ...
```

## <a name="evnt">Events</a>
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
- An application can use ::xeEventQueryElapsedTime to calculate the time (in milliseconds) between two events signalled by the same device.
@todo [**Ben**] Explore exposing GPU clocks directly with equivalent query on clock rate.  Common request from other teams.
@todo [**Ben**] Explore exposing both wall clock time and actual GPU execution time due to preemption.

Events are generic synchronization primitives that can be used across many different usage-models, includes those of fences and semaphores.
However, this generality comes with some cost in efficiency.

Events do **not** represent intra-command list dependencies between programs.

The following diagram illustrates an example of events:  
![Event](../images/core_event.png?raw=true)  
@image latex ../images/core_event.png

The following sample code demonstrates a sequence for creation and submission of an event:
```c
    // Create event
    xe_event_desc_t eventDesc = {
        XE_EVENT_DESC_VERSION,
        XE_EVENT_FLAG_NONE
    };
    xe_event_handle_t hEvent;
    xeDeviceCreateEvent(hDevice, &eventDesc, &hEvent);

    // Encode a wait on an event into a command list
    xeCommandListEncodeWaitOnEvent(hCommandList, hEvent);

    // Enqueue wait via the command list into a command queue
    xeCommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

    // Signal the device
    xeHostSignalEvent(hEvent);
    ...
```

## <a name="sema">Semaphores</a>
A semaphore is used for fine-grain control of command lists execution across multiple, simultaneous command queues within a device.
- A semaphore can only be signaled and waited upon from within a device's command lists.
- A semaphore has a 64-bit value, initialized to zero and changed when signaled.
- A semaphore wait can test its value for less-than, less-than-or-equal, equal, not-equal, greater-than-or-equal, or greater-than another value.
- A semaphore can be encoded into any command list from the same device.
- A semaphore can be signaled and waited upon in the same command list.
- A semaphore can be encoded into multiple command lists simultaneously.
- A semaphore cannot be shared across processes.
- A semaphore imposes an implicit execution barrier; therefore should be used sparingly to avoid device underutilization.
- There are no protections against semaphores causing deadlocks.

The primary usage model(s) for semaphores is:
- Low-latency device-side scheduling of programs executing concurrently across multiple command queues.

The following diagram illustrates an example of semaphores:  
![Semaphore](../images/core_semaphore.png?raw=true)  
@image latex ../images/core_semaphore.png

The following sample code demonstrates a sequence for creation and submission of a semaphore:
```c
    // Create semaphore
    xe_semaphore_desc_t semaphoreDesc = {
        XE_SEMAPHORE_DESC_VERSION,
        XE_SEMAPHORE_FLAG_NONE
    };
    xe_semaphore_handle_t hSemaphore;
    xeDeviceCreateSemaphore(hDevice, &semaphoreDesc, &hSemaphore);

    // Encode a wait on an semaphore into a command list
    xeCommandListEncodeSemaphoreWait(hCommandList0, hSemaphore,
        XE_SEMAPHORE_WAIT_OPERATION_GREATER_OR_EQUAL_TO, 1);

    // Encode a signal of a semaphore into another command list
    xeCommandListEncodeSemaphoreSignal(hCommandList1, hSemaphore, 1);

    // Enqueue the command lists into the parallel command queues
    xeCommandQueueEnqueueCommandLists(hCommandQueue0, 1, &hCommandList0, nullptr);
    xeCommandQueueEnqueueCommandLists(hCommandQueue1, 1, &hCommandList1, nullptr);
    ...
```

# <a name="mim">Memory and Image Management</a>
There are two types of allocations:
1. **Memory** - linear, unformatted allocations for direct access from both the host and device.
2. **Images** - non-linear, formatted allocations for direct access from the device.

## Memory
Linear, unformatted memory allocations are represented as pointers in the host application.
A pointer on the host has the same size as a pointer on the device.

Three types of allocations are supported.
The type of allocation describes the _ownership_ of the allocation:
1. **Host** allocations are owned by the host and are intended to be allocated out system memory.
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

Devices may support different capabilities for each type of allocation.
Supported capabilities are:
* ::XE_MEMORY_ACCESS - if a device supports access (read or write) to allocations of the specified type.
* ::XE_MEMORY_ATOMIC_ACCESS - if a device support atomic access to allocations of the specified type.
* ::XE_MEMORY_CONCURRENT_ACCESS - if a device supports concurrent access to allocations of the specified type, or another device's allocation of the specified type.
* ::XE_MEMORY_CONCURRENT_ATOMIC_ACCESS - if a device supports concurrent atomic access to allocations of the specified type, or another device's allocations of the specified type.

The required matrix of capabilities are:
| Allocation Type         | Access   | Atomic Access | Concurrent Access | Concurrent Atomic Access |
| :--:                    | :--:     | :--:          | :--:              | :--:                     |
| **Host**                | Required | Optional      | Optional          | Optional                 |
| **Device**              | Required | Optional      | Optional          | Optional                 |
| **Shared**              | Optional | Optional      | Optional          | Optional                 |
| Cross-Device **Shared** | Optional | Optional      | Optional          | Optional                 |

### Cache Hints, Prefetch, and Memory Advice
Cacheability hints may be provided via separate host and device allocation flags when memory is allocated.

**Shared** allocations may be prefetched to a supporting device via the ::xeCommandListEncodeMemoryPrefetch API.
Prefetching may allow memory transfers to be scheduled concurrently with other computations and may improve performance.

Additionally, an application may provide memory advice for a **shared** allocation via the ::xeCommandListEncodeMemAdvise API, to override driver heuristics or migration policies.
Memory advice may avoid unnecessary or unprofitable memory transfers and may improve performance.

Both prefetch and memory advice are asynchronous operations that are encoded into command lists.

## Images
An image is used to store multi-dimensional and format-defined memory for optimal device access.
An image's contents can be copied to and from other images, as well as host-accessable memory allocations.
This is the only method for host access to the contents of an image.
This methodology allows for device-specific encoding of image contents (e.g., tile swizzle patterns, loseless compression, etc.) 
and avoids exposing these details in the API in a backwards compatible fashion.

```c
    xe_image_desc_t imageDesc = {
        XE_IMAGE_DESC_VERSION,
        XE_IMAGE_FLAG_KERNEL_READ,
        XE_IMAGE_TYPE_2D,
        XE_IMAGE_FORMAT_FLOAT32, 1,
        128, 128, 0, 0, 0
    };
    xe_image_handle_t hImage;
    xeDeviceCreateImage(hDevice, &imageDesc, &hImage);

    // upload contents from host pointer
    xeCommandListEncodeImageCopyFromMemory(hCommandList, hImage, nullptr, pImageData);
    ...
```

## Device Cache Settings
For device support cache control and config, there are two methods for cache control:
1. Cache Size Configuration: Ability to configure larger size for SLM vs Data globally for Device
2. Runtime Hint/prefrence for application to allow access to be Cached or not in Device Caches. For GPU device this is provided via two ways  
      -  During Image creation via Flag
      -  Kernel instruction 

The following sample code demonstrates a basic sequence for Cache size configuration:
```c
    // Large SLM for Intermediate and Last Level cache
    xeDeviceSetIntermediateCacheConfig(hDevice, XE_CACHE_CONFIG_LARGE_SLM);
    xeDeviceSetLastLevelCacheConfig(hDevice, XE_CACHE_CONFIG_LARGE_SLM);
    ...
```
The following sample code demonstrates a basic sequence for Runtime Hint/Prefrence for Cache:

## Device Residency
For devices that do not support page-faults, the driver must ensure that all pages that will be accessed by the kernel are resident before program execution.
This can be determined by checking xe_device_memory_properties_t.onDemandPageFaults.

In most cases, the driver implicitly handles residency of allocations for device access.
This can be done by inspecting API parameters, including function arguments.
However, in cases where the devices does **not** support page-faulting _and_ the driver is incapable of determining whether an allocation will be accessed by the device,
such as multiple levels of indirection, there are two methods available:
1. the application may set the ::XE_FUNCTION_FLAG_FORCE_RESIDENCY flag during program creation to force all device allocations to be resident during execution.
 + in addition, the application should indicate the type of allocations that will be indirectly accessed using ::xe_function_argument_attribute_t
2. explcit APIs are included for the application to dynamically change residency as needed.

If the application does not properly manage residency for these cases then the device may experience unrecoverable page-faults.

The following sample code demonstrate a sequence for using coarse-grain residency control for indirect arguments:
```c
    struct node {
        node* next;
    };
    node* begin = nullptr;
    xeHostMemAlloc(XE_HOST_MEM_ALLOC_DEFAULT, sizeof(node), 1, &begin);
    xeHostMemAlloc(XE_HOST_MEM_ALLOC_DEFAULT, sizeof(node), 1, &begin->next);
    xeHostMemAlloc(XE_HOST_MEM_ALLOC_DEFAULT, sizeof(node), 1, &begin->next->next);

    // 'begin' is passed as function argument and encoded into command list
    xeFunctionArgsSetAttribute(hFuncArgs, XE_FUNCTION_ARG_ATTR_INDIRECT_HOST_ACCESS, 1);
    xeFunctionArgsSetValue(hFuncArgs, 0, sizeof(node*), &begin);
    xeCommandListEncodeDispatchFunction(hCommandList, hFunction, hFunctionArgs, ...);
    ...

    xeCommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, nullptr);
    ...
```

The following sample code demonstrate a sequence for using fine-grain residency control for indirect arguments:
```c
    struct node {
        node* next;
    };
    node* begin = nullptr;
    xeHostMemAlloc(XE_HOST_MEM_ALLOC_DEFAULT, sizeof(node), 1, &begin);
    xeHostMemAlloc(XE_HOST_MEM_ALLOC_DEFAULT, sizeof(node), 1, &begin->next);
    xeHostMemAlloc(XE_HOST_MEM_ALLOC_DEFAULT, sizeof(node), 1, &begin->next->next);

    // 'begin' is passed as function argument and encoded into command list
    xeFunctionArgsSetValue(hFuncArgs, 0, sizeof(node*), &begin);
    xeCommandListEncodeDispatchFunction(hCommandList, hFunction, hFunctionArgs, ...);
    ...

    // Make indirect allocations resident before enqueuing
    xeDeviceMakeMemoryResident(hDevice, begin->next, sizeof(node));
    xeDeviceMakeMemoryResident(hDevice, begin->next->next, sizeof(node));

    xeCommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

    // wait until complete
    xeFenceEnqueueSignal(hFence);
    xeHostWaitOnFence(hFence);

    // Finally, evict to free device resources
    xeDeviceEvictMemory(hDevice, begin->next, sizeof(node));
    xeDeviceEvictMemory(hDevice, begin->next->next, sizeof(node));
    ...
```

# <a name="mnf">Modules and Functions</a>
There are multiple levels of constructs needed for executing functions on the device:
1. A [**Module**](#mod) represents a single translation unit that consists of functions that have been compiled together.
2. A [**Function**](#func) represents the function within the module that will be dispatched directly from a command list.
3. A [**FunctionArgs**](#arg) represents an instance of arguments to be used by the function when dispatched.

## <a name="mod">Modules</a>
Modules can be created from an IL or directly from native format using ::xeDeviceCreateModule.
- ::xeDeviceCreateModule takes a format argument that specifies the input format.
- ::xeDeviceCreateModule performs a compilation step when format is IL.

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
    xe_module_desc_t moduleDesc = {
        XE_MODULE_DESC_VERSION
        XE_MODULE_IL_SPIRV,
        ilSize,
        pImageScalingIL,
        nullptr
    };
    xe_module_handle_t hModule;
    xeDeviceCreateModule(hDevice, &moduleDesc, &hModule);
    ...
```

### Module Build Options
Build options can be passed with ::xe_module_desc_t as a string.

| Build Option                                  | Description                                           | Default  |
| :--                                           | :--                                                   | :--      |
| -xe-opt-disable                             | Disable optimizations.                                | Disabled |
| -xe-opt-greater-than-4GB-buffer-required    | Use 64-bit offset calculations for buffers.           | Disabled |
| -xe-opt-large-register-file                 | Increase number of registers available to threads.    | Disabled |

### Module Build Log
The ::xeDeviceCreateModule function can optionally generate a build log object ::xe_module_build_log_handle_t.

```c
    ...
    xe_module_build_log_handle_t buildlog;
    xeDeviceCreateModule(hDevice, &desc, &module, &buildlog);

    uint32_t buildlogSize;
    char* pBuildLogString;
    xeModuleBuildLogGetString(buildlog, &buildlogSize, &pBuildLogString);

    // Save log to disk.
    ...

    xeModuleBuildLogDestroy(buildlog);
```

### Module Caching with Native Binaries
Disk caching of modules is not supported by the driver. If a disk cache for modules is desired then it is the
responsibility of the application to implement this using ::xeModuleGetNativeBinary.

```c
    ...
    // compute hash for pIL and check cache.
    ...

    if (cacheUpdateNeeded)
    {
        uint32_t size;
        char* pNativeBinary;  // Pointer to native binary.
        xeModuleGetNativeBinary(hModule, &size, &pNativeBinary);

        // cache pNativeBinary for corresponding IL
        ...
    }
```
Also, note that the native binary will retain all debug information that is associated with the module. This allows debug
capabilities for modules that are created from native binaries.

## <a name="func">Functions</a>
Functions are immutable references to functions within a module.

The following sample code demonstrates a sequence for creating a function from a module:
```c
    xe_function_desc_t functionDesc = {
        XE_FUNCTION_DESC_VERSION,
        XE_FUNCTION_FLAG_NONE,
        "image_scaling"
    };
    xe_function_handle_t hFunction;
    xeModuleCreateFunction(hModule, &functionDesc, &hFunction);
    ...
```

### Function Attributes
Use xeFunctionQueryAttribute to query attributes from a function object.

```c
    ...
    uint32_t numRegisters;

    // Number of hardware registers used by function.
    xeFunctionQueryAttribute(hFunction, XE_FUNCTION_ATTR_HAS_BARRIERS, &numRegisters);
    ...
```

See xe_function_attribute_t for more information on the attributes.

### Function Group Size
The API supports a query for suggested group size. If the function has an embedded group size then this
will be returned. Otherwise, one will be suggested. This function should not be used if a group size is
not already associated with the function and the function requires specific alignment for group size.

```c
    // Find suggested group size for processing image.
    uint32_t groupSizeX;
    uint32_t groupSizeY;
    xeFunctionSuggestGroupSize(function, imageWidth, imageHeight, 1, &groupSizeX, &groupSizeY, nullptr);

    uint32_t numGroupsX = imageWidth / groupSizeX;
    uint32_t numGroupsY = imageHeight / groupSizeY;

    // Encode dispatch command
    xeCommandListEncodeDispatchFunction(
        hCommandList, hFunction, hFunctionArgs, 
        groupSizeX, groupSizeY, 1,
        numGroupsX, numGroupsY, 1);

    ...
```

## <a name="arg">FunctionArgs</a>
FunctionArgs represent the inputs for a function.
- FunctionArgs must be used with the Function object it was created for.
- Use xeFunctionArgsSetValue to setup arguments for a function dispatch.
- FunctionArgs can updated and used across multiple dispatches for the same function.
  - The driver will snapshot the arguments when dispatched.

The following sample code demonstrates a sequence for creating function args and dispatching the function:
```c
    xe_function_args_handle_t hFunctionArgs;
    xeFunctionCreateFunctionArgs(hFunction, &hFunctionArgs);

    // Bind arguments
    xeFunctionArgsSetValue(hFuncArgs, 0, sizeof(xe_image_handle_t), &src_image);
    xeFunctionArgsSetValue(hFuncArgs, 1, sizeof(xe_image_handle_t), &dest_image);
    xeFunctionArgsSetValue(hFuncArgs, 2, sizeof(uint32_t), &width);
    xeFunctionArgsSetValue(hFuncArgs, 3, sizeof(uint32_t), &height);

    // Encode dispatch command
    xeCommandListEncodeDispatchFunction(
        hCommandList, hFunction, hFunctionArgs, 
        pixelRegionWidth, pixelRegionHeight, 1, 
        numRegionsX, numRegionsY, 1,
        nullptr );

    // Update image pointers to copy and scale next image.
    xeFunctionArgsSetValue(hFuncArgs, 0, sizeof(xe_image_handle_t), &src2_image);
    xeFunctionArgsSetValue(hFuncArgs, 1, sizeof(xe_image_handle_t), &dest2_image);

    // Encode dispatch command
    xeCommandListEncodeDispatchFunction(
        hCommandList, hFunction, hFunctionArgs, 
        pixelRegionWidth, pixelRegionHeight, 1, 
        numRegionsX, numRegionsY, 1,
        nullptr );

    ...
```

# <a name="oi">OpenCL Interoperability</a>
Interoperability with OpenCL is currently only supported _from_ OpenCL _to_ Xe for a subset of types.
The APIs are designed to be OS agnostics and allow implementations to optimize for unified device drivers;
while allowing less-optimal interopability across different device types and/or vendors.

There are three OpenCL types that can be shared for interoperability:
1. **cl_mem** - an OpenCL buffer object
2. **cl_program** - an OpenCL program object
3. **cl_command_queue** - an OpenCL command queue object

## cl_mem
OpenCL buffer objects may be registered for use as an Xe device memory allocation.
Registering an OpenCL buffer object with Xe merely obtains a pointer to the underlying device memory
allocation and does not alter the lifetime of the device memory underlying the OpenCL buffer object.
Freeing the Xe device memory allocation effectively "un-registers" the allocation from Xe, 
and should be performed before the OpenCL buffer object is destroyed.
Using the Xe device memory allocation after destroying its associated OpenCL buffer object will
result in undefined behavior.

Applications are responsible for enforcing memory consistency for shared buffer objects using existing OpenCL and/or Xe APIs.

## cl_program
Xe modules are always in a compiled state and therefore prior to retrieving an xe_module_handle_t from
a cl_program the caller must ensure the cl_program is compiled and linked.

## cl_command_queue
Sharing OpenCL command queues provide opportunities to minimize transition costs when submitting work from
an OpenCL queue followed by submitting work to xe command queue and vice-versa.  Enqueuing xe command lists
to xe command queues are immediately dispatched to the device.  OpenCL implementations, however, may not
necessarily dispatch tasks to the device unless forced by explicit OpenCL API such as clFlush or clFinish.
To minimize overhead between sharing command queues, applications must explicitly dispatch OpenCL command 
queues using clFlush, clFinish or similar dispatch operations prior to enqueuing an xe command list.
Failing to explicitly dispatch device work may result in undefined behavior.  

Sharing an OpenCL command queue doesn't alter the lifetime of the API object.  It provides knowledge for the
driver to potentially reuse some internal resources which may have noticeable overhead when switching the resources.

Memory contents as reflected by any caching schemes will be consistent such that, for example, a memory write
in an OpenCL command queue can be read by a subsequent xe command list without any special user action. 
The cost to ensure memory consistency may be implementation dependent.  The performance of sharing command queues
will be no worse than an application submitting work to OpenCL, calling clFinish followed by submitting an
xe command list.  In most cases, command queue sharing may be much more efficient. 

# <a name="ipc">Inter-Process Communication</a>
The Xe Inter-Process Communication (IPC) APIs allow device memory allocations to be used across processes.
The following code examples demonstrate how to use the IPC APIs:

1. First, the allocation is made, packaged, and sent on the sending process:
```c
    void* dptr = nullptr;
    xeMemAlloc(..., &dptr);

    xe_ipc_mem_handle_t hIPC;
    xeIpcGetMemHandle(dptr, &hIPC);

    // Method of sending to receiving process is not defined by Xe:
    send_to_receiving_process(hIPC);
```

2. Next, the allocation is received and un-packaged on the receiving process:
```c
    // Method of receiving from sending process is not defined by Xe:
    xe_ipc_mem_handle_t hIPC;
    hIPC = receive_from_sending_process();

    void* dptr = nullptr;
    xeIpcOpenMemHandle(..., hIPC, &dptr);
```

3. Each process may now refer to the same device memory allocation via its `dptr`.
Note, there is no guaranteed address equivalence for the values of `dptr` in each process.

4. To cleanup, first close the handle in the receiving process:
```c
    xeIpcCloseMemHandle(..., dptr);
```

5. Finally, free the device pointer in the sending process:
```c
    xeMemFree(dptr);
```

# <a name="fut">Future</a>
The following is a list a features that are still being defined for inclusion:
- **Predicated Execution**
    + ability to cull program execution within a command list, based on device-generated value(s)
- **Execution Flow-Control**
    + ability to describe loops and if-else-then type program execution within a command list, based on device-generated value(s)
- **Timestamps and Metrics**
    + ability to retrieve device-specific counters for performance analysis, tuning and tooling
- **Execute Indirect**
    + ability for the device to generate and enqueue more work (better version of device-side enqueue)
- **GetLastError**
    + quality-of-life addition to enable debug-only error checks, such as:
```c
    assert(XE_RESULT_SUCCESS == GetLastError(hDevice));
    assert(XE_RESULT_SUCCESS == GetLastError(hCommandList));
    assert(XE_RESULT_SUCCESS == GetLastError(hCommandQueue));
    assert(XE_RESULT_SUCCESS == GetLastError(hModule));
    ...
```
