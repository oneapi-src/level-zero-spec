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
- A driver represents an instance of a Xe driver being loaded and initialized into the current process.
- Only one instance of a driver per process can be loaded.
- There is no reference tracking if multiple drivers are initialized.
- A driver has minimal global state associated; only that which is sufficient for querying devices recognized by the driver.
 
## Device
- A device represents a physical device in the system that can support Xe.
- More than one device may be available in the system.
- The application is responsible for sharing memory and explicit submission and synchronization across multiple devices.

## Initialization
The driver API must be initizalized by calling xeDriverInit before any other function.
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

# <a name="cnc">Command Queues and Command Lists</a>
The following diagram illustrates the hierarchy of command lists and command queues to the device:  
![Queue](../images/core_queue.png?raw=true)  
@image latex ../images/core_queue.png

## Command Queues
- A command queue represents a physical input stream to the device, 
  specified by an ordinal at creation time.
- The number of simultaneous command queues per device is queried from calling 
  ::xeDeviceGetProperties; returned as ::xe_device_properties_t.numAsyncComputeEngines
  and ::xe_device_properties_t.numAsyncCopyEngines.
- Multiple command queues may be created by an application.  For example,
  an application may want to create a command queue per CPU thread.
- There is no implicit binding of command queues to CPU threads. Therefore,
  an application may share a command queue handle across multiple CPU
  threads. However, the application is responsible for ensuring that 
  multiple CPU threads do not access the same command queue simultaneously.
- Commands are submitted to a command queue via command lists and are
  executed in a fifo manner.
- The application is responsible for making sure the GPU is not currently
  executing from a command queue before it is deleted.  This is 
  typically done by tracking command list events, but may also be
  handled by calling ::xeCommandQueueSynchronize.

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

## Command Lists
- A command list represents a sequence of commands for execution on
  a command queue.
- Multiple command lists may be created by an application.  For example,
  an application may want to create multiple command lists per command queue.
- There is no implicit association between a command list and a 
  command queue. Therefore, a command list may be submitted to any, or
  multiple command queues.
- There is no implicit binding of command lists to CPU threads. Therefore,
  an application may share a command list handle across multiple CPU
  threads. However, the application is responsible for ensuring that 
  multiple CPU threads do not access the same command list simultaneously.
- The command list maintains some machine state, which is inherited by
  subsequent commands. See ::xe_command_list_parameter_t for details.
- Command lists do not inherit state from other command lists executed
  on the same command queue.  i.e. each command list begins execution
  in its own default state.
- The application is responsible for calling close before submission
  to a command queue.
- The application is responsible for making sure the GPU is not currently
  executing from a command list before it is deleted.  This should be
  handled by tracking a completion event associated with the command list.
- The application is responsible for making sure the GPU is not currently
  executing from a command list before it is reset.  This should be
  handled by tracking a completion event associated with the command list.

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

The following sample code demonstrates submission of commands to a command queue, via a command list:
```c
    ...
    // finished encoding commands (typically done on another thread)
    xeCommandListClose(hCommandList);

    // Enqueue command list execution into command queue
    xeCommandQueueEnqueueCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

    // synchronize host and GPU
    xeCommandQueueSynchronize(hCommandQueue);

    // Reset (recycle) command list for new commands
    xeCommandListReset(hCommandList);
    ...
```

## Command Graphs (Experimental)
- A command graph represents non-linear dependencies between a collection of command lists to be executed.
- An implementation may use this information to reorder the execution of command lists to be optimized for the device.
- An implementation may also parallelize execution across an application-specified maximum number of command queues.
- The application is responsible for ensuring there are no inter-command list dependencies that would cause dead-lock;
  e.g., infinite loops, synchronization primtives, etc. 
- The application is responsible for calling close before submission to a command queue.
- The command graph itself does not allocate any device memory; therefore is mutable immediately after enqueuing.
- The command graph does not modify or copy any of the command lists.
- The command graph does have references to existing command lists, which must be removed prior to the command lists being destroyed.

The following diagram illustrates a representation of a command graph and how batches of command lists may be submitted to command queues:  
![Queue](../images/core_graph.png?raw=true)  
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
- Execution Barriers are used to insert a dependency between commands submitted to the same command list.
- Commands submitted to a command list are only gaurenteed to start in the same order in which they are submitted;
there is no implicit control of which order they complete.
- Execution barriers provide explicit control to indicate that previous commands must complete prior to
starting the following commands.

The following sample code demonstrates a sequence for submission of an execution barrier:
```c
    xeCommandListEncodeDispatchFunction(hCommandList, hFunction1, ...);

    // Encode a barrier into a command list to ensure hFunction1 completes before hFunction2 begins
    xeCommandListEncodeExecutionBarrier(hCommandList);

    xeCommandListEncodeDispatchFunction(hCommandList, hFunction2, ...);
    ...
```

# <a name="sp">Synchronization Primitives</a>
There are three types of synchronization primitives:
1. **Fences** - used to communicate to the host that command queue execution has completed.
2. **Events** - used as fine-grain host-to-device, device-to-host or device-to-device waits and signals within a command list.
3. **Semaphores** - used for fine-grain control of command lists execution across multiple, simultaneous command queues within a device.

## Fences
- A fence is associated with single command queue.
- A fence can only be signaled from a device's command queue (e.g. between execution of command lists)
and can only be waited upon from the host.
- A fence only has two states: not signaled and signaled.
- A fence cannot be shared across processes.
- An application can use ::{X}FenceQueryElapsedTime to calculate the time (in milliseconds) between two fences' signals.

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

