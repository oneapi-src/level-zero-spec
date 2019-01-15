# Driver API Programming Guide
The following documents the high-level programming models and guidelines.

@cond DEV
DO NOT EDIT: generated from /scripts/templates/driver.md.mako
@endcond

## Introduction
The Intel ${Xx} Driver API provides the lowest-level, fine-grain and most explicit control over:
- Memory Allocation and Cross-Process Sharing
- Kernel Submission
- Asynchronous E${x}cution and Scheduling
- Synchronization Primitives
- Metrics Reporting

### Naming Convention
todo: 
- all types follow **${x}_\<name\>_t** convention
- all macros and enumerator values use all caps **${X}_\<SCOPE\>_\<NAME\>** convention
- all functions use **${x}\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters

### Error Handling
todo:
- all apis return ::${x}_result_t.
- apis are gaurenteed to never throw exceptions. etc.

## Driver and Device
The following diagram illustrates the hierarchy of devices to the driver:  
![Driver Hierarchy](../images/driver.png?raw=true)

### Driver
 - A driver represents an instance of a ${Xx} driver being loaded and initialized into the current process.
 - Only one instance of a driver per process can be loaded.
 - There is no reference tracking if multiple drivers are initialized.
 - A driver has minimal global state associated; only that which is sufficient for querying devices recognized by the driver.
 
 ### Device
 - A device represents a physical device in the system that can support ${Xx}.
 - More than one device may be avilable in the system.

### Initialization
The following sample code demonstrates a basic initialization sequence:
```c
    // Initialize the driver
    ${x}Init(${X}_INIT_FLAG_NONE);

    // Get number of devices supporting ${Xx}
    uint32_t deviceCount = 0;
    ${x}DeviceGetCount(&deviceCount);
    if(0 == deviceCount)
    {
        printf("There is no device supporting ${Xx}.\n");
        return;
    }

    // Get the handle for device 0
    ${x}_device_handle_t ${x}Device;
    ${x}DeviceGet(0, &${x}Device);
    ...
```

## Command Queues and Command Lists
The following diagram illustrates the hierarchy of command lists and command queues to the device:  
![Device Hierarchy](../images/cmdqueue.png?raw=true)

### Command Queues
- A command queue represents a physical input stream to the device.
- The number of command queues per device is queried from calling 
  ::${x}GetDeviceProperties; returned as ::${x}_device_properties_t.numAsyncComputeEngines.
- Multiple command queues may be created by an application.  For example,
  an application may want to create a command queue per CPU thread.
- There is no implicit binding of command queues to CPU threads. Therefore,
  an application may share a command queue handle across multiple CPU
  threads. However, the application is responsible for ensuring that 
  multiple CPU threads do not access the same command queue simultaneously.
- The command queue maintains some machine state, which is inherited by
  subsequent e${x}cution. See ::${x}_command_queue_parameter_t for details.
- Commands are submitted to a command queue via command lists and are
  e${x}cuted in a fifo manner.
- The application is responsible for making sure the GPU is not currently
  e${x}cuting from a command queue before it is deleted.  This is 
  typically done by tracking command list events, but may also be
  handled by calling ::${x}CommandQueueSynchronize.

### Command Lists
- A command list represents a sequence of commands for e${x}cution on
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
- Command lists do not inherit state from other command lists e${x}cuted
  on the same command queue.  i.e. each command list begins e${x}cution
  in its own state.
- The application is responsible for calling close before submission
  to a command queue.
- The application is responsible for making sure the GPU is not currently
  e${x}cuting from a command list before it is deleted.  This should be
  handled by tracking a completion event associated with the command list.
- The application is responsible for making sure the GPU is not currently
  e${x}cuting from a command list before it is reset.  This should be
  handled by tracking a completion event associated with the command list.

### Initialization
The following sample code demonstrates a basic sequence for creation of command queues and command lists:
```c
    // Create a command queue
    ${x}_command_queue_desc_t ${x}CommandQueueDesc = {
        ${X}_COMMAND_QUEUE_DESC_VERSION,
        ${X}_COMMAND_QUEUE_FLAG_DEFAULT
    };
    ${x}_command_queue_handle_t ${x}CommandQueue;
    ${x}CommandQueueCreate(${x}Device, &${x}CommandQueueDesc, &${x}CommandQueue);

    // Create a command list
    ${x}_command_list_desc_t ${x}CommandListDesc = {
        ${X}_COMMAND_LIST_DESC_VERSION,
        ${X}_COMMAND_LIST_FLAG_NONE
    };
    ${x}_command_list_handle_t ${x}CommandList;
    ${x}CommandListCreate(${x}Device, &${x}CommandListDesc, &${x}CommandList);
    ...
```

