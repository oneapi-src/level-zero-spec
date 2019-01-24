${"#"} Core API Programming Guide

[DO NOT EDIT]: # (generated from /scripts/core/PROG.md)

The following documents the high-level programming models and guidelines.  

${"##"} Driver and Device
The following diagram illustrates the hierarchy of devices to the driver:  
![Driver Hierarchy](../images/core_driver.png?raw=true)

${"###"} Driver
- A driver represents an instance of a ${Xx} driver being loaded and initialized into the current process.
- Only one instance of a driver per process can be loaded.
- There is no reference tracking if multiple drivers are initialized.
- A driver has minimal global state associated; only that which is sufficient for querying devices recognized by the driver.
 
${"###"} Device
- A device represents a physical device in the system that can support ${Xx}.
- More than one device may be available in the system.
- The application is responsible for sharing memory and explicit submission and synchronization across multiple devices.

${"###"} Initialization
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

${"##"} Command Queues and Command Lists
The following diagram illustrates the hierarchy of command lists and command queues to the device:  
![Device Hierarchy](../images/core_queue.png?raw=true)

${"###"} Command Queues
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

${"###"} Command Lists
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

${"###"} Initialization
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

${"###"} Submission
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

${"##"} Synchronization Primitives
There are three types of synchronization primitives:
1. **Fences** - used to communicate to the host that command queue execution has completed.
2. **Events** - used as fine-grain host-to-device, device-to-host or device-to-device waits and signals within a command list.
3. **Semaphores** - used for fine-grain control of command lists execution across multiple, simultaneous command queues within a device.

${"###"} Fences
- A fence is associated with single command queue.
- A fence can only be signaled from a device's command queue (e.g. between execution of command lists)
and can only be waited upon from the host.
- A fence only has two states: not signaled and signaled.
- A fence cannot be shared across processes.

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
    if(${X}_RESULT_SUCCESS != ${x}FenceQueryStatus(hFence)
    {
        ${x}HostWaitOnFence(hFence);
    }

    ${x}FenceReset(hFence);
    ...
```

${"###"} Events
- An event can be __either__:
  + signaled from within a device's command list (e.g. between execution of kernels) and waited upon from the host or another device, **or**
  + signaled from the host, and waited upon from within a device's command list.
- An event only has two states: not signaled and signaled.
- An event can be encoded into any command list from the same device.
- An event cannot be encoded into multiple command lists simultaneously.
- An event can be shared across processes.

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

${"###"} Semaphores
- A semaphore can only be signaled and waited upon from within a device's command list.
- A semaphore has both a state and a value.
- A semaphore can be encoded into any command list from the same device.
- A semaphore can be encoded into multiple command lists simultaneously.
- A semaphore cannot be shared across processes.

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

${"##"} Memory and Image Management
There are two types of allocations:
1. Memory - linear, unformatted allocations for direct access from both the host and device.
2. Images - non-linear, formatted allocations for direct access from the device.

${"###"} Memory
@todo Ben: describe standard, managed, and shared

${"###"} Images
An image is used to store multi-dimensional and format-defined memory for optimal device access.
An image's contents can be copied to and from other images, as well as host-accessable memory allocations.
This is the only method for host access to the contents of an image.
This methodology allows for device-specific encoding of image contents (e.g., tile swizzle patterns, loseless compression, etc.) 
and avoids exposing these details in the API in a backwards compatible fashion.

```c
    ...
```

${"###"} Device Cache Settings
@todo Ankur: global vs allocation vs command queue

${"###"} Device Residency
In most cases, the driver implicitly handles residency of allocations for device access.
This can be done by inspecting API parameters, including function arguments.

However, in cases where the driver is incapable of determining whether an allocation will be accessed by the device, such as multiple levels of indirection,
there are two methods available.
1. the application may set a flag during memory allocation to force the allocation to be always resident.
2. explcit APIs are included for the application to dynamically change residency as needed.

If the application does not properly manage residency for these cases then the device may experience unrecoverable page-faults.

```c
    ...
```

${"###"} 

${"##"} Modules and Functions
A Module represents a single translation unit that consists of functions that have been compiled together.

- Modules can be created from an IL or directly from ISA using ${x}CreateModule.
  + ${x}CreateModule takes a format argument that specifies the input format.
  + ${x}CreateModule performs a compilation step when format is IL.
- The ISA can be queried from a Module using ${x}ModuleGetISA.

```c
    ...
    ${x}_module_handle_t hModule;
    ${x}CreateModule(hDevice, XE_MODULE_IL_SPIRV_TEXT, strlen(pIL), pIL, &hModule);

    ${x}_function_handle_t hFunction;
    ${x}ModuleCreateFunction(hModule, "vecsum", &hFunction);

    ${x}_function_args_handle_t hFunctionArgs;
    ${x}CreateFunctionArgs(hFunction, &hFunctionArgs);

    ${x}SetFunctionArgValue(hFunctionArgs, 0, sizeof(uint32_t), &rowLength);

    ${x}CommandListEncodeDispatchFunction(hCommandList, hFunction, hFunctionArgs, rowLength, 1, 1, numRows, 1, 1);

    ...
	
    ${x}DestroyFunctionArgs(hFunctionArgs);
    ${x}DestroyFunction(hFunction);
    ${x}DestroyModule(hModule);
```

${"###"} Occupancy
@todo Zack: write-up section