## Events
- An event can be __either__:
  + signaled from within a device's command list (e.g. between execution of kernels) and waited upon from the host or another device, **or**
  + signaled from the host, and waited upon from within a device's command list.
- An event only has two states: not signaled and signaled.
- An event can be encoded into any command list from the same device.
- An event cannot be encoded into multiple command lists simultaneously.
- An event can be shared across processes.
- An application can use ::{X}EventQueryElapsedTime to calculate the time (in milliseconds) between two events signalled by the same device.

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

## Semaphores
- A semaphore can only be signaled and waited upon from within a device's command list.
- A semaphore has both a state and a value.
- A semaphore can be encoded into any command list from the same device.
- A semaphore can be encoded into multiple command lists simultaneously.
- A semaphore cannot be shared across processes.

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
    xeDeviceCreateImage(&imageDesc, &hImage);

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
    xeDeviceSetIntermediateCacheConfig(hDevice, $X_CACHE_CONFIG_LARGE_SLM);
    xeDeviceSetLastLevelCacheConfig(hDevice, $X_CACHE_CONFIG_LARGE_SLM);
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

## Sub-Device Support
A multi-tile device consists of tiles that are tied together by high-speed interconnects. Each tile
has local memory that is shared to other tiles through these interconnects. The API represents tiles
as sub-devices and there are functions to query and obtain a sub-device. Outside of these functions
there are no distinction between sub-devices and devices. 

![Subdevice](../images/core_subdevice.png?raw=true)  
@image latex ../images/core_subdevice.png

If you want to allocate memory and dispatch
tasks to a particular sub-device then obtain the sub-device handle and then use this with the APIs for memory and dispatching work.

```c
    ...
    xeDeviceGetProperties(device, &deviceProps);
    ...

    // Code assumes a specific device configuration.
    assert(deviceProps.numSubDevices == 4);

    // Desire is to allocate and dispatch work to sub-device 2.
    uint32_t subdeviceId = 2;
    xeDeviceGetSubDevice(device, subdeviceId, &subdevice);

    ...
    void* pMemForSubDevice2;
    xeMemAlloc(subDevice, XE_DEVICE_MEM_ALLOC_DEFAULT, memSize, sizeof(uint32_t), &pMemForSubDevice2);
    ...
    
    ...
    xe_command_queue_handle_t commandQueueForSubDevice2;
    xeDeviceCreateCommandQueue(subdevice, desc, &commandQueueForSubDevice2);
    ...
```


# <a name="mnf">Modules and Functions</a>
There are multiple levels of constructs needed for executing functions on the device:
1. A **Module** represents a single translation unit that consists of functions that have been compiled together.
2. A **Function** represents the function within the module that will be dispatched directly from a command list.
3. A **FunctionArgs** represents an instance of arguments to be used by the function when dispatched.

## Modules
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
| -xe-opt-greater-than-4GB-buffer-required    | Optimize offset calculations within buffers.          | Disabled |
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


### Module Caching
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

## Function
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

## Function Attributes

Use xeFunctionQueryAttribute to query attributes from a function object.

```c
    ...
    uint32_t numRegisters;

    // Number of hardware registers used by function.
    xeFunctionQueryAttribute(hFunction, XE_FUNCTION_ATTR_HAS_BARRIERS, &numRegisters);
    ...
```

See xe_function_attribute_t for more information on the attributes.

## FunctionArgs
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

@todo [**Zack**] add function API to query optimal group dimensions from thread count, et al

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
Registering an OpenCL buffer object with Xe merely obtains a pointer to the underlying device memory allocation and does not alter the lifetime of the device memory underlying the OpenCL buffer object.
Freeing the Xe device memory allocation effectively "un-registers" the allocation from Xe, and should be performed before the OpenCL buffer object is destroyed.
Using the Xe device memory allocation after destroying its associated OpenCL buffer object will result in undefined behavior.

Applications are responsible for enforcing memory consistency for shared buffer objects using existing OpenCL and/or Xe APIs.

## cl_program
Xe modules are always in a compiled state and therefore prior to retrieving an xe_module_handle_t from
a cl_program the caller must ensure the cl_program is compiled and linked.

## cl_command_queue
Sharing OpenCL command queues provide opportunities to minimize transition costs when submitting work from an OpenCL queue followed by submitting work to xe command queue and vice-versa.  Enqueuing xe command lists to xe command queues are immediately dispatched to the device.  OpenCL implementations, however, may not necessarily dispatch tasks to the device unless forced by explicit OpenCL API such as clFlush or clFinish.  To minimize overhead between sharing command queues, applications must explicitly dispatch OpenCL command queues using clFlush, clFinish or similar dispatch operations prior to enqueuing an xe command list.  Failing to explicitly dispatch device work may result in undefined behavior.  

Sharing an OpenCL command queue doesn't alter the lifetime of the API object.  It provides knowledge for the driver to potentially reuse some internal resources which may have noticeable overhead when switching the resources.

Memory contents as reflected by any caching schemes will be consistent such that, for example, a memory write  in an OpenCL command queue can be read by a subsequent xe command list without any special user action.  The cost to ensure memory consistency may be implementation dependent.  The performance of sharing command queues will be no worse than an application submitting work to OpenCL, calling clFinish followed by submitting an xe command list.  In most cases, command queue sharing may be much more efficient. 

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
- **GetLastError**
    + quality-of-life addition to enable debug-only error checks, such as:
```c
    assert(XE_RESULT_SUCCESS != GetLastError(hDevice));
    assert(XE_RESULT_SUCCESS != GetLastError(hCommandList));
    assert(XE_RESULT_SUCCESS != GetLastError(hCommandQueue));
    assert(XE_RESULT_SUCCESS != GetLastError(hModule));
    ...
```
