# Core API Programming Guide

[DO NOT EDIT]: # (generated from /scripts/core/PROG.md)

The following documents the high-level programming models and guidelines.  

## Driver and Device
The following diagram illustrates the hierarchy of devices to the driver:  
![Driver Hierarchy](../images/core_driver.png?raw=true)

### Driver
- A driver represents an instance of a Xe driver being loaded and initialized into the current process.
- Only one instance of a driver per process can be loaded.
- There is no reference tracking if multiple drivers are initialized.
- A driver has minimal global state associated; only that which is sufficient for querying devices recognized by the driver.
 
### Device
- A device represents a physical device in the system that can support Xe.
- More than one device may be available in the system.
- The application is responsible for sharing memory and explicit submission and synchronization across multiple devices.

### Initialization
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

## Command Queues and Command Lists
The following diagram illustrates the hierarchy of command lists and command queues to the device:  
![Device Hierarchy](../images/core_queue.png?raw=true)

### Command Queues
- A command queue represents a physical input stream to the device.
- The number of simultaneous command queues per device is queried from calling 
  ::xeDeviceGetProperties; returned as ::xe_device_properties_t.numAsyncComputeEngines
  and ::xe_device_properties_t.numAsyncCopyEngines.
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
    xe_command_queue_desc_t commandQueueDesc = {
        XE_COMMAND_QUEUE_DESC_VERSION,
        XE_COMMAND_QUEUE_FLAG_NONE,
        XE_COMMAND_QUEUE_MODE_DEFAULT
    };
    xe_command_queue_handle_t hCommandQueue;
    xeDeviceCreateCommandQueue(hDevice, &commandQueueDesc, &hCommandQueue);

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
The following sample code demonstrates submission of commands to a command queue, via a command list:
```c
    // Encode kernel execution into a command list
    xeCommandListEncodeKernelExecution(hCommandList, hKernel);
    xeCommandListClose(hCommandList); // finished encoding commands

    // Enqueue command list execution into command queue
    xeCommandQueueEnqueueCommandList(hCommandQueue, hCommandList);
    xeCommandQueueSynchronize(hCommandQueue); // synchronize host and GPU

    // Reset (recycle) command list for new commands
    xeCommandListReset(hCommandList);
    ...
```

## Synchronization Primitives
There are three types of synchronization primitives:
1. **Fences** - used to communicate to the host that command queue execution has completed.
2. **Events** - used as fine-grain host-to-device, device-to-host or device-to-device waits and signals within a command list.
3. **Semaphores** - used for fine-grain control of command lists execution across multiple, simultaneous command queues within a device.

### Fences
- A fence is associated with single command queue.
- A fence can only be signaled from a device's command queue (e.g. between execution of command lists)
and can only be waited upon from the host.
- A fence only has two states: not signaled and signaled.
- A fence cannot be shared across processes.

The following sample code demonstrates a sequence for creation, submission and querying of a fence:
```c
    // Create fence
    xe_fence_desc_t fenceDesc = {
        XE_FENCE_DESC_VERSION,
        XE_FENCE_FLAG_NONE
    };
    xe_fence_handle_t hFence;
    xeDeviceCreateFence(hCommandQueue, &fenceDesc, &hFence);

    // Enqueue a signal of the fence into the command queue
    xeFenceEnqueueSignal(hFence);

    // Wait for fence to be signaled
    if(XE_RESULT_SUCCESS != xeFenceQueryStatus(hFence))
    {
        xeHostWaitOnFence(hFence);
    }

    xeFenceReset(hFence);
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
    xe_event_desc_t eventDesc = {
        XE_EVENT_DESC_VERSION,
        XE_EVENT_FLAG_NONE
    };
    xe_event_handle_t hEvent;
    xeDeviceCreateEvent(hDevice, &eventDesc, &hEvent);

    // Encode a wait on an event into a command list
    xeCommandListEncodeWaitOnEvent(hCommandList, hEvent);

    // Enqueue wait via the command list into a command queue
    xeCommandQueueEnqueueCommandList(hCommandQueue, hCommandList);

    // Signal the device
    xeHostSignalEvent(hEvent);
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
    xeCommandQueueEnqueueCommandList(hCommandQueue0, hCommandList0);
    xeCommandQueueEnqueueCommandList(hCommandQueue1, hCommandList1);
    ...
```

## Memory and Image Management
There are two types of allocations:
1. **Memory** - linear, unformatted allocations for direct access from both the host and device.
2. **Images** - non-linear, formatted allocations for direct access from the device.

