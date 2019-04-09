# Programming Guide (Tools)

## Hardware Metrics

### Introduction

### Enumeration

Sample code
```cpp
xe_result_t MetricGroupEnumerationExample( xe_device_handle_t hDevice, uint32_t desiredSamplingType )
{
    // METRIC GROUP COUNT
    uint32_t metricGroupCount = 0;
    xetMetricGroupGetCount( hDevice, &metricGroupCount );

    // METRIC GROUPS
    for( uint32_t i = 0; i < metricGroupCount; i++ )
    {   
        xet_metric_group_handle_t hMetricGroup = NULL;
        xet_metric_group_properties_t metricGroupProperties = {XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT};

        xetMetricGroupGet( hDevice, i, &hMetricGroup );
        xetMetricGroupGetProperties( hMetricGroup, &metricGroupProperties );
        cout << "Metric Group: " << metricGroupProperties.name << "\n";

        if( (metricGroupProperties.samplingType & desiredSamplingType) == desiredSamplingType )
        {   
	        // METRICS
            for( uint32_t j = 0; j < metricGroupProperties.metricCount; j++ )	
            {
                xet_metric_handle_t metricHandle = NULL;
                xet_metric_properties_t metricProperties = {XET_METRIC_PROPERTIES_VERSION_CURRENT};

                xeMetricGet( hMetricGroup, j, &metricHandle );
                xeMetricGetProperties( metricHandle, &metricProperties );
                cout << "Metric: " << metricProperties.name << "\n";
            }
        }
    }
}
```

### Configuration

Use the `xetDeviceActivateMetricGroups` API call to configure the hardware for data collection.
Subsequent calls to the function will disable hardware programming for the metric groups not selected for activation.
To avoid bogous data only call the `xetDeviceActivateMetricGroups` between experiments i.e. while not collecting data.

Programming restrictions:
- any combination of metric groups can be configured simultanously provided that all of them have different `domain`s
- MetricGroup must be active until MetricQueryGetDeta and MetricTracerClose
- Conflicting Groups cannot be activated, in such case the call to ... would fail

### Collection

There are two modes of metrics collection supported: time based and query based.
Time based collection is using a timer as well as other events to store data samples in circular buffer. A metric tracer interface is a software interface for configuration and collection.
Query based metrics collection is based on a pair of Begin/End events appended to command lists. Query result generally characterizes hardware behavior between those events.

#### Time Based

Time based collection is using a simple Open/Wait/Read/Close scheme:
- `xetMetricTracerOpen` opens the tracer
- `xeEventHostSynchronize` and `xeEventQueryStatus` can be used to wait for data
- `xetMetricTracerReadData` reads the data
- `xetMetricTracerClose` closes the tracer

**Note:** to avoid incorrect data, do not reconfigure the hardware using `xetDeviceActivateMetricGroups` while the tracer is opened.

```cpp
xe_result_t TimeBasedUsageExample( xe_device_handle_t hDevice )
{
    xet_metric_group_handle_t     hMetricGroup           = NULL;
    xet_metric_group_properties_t metricGroupProperties  = {};
    xe_event_handle_t	          hNotificationEvent     = NULL;
    xe_event_desc_t               eventDesc              = {XE_EVENT_FLAG_DEVICE_TO_HOST};
    xet_metric_tracer_handle_t    hMetricTracer          = NULL;
    xet_metric_tracer_desc_t      metricTracerDescriptor = {XET_METRIC_TRACER_DESC_VERSION_CURRENT}; 

    // Find a "RenderBasic" metric group suitable for Time Based collection
    FindMetricGroup( hDevice, "RenderBasic", XET_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED, &hMetricGroup );
    xetMetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

    // Configure the HW
    xetDeviceActivateMetricGroup( hDevice, 1 /* count */, &hMetricGroup );

    // Open time based sampling
    xeDeviceCreateEvent( hDevice, &eventDesc, &hNotificationEvent );
    metricTracerDescriptor.hMetricGroup     	= hMetricGroup;
    metricTracerDescriptor.samplingPeriodNs 	= 1000;
    metricTracerDescriptor.notifyEveryNReports  = 32768;
    xetMetricTracerOpen( hDevice, &metricTracerDescriptor, hNotificationEvent, &hMetricTracer );

    // Run your workload, in this example we assume the data for the whole experiment fits in the hardware buffer
    Workload(hDevice);
    // Optionally insert markers during workload execution
    //xetCommandListAppendMetricTracerMarker( hCommandList, hMetricTracer, tool_marker_value ); 

    // Wait for data, optional in this example since the whole workload has already been executedby now
    //xeEventHostSynchronize( metricTracerDescriptor.hNotificationEvent, 1000 /*timeout*/ );
    // reset the event if it fired

    // Read raw data
    uint32_t reportCount = 0;
    xetMetricTracerReadData( hMetricTracer, &reportCount, 0, NULL ); // first check how many reports are available
    uint32_t size = metricGroupProperties.rawReportSize * reportCount;
    uint8_t* rawData = malloc(size); 
    xeMetricTracerGetData( hMetricTracer, &reportCount, size, rawData );

    // Close metric tracer
    xeMetricTracerClose( hMetricTracer );   

    // Deconfigure the hardware
    xetDeviceActivateMetricGroups( hDevice, 0, NULL );

    // Calculate metric data, TODO: clarify/cleanup
    uint32_t calculatedDataSize = 0;
    xetMetricGroupCalculateData( hMetricGroup, &reportCount, size, &calculatedDataSize, NULL );
    xet_typed_value_t* calculatedData = (xet_typed_value_t*)malloc( calculatedDataSize * sizeof(xet_typed_value_t) );
    xetMetricGroupCalculateData( hMetricGroup, &reportCount, size, &calculatedDataSize, calculatedData );
}
```

