# Programming Guide
The following documents the high-level programming models and guidelines.

## Introduction
The Intel Xe Driver API provides the lowest-level, fine-grain and most explicit control over:
- Memory Allocation and Cross-Process Sharing
- Kernel Submission
- Asynchronous Execution and Scheduling
- Synchronization Primitives
- Metrics Reporting

### Naming Convention
todo: 
- all types follow **xe_\<name\>_t** convention
- all macros and enumerator values use all caps **XE_\<SCOPE\>_\<NAME\>** convention
- all functions use **xe\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters

### Error Handling
todo:
- all apis return ::xe_result_t.
- apis are gaurenteed to never throw exceptions. etc.

## Driver and Device
todo

### Initialization
The following sample code demonstrates a basic initialization sequence:
```c
    // Initialize the driver
    xeInit(XE_INIT_FLAG_NONE);

    // Get number of devices supporting Xe
    uint32_t deviceCount = 0;
    xeDeviceGetCount(&deviceCount);
    if(0 == deviceCount)
    {
        printf("There is no device supporting Xe.\n");
        return;
    }

    // Get the handle for device 0
    xe_device_handle_t xeDevice;
    xeDeviceGet(0, &xeDevice);
    ...
```

## Command Queues and Command Lists
The following diagram illustrates the hierarchy of command lists and command queues to the device:
![Hierarchy](../images/cmdqueue.png?raw=true)

### Command Queues
- A command queue represents a physical input stream to the device.
- The number of command queues per device is queried from calling 
  ::xeGetDeviceProperties; returned as ::xe_device_properties_t.numAsyncComputeEngines.
- Multiple command queues may be created by an application.  For example,
  an application may want to create a command queue per CPU thread.
- There is no implicit binding of command queues to CPU threads. Therefore,
  an application may share a command queue handle across multiple CPU
  threads. However, the application is responsible for ensuring that 
  multiple CPU threads do not access the same command queue simultaneously.
- The command queue maintains some machine state, which is inherited by
  subsequent execution. See ::xe_command_queue_parameter_t for details.
- Commands are submitted to a command queue via command lists and are
  executed in a fifo manner.
- The application is responsible for making sure the GPU is not currently
  executing from a command queue before it is deleted.  This is 
  typically done by tracking command list events, but may also be
  handled by calling ::xeCommandQueueSynchronize.

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
  subsequent commands. See xe_command_list_parameter_t for details.
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
    xe_command_queue_desc_t xeCommandQueueDesc = {
        XE_COMMAND_QUEUE_DESC_VERSION,
        XE_COMMAND_QUEUE_FLAG_DEFAULT
    };
    xe_command_queue_handle_t xeCommandQueue;
    xeCommandQueueCreate(xeDevice, &xeCommandQueueDesc, &xeCommandQueue);

    // Create a command list
    xe_command_list_desc_t xeCommandListDesc = {
        XE_COMMAND_LIST_DESC_VERSION,
        XE_COMMAND_LIST_FLAG_NONE
    };
    xe_command_list_handle_t xeCommandList;
    xeCommandListCreate(xeDevice, &xeCommandListDesc, &xeCommandList);
    ...
```

### Submission
The following sample code demonstrates submission of commands to a command queue, via a command list:
```c
    // Encode kernel execution into a command list
    xeCommandListEncodeKernelExecution(xeCommandList, xeKernel);
    xeCommandListClose(xeCommandList); // finished encoding commands

    // Enqueue command list execution into command queue
    xeCommandQueueEnqueueCommandList(xeCommandQueue, xeCommandList);
    xeCommandQueueSynchronize(xeCommandQueue); // synchronize host and GPU

    // Reset (recycle) command list for new commands
    xeCommandListReset(xeCommandList);
    ...
```

## Synchronization Primitives
There are three types of synchronization objects:
1. **Fences** - used to communicate to the host that command queue execution has completed.
2. **Semaphores** - used to control execution of command lists across multiple, simultaneous command queues.
3. **Events** - used as fine-grain host-to-device or device-to-host waits and signals within a command list.

### Fences
A fence can only be signaled from the device's command queue (e.g. between execution of command lists)
and waits are only allowed on the host.

The following sample code demonstrates a sequence for creation, submission and querying of a fence:
```c
    // Create fence
    xe_fence_desc_t xeFenceDesc = {
        XE_FENCE_DESC_VERSION,
        XE_FENCE_FLAG_NONE
    };
    xe_fence_handle_t xeFence;
    xeFenceCreate(xeDevice, &xeFenceDesc, &xeFence);

    // Enqueue a signal of the fence into a command queue
    xeCommandQueueEnqueueSignalFence(xeCommandQueue, xeFence);

    // 
    xeFenceGetStatus
    ...
```

### Semaphores
The following sample code demonstrates...
```c
    ...
```

### Events
An event can be __either__:
- signaled from within a command list (e.g. between execution of kernels) and waits occur on the host, **or**
- signaled from the host, and waits occur within a command list.

The following sample code demonstrates a sequence for creation of an event objects:
```c
    // Create event(s)
    xe_event_desc_t xeEventDesc = {
        XE_EVENT_DESC_VERSION,
        XE_EVENT_FLAG_DEVICE_TO_HOST
    };
    xe_event_handle_t xeEvent;
    xeEventCreate(xeDevice, &xeEventDesc, &xeEvent);
    ...
```

## Memory Allocation
todo

