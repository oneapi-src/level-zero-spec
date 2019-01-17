# Runtime API Programming Guide
The following documents the high-level programming models and guidelines.

@cond DEV
DO NOT EDIT: generated from /scripts/templates/runtime.md.mako
@endcond

## Introduction  
The Intel Xi Runtime API provides low-level support for:
- Memory Allocation and Cross-Process Sharing
- Kernel Submission
- Execution and Scheduling
- Synchronization Primitives
- Metrics Reporting

The Xi runtime API is implemented in the xi.dll, which is copied on the system during installation of the device driver.

### Naming Convention  
- all runtime entry points are prefixed with xi
- all types follow **xi_\<name\>_t** convention
- all macros and enumerator values use all caps **XI_\<SCOPE\>_\<NAME\>** convention
- all functions use **xi\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters
  
### Error Handling  
- all functions return ::xi_result_t.
- all functions are gaurenteed to never throw exceptions or fail silently.
  
## Context and Device  
![Context Hierarchy](../images/context.png?raw=true)
  
### Context  
- A context manages memory, command queues and programs for execution on one or more devices
  
### Device  
- A device represents a physical device in the system that can support Xi.
- More than one device may be available in the system.
  
### Initialization  
The application does not need to explicitly initialize or load the runtime dll.
The runtime is implicitly initialized on first use.  

The following sample code demonstrates a basic initialization sequence:
```c
    // Get number of devices supporting Xi
    uint32_t deviceCount = 0;
    xiDeviceGetCount(&deviceCount);
    if(0 == deviceCount)
    {
        printf("There is no device supporting Xi.\n");
        return;
    }

    // Get the handle for device 0
    xi_device_handle_t hDevice;
    xiDeviceGet(0, &hDevice);
    
    // Create the context
    xi_context_desc_t desc;
    desc.version = XI_CONTEXT_DESC_VERSION;
    desc.numDevices = 1;
    desc.hDevices = &hDevice;
    
    xi_context_handle_t hContext;
    if(XI_RESULT_SUCCESS != xiContextCreate(&desc, &hContext))
    {
        printf("Context creation failed.\n");
        return;
    }
    ...
```
  
## Command Queues and Command Lists
The following diagram illustrates the hierarchy of command lists and command queues to the context and device:  
![Device Hierarchy](../images/context_queue.png?raw=true)

### Command Queues
- A command queue represents a physical input stream to the device.
- The number of command queues per device is queried from calling 
  ::xiDeviceGetProperties; returned as ::xi_device_properties_t.numAsyncComputeEngines.
- Multiple command queues may be created by an application.  For example,
  an application may want to create a command queue per CPU thread.
- There is no implicit binding of command queues to CPU threads. Therefore,
  an application may share a command queue handle across multiple CPU
  threads. However, the application is responsible for ensuring that 
  multiple CPU threads do not access the same command queue simultaneously.
- The command queue maintains some machine state, which is inherited by
  subsequent execution. See ::xi_command_queue_parameter_t for details.
- Commands are submitted to a command queue via command lists and are
  executed in a fifo manner.
- The application is responsible for making sure the GPU is not currently
  executing from a command queue before it is deleted.  This is 
  typically done by tracking command list events, but may also be
  handled by calling ::xiCommandQueueSynchronize.

### Command Lists
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
  subsequent commands. See xi_command_list_parameter_t for details.
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

### Initialization
The following sample code demonstrates a basic sequence for creation of command queues and command lists:
```c
    // Create a command queue
    xi_command_queue_desc_t commandQueueDesc = {
        XI_COMMAND_QUEUE_DESC_VERSION,
        XI_COMMAND_QUEUE_FLAG_DEFAULT
    };
    xi_command_queue_handle_t hCommandQueue;
    xiCommandQueueCreate(hContext, hDevice, &commandQueueDesc, &hCommandQueue);

    // Create a command list
    xi_command_list_desc_t commandListDesc = {
        XI_COMMAND_LIST_DESC_VERSION,
        XI_COMMAND_LIST_FLAG_NONE
    };
    xi_command_list_handle_t hCommandList;
    xiCommandListCreate(hContext, hDevice, &commandListDesc, &hCommandList);
    ...
```

### Submission
The following sample code demonstrates submission of commands to a command queue, via a command list:
```c
    // Encode kernel execution into a command list
    xiCommandListEncodeKernelExecution(hCommandList, hKernel);
    xiCommandListClose(hCommandList); // finished encoding commands

    // Enqueue command list execution into command queue
    xiCommandQueueEnqueueCommandList(hCommandQueue, hCommandList);
    xiCommandQueueSynchronize(hCommandQueue); // synchronize host and GPU

    // Reset (recycle) command list for new commands
    xiCommandListReset(hCommandList);
    ...
```

## Synchronization Primitives
There are two types of synchronization primitives:
1. **Fences** - used to communicate to the host that command queue execution has completed.
2. **Events** - used as fine-grain host-to-device, device-to-host or device-to-device waits and signals within a command list.

### Fences
- A fence is associated with single command queue.
- A fence can only be signaled from a command queue (e.g. between execution of command lists)
and can only be waited upon from the host.
- A fence only has two states: not signaled and signaled.
- A fence cannot be shared across processes.

The following sample code demonstrates a sequence for creation, submission and querying of a fence:
```c
    // Create fence
    xi_fence_desc_t fenceDesc = {
        XI_FENCE_DESC_VERSION,
        XI_FENCE_FLAG_NONE
    };
    xi_fence_handle_t hFence;
    xiFenceCreate(hCommandQueue, &fenceDesc, &hFence);

    // Enqueue a signal of the fence into the command queue
    xiEnqueueSignalFence(hFence);

    // Wait for fence to be signaled
    if(XI_RESULT_SUCCESS != xiFenceQueryStatus(hFence)
    {
        xiFenceWait(hFence);
    }

    xiFenceReset(hFence);
    ...
```

### Events
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
    xi_event_desc_t eventDesc = {
        XI_EVENT_DESC_VERSION,
        XI_EVENT_FLAG_NONE
    };
    xi_event_handle_t hEvent;
    xiEventCreate(hDevice, &eventDesc, &hEvent);

    // Encode a wait on an event into a command list
    xiCommandListEncodeWaitOnEvent(hCommandList, hEvent);

    // Enqueue wait via the command list into a command queue
    xiCommandQueueEnqueueCommandList(hCommandQueue, hCommandList);

    // Signal the device
    xiEventSignal(hEvent);
    ...
```

## Memory Allocation  
todo

