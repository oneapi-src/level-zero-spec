# Programming Guide
The following documents the high-level programming models and guidelines.

## Initialization
The following sample code demonstrates a basic initialization sequence:
```c
    // Initialize the driver
    xeInit(XE_INIT_FLAG_NONE);

    // Get number of devices supporting XE
    uint32_t deviceCount = 0;
    xeDeviceGetCount(&deviceCount);
    if( 0 == deviceCount )
    {
        printf("There is no device supporting XE.\n");
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

The following sample code demonstrates submission of commands to a command queue, via a command list:
```c
    // Encode kernel execution into a command list
    xeCommandListEncodeKernelExecution( xeCommandList, xeKernel );
    xeCommandListClose( xeCommandList ); // finished encoding commands

    // Enqueue command list execution into command queue
    xeCommandQueueEnqueueCommandList( xeCommandQueue, xeCommandList );
    xeCommandQueueSynchronize( xeCommandQueue ); // synchronize host and GPU

    // Reset (recycle) command list for new commands
    xeCommandListReset( xeCommandList );
    ...
```

## Synchronization Events

The following sample code demonstrates a sequence for creation of multiple event objects from a single allocation:
```c
    // Allocate memory for event(s)
    xe_device_ptr_t ptr = nullptr;
    xeMemAlloc(2 * sizeof(xe_event_value_t), &ptr);

    // Create event(s)
    xe_event_desc_t xeEventDesc = {
        XE_EVENT_DESC_VERSION,
        XE_EVENT_FLAG_NONE,
        nullptr
    };
    xe_event_handle_t xeEvent[2];

    xeEventDesc.location = reinterpret_cast<xe_event_value_t>(ptr);
    xeEventCreate(xeDevice, &xeEventDesc, &xeEvent[0]);

    xeEventDesc.location += 1;
    xeEventCreate(xeDevice, &xeEventDesc, &xeEvent[1]);
    ...
```

