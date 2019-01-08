# Programming Guide
The following documents the high-level programming models and guidelines.

## Initialization
The following code demonstrates a basic initialization sequence:  
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
    
```

## Command Queues and Command Lists
The following diagram illustrates the hierarchy of command lists to command queues and the device.
![Hierarchy](../images/cmdqueue.png?raw=true)

## Synchronization Events