### Submission
The following sample code demonstrates submission of commands to a command queue, via a command list:
```c
    // Encode kernel e${x}cution into a command list
    ${x}CommandListEncodeKernelE${x}cution(${x}CommandList, ${x}Kernel);
    ${x}CommandListClose(${x}CommandList); // finished encoding commands

    // Enqueue command list e${x}cution into command queue
    ${x}CommandQueueEnqueueCommandList(${x}CommandQueue, ${x}CommandList);
    ${x}CommandQueueSynchronize(${x}CommandQueue); // synchronize host and GPU

    // Reset (recycle) command list for new commands
    ${x}CommandListReset(${x}CommandList);
    ...
```

## Synchronization Primitives
There are three types of synchronization primitives:
1. **Fences** - used to communicate to the host that command queue e${x}cution has completed.
2. **Events** - used as fine-grain host-to-device, device-to-host or device-to-device waits and signals within a command list.
3. **Semaphores** - used for fine-grain control of command lists e${x}cution across multiple, simultaneous command queues within a device.

### Fences
- A fence can only be signaled from a device's command queue (e.g. between e${x}cution of command lists)
and can only be waited upon from the host.
- A fence only has two states: not signaled and signaled.
- A fence can be enqueued on any command queue from the same device.
- A fence cannot be enqueud on multiple command queues simultaneously.
- A fence can be shared across processes.

The following sample code demonstrates a sequence for creation, submission and querying of a fence:
```c
    // Create fence
    ${x}_fence_desc_t ${x}FenceDesc = {
        ${X}_FENCE_DESC_VERSION,
        ${X}_FENCE_FLAG_NONE
    };
    ${x}_fence_handle_t ${x}Fence;
    ${x}FenceCreate(${x}Device, &${x}FenceDesc, &${x}Fence);

    // Enqueue a signal of the fence into a command queue
    ${x}CommandQueueEnqueueSignalFence(${x}CommandQueue, ${x}Fence);

    // Wait for fence to be signaled
    if(${X}_RESULT_SUCCESS != ${x}FenceQueryStatus(${x}Fence)
    {
        ${x}FenceWait(${x}Fence);
    }

    ${x}FenceReset(${x}Fence);
    ...
```

### Events
- An event can be __either__:
  + signaled from within a device's command list (e.g. between e${x}cution of kernels) and waited upon from the host or another device, **or**
  + signaled from the host, and waited upon from within a device's command list.
- An event only has two states: not signaled and signaled.
- An event can be encoded into any command list from the same device.
- An event cannot be encoded into multiple command lists simultaneously.
- An event can be shared across processes.

The following sample code demonstrates a sequence for creation and submission of an event:
```c
    // Create event
    ${x}_event_desc_t ${x}EventDesc = {
        ${X}_EVENT_DESC_VERSION,
        ${X}_EVENT_FLAG_NONE
    };
    ${x}_event_handle_t ${x}Event;
    ${x}EventCreate(${x}Device, &${x}EventDesc, &${x}Event);

    // Encode a wait on an event into a command list
    ${x}CommandListEncodeWaitOnEvent(${x}CommandList, ${x}Event);

    // Enqueue wait via the command list into a command queue
    ${x}CommandQueueEnqueueCommandList(${x}CommandQueue, ${x}CommandList);

    // Signal the device
    ${x}EventSignal(${x}Event);
    ...
```

### Semaphores
- A semaphore can only be signaled and waited upon from within a device's command list.
- A semaphore has both a state and a value.
- A semaphore can be encoded into any command list from the same device.
- A semaphore can be encoded into multiple command lists simultaneously.
- A semaphore cannot be shared across processes.

The following sample code demonstrates a sequence for creation and submission of a semaphore:
```c
    // Create semaphore
    ${x}_semaphore_desc_t ${x}SemaphoreDesc = {
        ${X}_SEMAPHORE_DESC_VERSION,
        ${X}_SEMAPHORE_FLAG_NONE
    };
    ${x}_semaphore_handle_t ${x}Semaphore;
    ${x}EventCreate(${x}Device, &${x}SemaphoreDesc, &${x}Semaphore);

    // Encode a wait on an semaphore into a command list
    ${x}CommandListEncodeSemaphoreWait(${x}CommandList0, ${x}Semaphore,
        ${X}_SEMAPHORE_WAIT_OPERATION_GREATER_OR_EQUAL_TO, 1);

    // Encode a signal of a semaphore into another command list
    ${x}CommandListEncodeSemaphoreSignal(${x}CommandList1, ${x}Semaphore, 1);

    // Enqueue the command lists into the parallel command queues
    ${x}CommandQueueEnqueueCommandList(${x}CommandQueue0, ${x}CommandList0);
    ${x}CommandQueueEnqueueCommandList(${x}CommandQueue1, ${x}CommandList1);
    ...
```

## Memory Allocation
todo

