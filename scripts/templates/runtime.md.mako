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
- More than one device may be avilable in the system.
  
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
    ${x}_device_handle_t ${x}Device;
    ${x}DeviceGet(0, &${x}Device);
    
    // Create the context
    ${x}_context_desc_t desc;
    desc.version = ${X}_CONTEXT_DESC_VERSION;
    desc.numDevices = 1;
    desc.hDevices = &${x}Device;
    
    $x_context_handle_t hContext;
    if(${X}_RESULT_SUCCESS != ${x}ContextCreate(&desc, &hContext))
    {
        printf("Context creation failed.\n");
        return;
    }
    ...
```
  
${"##"} Memory Allocation  
todo

