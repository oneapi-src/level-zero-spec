# Runtime API Programming Guide
The following documents the high-level programming models and guidelines.

@cond DEV
DO NOT EDIT: generated from /scripts/templates/runtime.md.mako
@endcond

## Introduction  
The Intel Xi Runtime API provides...
  
### Naming Convention  
todo: 
- all types follow **xi_\<name\>_t** convention
- all macros and enumerator values use all caps **XI_\<SCOPE\>_\<NAME\>** convention
- all functions use **xi\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters
  
### Error Handling  
todo:
- all apis return ::xi_result_t.
- apis are gaurenteed to never throw exceptions. etc.
  
## Context and Device  
![Context Hierarchy](../images/context.png?raw=true)
  
### Context  
- A context manages memory, command queues and programs for execution on one or more devices
  
### Device  
- A device represents a physical device in the system that can support Xi.
- More than one device may be avilable in the system.
  
### Initialization  
The following sample code demonstrates a basic initialization sequence:
```c
    // Initialize the runtime
    xiInit(XI_INIT_FLAG_NONE);

    // Get number of devices supporting Xi
    uint32_t deviceCount = 0;
    xiDeviceGetCount(&deviceCount);
    if(0 == deviceCount)
    {
        printf("There is no device supporting Xi.\n");
        return;
    }

    // Get the handle for device 0
    xi_device_handle_t xiDevice;
    xiDeviceGet(0, &xiDevice);
    
    // Create the context
    xi_context_desc_t desc;
    desc.version = XI_CONTEXT_DESC_VERSION;
    desc.numDevices = 1;
    desc.hDevices = &xiDevice;
    
    $x_context_handle_t hContext;
    if(XI_RESULT_SUCCESS != xiContextCreate(&desc, &hContext))
    {
        printf("Context creation failed.\n");
        return;
    }
    ...
```
  
## Memory Allocation  
todo