#### Queries

Query API provides a way of acquiring metrics per portions of workload delimited by BEGIN/END events.
Tpically multiple queries are used to characterize a workload so the API is pool based.
A metric query pool is created and destroyed using `xetMetricQueryPoolCreate` and `xetMetricQueryPoolDestroy` calls.
To work with individual query object, use `xetMetricQueryPoolGetMetricQuery` to get a handle.
Then insert BEGIN/END events into a command list using `xetCommandListAppendMetricQueryBegin` and `xetCommandListAppendMetricQueryEnd` calls.
Once the workload has been executed the `xetMetricQueryGetData` returns the raw data to be later processed by `xetMetricGroupCalculateData`.

```cpp
xe_result_t MetricQueryUsageExample( xe_device_handle_t hDevice )
{
    xet_metric_group_handle_t      hMetricGroup          = NULL;
    xet_metric_group_properties_t  metricGroupProperties = {XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT};
    xe_event_handle_t              hCompletionEvent      = NULL;
    xe_event_pool_desc_t           eventPoolDesc         = {XE_EVENT_POOL_DESC_VERSION_CURRENT};
    xe_event_pool_handle_t         hEventPool            = NULL;
    xet_metric_query_pool_handle_t hMetricQueryPool      = NULL;
    xet_metric_query_handle_t      hMetricQuery          = NULL;
    xet_metric_query_pool_desc_t   queryPoolDesc         = {XET_METRIC_QUERY_DESC_VERSION_CURRENT};
    
    // Find event metric group
    FindMetricGroup( hDevice, "RenderBasic", XET_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED, &hMetricGroup );
    xetMetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

    // Configure HW
    xetDeviceActivateMetricGroups( hDevice, 1 /* count */, &hMetricGroup );

    // Create metric query pool & completion event
    queryPoolDesc.flags        = XET_METRIC_QUERY_POOL_FLAG_PERORMANCE;
    queryPoolDesc.hMetricGroup = hMetricGroup;
    queryPoolDesc.slotCount    = 1000;
    xetMetricQueryPoolCreate( hDevice, &queryPoolDesc, &hMetricQueryPool );
    eventPoolDesc.flags = XE_EVENT_FLAG_DEVICE_TO_HOST;
    eventPoolDesc.count = 1000;
    xeEventPoolCreate( hDevice, &eventPoolDesc, &hEventPool );

    // Write BEGIN metric query to command list 
    xetMetricQueryPoolGetMetricQuery( hMetricQueryPool, 0 /*slot*/, &hMetricQuery );
    xetCommandListAppendMetricQueryBegin( hCommandList, hMetricQuery );

    // build your command list

    // Write END metric query to command list, use an event to determine if the data is available
    xeEventCreate( hEventPool, 0 /*slot*/, hCompletionEvent);
    xetCommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, 0 /*slot*/, hCompletionEvent );

    // use xeCommandQueueExecuteCommandLists to submit your workload to the hardware
   
    // Wait for data
    xeEventHostSynchronize( hCompletionEvent, 1000 /*timeout*/ );

    // Read raw data
    int size = metricGroupProperties.rawReportSize;
    uint8_t* rawData = malloc(size); 
    xetMetricQueryGetData( hMetricQuery, size, rawData );

    // Free the resources
    xeEventDestroy( hCompletionEvent );
    xeEventPoolDestroy( hEventPool );   
    xeMetricQueryDestroy( hMetricQuery );   

    // Deconfigure
    xetDeviceActivateMetricGroups( hDevice, 0, NULL );

    // Calculate metric data, TODO: clarify/cleanup
    uint32_t calculatedDataSize = 0;
    xetMetricGroupCalculateData( hMetricGroup, &reportCount, size, &calculatedDataSize, NULL );
    xet_typed_value_t* calculatedData = (xet_typed_value_t*)malloc( calculatedDataSize * sizeof(xet_typed_value_t) );
    xetMetricGroupCalculateData( hMetricGroup, &reportCount, size, &calculatedDataSize, calculatedData );
}
```

### Calculation