### Memory
@todo Ben: describe standard, managed, and shared
@todo Ben: describe property and advise

### Images
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

### Device Cache Settings
@todo Ankur: global vs allocation vs command queue

### Device Residency
In most cases, the driver implicitly handles residency of allocations for device access.
This can be done by inspecting API parameters, including function arguments.

However, in cases where the driver is incapable of determining whether an allocation will be accessed by the device, such as multiple levels of indirection,
there are two methods available.
1. the application may set a flag during memory allocation to force the allocation to be always resident.
2. explcit APIs are included for the application to dynamically change residency as needed.

If the application does not properly manage residency for these cases then the device may experience unrecoverable page-faults.

```c
    struct node {
        node* next;
    };
    node* begin = nullptr;
    xeMemAlloc(hDevice, sizeof(node), &begin);
    xeMemAlloc(hDevice, sizeof(node), &begin->next);
    xeMemAlloc(hDevice, sizeof(node), &begin->next->next);

    // 'begin' is passed as function argument and encoded into command list
    ...

    // Make indirect allocations resident before enqueuing
    xeDeviceMakeMemoryResident(hDevice, begin->next, sizeof(node));
    xeDeviceMakeMemoryResident(hDevice, begin->next->next, sizeof(node));

    xeCommandQueueEnqueueCommandList(hCommandQueue, hCommandList);

    // wait until complete
    xeFenceEnqueueSignal(hFence);
    xeHostWaitOnFence(hFence);

    // Finally, evict to free device resources
    xeDeviceEvictMemory(hDevice, begin->next, sizeof(node));
    xeDeviceEvictMemory(hDevice, begin->next->next, sizeof(node));
    ...
```

## Modules and Functions
A Module represents a single translation unit that consists of functions that have been compiled together.

- Modules can be created from an IL or directly from native format using xeDeviceCreateModule.
  + xeDeviceCreateModule takes a format argument that specifies the input format.
  + xeDeviceCreateModule performs a compilation step when format is IL.


The following is an example function written in OCL C.
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
```

The following are the API calls for using this function.
```c
    ...
    // OCL C function has been compiled to SPIRV IL (pImageScalingIL)
    xe_module_handle_t hModule;
    xeDeviceCreateModule(hDevice, XE_MODULE_IL_SPIRV, ilSize, pImageScalingIL, &hModule);

    xe_function_handle_t hFunction;
    xeModuleCreateFunction(hModule, "image_scaling", &hFunction);

    xe_function_args_handle_t hFunctionArgs;
    xeFunctionCreateFunctionArgs(hFunction, &hFunctionArgs);

    // Bind arguments
    xeFunctionArgsSetValue(hFuncArgs, 0, sizeof(xe_image_handle_t), &src_image);
    xeFunctionArgsSetValue(hFuncArgs, 1, sizeof(xe_image_handle_t), &dest_image);
    xeFunctionArgsSetValue(hFuncArgs, 2, sizeof(uint32_t), &width);
    xeFunctionArgsSetValue(hFuncArgs, 3, sizeof(uint32_t), &height);

    // Encode dispatch command
    xeCommandListEncodeDispatchFunction(hCommandList, hFunction, hFunctionArgs, pixelRegionWidth, pixelRegionHeight, 1, numRegionsX, numRegionsY, 1);

    ...
	
    xeFunctionArgsDestroy(hFunctionArgs);
    xeFunctionDestroy(hFunction);
    xeModuleDestroy(hModule);
```

Argument indices can be queried from the function object by name.
```c
    ...
    
    uint32_t src_img_index;
    xeFunctionGetArgIndexFromName(hFunc, "src_img", &src_img_index);

    // Bind arguments
    xeFunctionArgsSetValue(hFuncArgs, src_img_index, sizeof(xe_image_handle_t), &src_image);

    ...
```

### Occupancy
@todo Zack: write-up section

## OpenCL Interoperability
There are three OpenCL objects that can be shared for interoperability:
1. **cl_mem** - an OpenCL buffer object
2. **cl_program** - an OpenCL program object
3. **cl_command_queue** - an OpenCL command queue object

### cl_mem
@todo Ben any details about memory sharing

### cl_program
@todo Zack any details about program sharing
- clBuildProgram or clCompileProgram/clLinkProgram must be called prior to $xDeviceRegisterCLProgram

### cl_command_queue
@todo Brandon any details about command queue sharing
- clFlush must be called prior to any xeCommandQueueEnqueue* function

