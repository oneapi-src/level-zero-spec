${"#"} Programming Guide (Core)

[DO NOT EDIT]: # (generated from /scripts/core/PROG.md)

The following documents the high-level programming models and guidelines.  

${"##"} Table of Contents
* [Driver and Device](#dnd)
* [Command Queues and Command Lists](#cnc)
* [Synchronization Primitives](#sp)
* [Memory and Image Management](#mim)
* [Modules and Functions](#mnf)
* [OpenCL Interoperability](#oi)

${"#"} <a name="dnd">Driver and Device</a>
The following diagram illustrates the hierarchy of devices to the driver:  
![Driver Hierarchy](../images/core_driver.png?raw=true)

${"##"} Driver
- A driver represents an instance of a ${Xx} driver being loaded and initialized into the current process.
- Only one instance of a driver per process can be loaded.
- There is no reference tracking if multiple drivers are initialized.
- A driver has minimal global state associated; only that which is sufficient for querying devices recognized by the driver.
 
${"##"} Device
- A device represents a physical device in the system that can support ${Xx}.
- More than one device may be available in the system.
- The application is responsible for sharing memory and explicit submission and synchronization across multiple devices.

${"##"} Initialization
The driver API must be initizalized by calling ${x}DriverInit before any other function.
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

    // Get the handle for device that supports required API version
    ${x}_device_handle_t hDevice;
    for(uint32_t i = 0; i < deviceCount; ++i)
    {
        ${x}DriverGetDevice(i, &hDevice);
        
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

${"#"} <a name="cnc">Command Queues and Command Lists</a>
The following diagram illustrates the hierarchy of command lists and command queues to the device:  
![Device Hierarchy](../images/core_queue.png?raw=true)

${"##"} Command Queues
- A command queue represents a physical input stream to the device.
- The number of simultaneous command queues per device is queried from calling 
  ::${x}DeviceGetProperties; returned as ::${x}_device_properties_t.numAsyncComputeEngines
  and ::${x}_device_properties_t.numAsyncCopyEngines.
- Multiple command queues may be created by an application.  For example,
  an application may want to create a command queue per CPU thread.
- There is no implicit binding of command queues to CPU threads. Therefore,
  an application may share a command queue handle across multiple CPU
  threads. However, the application is responsible for ensuring that 
  multiple CPU threads do not access the same command queue simultaneously.
- The command queue maintains some machine state, which is inherited by
  subsequent execution. See ::${x}_command_queue_parameter_t for details.
- Commands are submitted to a command queue via command lists and are
  executed in a fifo manner.
- The application is responsible for making sure the GPU is not currently
  executing from a command queue before it is deleted.  This is 
  typically done by tracking command list events, but may also be
  handled by calling ::${x}CommandQueueSynchronize.

${"##"} Command Lists
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
  subsequent commands. See ${x}_command_list_parameter_t for details.
- Command lists do not inherit state from other command lists executed
  on the same command queue.  i.e. each command list begins execution
  in its own state.
- The application is responsible for calling close before submission
  to a command queue.
- The application is responsible for making sure the GPU is not currently
  executing from a command list before it is deleted.  This should be
  handled by tracking a completion event associated with the command list.
- The application is responsible for making sure the GPU is not currently
  executing from a command list before it is reset.  This should be
  handled by tracking a completion event associated with the command list.

${"##"} Initialization
The following sample code demonstrates a basic sequence for creation of command queues and command lists:
```c
    // Create a command queue
    ${x}_command_queue_desc_t commandQueueDesc = {
        ${X}_COMMAND_QUEUE_DESC_VERSION,
        ${X}_COMMAND_QUEUE_FLAG_NONE,
        ${X}_COMMAND_QUEUE_MODE_DEFAULT
    };
    ${x}_command_queue_handle_t hCommandQueue;
    ${x}DeviceCreateCommandQueue(hDevice, &commandQueueDesc, &hCommandQueue);

    // Create a command list
    ${x}_command_list_desc_t commandListDesc = {
        ${X}_COMMAND_LIST_DESC_VERSION,
        ${X}_COMMAND_LIST_FLAG_NONE
    };
    ${x}_command_list_handle_t hCommandList;
    ${x}DeviceCreateCommandList(hDevice, &commandListDesc, &hCommandList);
    ...
```

${"##"} Submission
The following sample code demonstrates submission of commands to a command queue, via a command list:
```c
    // Encode kernel execution into a command list
    ${x}CommandListEncodeKernelExecution(hCommandList, hKernel);
    ${x}CommandListClose(hCommandList); // finished encoding commands

    // Enqueue command list execution into command queue
    ${x}CommandQueueEnqueueCommandList(hCommandQueue, hCommandList);
    ${x}CommandQueueSynchronize(hCommandQueue); // synchronize host and GPU

    // Reset (recycle) command list for new commands
    ${x}CommandListReset(hCommandList);
    ...
```

${"#"} <a name="sp">Synchronization Primitives</a>
There are three types of synchronization primitives:
1. **Fences** - used to communicate to the host that command queue execution has completed.
2. **Events** - used as fine-grain host-to-device, device-to-host or device-to-device waits and signals within a command list.
3. **Semaphores** - used for fine-grain control of command lists execution across multiple, simultaneous command queues within a device.

${"##"} Fences
- A fence is associated with single command queue.
- A fence can only be signaled from a device's command queue (e.g. between execution of command lists)
and can only be waited upon from the host.
- A fence only has two states: not signaled and signaled.
- A fence cannot be shared across processes.

The following diagram illustrates an example of fences:
![Fence](../images/core_fence.png?raw=true)

The following sample code demonstrates a sequence for creation, submission and querying of a fence:
```c
    // Create fence
    ${x}_fence_desc_t fenceDesc = {
        ${X}_FENCE_DESC_VERSION,
        ${X}_FENCE_FLAG_NONE
    };
    ${x}_fence_handle_t hFence;
    ${x}DeviceCreateFence(hCommandQueue, &fenceDesc, &hFence);

    // Enqueue a signal of the fence into the command queue
    ${x}FenceEnqueueSignal(hFence);

    // Wait for fence to be signaled
    if(${X}_RESULT_SUCCESS != ${x}FenceQueryStatus(hFence))
    {
        ${x}HostWaitOnFence(hFence);
    }

    ${x}FenceReset(hFence);
    ...
```

${"##"} Events
- An event can be __either__:
  + signaled from within a device's command list (e.g. between execution of kernels) and waited upon from the host or another device, **or**
  + signaled from the host, and waited upon from within a device's command list.
- An event only has two states: not signaled and signaled.
- An event can be encoded into any command list from the same device.
- An event cannot be encoded into multiple command lists simultaneously.
- An event can be shared across processes.

The following diagram illustrates an example of events:
![Event](../images/core_event.png?raw=true)

The following sample code demonstrates a sequence for creation and submission of an event:
```c
    // Create event
    ${x}_event_desc_t eventDesc = {
        ${X}_EVENT_DESC_VERSION,
        ${X}_EVENT_FLAG_NONE
    };
    ${x}_event_handle_t hEvent;
    ${x}DeviceCreateEvent(hDevice, &eventDesc, &hEvent);

    // Encode a wait on an event into a command list
    ${x}CommandListEncodeWaitOnEvent(hCommandList, hEvent);

    // Enqueue wait via the command list into a command queue
    ${x}CommandQueueEnqueueCommandList(hCommandQueue, hCommandList);

    // Signal the device
    ${x}HostSignalEvent(hEvent);
    ...
```

${"##"} Semaphores
- A semaphore can only be signaled and waited upon from within a device's command list.
- A semaphore has both a state and a value.
- A semaphore can be encoded into any command list from the same device.
- A semaphore can be encoded into multiple command lists simultaneously.
- A semaphore cannot be shared across processes.

The following diagram illustrates an example of semaphores:
![Semaphore](../images/core_semaphore.png?raw=true)

The following sample code demonstrates a sequence for creation and submission of a semaphore:
```c
    // Create semaphore
    ${x}_semaphore_desc_t semaphoreDesc = {
        ${X}_SEMAPHORE_DESC_VERSION,
        ${X}_SEMAPHORE_FLAG_NONE
    };
    ${x}_semaphore_handle_t hSemaphore;
    ${x}DeviceCreateSemaphore(hDevice, &semaphoreDesc, &hSemaphore);

    // Encode a wait on an semaphore into a command list
    ${x}CommandListEncodeSemaphoreWait(hCommandList0, hSemaphore,
        ${X}_SEMAPHORE_WAIT_OPERATION_GREATER_OR_EQUAL_TO, 1);

    // Encode a signal of a semaphore into another command list
    ${x}CommandListEncodeSemaphoreSignal(hCommandList1, hSemaphore, 1);

    // Enqueue the command lists into the parallel command queues
    ${x}CommandQueueEnqueueCommandList(hCommandQueue0, hCommandList0);
    ${x}CommandQueueEnqueueCommandList(hCommandQueue1, hCommandList1);
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

* ::${X}_MEMORY_ACCESS - if a device supports access (read or write) to allocations of the specified type.
* ::${X}_MEMORY_ATOMIC_ACCESS - if a device support atomic access to allocations of the specified type.
* ::${X}_MEMORY_CONCURRENT_ACCESS - if a device supports concurrent access to allocations of the specified type, or another device's allocation of the specified type.
* ::${X}_MEMORY_CONCURRENT_ATOMIC_ACCESS - if a device supports concurrent atomic access to allocations of the specified type, or another device's allocations of the specified type.

${"###"} Prefetch and Memory Advice

**Shared** allocations may be prefetched to a supporting device via the ::${x}CommandListEncodeMemoryPrefetch API.

Additionally, an application may provide memory advices for a **shared** allocation via the ::${x}MemAdvise API, to override driver heuristics or migration policies.

${"##"} Images
An image is used to store multi-dimensional and format-defined memory for optimal device access.
An image's contents can be copied to and from other images, as well as host-accessable memory allocations.
This is the only method for host access to the contents of an image.
This methodology allows for device-specific encoding of image contents (e.g., tile swizzle patterns, loseless compression, etc.) 
and avoids exposing these details in the API in a backwards compatible fashion.

```c
    ${x}_image_desc_t imageDesc = {
        ${X}_IMAGE_DESC_VERSION,
        ${X}_IMAGE_FLAG_KERNEL_READ,
        ${X}_IMAGE_TYPE_2D,
        ${X}_IMAGE_FORMAT_FLOAT32, 1,
        128, 128, 0, 0, 0
    };
    ${x}_image_handle_t hImage;
    ${x}DeviceCreateImage(&imageDesc, &hImage);

    // upload contents from host pointer
    ${x}CommandListEncodeImageCopyFromMemory(hCommandList, hImage, nullptr, pImageData);
    ...
```

${"##"} Device Cache Settings
@todo Ankur: global vs allocation vs command queue

${"##"} Device Residency
For devices that do not support page-faults, the driver must ensure that all pages that will be accessed by the kernel are resident before program execution.
This can be determined by checking ${x}_device_memory_properties_t.onDemandPageFaults.

In most cases, the driver implicitly handles residency of allocations for device access.
This can be done by inspecting API parameters, including function arguments.
However, in cases where the devices does **not** support page-faulting _and_ the driver is incapable of determining whether an allocation will be accessed by the device,
such as multiple levels of indirection, there are two methods available:
1. the application may set the ::${X}_FUNCTION_FLAG_FORCE_RESIDENCY flag during program creation to force all device allocations to be resident during execution.
2. explcit APIs are included for the application to dynamically change residency as needed.

If the application does not properly manage residency for these cases then the device may experience unrecoverable page-faults.

```c
    struct node {
        node* next;
    };
    node* begin = nullptr;
    ${x}MemAlloc(hDevice, sizeof(node), &begin);
    ${x}MemAlloc(hDevice, sizeof(node), &begin->next);
    ${x}MemAlloc(hDevice, sizeof(node), &begin->next->next);

    // 'begin' is passed as function argument and encoded into command list
    ...

    // Make indirect allocations resident before enqueuing
    ${x}DeviceMakeMemoryResident(hDevice, begin->next, sizeof(node));
    ${x}DeviceMakeMemoryResident(hDevice, begin->next->next, sizeof(node));

    ${x}CommandQueueEnqueueCommandList(hCommandQueue, hCommandList);

    // wait until complete
    ${x}FenceEnqueueSignal(hFence);
    ${x}HostWaitOnFence(hFence);

    // Finally, evict to free device resources
    ${x}DeviceEvictMemory(hDevice, begin->next, sizeof(node));
    ${x}DeviceEvictMemory(hDevice, begin->next->next, sizeof(node));
    ...
```

${"#"} <a name="mnf">Modules and Functions</a>
There are multiple levels of constructs needed for executing functions on the device:
1. A **Module** represents a single translation unit that consists of functions that have been compiled together.
2. A **Function** represents the function within the module that will be dispatched directly from a command list.
3. A **FunctionArgs** represents an instance of arguments to be used by the function when dispatched.

${"##"} Modules
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
        ${X}_MODULE_DESC_VERSION
        ${X}_MODULE_IL_SPIRV,
        ilSize,
        pImageScalingIL
    };
    ${x}_module_handle_t hModule;
    ${x}DeviceCreateModule(hDevice, &moduleDesc, &hModule);
    ...
```

${"##"} Function
Functions are immuatable references to functions within a module.

The following sample code demonstrates a sequence for creating a function from a module:
```c
    ${x}_function_desc_t functionDesc = {
        ${X}_FUNCTION_DESC_VERSION,
        ${X}_FUNCTION_FLAG_NONE,
        "image_scaling"
    };
    ${x}_function_handle_t hFunction;
    ${x}ModuleCreateFunction(hModule, &functionDesc, &hFunction);
    ...
```

${"##"} FunctionArgs
FunctionArgs represent an instance of argument values to be used by the function when called.

The following sample code demonstrates a sequence for creating function args and dispatching the function:
```c
    ${x}_function_args_handle_t hFunctionArgs;
    ${x}FunctionCreateFunctionArgs(hFunction, &hFunctionArgs);

    // Bind arguments
    ${x}FunctionArgsSetValue(hFuncArgs, 0, sizeof(${x}_image_handle_t), &src_image);
    ${x}FunctionArgsSetValue(hFuncArgs, 1, sizeof(${x}_image_handle_t), &dest_image);
    ${x}FunctionArgsSetValue(hFuncArgs, 2, sizeof(uint32_t), &width);
    ${x}FunctionArgsSetValue(hFuncArgs, 3, sizeof(uint32_t), &height);

    // Encode dispatch command
    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, hFunctionArgs, pixelRegionWidth, pixelRegionHeight, 1, numRegionsX, numRegionsY, 1);
    ...
```

The following sample code demonstrates a sequence for querying argument indices from the function by name:
```c
    uint32_t src_img_index;
    ${x}FunctionGetArgIndexFromName(hFunc, "src_img", &src_img_index);

    // Bind arguments
    ${x}FunctionArgsSetValue(hFuncArgs, src_img_index, sizeof(${x}_image_handle_t), &src_image);
    ...
```

${"##"} Occupancy
@todo Zack: write-up section

${"#"} <a name="oi">OpenCL Interoperability</a>
There are three OpenCL objects that can be shared for interoperability:
1. **cl_mem** - an OpenCL buffer object
2. **cl_program** - an OpenCL program object
3. **cl_command_queue** - an OpenCL command queue object

${"##"} cl_mem
@todo Ben any details about memory sharing

${"##"} cl_program
@todo Zack any details about program sharing
- clBuildProgram or clCompileProgram/clLinkProgram must be called prior to ${x}DeviceRegisterCLProgram

${"##"} cl_command_queue
@todo Brandon any details about command queue sharing
- clFlush must be called prior to any ${x}CommandQueueEnqueue* function

