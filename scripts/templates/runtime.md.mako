${"#"} Runtime API Programming Guide
The following documents the high-level programming models and guidelines.

@cond DEV
DO NOT EDIT: generated from /scripts/templates/runtime.md.mako
@endcond

${"##"} Introduction  
The Intel ${Xx} Runtime API provides...
  
${"###"} Naming Convention  
todo: 
- all types follow **${x}_\<name\>_t** convention
- all macros and enumerator values use all caps **${X}_\<SCOPE\>_\<NAME\>** convention
- all functions use **${x}\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters
  
${"###"} Error Handling  
todo:
- all apis return ::${x}_result_t.
- apis are gaurenteed to never throw exceptions. etc.
  
${"##"} Context and Device  
![Context Hierarchy](../images/context.png?raw=true)
  
${"###"} Context  
- A context manages memory, command queues and programs for execution on one or more devices
  
${"###"} Device  
- A device represents a physical device in the system that can support ${Xx}.
- More than one device may be available in the system.
  
${"###"} Initialization  
The following sample code demonstrates a basic initialization sequence:
```c
    // Initialize the runtime
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
    ${x}_device_handle_t hDevice;
    ${x}DeviceGet(0, &hDevice);
    
    // Create the context
    ${x}_context_desc_t desc;
    desc.version = ${X}_CONTEXT_DESC_VERSION;
    desc.numDevices = 1;
    desc.hDevices = &hDevice;
    
    $x_context_handle_t hContext;
    if(${X}_RESULT_SUCCESS != ${x}ContextCreate(&desc, &hContext))
    {
        printf("Context creation failed.\n");
        return;
    }
    ...
```
  
${"##"} Command Queues and Command Lists
The following diagram illustrates the hierarchy of command lists and command queues to the context and device:  
![Device Hierarchy](../images/context_queue.png?raw=true)

${"###"} Command Queues
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
        ${X}_COMMAND_QUEUE_FLAG_DEFAULT
    };
    ${x}_command_queue_handle_t hCommandQueue;
    ${x}CommandQueueCreate(hContext, hDevice, &commandQueueDesc, &hCommandQueue);

    // Create a command list
    ${x}_command_list_desc_t commandListDesc = {
        ${X}_COMMAND_LIST_DESC_VERSION,
        ${X}_COMMAND_LIST_FLAG_NONE
    };
    ${x}_command_list_handle_t hCommandList;
    ${x}CommandListCreate(hContext, hDevice, &commandListDesc, &hCommandList);
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
todo

${"##"} Memory Allocation  
todo

